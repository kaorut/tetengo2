/*! \file
    \brief The definition of test_tetengo2::type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_TYPELIST_H)
#define TESTTETENGO2_TYPELIST_H

//#include <cstddef>
//#include <iterator>
//#include <string>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>

#include "tetengo2.detail.stub.config.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.message.message_catalog.h"
#include "tetengo2.message.message_catalog_parser.h"
#include "tetengo2.message.messages.h"
#include "tetengo2.meta.assoc_list.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.text.grammar.json.h"
#include "tetengo2.text.pull_parser.h"
#include "tetengo2.text.push_parser.h"


namespace test_tetengo2
{
    /**** Common ************************************************************/

    namespace type
    {
        struct size;           //!< The size type.
        struct string;         //!< The string type.
        struct io_string;      //!< The I/O string type.
    }

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, std::string>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::io_string, std::string>,
        tetengo2::meta::assoc_list_end
        >>>
        type_list;


    /**** Configuration *****************************************************/

    namespace type { namespace config
    {
        struct encoder;        //!< The encoder tyep.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace config
    {
        typedef tetengo2::detail::stub::encoding encoding_details_type;
        typedef
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::string>::type, encoding_details_type>
            internal_encoding_type;
        typedef
            tetengo2::text::encoding::locale<tetengo2::detail::stub::config::string_type, encoding_details_type>
            config_encoding_type;
        typedef tetengo2::text::encoder<internal_encoding_type, config_encoding_type> encoder_type;
    }}
#endif

    //! The configuration type list.
    typedef
        tetengo2::meta::assoc_list<boost::mpl::pair<type::config::encoder, detail::config::encoder_type>,
        tetengo2::meta::assoc_list_end
        >
        config_type_list;


    /**** Text **************************************************************/

    namespace type { namespace text
    {
        struct input_stream_iterator; //!< The input stream iterator type.
        struct grammar;        //!< The grammar type.
        struct push_parser;    //!< The push parser type.
        struct pull_parser;    //!< The pull parser type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace text
    {
        typedef
            boost::spirit::multi_pass<
                std::istreambuf_iterator<boost::mpl::at<type_list, type::io_string>::type::value_type>
            >
            input_stream_iterator_type;
        typedef tetengo2::text::grammar::json<input_stream_iterator_type> grammar_type;
        typedef tetengo2::text::push_parser<input_stream_iterator_type, grammar_type, int, double> push_parser_type;
    }}
#endif

    //! The text type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::text::input_stream_iterator, detail::text::input_stream_iterator_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::text::grammar, detail::text::grammar_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::text::push_parser, detail::text::push_parser_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::text::pull_parser,
                tetengo2::text::pull_parser<
                    detail::text::push_parser_type, boost::mpl::at<type_list, type::size>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>
        text_type_list;


    /**** Message ***********************************************************/

    namespace type { namespace message
    {
        struct message_catalog_parser; //!< The message catalog parser type.
        struct messages;        //!< The messages type.
        struct message_catalog; //!< The message catalog type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace message
    {
        typedef tetengo2::detail::stub::encoding encoding_details_type;
        typedef
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::string>::type, encoding_details_type>
            internal_encoding_type;
        typedef
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::io_string>::type, encoding_details_type>
            message_catalog_encoding_type;
        typedef
            tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>
            message_catalog_encoder_type;
        typedef
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::io_string>::type, encoding_details_type>
            locale_name_encoding_type;
        typedef tetengo2::text::encoder<internal_encoding_type, locale_name_encoding_type> locale_name_encoder_type;
        typedef
            tetengo2::message::message_catalog_parser<
                boost::mpl::at<text_type_list, type::text::pull_parser>::type,
                boost::mpl::at<type_list, type::string>::type,
                message_catalog_encoder_type
            >
            message_catalog_parser_type;
        typedef
            tetengo2::message::messages<boost::filesystem::path, message_catalog_parser_type, locale_name_encoder_type>
            messages_type;
    }}
#endif

    //! The message type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::message::message_catalog_parser, detail::message::message_catalog_parser_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::message::messages, detail::message::messages_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message::message_catalog, tetengo2::message::message_catalog<detail::message::messages_type>
            >,
        tetengo2::meta::assoc_list_end
        >>>
        message_type_list;


}


#endif
