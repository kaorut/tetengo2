/*! \file
    \brief Test of class bobura::model::serializer::bzip2_writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <sstream>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::bzip2_writer
        >::type
        writer_type;

    typedef writer_type::path_string_type path_string_type;


}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(bzip2_writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        //const writer_type bzip2_writer;
    }

    BOOST_AUTO_TEST_CASE(extension)
    {
        BOOST_TEST_PASSPOINT();

        //const writer_type bzip2_writer;

        //BOOST_CHECK(
        //    bzip2_writer.extension() == path_string_type(TETENGO2_TEXT("btt"))
        //);
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        //const writer_type bzip2_writer;

        //BOOST_CHECK(
        //    bzip2_writer.selects(path_string_type(TETENGO2_TEXT("btt")))
        //);
        //BOOST_CHECK(
        //    !bzip2_writer.selects(path_string_type(TETENGO2_TEXT("hoge")))
        //);
        //BOOST_CHECK(!bzip2_writer.selects(path_string_type()));
    }

    BOOST_AUTO_TEST_CASE(write)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
