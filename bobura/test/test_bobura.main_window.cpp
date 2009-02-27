/*! \file
    \brief Test of class bobura::main_window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <cstddef>
#include <string>

#include <boost/function.hpp>
#include <boost/test/unit_test.hpp>

#include <stub_tetengo2.gui.gui_type_list.h>

#include "bobura.main_window.h"


namespace
{
    // types

    typedef
        stub_tetengo2::gui::gui_type_list<
            std::ptrdiff_t, std::size_t, std::wstring
        >
        gui_type_list_type;

    typedef
        bobura::main_window<gui_type_list_type, boost::function<void ()> >
        main_window_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(main_window)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        const main_window_type main_window;
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
