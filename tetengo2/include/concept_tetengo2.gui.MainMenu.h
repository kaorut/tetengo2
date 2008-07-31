/*! \file
    \brief The definition of concept_tetengo2::gui::MainMenu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MAINMENU_H)
#define CONCEPTTETENGO2_GUI_MAINMENU_H

#include <memory>

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a main menu.

        \tparam Type A type.
    */
    template <typename Type>
    class MainMenu
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::handle_type handle_type;

        typedef typename Type::menu_item_type menu_item_type;

        typedef typename Type::menu_item_iterator menu_item_iterator;

        typedef
            typename Type::const_menu_item_iterator const_menu_item_iterator;


        // usage checks

        BOOST_CONCEPT_USAGE(MainMenu)
        {
            const menu_item_iterator first = m_object.menu_item_begin();
            boost::ignore_unused_variable_warning(first);

            const menu_item_iterator last = m_object.menu_item_end();
            boost::ignore_unused_variable_warning(last);

            m_object.insert(first, std::auto_ptr<menu_item_type>());

            m_object.erase(first, last);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const handle_type handle = object.handle();
            boost::ignore_unused_variable_warning(handle);

            const const_menu_item_iterator first = m_object.menu_item_begin();
            boost::ignore_unused_variable_warning(first);

            const const_menu_item_iterator last = m_object.menu_item_end();
            boost::ignore_unused_variable_warning(last);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
