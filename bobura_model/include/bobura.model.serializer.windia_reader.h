/*! \file
    \brief The definition of bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WINDIA2READER_H)
#define BOBURA_MODEL_SERIALIZER_WINDIA2READER_H

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include <boost/foreach.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a WinDIA reader.

        \tparam ForwardIterator     A forward iterator type.
        \tparam Timetable           A timetable type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam Encoder             An encoder type.
    */
    template <typename ForwardIterator, typename Timetable, typename StationGradeTypeSet, typename Encoder>
    class windia_reader : public reader<ForwardIterator, Timetable>
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
        windia_reader()
        :
        base_type()
        {}

        /*!
            \brief Destroys the windia_reader.
        */
        virtual ~windia_reader()
        {}


    private:
        // types

        typedef typename iterator::value_type input_char_type;

        typedef std::basic_string<input_char_type> input_string_type;

        typedef typename timetable_type::string_type string_type;

        typedef typename timetable_type::train_kind_type train_kind_type;

        class state
        {
        public:
            virtual ~state()
            {}

            virtual bool parse(const string_type& line)
            = 0;

        };

        class initial_state : public state
        {
        public:
            virtual ~initial_state()
            {}

            virtual bool parse(const string_type& line)
            {
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("Cannot parse any line in the initial state."));
            }

        };

        class windia_state : public state
        {
        public:
            explicit windia_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~windia_state()
            {}

            virtual bool parse(const string_type& line)
            {
                m_timetable.set_title(line);
                return true;
            }

        private:
            timetable_type& m_timetable;

        };

        class station_state : public state
        {
        public:
            explicit station_state(timetable_type& timetable)
            :
            m_timetable(timetable),
            m_meterage(0)
            {}

            virtual ~station_state()
            {}

            virtual bool parse(const string_type& line)
            {
                const std::size_t comma_position = line.find(TETENGO2_TEXT(','));
                if (comma_position == string_type::npos)
                    return false;

                const string_type props = line.substr(0, comma_position);
                string_type name = line.substr(comma_position + 1);

                station_location_type station_location(
                    station_type(
                        std::move(name),
                        to_grade(
                            props.find(TETENGO2_TEXT('p')) != string_type::npos,
                            props.find(TETENGO2_TEXT('b')) != string_type::npos
                        ),
                        props.find(TETENGO2_TEXT('d')) != string_type::npos,
                        props.find(TETENGO2_TEXT('u')) != string_type::npos
                    ),
                    m_meterage
                );
                m_timetable.insert_station_location(
                    m_timetable.station_locations().end(), std::move(station_location)
                );

                ++m_meterage;

                return true;
            }

        private:
            typedef typename timetable_type::station_location_type station_location_type;

            typedef typename station_location_type::station_type station_type;

            typedef typename station_type::grade_type grade_type;

            typedef typename station_location_type::meterage_type meterage_type;

            static const grade_type& to_grade(const bool principal, const bool show_arrival_and_departure_time)
            {
                if      (principal && show_arrival_and_departure_time)
                    return station_grade_type_set_type::principal_terminal_type::instance();
                else if (show_arrival_and_departure_time)
                    return station_grade_type_set_type::local_terminal_type::instance();
                else if (principal)
                    return station_grade_type_set_type::principal_type::instance();
                else
                    return station_grade_type_set_type::local_type::instance();
            }

            timetable_type& m_timetable;

            meterage_type m_meterage;

        };

        class line_kind_state : public state
        {
        public:
            explicit line_kind_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~line_kind_state()
            {}

            virtual bool parse(const string_type& line)
            {

                return true;
            }

        private:
            timetable_type& m_timetable;

        };

        class down_train_state : public state
        {
        public:
            explicit down_train_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~down_train_state()
            {}

            virtual bool parse(const string_type& line)
            {

                return true;
            }

        private:
            timetable_type& m_timetable;

        };

        class up_train_state : public state
        {
        public:
            explicit up_train_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~up_train_state()
            {}

            virtual bool parse(const string_type& line)
            {

                return true;
            }

        private:
            timetable_type& m_timetable;

        };


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static const input_string_type& windia_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[WinDIA]"));
            return singleton;
        }

        static const input_string_type& station_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[\x89\x77]")); // "eki"
            return singleton;
        }

        static const input_string_type& line_kind_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[\x90\xFC\x8E\xED]")); // "senshu"
            return singleton;
        }

        static const input_string_type& down_train_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[\x89\xBA\x82\xE8]")); // "kudari"
            return singleton;
        }

        static const input_string_type& up_train_section_label()
        {
            static const input_string_type singleton(TETENGO2_TEXT("[\x8F\xE3\x82\xE8]")); // "nobori"
            return singleton;
        }

        static void insert_preset_train_kinds(timetable_type& timetable)
        {
            typedef std::pair<input_string_type, input_string_type> name_and_abbr_type;
            std::vector<name_and_abbr_type> names;

            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x95\x81\x92\xCA")), // "futsuu"
                    input_string_type(TETENGO2_TEXT("\x95\x81\x92\xCA")) // "futsuu"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x89\xF5\x91\xAC")), // "kaosoku"
                    input_string_type(TETENGO2_TEXT("\x89\xF5\x91\xAC")) // "kaosoku"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x93\xC1\x95\xCA\x89\xF5\x91\xAC")), // "tokubetsukaisoku"
                    input_string_type(TETENGO2_TEXT("\x93\xC1\x89\xF5")) // "tokkai"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x90\x56\x89\xF5\x91\xAC")), // "shinkaisoku"
                    input_string_type(TETENGO2_TEXT("\x90\x56\x89\xF5")) // "shinkai"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x92\xCA\x8B\xCE\x89\xF5\x91\xAC")), // "tsuukinkaisoku"
                    input_string_type(TETENGO2_TEXT("\x92\xCA\x89\xF5")) // "tsuukai"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x8F\x80\x8B\x7D")), // "junkyuu"
                    input_string_type(TETENGO2_TEXT("\x8F\x80\x8B\x7D")) // "junkyuu"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x8B\x7D\x8D\x73")), // "kyuukou"
                    input_string_type(TETENGO2_TEXT("\x8B\x7D\x8D\x73")) // "kyuukou"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x89\xF5\x91\xAC\x8B\x7D\x8D\x73")), // "kaisokukyuukou"
                    input_string_type(TETENGO2_TEXT("\x89\xF5\x8B\x7D")) // "kaikyuu"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x93\xC1\x8B\x7D")), // "tokkyuu"
                    input_string_type(TETENGO2_TEXT("\x93\xC1\x8B\x7D")) // "tokkyuu"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x89\xF5\x91\xAC\x93\xC1\x8B\x7D")), // "kaisokutokkyuu"
                    input_string_type(TETENGO2_TEXT("\x89\xF5\x93\xC1")) // "kaitoku"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x92\xCA\x8B\xCE\x8F\x80\x8B\x7D")), // "tsuukinjunkyuu"
                    input_string_type(TETENGO2_TEXT("\x92\xCA\x8F\x80")) // "tsuujun"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x92\xCA\x8B\xCE\x8B\x7D\x8D\x73")), // "tsuukinkyuukou"
                    input_string_type(TETENGO2_TEXT("\x92\xCA\x8B\x7D")) // "tsuukyuu"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x8B\xE6\x8A\xD4\x89\xF5\x91\xAC")), // "kukankaisoku"
                    input_string_type(TETENGO2_TEXT("\x8B\xE6\x89\xF5")) // "kukai"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x8B\xE6\x8A\xD4\x8B\x7D\x8D\x73")), // "kukankyuukou"
                    input_string_type(TETENGO2_TEXT("\x8B\xE6\x8B\x7D")) // "kukyuu"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x89\xF1\x91\x97")), // "kaisou"
                    input_string_type(TETENGO2_TEXT("\x89\xF1\x91\x97")) // "kaisou"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x89\xDD\x95\xA8")), // "kamotsu"
                    input_string_type(TETENGO2_TEXT("\x89\xDD\x95\xA8")) // "kamotsu"
                )
            );
            names.push_back(
                std::make_pair(
                    input_string_type(TETENGO2_TEXT("\x8B\x7D\x8D\x73\x89\xDD\x95\xA8")), // "kyuukoukamotsu"
                    input_string_type(TETENGO2_TEXT("\x8B\x7D\x89\xDD")) // "kyuuka"
                )
            );

            BOOST_FOREACH (const name_and_abbr_type& name, names)
            {
                timetable.insert_train_kind(
                    timetable.train_kinds().end(),
                    train_kind_type(encoder().decode(name.first), encoder().decode(name.second))
                );
            }
        }

        static input_string_type next_line(iterator& first, const iterator last)
        {
            input_string_type line;
            for (;;)
            {
                skip_line_breaks(first, last);
                const iterator next_line_break = std::find_if(first, last, line_break);
                line += input_string_type(first, next_line_break);

                first = next_line_break;
                if (!line.empty() && line_contination(line.back()))
                    line.pop_back();
                else
                    break;
            }

            return line;
        }

        static void skip_line_breaks(iterator& first, const iterator last)
        {
            while (first != last && (line_break(*first) || tab(*first)))
                ++first;
        }

        static bool line_break(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\r')) ||
                character == input_char_type(TETENGO2_TEXT('\n'));
        }

        static bool line_contination(const input_char_type character)
        {
            return character == input_char_type(TETENGO2_TEXT('\\'));
        }

        static bool tab(const input_char_type character)
        {
            return
                character == input_char_type(TETENGO2_TEXT('\t'));
        }


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            iterator mutable_first = first;
            return next_line(mutable_first, last) == windia_section_label();
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last)
        {
            std::unique_ptr<timetable_type> p_timetable = tetengo2::make_unique<timetable_type>();

            insert_preset_train_kinds(*p_timetable);

            std::unique_ptr<state> p_state = tetengo2::make_unique<initial_state>();
            iterator next_line_first = first;
            for (;;)
            {
                const input_string_type input_line = next_line(next_line_first, last);
                if (next_line_first == last)
                    break;

                if      (input_line == windia_section_label())
                    p_state = tetengo2::make_unique<windia_state>(*p_timetable);
                else if (input_line == station_section_label())
                    p_state = tetengo2::make_unique<station_state>(*p_timetable);
                else if (input_line == line_kind_section_label())
                    p_state = tetengo2::make_unique<line_kind_state>(*p_timetable);
                else if (input_line == down_train_section_label())
                    p_state = tetengo2::make_unique<down_train_state>(*p_timetable);
                else if (input_line == up_train_section_label())
                    p_state = tetengo2::make_unique<up_train_state>(*p_timetable);
                else
                {
                    if (!p_state->parse(encoder().decode(input_line)))
                        return std::unique_ptr<timetable_type>();
                }
            }

            return std::move(p_timetable);
        }


    };


}}}


#endif
