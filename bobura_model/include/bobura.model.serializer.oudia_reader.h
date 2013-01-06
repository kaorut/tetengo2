/*! \file
    \brief The definition of bobura::model::serializer::oudia_reader.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_OUDIAREADER_H)
#define BOBURA_MODEL_SERIALIZER_OUDIAREADER_H

#include <algorithm>
#include <cassert>
//#include <cstddef>
//#include <memory>
#include <stdexcept>
#include <string>
//#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for an OuDia reader.

        \tparam ForwardIterator     A forward iterator type.
        \tparam Timetable           A timetable type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam Encoder             An encoder type.
    */
    template <typename ForwardIterator, typename Timetable, typename StationGradeTypeSet, typename Encoder>
    class oudia_reader : public reader<ForwardIterator, Timetable>
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The base type.
        typedef reader<iterator, timetable_type> base_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a WinDIA reader.
        */
        oudia_reader()
        :
        base_type()
        {}

        /*!
            \brief Destroys the oudia_reader.
        */
        virtual ~oudia_reader()
        {}


    private:
        // types

        typedef typename iterator::value_type input_char_type;

        typedef std::basic_string<input_char_type> input_string_type;

        typedef typename timetable_type::string_type string_type;

        typedef typename string_type::value_type char_type;

        typedef typename timetable_type::train_kind_type train_kind_type;

        typedef typename train_kind_type::color_type color_type;

        typedef typename train_kind_type::weight_type weight_type;

        typedef typename train_kind_type::line_style_type line_style_type;

        typedef typename timetable_type::train_type train_type;

        class state
        {
        public:
            virtual ~state()
            {}

            virtual bool parse(const string_type& line)
            = 0;

        };


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static string_type next_line(iterator& first, const iterator last)
        {
            string_type line;
            for (;;)
            {
                skip_line_breaks(first, last);
                const iterator next_line_break = std::find_if(first, last, line_break);
                line += encoder().decode(input_string_type(first, next_line_break));

                first = next_line_break;
                if (!line.empty() && line_contination(line[line.length() - 1]))
                    line.resize(line.length() - 1);
                else
                    break;
            }

            return line;
        }

        static void skip_line_breaks(iterator& first, const iterator last)
        {
            while (first != last && line_break(*first))
                ++first;
        }

        static bool line_break(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\r')) ||
                character == input_char_type(TETENGO2_TEXT('\n'));
        }


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            return false;
            //iterator mutable_first = first;
            //return next_line(mutable_first, last) == windia_section_label();
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last)
        {
            std::unique_ptr<timetable_type> p_timetable = tetengo2::make_unique<timetable_type>();

            //insert_preset_train_kinds(*p_timetable);

            //std::unique_ptr<state> p_state = tetengo2::make_unique<initial_state>();
            //iterator next_line_first = first;
            //for (;;)
            //{
            //    const string_type input_line = next_line(next_line_first, last);
            //    if (next_line_first == last)
            //        break;

            //    if      (input_line == windia_section_label())
            //        p_state = tetengo2::make_unique<windia_state>(*p_timetable);
            //    else if (input_line == station_section_label())
            //        p_state = tetengo2::make_unique<station_state>(*p_timetable);
            //    else if (input_line == line_kind_section_label())
            //        p_state = tetengo2::make_unique<line_kind_state>(*p_timetable);
            //    else if (input_line == down_train_section_label())
            //        p_state = tetengo2::make_unique<down_train_state>(*p_timetable);
            //    else if (input_line == up_train_section_label())
            //        p_state = tetengo2::make_unique<up_train_state>(*p_timetable);
            //    else
            //    {
            //        if (!p_state->parse(input_line))
            //            return std::unique_ptr<timetable_type>();
            //    }
            //}

            //erase_unreferred_train_kinds(*p_timetable);

            //if (dynamic_cast<up_train_state*>(p_state.get()) == 0)
            //    return std::unique_ptr<timetable_type>();

            return std::move(p_timetable);
        }


    };


}}}


#endif
