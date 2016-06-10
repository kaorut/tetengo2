/*! \file
    \brief The definition of tetengo2::concurrent::channel.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CHANNEL_H)
#define TETENGO2_CONCURRENT_CHANNEL_H

#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <exception>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a channel.

        \tparam T A type.
    */
    template <typename T>
    class channel : private boost::noncopyable
    {
    public:
        // types

        //! The value type.
        using value_type = T;

        //! The size type.
        using size_type = type_list::size_type;


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
        m_capacity(capacity),
        m_close_requested(false)
        {
            if (capacity == 0)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Capacity is zero." }));
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
            std::unique_lock<mutex_type> lock{ m_mutex };
            m_condition_variable.wait(lock, [this]() { return this->can_take(); });
            if (closed_impl())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The channel is already closed." }));

            if (m_queue.front()->which() == 0)
            {
                return boost::get<value_type>(*m_queue.front());
            }
            else
            {
                assert(m_queue.front()->which() == 1);

                std::rethrow_exception(boost::get<std::exception_ptr>(*m_queue.front()));
                
                assert(false);
                BOOST_THROW_EXCEPTION((std::logic_error{ "Must not come here." }));
            }
        }

        /*!
            \brief Takes a value.

            \throw std::logic_error When the channel is already closed.
        */
        void take()
        {
            std::unique_lock<mutex_type> lock{ m_mutex };
            m_condition_variable.wait(lock, [this]() { return this->can_take(); });
            if (closed_impl())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The channel is already closed." }));

            m_queue.pop();

            m_condition_variable.notify_all();
        }

        /*!
            \brief Checks whether the channel close is requested.

            \retval true  When the channel close is requested.
            \retval false Otherwise.
        */
        bool close_requested()
        const
        {
            std::unique_lock<mutex_type> lock{ m_mutex };
            return m_close_requested;
        }

        /*!
            \brief Request the channel to close.
        */
        void request_close()
        {
            std::unique_lock<mutex_type> lock{ m_mutex };
            m_close_requested = true;
        }

        /*!
            \brief Closes the channel.
        */
        void close()
        {
            std::unique_lock<mutex_type> lock{ m_mutex };
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
            std::unique_lock<mutex_type> lock{ m_mutex };
            m_condition_variable.wait(lock, [this]() { return this->can_take(); });
            return closed_impl();
        }


    private:
        // types

        using mutex_type = std::mutex;

        using condition_variable_type = std::condition_variable;

        using queue_element_type = boost::variant<value_type, std::exception_ptr>;

        using queue_type = std::queue<boost::optional<queue_element_type>>;


        // variables

        mutable mutex_type m_mutex;

        mutable condition_variable_type m_condition_variable;

        queue_type m_queue;

        const size_type m_capacity;

        bool m_close_requested;


        // functions

        bool closed_impl()
        const
        {
            return !m_queue.empty() && !m_queue.front();
        }

        void insert_impl(queue_element_type value)
        {
            std::unique_lock<mutex_type> lock{ m_mutex };
            m_condition_variable.wait(lock, [this]() { return this->can_insert(); });
            if (can_take() && !m_queue.back())
            {
                m_condition_variable.notify_all();
                return;
            }

            m_queue.emplace(queue_element_type{ std::move(value) });

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
