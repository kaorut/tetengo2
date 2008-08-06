/*! \file
    \brief The definition of bobura::bobura.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

//#include <memory>
#include <string>

//#include <boost/concept_check.hpp>
//#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <concept_tetengo2.gui.GuiFactory.h>

#include "bobura.message.main_window_menu_observer.h"
#include "bobura.message.main_window_paint_observer.h"
#include "bobura.message.main_window_window_observer.h"


namespace bobura
{
    /*!
        \brief The class template for a bobura application.

        \tparam GuiFactory      An abstract factory type to create platform
                                specific GUI components. It must conform to
                                concept_tetengo2::gui::GuiFactory<GuiFactory>.
        \tparam MessageLoop     A generator type for the message loop. It must
                                conform to boost::Generator<MessageLoop, int>.
        \tparam QuitMessageLoop A unary functor type for quitting the message
                                loop. It must conform to
                                boost::UnaryFunction<QuitMessageLoop, void, int>.
    */
    template <
        typename GuiFactory,
        typename MessageLoop,
        typename QuitMessageLoop
    >
    class bobura : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::GuiFactory<GuiFactory>));
        BOOST_CONCEPT_ASSERT((boost::Generator<MessageLoop, int>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));


    public:
        // types

        //! The abstract factory type to create platform specific GUI
        //! components.
        typedef GuiFactory gui_factory_type;


        // constructors and destructor

        /*!
            \brief Creates a bobura application.

            \param p_gui_factory An auto pointer to a GUI factory.
        */
        explicit bobura(std::auto_ptr<const gui_factory_type> p_gui_factory)
        :
        m_p_gui_factory(p_gui_factory)
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
            const boost::scoped_ptr<window_type> p_main_window(
                m_p_gui_factory->create_window()
            );
            initialize_window(p_main_window.get());

            p_main_window->set_visible(true);

            return message_loop_type()();
        }


    private:
        //types

        typedef typename gui_factory_type::window_type window_type;

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
            typename gui_factory_type::menu_command_type menu_command_type;

        typedef typename gui_factory_type::popup_menu_type popup_menu_type;

        typedef MessageLoop message_loop_type;

        typedef QuitMessageLoop quit_message_loop_type;


        // variables

        const boost::scoped_ptr<const gui_factory_type> m_p_gui_factory;


        // functions

        void initialize_window(window_type* const p_window)
        const
        {
            set_message_observers(p_window);
            set_menus(p_window);
            p_window->set_text(L"ぼうぶら テストプログラム");
        }

        void set_message_observers(window_type* const p_window)
        const
        {
            p_window->add_window_observer(
                std::auto_ptr<window_observer_type> (
                    new message::main_window_window_observer<
                        quit_message_loop_type
                    >(quit_message_loop_type())
                )
            );

            p_window->add_paint_observer(
                std::auto_ptr<paint_observer_type> (
                    new message::main_window_paint_observer<canvas_type>()
                )
            );
        }

        void set_menus(window_type* const p_window)
        const
        {
            std::auto_ptr<main_menu_type> p_main_menu(
                m_p_gui_factory->create_main_menu()
            );

            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    m_p_gui_factory->create_popup_menu(L"ファイル(&F)")
                );

                append_menu_command(
                    *p_popup_menu, L"新規作成(&N)\tCtrl+N", L"New"
                );
                append_menu_command(
                    *p_popup_menu, L"開く(&O)...\tCtrl+O", L"Open"
                );
                append_menu_command(
                    *p_popup_menu, L"上書き保存(&S)\tCtrl+S", L"Save"
                );
                append_menu_command(
                    *p_popup_menu, L"名前を付けて保存(&A)...", L"SaveAs"
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu, L"終了(&X)", L"Exit"
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }
            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    m_p_gui_factory->create_popup_menu(L"編集(&E)")
                );

                append_menu_command(
                    *p_popup_menu, L"元に戻す(&U)\tCtrl+Z", L"Undo"
                );
                append_menu_command(
                    *p_popup_menu, L"やり直し(&R)\tCtrl+Y", L"Redo"
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu, L"切り取り(&T)\tCtrl+X", L"Cut"
                );
                append_menu_command(
                    *p_popup_menu, L"コピー(&C)\tCtrl+C", L"Copy"
                );
                append_menu_command(
                    *p_popup_menu, L"貼り付け(&P)\tCtrl+V", L"Paste"
                );
                append_menu_separator(*p_popup_menu);
                append_menu_command(
                    *p_popup_menu, L"検索(&F)...\tCtrl+F", L"Find"
                );
                append_menu_command(
                    *p_popup_menu, L"置換(&R)...\tCtrl+H", L"Replace"
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }
            {
                std::auto_ptr<popup_menu_type> p_popup_menu(
                    m_p_gui_factory->create_popup_menu(L"ヘルプ(&H)")
                );

                append_menu_command(
                    *p_popup_menu, L"バージョン情報(&A)...", L"About"
                );

                p_main_menu->insert(
                    p_main_menu->menu_item_end(),
                    std::auto_ptr<menu_item_type>(p_popup_menu)
                );
            }

            p_window->set_main_menu(p_main_menu);
        }

        void append_menu_command(
            popup_menu_type&                            popup_menu,
            const typename menu_item_type::string_type& text,
            const std::wstring&                         command
        )
        const
        {
            std::auto_ptr<menu_item_type> p_menu_command(
                m_p_gui_factory->create_menu_command(text)
            );

            std::auto_ptr<menu_observer_type> p_menu_observer(
                new message::main_window_menu_observer<std::wstring>(command)
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
                m_p_gui_factory->create_menu_separator()
            );
            popup_menu.insert(
                popup_menu.menu_item_end(), p_menu_separator
            );
        }

    };


}

#endif
