/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Window                    A window type.
        \tparam MessageCatalog            A message catalog type.
        \tparam Settings                  A settings type.
        \tparam ConfirmFileSave           A file save confirmation type.
        \tparam MessageLoopBreak          A message loop break type.
        \tparam MainWindowMessageTypeList A message type.
    */
    template <
        typename Window,
        typename MessageCatalog,
        typename Settings,
        typename ConfirmFileSave,
        typename MessageLoopBreak,
        typename MainWindowMessageTypeList
    >
    class main_window : public Window
    {
    public:
        // types

        //! The base type.
        typedef Window base_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The settings type.
        typedef Settings settings_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;

        //! The message loop break type.
        typedef MessageLoopBreak message_loop_break_type;

        //! The message type list type.
        typedef MainWindowMessageTypeList main_window_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a main window.

            \param message_catalog A message catalog.
            \param settings        Settings.
        */
        main_window(
            const message_catalog_type&   message_catalog,
            const settings_type&          settings,
            const confirm_file_save_type& confirm_file_save
        )
        :
        base_type(),
        m_message_catalog(message_catalog),
        m_settings(settings),
        m_confirm_file_save(confirm_file_save)
        {
            initialize_window();
        }

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Sets a title.

            \param document_name A document name.
            \param changed       A changed status.
        */
        void set_title(
            const boost::optional<string_type>& document_name,
            const bool                          changed
        )
        {
            string_type title =
                document_name ?
                *document_name :
                m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));
            if (changed)
                title += string_type(TETENGO2_TEXT(" *"));
            title += string_type(TETENGO2_TEXT(" - "));
            title += m_message_catalog.get(TETENGO2_TEXT("App:Bobura"));

            set_text(title);
        }


    private:
        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;

        const confirm_file_save_type& m_confirm_file_save;


        // functions

        void initialize_window()
        {
            set_message_observers();

            set_title(boost::none, false);
        }

        void set_message_observers()
        {
            this->window_observer_set().destroyed().connect(
                TETENGO2_CPP11_BIND(message_loop_break_type(), 0)
            );

            this->paint_observer_set().paint().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::paint
                >::type(m_settings.image_directory_path())
            );

            this->window_observer_set().closing().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::window
                >::type(*this, m_confirm_file_save)
            );
        }


    };


}

#endif
