/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.GuiTypeList.h>

#include "concept_bobura.command.CommandTypeList.h"
#include "concept_bobura.message.MessageTypeList.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam GuiTypeList     A GUI type list type. It must conform to
                                concept_tetengo2::gui::GuiTypeList<GuiTypeList>.
        \tparam CommandTypeList A command type. It must conform to
                                concept_bobura::command::CommandTypeList<CommandTypeList>.
        \tparam MessageTypeList A message type. It must conform to
                                concept_bobura::message::MessageTypeList<MessageTypeList>.
    */
    template <
        typename GuiTypeList,
        typename CommandTypeList,
        typename MessageTypeList
    >
    class main_window : public GuiTypeList::window_type
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::GuiTypeList<GuiTypeList>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_bobura::command::CommandTypeList<CommandTypeList>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_bobura::message::MessageTypeList<MessageTypeList>
        ));


    public:
        // types

        //! The GUI type list type.
        typedef GuiTypeList gui_type_list_type;

        //! The window type.
        typedef typename gui_type_list_type::window_type window_type;

        //! The widget type.
        typedef typename window_type::widget_type widget_type;

        //! The handle type.
        typedef typename window_type::handle_type handle_type;

        //! The canvas type.
        typedef typename window_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename window_type::alert_type alert_type;

        //! The difference type.
        typedef typename window_type::difference_type difference_type;

        //! The size type.
        typedef typename window_type::size_type size_type;

        //! The position type.
        typedef typename window_type::position_type position_type;

        //! The dimension type.
        typedef typename window_type::dimension_type dimension_type;

        //! The string type.
        typedef typename window_type::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename window_type::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename window_type::encode_to_native_type
            encode_to_native_type;

        //! The paint observer type.
        typedef
            typename window_type::paint_observer_type paint_observer_type;

        //! The main menu type.
        typedef typename window_type::main_menu_type main_menu_type;

        //! The window observer type.
        typedef
            typename window_type::window_observer_type window_observer_type;

        //! The style type.
        typedef typename window_type::style_type style_type;

        //! The command type list type.
        typedef CommandTypeList command_type_list_type;

        //! The message type list type.
        typedef MessageTypeList message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a main window.
        */
        main_window()
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

        typedef
            typename gui_type_list_type::quit_message_loop_type
            quit_message_loop_type;

        typedef typename main_menu_type::menu_item_type menu_item_type;

        typedef
            typename menu_item_type::menu_observer_type menu_observer_type;

        typedef
            typename gui_type_list_type::menu_command_type menu_command_type;

        typedef typename gui_type_list_type::popup_menu_type popup_menu_type;

        typedef
            typename gui_type_list_type::menu_separator_type
            menu_separator_type;

        typedef typename command_type_list_type::command_type command_type;


        // static functions

        static void initialize_window(main_window& window)
        {
            set_message_observers(window);
            set_menus(window);
            window.set_text(L"ぼうぶら テストプログラム");
        }

        static void set_message_observers(window_type& window)
        {
            window.add_window_observer(
                std::auto_ptr<window_observer_type>(
                    new typename message_type_list_type::main_window_window_observer_type(
                        quit_message_loop_type()
                    )
                )
            );

            window.add_paint_observer(
                std::auto_ptr<paint_observer_type>(
                    new typename message_type_list_type::main_window_paint_observer_type()
                )
            );
        }

        static void set_menus(window_type& window)
        {
            std::auto_ptr<main_menu_type> p_main_menu(new main_menu_type());

            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    new popup_menu_type(L"ファイル(&F)")
                );

                append_menu_command(
                    *p_popup_menu,
                    L"新規作成(&N)\tCtrl+N",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"開く(&O)...\tCtrl+O",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"上書き保存(&S)\tCtrl+S",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"名前を付けて保存(&A)...",
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    L"終了(&X)",
                    typename command_type_list_type::exit_type(window)
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }
            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    new popup_menu_type(L"編集(&E)")
                );

                append_menu_command(
                    *p_popup_menu,
                    L"元に戻す(&U)\tCtrl+Z",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"やり直し(&R)\tCtrl+Y",
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    L"切り取り(&T)\tCtrl+X",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"コピー(&C)\tCtrl+C",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"貼り付け(&P)\tCtrl+V",
                    typename command_type_list_type::nop_type()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu,
                    L"検索(&F)...\tCtrl+F",
                    typename command_type_list_type::nop_type()
                );
                append_menu_command(
                    *p_popup_menu,
                    L"置換(&R)...\tCtrl+H",
                    typename command_type_list_type::nop_type()
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }
            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    new popup_menu_type(L"ヘルプ(&H)")
                );

                append_menu_command(
                    *p_popup_menu,
                    L"バージョン情報(&A)...",
                    typename command_type_list_type::about_type(window)
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }

            window.set_main_menu(p_main_menu);
        }

        static void append_menu_command(
            popup_menu_type&                            popup_menu,
            const typename menu_item_type::string_type& text,
            const command_type&                         command
        )
        {
            std::auto_ptr<menu_item_type> p_menu_command(
                new menu_command_type(text)
            );

            std::auto_ptr<menu_observer_type> p_menu_observer(
                new typename message_type_list_type::main_window_menu_observer_type(
                    command
                )
            );
            p_menu_command->add_menu_observer(p_menu_observer);

            popup_menu.insert(
                popup_menu.menu_item_end(), p_menu_command
            );
        }

        static void append_menu_separator(popup_menu_type& popup_menu)
        {
            std::auto_ptr<menu_item_type> p_menu_separator(
                new menu_separator_type()
            );
            popup_menu.insert(
                popup_menu.menu_item_end(), p_menu_separator
            );
        }


    };


}

#endif
