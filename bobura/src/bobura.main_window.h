/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

//#include <memory>
//#include <utility>

#include <boost/mpl/at.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.command.type_list.h"
#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Window                    A window type.
        \tparam MessageCatalog            A message catalog type.
        \tparam Settings                  A settings type.
        \tparam MessageLoopBreak          A message loop break type.
        \tparam MenuCommand               A menu command type.
        \tparam PopupMenu                 A popup menu type.
        \tparam MenuSeparator             A menu separator type.
        \tparam CommandSet                A command set type.
        \tparam CommandTypeList           A command type.
        \tparam MainWindowMessageTypeList A message type.
    */
    template <
        typename Window,
        typename MessageCatalog,
        typename Settings,
        typename MessageLoopBreak,
        typename MenuCommand,
        typename PopupMenu,
        typename MenuSeparator,
        typename CommandSet,
        typename CommandTypeList,
        typename MainWindowMessageTypeList
    >
    class main_window : public Window
    {
    public:
        // types

        //! The base type.
        typedef Window base_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The settings type.
        typedef Settings settings_type;

        //! The message loop break type.
        typedef MessageLoopBreak message_loop_break_type;

        //! The menu bar type.
        typedef typename base_type::menu_bar_type menu_bar_type;

        //! The menu command type.
        typedef MenuCommand menu_command_type;

        //! The popup menu type.
        typedef PopupMenu popup_menu_type;

        //! The menu separator type.
        typedef MenuSeparator menu_separator_type;

        //! The command set type.
        typedef CommandSet command_set_type;

        //! The command type list type.
        typedef CommandTypeList command_type_list_type;

        //! The message type list type.
        typedef MainWindowMessageTypeList main_window_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a main window.

            \param message_catalog A message catalog.
            \param settings        Settings.
        */
        main_window(
            const message_catalog_type& message_catalog,
            const settings_type&        settings,
            const command_set_type&     command_set
        )
        :
        base_type(),
        m_message_catalog(message_catalog),
        m_settings(settings)
        {
            initialize_window(command_set);
        }

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        //types

        typedef typename menu_bar_type::base_type::base_type menu_base_type;

        typedef typename menu_base_type::shortcut_key_type shortcut_key_type;

        typedef typename shortcut_key_type::virtual_key_type virtual_key_type;

        typedef
            typename menu_base_type::menu_observer_set_type
            menu_observer_set_type;

        typedef typename base_type::string_type string_type;

        typedef
            typename boost::mpl::at<
                command_type_list_type, command::type::command
            >::type
            command_type;


        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


        // functions

        void initialize_window(const command_set_type& command_set)
        {
            set_message_observers();

            set_text(m_message_catalog.get(TETENGO2_TEXT("App:Bobura")));
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
        }


    };


}

#endif
