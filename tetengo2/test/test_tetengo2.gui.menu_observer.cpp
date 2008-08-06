/*! \file
    \brief Test of class tetengo2::gui::menu_observer.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.menu_observer.h"

#include "test_tetengo2.gui.menu_observer.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* menu_observer::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::menu_observer");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(selected));

        return p_suite;
    }

    void menu_observer::construction()
    {
        BOOST_CHECKPOINT("");

        tetengo2::gui::menu_observer();
    }

    void menu_observer::selected()
    {
        BOOST_CHECKPOINT("");

        tetengo2::gui::menu_observer menu_observer;

        menu_observer.selected();
    }


}}
