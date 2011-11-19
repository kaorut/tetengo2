/*! \file
    \brief The definition of tetengo2::concurrent::channel.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CHANNEL_H)
#define TETENGO2_CONCURRENT_CHANNEL_H

#include <cassert>
#include <queue>
#include <stdexcept>
#include <utility>

#include <boost/exception_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant.hpp>

#include "tetengo2.cpp11.h"


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
        channel(const size_type capacity)
        :
        m_mutex(),
        m_condition_variable(),
        m_queue(),
        m_capacity(capacity)
        {
            if (capacity == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Capacity is zero.")
                );
            }
        }


        // functions
        
        /*!
            \brief Inserts a value.

            The values inserted after a close() call are just discarded.

            \tparam V A value type.

            \param value A value.

            \throw boost::thread_interrupted When the thread is interrupted.
        */
        template <typename V>
        void insert(V&& value)
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_insert, this)
            );
            if (can_take() && !m_queue.back())
            {
                m_condition_variable.notify_all();
                return;
            }

            m_queue.push(
                boost::make_optional(
                    queue_element_type(std::forward<V>(value))
                )
            );

            m_condition_variable.notify_all();
        }

        /*!
            \brief Inserts an exception.

            The exceptions inserted after a close() call are just discarded.

            \param p_exception A pointer to an exceptoin.

            \throw boost::thread_interrupted When the thread is interrupted.
        */
        void insert_exception(const boost::exception_ptr& p_exception)
        {
            insert(p_exception);
        }

        /*!
            \brief Peeks a value.

            It just peeks a value, doesn't extract the one.

            \return A value.

            \throw unspecified               An exception inserted with
                                             insert_exception().
            \throw std::logic_error          When the channel is already
                                             closed.
            \throw boost::thread_interrupted When the thread is interrupted.
        */
        const value_type& peek()
        const
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_take, this)
            );
            if (closed_impl())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The channel is already closed.")
                );
            }

            if (m_queue.front()->which() == 0)
            {
                return boost::get<value_type>(*m_queue.front());
            }
            else
            {
                assert(m_queue.front()->which() == 1);

                boost::rethrow_exception(
                    boost::get<boost::exception_ptr>(*m_queue.front())
                );
            }
        }

        /*!
            \brief Takes a value.

            \return A value.

            \throw unspecified               An exception inserted with
                                             insert_exception().
            \throw std::logic_error          When the channel is already
                                             closed.
            \throw boost::thread_interrupted When the thread is interrupted.
        */
        value_type take()
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_take, this)
            );
            if (closed_impl())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The channel is already closed.")
                );
            }

            if (m_queue.front()->which() == 0)
            {
                const value_type value =
                    std::move(boost::get<value_type>(*m_queue.front()));
                m_queue.pop();

                m_condition_variable.notify_all();

                return value;
            }
            else
            {
                assert(m_queue.front()->which() == 1);

                const boost::exception_ptr p_exception =
                    std::move(
                        boost::get<boost::exception_ptr>(*m_queue.front())
                    );
                m_queue.pop();

                m_condition_variable.notify_all();

                boost::rethrow_exception(p_exception);
            }
        }

        /*!
            \brief Closes the channel.

            \throw boost::thread_interrupted When the thread is interrupted.
        */
        void close()
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            if (can_take() && !m_queue.back())
            {
                m_condition_variable.notify_all();
                return;
            }

            m_queue.push(boost::none);
            assert(m_queue.size() <= m_capacity + 1);

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
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_take, this)
            );
            return closed_impl();
        }


    private:
        // types

        typedef boost::mutex mutex_type;

        typedef boost::condition_variable condition_variable_type;

        typedef
            boost::variant<value_type, boost::exception_ptr>
            queue_element_type;

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
