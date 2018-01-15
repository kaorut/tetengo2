/*! \file
    \brief Test of class tetengo2::gui::drawing::picture.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <stdexcept>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/unit/pixel.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using picture_type = tetengo2::gui::drawing::picture<dimension_type, drawing_details_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(picture)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const picture_type picture{ dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } } };
        }
        {
            picture_type::details_ptr_type p_details{
                drawing_details_type::create_picture(
                    dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } }
                )
            };
            const picture_type picture2{ std::move(p_details) };
        }
        {
            picture_type::details_ptr_type p_details;

            BOOST_CHECK_THROW(picture_type picture{ std::move(p_details) }, std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const picture_type picture{ dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } } };

        BOOST_CHECK((picture.dimension() == dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } }));
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const picture_type picture{ dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } } };

            picture.details();
        }
        {
            picture_type picture{ dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } } };

            picture.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
