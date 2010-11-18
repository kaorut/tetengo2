/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2010 kaoru

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
        */
        explicit main_window(const message_catalog_type& message_catalog)
        :
        base_type(),
        m_message_catalog(message_catalog)
        {
            initialize_window(*this);
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

        static void initialize_window(main_window& window)
        {
            set_message_observers(window);
            set_menus(window);

            const message_catalog_type& message_catalog =
                window.m_message_catalog;
            window.set_text(message_catalog.get(TETENGO2_TEXT("Bobura")));
        }

        static void set_message_observers(main_window& window)
        {
            window.window_observer_set().destroyed().connect(
                boost::bind(quit_message_loop_type(), 0)
            );

            window.paint_observer_set().paint().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::paint
                >::type()
            );
        }

        static void set_menus(main_window& window)
        {
            const message_catalog_type& message_catalog =
                window.m_message_catalog;

            std::auto_ptr<main_menu_type> p_main_menu(new main_menu_type());

            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        message_catalog.get(TETENGO2_TEXT("&File"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&New\tCtrl+N")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&Open...\tCtrl+O")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&Save\tCtrl+S")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Save &As...")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("E&xit")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::exit
                    >::type(window)
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }
            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        message_catalog.get(TETENGO2_TEXT("&Edit"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&Undo\tCtrl+Z")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&Redo\tCtrl+Y")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("Cu&t\tCtrl+X")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&Copy\tCtrl+C")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&Paste\tCtrl+V")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&Find...\tCtrl+F")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&Replace...\tCtrl+H")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }
            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        message_catalog.get(TETENGO2_TEXT("&Help"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    message_catalog.get(TETENGO2_TEXT("&About...")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::about
                    >::type(window)
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }

            window.set_main_menu(p_main_menu);
        }

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


    };


}

#endif
