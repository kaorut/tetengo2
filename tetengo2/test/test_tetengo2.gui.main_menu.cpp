/*! \file
    \brief Test of class tetengo2::gui::main_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"
#include "tetengo2.gui.menu_observer_set.h"
#include "tetengo2.gui.traits.menu_traits.h"

#include "tetengo2.gui.main_menu.h"


namespace
{
    // types

    typedef
        tetengo2::encoding::locale<
            std::string, tetengo2::detail::stub::encoding
        >
        encoding_type;

    typedef tetengo2::encoder<encoding_type, encoding_type> encoder_type;

    typedef
        tetengo2::gui::traits::menu_traits<
            std::string, encoder_type, tetengo2::gui::menu_observer_set
        >
        menu_traits_type;

    typedef tetengo2::detail::stub::menu menu_details_type;

    typedef
        tetengo2::gui::main_menu<menu_traits_type, menu_details_type>
        main_menu_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(main_menu)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const main_menu_type main_menu;
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const main_menu_type main_menu;

        BOOST_CHECK(
            &main_menu.style() == &menu_details_type::main_menu_style()
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
