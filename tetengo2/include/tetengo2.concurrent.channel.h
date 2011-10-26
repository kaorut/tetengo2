/*! \file
    \brief The definition of tetengo2::concurrent::channel.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CHANNEL_H)
#define TETENGO2_CONCURRENT_CHANNEL_H

#include <queue>

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

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

            \throw boost::thread_interrupted When the thread is interrupted.
        */
        template <typename V>
        void insert(V&& value)
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_insert, this)
            );

            m_queue.push(value);

            m_condition_variable.notify_all();
        }

        /*!
            \brief Takes a value.

            \return A value.

            \throw boost::thread_interrupted When the thread is interrupted.
        */
        value_type take()
        {
            boost::unique_lock<mutex_type> lock(m_mutex);
            m_condition_variable.wait(
                lock, TETENGO2_CPP11_BIND(&channel::can_take, this)
            );

            const value_type value = std::move(m_queue.front());
            m_queue.pop();

            m_condition_variable.notify_all();

            return value;
        }


    private:
        // types

        typedef boost::mutex mutex_type;

        typedef boost::condition_variable condition_variable_type;

        typedef std::queue<value_type> queue_type;


        // variables

        mutex_type m_mutex;

        condition_variable_type m_condition_variable;

        queue_type m_queue;

        const size_type m_capacity;


        // functions

        bool can_insert()
        const
        {
            return m_queue.size() < m_capacity;
        }

        bool can_take()
        {
            return !m_queue.empty();
        }


    };


}}


#endif
