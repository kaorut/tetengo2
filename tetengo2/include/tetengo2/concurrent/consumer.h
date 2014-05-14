/*! \file
    \brief The definition of tetengo2::concurrent::consumer.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CONSUMER_H)
#define TETENGO2_CONCURRENT_CONSUMER_H

#include <stdexcept>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a consumer.

        \tparam Channel A channel type.
    */
    template <typename Channel>
    class consumer : private boost::noncopyable
    {
    public:
        // types

        //! The channel type.
        using channel_type = Channel;

        //! The value type.
        using value_type = typename channel_type::value_type;


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
        TETENGO2_STDALT_NOEXCEPT
        {
            try
            {
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
                BOOST_THROW_EXCEPTION(std::logic_error("The channel is already closed."));

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
                BOOST_THROW_EXCEPTION(std::logic_error("The channel is already closed."));

            m_channel.take();
        }


    private:
        // variables

        channel_type& m_channel;


    };


}}


#endif
