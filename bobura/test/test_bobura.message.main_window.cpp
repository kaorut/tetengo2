/*! \file
    \brief Test of class bobura::message::main_window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"

#include "bobura.message.main_window.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(main_window)
BOOST_AUTO_TEST_SUITE(menu)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        typedef
            boost::mpl::at<
                command_type_list_type, bobura::command::type::nop
            >::type
            command_type;

        const command_type command = command_type();
        const bobura::message::main_window::menu<command_type> menu(command);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        typedef
            boost::mpl::at<
                command_type_list_type, bobura::command::type::nop
            >::type
            command_type;

        const command_type command = command_type();
        const bobura::message::main_window::menu<command_type> menu(command);

        menu();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(paint)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::main_window::paint<
            canvas_type, position_type, picture_reader_type
        > paint(boost::filesystem::path("image_path"));
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::main_window::paint<
            canvas_type, position_type, picture_reader_type
        > paint(boost::filesystem::path("image_path"));

        const window_type window;
        tetengo2::cpp0x::unique_ptr<canvas_type>::type p_canvas(
            window.create_canvas()
        );
        paint(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
