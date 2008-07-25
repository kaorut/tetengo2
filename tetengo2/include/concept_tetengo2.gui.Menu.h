/*! \file
    \brief The definition of concept_tetengo2::gui::Menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENU_H)
#define CONCEPTTETENGO2_GUI_MENU_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu.

        \tparam Type A type.
    */
    template <typename Type>
    class Menu
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::handle_type handle_type;

        typedef typename Type::menu_item_type menu_item_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Menu)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const handle_type handle = object.handle();
            boost::ignore_unused_variable_warning(handle);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
