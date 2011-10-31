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
        */
        channel(const size_type capacity)
        :
        m_mutex(),
        m_condition_variable(),
        m_queue(),
        m_capacity(capacity)
        {}


        // functions
        
        /*!
            \brief Inserts a value.

            \tparam V A value type.

            \param value A value.

            \throw std::logic_error          When the insertion is already
                                             finished.
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
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The insertion is already finished.")
                );
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

            \param p_exception A pointer to an exceptoin.

            \throw std::logic_error          When the insertion is already
                                             finished.
            \throw boost::thread_interrupted When the thread is interrupted.
        */
        void insert_exception(const boost::exception_ptr& p_exception)
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_insert, this)
            );
            if (can_take() && !m_queue.back())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The insertion is already finished.")
                );
            }

            m_queue.push(
                boost::make_optional(queue_element_type(p_exception))
            );

            m_condition_variable.notify_all();
        }

        /*!
            \brief Takes a value.

            \return A value.

            \throw unspecified               An exception inserted with
                                             insert_exception().
            \throw std::logic_error          When the channel has no more
                                             element.
            \throw boost::thread_interrupted When the thread is interrupted.
        */
        value_type take()
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_take, this)
            );
            if (has_no_more_impl())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The channel has no more element.")
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
            \brief Finishes the insertion.

            \throw std::logic_error          When the insertion is already
                                             finished.
            \throw boost::thread_interrupted When the thread is interrupted.
        */
        void finish_insertion()
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_insert, this)
            );
            if (can_take() && !m_queue.back())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The insertion is already finished.")
                );
            }

            m_queue.push(boost::none);

            m_condition_variable.notify_all();
        }

        /*!
            \brief Checks whether the channel has no more element.

            \retval true  When the channel has no more element.
            \retval false Otherwise.
        */
        bool has_no_more()
        const
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_take, this)
            );
            return has_no_more_impl();
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

        bool has_no_more_impl()
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
