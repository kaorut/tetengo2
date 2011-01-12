/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

#include <memory>
#include <utility>

#include <boost/bind.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.cpp0x_keyword.h>
#include <tetengo2.text.h>

#include "bobura.command.type_list.h"
#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Window                    A window type.
        \tparam MessageCatalog            A message catalog type.
        \tparam Settings                  A settings type.
        \tparam QuitMessageLoop           A quit-message-loop type.
        \tparam MenuCommand               A menu command type.
        \tparam PopupMenu                 A popup menu type.
        \tparam MenuSeparator             A menu separator type.
        \tparam CommandTypeList           A command type.
        \tparam MainWindowMessageTypeList A message type.
    */
    template <
        typename Window,
        typename MessageCatalog,
        typename Settings,
        typename QuitMessageLoop,
        typename MenuCommand,
        typename PopupMenu,
        typename MenuSeparator,
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

        //! The quit-message-loop type.
        typedef QuitMessageLoop quit_message_loop_type;

        //! The menu command type.
        typedef MenuCommand menu_command_type;

        //! The popup menu type.
        typedef PopupMenu popup_menu_type;

        //! The menu separator type.
        typedef MenuSeparator menu_separator_type;

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
            const settings_type&        settings
        )
        :
        base_type(),
        m_message_catalog(message_catalog),
        m_settings(settings)
        {
            initialize_window();
        }

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        TETENGO2_NOEXCEPT
        {}


    private:
        //types

        typedef typename base_type::main_menu_type main_menu_type;

        typedef typename main_menu_type::base_type::base_type menu_type;

        typedef
            typename menu_type::menu_observer_set_type menu_observer_set_type;

        typedef typename base_type::string_type string_type;

        typedef
            typename boost::mpl::at<
                command_type_list_type, command::type::command
            >::type
            command_type;


        // static functions

        static void append_menu_command(
            menu_type&                        popup_menu,
            typename menu_type::string_type&& text,
            const command_type&               command
        )
        {
            std::auto_ptr<menu_type> p_menu_command(
                new menu_command_type(
                    std::forward<typename menu_type::string_type>(text)
                )
            );

            p_menu_command->menu_observer_set().selected().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::menu
                >::type(command)
            );

            popup_menu.insert(popup_menu.end(), p_menu_command);
        }

        static void append_menu_separator(menu_type& popup_menu)
        {
            std::auto_ptr<menu_type> p_menu_separator(
                new menu_separator_type()
            );
            popup_menu.insert(popup_menu.end(), p_menu_separator);
        }


        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


        // functions

        void initialize_window()
        {
            set_message_observers();
            set_menus();

            set_text(m_message_catalog.get(TETENGO2_TEXT("Bobura")));
        }

        void set_message_observers()
        {
            this->window_observer_set().destroyed().connect(
                boost::bind(quit_message_loop_type(), 0)
            );

            this->paint_observer_set().paint().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::paint
                >::type(m_settings.image_directory_path())
            );
        }

        void set_menus()
        {
            std::auto_ptr<main_menu_type> p_main_menu(new main_menu_type());

            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        m_message_catalog.get(TETENGO2_TEXT("&File"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&New\tCtrl+N")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&Open...\tCtrl+O")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&Save\tCtrl+S")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("Save &As...")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("E&xit")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::exit
                    >::type(*this)
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }
            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        m_message_catalog.get(TETENGO2_TEXT("&Edit"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&Undo\tCtrl+Z")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&Redo\tCtrl+Y")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("Cu&t\tCtrl+X")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&Copy\tCtrl+C")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&Paste\tCtrl+V")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&Find...\tCtrl+F")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(
                        TETENGO2_TEXT("&Replace...\tCtrl+H")
                    ),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }
            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        m_message_catalog.get(TETENGO2_TEXT("&Help"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("&About...")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::about
                    >::type(*this, m_message_catalog, m_settings)
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }

            this->set_main_menu(p_main_menu);
        }


    };


}

#endif
