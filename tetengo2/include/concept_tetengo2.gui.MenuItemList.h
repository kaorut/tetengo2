/*! \file
    \brief The definition of concept_tetengo2::gui::MenuItemList.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUITEMLIST_H)
#define CONCEPTTETENGO2_GUI_MENUITEMLIST_H

#include <memory>

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu item list.

        \tparam Type A type.
    */
    template <typename Type>
    class MenuItemList
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::menu_handle_type menu_handle_type;

        typedef typename Type::menu_item_type menu_item_type;

        typedef typename Type::iterator iterator;

        typedef typename Type::const_iterator const_iterator;


        // usage checks

        BOOST_CONCEPT_USAGE(MenuItemList)
        {
            const iterator first = m_object.begin();
            boost::ignore_unused_variable_warning(first);

            const iterator last = m_object.end();
            boost::ignore_unused_variable_warning(last);

            m_object.insert(first, std::auto_ptr<menu_item_type>());

            m_object.erase(first, last);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const const_iterator first = m_object.begin();
            boost::ignore_unused_variable_warning(first);

            const const_iterator last = m_object.end();
            boost::ignore_unused_variable_warning(last);

        }

        
    private:
        // variables

        Type m_object;

        menu_item_type m_menu_item;


#endif
    };


}}

#endif
