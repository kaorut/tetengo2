/*! \file
    \brief Test of class tetengo2::gui::menu_separator.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.gui.menu_observer_set.h"
#include "tetengo2.gui.traits.menu_traits.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"

#include "tetengo2.gui.menu_separator.h"


namespace
{
    // types

    typedef
        tetengo2::text::encoding::locale<
            std::string, tetengo2::detail::stub::encoding
        >
        encoding_type;

    typedef
        tetengo2::text::encoder<encoding_type, encoding_type> encoder_type;

    typedef
        tetengo2::gui::traits::menu_traits<
            std::string, encoder_type, tetengo2::gui::menu_observer_set
        >
        menu_traits_type;

    typedef tetengo2::detail::stub::menu menu_details_type;

    typedef
        tetengo2::gui::menu_separator<menu_traits_type, menu_details_type>
        menu_separator_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu_separator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const menu_separator_type menu_separator;
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const menu_separator_type menu_separator;

        BOOST_CHECK(
            &menu_separator.style() ==
            &menu_details_type::menu_separator_style()
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
