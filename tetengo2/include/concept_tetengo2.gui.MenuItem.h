/*! \file
    \brief The definition of concept_tetengo2::gui::MenuItem.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUITEM_H)
#define CONCEPTTETENGO2_GUI_MENUITEM_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu item.

        \tparam Type A type.
    */
    template <typename Type>
    class MenuItem
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::string_type string_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MenuItem)
        {
            m_object.set_text(string_type());

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const string_type text = object.text();
            boost::ignore_unused_variable_warning(text);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
