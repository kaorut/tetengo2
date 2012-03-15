/*! \file
    \brief Test of class bobura::command::exit.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.command.exit.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            bobura::model_type_list, bobura::type::model::model
        >::type
        model_type;

    typedef
        boost::mpl::at<
            bobura::ui_type_list, bobura::type::ui::abstract_window
        >::type
        abstract_window_type;

    typedef
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type
        window_type;

    typedef bobura::command::exit<model_type, abstract_window_type> exit_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(exit)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const exit_type exit = exit_type();

        model_type model;
        window_type window;
        exit(model, window);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
