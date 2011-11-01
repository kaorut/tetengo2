/*! \file
    \brief The definition of tetengo2::concurrent::producer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PRODUCER_H)
#define TETENGO2_CONCURRENT_PRODUCER_H

#include <cassert>
//#include <functional>

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
        producer(
            const generator_type generator,
            channel_type&        channel
        )
        :
        m_p_thread(),
        m_thread_procedure_impl(
            TETENGO2_CPP11_BIND(generator, tetengo2::cpp11::ref(channel))
        ),
        m_channel(channel)
        {
            m_p_thread =
                tetengo2::make_unique<boost::thread>(
                    TETENGO2_CPP11_BIND(&producer::thread_procedure, this)
                );
        }


        // functions
        
        /*!
            \brief Joins the producing thread.
        */
        void join()
        {
            try
            {
                assert(m_p_thread);
                m_p_thread->join();
            }
            catch (const boost::thread_interrupted& e)
            {
                m_channel.insert_exception(boost::copy_exception(e));
                m_channel.finish_insertion();
            }
        }


    private:
        // variables

        std::unique_ptr<boost::thread> m_p_thread;

        std::function<void ()> m_thread_procedure_impl;

        channel_type& m_channel;


        // functions

        void thread_procedure()
        {
            try
            {
                m_thread_procedure_impl();
            }
            catch (const std::exception& e)
            {
                m_channel.insert_exception(boost::copy_exception(e));
                m_channel.finish_insertion();
            }
            catch (...)
            {
                m_channel.insert_exception(boost::current_exception());
                m_channel.finish_insertion();
            }
        }


    };


}}


#endif
