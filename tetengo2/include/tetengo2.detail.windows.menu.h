/*! \file
    \brief The definition of tetengo2::detail::windows::menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MENU_H)
#define TETENGO2_DETAIL_WINDOWS_MENU_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp0x.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct menu_deleter
        {
            void operator()(::HMENU gdi_menu_handle)
            const
            {
                if (::IsMenu(gdi_menu_handle))
                    ::DestroyMenu(gdi_menu_handle);
            }


        };


    }
#endif

    /*!
        \brief The class for a detail implementation of a menu.
    */
    class menu
    {
    public:
        // types

        //! The menu details type.
        typedef std::remove_pointer< ::HMENU>::type menu_details_type;

        //! The menu details pointer type.
        typedef
            cpp0x::unique_ptr<menu_details_type, detail::menu_deleter>::type
            menu_details_ptr_type;


        // static functions

        /*!
            \brief Creates a main menu.

            \return A unque pointer to a main menu.
        */
        static menu_details_ptr_type create_main_menu()
        {
            menu_details_ptr_type p_menu(::CreateMenu());
            if (p_menu.get() == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a main menu.")
                );
            }

            return std::move(p_menu);
        }

        /*!
            \brief Creates a popup menu.

            \return A unque pointer to a popup menu.
        */
        static menu_details_ptr_type create_popup_menu()
        {
            menu_details_ptr_type p_menu(::CreatePopupMenu());
            if (p_menu.get() == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a popup menu.")
                );
            }

            return std::move(p_menu);
        }

        /*!
            \brief Inserts a menu.

            \tparam PopupMenu       A popup menu type.
            \tparam ForwardIterator An forward iterator type.
            \tparam Menu            A menu type.
            \tparam Encoder         An encoder type.

            \param popup_menu A popup menu to which a menu is inserted.
            \param offset     An offset.
            \param menu       A menu to insert.
            \param encoder    An encoder.
        */
        template <
            typename PopupMenu,
            typename ForwardIterator,
            typename Menu,
            typename Encoder
        >
        static void insert_menu(
            PopupMenu&            popup_menu,
            const ForwardIterator offset,
            Menu&                 menu,
            const Encoder&        encoder
        )
        {
            ::MENUITEMINFOW menu_info = {};
            menu_info.cbSize = sizeof(::MENUITEMINFO);
            std::vector< ::WCHAR> duplicated_text =
                duplicate_text(menu.text(), encoder);
            menu.set_menu_info(menu_info, duplicated_text);

            assert(popup_menu.details());
            const ::BOOL result = ::InsertMenuItem(
                &*popup_menu.details(),
                static_cast< ::UINT>(
                    std::distance(popup_menu.begin(), offset)
                ),
                TRUE,
                &menu_info
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't insert a native menu.")
                );
            }
        }

        /*!
            \brief Erases a menu.

            \tparam PopupMenu       A popup menu type.
            \tparam ForwardIterator An forward iterator type.

            \param popup_menu A popup menu to which a menu is inserted.
            \param first      A first position to erase.
            \param last       A last position to erase.
        */
        template <typename PopupMenu, typename ForwardIterator>
        static void erase_menus(
            PopupMenu&            popup_menu,
            const ForwardIterator first,
            const ForwardIterator last
        )
        {
            for (ForwardIterator i = first; i != last; ++i)
                erase_menu(popup_menu, i);
        }


    private:
        // static functions

        template <typename String, typename Encoder>
        static std::vector< ::WCHAR> duplicate_text(
            const String&  text,
            const Encoder& encoder
        )
        {
            const std::wstring native_string = encoder.encode(text);

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

        template <typename PopupMenu, typename ForwardIterator>
        static void erase_menu(
            PopupMenu&            popup_menu,
            const ForwardIterator offset
        )
        {
            assert(popup_menu.details());
            const ::BOOL result =
                ::RemoveMenu(
                    &*popup_menu.details(),
                    static_cast< ::UINT>(
                        std::distance(popup_menu.begin(), offset)
                    ),
                    MF_BYPOSITION
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't remove a native menu.")
                );
            }
        }


        // forbidden operations

        menu();


   };


}}}


#endif
