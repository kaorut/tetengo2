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
        m_condition_variable()
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

        }

        /*!
            \brief Takes a value.

            \return A value.

            \throw boost::thread_interrupted When the thread is interrupted.
        */
        value_type take()
        {
            boost::unique_lock<mutex_type> lock(m_mutex);

            return value_type();
        }


    private:
        // types

        typedef boost::mutex mutex_type;

        typedef boost::condition_variable condition_variable_type;


        // variables

        mutex_type m_mutex;

        condition_variable_type m_condition_variable;


    };


}}


#endif
