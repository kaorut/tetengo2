/*! \file
    \brief The definition of tetengo2::detail::windows::menu.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MENU_H)
#define TETENGO2_DETAIL_WINDOWS_MENU_H

#include <algorithm>
//#include <cassert>
//#include <cstddef>
//#include <iterator>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <system_error>
#include <tuple>
//#include <type_traits>
//#include <utility>
//#include <vector>

//#include <boost/noncopyable.hpp>
//#include <boost/throw_exception.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
//#include <intsafe.h>
//#include <stdint.h>
//#pragma warning(pop)
//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.text.h"
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
            std::tuple< ::UINT, std::unique_ptr<typename std::remove_pointer< ::HMENU>::type, menu_deleter>, ::HMENU>
            id_handle_type;

        struct accelerator_table_deleter
        {
            void operator()(const ::HACCEL accelerator_table_handle)
            const
            {
                if (accelerator_table_handle)
                    ::DestroyAcceleratorTable(accelerator_table_handle);
            }


        };


    }
#endif


    /*!
        \brief The class for a detail implementation of a menu.
    */
    class menu : private boost::noncopyable
    {
    public:
        // types

        //! The menu details type.
        typedef detail::id_handle_type menu_details_type;

        //! The menu details pointer type.
        typedef std::unique_ptr<menu_details_type> menu_details_ptr_type;

        //! The shortcut key table details type.
        typedef std::remove_pointer< ::HACCEL>::type shortcut_key_table_details_type;

        //! The shortcut key table details pointer type.
        typedef
            std::unique_ptr<shortcut_key_table_details_type, detail::accelerator_table_deleter>
            shortcut_key_table_details_ptr_type;

        /*!
            \brief The style tag type.

            \tparam MenuBase A menu base type.
        */
        template <typename MenuBase>
        struct style_tag
        {
#if !defined(DOCUMENTATION)
            virtual void set_style(
                const menu_details_type&              details,
                ::MENUITEMINFOW&                      menu_info,
                std::vector< ::WCHAR>&                text,
                bool                                  enabled,
                typename MenuBase::state_type::enum_t state
            )
            const = 0;
#endif


        };


        // static functions

        /*!
            \brief Creates a menu bar.

            \return A unque pointer to a menu bar.

            \throw std::system_error When a menu bar cannot be created.
        */
        static menu_details_ptr_type create_menu_bar()
        {
            menu_details_ptr_type p_menu(
                make_unique<menu_details_type>(get_and_increment_id(), ::CreateMenu(), static_cast< ::HMENU>(NULL))
            );
            if (!std::get<1>(*p_menu))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't create a menu bar.")
                );
            }

            return std::move(p_menu);
        }

        /*!
            \brief Creates a popup menu.

            \return A unque pointer to a popup menu.

            \throw std::system_error When a popup menu cannot be created.
        */
        static menu_details_ptr_type create_popup_menu()
        {
            menu_details_ptr_type p_menu(
                make_unique<menu_details_type>(
                    get_and_increment_id(), ::CreatePopupMenu(), static_cast< ::HMENU>(NULL)
                )
            );
            if (!std::get<1>(*p_menu))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't create a popup menu."
                    )
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
            return
                make_unique<menu_details_type>(
                    get_and_increment_id(), static_cast< ::HMENU>(NULL), static_cast< ::HMENU>(NULL)
                );
        }
        
        /*!
            \brief Sets an enabled status.

            \tparam MenuBase A menu base type.

            \param menu    A menu.
            \param enabled An enabled status.
        */
        template <typename MenuBase>
        static void set_enabled(MenuBase& menu, const bool enabled)
        {
            if (!std::get<2>(*menu.details()))
                return;

            set_menu_info_style<MenuBase>(
                std::get<2>(*menu.details()), std::get<0>(*menu.details()), enabled, menu.state()
            );
        }

        /*!
            \brief Sets a state.

            \tparam MenuBase A menu base type.

            \param menu  A menu.
            \param state A status.
        */
        template <typename MenuBase>
        static void set_state(MenuBase& menu, const typename MenuBase::state_type::enum_t state)
        {
            if (!std::get<2>(*menu.details()))
                return;

            set_menu_info_style<MenuBase>(
                std::get<2>(*menu.details()), std::get<0>(*menu.details()), menu.enabled(), state
            );
        }

        /*!
            \brief Creates an empty shortcut key table.

            \tparam Entry A shortcut key table entry type.

            \return A unique pointer to a shortcut key table.
        */
        template <typename Entry>
        static shortcut_key_table_details_ptr_type create_shortcut_key_table()
        {
            return shortcut_key_table_details_ptr_type();
        }

        /*!
            \brief Creates a shortcut key table.

            \tparam ForwardIterator A forward iterator type.

            \param first A first position among shortcut key table entries.
            \param last  A last position among shortcut key table entries.

            \return A unique pointer to a shortcut key table.

            \throw std::system_error When a shortcut key table cannot be created.
        */
        template <typename ForwardIterator>
        static shortcut_key_table_details_ptr_type create_shortcut_key_table(
            const ForwardIterator first,
            const ForwardIterator last
        )
        {
            std::vector< ::ACCEL> accelerators;
            for (ForwardIterator i = first; i != last; ++i)
            {
                if (!i->has_shortcut_key()) continue;

                accelerators.push_back(to_accel(*i));
            }
            if (accelerators.empty())
                return shortcut_key_table_details_ptr_type();

            const ::HACCEL accelerator_table_handle =
                ::CreateAcceleratorTableW(accelerators.data(), static_cast<int>(accelerators.size()));
            if (!accelerator_table_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't create a shortcut key table."
                    )
                );
            }

            return shortcut_key_table_details_ptr_type(accelerator_table_handle);
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

            \throw std::system_error When a menu cannot be inserted.
        */
        template <typename PopupMenu, typename ForwardIterator, typename MenuBase, typename Encoder>
        static void insert_menu(
            PopupMenu&            popup_menu,
            const ForwardIterator offset,
            MenuBase&             menu,
            const Encoder&        encoder
        )
        {
            assert(!std::get<2>(*menu.details()));

            ::MENUITEMINFOW menu_info = {};
            menu_info.cbSize = sizeof(::MENUITEMINFO);
            std::vector< ::WCHAR> duplicated_text = make_text(menu, encoder);
            menu.style().set_style(*menu.details(), menu_info, duplicated_text, menu.enabled(), menu.state());

            assert(popup_menu.details());
            const ::BOOL result =
                ::InsertMenuItem(
                    &*std::get<1>(*popup_menu.details()),
                    static_cast< ::UINT>(std::distance(popup_menu.begin(), offset)),
                    TRUE,
                    &menu_info
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't insert a native menu."
                    )
                );
            }

            std::get<2>(*menu.details()) = &*std::get<1>(*popup_menu.details());
        }

        /*!
            \brief Erases a menu.

            \tparam PopupMenu       A popup menu type.
            \tparam ForwardIterator An forward iterator type.

            \param popup_menu A popup menu to which a menu is inserted.
            \param first      A first position to erase.
            \param last       A last position to erase.

            \throw std::system_error When a menu cannot be erased.
        */
        template <typename PopupMenu, typename ForwardIterator>
        static void erase_menus(PopupMenu& popup_menu, const ForwardIterator first, const ForwardIterator last)
        {
            for (ForwardIterator i = first; i != last; ++i)
                erase_menu(popup_menu, i);
        }

        /*!
            \brief Returns the menu bar style.

            \tparam MenuBase A menu base type.

            \return The menu bar style.
        */
        template <typename MenuBase>
        static const style_tag<MenuBase>& menu_bar_style()
        {
            static const menu_bar_style_tag<MenuBase> singleton;
            return singleton;
        }

        /*!
            \brief Returns the popup menu style.

            \tparam MenuBase A menu base type.

            \return The popup menu style.
        */
        template <typename MenuBase>
        static const style_tag<MenuBase>& popup_menu_style()
        {
            static const popup_menu_style_tag<MenuBase> singleton;
            return singleton;
        }

        /*!
            \brief Returns the menu command style.

            \tparam MenuBase A menu base type.

            \return The menu command style.
        */
        template <typename MenuBase>
        static const style_tag<MenuBase>& menu_command_style()
        {
            static const menu_command_style_tag<MenuBase> singleton;
            return singleton;
        }

        /*!
            \brief Returns the menu separator style.

            \tparam MenuBase A menu base type.

            \return The menu separator style.
        */
        template <typename MenuBase>
        static const style_tag<MenuBase>& menu_separator_style()
        {
            static const menu_separator_style_tag<MenuBase> singleton;
            return singleton;
        }


    private:
        // types

        template <typename MenuBase>
        struct menu_bar_style_tag : public style_tag<MenuBase>
        {
            virtual void set_style(
                const menu_details_type&              details,
                ::MENUITEMINFOW&                      menu_info,
                std::vector< ::WCHAR>&                text,
                bool                                  enabled,
                typename MenuBase::state_type::enum_t state
            )
            const
            {
                assert(false);
                BOOST_THROW_EXCEPTION(std::logic_error("A menu bar cannot be inserted."));
            }
        };

        template <typename MenuBase>
        struct popup_menu_style_tag : public style_tag<MenuBase>
        {
            virtual void set_style(
                const menu_details_type&              details,
                ::MENUITEMINFOW&                      menu_info,
                std::vector< ::WCHAR>&                text,
                bool                                  enabled,
                typename MenuBase::state_type::enum_t state
            )
            const
            {
                menu_info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING | MIIM_ID | MIIM_SUBMENU;

                menu_info.fType = 0;
                menu_info.fType |= state == MenuBase::state_type::selected ? MFT_RADIOCHECK : 0;

                menu_info.fState = 0;
                menu_info.fState |= enabled ? MFS_ENABLED : MFS_DISABLED;
                menu_info.fState |=
                    state == MenuBase::state_type::checked || state == MenuBase::state_type::selected ?
                    MFS_CHECKED : MFS_UNCHECKED;

                menu_info.dwTypeData = text.data();
                menu_info.cch = static_cast< ::UINT>(text.size() - 1);
                menu_info.wID = std::get<0>(details);
                menu_info.hSubMenu = &*std::get<1>(details);
            }


        };

        template <typename MenuBase>
        struct menu_command_style_tag : public style_tag<MenuBase>
        {
            virtual void set_style(
                const menu_details_type&              details,
                ::MENUITEMINFOW&                      menu_info,
                std::vector< ::WCHAR>&                text,
                bool                                  enabled,
                typename MenuBase::state_type::enum_t state
            )
            const
            {
                menu_info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING | MIIM_ID;

                menu_info.fType = 0;
                menu_info.fType |= state == MenuBase::state_type::selected ? MFT_RADIOCHECK : 0;

                menu_info.fState = 0;
                menu_info.fState |= enabled ? MFS_ENABLED : MFS_DISABLED;
                menu_info.fState |=
                    state == MenuBase::state_type::checked || state == MenuBase::state_type::selected ?
                    MFS_CHECKED : MFS_UNCHECKED;

                menu_info.dwTypeData = text.data();
                menu_info.cch = static_cast< ::UINT>(text.size() - 1);
                menu_info.wID = std::get<0>(details);
            }


        };

        template <typename MenuBase>
        struct menu_separator_style_tag : public style_tag<MenuBase>
        {
            virtual void set_style(
                const menu_details_type&              details,
                ::MENUITEMINFOW&                      menu_info,
                std::vector< ::WCHAR>&                text,
                bool                                  enabled,
                typename MenuBase::state_type::enum_t state
            )
            const
            {
                menu_info.fMask = MIIM_FTYPE;
                menu_info.fType = MFT_SEPARATOR;
            }


        };


        // static functions

        template <typename MenuBase>
        static void set_menu_info_style(
            const ::HMENU                               menu_handle,
            const ::UINT                                menu_id,
            const bool                                  enabled,
            const typename MenuBase::state_type::enum_t state
        )
        {
            ::MENUITEMINFOW menu_info = {};
            menu_info.cbSize = sizeof(::MENUITEMINFOW);
            const ::BOOL get_result = ::GetMenuItemInfoW(menu_handle, menu_id, FALSE, &menu_info);
            if (get_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get a menu item info."
                    )
                );
            }

            menu_info.fMask = MIIM_FTYPE | MIIM_STATE;

            menu_info.fType &= ~MFT_RADIOCHECK;
            menu_info.fType |= state == MenuBase::state_type::selected ? MFT_RADIOCHECK : 0;

            menu_info.fState &= ~(MFS_ENABLED | MFS_DISABLED | MFS_CHECKED | MFS_UNCHECKED);
            menu_info.fState |= enabled ? MFS_ENABLED : MFS_DISABLED;
            menu_info.fState |=
                state == MenuBase::state_type::checked || state == MenuBase::state_type::selected ?
                MFS_CHECKED : MFS_UNCHECKED;

            const ::BOOL set_result = ::SetMenuItemInfoW(menu_handle, menu_id, FALSE, &menu_info);
            if (set_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't set a menu item info."
                    )
                );
            }
        }

        template <typename MenuBase>
        static ::ACCEL to_accel(const MenuBase& menu)
        {
            const typename MenuBase::shortcut_key_type& shortcut_key = menu.shortcut_key();

            ::ACCEL accel = {};

            if (shortcut_key.shift())   accel.fVirt |= FSHIFT;
            if (shortcut_key.control()) accel.fVirt |= FCONTROL;
            if (shortcut_key.meta())    accel.fVirt |= FALT;
            accel.fVirt |= FVIRTKEY;
            
            accel.key = shortcut_key.key().code();

            assert(menu.details());
            accel.cmd = static_cast< ::WORD>(std::get<0>(*menu.details()));

            return accel;
        }

        static ::UINT get_and_increment_id()
        {
            static ::UINT id = 40001;

            return id++;
        }

        template <typename MenuBase, typename Encoder>
        static std::vector< ::WCHAR> make_text(const MenuBase& menu, const Encoder&  encoder)
        {
            typename MenuBase::string_type text = menu.text();
            if (menu.has_shortcut_key())
            {
                text += typename MenuBase::string_type(TETENGO2_TEXT("\t"));
                text += menu.shortcut_key().to_string();
            }
            const std::wstring native_string = encoder.encode(text);

            std::vector< ::WCHAR> duplicated;
            duplicated.reserve(native_string.length() + 1);
            std::copy(native_string.begin(), native_string.end(), std::back_inserter(duplicated));
            duplicated.push_back(L'\0');

            return duplicated;
        }

        template <typename PopupMenu, typename ForwardIterator>
        static void erase_menu(PopupMenu& popup_menu, const ForwardIterator offset)
        {
            assert(std::get<1>(*popup_menu.details()));
            assert(std::get<2>(*offset->details()));

            const ::BOOL result =
                ::RemoveMenu(
                    &*std::get<1>(*popup_menu.details()),
                    static_cast< ::UINT>(std::distance(popup_menu.begin(), offset)),
                    MF_BYPOSITION
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't remove a native menu."
                    )
                );
            }

            std::get<2>(*offset->details()) = NULL;
        }


        // forbidden operations

        menu();


   };


}}}


#endif
