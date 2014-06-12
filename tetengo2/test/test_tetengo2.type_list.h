/*! \file
    \brief The definition of test_tetengo2::type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_TYPELIST_H)
#define TESTTETENGO2_TYPELIST_H

#include <cstddef>
#include <iterator>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.h>
#include <tetengo2/detail/stub/config.h>

#include "test_tetengo2.detail_type_list.h"


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
    using type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, std::string>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::io_string, std::string>,
        tetengo2::meta::assoc_list_end
        >>>;


    /**** Configuration *****************************************************/

    namespace type { namespace config
    {
        struct encoder;        //!< The encoder tyep.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace config
    {
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using internal_encoding_type =
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::string>::type, encoding_details_type>;
        using config_encoding_type =
            tetengo2::text::encoding::locale<
                boost::mpl::at<detail_type_list, type::detail::config>::type::string_type, encoding_details_type
            >;
        using encoder_type = tetengo2::text::encoder<internal_encoding_type, config_encoding_type>;
    }}
#endif

    //! The configuration type list.
    using config_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::config::encoder, detail::config::encoder_type>,
        tetengo2::meta::assoc_list_end
        >;


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
        using input_stream_iterator_type =
            boost::spirit::multi_pass<
                std::istreambuf_iterator<boost::mpl::at<type_list, type::io_string>::type::value_type>
            >;
        using grammar_type = tetengo2::text::grammar::json<input_stream_iterator_type>;
        using push_parser_type = tetengo2::text::push_parser<input_stream_iterator_type, grammar_type, int, double>;
    }}
#endif

    //! The text type list.
    using text_type_list =
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
        >>>>;


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
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using internal_encoding_type =
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::string>::type, encoding_details_type>;
        using message_catalog_encoding_type =
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::io_string>::type, encoding_details_type>;
        using message_catalog_encoder_type =
            tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>;
        using locale_name_encoding_type =
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::io_string>::type, encoding_details_type>;
        using locale_name_encoder_type = tetengo2::text::encoder<internal_encoding_type, locale_name_encoding_type>;
        using message_catalog_parser_type =
            tetengo2::message::message_catalog_parser<
                boost::mpl::at<text_type_list, type::text::pull_parser>::type,
                boost::mpl::at<type_list, type::string>::type,
                message_catalog_encoder_type
            >;
        using messages_type =
            tetengo2::message::messages<
                boost::filesystem::path, message_catalog_parser_type, locale_name_encoder_type
            >;
    }}
#endif

    //! The message type list.
    using message_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::message::message_catalog_parser, detail::message::message_catalog_parser_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::message::messages, detail::message::messages_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message::message_catalog, tetengo2::message::message_catalog<detail::message::messages_type>
            >,
        tetengo2::meta::assoc_list_end
        >>>;


}


#endif
