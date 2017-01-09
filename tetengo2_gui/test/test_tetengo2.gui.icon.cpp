/*! \file
    \brief Test of class tetengo2::gui::icon.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <cstddef>

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/measure.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using dimension_type = common_type_list_type::dimension_type;

    using icon_type = tetengo2::gui::icon<dimension_type, detail_type_list_type::icon_type>;


    // functions

    dimension_type make_dimension(const std::size_t width, const std::size_t height)
    {
        using width_type = tetengo2::gui::dimension<dimension_type>::width_type;
        using height_type = tetengo2::gui::dimension<dimension_type>::height_type;
        return { width_type{ width }, height_type{ height } };
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
            const icon_type icon{ boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") } };
        }
        {
            const icon_type icon{ boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") }, make_dimension(42, 42) };
        }
    }

    BOOST_AUTO_TEST_CASE(path)
    {
        BOOST_TEST_PASSPOINT();

        const icon_type icon{ boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") } };

        BOOST_CHECK(icon.path() == boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") });
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const icon_type icon{ boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") }, make_dimension(42, 42) };

        BOOST_CHECK(icon.dimension() == make_dimension(42, 42));
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const icon_type icon{ boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") } };

            icon.details();
        }
        {
            icon_type icon{ boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") } };

            icon.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
