/*! \file
    \brief The definition of bobura::about_dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_ABOUTDIALOG_H)
#define BOBURA_ABOUTDIALOG_H

#include <memory>
#include <utility>

#include <boost/mpl/at.hpp>

#include <tetengo2.text.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the about dialog.

        \tparam Dialog                     A dialog type.
        \tparam Button                     A button type.
        \tparam AboutDialogMessageTypeList A message type.
    */
    template <
        typename Dialog,
        typename Button,
        typename AboutDialogMessageTypeList
    >
    class about_dialog : public Dialog
    {
    public:
        // types

        //! \return The base type.
        typedef Dialog base_type;

        //! \copydoc tetengo2::gui::win32::widget::handle_type
        typedef typename base_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::widget::canvas_type
        typedef typename base_type::canvas_type canvas_type;

        //! \copydoc tetengo2::gui::win32::widget::alert_type
        typedef typename base_type::alert_type alert_type;

        //! \copydoc tetengo2::gui::win32::widget::difference_type
        typedef typename base_type::difference_type difference_type;

        //! \copydoc tetengo2::gui::win32::widget::size_type
        typedef typename base_type::size_type size_type;

        //! \copydoc tetengo2::gui::win32::widget::position_type
        typedef typename base_type::position_type position_type;

        //! \copydoc tetengo2::gui::win32::widget::dimension_type
        typedef typename base_type::dimension_type dimension_type;

        //! \copydoc tetengo2::gui::win32::widget::string_type
        typedef typename base_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::widget::encoder_type
        typedef typename base_type::encoder_type encoder_type;

        //! \copydoc tetengo2::gui::win32::widget::font_type
        typedef typename base_type::font_type font_type;

        //! \copydoc tetengo2::gui::win32::widget::child_type
        typedef typename base_type::child_type child_type;

        //! \copydoc tetengo2::gui::win32::widget::paint_observer_type
        typedef typename base_type::paint_observer_type paint_observer_type;

        //! \copydoc tetengo2::gui::win32::widget::mouse_observer_type
        typedef typename base_type::mouse_observer_type mouse_observer_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::main_menu_type.
        typedef typename base_type::main_menu_type main_menu_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::window_observer_type.
        typedef typename base_type::window_observer_type window_observer_type;

        //! \copydoc tetengo2::gui::win32::dialog::message_loop_type
        typedef typename base_type::message_loop_type message_loop_type;

        //! \copydoc tetengo2::gui::win32::dialog::quit_message_loop_type
        typedef
            typename base_type::quit_message_loop_type
            quit_message_loop_type;

        //! \return The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! \return The button type.
        typedef Button button_type;

        //! \return The message type list type.
        typedef
            AboutDialogMessageTypeList about_dialog_message_type_list_type;

        //! \return The OK button mouse observer type.
        typedef
            typename boost::mpl::at<
                about_dialog_message_type_list_type,
                message::about_dialog::type::ok_button_mouse_observer
            >::type
            about_dialog_ok_button_mouse_observer_type;


        // constructors and destructor

        /*!
            \brief Creates an about dialog.

            \param parent A parent window.
        */
        explicit about_dialog(abstract_window_type& parent)
        :
        base_type(parent),
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
            dialog.m_p_ok_button->set_text(string_type(TETENGO2_TEXT("OK")));
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
