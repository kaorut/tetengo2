/*! \file
    \brief The definition of bobura::model::serializer::json_writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONWRITER_H)
#define BOBURA_MODEL_SERIALIZER_JSONWRITER_H

#include <cstddef>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>

#include <boost/format.hpp>
//#include <boost/utility.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>

#include "bobura.model.serializer.writer.h"
#include "bobura.model.station_info.grade.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON writer.

        \tparam OutputStream        A output stream type.
        \tparam Timetable           A timetable type.
        \tparam Path                A path type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam Encoder             An encoder type.
    */
    template <typename OutputStream, typename Timetable, typename Path, typename StationGradeTypeSet, typename Encoder>
    class json_writer : public writer<OutputStream, Timetable, Path>
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path type.
        typedef Path path_type;

        //! The base type.
        typedef writer<output_stream_type, timetable_type, path_type> base_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a JSON writer.
        */
        json_writer()
        :
        base_type()
        {}

        /*!
            \brief Destroys the json_writer.
        */
        virtual ~json_writer()
        {}


    private:
        // types

        typedef typename timetable_type::station_location_type station_location_type;

        typedef typename timetable_type::train_kind_type train_kind_type;

        typedef typename train_kind_type::color_type color_type;

        typedef typename train_kind_type::weight_type weight_type;

        typedef typename train_kind_type::line_style_type line_style_type;

        typedef typename timetable_type::train_type train_type;

        typedef typename train_type::stops_type stops_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename stop_type::time_type time_type;

        typedef typename timetable_type::string_type string_type;

        typedef typename string_type::value_type char_type;

        typedef typename string_type::size_type size_type;

        typedef typename output_stream_type::char_type output_char_type;

        typedef std::basic_string<output_char_type> output_string_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static const output_string_type& comma()
        {
            static const output_string_type singleton(TETENGO2_TEXT(","));
            return singleton;
        }

        static const output_string_type& space()
        {
            static const output_string_type singleton(TETENGO2_TEXT(" "));
            return singleton;
        }

        static const output_string_type& array_begin()
        {
            static const output_string_type singleton(TETENGO2_TEXT("["));
            return singleton;
        }

        static const output_string_type& array_end()
        {
            static const output_string_type singleton(TETENGO2_TEXT("]"));
            return singleton;
        }

        static const output_string_type& object_begin()
        {
            static const output_string_type singleton(TETENGO2_TEXT("{"));
            return singleton;
        }

        static const output_string_type& object_end()
        {
            static const output_string_type singleton(TETENGO2_TEXT("}"));
            return singleton;
        }

        static const string_type quote(const string_type& string)
        {
            static const string_type quotation_symbol(TETENGO2_TEXT("\""));
            return quotation_symbol + string + quotation_symbol;
        }

        static void new_line(const size_type level, output_stream_type& output_stream)
        {
            output_stream << std::endl;
            output_stream << output_string_type(level * 4, output_char_type(TETENGO2_TEXT(' ')));
        }

        static void write_object_key(const string_type& key, const size_type level, output_stream_type& output_stream)
        {
            output_stream << encoder().encode(quote(key)) << output_string_type(TETENGO2_TEXT(": "));
        }

        static void write_object_entry(
            const string_type&  key,
            const string_type&  value,
            const size_type     level,
            output_stream_type& output_stream
        )
        {
            write_object_key(key, level, output_stream);
            output_stream << encoder().encode(quote(value));
        }

        template <typename Integer>
        static void write_object_entry(
            const string_type&  key,
            const Integer       value,
            const size_type     level,
            output_stream_type& output_stream,
            const typename std::enable_if<std::is_integral<Integer>::value>::type* const = NULL
        )
        {
            write_object_key(key, level, output_stream);
            output_stream << value;
        }

        static void write_object_entry(
            const string_type&  key,
            const bool          value,
            const size_type     level,
            output_stream_type& output_stream
        )
        {
            write_object_key(key, level, output_stream);
            output_stream <<
                (value ? output_string_type(TETENGO2_TEXT("true")) : output_string_type(TETENGO2_TEXT("false")));
        }

        static void write_header(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << object_begin();

            new_line(level + 1, output_stream);
            write_object_entry(string_type(TETENGO2_TEXT("title")), timetable.title(), level + 1, output_stream);

            new_line(level, output_stream);
            output_stream << object_end();
        }

        static void write_station_locations(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            if (!timetable.station_locations().empty())
            {
                std::for_each(
                    timetable.station_locations().begin(),
                    boost::prior(timetable.station_locations().end()),
                    TETENGO2_CPP11_BIND(
                        write_station_location,
                        tetengo2::cpp11::placeholders_1(),
                        level,
                        tetengo2::cpp11::ref(output_stream),
                        false
                    )
                );
                write_station_location(*boost::prior(timetable.station_locations().end()), level, output_stream, true);

                new_line(level, output_stream);
            }

            output_stream << array_end();
        }

        static void write_station_location(
            const station_location_type& station_location,
            const size_type              level,
            output_stream_type&          output_stream,
            const bool                   last
        )
        {
            new_line(level + 1, output_stream);
            output_stream << object_begin();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("name")), station_location.station().name(), level, output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("grade")), station_location.station().grade().name(), level, output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("show_down_arrival_times")),
                station_location.station().shows_down_arrival_times(),
                level,
                output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("show_up_arrival_times")),
                station_location.station().shows_up_arrival_times(),
                level,
                output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("meterage")), station_location.meterage(), level, output_stream
            );

            new_line(level + 1, output_stream);
            output_stream << object_end();
            if (!last)
                output_stream << comma();
        }

        static void write_train_kinds(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            if (!timetable.train_kinds().empty())
            {
                std::for_each(
                    timetable.train_kinds().begin(),
                    boost::prior(timetable.train_kinds().end()),
                    TETENGO2_CPP11_BIND(
                        write_train_kind,
                        tetengo2::cpp11::placeholders_1(),
                        level,
                        tetengo2::cpp11::ref(output_stream),
                        false
                    )
                );
                write_train_kind(*boost::prior(timetable.train_kinds().end()), level, output_stream, true);

                new_line(level, output_stream);
            }

            output_stream << array_end();
        }

        static void write_train_kind(
            const train_kind_type& train_kind,
            const size_type        level,
            output_stream_type&    output_stream,
            const bool             last
        )
        {
            new_line(level + 1, output_stream);
            output_stream << object_begin();

            new_line(level + 2, output_stream);
            write_object_entry(string_type(TETENGO2_TEXT("name")), train_kind.name(), level, output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("abbreviation")), train_kind.abbreviation(), level, output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("color")), to_string(train_kind.color()), level, output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("weight")), static_cast<int>(train_kind.weight()), level, output_stream
            );
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("line_style")),
                static_cast<int>(train_kind.line_style()),
                level,
                output_stream
            );

            new_line(level + 1, output_stream);
            output_stream << object_end();
            if (!last)
                output_stream << comma();
        }

        static string_type to_string(const color_type& color)
        {
            std::basic_ostringstream<char_type> stream;

            stream <<
                boost::basic_format<char_type>(string_type(TETENGO2_TEXT("%02X%02X%02X"))) %
                static_cast<int>(color.red()) %
                static_cast<int>(color.green()) %
                static_cast<int>(color.blue());

            return stream.str();
        }

        static void write_down_trains(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            if (!timetable.down_trains().empty())
            {
                std::for_each(
                    timetable.down_trains().begin(),
                    boost::prior(timetable.down_trains().end()),
                    TETENGO2_CPP11_BIND(
                        write_train,
                        tetengo2::cpp11::placeholders_1(),
                        level,
                        tetengo2::cpp11::ref(output_stream),
                        false
                    )
                );
                write_train(*boost::prior(timetable.down_trains().end()), level, output_stream, true);

                new_line(level, output_stream);
            }


            output_stream << array_end();
        }

        static void write_up_trains(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            if (!timetable.up_trains().empty())
            {
                std::for_each(
                    timetable.up_trains().begin(),
                    boost::prior(timetable.up_trains().end()),
                    TETENGO2_CPP11_BIND(
                        write_train,
                        tetengo2::cpp11::placeholders_1(),
                        level,
                        tetengo2::cpp11::ref(output_stream),
                        false
                    )
                );
                write_train(*boost::prior(timetable.up_trains().end()), level, output_stream, true);

                new_line(level, output_stream);
            }

            output_stream << array_end();
        }

        static void write_train(
            const train_type&   train,
            const size_type     level,
            output_stream_type& output_stream,
            const bool          last
        )
        {
            new_line(level + 1, output_stream);
            output_stream << object_begin();

            new_line(level + 2, output_stream);
            write_object_entry(string_type(TETENGO2_TEXT("number")), train.number(), level, output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type(TETENGO2_TEXT("kind_index")), train.kind_index(), level, output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type(TETENGO2_TEXT("name")), train.name(), level, output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type(TETENGO2_TEXT("name_number")), train.name_number(), level, output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_entry(string_type(TETENGO2_TEXT("note")), train.note(), level, output_stream);
            output_stream << comma();

            new_line(level + 2, output_stream);
            write_object_key(string_type(TETENGO2_TEXT("stops")), level, output_stream);
            write_stops(train.stops(), level + 2, output_stream);

            new_line(level + 1, output_stream);
            output_stream << object_end();
            if (!last)
                output_stream << comma();
        }

        static void write_stops(
            const stops_type&   stops,
            const size_type     level,
            output_stream_type& output_stream
        )
        {
            output_stream << array_begin();

            if (!stops.empty())
            {
                std::for_each(
                    stops.begin(),
                    boost::prior(stops.end()),
                    TETENGO2_CPP11_BIND(
                        write_stop, 
                        tetengo2::cpp11::placeholders_1(),
                        level,
                        tetengo2::cpp11::ref(output_stream),
                        false
                    )
                );
                write_stop(*boost::prior(stops.end()), level, output_stream, true);

                new_line(level, output_stream);
            }

            output_stream << array_end();
        }

        static void write_stop(
            const stop_type&    stop,
            const size_type     level,
            output_stream_type& output_stream,
            const bool          last
        )
        {
            new_line(level + 1, output_stream);
            output_stream << array_begin();

            output_stream << time_representation(stop.arrival());
            output_stream << comma() << space();

            output_stream << time_representation(stop.departure());
            output_stream << comma() << space();

            output_stream << encoder().encode(quote(stop.platform()));

            output_stream << array_end();
            if (!last)
                output_stream << comma();
        }

        static output_string_type time_representation(const time_type& time)
        {
            if (time == time_type::uninitialized())
                return output_string_type(TETENGO2_TEXT("    -1"));

            typedef typename time_type::tick_type tick_type;
            typedef std::tuple<tick_type, tick_type, tick_type> hours_minutes_seconds_type;
            const hours_minutes_seconds_type hours_minutes_seconds = time.hours_minutes_seconds();
            const tick_type representation =
                std::get<0>(hours_minutes_seconds) * 10000 +
                std::get<1>(hours_minutes_seconds) * 100 +
                std::get<2>(hours_minutes_seconds);
            std::basic_ostringstream<output_char_type> stream;
            stream <<
                boost::basic_format<output_char_type>(TETENGO2_TEXT("% 6d"), std::locale::classic()) % representation;
            return stream.str();
        }


        // virtual functions

        virtual path_type extension_impl()
        const
        {
            return path_type(TETENGO2_TEXT(".btt"));
        }

        virtual void write_impl(const timetable_type& timetable, output_stream_type& output_stream)
        {
            output_stream << array_begin();

            new_line(1, output_stream);
            write_header(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_station_locations(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_train_kinds(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_down_trains(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_up_trains(timetable, 1, output_stream);

            new_line(0, output_stream);
            output_stream << array_end();

            new_line(0, output_stream);
        }


    };


}}}


#endif
