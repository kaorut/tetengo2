/*! \file
    \brief The definition of tetengo2::gui::gui_type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUITYPELIST_H)
#define TETENGO2_GUI_GUITYPELIST_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MainMenu.h"
#include "concept_tetengo2.gui.MenuCommand.h"
#include "concept_tetengo2.gui.PopupMenu.h"
#include "concept_tetengo2.gui.MenuSeparator.h"
#include "concept_tetengo2.gui.Window.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a GUI type list.

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
    class gui_type_list
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


    };


}}

#endif
