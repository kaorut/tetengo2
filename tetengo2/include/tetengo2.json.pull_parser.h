/*! \file
    \brief The definition of tetengo2::json::pull_parser.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_JSON_PULLPARSER_H)
#define TETENGO2_JSON_PULLPARSER_H

#include <memory>
#include <utility>

#include <boost/noncopyable.hpp>

#include "tetengo2.concurrent.channel.h"
#include "tetengo2.concurrent.consumer.h"
#include "tetengo2.concurrent.producer.h"


namespace tetengo2 { namespace json
{
    /*!
        \brief The class template for a pull parser.

        \tparam PushParser A push parser type.
        \tparam Size       A size type.
    */
    template <typename PushParser, typename Size>
    class pull_parser : private boost::noncopyable
    {
    public:
        // types

        //! The push parser type.
        typedef PushParser push_parser_type;

        //! The size type.
        typedef Size size_type;


        // constructors and destructor

        /*!
            \brief Creates a pull parser.

            \param p_push_parser    A unique pointer to a push parser.
            \param channel_capacity A channel capacity.
                                    It must be greater than 0.
        */
        pull_parser(
            std::unique_ptr<push_parser_type> p_push_parser,
            const size_type                   channel_capacity

        )
        :
        m_p_push_parser(std::move(p_push_parser)),
        m_channel(channel_capacity),
        m_producer(generate, m_channel)
        {}


        // functions


    private:
        // types

        typedef int channel_element_type;

        typedef
            concurrent::channel<channel_element_type, size_type> channel_type;

        typedef concurrent::producer<channel_type> producer_type;

        typedef concurrent::consumer<channel_type> consumer_type;


        // static functions

        static void generate(channel_type& channel)
        {

        }


        // variables

        const std::unique_ptr<push_parser_type> m_p_push_parser;

        channel_type m_channel;

        producer_type m_producer;

        
    };


}}


#endif
