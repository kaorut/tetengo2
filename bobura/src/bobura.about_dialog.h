/*! \file
    \brief The definition of bobura::about_dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_ABOUTDIALOG_H)
#define BOBURA_ABOUTDIALOG_H

#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/scoped_ptr.hpp>

#include <tetengo2.cpp0x_keyword.h>
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

        //! The base type.
        typedef Dialog base_type;

        //! The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! The button type.
        typedef Button button_type;

        //! The message type list type.
        typedef
            AboutDialogMessageTypeList about_dialog_message_type_list_type;


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
        TETENGO2_NOEXCEPT
        {}


    private:
        // static functions

        static void initialize_dialog(
            about_dialog&               dialog,
            const abstract_window_type& parent
        )
        {
            const typename about_dialog::position_type& parent_position =
                parent.position();
            dialog.set_client_dimension(std::make_pair(384, 256));
            dialog.set_position(
                std::make_pair(
                    parent_position.first + 64, parent_position.second + 64
                )
            );

            dialog.m_p_ok_button.reset(
                new button_type(dialog, button_type::style_default)
            );
            dialog.m_p_ok_button->set_text(
                typename about_dialog::string_type(TETENGO2_TEXT("OK"))
            );
            dialog.m_p_ok_button->set_dimension(std::make_pair(88, 24));
            dialog.m_p_ok_button->set_position(std::make_pair(280, 216));
            dialog.m_p_ok_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    about_dialog_message_type_list_type,
                    message::about_dialog::type::ok_button_mouse
                >::type(dialog)
            );
        }


        // variables

        boost::scoped_ptr<button_type> m_p_ok_button;


    };


}

#endif
