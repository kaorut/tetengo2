/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

#include <memory>

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.Menu.h>
#include <concept_tetengo2.gui.Window.h>
#include <tetengo2.text.h>

#include "concept_bobura.command.CommandTypeList.h"
#include "concept_bobura.message.MessageTypeLists.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Window                    A window type. It must conform to
                                          concept_tetengo2::gui::Window<Window>.
        \tparam QuitMessageLoop           A quit-message-loop type. It must
                                          conform to
                                          boost::UnaryFunction<MessageLoop, void, int>.
        \tparam MenuCommand               A menu command type. It must conform
                                          to
                                          concept_tetengo2::gui::Menu<MenuCommand, typename MenuCommand::base_type>.
        \tparam PopupMenu                 A popup menu type. It must conform
                                          to
                                          concept_tetengo2::gui::Menu<PopupMenu, typename PopupMenu::base_type::base_type>.
        \tparam MenuSeparator             A menu separator type. It must
                                          conform to
                                          concept_tetengo2::gui::Menu<MenuSeparator, typename MenuSeparator::base_type>.
        \tparam CommandTypeList           A command type. It must conform to
                                          concept_bobura::command::CommandTypeList<CommandTypeList>.
        \tparam MainWindowMessageTypeList A message type. It must conform to
                                          concept_bobura::message::MainWindowMessageTypeList<MainWindowMessageTypeList>.
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
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::Window<Window>
        ));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::Menu<
                MenuCommand, typename MenuCommand::base_type
            >
        ));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::Menu<
                PopupMenu, typename PopupMenu::base_type::base_type
            >
        ));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::Menu<
                MenuSeparator, typename MenuSeparator::base_type
            >
        ));
        BOOST_CONCEPT_ASSERT((
            concept_bobura::command::CommandTypeList<CommandTypeList>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_bobura::message::MainWindowMessageTypeList<
                MainWindowMessageTypeList
            >
        ));


    public:
        // types

        //! \return The base type.
        typedef Window base_type;

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

        typedef typename main_menu_type::base_type::base_type menu_type;

        typedef typename menu_type::menu_observer_type menu_observer_type;

        typedef typename command_type_list_type::command_type command_type;


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
            window.add_window_observer(
                std::auto_ptr<window_observer_type>(
                    new typename main_window_message_type_list_type::main_window_window_observer_type(
                        quit_message_loop_type()
                    )
                )
            );

            window.add_paint_observer(
                std::auto_ptr<paint_observer_type>(
                    new typename main_window_message_type_list_type::main_window_paint_observer_type()
                )
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
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("開く(&O)...\tCtrl+O")),
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("上書き保存(&S)\tCtrl+S")),
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("名前を付けて保存(&A)...")),
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("終了(&X)")),
                    typename command_type_list_type::exit_type(window)
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
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("やり直し(&R)\tCtrl+Y")),
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("切り取り(&T)\tCtrl+X")),
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("コピー(&C)\tCtrl+C")),
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("貼り付け(&P)\tCtrl+V")),
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("検索(&F)...\tCtrl+F")),
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    string_type(TETENGO2_TEXT("置換(&R)...\tCtrl+H")),
                    typename command_type_list_type::nop_type()
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
                    typename command_type_list_type::about_type(window)
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

            std::auto_ptr<menu_observer_type> p_menu_observer(
                new typename main_window_message_type_list_type::main_window_menu_observer_type(
                    command
                )
            );
            p_menu_command->add_menu_observer(p_menu_observer);

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
