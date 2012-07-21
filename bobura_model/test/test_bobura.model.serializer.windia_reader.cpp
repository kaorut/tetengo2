/*! \file
    \brief Test of class bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <iterator>
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

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::windia_reader
        >::type
        reader_type;


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
        "6,101D,foo,1,1100,-,-,1130/1140,-,1150/,\\\n"
        "\t%\n"
        "(96),123D,,,1200,1210,1220/1230,1240/,,,\\\n"
        "\t%xyzw\n"
        "\n"
        "[\x8F\xE3\x82\xE8]\n" // nobori
        ",122D,,,1040/,1030/,1010/1020,1000,,\n"
        ",124D,,,1210/,1200/,1140/1150,1120/1130,1110/,1100,\\\n"
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
            const std::unique_ptr<timetable_type> p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );

            BOOST_CHECK(!p_timetable);
        }
        {
            reader_type reader;

            std::istringstream input_stream(data3);
            const std::unique_ptr<timetable_type> p_timetable =
                reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );

            BOOST_CHECK(!p_timetable);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
