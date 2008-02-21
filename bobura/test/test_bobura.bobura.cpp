/*! \file
    \brief Test of class bobura::bobura.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include <memory>

//#include <boost/test/unit_test.hpp>

#include "bobura.bobura.h"

#include <stub_tetengo2.gui.gui_factory.h>
#include <stub_tetengo2.gui.message_loop.h>
#include <stub_tetengo2.gui.quit_message_loop.h>

#include "test_bobura.bobura.h"


namespace
{
    // types

    typedef stub_tetengo2::gui::gui_factory gui_factory_type;

    typedef
        gui_factory_type::gui_initializer_finalizer_type
        gui_initializer_finalizer_type;

    typedef
        bobura::bobura<
            gui_factory_type,
            stub_tetengo2::gui::message_loop,
            stub_tetengo2::gui::quit_message_loop
        >
        bobura_type;

}

namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* bobura::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::bobura");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(run));

        return p_suite;
    }

    void bobura::construction()
    {
        BOOST_CHECKPOINT("");

        const bobura_type bobura(
            std::auto_ptr<const gui_factory_type>(
                new gui_factory_type(
                    std::auto_ptr<const gui_initializer_finalizer_type>(
                        new gui_initializer_finalizer_type()
                    )
                )
            )
        );
    }

    void bobura::run()
    {
        BOOST_CHECKPOINT("");

        const bobura_type bobura(
            std::auto_ptr<const gui_factory_type>(
                new gui_factory_type(
                    std::auto_ptr<const gui_initializer_finalizer_type>(
                        new gui_initializer_finalizer_type()
                    )
                )
            )
        );

        BOOST_CHECK_EQUAL(bobura.run(), 0);
    }

}
