/*! \file
    \brief The definition of bobura::model::serializer::json_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONREADER_H)
#define BOBURA_MODEL_SERIALIZER_JSONREADER_H

//#include <istream>
#include <iterator>
//#include <memory>

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
            if (!pull_parser.has_next())
                return std::unique_ptr<timetable_type>();

            std::unique_ptr<timetable_type> p_timetable =
                tetengo2::make_unique<timetable_type>(string_type());

            return std::move(p_timetable);
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
