/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

#include <memory>

#include <boost/bind.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.text.h>

#include "bobura.command.type_list.h"
#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Window                    A window type.
        \tparam QuitMessageLoop           A quit-message-loop type.
        \tparam MenuCommand               A menu command type.
        \tparam PopupMenu                 A popup menu type.
        \tparam MenuSeparator             A menu separator type.
        \tparam CommandTypeList           A command type.
        \tparam MainWindowMessageTypeList A message type.
    */
    template <
        typename Window,
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

        //! \return The base type.
        typedef Window base_type;

        //! \return The quit-message-loop type.
        typedef QuitMessageLoop quit_message_loop_type;

        //! \return The menu command type.
        typedef MenuCommand menu_command_type;

        //! \return The popup menu type.
        typedef PopupMenu popup_menu_type;

        //! \return The menu separator type.
        typedef MenuSeparator menu_separator_type;

        //! \return The command type list type.
        typedef CommandTypeList command_type_list_type;

        //! \return The message type list type.
        typedef MainWindowMessageTypeList main_window_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a main window.
        */
        main_window()
        :
        base_type()
        {
            initialize_window(*this);
        }

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        throw ()
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
#if defined(_MSC_VER)
            window.set_text(
                string_type(TETENGO2_TEXT("ぼうぶら テストプログラム"))
            );
#endif
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
            std::auto_ptr<main_menu_type> p_main_menu(new main_menu_type());

#if defined(_MSC_VER)
            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        string_type(TETENGO2_TEXT("ファイル(&F)"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("新規作成(&N)\tCtrl+N")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("開く(&O)...\tCtrl+O")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("上書き保存(&S)\tCtrl+S")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("名前を付けて保存(&A)...")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("終了(&X)")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::exit
                    >::type(window)
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }
            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        string_type(TETENGO2_TEXT("編集(&E)"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("元に戻す(&U)\tCtrl+Z")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("やり直し(&R)\tCtrl+Y")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("切り取り(&T)\tCtrl+X")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("コピー(&C)\tCtrl+C")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("貼り付け(&P)\tCtrl+V")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("検索(&F)...\tCtrl+F")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("置換(&R)...\tCtrl+H")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::nop
                    >::type()
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }
            {
                std::auto_ptr<menu_type> p_popup_menu(
                    new popup_menu_type(
                        string_type(TETENGO2_TEXT("ヘルプ(&H)"))
                    )
                );

                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("バージョン情報(&A)...")),
                    typename boost::mpl::at<
                        command_type_list_type, command::type::about
                    >::type(window)
                );

                p_main_menu->insert(p_main_menu->end(), p_popup_menu);
            }
#endif

            window.set_main_menu(p_main_menu);
        }

        static void append_menu_command(
            menu_type&                              popup_menu,
            const typename menu_type::string_type&  text,
            const command_type&                     command
        )
        {
            std::auto_ptr<menu_type> p_menu_command(
                new menu_command_type(text)
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


    };


}

#endif
