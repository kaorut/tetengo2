/*! \file
    \brief The definition of bobura::model::serializer::json_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONREADER_H)
#define BOBURA_MODEL_SERIALIZER_JSONREADER_H

//#include <cstddef>
#include <ios>
//#include <memory>
#include <sstream>
#include <unordered_map>
//#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reader.

        \tparam PullParser          A pull parser type.
        \tparam Timetable           A timetable type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam Encoder             An encoder type.
    */
    template <typename PullParser, typename Timetable, typename StationGradeTypeSet, typename Encoder>
    class json_reader : public reader<typename PullParser::push_parser_type::iterator, Timetable>
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

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
        {}


    private:
        // types

        typedef typename timetable_type::string_type string_type;

        typedef typename timetable_type::train_kind_index_type train_kind_index_type;

        typedef typename push_parser_type::grammar_type grammar_type;

        typedef typename push_parser_type::string_type input_string_type;

        typedef std::unordered_map<string_type, string_type> header_type;

        typedef typename timetable_type::station_location_type station_location_type;

        typedef typename station_location_type::station_type station_type;

        typedef typename station_type::grade_type station_grade_type;

        typedef typename station_location_type::meterage_type meterage_type;

        typedef typename timetable_type::train_kind_type train_kind_type;

        typedef typename train_kind_type::color_type color_type;

        typedef typename train_kind_type::weight_type weight_type;

        typedef typename train_kind_type::line_style_type line_style_type;

        typedef typename timetable_type::train_type train_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename stop_type::time_type time_type;

        typedef typename pull_parser_type::element_type element_type;

        typedef typename pull_parser_type::structure_begin_type structure_begin_type;

        typedef typename pull_parser_type::structure_end_type structure_end_type;

        typedef typename pull_parser_type::attribute_map_type attribute_map_type;

        typedef typename pull_parser_type::value_type value_type;

        typedef typename push_parser_type::integer_type integer_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static std::unique_ptr<timetable_type> read_timetable(pull_parser_type& pull_parser)
        {
            std::unique_ptr<timetable_type> p_timetable = tetengo2::make_unique<timetable_type>();

            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return std::unique_ptr<timetable_type>();
            pull_parser.next();

            const boost::optional<header_type> header = read_header(pull_parser);
            if (!header)
                return std::unique_ptr<timetable_type>();
            {
                const typename header_type::const_iterator found = header->find(string_type(TETENGO2_TEXT("title")));
                if (found != header->end())
                    p_timetable->set_title(found->second);
            }

            const boost::optional<std::vector<station_location_type>> stations = read_stations(pull_parser);
            if (!stations)
                return std::unique_ptr<timetable_type>();
            BOOST_FOREACH (const station_location_type& station, *stations)
            {
                p_timetable->insert_station_location(p_timetable->station_locations().end(), station);
            }

            const boost::optional<std::vector<train_kind_type>> train_kinds = read_train_kinds(pull_parser);
            if (!train_kinds)
                return std::unique_ptr<timetable_type>();
            BOOST_FOREACH (const train_kind_type& train_kind, *train_kinds)
            {
                p_timetable->insert_train_kind(p_timetable->train_kinds().end(), train_kind);
            }

            const boost::optional<std::vector<train_type>> down_trains =
                read_trains(pull_parser, stations->size(), train_kinds->size());
            if (!down_trains)
                return std::unique_ptr<timetable_type>();
            BOOST_FOREACH (const train_type& train, *down_trains)
            {
                p_timetable->insert_down_train(p_timetable->down_trains().end(), train);
            }

            const boost::optional<std::vector<train_type>> up_trains =
                read_trains(pull_parser, stations->size(), train_kinds->size());
            if (!up_trains)
                return std::unique_ptr<timetable_type>();
            BOOST_FOREACH (const train_type& train, *up_trains)
            {
                p_timetable->insert_up_train(p_timetable->up_trains().end(), train);
            }

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return std::unique_ptr<timetable_type>();
            pull_parser.next();

            return std::move(p_timetable);
        }

        static boost::optional<header_type> read_header(pull_parser_type& pull_parser)
        {
            header_type header;

            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("object"))))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    break;

                header.insert(*member);
            }

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("object"))))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(header));
        }

        static boost::optional<std::vector<station_location_type>> read_stations(pull_parser_type& pull_parser)
        {
            std::vector<station_location_type> stations;

            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                const boost::optional<station_location_type> station = read_station(pull_parser);
                if (!station)
                    break;

                stations.push_back(*station);
            }

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(stations));
        }

        static boost::optional<station_location_type> read_station(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("object"))))
                return boost::none;
            pull_parser.next();

            string_type name;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("name")))
                    return boost::none;

                name = member->second;
            }

            const station_grade_type* p_grade = NULL;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("grade")))
                    return boost::none;

                p_grade = to_station_grade(member->second);
                if (!p_grade)
                    return boost::none;
            }

            bool show_down_arrival_times = false;
            {
                const boost::optional<std::pair<string_type, bool>> member = read_boolean_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("show_down_arrival_times")))
                    return boost::none;

                show_down_arrival_times = member->second;
            }

            bool show_up_arrival_times = false;
            {
                const boost::optional<std::pair<string_type, bool>> member = read_boolean_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("show_up_arrival_times")))
                    return boost::none;

                show_up_arrival_times = member->second;
            }

            meterage_type meterage = 0;
            {
                const boost::optional<std::pair<string_type, meterage_type>> member =
                    read_integer_member<meterage_type>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("meterage")))
                    return boost::none;

                meterage = member->second;
            }
            
            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("object"))))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    station_location_type(
                        station_type(std::move(name), *p_grade, show_down_arrival_times, show_up_arrival_times),
                        meterage
                    )
                );
        }

        static const station_grade_type* to_station_grade(const string_type& name)
        {
            if      (name == station_grade_type_set_type::local_type::instance().name())
                return &station_grade_type_set_type::local_type::instance();
            else if (name == station_grade_type_set_type::principal_type::instance().name())
                return &station_grade_type_set_type::principal_type::instance();
            else if (name == station_grade_type_set_type::local_terminal_type::instance().name())
                return &station_grade_type_set_type::local_terminal_type::instance();
            else if (name == station_grade_type_set_type::principal_terminal_type::instance().name())
                return &station_grade_type_set_type::principal_terminal_type::instance();
            else
                return NULL;
        }

        static boost::optional<std::vector<train_kind_type>> read_train_kinds(pull_parser_type& pull_parser)
        {
            std::vector<train_kind_type> train_kinds;

            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                const boost::optional<train_kind_type> train_kind = read_train_kind(pull_parser);
                if (!train_kind)
                    break;

                train_kinds.push_back(*train_kind);
            }

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(train_kinds));
        }

        static boost::optional<train_kind_type> read_train_kind(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("object"))))
                return boost::none;
            pull_parser.next();

            string_type name;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("name")))
                    return boost::none;

                name = member->second;
            }

            string_type abbreviation;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("abbreviation")))
                    return boost::none;

                abbreviation = member->second;
            }

            boost::optional<color_type> color;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("color")))
                    return boost::none;

                color = to_color(member->second);
                if (!color)
                    return boost::none;
            }

            boost::optional<typename weight_type::enum_t> weight;
            {
                const boost::optional<std::pair<string_type, int>> member = read_integer_member<int>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("weight")))
                    return boost::none;

                weight = to_weight(member->second);
                if (!weight)
                    return boost::none;
            }

            boost::optional<typename line_style_type::enum_t> line_style;
            {
                const boost::optional<std::pair<string_type, int>> member = read_integer_member<int>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("line_style")))
                    return boost::none;

                line_style = to_line_style(member->second);
                if (!line_style)
                    return boost::none;
            }

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("object"))))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    train_kind_type(std::move(name), std::move(abbreviation), std::move(*color), *weight, *line_style)
                );
        }

        static boost::optional<color_type> to_color(const string_type& color_string)
        {
            if (color_string.length() != 6)
                return boost::none;

            const unsigned int color_value = to_color_value(color_string);

            return
                boost::make_optional(
                    color_type(
                        (color_value / 0x010000) & 0x0000FF,
                        (color_value / 0x000100) & 0x0000FF,
                        color_value & 0x0000FF
                    )
                );
        }

        static unsigned int to_color_value(const string_type& color_string)
        {
            std::basic_istringstream<typename string_type::value_type> stream(color_string);

            unsigned int value = 0;
            stream >> std::hex >> value;

            return value;
        }

        static boost::optional<typename weight_type::enum_t> to_weight(const int weight_integer)
        {
            if (
                weight_integer < train_kind_type::weight_type::normal ||
                train_kind_type::weight_type::bold < weight_integer
            )
            {
                return boost::none;
            }

            return static_cast<typename weight_type::enum_t>(weight_integer);
        }

        static boost::optional<typename line_style_type::enum_t> to_line_style(const int line_style_integer)
        {
            if (
                line_style_integer < train_kind_type::line_style_type::solid ||
                train_kind_type::line_style_type::dot_dashed < line_style_integer
            )
            {
                return boost::none;
            }

            return static_cast<typename line_style_type::enum_t>(line_style_integer);
        }

        static boost::optional<std::vector<train_type>> read_trains(
            pull_parser_type& pull_parser,
            const std::size_t station_count,
            const std::size_t kind_count
        )
        {
            std::vector<train_type> trains;

            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                const boost::optional<train_type> train = read_train(pull_parser, station_count, kind_count);
                if (!train)
                    break;

                trains.push_back(*train);
            }

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(trains));
        }

        static boost::optional<train_type> read_train(
            pull_parser_type& pull_parser,
            const std::size_t station_count,
            const std::size_t kind_count
        )
        {
            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("object"))))
                return boost::none;
            pull_parser.next();

            string_type number;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("number")))
                    return boost::none;

                number = member->second;
            }

            train_kind_index_type kind_index;
            {
                const boost::optional<std::pair<string_type, train_kind_index_type>> member =
                    read_integer_member<train_kind_index_type>(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("kind_index")))
                    return boost::none;

                kind_index = member->second;
                if (kind_index >= kind_count)
                    return boost::none;
            }

            string_type name;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("name")))
                    return boost::none;

                name = member->second;
            }

            string_type name_number;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("name_number")))
                    return boost::none;

                name_number = member->second;
            }

            string_type note;
            {
                const boost::optional<std::pair<string_type, string_type>> member = read_string_member(pull_parser);
                if (!member)
                    return boost::none;
                if (member->first != string_type(TETENGO2_TEXT("note")))
                    return boost::none;

                note = member->second;
            }

            train_type train(std::move(number), kind_index, std::move(name), std::move(name_number), std::move(note));

            boost::optional<std::vector<stop_type>> stops = read_stops(pull_parser);
            if (!stops)
                return boost::none;
            if (stops->size() > station_count)
                return boost::none;
            BOOST_FOREACH (stop_type& stop, *stops)
            {
                train.insert_stop(train.stops().end(), std::move(stop));
            }
            for (std::size_t i = stops->size(); i < station_count; ++i)
                train.insert_stop(train.stops().end(), empty_stop());

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("object"))))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(train));
        }

        static stop_type empty_stop()
        {
            return stop_type(time_type::uninitialized(), time_type::uninitialized(), string_type());
        }

        static boost::optional<std::vector<stop_type>> read_stops(pull_parser_type& pull_parser)
        {
            std::vector<stop_type> stops;

            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("member"))))
                return boost::none;
            const input_string_type key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            if (key != "stops")
                return boost::none;
            pull_parser.next();

            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            for (;;)
            {
                boost::optional<stop_type> stop = read_stop(pull_parser);
                if (!stop)
                    break;

                stops.push_back(std::move(*stop));
            }

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("member"))))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::move(stops));
        }

        static boost::optional<stop_type> read_stop(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            const boost::optional<std::ptrdiff_t> arrival_input = read_integer<std::ptrdiff_t>(pull_parser);
            if (!arrival_input)
                return boost::none;
            const boost::optional<time_type> arrival_time = to_time(*arrival_input);
            if (!arrival_time)
                return boost::none;

            const boost::optional<std::ptrdiff_t> departure_input = read_integer<std::ptrdiff_t>(pull_parser);
            if (!departure_input)
                return boost::none;
            const boost::optional<time_type> departure_time = to_time(*departure_input);
            if (!departure_time)
                return boost::none;

            const boost::optional<input_string_type> platform = read_string(pull_parser);
            if (!platform)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    stop_type(
                        std::move(*arrival_time), std::move(*departure_time), encoder().decode(std::move(*platform))
                    )
                );
        }

        static boost::optional<time_type> to_time(const std::ptrdiff_t input)
        {
            if (input < 0)
                return boost::make_optional(time_type::uninitialized());

            const std::size_t hours = (input / 10000) % 100;
            if (hours > 23)
                return boost::none;

            const std::size_t minutes = (input / 100) % 100;
            if (minutes > 59)
                return boost::none;

            const std::size_t seconds = input % 100;
            if (seconds > 59)
                return boost::none;

            return time_type(hours, minutes, seconds);
        }

        static boost::optional<std::pair<string_type, string_type>> read_string_member(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("member"))))
                return boost::none;
            const input_string_type key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            const boost::optional<input_string_type> value = read_string(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("member"))))
                return boost::none;
            pull_parser.next();

            return
                boost::make_optional(
                    std::make_pair(encoder().decode(std::move(key)), encoder().decode(std::move(*value)))
                );
        }

        static boost::optional<input_string_type> read_string(pull_parser_type& pull_parser)
        {
            if (!pull_parser.has_next())
                return boost::none;
            const element_type& element = pull_parser.peek();
            if (element.which() != 2)
                return boost::none;
            const value_type& value = boost::get<value_type>(element);
            if (value.which() != 4)
                return boost::none;
            const input_string_type string = boost::get<input_string_type>(value);
            pull_parser.next();
            return boost::make_optional(std::move(string));
        }

        template <typename Integer>
        static boost::optional<std::pair<string_type, Integer>> read_integer_member(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("member"))))
                return boost::none;
            const input_string_type key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            const boost::optional<Integer> value = read_integer<Integer>(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("member"))))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::make_pair(encoder().decode(std::move(key)), *value));
        }

        template <typename Integer>
        static boost::optional<Integer> read_integer(pull_parser_type& pull_parser)
        {
            if (!pull_parser.has_next())
                return boost::none;
            const element_type& element = pull_parser.peek();
            if (element.which() != 2)
                return boost::none;
            const value_type& value = boost::get<value_type>(element);
            if (value.which() != 2)
                return boost::none;
            const Integer integer = boost::get<integer_type>(value);
            pull_parser.next();
            return boost::make_optional(integer);
        }

        static boost::optional<std::pair<string_type, bool>> read_boolean_member(pull_parser_type& pull_parser)
        {
            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("member"))))
                return boost::none;
            const input_string_type key = get_attribute(boost::get<structure_begin_type>(pull_parser.peek()));
            if (key.empty())
                return boost::none;
            pull_parser.next();

            const boost::optional<bool> value = read_boolean(pull_parser);
            if (!value)
                return boost::none;

            if (!next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("member"))))
                return boost::none;
            pull_parser.next();

            return boost::make_optional(std::make_pair(encoder().decode(std::move(key)), *value));
        }

        static boost::optional<bool> read_boolean(pull_parser_type& pull_parser)
        {
            if (!pull_parser.has_next())
                return boost::none;
            const element_type& element = pull_parser.peek();
            if (element.which() != 2)
                return boost::none;
            const value_type& value = boost::get<value_type>(element);
            if (value.which() != 0)
                return boost::none;
            const bool boolean = boost::get<bool>(value);
            pull_parser.next();
            return boost::make_optional(boolean);
        }

        static bool next_is_structure_begin(const pull_parser_type& pull_parser, const input_string_type& name)
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

        static bool next_is_structure_end(const pull_parser_type& pull_parser, const input_string_type& name)
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

        static bool next_is_value(const pull_parser_type& pull_parser, const int which)
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

        static input_string_type get_attribute(const structure_begin_type& structure)
        {
            const typename attribute_map_type::const_iterator found =
                structure.attribute_map().find(input_string_type(TETENGO2_TEXT("name")));
            if (found == structure.attribute_map().end())
                return input_string_type();
            if (found->second.which() != 4)
                return input_string_type();
            
            return boost::get<input_string_type>(found->second);
        }


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            std::unique_ptr<push_parser_type> p_push_parser =
                tetengo2::make_unique<push_parser_type>(first, last, tetengo2::make_unique<grammar_type>());
            pull_parser_type pull_parser(std::move(p_push_parser), 5);

            if (!next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("array"))))
                return false;
            pull_parser.next();
            return
                next_is_structure_begin(pull_parser, input_string_type(TETENGO2_TEXT("object"))) ||
                next_is_structure_end(pull_parser, input_string_type(TETENGO2_TEXT("array")));
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last)
        {
            std::unique_ptr<push_parser_type> p_push_parser =
                tetengo2::make_unique<push_parser_type>(first, last, tetengo2::make_unique<grammar_type>());
            pull_parser_type pull_parser(std::move(p_push_parser), 5);

            return read_timetable(pull_parser);
        }


    };


}}}


#endif
