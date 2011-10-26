/*! \file
    \brief The definition of tetengo2::concurrent::channel.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CHANNEL_H)
#define TETENGO2_CONCURRENT_CHANNEL_H

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
        {}

        /*!
            \brief Takes a value.

            \return A value.

            \throw boost::thread_interrupted When the thread is interrupted.
        */
        value_type take()
        {
            return value_type();
        }


    private:
        // variables


    };


}}


#endif
