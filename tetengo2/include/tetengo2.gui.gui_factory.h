/*! \file
    \brief The definition of tetengo2::gui::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIFACTORY_H)
#define TETENGO2_GUI_GUIFACTORY_H

//#include <memory>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "concept_tetengo2.gui.MainMenu.h"
#include "concept_tetengo2.gui.MenuCommand.h"
#include "concept_tetengo2.gui.PopupMenu.h"
#include "concept_tetengo2.gui.MenuSeparator.h"
#include "concept_tetengo2.gui.Window.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a GUI object factory.

        \tparam GuiInitializerFinalizer A initalization and finalization
                                        manager type.
        \tparam Window                  A window type. It must conform to
                                        concept_tetengo2::gui::Window<Window>.
        \tparam MainMenu                A main menu type It must conform to
                                        concept_tetengo2::gui::MainMenu<MainMenu>.
        \tparam MenuCommand             A menu command type It must conform to
                                        concept_tetengo2::gui::MenuCommand<MenuCommand>.
        \tparam PopupMenu               A popup menu type It must conform to
                                        concept_tetengo2::gui::PopupMenu<PopupMenu>.
        \tparam MenuSeparator           A menu separator type It must conform
                                        to
                                        concept_tetengo2::gui::MenuSeparator<MenuSeparator>.
    */
    template <
        typename GuiInitializerFinalizer,
        typename Window,
        typename MainMenu,
        typename MenuCommand,
        typename PopupMenu,
        typename MenuSeparator
    >
    class gui_factory : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MainMenu<MainMenu>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuCommand<MenuCommand>
        ));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::PopupMenu<PopupMenu>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuSeparator<MenuSeparator>
        ));


    public:
        // types

        //! The GUI initialization and finalization manager type.
        typedef GuiInitializerFinalizer gui_initializer_finalizer_type;

        //! The window type.
        typedef Window window_type;

        //! The main menu type.
        typedef MainMenu main_menu_type;

        //! The menu command type.
        typedef MenuCommand menu_command_type;

        //! The popup menu type.
        typedef PopupMenu popup_menu_type;

        //! The menu separator type.
        typedef MenuSeparator menu_separator_type;


        // constructors and destructor

        /*!
            \brief Creates a GUI object factory.

            \param p_gui_initializer_finalizer An auto pointer to a GUI
                                               initalization and finalization
                                               manager.
        */
        explicit gui_factory(
            std::auto_ptr<const gui_initializer_finalizer_type>
            p_gui_initializer_finalizer    
        )
        :
        m_p_gui_initializer_finalizer(p_gui_initializer_finalizer)
        {}

        /*!
            \brief Destroys the GUI object factory.
        */
        ~gui_factory()
        throw ()
        {}


        // functions

        /*!
            \brief Creates a window.

            \return An auto pointer to a window.
        */
        std::auto_ptr<window_type> create_window()
        const
        {
            return std::auto_ptr<window_type>(new window_type());
        }

        /*!
            \brief Creates a main menu.

            \return An auto pointer to a main menu.
        */
        std::auto_ptr<main_menu_type> create_main_menu()
        const
        {
            return std::auto_ptr<main_menu_type>(new main_menu_type());
        }

        /*!
            \brief Creates a menu command.

            \param text    A text.
            \param command A command.

            \return An auto pointer to a menu command.
        */
        std::auto_ptr<menu_command_type> create_menu_command(
            const typename menu_command_type::string_type&  text,
            const typename menu_command_type::command_type& command
        )
        const
        {
            return std::auto_ptr<menu_command_type>(
                new menu_command_type(text, command)
            );
        }

        /*!
            \brief Creates a popup menu.

            \param text A text.

            \return An auto pointer to a popup menu.
        */
        std::auto_ptr<popup_menu_type> create_popup_menu(
            const typename menu_command_type::string_type& text
        )
        const
        {
            return std::auto_ptr<popup_menu_type>(new popup_menu_type(text));
        }

        /*!
            \brief Creates a menu separator.

            \return An auto pointer to a menu separator.
        */
        std::auto_ptr<menu_separator_type> create_menu_separator()
        const
        {
            return std::auto_ptr<menu_separator_type>(
                new menu_separator_type()
            );
        }


    private:
        // variables

        const boost::scoped_ptr<const gui_initializer_finalizer_type>
        m_p_gui_initializer_finalizer;


    };


}}

#endif
