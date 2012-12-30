/*! \file
    \brief The definition of tetengo2::concurrent::producer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PRODUCER_H)
#define TETENGO2_CONCURRENT_PRODUCER_H

//#include <functional>

#include <boost/exception_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.unique.h"


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
        producer(const generator_type generator, channel_type& channel)
        :
        m_thread_procedure_impl(TETENGO2_CPP11_BIND(generator, cpp11::ref(channel))),
        m_channel(channel),
        m_thread(TETENGO2_CPP11_BIND(&producer::thread_procedure, m_thread_procedure_impl, cpp11::ref(channel)))
        {}


        // functions
        
        /*!
            \brief Joins the producing thread.
        */
        void join()
        {
            try
            {
                m_channel.close();
                m_thread.join();
            }
            catch (const boost::thread_interrupted& e)
            {
                m_channel.insert_exception(boost::copy_exception(e));
                m_channel.close();
            }
        }


    private:
        // static functions

        static void thread_procedure(const std::function<void ()> thread_procedure_impl, channel_type& channel)
        {
            try
            {
                thread_procedure_impl();
                channel.close();
            }
            catch (...)
            {
                channel.insert_exception(boost::current_exception());
                channel.close();
            }
        }


        // variables

        std::function<void ()> m_thread_procedure_impl;

        channel_type& m_channel;

        boost::thread m_thread;


    };


}}


#endif
