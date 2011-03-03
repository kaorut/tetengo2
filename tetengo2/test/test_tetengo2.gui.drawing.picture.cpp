/*! \file
    \brief Test of class tetengo2::gui::drawing::picture.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <stdexcept>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.drawing.h"

#include "tetengo2.gui.drawing.picture.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::drawing drawing_details_type;

    typedef
        tetengo2::gui::drawing::picture<std::size_t, drawing_details_type>
        picture_type;

    typedef picture_type::dimension_type dimension_type;

    typedef int canvas_type;


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
            const canvas_type canvas(42);
            const picture_type picture(dimension_type(123, 456), canvas);
        }
        {
            const canvas_type canvas(42);
            picture_type::details_ptr_type p_details(
                tetengo2::detail::stub::drawing::create_picture(
                    dimension_type(123, 456), canvas
                )
            );
            const picture_type picture2(std::move(p_details));
        }
        {
            picture_type::details_ptr_type p_details;
            
            BOOST_CHECK_THROW(
                const picture_type picture(std::move(p_details)),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const canvas_type canvas(42);
        const picture_type picture(dimension_type(123, 456), canvas);

        BOOST_CHECK(picture.dimension() == dimension_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const canvas_type canvas(42);
            picture_type picture(dimension_type(123, 456), canvas);

            picture.details();
        }
        {
            const canvas_type canvas(42);
            const picture_type picture(dimension_type(123, 456), canvas);

            picture.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
