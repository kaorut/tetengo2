/*! \file
    \brief Test of class tetengo2::gui::drawing::picture_reader.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using path_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::path>::type;

    using picture_type =
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::picture>::type;

    using picture_reader_type =
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::picture_reader>::type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(picture_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        path_type path{};
        const picture_reader_type reader{ std::move(path) };
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        path_type path{};
        picture_reader_type reader{ std::move(path) };

        const auto p_picture = reader.read();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
