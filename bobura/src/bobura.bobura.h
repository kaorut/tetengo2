/*! \file
    \brief The definition of bobura::bobura.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

//#include <memory>

//#include <boost/concept_check.hpp>
//#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <concept_tetengo2.gui.GuiFactory.h>

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
            std::auto_ptr<main_menu_type> p_main_menu(new main_menu_type());

            p_main_menu->insert(
                p_main_menu->menu_item_end(),
                std::auto_ptr<main_menu_type::menu_item_type>(
                    m_p_gui_factory->create_menu_command(L"ファイル(&F)", L"")
                )
            );

            p_window->set_main_menu(p_main_menu);

        }


    };


}

#endif
