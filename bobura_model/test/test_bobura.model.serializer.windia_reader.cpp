/*! \file
    \brief Test of class bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <iterator>
//#include <memory>
//#include <sstream>
//#include <string>

//#include <boost/mpl/at.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type string_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::timetable>::type
        timetable_type;

    typedef timetable_type::station_location_type station_location_type;

    typedef timetable_type::train_kind_type train_kind_type;

    typedef train_kind_type::color_type color_type;

    typedef timetable_type::train_type train_type;

    typedef train_type::stop_type stop_type;

    typedef stop_type::time_type time_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::windia_reader
        >::type
        reader_type;

    typedef reader_type::error_type error_type;


    // variables

    const std::string data0;

    const std::string data1 =
        "[WinDIA]\n"
        "\n"
        "\n"
        "[\x89\x77]\n" // eki
        "\n"
        "[\x89\xBA\x82\xE8]\n" // kudari
        "\n"
        "[\x8F\xE3\x82\xE8]\n"; // nobori

    const std::string data2 =
        "[WinDIA]\n"
        "abc\n"
        "\n"
        "[\x89\x77]\n" // eki
        ",hoge\n"
        "u,fuga\n"
        "b,piyo\n"
        "pb,mnu\n"
        "u,iroha\n"
        "p,nihohe\n"
        "\n"
        "[\x90\xFC\x8E\xED]\n" // senshu
        "LINES=0,0,0,0,0,128,128,128,128,128,128,128,0,128,3,1,129,0,0,0,0,0,0,0\n"
        "Train04=junkaisoku,junk\n"
        "Train06=express,expr\n"
        "\n"
        "[\x89\xBA\x82\xE8]\n" // kudari
        ",121D,,,1000,1010,1020/1030,1040/1050,1100,1110/,\\\n"
        "\t%\n"
        "6,101D,foo,1,1100,-,-,1130/1140?,-,1150/,\\\n"
        "\t%\n"
        "(96),123D,,,1200,1210,1220/1230,1240/,,,\\\n"
        "\t%xyzw\n"
        "\n"
        "[\x8F\xE3\x82\xE8]\n" // nobori
        ",122D,,,1040/,1030/,1010/1020,1000,,\n"
        ",124D,,,1210/,1200/,1140?/1150,1120/1130,1110/,1100,\\\n"
        "\t%\n"
        "6(213),102D,bar,2,1230/,-,-,-,-,1200,\\\n"
        "\t%\n";

    const std::string data3 =
        "[hoge]\n";


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(windia_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const reader_type reader;
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        {
            reader_type reader;

            std::istringstream input_stream(data0);
            BOOST_CHECK(
                !reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            reader_type reader;

            std::istringstream input_stream(data1);
            BOOST_CHECK(
                reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            reader_type reader;

            std::istringstream input_stream(data3);
            BOOST_CHECK(
                !reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        {
            reader_type reader;

            std::istringstream input_stream(data0);
            error_type::enum_t error = error_type::none;
            const std::unique_ptr<timetable_type> p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK_EQUAL(error, error_type::corrupted);
        }
        {
            reader_type reader;

            std::istringstream input_stream(data1);
            error_type::enum_t error = error_type::none;
            const std::unique_ptr<timetable_type> p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK_EQUAL(error, error_type::none);
            BOOST_CHECK(p_timetable->line_name().empty());
            BOOST_CHECK(p_timetable->station_locations().empty());
            BOOST_CHECK(p_timetable->train_kinds().empty());
            BOOST_CHECK(p_timetable->down_trains().empty());
            BOOST_CHECK(p_timetable->up_trains().empty());
        }
        {
            reader_type reader;

            std::istringstream input_stream(data2);
            error_type::enum_t error = error_type::none;
            const std::unique_ptr<timetable_type> p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK_EQUAL(error, error_type::none);
            BOOST_CHECK(p_timetable->line_name() == string_type(TETENGO2_TEXT("abc")));

            BOOST_REQUIRE_EQUAL(p_timetable->station_locations().size(), 6U);
            {
                const station_location_type& station_location = p_timetable->station_locations()[0];
                BOOST_CHECK(station_location.station().name() == string_type(TETENGO2_TEXT("hoge")));
                BOOST_CHECK(station_location.station().grade().name() == string_type(TETENGO2_TEXT("local")));
                BOOST_CHECK_EQUAL(station_location.meterage(), 0U);
            }
            {
                const station_location_type& station_location = p_timetable->station_locations()[2];
                BOOST_CHECK(station_location.station().name() == string_type(TETENGO2_TEXT("piyo")));
                BOOST_CHECK(
                    station_location.station().grade().name() == string_type(TETENGO2_TEXT("local terminal"))
                );
                BOOST_CHECK_EQUAL(station_location.meterage(), 2U);
            }
            {
                const station_location_type& station_location = p_timetable->station_locations()[4];
                BOOST_CHECK(station_location.station().name() == string_type(TETENGO2_TEXT("iroha")));
                BOOST_CHECK(station_location.station().grade().name() == string_type(TETENGO2_TEXT("local")));
                BOOST_CHECK(station_location.station().shows_up_arrival_times());
                BOOST_REQUIRE_EQUAL(station_location.meterage(), 4U);
            }

            BOOST_REQUIRE_EQUAL(p_timetable->train_kinds().size(), 4U);
            {
                const train_kind_type& train_kind = p_timetable->train_kinds()[0];

                BOOST_CHECK(train_kind.name() == string_type(TETENGO2_TEXT("\x95\x81\x92\xCA"))); // futsuu
                BOOST_CHECK(train_kind.color() == color_type(0, 0, 0));
                BOOST_CHECK_EQUAL(train_kind.weight(), train_kind_type::weight_type::normal);
            }
            {
                const train_kind_type& train_kind = p_timetable->train_kinds()[3];

                BOOST_CHECK(train_kind.name() == string_type(TETENGO2_TEXT("express")));
                BOOST_CHECK(train_kind.color() == color_type(255, 0, 0));
                BOOST_CHECK_EQUAL(train_kind.weight(), train_kind_type::weight_type::bold);
            }

            BOOST_REQUIRE_EQUAL(p_timetable->down_trains().size(), 3U);
            {
                const train_type& train = p_timetable->down_trains()[0];

                BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("121D")));
                BOOST_CHECK(train.name().empty());
                BOOST_CHECK_EQUAL(train.kind_index(), 0U);
                BOOST_REQUIRE_EQUAL(train.stops().size(), 6U);
                {
                    const stop_type& stop = train.stops()[0];

                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(stop.departure() == time_type(10, 0, 0));
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const stop_type& stop = train.stops()[2];

                    BOOST_CHECK(stop.arrival() == time_type(10, 20, 0));
                    BOOST_CHECK(stop.departure() == time_type(10, 30, 0));
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            {
                const train_type& train = p_timetable->down_trains()[1];

                BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("101D")));
                BOOST_CHECK(train.name() == string_type(TETENGO2_TEXT("foo")));
                BOOST_CHECK_EQUAL(train.kind_index(), 1U);
                BOOST_REQUIRE_EQUAL(train.stops().size(), 6U);
                {
                    const stop_type& stop = train.stops()[0];

                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(stop.departure() == time_type(11, 0, 0));
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const stop_type& stop = train.stops()[2];

                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(stop.departure() == time_type::uninitialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const stop_type& stop = train.stops()[3];

                    BOOST_CHECK(stop.arrival() == time_type(11, 30, 0));
                    BOOST_CHECK(stop.departure() == time_type(11, 40, 0));
                    BOOST_CHECK(stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }

            BOOST_REQUIRE_EQUAL(p_timetable->up_trains().size(), 3U);
            {
                const train_type& train = p_timetable->up_trains()[1];

                BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("124D")));
                BOOST_CHECK(train.name().empty());
                BOOST_CHECK_EQUAL(train.kind_index(), 0U);
                BOOST_REQUIRE_EQUAL(train.stops().size(), 6U);
                {
                    const stop_type& stop = train.stops()[2];

                    BOOST_CHECK(stop.arrival() == time_type(11, 40, 00));
                    BOOST_CHECK(stop.departure() == time_type(11, 50, 00));
                    BOOST_CHECK(stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const stop_type& stop = train.stops()[4];

                    BOOST_CHECK(stop.arrival() == time_type(11, 10, 0));
                    BOOST_CHECK(stop.departure() == time_type::uninitialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            {
                const train_type& train = p_timetable->up_trains()[2];

                BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("102D")));
                BOOST_CHECK(train.name() == string_type(TETENGO2_TEXT("bar")));
                BOOST_CHECK_EQUAL(train.kind_index(), 3U);
                BOOST_REQUIRE_EQUAL(train.stops().size(), 6U);
                {
                    const stop_type& stop = train.stops()[4];

                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(stop.departure() == time_type::uninitialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
        }
        {
            reader_type reader;

            std::istringstream input_stream(data3);
            error_type::enum_t error = error_type::none;
            const std::unique_ptr<timetable_type> p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK_EQUAL(error, error_type::corrupted);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
