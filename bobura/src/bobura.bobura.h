/*! \file
    \brief The definition of bobura::bobura.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

//#include <cstddef>
//#include <memory>

//#include <boost/concept_check.hpp>
//#include <boost/noncopyable.hpp>

#include <concept_tetengo2.gui.GuiTypeList.h>

#include "bobura.command.about.h"
#include "bobura.command.exit.h"
#include "bobura.command.nop.h"
#include "bobura.message.main_window_menu_observer.h"
#include "bobura.message.main_window_paint_observer.h"
#include "bobura.message.main_window_window_observer.h"

#include "concept_bobura.Settings.h"


namespace bobura
{
    /*!
        \brief The class template for a bobura application.

        \tparam Settings    Settings type. It must conform to
                            concept_bobura::Settings<Settings>.
        \tparam GuiTypeList A type list type to create platform specific GUI
                            components. It must conform to
                            concept_tetengo2::gui::GuiTypeList<GuiTypeList>.
        \tparam Command     A command type. It must conform to
                            boost::Generator<Command, void>.
    */
    template <typename Settings, typename GuiTypeList, typename Command>
    class bobura : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_bobura::Settings<Settings>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::GuiTypeList<GuiTypeList>
        ));
        BOOST_CONCEPT_ASSERT((boost::Generator<Command, void>));


    public:
        // types

        //! The settings type.
        typedef Settings settings_type;

        //! The type list type to create platform specific GUI
        //! components.
        typedef GuiTypeList gui_type_list_type;

        //! The message loop type.
        typedef
            typename gui_type_list_type::message_loop_type message_loop_type;

        //! The quit-message-loop type.
        typedef
            typename gui_type_list_type::quit_message_loop_type
            quit_message_loop_type;

        //! The command type.
        typedef Command command_type;


        // constructors and destructor

        /*!
            \brief Creates a bobura application.

            \param settings Settings of the bobura.
        */
        bobura(const settings_type& settings)
        :
        m_gui_initializer_finalizer(),
        m_settings(settings)
        {}

        /*!
            \brief Destroys the bobura application.
        */
        ~bobura()
        throw ()
        {}


        // functions

        /*!
            \brief Runs the main process of the application.

            \return The exit status code.
        */
        int run()
        const
        {
            window_type main_window(typename window_type::style_frame, NULL);
            initialize_window(main_window);

            main_window.set_visible(true);

            return message_loop_type()();
        }


    private:
        //types

        typedef
            typename gui_type_list_type::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        typedef typename gui_type_list_type::window_type window_type;

        typedef typename window_type::canvas_type canvas_type;

        typedef typename window_type::main_menu_type main_menu_type;

        typedef
            typename window_type::window_observer_type
            window_observer_type;

        typedef
            typename window_type::paint_observer_type
            paint_observer_type;

        typedef typename main_menu_type::menu_item_type menu_item_type;

        typedef
            typename menu_item_type::menu_observer_type menu_observer_type;

        typedef
            typename gui_type_list_type::menu_command_type menu_command_type;

        typedef typename gui_type_list_type::popup_menu_type popup_menu_type;

        typedef
            typename gui_type_list_type::menu_separator_type
            menu_separator_type;


        // variables

        const gui_initializer_finalizer_type m_gui_initializer_finalizer;

        const settings_type& m_settings;


        // functions

        void initialize_window(window_type& window)
        const
        {
            set_message_observers(window);
            set_menus(window);
            window.set_text(L"ぼうぶら テストプログラム");
        }

        void set_message_observers(window_type& window)
        const
        {
            window.add_window_observer(
                std::auto_ptr<window_observer_type> (
                    new message::main_window_window_observer<
                        quit_message_loop_type
                    >(quit_message_loop_type())
                )
            );

            window.add_paint_observer(
                std::auto_ptr<paint_observer_type> (
                    new message::main_window_paint_observer<canvas_type>()
                )
            );
        }

        void set_menus(window_type& window)
        const
        {
            std::auto_ptr<main_menu_type> p_main_menu(new main_menu_type());

            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    new popup_menu_type(L"ファイル(&F)")
                );

                append_menu_command(
                    *p_popup_menu, L"新規作成(&N)\tCtrl+N", command::nop()
                );
                append_menu_command(
                    *p_popup_menu, L"開く(&O)...\tCtrl+O", command::nop()
                );
                append_menu_command(
                    *p_popup_menu, L"上書き保存(&S)\tCtrl+S", command::nop()
                );
                append_menu_command(
                    *p_popup_menu, L"名前を付けて保存(&A)...", command::nop()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu, L"終了(&X)",
                    command::exit<window_type>(window)
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
                    *p_popup_menu, L"元に戻す(&U)\tCtrl+Z", command::nop()
                );
                append_menu_command(
                    *p_popup_menu, L"やり直し(&R)\tCtrl+Y", command::nop()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu, L"切り取り(&T)\tCtrl+X", command::nop()
                );
                append_menu_command(
                    *p_popup_menu, L"コピー(&C)\tCtrl+C", command::nop()
                );
                append_menu_command(
                    *p_popup_menu, L"貼り付け(&P)\tCtrl+V", command::nop()
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu, L"検索(&F)...\tCtrl+F", command::nop()
                );
                append_menu_command(
                    *p_popup_menu, L"置換(&R)...\tCtrl+H", command::nop()
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
                    *p_popup_menu, L"バージョン情報(&A)...",
                    command::about<
                        window_type, message_loop_type, quit_message_loop_type
                    >(window)
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }

            window.set_main_menu(p_main_menu);
        }

        void append_menu_command(
            popup_menu_type&                            popup_menu,
            const typename menu_item_type::string_type& text,
            const command_type&                         command
        )
        const
        {
            std::auto_ptr<menu_item_type> p_menu_command(
                new menu_command_type(text)
            );

            std::auto_ptr<menu_observer_type> p_menu_observer(
                new message::main_window_menu_observer<command_type>(command)
            );
            p_menu_command->add_menu_observer(p_menu_observer);

            popup_menu.insert(
                popup_menu.menu_item_end(), p_menu_command
            );
        }

        void append_menu_separator(popup_menu_type& popup_menu)
        const
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
