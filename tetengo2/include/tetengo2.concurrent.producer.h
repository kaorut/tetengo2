/*! \file
    \brief The definition of tetengo2::concurrent::producer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PRODUCER_H)
#define TETENGO2_CONCURRENT_PRODUCER_H

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include "tetengo2.cpp11.h"


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a producer.

        \tparam Channel A channel type.
    */
    template <typename Channel>
    class producer : private boost::noncopyable
    {
    public:
        // types

        //! The channel type.
        typedef Channel channel_type;

        //! The value type.
        typedef typename channel_type::value_type value_type;


        // constructors and destructor

        /*!
            \brief Creates a producer.

            \tparam Generator A generator type.
                              It must be a unary function, which returns void,
                              and whose parameter is a channel.

            \param channel   A channel.
            \param generator A generator.
        */
        template <typename Generator>
        explicit producer(channel_type& channel, const Generator& generator)
        :
        m_channel(channel),
        m_thread(
            TETENGO2_CPP11_BIND(generator, tetengo2::cpp11::ref(m_channel))
        )
        {}


        // functions
        
        /*!
            \brief Joins the producing thread.
        */
        void join()
        {
            m_thread.join();
        }


    private:
        // variables

        channel_type& m_channel;

        boost::thread m_thread;


    };


}}


#endif
