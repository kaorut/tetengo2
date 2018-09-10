/*! \file
    \brief The definition of tetengo2::detail::windows::menu.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/menu.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui { namespace menu {
    class abstract_popup;
    class menu_base;
}}}


namespace tetengo2::detail::windows {
    class menu::impl : private boost::noncopyable
    {
    public:
        // types

        using menu_details_type = menu::menu_details_type;

        using menu_details_ptr_type = menu::menu_details_ptr_type;

        using shortcut_key_table_details_type = menu::shortcut_key_table_details_type;

        using shortcut_key_table_details_ptr_type = menu::shortcut_key_table_details_ptr_type;

        using style_tag = menu::style_tag;

        using state_type = menu::state_type;

        using iterator = menu::iterator;


        // functions

        menu_details_ptr_type create_menu_bar_impl() const
        {
            std::unique_ptr<windows_menu_details_type> p_menu{ std::make_unique<windows_menu_details_type>(
                get_and_increment_id(),
                reinterpret_cast<std::intptr_t>(::CreateMenu()),
                reinterpret_cast<std::intptr_t>(nullptr)) };
            if (!p_menu->handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a menu bar." }));
            }

            return std::move(p_menu);
        }

        menu_details_ptr_type create_popup_menu_impl() const
        {
            std::unique_ptr<windows_menu_details_type> p_menu{ std::make_unique<windows_menu_details_type>(
                get_and_increment_id(),
                reinterpret_cast<std::intptr_t>(::CreatePopupMenu()),
                reinterpret_cast<std::intptr_t>(nullptr)) };
            if (!p_menu->handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a popup menu." }));
            }

            return std::move(p_menu);
        }

        menu_details_ptr_type create_menu_impl() const
        {
            return std::make_unique<windows_menu_details_type>(
                get_and_increment_id(),
                reinterpret_cast<std::intptr_t>(nullptr),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        void set_enabled_impl(gui::menu::menu_base& menu, const bool enabled) const
        {
            auto& details = static_cast<windows_menu_details_type&>(menu.details());
            if (!details.parent_handle)
                return;

            set_menu_info_style(
                reinterpret_cast<::HMENU>(details.parent_handle),
                static_cast<::UINT>(details.id),
                enabled,
                menu.state());
        }

        void set_state_impl(gui::menu::menu_base& menu, const state_type state) const
        {
            auto& details = static_cast<windows_menu_details_type&>(menu.details());
            if (!details.parent_handle)
                return;

            set_menu_info_style(
                reinterpret_cast<::HMENU>(details.parent_handle),
                static_cast<::UINT>(details.id),
                menu.enabled(),
                static_cast<gui::menu::menu_base::state_type>(state));
        }

        shortcut_key_table_details_ptr_type create_shortcut_key_table_impl() const
        {
            return std::make_unique<windows_shortcut_key_table_details_type>();
        }

        shortcut_key_table_details_ptr_type create_shortcut_key_table_impl(const gui::menu::menu_base& root_menu) const
        {
            std::vector<::ACCEL> accelerators{};
            for (auto i = root_menu.recursive_begin(); i != root_menu.recursive_end(); ++i)
            {
                if (!i->has_shortcut_key())
                    continue;

                accelerators.push_back(to_accel(*i));
            }
            if (accelerators.empty())
                return {};

            const auto accelerator_table_handle =
                ::CreateAcceleratorTableW(accelerators.data(), static_cast<int>(accelerators.size()));
            if (!accelerator_table_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a shortcut key table." }));
            }

            return std::make_unique<windows_shortcut_key_table_details_type>(
                reinterpret_cast<std::intptr_t>(accelerator_table_handle));
        }

        void insert_menu_impl(gui::menu::abstract_popup& popup_menu, const iterator& offset, gui::menu::menu_base& menu)
            const
        {
            auto& details = static_cast<windows_menu_details_type&>(menu.details());
            assert(!details.parent_handle);

            ::MENUITEMINFOW menu_info{};
            menu_info.cbSize = sizeof(::MENUITEMINFO);
            auto duplicated_text = make_text(menu);
            static_cast<const windows_style_tag&>(menu.style())
                .set_style(details, menu_info, duplicated_text, menu.enabled(), menu.state());

            auto&      popup_details = static_cast<windows_menu_details_type&>(popup_menu.details());
            const auto result = ::InsertMenuItem(
                reinterpret_cast<::HMENU>(popup_details.handle),
                static_cast<::UINT>(std::distance<iterator>(popup_menu.begin(), offset)),
                TRUE,
                &menu_info);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't insert a native menu." }));
            }

            details.parent_handle = popup_details.handle;
        }

        void erase_menus_impl(gui::menu::abstract_popup& popup_menu, const iterator& first, const iterator& last) const
        {
            for (auto i = first; i != last; ++i)
                erase_menu(popup_menu, i);
        }

        const style_tag& menu_bar_style_impl() const
        {
            static const menu_bar_style_tag singleton;
            return singleton;
        }

        const style_tag& popup_menu_style_impl() const
        {
            static const popup_menu_style_tag singleton;
            return singleton;
        }

        const style_tag& menu_command_style_impl() const
        {
            static const menu_command_style_tag singleton;
            return singleton;
        }

        const style_tag& menu_separator_style_impl() const
        {
            static const menu_separator_style_tag singleton;
            return singleton;
        }


    private:
        // types

        using native_menu_encoder_type =
            text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::wstring>>;

        struct windows_style_tag : public style_tag
        {
            virtual ~windows_style_tag() = default;

            virtual void set_style(
                const windows_menu_details_type& details,
                ::MENUITEMINFOW&                 menu_info,
                std::vector<::WCHAR>&            text,
                bool                             enabled,
                gui::menu::menu_base::state_type state) const = 0;
        };

        struct menu_bar_style_tag : public windows_style_tag
        {
            virtual ~menu_bar_style_tag() = default;

            virtual void set_style(
                TETENGO2_STDALT_MAYBE_UNUSED const windows_menu_details_type& details,
                TETENGO2_STDALT_MAYBE_UNUSED ::MENUITEMINFOW&                 menu_info,
                TETENGO2_STDALT_MAYBE_UNUSED std::vector<::WCHAR>& text,
                TETENGO2_STDALT_MAYBE_UNUSED bool                  enabled,
                TETENGO2_STDALT_MAYBE_UNUSED gui::menu::menu_base::state_type state) const override
            {
                assert(false);
                BOOST_THROW_EXCEPTION((std::logic_error{ "A menu bar cannot be inserted." }));
            }
        };

        struct popup_menu_style_tag : public windows_style_tag
        {
            virtual ~popup_menu_style_tag() = default;

            virtual void set_style(
                const windows_menu_details_type& details,
                ::MENUITEMINFOW&                 menu_info,
                std::vector<::WCHAR>&            text,
                bool                             enabled,
                gui::menu::menu_base::state_type state) const override
            {
                menu_info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING | MIIM_ID | MIIM_SUBMENU;

                menu_info.fType = 0;
                menu_info.fType |= state == gui::menu::menu_base::state_type::selected ? MFT_RADIOCHECK : 0;

                menu_info.fState = 0;
                menu_info.fState |= enabled ? MFS_ENABLED : MFS_DISABLED;
                menu_info.fState |= state == gui::menu::menu_base::state_type::checked ||
                                            state == gui::menu::menu_base::state_type::selected ?
                                        MFS_CHECKED :
                                        MFS_UNCHECKED;

                menu_info.dwTypeData = text.data();
                menu_info.cch = static_cast<::UINT>(text.size() - 1);
                menu_info.wID = static_cast<::UINT>(details.id);
                menu_info.hSubMenu = reinterpret_cast<::HMENU>(details.handle);
            }
        };

        struct menu_command_style_tag : public windows_style_tag
        {
            virtual ~menu_command_style_tag() = default;

            virtual void set_style(
                const windows_menu_details_type& details,
                ::MENUITEMINFOW&                 menu_info,
                std::vector<::WCHAR>&            text,
                bool                             enabled,
                gui::menu::menu_base::state_type state) const override
            {
                menu_info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING | MIIM_ID;

                menu_info.fType = 0;
                menu_info.fType |= state == gui::menu::menu_base::state_type::selected ? MFT_RADIOCHECK : 0;

                menu_info.fState = 0;
                menu_info.fState |= enabled ? MFS_ENABLED : MFS_DISABLED;
                menu_info.fState |= state == gui::menu::menu_base::state_type::checked ||
                                            state == gui::menu::menu_base::state_type::selected ?
                                        MFS_CHECKED :
                                        MFS_UNCHECKED;

                menu_info.dwTypeData = text.data();
                menu_info.cch = static_cast<::UINT>(text.size() - 1);
                menu_info.wID = static_cast<::UINT>(details.id);
            }
        };

        struct menu_separator_style_tag : public windows_style_tag
        {
            virtual ~menu_separator_style_tag() = default;

            virtual void set_style(
                TETENGO2_STDALT_MAYBE_UNUSED const windows_menu_details_type& details,
                ::MENUITEMINFOW&                                              menu_info,
                TETENGO2_STDALT_MAYBE_UNUSED std::vector<::WCHAR>& text,
                TETENGO2_STDALT_MAYBE_UNUSED bool                  enabled,
                TETENGO2_STDALT_MAYBE_UNUSED gui::menu::menu_base::state_type state) const override
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

        static void set_menu_info_style(
            const ::HMENU                          menu_handle,
            const ::UINT                           menu_id,
            const bool                             enabled,
            const gui::menu::menu_base::state_type state)
        {
            ::MENUITEMINFOW menu_info{};
            menu_info.cbSize = sizeof(::MENUITEMINFOW);
            const auto get_result = ::GetMenuItemInfoW(menu_handle, menu_id, FALSE, &menu_info);
            if (get_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get a menu item info." }));
            }

            menu_info.fMask = MIIM_FTYPE | MIIM_STATE;

            menu_info.fType &= ~MFT_RADIOCHECK;
            menu_info.fType |= state == gui::menu::menu_base::state_type::selected ? MFT_RADIOCHECK : 0;

            menu_info.fState &= ~(MFS_ENABLED | MFS_DISABLED | MFS_CHECKED | MFS_UNCHECKED);
            menu_info.fState |= enabled ? MFS_ENABLED : MFS_DISABLED;
            menu_info.fState |= state == gui::menu::menu_base::state_type::checked ||
                                        state == gui::menu::menu_base::state_type::selected ?
                                    MFS_CHECKED :
                                    MFS_UNCHECKED;

            const auto set_result = ::SetMenuItemInfoW(menu_handle, menu_id, FALSE, &menu_info);
            if (set_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't set a menu item info." }));
            }
        }

        static ::ACCEL to_accel(const gui::menu::menu_base& menu)
        {
            const auto& shortcut_key = menu.get_shortcut_key();

            ::ACCEL accel{};

            if (shortcut_key.shift())
                accel.fVirt |= FSHIFT;
            if (shortcut_key.control())
                accel.fVirt |= FCONTROL;
            if (shortcut_key.meta())
                accel.fVirt |= FALT;
            accel.fVirt |= FVIRTKEY;

            accel.key = static_cast<::WORD>(shortcut_key.key().code());

            accel.cmd = static_cast<::WORD>(static_cast<const windows_menu_details_type&>(menu.details()).id);

            return accel;
        }

        static std::vector<::WCHAR> make_text(const gui::menu::menu_base& menu)
        {
            auto text = menu.text();
            if (menu.has_shortcut_key())
            {
                text += type_list::string_type{ TETENGO2_TEXT("\t") };
                text += menu.get_shortcut_key().to_string();
            }
            const auto native_string = native_menu_encoder().encode(text);

            std::vector<::WCHAR> duplicated{};
            duplicated.reserve(native_string.length() + 1);
            std::copy(native_string.begin(), native_string.end(), std::back_inserter(duplicated));
            duplicated.push_back(L'\0');

            return duplicated;
        }

        static const native_menu_encoder_type& native_menu_encoder()
        {
            static const native_menu_encoder_type singleton;
            return singleton;
        }

        static void erase_menu(gui::menu::abstract_popup& popup_menu, const iterator& offset)
        {
            auto& popup_details = static_cast<windows_menu_details_type&>(popup_menu.details());
            auto& offset_details = static_cast<windows_menu_details_type&>(offset->details());
            assert(popup_details.handle);
            assert(offset_details.parent_handle);

            const auto result = ::RemoveMenu(
                reinterpret_cast<::HMENU>(popup_details.handle),
                static_cast<::UINT>(std::distance<iterator>(popup_menu.begin(), offset)),
                MF_BYPOSITION);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't remove a native menu." }));
            }

            offset_details.parent_handle = reinterpret_cast<std::intptr_t>(nullptr);
        }
    };


    menu::windows_menu_details_type::windows_menu_details_type(
        const type_list::size_type id,
        const std::intptr_t        handle,
        const std::intptr_t        parent_handle)
    : id{ id }, handle{ handle }, parent_handle{ parent_handle }
    {}

    menu::windows_menu_details_type::~windows_menu_details_type() noexcept
    {
        const ::HMENU menu_handle = reinterpret_cast<::HMENU>(handle);
        if (::IsMenu(menu_handle))
            ::DestroyMenu(menu_handle);
    };

    menu::windows_shortcut_key_table_details_type::windows_shortcut_key_table_details_type()
    : m_accelerator_table_handle{}
    {}

    menu::windows_shortcut_key_table_details_type::windows_shortcut_key_table_details_type(
        std::intptr_t accelerator_table_handle)
    : m_accelerator_table_handle{ accelerator_table_handle }
    {}

    menu::windows_shortcut_key_table_details_type::~windows_shortcut_key_table_details_type() noexcept
    {
        const ::HACCEL accelerator_handle = reinterpret_cast<::HACCEL>(m_accelerator_table_handle);
        if (accelerator_handle)
            ::DestroyAcceleratorTable(accelerator_handle);
    }

    std::intptr_t menu::windows_shortcut_key_table_details_type::get() const
    {
        return m_accelerator_table_handle;
    }

    const menu& menu::instance()
    {
        static const menu singleton;
        return singleton;
    }

    menu::~menu() = default;

    menu::menu() : m_p_impl{ std::make_unique<impl>() } {}

    menu::menu_details_ptr_type menu::create_menu_bar_impl() const
    {
        return m_p_impl->create_menu_bar_impl();
    }

    menu::menu_details_ptr_type menu::create_popup_menu_impl() const
    {
        return m_p_impl->create_popup_menu_impl();
    }

    menu::menu_details_ptr_type menu::create_menu_impl() const
    {
        return m_p_impl->create_menu_impl();
    }

    void menu::set_enabled_impl(gui::menu::menu_base& menu, bool enabled) const
    {
        m_p_impl->set_enabled_impl(menu, enabled);
    }

    void menu::set_state_impl(gui::menu::menu_base& menu, state_type state) const
    {
        m_p_impl->set_state_impl(menu, state);
    }

    menu::shortcut_key_table_details_ptr_type menu::create_shortcut_key_table_impl() const
    {
        return m_p_impl->create_shortcut_key_table_impl();
    }

    menu::shortcut_key_table_details_ptr_type
    menu::create_shortcut_key_table_impl(const gui::menu::menu_base& root_menu) const
    {
        return m_p_impl->create_shortcut_key_table_impl(root_menu);
    }

    void menu::insert_menu_impl(
        gui::menu::abstract_popup& popup_menu,
        const iterator&            offset,
        gui::menu::menu_base&      menu) const
    {
        m_p_impl->insert_menu_impl(popup_menu, offset, menu);
    }

    void
    menu::erase_menus_impl(gui::menu::abstract_popup& popup_menu, const iterator& first, const iterator& last) const
    {
        m_p_impl->erase_menus_impl(popup_menu, first, last);
    }

    const menu::style_tag& menu::menu_bar_style_impl() const
    {
        return m_p_impl->menu_bar_style_impl();
    }

    const menu::style_tag& menu::popup_menu_style_impl() const
    {
        return m_p_impl->popup_menu_style_impl();
    }

    const menu::style_tag& menu::menu_command_style_impl() const
    {
        return m_p_impl->menu_command_style_impl();
    }

    const menu::style_tag& menu::menu_separator_style_impl() const
    {
        return m_p_impl->menu_separator_style_impl();
    }
}
