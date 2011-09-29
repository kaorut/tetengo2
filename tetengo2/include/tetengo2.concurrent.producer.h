/*! \file
    \brief The definition of tetengo2::concurrent::producer.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PRODUCER_H)
#define TETENGO2_CONCURRENT_PRODUCER_H

#include <boost/noncopyable.hpp>


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


        // constructors and destructor

        /*!
            \brief Creates a producer.

            \param channel A channel.
        */
        explicit producer(channel_type& channel)
        :
        m_channel(channel)
        {}


        // functions
        
        /*!
            \brief Joins the producing thread.
        */
        void join()
        {

        }


    private:
        // variables

        channel_type& m_channel;


    };


}}


#endif
