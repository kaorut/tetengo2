/*! \file
    \brief The definition of tetengo2::detail::windows::menu.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MENU_H)
#define TETENGO2_DETAIL_WINDOWS_MENU_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
//#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
//#include <utility>
#include <vector>

#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct menu_deleter
        {
            void operator()(const ::HMENU menu_handle)
            const
            {
                if (::IsMenu(menu_handle))
                    ::DestroyMenu(menu_handle);
            }


        };

        typedef
            std::pair<
                ::UINT,
                std::unique_ptr<
                    typename std::remove_pointer< ::HMENU>::type, menu_deleter
                >
            >
            id_handle_type;


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
        typedef detail::id_handle_type menu_details_type;

        //! The menu details pointer type.
        typedef std::unique_ptr<menu_details_type> menu_details_ptr_type;

        //! The style tag type.
        struct style_tag
        {
#if !defined(DOCUMENTATION)
            virtual void set_style(
                const menu_details_type& details,
                ::MENUITEMINFOW&         menu_info,
                std::vector< ::WCHAR>&   text
            )
            const = 0;
#endif


        };



        // static functions

        /*!
            \brief Creates a menu bar.

            \return A unque pointer to a menu bar.
        */
        static menu_details_ptr_type create_menu_bar()
        {
            menu_details_ptr_type p_menu(
                make_unique<menu_details_type>(
                    get_and_increment_id(), ::CreateMenu()
                )
            );
            if (!p_menu->second)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a menu bar.")
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
            menu_details_ptr_type p_menu(
                make_unique<menu_details_type>(
                    get_and_increment_id(), ::CreatePopupMenu()
                )
            );
            if (!p_menu->second)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a popup menu.")
                );
            }

            return std::move(p_menu);
        }

        /*!
            \brief Creates a menu.

            \return A unque pointer to a menu.
        */
        static menu_details_ptr_type create_menu()
        {
            return make_unique<menu_details_type>(
                get_and_increment_id(), static_cast< ::HMENU>(NULL)
            );
        }

        /*!
            \brief Inserts a menu.

            \tparam PopupMenu       A popup menu type.
            \tparam ForwardIterator An forward iterator type.
            \tparam MenuBase        A menu base type.
            \tparam Encoder         An encoder type.

            \param popup_menu A popup menu to which a menu is inserted.
            \param offset     An offset.
            \param menu       A menu to insert.
            \param encoder    An encoder.
        */
        template <
            typename PopupMenu,
            typename ForwardIterator,
            typename MenuBase,
            typename Encoder
        >
        static void insert_menu(
            PopupMenu&            popup_menu,
            const ForwardIterator offset,
            MenuBase&             menu,
            const Encoder&        encoder
        )
        {
            ::MENUITEMINFOW menu_info = {};
            menu_info.cbSize = sizeof(::MENUITEMINFO);
            std::vector< ::WCHAR> duplicated_text =
                duplicate_text(menu.text(), encoder);
            menu.style().set_style(
                *menu.details(), menu_info, duplicated_text
            );

            assert(popup_menu.details());
            const ::BOOL result = ::InsertMenuItem(
                &*popup_menu.details()->second,
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

        /*!
            \brief Returns the menu bar style.

            \return The menu bar style.
        */
        static const style_tag& menu_bar_style()
        {
            static const menu_bar_style_tag singleton;
            return singleton;
        }

        /*!
            \brief Returns the popup menu style.

            \return The popup menu style.
        */
        static const style_tag& popup_menu_style()
        {
            static const popup_menu_style_tag singleton;
            return singleton;
        }

        /*!
            \brief Returns the menu command style.

            \return The menu command style.
        */
        static const style_tag& menu_command_style()
        {
            static const menu_command_style_tag singleton;
            return singleton;
        }

        /*!
            \brief Returns the menu separator style.

            \return The menu separator style.
        */
        static const style_tag& menu_separator_style()
        {
            static const menu_separator_style_tag singleton;
            return singleton;
        }


    private:
        // types

        struct menu_bar_style_tag : public style_tag
        {
            virtual void set_style(
                const menu_details_type& details,
                ::MENUITEMINFOW&         menu_info,
                std::vector< ::WCHAR>&   text
            )
            const
            {
                assert(false);
                BOOST_THROW_EXCEPTION(
                    std::logic_error("A menu bar cannot be inserted.")
                );
            }
        };

        struct popup_menu_style_tag : public style_tag
        {
            virtual void set_style(
                const menu_details_type& details,
                ::MENUITEMINFOW&         menu_info,
                std::vector< ::WCHAR>&   text
            )
            const
            {
                menu_info.fMask = MIIM_STRING | MIIM_ID | MIIM_SUBMENU;
                menu_info.dwTypeData = text.data();
                menu_info.wID = details.first;
                menu_info.hSubMenu = &*details.second;
            }


        };

        struct menu_command_style_tag : public style_tag
        {
            virtual void set_style(
                const menu_details_type& details,
                ::MENUITEMINFOW&         menu_info,
                std::vector< ::WCHAR>&   text
            )
            const
            {
                menu_info.fMask = MIIM_STRING | MIIM_ID;
                menu_info.dwTypeData = text.data();
                menu_info.wID = details.first;
            }


        };

        struct menu_separator_style_tag : public style_tag
        {
            virtual void set_style(
                const menu_details_type& details,
                ::MENUITEMINFOW&         menu_info,
                std::vector< ::WCHAR>&   text
            )
            const
            {
                menu_info.fMask = MIIM_FTYPE;
                menu_info.fType = MFT_SEPARATOR;
            }


        };


        // static functions

        static ::UINT get_and_increment_id()
        {
            static ::UINT id = 40001;

            return id++;
        }

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
            assert(popup_menu.details()->second);
            const ::BOOL result =
                ::RemoveMenu(
                    &*popup_menu.details()->second,
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
