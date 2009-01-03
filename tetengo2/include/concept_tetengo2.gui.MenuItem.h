/*! \file
    \brief The definition of concept_tetengo2::gui::MenuItem.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUITEM_H)
#define CONCEPTTETENGO2_GUI_MENUITEM_H

#include <memory>

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

        typedef typename Type::id_type id_type;

        typedef typename Type::handle_type handle_type;

        typedef typename Type::string_type string_type;

        typedef
            typename Type::encode_from_native_type encode_from_native_type;

        typedef typename Type::encode_to_native_type encode_to_native_type;

        typedef typename Type::menu_observer_type menu_observer_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MenuItem)
        {
            m_p_object->set_text(string_type());

            m_p_object->select();

            std::auto_ptr<menu_observer_type> p_menu_observer;
            m_p_object->add_menu_observer(p_menu_observer);

            const_constraints(*m_p_object);
        }

        void const_constraints(const Type& object)
        {
            const bool is_command = object.is_command();
            boost::ignore_unused_variable_warning(is_command);

            const bool is_popup = object.is_popup();
            boost::ignore_unused_variable_warning(is_popup);

            const bool is_separator = object.is_separator();
            boost::ignore_unused_variable_warning(is_separator);

            const id_type id = object.id();
            boost::ignore_unused_variable_warning(id);

            const handle_type handle = object.handle();
            boost::ignore_unused_variable_warning(handle);

            const string_type text = object.text();
            boost::ignore_unused_variable_warning(text);
        }

        
    private:
        // variables

        Type* m_p_object;


#endif
    };


}}

#endif
