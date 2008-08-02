/*! \file
    \brief The definition of tetengo2::gui::win32::menu_item_list.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUITEMLIST_H)
#define TETENGO2_GUI_WIN32_MENUITEMLIST_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iterator>
//#include <memory>
#include <stdexcept>
#include <vector>

//#include <boost/concept_check.hpp>
//#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.MenuItem.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a menu item list for Win32 platforms.

        \tparam MenuItem A menu item type. It must conform to
                         concept_tetengo2::gui::MenuItem<MenuItem>.
   */
    template <typename MenuItem>
    class menu_item_list : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        //! The menu item type.
        typedef MenuItem menu_item_type;

        //! The menu handle type.
        typedef typename menu_item_type::handle_type menu_handle_type;

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
        {
            assert(::IsMenu(m_menu_handle) == 0);
        }


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
            erase_native_menus(first, last);

            m_menu_items.erase(first, last);
        }


    private:
        // static functions

        static ::UINT get_and_increment_menu_id()
        {
            static ::UINT menu_id = 40001;
            return menu_id++;
        }


        // variables

        const menu_handle_type m_menu_handle;

        menu_items_type m_menu_items;


        // functions

        void insert_native_menu_item(
            const_iterator  offset,
            menu_item_type& menu_item
        )
        const
        {
            std::vector< ::WCHAR> duplicated_text =
                duplicate_text(menu_item.text());

            ::MENUITEMINFOW menu_item_info;
            std::memset(&menu_item_info, 0, sizeof(::MENUITEMINFO));
            menu_item_info.cbSize = sizeof(::MENUITEMINFO);

            if      (menu_item.is_command())
            {
                set_menu_item_info_for_command(
                    menu_item_info, duplicated_text
                );
            }
            else if (menu_item.is_popup())
            {
                set_menu_item_info_for_popup(
                    menu_item, menu_item_info, duplicated_text
                );
            }
            else if (menu_item.is_separator())
            {
                set_menu_item_info_for_separator(menu_item, menu_item_info);
            }
            else
            {
                set_menu_item_info_for_unknown(
                    menu_item, menu_item_info, duplicated_text
                );
            }

            const ::BOOL result = ::InsertMenuItem(
                m_menu_handle,
                static_cast< ::UINT>(
                    std::distance(m_menu_items.begin(), offset)
                ),
                TRUE,
                &menu_item_info
            );
            if (result == 0)
            {
                throw std::runtime_error(
                    "Can't insert a native menu command."
                );
            }
        }

        const std::vector< ::WCHAR> duplicate_text(
            const typename menu_item_type::string_type& text
        )
        const
        {
            std::vector< ::WCHAR> duplicated;
            duplicated.reserve(text.length() + 1);
            std::copy(
                text.begin(), text.end(), std::back_inserter(duplicated)
            );
            duplicated.push_back(L'\0');

            return duplicated;
        }

        void set_menu_item_info_for_command(
            ::MENUITEMINFOW&       menu_item_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_ID;
            menu_item_info.dwTypeData = &duplicated_text[0];
            menu_item_info.wID = get_and_increment_menu_id();
        }

        void set_menu_item_info_for_popup(
            menu_item_type&        menu_item,
            ::MENUITEMINFOW&       menu_item_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_SUBMENU;
            menu_item_info.dwTypeData = &duplicated_text[0];
            menu_item_info.hSubMenu = menu_item.handle();
        }

        void set_menu_item_info_for_separator(
            menu_item_type&  menu_item,
            ::MENUITEMINFOW& menu_item_info
        )
        const
        {
            menu_item_info.fMask = MIIM_FTYPE;
            menu_item_info.fType = MFT_SEPARATOR;
        }

        void set_menu_item_info_for_unknown(
            menu_item_type&        menu_item,
            ::MENUITEMINFOW&       menu_item_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_STATE;
            menu_item_info.dwTypeData = &duplicated_text[0];
            menu_item_info.fState = MFS_DISABLED;
        }

        void erase_native_menus(const_iterator first, const_iterator last)
        const
        {
            for (const_iterator i = first; i != last; ++i)
                erase_native_menu(i);
        }

        void erase_native_menu(const_iterator offset)
        const
        {
            ::RemoveMenu(
                m_menu_handle,
                static_cast< ::UINT>(
                    std::distance(m_menu_items.begin(), offset)
                ),
                MF_BYPOSITION
            );
        }


    };


}}}

#endif
