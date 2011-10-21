/*! \file
    \brief The definition of tetengo2::concurrent::channel.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_CHANNEL_H)
#define TETENGO2_CONCURRENT_CHANNEL_H

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a channel.
    */
    class channel : private boost::noncopyable
    {
    public:
        // types


        // constructors and destructor

        /*!
            \brief Creates a channel.
        */
        channel()
        {}


        // functions
        

    private:
        // variables


    };


}}


#endif
