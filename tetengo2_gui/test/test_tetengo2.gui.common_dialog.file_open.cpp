/*! \file
    \brief Test of class tetengo2::gui::common_dialog::file_open.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.common_dialog.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.cursor.system.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.transparent_background.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.message.focus_observer_set.h"
#include "tetengo2.gui.message.keyboard_observer_set.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.message.mouse_observer_set.h"
#include "tetengo2.gui.message.paint_observer_set.h"
#include "tetengo2.gui.message.window_observer_set.h"
#include "tetengo2.gui.menu.menu_bar.h"
#include "tetengo2.gui.menu.menu_base.h"
#include "tetengo2.gui.menu.shortcut_key.h"
#include "tetengo2.gui.menu.shortcut_key_table.h"
#include "tetengo2.gui.menu.traits.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.gui.widget.abstract_window.h"
#include "tetengo2.gui.widget.window.h"
#include "tetengo2.gui.widget.traits.widget_traits.h"
#include "tetengo2.gui.widget.traits.abstract_window_traits.h"
#include "tetengo2.gui.widget.traits.window_traits.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"


#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::window
        >::type
        window_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::common_dialog_type_list,
            test_tetengo2::gui::type::common_dialog::file_open
        >::type
        file_open_dialog_type;


    // functions

    file_open_dialog_type::file_filters_type make_file_filters()
    {
        file_open_dialog_type::file_filters_type filters;

        filters.push_back(std::make_pair("All Files", "*.*"));

        return filters;
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(file_open)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_open_dialog_type file_open(
                std::string(), make_file_filters(), parent
            );
        }
        {
            window_type parent;
            const file_open_dialog_type file_open(
                "hoge", file_open_dialog_type::file_filters_type(), parent
            );
        }
        {
            window_type parent;
            const file_open_dialog_type file_open(
                "hoge", make_file_filters(), parent
            );
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_open_dialog_type file_open(
                L"hoge", make_file_filters(), parent
            );

            BOOST_CHECK(file_open.result().empty());
        }
        {
            window_type parent;
            file_open_dialog_type file_open(
                L"hoge", make_file_filters(), parent
            );

            file_open.do_modal();

            BOOST_CHECK(!file_open.result().empty());
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        file_open_dialog_type file_open(L"hoge", make_file_filters(), parent);

        file_open.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_open_dialog_type file_open(
                L"hoge", make_file_filters(), parent
            );

            file_open.details();
        }
        {
            window_type parent;
            file_open_dialog_type file_open(
                L"hoge", make_file_filters(), parent
            );

            file_open.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
