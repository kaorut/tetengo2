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
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        //types

        typedef typename base_type::menu_bar_type menu_bar_type;

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


        // static functions

        static void append_menu_command(
            menu_base_type&                        popup_menu,
            typename menu_base_type::string_type&& text,
            command_type&&                         command
        )
        {
            std::unique_ptr<menu_base_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(
                    std::forward<typename menu_base_type::string_type>(text)
                )
            );

            p_menu_command->menu_observer_set().selected().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::menu
                >::type(std::forward<command_type>(command))
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
        }

        static void append_menu_command(
            menu_base_type&                        popup_menu,
            typename menu_base_type::string_type&& text,
            command_type&&                         command,
            shortcut_key_type&&                    shortcut_key
        )
        {
            std::unique_ptr<menu_base_type> p_menu_command(
                tetengo2::make_unique<menu_command_type>(
                    std::forward<typename menu_base_type::string_type>(text),
                    std::forward<shortcut_key_type>(shortcut_key)
                )
            );

            p_menu_command->menu_observer_set().selected().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::menu
                >::type(std::forward<command_type>(command))
            );

            popup_menu.insert(popup_menu.end(), std::move(p_menu_command));
        }

        static void append_menu_separator(menu_base_type& popup_menu)
        {
            std::unique_ptr<menu_base_type> p_menu_separator(
                tetengo2::make_unique<menu_separator_type>()
            );
            popup_menu.insert(popup_menu.end(), std::move(p_menu_separator));
        }


        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


        // functions

        void initialize_window()
        {
            set_message_observers();
            set_menus();

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

        void set_menus()
        {
            std::unique_ptr<menu_bar_type> p_menu_bar(
                tetengo2::make_unique<menu_bar_type>()
            );

            {
                std::unique_ptr<menu_base_type> p_popup_menu(
                    tetengo2::make_unique<popup_menu_type>(
                        m_message_catalog.get(TETENGO2_TEXT("Menu:&File"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("Menu:File:&New")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type(),
                    shortcut_key_type(
                        virtual_key_type::char_n(), false, true, false
                    )
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(
                        TETENGO2_TEXT("Menu:File:&Open...")
                    ),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::load_from_file
                    >::type(*this, m_message_catalog),
                    shortcut_key_type(
                        virtual_key_type::char_o(), false, true, false
                    )
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("Menu:File:&Save")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type(),
                    shortcut_key_type(
                        virtual_key_type::char_s(), false, true, false
                    )
                );
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(
                        TETENGO2_TEXT("Menu:File:Save &As...")
                    ),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(TETENGO2_TEXT("Menu:File:E&xit")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::exit
                    >::type(*this)
                );

                p_menu_bar->insert(
                    p_menu_bar->end(), std::move(p_popup_menu)
                );
            }
            {
                std::unique_ptr<menu_base_type>
                p_popup_menu(
                    tetengo2::make_unique<popup_menu_type>(
                        m_message_catalog.get(TETENGO2_TEXT("Menu:&Help"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    m_message_catalog.get(
                        TETENGO2_TEXT("Menu:Help:&About")
                    ),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::about
                    >::type(*this, m_message_catalog, m_settings)
                );

                p_menu_bar->insert(
                    p_menu_bar->end(), std::move(p_popup_menu)
                );
            }

            this->set_menu_bar(std::move(p_menu_bar));
        }


    };


}

#endif
