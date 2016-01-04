/*! \file
    \brief The definition of tetengo2::concurrent::producer.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PRODUCER_H)
#define TETENGO2_CONCURRENT_PRODUCER_H

#include <exception>
#include <functional>
#include <thread>

#include <boost/core/noncopyable.hpp>


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
        using channel_type = Channel;

        //! The generator type.
        using generator_type = std::function<void (channel_type&)>;


        // constructors and destructor

        /*!
            \brief Creates a producer.

            \param generator A generator.
            \param channel   A channel.
        */
        producer(const generator_type generator, channel_type& channel)
        :
#if !defined(DOCUMENTATION) // Doxygen warning suppression
        m_thread_procedure_impl([generator, &channel]() { generator(channel); }),
        m_channel(channel),
        m_thread([this, &channel]() { thread_procedure(this->m_thread_procedure_impl, channel); })
#endif
        {}

        /*!
            \brief Destroys the producer.
        */
        ~producer()
        noexcept
        {
            join();
        }


        // functions
        
        /*!
            \brief Joins the producing thread.
        */
        void join()
        {
            m_channel.close();
            if (m_thread.joinable())
                m_thread.join();
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
                channel.insert_exception(std::current_exception());
                channel.close();
            }
        }


        // variables

        std::function<void ()> m_thread_procedure_impl;

        channel_type& m_channel;

        std::thread m_thread;


    };


}}


#endif
