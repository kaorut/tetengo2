/*! \file
    \brief The definition of concept_tetengo2::gui::GuiTypeList.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_GUITYPELIST_H)
#define CONCEPTTETENGO2_GUI_GUITYPELIST_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a GUI type list.

        \tparam Type A type.
    */
    template <typename Type>
    class GuiTypeList
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef
            typename Type::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        typedef typename Type::message_loop_type message_loop_type;

        typedef typename Type::quit_message_loop_type quit_message_loop_type;

        typedef typename Type::alert_type alert_type;

        typedef typename Type::widget_type widget_type;

        typedef typename Type::main_menu_type main_menu_type;

        typedef typename Type::menu_command_type menu_command_type;

        typedef typename Type::window_type window_type;

        typedef typename Type::popup_menu_type popup_menu_type;

        typedef typename Type::menu_separator_type menu_separator_type;

        typedef typename Type::dialog_type dialog_type;


        // usage checks

        BOOST_CONCEPT_USAGE(GuiTypeList)
        {}

        
#endif
    };


}}

#endif
