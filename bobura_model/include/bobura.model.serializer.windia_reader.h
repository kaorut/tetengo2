/*! \file
    \brief The definition of bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WINDIA2READER_H)
#define BOBURA_MODEL_SERIALIZER_WINDIA2READER_H

#include <algorithm>
#include <cassert>
//#include <cstddef>
//#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
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

        class initial_state : public state
        {
        public:
            virtual ~initial_state()
            {}

            virtual bool parse(const string_type& line)
            {
                return false;
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
                const boost::optional<split_type> split = split_line(line);
                if (!split)
                    return false;

                if (std::get<0>(*split) == string_type(TETENGO2_TEXT("LINES")))
                    return set_line_props(std::get<2>(*split));
                else if (std::get<0>(*split) == string_type(TETENGO2_TEXT("Train")))
                    return set_name(std::get<1>(*split), std::get<2>(*split));
                else
                    return false;
            }

        private:
            typedef std::tuple<string_type, std::size_t, std::vector<string_type>> split_type;

            static boost::optional<split_type> split_line(const string_type& line)
            {
                const std::size_t equal_position = line.find(TETENGO2_TEXT('='));
                if (equal_position == string_type::npos)
                    return boost::none;

                const string_type key_and_index = line.substr(0, equal_position);
                const std::size_t index_position = key_and_index.find_first_of(TETENGO2_TEXT("0123456789"));
                string_type key = key_and_index.substr(0, index_position);
                std::size_t index = 0;
                if (index_position != string_type::npos)
                {
                    try
                    {
                        index = boost::lexical_cast<std::size_t>(key_and_index.substr(index_position));
                    }
                    catch (const boost::bad_lexical_cast&)
                    {
                        return boost::none;
                    }
                }

                std::vector<string_type> values = split_by_comma(line.substr(equal_position + 1));

                return boost::make_optional(split_type(std::move(key), index, std::move(values)));
            }

            timetable_type& m_timetable;

            bool set_line_props(const std::vector<string_type>& props)
            {
                const std::size_t train_kind_count = m_timetable.train_kinds().size();
                if (props.size() < train_kind_count)
                    return false;

                for (std::size_t i = 0; i < train_kind_count; ++i)
                {
                    unsigned int prop = 0;
                    try
                    {
                        prop = boost::lexical_cast<unsigned int>(props[i]);
                    }
                    catch (const boost::bad_lexical_cast&)
                    {
                        return false;
                    }

                    boost::optional<train_kind_type> new_train_kind =
                        make_train_kind(m_timetable.train_kinds()[i], prop);
                    if (!new_train_kind)
                        return false;
                    m_timetable.set_train_kind(
                        boost::next(m_timetable.train_kinds().begin(), i), std::move(*new_train_kind)
                    );
                }

                return true;
            }

            bool set_name(const std::size_t index, const std::vector<string_type>& name_and_abbreviation)
            {
                if (index >= m_timetable.train_kinds().size())
                    return false;
                if (name_and_abbreviation.size() < 2)
                    return false;

                train_kind_type new_kind(
                    name_and_abbreviation[0],
                    name_and_abbreviation[1],
                    m_timetable.train_kinds()[index].color(),
                    m_timetable.train_kinds()[index].weight(),
                    m_timetable.train_kinds()[index].line_style()
                );

                m_timetable.set_train_kind(
                    boost::next(m_timetable.train_kinds().begin(), index), std::move(new_kind)
                );

                return true;
            }

        };

        class train_state : public state
        {
        public:
            explicit train_state(timetable_type& timetable)
            :
            m_timetable(timetable)
            {}

            virtual ~train_state()
            {}

            virtual bool parse(const string_type& line)
            {
                std::pair<string_type, string_type> others_and_note = split_line(line);
                std::vector<string_type> split = split_by_comma(others_and_note.first);
                if (split.size() < 4 + m_timetable.station_locations().size())
                    return false;

                const boost::optional<train_kind_index_type> train_kind_index = to_train_kind_index(split[0]);
                if (!train_kind_index)
                    return false;

                train_type train(
                    std::move(split[1]),
                    *train_kind_index,
                    std::move(split[2]),
                    std::move(split[3]),
                    std::move(others_and_note.second)
                );
                for (std::size_t i = 0; i < m_timetable.station_locations().size(); ++i)
                {
                    boost::optional<stop_type> stop = to_stop(std::move(split[4 + i]));
                    if (!stop)
                        return false;
                    train.insert_stop(train.stops().end(), std::move(*stop));
                }

                insert_train(std::move(train));

                return true;
            }

        protected:
            timetable_type& m_timetable;

        private:
            typedef typename train_type::kind_index_type train_kind_index_type;

            typedef typename train_type::stop_type stop_type;

            typedef typename stop_type::time_type time_type;

            typedef typename time_type::tick_type time_tick_type;

            static std::pair<string_type, string_type> split_line(const string_type& line)
            {
                const std::size_t percent_position = line.find(TETENGO2_TEXT('%'));
                if (percent_position == string_type::npos)
                    return std::make_pair(line, string_type());

                return std::make_pair(line.substr(0, percent_position), line.substr(percent_position + 1));
            }

            virtual void insert_train(train_type&& train)
            = 0;

            boost::optional<train_kind_index_type> to_train_kind_index(const string_type& train_kind_string)
            {
                const std::size_t opening_paren_position = train_kind_string.find(TETENGO2_TEXT('('));
                if (opening_paren_position == string_type::npos)
                {
                    try
                    {
                        return
                            train_kind_string.empty() ?
                            boost::make_optional(static_cast<train_kind_index_type>(0)) :
                            boost::make_optional(boost::lexical_cast<train_kind_index_type>(train_kind_string));
                    }
                    catch (const boost::bad_lexical_cast&)
                    {
                        return boost::none;
                    }
                }

                const std::size_t closing_paren_position = train_kind_string.find(TETENGO2_TEXT(')'));
                if (closing_paren_position == string_type::npos || closing_paren_position <= opening_paren_position)
                    return boost::none;

                train_kind_index_type base_index = 0;
                try
                {
                    const string_type index_string = train_kind_string.substr(0, opening_paren_position);
                    base_index = index_string.empty() ? 0 : boost::lexical_cast<train_kind_index_type>(index_string);
                }
                catch (const boost::bad_lexical_cast&)
                {
                    return boost::none;
                }
                if (base_index >= m_timetable.train_kinds().size())
                    return boost::none;

                unsigned int prop = 0;
                try
                {
                    prop =
                        boost::lexical_cast<unsigned int>(
                            train_kind_string.substr(
                                opening_paren_position + 1, closing_paren_position - opening_paren_position - 1
                            )
                        );
                }
                catch (const boost::bad_lexical_cast&)
                {
                    return boost::none;
                }

                boost::optional<train_kind_type> new_train_kind =
                    make_train_kind(m_timetable.train_kinds()[base_index], prop);
                if (!new_train_kind)
                    return boost::none;
                m_timetable.insert_train_kind(m_timetable.train_kinds().end(), std::move(*new_train_kind));

                return boost::make_optional<train_kind_index_type>(m_timetable.train_kinds().size() - 1);
            }

            boost::optional<stop_type> to_stop(string_type&& time_string)
            {
                const std::pair<string_type, string_type> arrival_and_departure_string =
                    split_time_string(std::forward<string_type>(time_string));

                boost::optional<time_type> arrival = to_time(arrival_and_departure_string.first);
                if (!arrival)
                    return boost::none;
                boost::optional<time_type> departure = to_time(arrival_and_departure_string.second);
                if (!departure)
                    return boost::none;

                return stop_type(std::move(*arrival), std::move(*departure), string_type());
            }

            std::pair<string_type, string_type> split_time_string(string_type&& time_string)
            {
                const std::size_t slash_position = time_string.find(TETENGO2_TEXT('/'));
                if (slash_position == string_type::npos)
                    return std::make_pair(string_type(), std::forward<string_type>(time_string));

                return std::make_pair(time_string.substr(0, slash_position), time_string.substr(slash_position + 1));
            }

            boost::optional<time_type> to_time(const string_type& time_string)
            {
                if (time_string.empty() || time_string == string_type(TETENGO2_TEXT("-")))
                    return boost::make_optional(time_type::uninitialized());

                const std::size_t time_string_length =
                    time_string.back() == char_type(TETENGO2_TEXT('?')) ?
                    time_string.length() - 1 : time_string.length();
                if (time_string_length < 3 && 4 < time_string_length)
                    return boost::none;
                const std::size_t minute_position = time_string_length == 3 ? 1 : 2;

                time_tick_type hours = 0;
                try
                {
                    hours = boost::lexical_cast<time_tick_type>(time_string.substr(0, minute_position));
                }
                catch (const boost::bad_lexical_cast&)
                {
                    return boost::none;
                }
                if (hours > 23)
                    return boost::none;

                time_tick_type minutes = 0;
                try
                {
                    minutes = boost::lexical_cast<time_tick_type>(time_string.substr(minute_position, 2));
                }
                catch (const boost::bad_lexical_cast&)
                {
                    return boost::none;
                }
                if (minutes > 59)
                    return boost::none;

                return time_type(hours, minutes, 0);
            }

        };

        class down_train_state : public train_state
        {
        public:
            explicit down_train_state(timetable_type& timetable)
            :
            train_state(timetable)
            {}

            virtual ~down_train_state()
            {}

        private:
            virtual void insert_train(train_type&& train)
            {
                m_timetable.insert_down_train(m_timetable.down_trains().end(), std::forward<train_type>(train));
            }

        };

        class up_train_state : public train_state
        {
        public:
            explicit up_train_state(timetable_type& timetable)
            :
            train_state(timetable)
            {}

            virtual ~up_train_state()
            {}

        private:
            virtual void insert_train(train_type&& train)
            {
                m_timetable.insert_up_train(m_timetable.up_trains().end(), std::forward<train_type>(train));
            }

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
                    train_kind_type(
                        encoder().decode(name.first),
                        encoder().decode(name.second),
                        color_type(0, 0, 0),
                        train_kind_type::weight_normal,
                        train_kind_type::line_style_solid
                    )
                );
            }
        }

        static const std::vector<color_type>& preset_palette()
        {
            static const std::vector<color_type> singleton =
                make_preset_palette();
            return singleton;
        }

        static std::vector<color_type> make_preset_palette()
        {
            std::vector<color_type> palette;
            palette.reserve(16);

            palette.push_back(color_type(  0,   0, 255));
            palette.push_back(color_type(  0, 255,   0));
            palette.push_back(color_type(  0,   0, 128));
            palette.push_back(color_type(  0, 128,   0));
            palette.push_back(color_type(  0, 255, 255));
            palette.push_back(color_type(255,   0,   0));
            palette.push_back(color_type(  0, 128, 128));
            palette.push_back(color_type(128,   0,   0));
            palette.push_back(color_type(255,   0, 255));
            palette.push_back(color_type(255, 255,   0));
            palette.push_back(color_type(128,   0, 128));
            palette.push_back(color_type(128, 128,   0));
            palette.push_back(color_type(  0,   0,   0));
            palette.push_back(color_type(128, 128, 128));
            palette.push_back(color_type(192, 192, 192));
            palette.push_back(color_type(255, 255, 255));

            return palette;
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

        static std::vector<string_type> split_by_comma(const string_type& string)
        {
            std::vector<string_type> values;

            std::size_t offset = 0;
            for (;;)
            {
                const std::size_t next_offset = string.find(TETENGO2_TEXT(','), offset);
                values.push_back(string.substr(offset, next_offset - offset));
                if (next_offset == string_type::npos)
                    break;
                offset = next_offset + 1;
            }

            return values;
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

        static boost::optional<train_kind_type> make_train_kind(const train_kind_type& base, const unsigned int prop)
        {
            const line_style_type line_style = to_line_style(prop & 0x03);
            const bool custom_color = (prop & 0x40) != 0;
            const boost::optional<color_type> color =
                custom_color ? to_color((prop & 0x3C) / 0x04) : boost::make_optional(base.color());
            if (!color)
                return boost::none;
            const weight_type weight = to_weight((prop & 0x80) != 0);

            return
                boost::make_optional(
                    train_kind_type(base.name(), base.abbreviation(), std::move(*color), weight, line_style)
                );
        }

        static boost::optional<color_type> to_color(const std::size_t index)
        {
            if (index >= preset_palette().size())
                return boost::none;
            return boost::make_optional(preset_palette()[index]);
        }

        static weight_type to_weight(const bool bold)
        {
            return bold ? train_kind_type::weight_bold : train_kind_type::weight_normal;
        }

        static line_style_type to_line_style(const std::size_t index)
        {
            switch (index)
            {
            case 0:
                return train_kind_type::line_style_solid;
            case 1:
                return train_kind_type::line_style_dashed;
            case 2:
                return train_kind_type::line_style_dotted;
            case 3:
                return train_kind_type::line_style_dot_dashed;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("We must not come here."));
            }
        }

        static void erase_unreferred_train_kinds(timetable_type& timetable)
        {
            for (;;)
            {
                timetable_type::train_kinds_type::const_iterator found = timetable.train_kinds().end();
                for (std::size_t i = 0; i < timetable.train_kinds().size(); ++i)
                {
                    if (!timetable.train_kind_referred(i))
                    {
                        found = boost::next(timetable.train_kinds().begin(), i);
                        break;
                    }
                }

                if (found == timetable.train_kinds().end())
                    break;

                timetable.erase_train_kind(found);
            }
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

            erase_unreferred_train_kinds(*p_timetable);

            if (dynamic_cast<up_train_state*>(p_state.get()) == 0)
                return std::unique_ptr<timetable_type>();

            return std::move(p_timetable);
        }


    };


}}}


#endif
