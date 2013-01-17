/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

//#include <algorithm>
//#include <cstddef>
//#include <iterator>
#include <ostream>
//#include <string>
//#include <utility>

#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>

#include "tetengo2.detail.stub.drawing.h"
#include <tetengo2.detail.stub.encoding.h>
#include <tetengo2.meta.assoc_list.h>
#include <tetengo2.text.encoder.h>
#include <tetengo2.text.encoding.locale.h>
#include <tetengo2.text.grammar.json.h>
#include <tetengo2.text.pull_parser.h>
#include <tetengo2.text.push_parser.h>
#include <tetengo2.gui.drawing.color.h>
#include <tetengo2.gui.drawing.font.h>

#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.serializer.reader.h"
#include "bobura.model.serializer.reader_selector.h"
#include "bobura.model.serializer.reader_set.h"
#include "bobura.model.serializer.writer.h"
#include "bobura.model.serializer.writer_selector.h"
#include "bobura.model.serializer.writer_set.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.station.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.font_color_set.h"
#include "bobura.model.timetable_info.station_interval_calculator.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"
#include "bobura.model.train_kind.h"


namespace test_bobura { namespace model
{
    /**** Common ************************************************************/

    namespace type
    {
        struct size;           //!< The size type.
        struct difference;     //!< The difference type.
        struct string;         //!< The string type.
        struct path;           //!< The path type.
        struct output_stream;  //!< The output stream type.
        struct font;           //!< The font type.
        struct color;          //!< The color type.
        struct abstract_window; //!< The abstract window type.
        struct message_catalog; //!< The message catalog type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        typedef tetengo2::detail::stub::drawing drawing_details_type;
        struct abstract_window_type
        {};
        struct message_catalog_type
        {};
    }
#endif

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, std::string>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::path, boost::filesystem::path>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::output_stream, std::ostream>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::font, tetengo2::gui::drawing::font<std::string, std::size_t, detail::drawing_details_type>
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::color, tetengo2::gui::drawing::color<unsigned char>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::abstract_window, detail::abstract_window_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::message_catalog, detail::message_catalog_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>
        type_list;


    /**** Model *************************************************************/

    namespace type { namespace model
    {
        struct font_color;     //!< The font and color type.
        struct font_color_set; //!< The font and color set type.
        struct grade_type_set; //!< The station grade type set type.
        struct station;        //!< The station type.
        struct station_location; //!< The station location type.
        struct train_kind;     //!< The train kind type.
        struct time_span;      //!< The time span type.
        struct time;           //!< The time type.
        struct stop;           //!< The stop type.
        struct train;          //!< The train type.
        struct station_interval_calculator; //!< The station interval calculator type.
        struct timetable;      //!< The timetable type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace model
    {
        typedef
            bobura::model::timetable_info::font_color<
                boost::mpl::at<type_list, type::font>::type, boost::mpl::at<type_list, type::color>::type
            >
            font_color_type;
        typedef bobura::model::timetable_info::font_color_set<font_color_type> font_color_set_type;
        typedef
            bobura::model::station_info::grade_type_set<boost::mpl::at<type_list, type::string>::type>
            grade_type_set_type;
        typedef grade_type_set_type::grade_type grade_type;
        typedef bobura::model::station<boost::mpl::at<type_list, type::string>::type, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<station_type, boost::mpl::at<type_list, type::size>::type>
            station_location_type;
        typedef
            bobura::model::train_kind<
                boost::mpl::at<type_list, type::string>::type, boost::mpl::at<type_list, type::color>::type
            >
            train_kind_type;
        typedef bobura::model::train_info::time_span<boost::mpl::at<type_list, type::difference>::type> time_span_type;
        typedef bobura::model::train_info::time<boost::mpl::at<type_list, type::size>::type, time_span_type> time_type;
        typedef
            bobura::model::train_info::stop<detail::model::time_type, boost::mpl::at<type_list, type::string>::type>
            stop_type;
        typedef
            bobura::model::train<
                boost::mpl::at<type_list, type::string>::type, boost::mpl::at<type_list, type::size>::type, stop_type
            >
            train_type;
        typedef
            bobura::model::timetable_info::station_interval_calculator<station_location_type, train_type>
            station_interval_calculator_type;
    }}
#endif

    //! The model type list.
    typedef
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::font_color_set, detail::model::font_color_set_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::grade_type_set, detail::model::grade_type_set_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::station, detail::model::station_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::station_location, detail::model::station_location_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::train_kind, detail::model::train_kind_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::time_span, detail::model::time_span_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::time, detail::model::time_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::stop, detail::model::stop_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::model::train, detail::model::train_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::station_interval_calculator, detail::model::station_interval_calculator_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::timetable,
                bobura::model::timetable<
                    boost::mpl::at<type_list, type::string>::type,
                    detail::model::station_location_type,
                    detail::model::station_interval_calculator_type,
                    detail::model::train_kind_type,
                    detail::model::train_type,
                    detail::model::font_color_set_type,
                    bobura::model::message::timetable_observer_set
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>
        model_type_list;


    /**** Serialization *****************************************************/

    namespace type { namespace serialization
    {
        struct reader;         //!< The reader type.
        struct reader_selector; //!< The reader selector type.
        struct json_reader;    //!< The JSON reader type.
        struct bzip2_reader;   //!< The bzip2 reader type.
        struct oudia_reader;   //!< The OuDia reader type.
        struct windia_reader;  //!< The WinDIA reader type.
        struct reader_set;     //!< The reader set type.
        struct writer;         //!< The writer type.
        struct writer_selector; //!< The writer selector type.
        struct json_writer;    //!< The JSON writer type.
        struct bzip2_writer;   //!< The bzip2 writer type.
        struct writer_set;     //!< The writer set type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace serialization
    {
        typedef std::string io_string_type;
        typedef
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>> input_stream_iterator_type;
        typedef tetengo2::text::grammar::json<input_stream_iterator_type> grammar_type;
        typedef tetengo2::text::push_parser<input_stream_iterator_type, grammar_type, int, double> push_parser_type;
        typedef
            tetengo2::text::pull_parser<push_parser_type, boost::mpl::at<type_list, type::size>::type>
            pull_parser_type;
        struct select_oudia_diagram_type
        {
            typedef boost::mpl::at<type_list, type::string>::type string_type;

            typedef boost::mpl::at<type_list, type::abstract_window>::type abstract_window_type;

            typedef boost::mpl::at<type_list, type::message_catalog>::type message_catalog_type;

            string_type m_wanted;

            select_oudia_diagram_type()
            :
            m_wanted()
            {}

            explicit select_oudia_diagram_type(string_type wanted)
            :
            m_wanted(std::move(wanted))
            {}

            template <typename Iterator>
            Iterator operator()(const Iterator first, const Iterator last)
            const
            {
                return std::find(first, last, m_wanted);
            }

        };
        typedef tetengo2::detail::stub::encoding encoding_details_type;
        typedef
            tetengo2::text::encoding::locale<boost::mpl::at<type_list, type::string>::type, encoding_details_type>
            internal_encoding_type;
        typedef tetengo2::text::encoding::locale<io_string_type, encoding_details_type> timetable_file_encoding_type;
        typedef
            tetengo2::text::encoder<internal_encoding_type, timetable_file_encoding_type> timetable_file_encoder_type;
        typedef
            bobura::model::serializer::reader_set<
                detail::serialization::input_stream_iterator_type,
                boost::mpl::at<model_type_list, type::model::timetable>::type,
                pull_parser_type,
                boost::mpl::at<model_type_list, type::model::grade_type_set>::type,
                select_oudia_diagram_type,
                timetable_file_encoder_type,
                timetable_file_encoder_type
            >
            reader_set_type;
        typedef
            bobura::model::serializer::writer_set<
                boost::mpl::at<type_list, type::output_stream>::type,
                boost::mpl::at<model_type_list, type::model::timetable>::type,
                boost::mpl::at<type_list, type::path>::type,
                boost::mpl::at<model_type_list, type::model::grade_type_set>::type,
                timetable_file_encoder_type
            >
            writer_set_type;
    }}
#endif

    //! The serialization type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::reader,
                bobura::model::serializer::reader<
                    detail::serialization::input_stream_iterator_type,
                    boost::mpl::at<model_type_list, type::model::timetable>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::reader_selector,
                bobura::model::serializer::reader_selector<
                    detail::serialization::input_stream_iterator_type,
                    boost::mpl::at<model_type_list, type::model::timetable>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::json_reader, detail::serialization::reader_set_type::json_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::bzip2_reader, detail::serialization::reader_set_type::bzip2_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::oudia_reader, detail::serialization::reader_set_type::oudia_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::windia_reader, detail::serialization::reader_set_type::windia_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::serialization::reader_set, detail::serialization::reader_set_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::writer,
                bobura::model::serializer::writer<
                    boost::mpl::at<type_list, type::output_stream>::type,
                    boost::mpl::at<model_type_list, type::model::timetable>::type,
                    boost::mpl::at<type_list, type::path>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::writer_selector,
                bobura::model::serializer::writer_selector<
                    boost::mpl::at<type_list, type::output_stream>::type,
                    boost::mpl::at<model_type_list, type::model::timetable>::type,
                    boost::mpl::at<type_list, type::path>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::json_writer, detail::serialization::writer_set_type::json_writer_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::serialization::bzip2_writer, detail::serialization::writer_set_type::bzip2_writer_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::serialization::writer_set, detail::serialization::writer_set_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>
        serialization_type_list;


}}


#endif
