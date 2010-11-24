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
#include <boost/scoped_ptr.hpp>

#include <tetengo2.cpp0x_keyword.h>
#include <tetengo2.text.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the about dialog.

        \tparam Dialog                     A dialog type.
        \tparam MessageCatalog             A message catalog type.
        \tparam Button                     A button type.
        \tparam AboutDialogMessageTypeList A message type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
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

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The button type.
        typedef Button button_type;

        //! The message type list type.
        typedef
            AboutDialogMessageTypeList about_dialog_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates an about dialog.

            \param parent A parent window.
            \param message_catalog A message catalog.
        */
        about_dialog(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog
        )
        :
        base_type(parent),
        m_message_catalog(message_catalog),
        m_p_ok_button()
        {
            initialize_dialog(parent);
        }

        /*!
            \brief Destroys the about dialog.
        */
        virtual ~about_dialog()
        TETENGO2_NOEXCEPT
        {}


    private:
        // variables

        const message_catalog_type& m_message_catalog;

        boost::scoped_ptr<button_type> m_p_ok_button;


        // functions

        void initialize_dialog(const abstract_window_type& parent)
        {
            const typename about_dialog::position_type& parent_position =
                parent.position();
            set_client_dimension(std::make_pair(384, 256));
            set_position(
                std::make_pair(
                    parent_position.first + 64, parent_position.second + 64
                )
            );

            m_p_ok_button.reset(create_ok_button().release());
        }

        std::auto_ptr<button_type> create_ok_button()
        {
            std::auto_ptr<button_type> p_button(
                new button_type(*this, button_type::style_default)
            );

            p_button->set_text(
                typename about_dialog::string_type(TETENGO2_TEXT("OK"))
            );
            p_button->set_dimension(std::make_pair(88, 24));
            p_button->set_position(std::make_pair(280, 216));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    about_dialog_message_type_list_type,
                    message::about_dialog::type::ok_button_mouse
                >::type(*this)
            );

            return p_button;
        }


    };


}

#endif
