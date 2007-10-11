/*! \file
    \brief Test of class bobura::bobura.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.stub.gui_factory.h>
#include <tetengo2.gui.stub.message_loop.h>
#include <tetengo2.gui.stub.quit_message_loop.h>

#include "bobura.bobura.h"

#include "test_bobura.bobura.h"


namespace
{
    // types

    typedef tetengo2::gui::stub::gui_factory gui_factory_type;

    typedef
        gui_factory_type::gui_initializer_finalizer_type
        gui_initializer_finalizer_type;

    typedef
        bobura::bobura<
            gui_factory_type,
            tetengo2::gui::stub::message_loop,
            tetengo2::gui::stub::quit_message_loop
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

        p_suite->add(BOOST_TEST_CASE(test_bobura::bobura::construction));
        p_suite->add(BOOST_TEST_CASE(test_bobura::bobura::run));

        return p_suite;
    }

    void bobura::construction()
    {
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
