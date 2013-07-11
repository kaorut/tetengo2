/*! \file
    \brief The definition of tetengo2::concurrent::channel.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CHANNEL_H)
#define TETENGO2_CONCURRENT_CHANNEL_H

#include <cassert>
#include <exception>
#include <queue>
#include <stdexcept>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a channel.

        \tparam T    A type.
        \tparam Size A size type.
    */
    template <typename T, typename Size>
    class channel : private boost::noncopyable
    {
    public:
        // types

        //! The value type.
        typedef T value_type;

        //! The size type.
        typedef Size size_type;


        // constructors and destructor

        /*!
            \brief Creates a channel.

            \param capacity A capacity.

            \throw std::invalid_argument When capacity is equal to 0.
        */
        explicit channel(const size_type capacity)
        :
        m_mutex(),
        m_condition_variable(),
        m_queue(),
        m_capacity(capacity)
        {
            if (capacity == 0)
                BOOST_THROW_EXCEPTION(std::invalid_argument("Capacity is zero."));
        }


        // functions
        
        /*!
            \brief Inserts a value.

            The values inserted after a close() call are just discarded.

            \param value A value.
        */
        void insert(value_type value)
        {
            insert_impl(std::move(value));
        }

        /*!
            \brief Inserts an exception.

            The exceptions inserted after a close() call are just discarded.

            \param p_exception A pointer to an exceptoin.
        */
        void insert_exception(const std::exception_ptr& p_exception)
        {
            insert_impl(p_exception);
        }

        /*!
            \brief Peeks a value.

            It just peeks a value, doesn't extract the one.

            \return A value.

            \throw unspecified      An exception inserted with insert_exception().
            \throw std::logic_error When the channel is already closed.
        */
        const value_type& peek()
        const
        {
            typename cpp11::unique_lock<mutex_type>::type lock(m_mutex);
            m_condition_variable.wait(lock, [this]() { return this->can_take(); });
            if (closed_impl())
                BOOST_THROW_EXCEPTION(std::logic_error("The channel is already closed."));

            if (m_queue.front()->which() == 0)
            {
                return boost::get<value_type>(*m_queue.front());
            }
            else
            {
                assert(m_queue.front()->which() == 1);

                std::rethrow_exception(boost::get<std::exception_ptr>(*m_queue.front()));
                
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Must not come here."));
            }
        }

        /*!
            \brief Takes a value.

            \throw std::logic_error When the channel is already closed.
        */
        void take()
        {
            typename cpp11::unique_lock<mutex_type>::type lock(m_mutex);
            m_condition_variable.wait(lock, [this]() { return this->can_take(); });
            if (closed_impl())
                BOOST_THROW_EXCEPTION(std::logic_error("The channel is already closed."));

            m_queue.pop();

            m_condition_variable.notify_all();
        }

        /*!
            \brief Closes the channel.
        */
        void close()
        {
            typename cpp11::unique_lock<mutex_type>::type lock(m_mutex);
            m_condition_variable.wait(lock, [this]() { return this->can_insert(); });
            if (can_take() && !m_queue.back())
            {
                m_condition_variable.notify_all();
                return;
            }

            m_queue.push(boost::none);

            m_condition_variable.notify_all();
        }

        /*!
            \brief Checks whether the channel is closed.

            \retval true  When the channel is closed.
            \retval false Otherwise.
        */
        bool closed()
        const
        {
            typename cpp11::unique_lock<mutex_type>::type lock(m_mutex);
            m_condition_variable.wait(lock, [this]() { return this->can_take(); });
            return closed_impl();
        }


    private:
        // types

        typedef cpp11::mutex mutex_type;

        typedef cpp11::condition_variable condition_variable_type;

        typedef boost::variant<value_type, std::exception_ptr> queue_element_type;

        typedef std::queue<boost::optional<queue_element_type>> queue_type;


        // variables

        mutable mutex_type m_mutex;

        mutable condition_variable_type m_condition_variable;

        queue_type m_queue;

        const size_type m_capacity;


        // functions

        bool closed_impl()
        const
        {
            return !m_queue.empty() && !m_queue.front();
        }

        void insert_impl(queue_element_type value)
        {
            typename cpp11::unique_lock<mutex_type>::type lock(m_mutex);
            m_condition_variable.wait(lock, [this]() { return this->can_insert(); });
            if (can_take() && !m_queue.back())
            {
                m_condition_variable.notify_all();
                return;
            }

            m_queue.emplace(queue_element_type(std::move(value)));

            m_condition_variable.notify_all();
        }

        bool can_insert()
        const
        {
            return m_queue.size() < m_capacity;
        }

        bool can_take()
        const
        {
            return !m_queue.empty();
        }


    };


}}


#endif
