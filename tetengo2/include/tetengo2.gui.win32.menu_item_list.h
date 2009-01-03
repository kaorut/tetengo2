/*! \file
    \brief The definition of tetengo2::gui::win32::menu_item_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUITEMLIST_H)
#define TETENGO2_GUI_WIN32_MENUITEMLIST_H

#include <algorithm>
#include <cassert>
//#include <cstddef>
#include <cstring>
#include <iterator>
//#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/mem_fn.hpp>
//#include <boost/concept_check.hpp>
//#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.PopupMenu.h"


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

        //! The menu id_type.
        typedef typename menu_item_type::id_type menu_id_type;

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
            \brief Inserts a menu item.

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

        /*!
            \brief Finds a menu item by the specified id.

            If the menu item does not exist, it returns NULL.

            \tparam PopupMenu A popup menu type. It must conform to
                              concept_tetengo2::gui::PopupMenu<PopupMenu>.

            \param id An id.

            \return The pointer to the menu item.
        */
        template <typename PopupMenu>
        const menu_item_type* find_by_id(const menu_id_type id)
        const
        {
            return find_impl<const PopupMenu, const menu_item_type>(
                begin(),
                end(),
                id,
                boost::mem_fn(&menu_item_type::id),
                call_find_by_id_const<PopupMenu>
            );
        }

        /*!
            \brief Finds a menu item by the specified id.

            If the menu item does not exist, it returns NULL.

            \tparam PopupMenu A popup menu type. It must conform to
                              concept_tetengo2::gui::PopupMenu<PopupMenu>.

            \param id An id.

            \return The pointer to the menu item.
        */
        template <typename PopupMenu>
        menu_item_type* find_by_id(const menu_id_type id)
        {
            return find_impl<PopupMenu, menu_item_type>(
                begin(),
                end(),
                id,
                boost::mem_fn(&menu_item_type::id),
                call_find_by_id<PopupMenu>
            );
        }

        /*!
            \brief Finds a menu item by the specified handle.

            If the menu item does not exist, it returns NULL.

            \tparam PopupMenu A popup menu type. It must conform to
                              concept_tetengo2::gui::PopupMenu<PopupMenu>.

            \param handle A handle.

            \return The pointer to the menu item.
        */
        template <typename PopupMenu>
        const menu_item_type* find_by_handle(const menu_handle_type handle)
        const
        {
            BOOST_CONCEPT_ASSERT((
                concept_tetengo2::gui::PopupMenu<PopupMenu>
            ));

            return find_impl<const PopupMenu, const menu_item_type>(
                begin(),
                end(),
                handle,
                boost::mem_fn(&menu_item_type::handle),
                call_find_by_handle_const<PopupMenu>
            );
        }

        /*!
            \brief Finds a menu item by the specified handle.

            If the menu item does not exist, it returns NULL.

            \tparam PopupMenu A popup menu type. It must conform to
                              concept_tetengo2::gui::PopupMenu<PopupMenu>.

            \param handle A handle.

            \return The pointer to the menu item.
        */
        template <typename PopupMenu>
        menu_item_type* find_by_handle(const menu_handle_type handle)
        {
            BOOST_CONCEPT_ASSERT((
                concept_tetengo2::gui::PopupMenu<PopupMenu>
            ));

            return find_impl<PopupMenu, menu_item_type>(
                begin(),
                end(),
                handle,
                boost::mem_fn(&menu_item_type::handle),
                call_find_by_handle<PopupMenu>
            );
        }


    private:
        // types

        typedef typename menu_item_type::string_type string_type;

        typedef
            typename menu_item_type::encode_to_native_type
            encode_to_native_type;


        // static functions

        template <typename PopupMenu>
        static const menu_item_type* call_find_by_id_const(
            const PopupMenu&   popup_menu,
            const menu_id_type id
        )
        {
            return popup_menu.find_by_id(id);
        }

        template <typename PopupMenu>
        static menu_item_type* call_find_by_id(
            PopupMenu&         popup_menu,
            const menu_id_type id
        )
        {
            return popup_menu.find_by_id(id);
        }

        template <typename PopupMenu>
        static const menu_item_type* call_find_by_handle_const(
            const PopupMenu&       popup_menu,
            const menu_handle_type handle
        )
        {
            return popup_menu.find_by_handle(handle);
        }

        template <typename PopupMenu>
        static menu_item_type* call_find_by_handle(
            PopupMenu&             popup_menu,
            const menu_handle_type handle
        )
        {
            return popup_menu.find_by_handle(handle);
        }

        template <
            typename PopupMenu,
            typename MenuItem,
            typename InputIterator,
            typename Target,
            typename GetTarget,
            typename RecursiveFind
        >
        static MenuItem* find_impl(
            InputIterator      first,
            InputIterator      last,
            const Target       target,
            GetTarget          get_target,
            RecursiveFind      recursive_find
        )
        {
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<GetTarget, Target, MenuItem&>
            ));
            BOOST_CONCEPT_ASSERT((
                boost::BinaryFunction<
                    RecursiveFind, MenuItem*, PopupMenu, Target
                >
            ));

            for (InputIterator i = first; i != last; ++i)
            {
                if (get_target(*i) == target) return &*i;

                if (i->is_popup())
                {
                    assert(dynamic_cast<PopupMenu*>(&*i) != NULL);
                    MenuItem* const p_found =
                        recursive_find(static_cast<PopupMenu&>(*i), target);
                    if (p_found != NULL) return p_found;
                }
            }

            return NULL;
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
                    menu_item, menu_item_info, duplicated_text
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

        const std::vector< ::WCHAR> duplicate_text(const string_type& text)
        const
        {
            const std::wstring native_string = encode_to_native_type()(text);

            std::vector< ::WCHAR> duplicated;
            duplicated.reserve(native_string.length() + 1);
            std::copy(
                native_string.begin(),
                native_string.end(),
                std::back_inserter(duplicated)
            );
            duplicated.push_back(L'\0');

            return duplicated;
        }

        void set_menu_item_info_for_command(
            menu_item_type&        menu_item,
            ::MENUITEMINFOW&       menu_item_info,
            std::vector< ::WCHAR>& text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_ID;
            menu_item_info.dwTypeData = &text[0];
            menu_item_info.wID = menu_item.id();
        }

        void set_menu_item_info_for_popup(
            menu_item_type&        menu_item,
            ::MENUITEMINFOW&       menu_item_info,
            std::vector< ::WCHAR>& text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_SUBMENU;
            menu_item_info.dwTypeData = &text[0];
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
            std::vector< ::WCHAR>& text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_STATE;
            menu_item_info.dwTypeData = &text[0];
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
