/*! \file
    \brief Test of class tetengo2::gui::drawing::background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.drawing.h"

#include "tetengo2.gui.drawing.background.h"


namespace
{
    // types

    typedef
        tetengo2::gui::drawing::background<tetengo2::detail::stub::drawing>
        background_type;

    struct concrete_background : public background_type
    {
        concrete_background()
        :
        background_type()
        {}


    private:
        virtual boost::optional<const background_type::details_type&>
        details_impl()
        const
        {
            return boost::optional<const background_type::details_type&>();
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(background)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_background background;
    }

    BOOST_AUTO_TEST_CASE(handle)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_background background;

        background.details();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
