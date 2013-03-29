/*! \file
    \brief Test of class bobura::message::train_kind_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.utility.h>

#include "bobura.type_list.h"

#include "bobura.message.train_kind_dialog.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::size>::type size_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::list_box>::type list_box_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dialog>::type dialog_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef window_type::dimension_type dimension_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef canvas_type::font_type font_type;

    typedef canvas_type::color_type color_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;

    struct info_set_type
    {
        typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

        typedef model_type::timetable_type::train_kind_type train_kind_type;

        info_set_type()
        {}

        info_set_type(
            boost::optional<size_type> original_index,
            const bool                 referred,
            train_kind_type            train_kind
        )
        {
            tetengo2::suppress_unused_variable_warning(original_index, referred, train_kind);
        }

        const boost::optional<size_type>& original_index()
        const
        {
            static const boost::optional<size_type> singleton;
            return singleton;
        }

        bool referred()
        const
        {
            return false;
        }

        const train_kind_type& train_kind()
        const
        {
            static const train_kind_type singleton(
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("abbreviation")),
                color_type(0x12, 0x34, 0x56),
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid
            );
            return singleton;
        }

        train_kind_type& train_kind()
        {
            static train_kind_type singleton(
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("abbreviation")),
                color_type(0x12, 0x34, 0x56),
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid
            );
            return singleton;
        }

    };


    typedef
        boost::mpl::at<bobura::common_dialog_type_list, bobura::type::common_dialog::color>::type color_dialog_type;

    class concrete_dialog : public dialog_type
    {
    public:
        explicit concrete_dialog(window_type::base_type& parent)
        :
        dialog_type(parent)
        {}

    };


    // functions

    void sync_function()
    {}

    void update_function()
    {}

    void apply_function()
    {}


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(train_kind_dialog)
BOOST_AUTO_TEST_SUITE(train_kind_list_box_selection_changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        boost::optional<size_type> current_train_kind_index;
        window_type window;
        list_box_type list_box(window, list_box_type::scroll_bar_style_type::none);
        const bobura::message::train_kind_dialog::train_kind_list_box_selection_changed<size_type, list_box_type>
        observer(current_train_kind_index, list_box, update_function);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        boost::optional<size_type> current_train_kind_index;
        window_type window;
        list_box_type list_box(window, list_box_type::scroll_bar_style_type::none);
        const bobura::message::train_kind_dialog::train_kind_list_box_selection_changed<size_type, list_box_type>
        observer(current_train_kind_index, list_box, update_function);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(add_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<info_set_type> info_sets(3, info_set_type());
        const boost::optional<size_type> current_train_kind_index(1);
        const message_catalog_type message_catalog;
        const bobura::message::train_kind_dialog::add_button_mouse_clicked<
            info_set_type, size_type, message_catalog_type
        > observer(info_sets, current_train_kind_index, sync_function, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<info_set_type> info_sets(3, info_set_type());
        const boost::optional<size_type> current_train_kind_index(1);
        const message_catalog_type message_catalog;
        const bobura::message::train_kind_dialog::add_button_mouse_clicked<
            info_set_type, size_type, message_catalog_type
        > observer(info_sets, current_train_kind_index, sync_function, message_catalog);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(delete_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<info_set_type> info_sets(3, info_set_type());
        boost::optional<size_type> current_train_kind_index(1);
        const bobura::message::train_kind_dialog::delete_button_mouse_clicked<info_set_type, size_type> observer(
            info_sets, current_train_kind_index, sync_function
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<info_set_type> info_sets(3, info_set_type());
        boost::optional<size_type> current_train_kind_index(1);
        const bobura::message::train_kind_dialog::delete_button_mouse_clicked<info_set_type, size_type> observer(
            info_sets, current_train_kind_index, sync_function
        );

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(up_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<info_set_type> info_sets(3, info_set_type());
        boost::optional<size_type> current_train_kind_index(1);
        const bobura::message::train_kind_dialog::up_button_mouse_clicked<info_set_type, size_type> observer(
            info_sets, current_train_kind_index, sync_function
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<info_set_type> info_sets(3, info_set_type());
        boost::optional<size_type> current_train_kind_index(1);
        const bobura::message::train_kind_dialog::up_button_mouse_clicked<info_set_type, size_type> observer(
            info_sets, current_train_kind_index, sync_function
        );

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(down_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<info_set_type> info_sets(3, info_set_type());
        boost::optional<size_type> current_train_kind_index(1);
        const bobura::message::train_kind_dialog::down_button_mouse_clicked<info_set_type, size_type> observer(
            info_sets, current_train_kind_index, sync_function
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<info_set_type> info_sets(3, info_set_type());
        boost::optional<size_type> current_train_kind_index(1);
        const bobura::message::train_kind_dialog::down_button_mouse_clicked<info_set_type, size_type> observer(
            info_sets, current_train_kind_index, sync_function
        );

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(name_text_box_changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::name_text_box_changed observer(apply_function);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::name_text_box_changed observer(apply_function);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(abbreviation_text_box_changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::abbreviation_text_box_changed observer(apply_function);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::abbreviation_text_box_changed observer(apply_function);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(color_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        concrete_dialog dialog(window);
        color_type color(0x12, 0x34, 0x56);
        const bobura::message::train_kind_dialog::color_button_mouse_clicked<dialog_type, color_dialog_type> observer(
            dialog, color, apply_function
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        concrete_dialog dialog(window);
        color_type color(0x12, 0x34, 0x56);
        const bobura::message::train_kind_dialog::color_button_mouse_clicked<dialog_type, color_dialog_type> observer(
            dialog, color, apply_function
        );

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(weight_dropdown_box_selection_changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::weight_dropdown_box_selection_changed observer(apply_function);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::abbreviation_text_box_changed observer(apply_function);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(line_style_dropdown_box_selection_changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::line_style_dropdown_box_selection_changed observer(apply_function);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::line_style_dropdown_box_selection_changed observer(apply_function);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(sample_picture_box_paint)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::sample_picture_box_paint<info_set_type, size_type, canvas_type>
        observer(
            std::vector<info_set_type>(),
            boost::none,
            font_type::dialog_font(),
            color_type(0x12, 0x34, 0x56),
            dimension_type(width_type(42), height_type(24))
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::train_kind_dialog::sample_picture_box_paint<info_set_type, size_type, canvas_type>
        observer(
            std::vector<info_set_type>(),
            boost::none,
            font_type::dialog_font(),
            color_type(0x12, 0x34, 0x56),
            dimension_type(width_type(42), height_type(24))
        );

        window_type window;
        const auto p_canvas = window.create_canvas();
        observer(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(ok_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_dialog dialog(parent);
        const bobura::message::train_kind_dialog::ok_button_mouse_clicked<dialog_type> observer(dialog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_dialog dialog(parent);
        const bobura::message::train_kind_dialog::ok_button_mouse_clicked<dialog_type> observer(dialog);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(cancel_button_mouse_clicked)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_dialog dialog(parent);
        const bobura::message::train_kind_dialog::cancel_button_mouse_clicked<dialog_type> observer(dialog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_dialog dialog(parent);
        const bobura::message::train_kind_dialog::cancel_button_mouse_clicked<dialog_type> observer(dialog);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
