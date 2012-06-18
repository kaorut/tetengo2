/*! \file
    \brief Test of class bobura::command::command_base.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.command.command_base.h"

namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window>::type abstract_window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    class concrete_command : public bobura::command::command_base<model_type, abstract_window_type>
    {
    private:
        virtual bool enabled_impl()
        const
        {
            return true;
        }

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const
        {}

    };

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(command_base)
    // test cases

    BOOST_AUTO_TEST_CASE(enabled)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_command command;

        command.enabled();
    }

    BOOST_AUTO_TEST_CASE(execute)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_command command;

        model_type model;
        window_type window;
        command.execute(model, window);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
