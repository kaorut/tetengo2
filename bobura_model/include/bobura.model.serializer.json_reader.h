/*! \file
    \brief The definition of bobura::model::serializer::json_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONREADER_H)
#define BOBURA_MODEL_SERIALIZER_JSONREADER_H

//#include <memory>
#include <unordered_map>
//#include <utility>

#include <boost/optional.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reader.

        \tparam Timetable       A timetable type.
        \tparam PullParser      A pull parser type.
        \tparam Encoder         An encoder type.
    */
    template <typename Timetable, typename PullParser, typename Encoder>
    class json_reader :
        public reader<
            typename PullParser::push_parser_type::iterator, Timetable
        >
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The pull parser type.
        typedef PullParser pull_parser_type;

        //! The push parser type.
        typedef typename pull_parser_type::push_parser_type push_parser_type;

        //! The iterator type.
        typedef typename push_parser_type::iterator iterator;

        //! The base type.
        typedef reader<iterator, timetable_type> base_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a JSON reader.
        */
        json_reader()
        :
        base_type()
        {}

        /*!
            \brief Destroys the json_reader.
        */
        virtual ~json_reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename timetable_type::string_type string_type;

        typedef typename push_parser_type::grammar_type grammar_type;

        typedef typename push_parser_type::string_type input_string_type;

        typedef std::unordered_map<string_type, string_type> header_type;

        typedef typename pull_parser_type::element_type element_type;

        typedef
            typename pull_parser_type::structure_begin_type
            structure_begin_type;

        typedef
            typename pull_parser_type::structure_end_type structure_end_type;

        typedef
            typename pull_parser_type::attribute_map_type attribute_map_type;

        typedef typename pull_parser_type::value_type value_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static std::unique_ptr<timetable_type> read_timetable(
            pull_parser_type& pull_parser
        )
        {
            std::unique_ptr<timetable_type> p_timetable =
                tetengo2::make_unique<timetable_type>(string_type());

            if (
                !next_is_structure_begin(
                    pull_parser, input_string_type(TETENGO2_TEXT("array"))
                )
            )
            {
                return std::unique_ptr<timetable_type>();
            }
            pull_parser.next();

            const boost::optional<header_type> header =
                read_header(pull_parser);
            if (!header)
                return std::unique_ptr<timetable_type>();
            {
                const typename header_type::const_iterator found =
                    header->find(string_type(TETENGO2_TEXT("title")));
                if (found != header->end())
                    p_timetable->set_title(found->second);
            }

            if (
                !next_is_structure_end(
                    pull_parser, input_string_type(TETENGO2_TEXT("array"))
                )
            )
            {
                return std::unique_ptr<timetable_type>();
            }
            pull_parser.next();

            return std::move(p_timetable);
        }

        static boost::optional<header_type> read_header(
            pull_parser_type& pull_parser
        )
        {
            header_type header;

            if (
                !next_is_structure_begin(
                    pull_parser, input_string_type(TETENGO2_TEXT("object"))
                )
            )
            {
                return boost::none;
            }
            pull_parser.next();

            for (;;)
            {
                const boost::optional<std::pair<string_type, string_type>>
                header_member = read_header_member(pull_parser);
                if (!header_member)
                    break;

                header.insert(*header_member);
            }

            if (
                !next_is_structure_end(
                    pull_parser, input_string_type(TETENGO2_TEXT("object"))
                )
            )
            {
                return boost::none;
            }
            pull_parser.next();

            return boost::make_optional(header);
        }

        static boost::optional<std::pair<string_type, string_type>>
        read_header_member(pull_parser_type& pull_parser)
        {
            if (
                !next_is_structure_begin(
                    pull_parser, input_string_type(TETENGO2_TEXT("member"))
                )
            )
            {
                return boost::none;
            }
            const input_string_type key =
                get_attribute(
                    boost::get<structure_begin_type>(pull_parser.peek())
                );
            if (key.empty())
                return boost::none;
            pull_parser.next();

            const input_string_type value = read_string(pull_parser);
            pull_parser.next();

            if (
                !next_is_structure_end(
                    pull_parser, input_string_type(TETENGO2_TEXT("member"))
                )
            )
            {
                return boost::none;
            }
            pull_parser.next();

            return boost::make_optional(
                std::make_pair(encoder().decode(key), encoder().decode(value))
            );
        }

        static bool next_is_structure_begin(
            const pull_parser_type&  pull_parser,
            const input_string_type& name
        )
        {
            if (!pull_parser.has_next())
                return false;
            const element_type& element = pull_parser.peek();
            if (element.which() != 0)
                return false;
            if (boost::get<structure_begin_type>(element).name() != name)
                return false;

            return true;
        }

        static bool next_is_structure_end(
            const pull_parser_type&  pull_parser,
            const input_string_type& name
        )
        {
            if (!pull_parser.has_next())
                return false;
            const element_type& element = pull_parser.peek();
            if (element.which() != 1)
                return false;
            if (boost::get<structure_end_type>(element).name() != name)
                return false;

            return true;
        }

        static bool next_is_value(
            const pull_parser_type& pull_parser,
            const int               which
        )
        {
            if (!pull_parser.has_next())
                return false;
            const element_type& element = pull_parser.peek();
            if (element.which() != 2)
                return false;
            const value_type& value = boost::get<value_type>(element);
            if (value.which() != which)
                return false;

            return true;
        }

        static input_string_type read_string(
            const pull_parser_type& pull_parser
        )
        {
            return boost::get<input_string_type>(
                boost::get<value_type>(pull_parser.peek())
            );
        }

        static input_string_type get_attribute(
            const structure_begin_type& structure
        )
        {
            const typename attribute_map_type::const_iterator found =
                structure.attribute_map().find(
                    input_string_type(TETENGO2_TEXT("name"))
                );
            if (found == structure.attribute_map().end())
                return input_string_type();
            if (found->second.which() != 4)
                return input_string_type();
            
            return boost::get<input_string_type>(found->second);
        }


        // virtual functions

        virtual std::unique_ptr<timetable_type> read_impl(
            const iterator first,
            const iterator last
        )
        {
            std::unique_ptr<push_parser_type> p_push_parser =
                tetengo2::make_unique<push_parser_type>(
                    first, last, tetengo2::make_unique<grammar_type>()
                );
            pull_parser_type pull_parser(std::move(p_push_parser), 5);

            return read_timetable(pull_parser);
        }


    };


}}}


#endif
