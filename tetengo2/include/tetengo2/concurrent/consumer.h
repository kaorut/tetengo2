/*! \file
    \brief The definition of tetengo2::concurrent::consumer.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CONSUMER_H)
#define TETENGO2_CONCURRENT_CONSUMER_H

#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/concurrent/channel.h>


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a consumer.

        \tparam T A type.
    */
    template <typename T>
    class consumer : private boost::noncopyable
    {
    public:
        // types

        //! The value type.
        using value_type = T;

        //! The channel type.
        using channel_type = channel<T>;


        // constructors and destructor

        /*!
            \brief Creates a consumer.

            \param channel A channel.
        */
        explicit consumer(channel_type& channel)
        :
        m_channel(channel)
        {}

        /*!
            \brief Destroys the consumer.
        */
        ~consumer()
        noexcept
        {
            try
            {
                m_channel.request_close();
                while (!closed())
                    take();
            }
            catch (...)
            {}
        }


        // functions
        
        /*!
            \brief Checks whether the channel is closed.

            \retval true  When the channel is closed.
            \retval false Otherwise.
        */
        bool closed()
        const
        {
            return m_channel.closed();
        }

        /*!
            \brief Peeks a value.

            It just peeks a value, doesn't extract the one.

            \return A value.

            \throw std::logic_error When the channel is closed.
        */
        const value_type& peek()
        const
        {
            if (closed())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The channel is already closed." }));

            return m_channel.peek();
        }

        /*!
            \brief Takes a value.

            It extracts a value from the channel and the channel is shrinked.

            \throw std::logic_error When the channel is closed.
        */
        void take()
        {
            if (closed())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The channel is already closed." }));

            m_channel.take();
        }


    private:
        // variables

        channel_type& m_channel;


    };


}}


#endif
