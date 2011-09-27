/*! \file
    \brief The definition of tetengo2::concurrent::consumer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CONSUMER_H)
#define TETENGO2_CONCURRENT_CONSUMER_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a consumer.

        \tparam Value   A value type.
        \tparam Channel A channel type.
    */
    template <typename Value, typename Channel>
    class consumer : private boost::noncopyable
    {
    public:
        // types

        //! The value type.
        typedef Value value_type;

        //! The channel type.
        typedef Channel channel_type;


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
            \brief Takes a value.

            It extracts a value from the channel and the channel is shrinked.

            \return A value.
        */
        value_type pop()
        {
            return m_channel.pop();
        }


    private:
        // variables

        channel_type& m_channel;


    };


}}


#endif
