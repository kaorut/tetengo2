/*! \file
    \brief The definition of tetengo2::concurrent::consumer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CONSUMER_H)
#define TETENGO2_CONCURRENT_CONSUMER_H

#include <stdexcept>

#include <boost/noncopyable.hpp>


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
        typedef Channel channel_type;

        //! The value type.
        typedef typename channel_type::value_type value_type;


        // constructors and destructor

        /*!
            \brief Creates a consumer.

            \param channel A channel.
        */
        explicit consumer(channel_type& channel)
        :
        m_channel(channel)
        {}


        // functions
        
        /*!
            \brief Checks whether the channel is empty.

            \retval true  When the channel is empty.
            \retval false Otherwise.
        */
        bool empty()
        const
        {
            return m_channel.empty();
        }

        /*!
            \brief Pops and return a value.

            It extracts a value from the channel and the channel is shrinked.

            \return A value.

            \throw std::logic_error When the channel is empty.
        */
        value_type pop()
        {
            if (empty())
                throw std::logic_error("The channel is empty.");

            return m_channel.pop();
        }


    private:
        // variables

        channel_type& m_channel;


    };


}}


#endif
