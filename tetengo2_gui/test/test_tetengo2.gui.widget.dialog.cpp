/*! \file
    \brief Test of class tetengo2::gui::widget::dialog.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>


#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using abstract_window_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::abstract_window>::type;

    using window_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type;

    using dialog_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::dialog>::type;

    class concrete_dialog : public dialog_type
    {
    public:
        explicit concrete_dialog(abstract_window_type& parent, const bool file_droppable = false)
        :
        dialog_type(parent, file_droppable)
        {}

    };


}




BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const concrete_dialog dialog(parent, false);
        }
        {
            window_type parent{};
            const concrete_dialog dialog(parent, true);
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const concrete_dialog dialog(parent);

            BOOST_CHECK(dialog.result() == dialog_type::result_type::undecided);
        }
        {
            window_type parent{};
            concrete_dialog dialog(parent);

            dialog.set_result(dialog_type::result_type::undecided);

            BOOST_CHECK(dialog.result() == dialog_type::result_type::undecided);
        }
        {
            window_type parent{};
            concrete_dialog dialog(parent);

            dialog.set_result(dialog_type::result_type::accepted);

            BOOST_CHECK(dialog.result() == dialog_type::result_type::accepted);
        }
        {
            window_type parent{};
            concrete_dialog dialog(parent);

            dialog.set_result(dialog_type::result_type::canceled);

            BOOST_CHECK(dialog.result() == dialog_type::result_type::canceled);
        }
    }

    BOOST_AUTO_TEST_CASE(set_result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            concrete_dialog dialog(parent);

            dialog.set_result(dialog_type::result_type::undecided);
        }
        {
            window_type parent{};
            concrete_dialog dialog(parent);

            dialog.set_result(dialog_type::result_type::accepted);
        }
        {
            window_type parent{};
            concrete_dialog dialog(parent);

            dialog.set_result(dialog_type::result_type::canceled);
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_dialog dialog(parent);

        dialog.do_modal();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
