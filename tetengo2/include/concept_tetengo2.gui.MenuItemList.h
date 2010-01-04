/*! \file
    \brief The definition of concept_tetengo2::gui::MenuItemList.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUITEMLIST_H)
#define CONCEPTTETENGO2_GUI_MENUITEMLIST_H

#include <cstddef>
#include <memory>

#include <boost/concept_check.hpp>


namespace
{
    template <typename MenuItemType>
    struct popup_menu : public MenuItemType
    {
        typedef typename MenuItemType::id_type id_type;

        typedef typename MenuItemType::handle_type handle_type;

        typedef MenuItemType menu_item_type;

        typedef int menu_items_type;

        typedef void* menu_item_iterator;

        typedef const void* const_menu_item_iterator;

        virtual ~popup_menu()
        throw ()
        {}

        virtual bool is_command()
        const
        {
            return false;
        }

        virtual bool is_popup()
        const
        {
            return false;
        }

        virtual bool is_separator()
        const
        {
            return false;
        }

        virtual handle_type handle()
        const
        {
            return NULL;
        }

        const_menu_item_iterator menu_item_begin()
        const
        {
            return NULL;
        }

        menu_item_iterator menu_item_begin()
        {
            return NULL;
        }

        const_menu_item_iterator menu_item_end()
        const
        {
            return NULL;
        }

        menu_item_iterator menu_item_end()
        {
            return NULL;
        }

        void insert(
            menu_item_iterator            offset,
            std::auto_ptr<menu_item_type> p_menu_item
        )
        {}

        void erase(menu_item_iterator first, menu_item_iterator last)
        {}

        const menu_item_type* find_by_id(const id_type id)
        const
        {
            return NULL;
        }

        menu_item_type* find_by_id(const id_type id)
        {
            return NULL;
        }

        const menu_item_type* find_by_handle(const handle_type handle)
        const
        {
            return NULL;
        }

        menu_item_type* find_by_handle(const handle_type handle)
        {
            return NULL;
        }


    };


}


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu item list.

        \tparam Type      A type.
    */
    template <typename Type>
    class MenuItemList
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::menu_item_type menu_item_type;

        typedef typename Type::menu_id_type menu_id_type;

        typedef typename Type::menu_handle_type menu_handle_type;

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

            menu_item_type* const p_found_by_id =
#if defined(_MSC_VER)
                m_object.find_by_id<popup_menu_type>(0);
#else
                m_object.find_by_id(0);
#endif
            boost::ignore_unused_variable_warning(p_found_by_id);

            menu_item_type* const p_found_by_handle =
#if defined(_MSC_VER)
                m_object.find_by_handle<popup_menu_type>(NULL);
#else
                m_object.find_by_handle(NULL);
#endif
            boost::ignore_unused_variable_warning(p_found_by_handle);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const const_iterator first = object.begin();
            boost::ignore_unused_variable_warning(first);

            const const_iterator last = object.end();
            boost::ignore_unused_variable_warning(last);

            const menu_item_type* const p_found_by_id =
#if defined(_MSC_VER)
                m_object.find_by_id<popup_menu_type>(0);
#else
                m_object.find_by_id(0);
#endif
            boost::ignore_unused_variable_warning(p_found_by_id);

            const menu_item_type* const p_found_by_handle =
#if defined(_MSC_VER)
                m_object.find_by_handle<popup_menu_type>(NULL);
#else
                m_object.find_by_handle(NULL);
#endif
            boost::ignore_unused_variable_warning(p_found_by_handle);
        }

        
    private:
        // types

        typedef popup_menu<menu_item_type> popup_menu_type;


        // variables

        Type m_object;


#endif
    };


}}

#endif
