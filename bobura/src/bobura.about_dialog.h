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

#include "concept_bobura.message.MessageTypeList.h"


namespace bobura
{
    /*!
        \brief The class template for the about dialog.

        \tparam Dialog          A dialog type. It must conform to
                                concept_tetengo2::gui::Dialog<Dialog>.
        \tparam Button          A button type. It must conform to
                                concept_tetengo2::gui::Button<Button>.
        \tparam MessageTypeList A message type. It must conform to
                                concept_bobura::message::MessageTypeList<MessageTypeList>.
    */
    template <typename Dialog, typename Button, typename MessageTypeList>
    class about_dialog : public Dialog
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Button<Button>));
        //BOOST_CONCEPT_ASSERT((
        //    concept_bobura::message::MessageTypeList<MessageTypeList>
        //));


    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;

        //! The abstract window type.
        typedef
            typename dialog_type::abstract_window_type abstract_window_type;

        //! The handle type.
        typedef typename dialog_type::handle_type handle_type;

        //! The canvas type.
        typedef typename dialog_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename dialog_type::alert_type alert_type;

        //! The difference type.
        typedef typename dialog_type::difference_type difference_type;

        //! The size type.
        typedef typename dialog_type::size_type size_type;

        //! The position type.
        typedef typename dialog_type::position_type position_type;

        //! The dimension type.
        typedef typename dialog_type::dimension_type dimension_type;

        //! The string type.
        typedef typename dialog_type::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename dialog_type::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename dialog_type::encode_to_native_type
            encode_to_native_type;

        //! The font type.
        typedef typename dialog_type::font_type font_type;

        //! The child type.
        typedef typename dialog_type::child_type child_type;

        //! The paint observer type.
        typedef typename dialog_type::paint_observer_type paint_observer_type;

        //! The mouse observer type.
        typedef typename dialog_type::mouse_observer_type mouse_observer_type;

        //! The main menu type.
        typedef typename dialog_type::main_menu_type main_menu_type;

        //! The window observer type.
        typedef
            typename dialog_type::window_observer_type window_observer_type;

        //! The message loop type.
        typedef typename dialog_type::message_loop_type message_loop_type;

        //! The quit message loop type.
        typedef
            typename dialog_type::quit_message_loop_type
            quit_message_loop_type;

        //! The button type.
        typedef Button button_type;

        //! The message type list type.
        typedef MessageTypeList message_type_list_type;

        //! The OK button mouse observer type.
        typedef
            typename message_type_list_type::about_dialog_ok_button_mouse_observer_type
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
                    new about_dialog_ok_button_mouse_observer_type()
                )
            );
        }


        // variables

        std::auto_ptr<button_type> m_p_ok_button;


    };


}

#endif
