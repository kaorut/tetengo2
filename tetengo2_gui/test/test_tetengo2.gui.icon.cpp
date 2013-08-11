/*! \file
    \brief Test of class tetengo2::gui::icon.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <cstddef>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.icon.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"

#include "tetengo2.gui.icon.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::path>::type path_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type dimension_type;

    typedef tetengo2::gui::icon<path_type, dimension_type, tetengo2::detail::stub::icon> icon_type;


    // functions

    dimension_type make_dimension(const std::size_t width, const std::size_t height)
    {
        typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;
        typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;
        return dimension_type(width_type(width), height_type(height));
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(icon)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const icon_type icon(path_type(TETENGO2_TEXT("hoge.ico")));
        }
        {
            const icon_type icon(path_type(TETENGO2_TEXT("hoge.ico")), make_dimension(42, 42));
        }
    }

    BOOST_AUTO_TEST_CASE(path)
    {
        BOOST_TEST_PASSPOINT();

        const icon_type icon(path_type(TETENGO2_TEXT("hoge.ico")));

        BOOST_CHECK(icon.path() == path_type(TETENGO2_TEXT("hoge.ico")));
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const icon_type icon(path_type(TETENGO2_TEXT("hoge.ico")));

            icon.details();
        }
        {
            icon_type icon(path_type(TETENGO2_TEXT("hoge.ico")));

            icon.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
