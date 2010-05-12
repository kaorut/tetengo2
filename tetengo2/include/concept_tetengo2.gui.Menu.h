/*! \file
    \brief The definition of concept_tetengo2::gui::Menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUITEM_H)
#define CONCEPTTETENGO2_GUI_MENUITEM_H

#include <memory>

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu.

        \tparam Type     A type.
        \tparam BaseType A base type.
    */
    template <typename Type, typename BaseType = Type>
    class Menu
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::id_type id_type;

        typedef typename Type::handle_type handle_type;

        typedef typename Type::string_type string_type;

        typedef typename Type::encoder_type encoder_type;

        typedef typename Type::menu_observer_type menu_observer_type;

        typedef typename Type::iterator iterator;

        typedef typename Type::const_iterator const_iterator;

        typedef typename Type::recursive_iterator recursive_iterator;

        typedef
            typename Type::const_recursive_iterator const_recursive_iterator;


        // usage checks

        BOOST_CONCEPT_USAGE(Menu)
        {
            m_p_object->select();

            std::auto_ptr<menu_observer_type> p_menu_observer;
            m_p_object->add_menu_observer(p_menu_observer);

            const iterator first = m_p_object->begin();
            boost::ignore_unused_variable_warning(first);

            const iterator last = m_p_object->end();
            boost::ignore_unused_variable_warning(last);

            const recursive_iterator recursive_first =
                m_p_object->recursive_begin();
            boost::ignore_unused_variable_warning(recursive_first);

            const recursive_iterator recursive_last =
                m_p_object->recursive_end();
            boost::ignore_unused_variable_warning(recursive_last);

            std::auto_ptr<BaseType> p;
            m_p_object->insert(first, p);

            m_p_object->erase(first, last);

            const_constraints(*m_p_object);
        }

        void const_constraints(const Type& object)
        {
            const id_type id = object.id();
            boost::ignore_unused_variable_warning(id);

            const handle_type handle = object.handle();
            boost::ignore_unused_variable_warning(handle);

            const string_type text = object.text();
            boost::ignore_unused_variable_warning(text);

            const const_iterator first = object.begin();
            boost::ignore_unused_variable_warning(first);

            const const_iterator last = object.end();
            boost::ignore_unused_variable_warning(last);

            const const_recursive_iterator recursive_first =
                object.recursive_begin();
            boost::ignore_unused_variable_warning(recursive_first);

            const const_recursive_iterator recursive_last =
                object.recursive_end();
            boost::ignore_unused_variable_warning(recursive_last);
        }

        
    private:
        // variables

        Type* m_p_object;


#endif
    };


}}

#endif
