/*! \file
    \brief The definition of concept_tetengo2::gui::GuiFactory.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_GUIFACTORY_H)
#define CONCEPTTETENGO2_GUI_GUIFACTORY_H

#include <memory>

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a GUI object factory.

        \tparam Type A type.
    */
    template <typename Type>
    class GuiFactory
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef
            typename Type::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        typedef typename Type::window_type window_type;

        typedef typename Type::main_menu_type main_menu_type;

        typedef typename Type::menu_command_type menu_command_type;

        typedef typename Type::popup_menu_type popup_menu_type;

        typedef typename Type::menu_separator_type menu_separator_type;


        // usage checks

        BOOST_CONCEPT_USAGE(GuiFactory)
        {
            std::auto_ptr<const gui_initializer_finalizer_type> p;
            const Type object(p);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const std::auto_ptr<window_type> p_window =
                object.create_window();
            boost::ignore_unused_variable_warning(p_window);

            const std::auto_ptr<main_menu_type> p_main_menu =
                object.create_main_menu();
            boost::ignore_unused_variable_warning(p_main_menu);

            const std::auto_ptr<menu_command_type> p_menu_command =
                object.create_menu_command(menu_command_type::string_type());
            boost::ignore_unused_variable_warning(p_menu_command);

            const std::auto_ptr<popup_menu_type> p_popup_menu =
                object.create_popup_menu(popup_menu_type::string_type());
            boost::ignore_unused_variable_warning(p_popup_menu);

            const std::auto_ptr<menu_separator_type> p_menu_separator =
                object.create_menu_separator();
            boost::ignore_unused_variable_warning(p_menu_separator);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
