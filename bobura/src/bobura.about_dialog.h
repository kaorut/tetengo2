/*! \file
    \brief The definition of bobura::about_dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_ABOUTDIALOG_H)
#define BOBURA_ABOUTDIALOG_H

//#include <memory>
//#include <utility>

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.Dialog.h>
#include <concept_tetengo2.gui.Button.h>

#include "concept_bobura.message.MessageTypeLists.h"


namespace bobura
{
    /*!
        \brief The class template for the about dialog.

        \tparam Dialog                     A dialog type. It must conform to
                                           concept_tetengo2::gui::Dialog<Dialog>.
        \tparam Button                     A button type. It must conform to
                                           concept_tetengo2::gui::Button<Button>.
        \tparam AboutDialogMessageTypeList A message type. It must conform to
                                           concept_bobura::message::AboutDialogMessageTypeList<AboutDialogMessageTypeList>.
    */
    template <
        typename Dialog,
        typename Button,
        typename AboutDialogMessageTypeList
    >
    class about_dialog : public Dialog
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Button<Button>));
        BOOST_CONCEPT_ASSERT((
            concept_bobura::message::AboutDialogMessageTypeList<
                AboutDialogMessageTypeList
            >
        ));


    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;

        //! The abstract window type.
        typedef
            typename dialog_type::abstract_window_type abstract_window_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::widget_type.
        typedef typename abstract_window_type::widget_type widget_type;

        //! \copydoc tetengo2::gui::win32::widget::handle_type
        typedef typename widget_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::widget::canvas_type
        typedef typename widget_type::canvas_type canvas_type;

        //! \copydoc tetengo2::gui::win32::widget::alert_type
        typedef typename widget_type::alert_type alert_type;

        //! \copydoc tetengo2::gui::win32::widget::difference_type
        typedef typename widget_type::difference_type difference_type;

        //! \copydoc tetengo2::gui::win32::widget::size_type
        typedef typename widget_type::size_type size_type;

        //! \copydoc tetengo2::gui::win32::widget::position_type
        typedef typename widget_type::position_type position_type;

        //! \copydoc tetengo2::gui::win32::widget::dimension_type
        typedef typename widget_type::dimension_type dimension_type;

        //! \copydoc tetengo2::gui::win32::widget::string_type
        typedef typename widget_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::widget::encode_from_native_type
        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        //! \copydoc tetengo2::gui::win32::widget::encode_to_native_type
        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        //! \copydoc tetengo2::gui::win32::widget::font_type
        typedef typename widget_type::font_type font_type;

        //! \copydoc tetengo2::gui::win32::widget::child_type
        typedef typename widget_type::child_type child_type;

        //! \copydoc tetengo2::gui::win32::widget::paint_observer_type
        typedef typename widget_type::paint_observer_type paint_observer_type;

        //! \copydoc tetengo2::gui::win32::widget::mouse_observer_type
        typedef typename widget_type::mouse_observer_type mouse_observer_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::main_menu_type.
        typedef typename abstract_window_type::main_menu_type main_menu_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::window_observer_type.
        typedef
            typename abstract_window_type::window_observer_type
            window_observer_type;

        //! \copydoc tetengo2::gui::win32::dialog::message_loop_type
        typedef typename dialog_type::message_loop_type message_loop_type;

        //! \copydoc tetengo2::gui::win32::dialog::quit_message_loop_type
        typedef
            typename dialog_type::quit_message_loop_type
            quit_message_loop_type;

        //! The button type.
        typedef Button button_type;

        //! The message type list type.
        typedef
            AboutDialogMessageTypeList about_dialog_message_type_list_type;

        //! The OK button mouse observer type.
        typedef
            typename about_dialog_message_type_list_type::about_dialog_ok_button_mouse_observer_type
            about_dialog_ok_button_mouse_observer_type;


        // constructors and destructor

        /*!
            \brief Creates an about dialog.

            \param parent A parent window.
        */
        explicit about_dialog(abstract_window_type& parent)
        :
        dialog_type(parent),
        m_p_ok_button()
        {
            initialize_dialog(*this, parent);
        }

        /*!
            \brief Destroys the about dialog.
        */
        virtual ~about_dialog()
        throw ()
        {}


    private:
        // static functions

        static void initialize_dialog(
            about_dialog&               dialog,
            const abstract_window_type& parent
        )
        {
            const position_type& parent_position = parent.position();
            dialog.set_client_dimension(std::make_pair(384, 256));
            dialog.set_position(
                std::make_pair(
                    parent_position.first + 64, parent_position.second + 64
                )
            );

            dialog.m_p_ok_button.reset(
                new button_type(dialog, button_type::style_default)
            );
            dialog.m_p_ok_button->set_text(L"OK");
            dialog.m_p_ok_button->set_dimension(std::make_pair(88, 24));
            dialog.m_p_ok_button->set_position(std::make_pair(280, 216));
            dialog.m_p_ok_button->add_mouse_observer(
                std::auto_ptr<mouse_observer_type>(
                    new about_dialog_ok_button_mouse_observer_type(&dialog)
                )
            );
        }


        // variables

        std::auto_ptr<button_type> m_p_ok_button;


    };


}

#endif
