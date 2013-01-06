/*! \file
    \brief Test of class bobura::model::serializer::oudia_reader.

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
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::oudia_reader
        >::type
        reader_type;


    // variables

    const std::string data_empty;

    const std::string data_no_train =
        "FileType=OuDia.1.02\n"
        "Rosen.\n"
        "Rosenmei=\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=\x95\x81\x92\xCA\n" // futsuu
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Jissen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "KitenJikoku=000\n"
        "DiagramDgrYZahyouKyoriDefault=60\n"
        "Comment=\n"
        ".\n"
        "DispProp.\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouVFont=PointTextHeight=9;Facename=@MS Gothic\n"
        "DiaEkimeiFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaJikokuFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaRessyaFont=PointTextHeight=9;Facename=MS Gothic\n"
        "CommentFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaMojiColor=00000000\n"
        "DiaHaikeiColor=00FFFFFF\n"
        "DiaRessyaColor=00000000\n"
        "DiaJikuColor=00C0C0C0\n"
        "EkimeiLength=6\n"
        "JikokuhyouRessyaWidth=5\n"
        ".\n"
        "FileTypeAppComment=OuDia Ver. 1.02.01\n";

    const std::string data_full =
        "FileType=OuDia.1.02\n"
        "Rosen.\n"
        "Rosenmei=abc\n"
        "Eki.\n"
        "Ekimei=hoge\n"
        "Ekijikokukeisiki=Jikokukeisiki_Hatsu\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Eki.\n"
        "Ekimei=fuga\n"
        "Ekijikokukeisiki=Jikokukeisiki_NoboriChaku\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Eki.\n"
        "Ekimei=piyo\n"
        "Ekijikokukeisiki=Jikokukeisiki_Hatsuchaku\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Eki.\n"
        "Ekimei=mnu\n"
        "Ekijikokukeisiki=Jikokukeisiki_Hatsuchaku\n"
        "Ekikibo=Ekikibo_Syuyou\n"
        ".\n"
        "Eki.\n"
        "Ekimei=iroha\n"
        "Ekijikokukeisiki=Jikokukeisiki_NoboriChaku\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Eki.\n"
        "Ekimei=nihohe\n"
        "Ekijikokukeisiki=Jikokukeisiki_Hatsu\n"
        "Ekikibo=Ekikibo_Ippan\n"
        ".\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=futsuu\n"
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Jissen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=Super Kaisoku\n"
        "Ryakusyou=SKai\n"
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Hasen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "Dia.\n"
        "DiaName=Dia\n"
        "Kudari.\n"
        "Ressya.\n"
        "Houkou=Kudari\n"
        "Syubetsu=0\n"
        "Ressyabangou=121D\n"
        "EkiJikoku=1;1000,1;1010,1;1020/1030,1;1040/1050,1;1100,1;1100\n"
        ".\n"
        "Ressya.\n"
        "Houkou=Kudari\n"
        "Syubetsu=1\n"
        "Ressyabangou=101D\n"
        "Ressyamei=foo\n"
        "Gousuu=1\n"
        "EkiJikoku=1;1100,2,2,2:1130/1140,2,1;1150\n"
        ".\n"
        "Ressya.\n"
        "Houkou=Kudari\n"
        "Syubetsu=0\n"
        "Ressyabangou=123D\n"
        "EkiJikoku=1;1200,1;1210,1;1220/1230,1;1240/,,\n"
        ".\n"
        ".\n"
        "Nobori.\n"
        "Ressya.\n"
        "Houkou=Nobori\n"
        "Syubetsu=0\n"
        "Ressyabangou=122D\n"
        "EkiJikoku=,,1;1000,1;1010/1020,1;1030/,1;1040\n"
        ".\n"
        "Ressya.\n"
        "Houkou=Nobori\n"
        "Syubetsu=0\n"
        "Ressyabangou=124D\n"
        "EkiJikoku=1;1100,1:1110/,1;1120/1130,2;1140/1150,1;1200/,1;1210\n"
        ".\n"
        "Ressya.\n"
        "Houkou=Nobori\n"
        "Syubetsu=1\n"
        "Ressyabangou=102D\n"
        "Ressyamei=bar\n"
        "Gousuu=2\n"
        "EkiJikoku=1;1200,2,2,2,2,1;1230\n"
        ".\n"
        ".\n"
        ".\n"
        "KitenJikoku=000\n"
        "DiagramDgrYZahyouKyoriDefault=60\n"
        "Comment=\n"
        ".\n"
        "DispProp.\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouVFont=PointTextHeight=9;Facename=@MS Gothic\n"
        "DiaEkimeiFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaJikokuFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaRessyaFont=PointTextHeight=9;Facename=MS Gothic\n"
        "CommentFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaMojiColor=00000000\n"
        "DiaHaikeiColor=00FFFFFF\n"
        "DiaRessyaColor=00000000\n"
        "DiaJikuColor=00C0C0C0\n"
        "EkimeiLength=6\n"
        "JikokuhyouRessyaWidth=5\n"
        ".\n"
        "FileTypeAppComment=OuDia Ver. 1.02.01\n";

    const std::string data_too_old_version =
        "FileType=OuDia.1.01\n"
        "Rosen.\n"
        "Rosenmei=\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=\x95\x81\x92\xCA\n" // futsuu
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Jissen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "KitenJikoku=000\n"
        "DiagramDgrYZahyouKyoriDefault=60\n"
        "Comment=\n"
        ".\n"
        "DispProp.\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouVFont=PointTextHeight=9;Facename=@MS Gothic\n"
        "DiaEkimeiFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaJikokuFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaRessyaFont=PointTextHeight=9;Facename=MS Gothic\n"
        "CommentFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaMojiColor=00000000\n"
        "DiaHaikeiColor=00FFFFFF\n"
        "DiaRessyaColor=00000000\n"
        "DiaJikuColor=00C0C0C0\n"
        "EkimeiLength=6\n"
        "JikokuhyouRessyaWidth=5\n"
        ".\n"
        "FileTypeAppComment=OuDia Ver. 1.02.01\n";

    const std::string data_too_new_version =
        "FileType=OuDia.1.03\n"
        "Rosen.\n"
        "Rosenmei=\n"
        "Ressyasyubetsu.\n"
        "Syubetsumei=\x95\x81\x92\xCA\n" // futsuu
        "JikokuhyouMojiColor=00000000\n"
        "JikokuhyouFontIndex=0\n"
        "DiagramSenColor=00000000\n"
        "DiagramSenStyle=SenStyle_Jissen\n"
        "StopMarkDrawType=EStopMarkDrawType_DrawOnStop\n"
        ".\n"
        "KitenJikoku=000\n"
        "DiagramDgrYZahyouKyoriDefault=60\n"
        "Comment=\n"
        ".\n"
        "DispProp.\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic;Bold=1;Itaric=1\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouFont=PointTextHeight=9;Facename=MS Gothic\n"
        "JikokuhyouVFont=PointTextHeight=9;Facename=@MS Gothic\n"
        "DiaEkimeiFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaJikokuFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaRessyaFont=PointTextHeight=9;Facename=MS Gothic\n"
        "CommentFont=PointTextHeight=9;Facename=MS Gothic\n"
        "DiaMojiColor=00000000\n"
        "DiaHaikeiColor=00FFFFFF\n"
        "DiaRessyaColor=00000000\n"
        "DiaJikuColor=00C0C0C0\n"
        "EkimeiLength=6\n"
        "JikokuhyouRessyaWidth=5\n"
        ".\n"
        "FileTypeAppComment=OuDia Ver. 1.02.01\n";


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(oudia_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const reader_type reader;
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        //{
        //    reader_type reader;

        //    std::istringstream input_stream(data_empty);
        //    BOOST_CHECK(
        //        !reader.selects(
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
        //        )
        //    );
        //}
        //{
        //    reader_type reader;

        //    std::istringstream input_stream(data_no_train);
        //    BOOST_CHECK(
        //        reader.selects(
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
        //        )
        //    );
        //}
        //{
        //    reader_type reader;

        //    std::istringstream input_stream(data_too_old_version);
        //    BOOST_CHECK(
        //        !reader.selects(
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
        //        )
        //    );
        //}
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        //{
        //    reader_type reader;

        //    std::istringstream input_stream(data_empty);
        //    const std::unique_ptr<timetable_type> p_timetable =
        //        reader.read(
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
        //        );

        //    BOOST_REQUIRE(!p_timetable);
        //}
        //{
        //    reader_type reader;

        //    std::istringstream input_stream(data_no_train);
        //    const std::unique_ptr<timetable_type> p_timetable =
        //        reader.read(
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
        //        );

        //    BOOST_REQUIRE(p_timetable);
        //    BOOST_CHECK(p_timetable->line_name().empty());
        //    BOOST_CHECK(p_timetable->station_locations().empty());
        //    BOOST_CHECK(p_timetable->train_kinds().empty());
        //    BOOST_CHECK(p_timetable->down_trains().empty());
        //    BOOST_CHECK(p_timetable->up_trains().empty());
        //}
        //{
        //    reader_type reader;

        //    std::istringstream input_stream(data_full);
        //    const std::unique_ptr<timetable_type> p_timetable =
        //        reader.read(
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
        //        );

        //    BOOST_REQUIRE(p_timetable);
        //    BOOST_CHECK(p_timetable->line_name() == string_type(TETENGO2_TEXT("abc")));

        //    BOOST_CHECK_EQUAL(p_timetable->station_locations().size(), 6U);
        //    {
        //        const station_location_type& station_location = p_timetable->station_locations()[0];
        //        BOOST_CHECK(station_location.station().name() == string_type(TETENGO2_TEXT("hoge")));
        //        BOOST_CHECK(station_location.station().grade().name() == string_type(TETENGO2_TEXT("local")));
        //        BOOST_CHECK_EQUAL(station_location.meterage(), 0U);
        //    }
        //    {
        //        const station_location_type& station_location = p_timetable->station_locations()[2];
        //        BOOST_CHECK(station_location.station().name() == string_type(TETENGO2_TEXT("piyo")));
        //        BOOST_CHECK(
        //            station_location.station().grade().name() == string_type(TETENGO2_TEXT("local terminal"))
        //        );
        //        BOOST_CHECK_EQUAL(station_location.meterage(), 2U);
        //    }
        //    {
        //        const station_location_type& station_location = p_timetable->station_locations()[4];
        //        BOOST_CHECK(station_location.station().name() == string_type(TETENGO2_TEXT("iroha")));
        //        BOOST_CHECK(station_location.station().grade().name() == string_type(TETENGO2_TEXT("local")));
        //        BOOST_CHECK(station_location.station().shows_up_arrival_times());
        //        BOOST_CHECK_EQUAL(station_location.meterage(), 4U);
        //    }

        //    BOOST_CHECK_EQUAL(p_timetable->train_kinds().size(), 4U);
        //    {
        //        const train_kind_type& train_kind = p_timetable->train_kinds()[0];

        //        BOOST_CHECK(train_kind.name() == string_type(TETENGO2_TEXT("\x95\x81\x92\xCA"))); // futsuu
        //        BOOST_CHECK(train_kind.color() == color_type(0, 0, 0));
        //        BOOST_CHECK_EQUAL(train_kind.weight(), train_kind_type::weight_type::normal);
        //    }
        //    {
        //        const train_kind_type& train_kind = p_timetable->train_kinds()[3];

        //        BOOST_CHECK(train_kind.name() == string_type(TETENGO2_TEXT("express")));
        //        BOOST_CHECK(train_kind.color() == color_type(255, 0, 0));
        //        BOOST_CHECK_EQUAL(train_kind.weight(), train_kind_type::weight_type::bold);
        //    }

        //    BOOST_CHECK_EQUAL(p_timetable->down_trains().size(), 3U);
        //    {
        //        const train_type& train = p_timetable->down_trains()[0];

        //        BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("121D")));
        //        BOOST_CHECK(train.name().empty());
        //        BOOST_CHECK_EQUAL(train.kind_index(), 0U);
        //        BOOST_CHECK_EQUAL(train.stops().size(), 6U);
        //        {
        //            const stop_type& stop = train.stops()[0];

        //            BOOST_CHECK(stop.arrival() == time_type::uninitialized());
        //            BOOST_CHECK(stop.departure() == time_type(10, 0, 0));
        //            BOOST_CHECK(!stop.operational());
        //            BOOST_CHECK(stop.platform().empty());
        //        }
        //        {
        //            const stop_type& stop = train.stops()[2];

        //            BOOST_CHECK(stop.arrival() == time_type(10, 20, 0));
        //            BOOST_CHECK(stop.departure() == time_type(10, 30, 0));
        //            BOOST_CHECK(!stop.operational());
        //            BOOST_CHECK(stop.platform().empty());
        //        }
        //    }
        //    {
        //        const train_type& train = p_timetable->down_trains()[1];

        //        BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("101D")));
        //        BOOST_CHECK(train.name() == string_type(TETENGO2_TEXT("foo")));
        //        BOOST_CHECK_EQUAL(train.kind_index(), 1U);
        //        BOOST_CHECK_EQUAL(train.stops().size(), 6U);
        //        {
        //            const stop_type& stop = train.stops()[0];

        //            BOOST_CHECK(stop.arrival() == time_type::uninitialized());
        //            BOOST_CHECK(stop.departure() == time_type(11, 0, 0));
        //            BOOST_CHECK(!stop.operational());
        //            BOOST_CHECK(stop.platform().empty());
        //        }
        //        {
        //            const stop_type& stop = train.stops()[2];

        //            BOOST_CHECK(stop.arrival() == time_type::uninitialized());
        //            BOOST_CHECK(stop.departure() == time_type::uninitialized());
        //            BOOST_CHECK(!stop.operational());
        //            BOOST_CHECK(stop.platform().empty());
        //        }
        //        {
        //            const stop_type& stop = train.stops()[3];

        //            BOOST_CHECK(stop.arrival() == time_type(11, 30, 0));
        //            BOOST_CHECK(stop.departure() == time_type(11, 40, 0));
        //            BOOST_CHECK(stop.operational());
        //            BOOST_CHECK(stop.platform().empty());
        //        }
        //    }

        //    BOOST_CHECK_EQUAL(p_timetable->up_trains().size(), 3U);
        //    {
        //        const train_type& train = p_timetable->up_trains()[1];

        //        BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("124D")));
        //        BOOST_CHECK(train.name().empty());
        //        BOOST_CHECK_EQUAL(train.kind_index(), 0U);
        //        BOOST_CHECK_EQUAL(train.stops().size(), 6U);
        //        {
        //            const stop_type& stop = train.stops()[2];

        //            BOOST_CHECK(stop.arrival() == time_type(11, 40, 00));
        //            BOOST_CHECK(stop.departure() == time_type(11, 50, 00));
        //            BOOST_CHECK(stop.operational());
        //            BOOST_CHECK(stop.platform().empty());
        //        }
        //        {
        //            const stop_type& stop = train.stops()[4];

        //            BOOST_CHECK(stop.arrival() == time_type(11, 10, 0));
        //            BOOST_CHECK(stop.departure() == time_type::uninitialized());
        //            BOOST_CHECK(!stop.operational());
        //            BOOST_CHECK(stop.platform().empty());
        //        }
        //    }
        //    {
        //        const train_type& train = p_timetable->up_trains()[2];

        //        BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("102D")));
        //        BOOST_CHECK(train.name() == string_type(TETENGO2_TEXT("bar")));
        //        BOOST_CHECK_EQUAL(train.kind_index(), 3U);
        //        BOOST_CHECK_EQUAL(train.stops().size(), 6U);
        //        {
        //            const stop_type& stop = train.stops()[4];

        //            BOOST_CHECK(stop.arrival() == time_type::uninitialized());
        //            BOOST_CHECK(stop.departure() == time_type::uninitialized());
        //            BOOST_CHECK(!stop.operational());
        //            BOOST_CHECK(stop.platform().empty());
        //        }
        //    }
        //}
        //{
        //    reader_type reader;

        //    std::istringstream input_stream(data_too_old_version);
        //    const std::unique_ptr<timetable_type> p_timetable =
        //        reader.read(
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
        //            boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
        //        );

        //    BOOST_REQUIRE(!p_timetable);
        //}
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
