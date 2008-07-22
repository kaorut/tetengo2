/*! \file
    \brief Test of namespace tetengo2::gui::win32.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_tetengo2.gui.win32.h"
#include "test_tetengo2.gui.win32.alert.h"
#include "test_tetengo2.gui.win32.canvas.h"
#include "test_tetengo2.gui.win32.gui_factory.h"
#include "test_tetengo2.gui.win32.gui_initializer_finalizer.h"
#include "test_tetengo2.gui.win32.message_loop.h"
#include "test_tetengo2.gui.win32.quit_message_loop.h"
#include "test_tetengo2.gui.win32.widget.h"
#include "test_tetengo2.gui.win32.window.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32");

        p_suite->add(alert::suite());
        p_suite->add(canvas::suite());
        p_suite->add(gui_factory::suite());
        p_suite->add(gui_initializer_finalizer::suite());
        p_suite->add(message_loop::suite());
        p_suite->add(quit_message_loop::suite());
        p_suite->add(widget::suite());
        p_suite->add(window::suite());

        return p_suite;
    }


}}}
