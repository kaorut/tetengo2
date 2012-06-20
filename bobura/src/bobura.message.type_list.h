/*! \file
    \brief The definition of bobura::message::type.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELIST_H)
#define BOBURA_MESSAGE_TYPELIST_H


namespace bobura { namespace message
{
    namespace timetable_model
    {
        namespace type
        {
            //! The reset observer type.
            struct reset;

            //! The changed observer type.
            struct changed;

        }
    }

    namespace main_window
    {
        namespace type
        {
            //! The popup menu selection observer type.
            struct popup_menu_selected;

            //! The menu command selection observer type.
            struct menu_command_selected;

            //! The window resized observer type.
            struct window_resized;

            //! The window closing observer type.
            struct window_closing;

        }
    }

    namespace diagram_picture_box
    {
        namespace type
        {
            //! The mouse observer type.
            struct mouse_wheeled;

            //! The keyboard key down observer type.
            struct keyboard_key_down;

            //! The paint observer type.
            struct paint_paint;

            //! The scroll bar observer type.
            struct scroll_bar_scrolled;

        }
    }

    namespace file_property_dialog
    {
        namespace type
        {
            //! The OK button mouse click observer type.
            struct ok_button_mouse_clicked;

            //! The cancel button mouse click observer type.
            struct cancel_button_mouse_clicked;

        }
    }

    namespace about_dialog
    {
        namespace type
        {
            //! The OK button mouse click observer type.
            struct ok_button_mouse_clicked;

        }
    }


}}


#endif
