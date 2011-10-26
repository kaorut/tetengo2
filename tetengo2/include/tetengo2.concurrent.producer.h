/*! \file
    \brief The definition of tetengo2::concurrent::producer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PRODUCER_H)
#define TETENGO2_CONCURRENT_PRODUCER_H

//#include <functional>

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

        //! The generator type.
        typedef std::function<void (channel_type&)> generator_type;


        // constructors and destructor

        /*!
            \brief Creates a producer.

            \param generator A generator.
            \param channel   A channel.
        */
        producer(
            const generator_type generator,
            channel_type&        channel
        )
        :
        m_thread(
            TETENGO2_CPP11_BIND(generator, tetengo2::cpp11::ref(channel))
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

        boost::thread m_thread;


    };


}}


#endif
