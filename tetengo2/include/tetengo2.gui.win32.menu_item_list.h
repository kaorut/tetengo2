/*! \file
    \brief The definition of tetengo2::gui::win32::menu_item_list.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUITEMLIST_H)
#define TETENGO2_GUI_WIN32_MENUITEMLIST_H

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <memory>
#include <stdexcept>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuItem.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a menu item list for Win32 platforms.

        \tparam MenuHandle A menu handle type. It must conform to
                           concept_tetengo2::gui::Handle<MenuHandle>.
        \tparam MenuItem   A menu item type. It must conform to
                           concept_tetengo2::gui::MenuItem<MenuItem>.
   */
    template <typename MenuHandle, typename MenuItem>
    class menu_item_list : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<MenuHandle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        //! The menu handle type.
        typedef MenuHandle menu_handle_type;

        //! The menu item type.
        typedef MenuItem menu_item_type;

        //! The menu items type.
        typedef boost::ptr_vector<menu_item_type> menu_items_type;

        //! The iterator type.
        typedef typename menu_items_type::iterator iterator;

        //! The const iterator type.
        typedef typename menu_items_type::const_iterator const_iterator;


        // constructors and destructor

        /*!
            \brief Creates a menu item list.

            \param menu_handle A menu handle.
        */
        menu_item_list(const menu_handle_type menu_handle)
        :
        m_menu_handle(menu_handle),
        m_menu_items()
        {}

        /*!
            \brief Destroys the menu item list.
        */
        ~menu_item_list()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the first immutable iterator to the menu items.

            \return The first immutable iterator.
        */
        const_iterator begin()
        const
        {
            return m_menu_items.begin();
        }

        /*!
            \brief Returns the first mutable iterator to the menu items.

            \return The first mutable iterator.
        */
        iterator begin()
        {
            return m_menu_items.begin();
        }

        /*!
            \brief Returns the last immutable iterator to the menu items.

            \return The last immutable iterator.
        */
        const_iterator end()
        const
        {
            return m_menu_items.end();
        }

        /*!
            \brief Returns the last mutable iterator to the menu items.

            \return The last mutable iterator.
        */
        iterator end()
        {
            return m_menu_items.end();
        }

        /*!
            \brief Insers a menu item.

            \param offset      An offset where a menu item is inserted.
            \param p_menu_item An auto pointer to a menu item. It must not be
                               NULL.
        */
        void insert(
            iterator                      offset,
            std::auto_ptr<menu_item_type> p_menu_item
        )
        {
            if (p_menu_item.get() == NULL)
            {
                throw std::invalid_argument(
                    "The auto pointer to a menu item is NULL."
                );
            }

            insert_native_menu_item(offset, *p_menu_item);

            m_menu_items.insert(offset, p_menu_item);
        }

        /*!
            \brief Erases the menu items.

            \param first The first iterator to the erased items.
            \param last  The last iterator to the eraed items.
        */
        void erase(iterator first, iterator last)
        {
            m_menu_items.erase(first, last);
        }


    private:
        // variables

        const menu_handle_type m_menu_handle;

        menu_items_type m_menu_items;


        // functions

        void insert_native_menu_item(
            iterator        offset,
            menu_item_type& menu_item
        )
        {
            const boost::scoped_array<::WCHAR> p_text(
                new ::WCHAR[menu_item.text().length() + 1]
            );
            std::copy(
                menu_item.text().begin(),
                menu_item.text().end(),
                p_text.get()
            );
            p_text[menu_item.text().length()] = L'\0';

            ::MENUITEMINFOW menu_item_info;
            std::memset(&menu_item_info, 0, sizeof(::MENUITEMINFO));

            menu_item_info.cbSize = sizeof(::MENUITEMINFO);
            menu_item_info.fMask = MIIM_STRING;
            menu_item_info.dwTypeData = p_text.get();

            ::InsertMenuItem(
                m_menu_handle,
                static_cast<::UINT>(
                    std::distance(m_menu_items.begin(), offset)
                ),
                TRUE,
                &menu_item_info
            );

        }
    };


}}}

#endif
