/*! \file
    \brief The definition of tetengo2::detail::windows::widget.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#// prevent sort by ClangFormat
#include <CommCtrl.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/icon.h>
#include <tetengo2/detail/windows/menu.h>
#include <tetengo2/detail/windows/message_handler.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/alert.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/dropdown_box.h>
#include <tetengo2/gui/widget/list_box.h>
#include <tetengo2/gui/widget/progress_bar.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>


namespace tetengo2::detail::windows {
    namespace detail {
        // types

        using native_widget_encoder_type =
            text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::wstring>>;

        const native_widget_encoder_type& native_widget_encoder()
        {
            static const native_widget_encoder_type singleton;
            return singleton;
        }
    }


    class widget::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = widget::size_type;

        using string_type = widget::string_type;

        using scroll_bar_style_type = widget::scroll_bar_style_type;

        using window_state_type = widget::window_state_type;

        using menu_base_type = widget::menu_base_type;

        using progress_bar_state_type = widget::progress_bar_state_type;

        using widget_details_type = widget::widget_details_type;

        using widget_details_ptr_type = widget::widget_details_ptr_type;


        // static functions

        static const widget& instance()
        {
            static const widget singleton;
            return singleton;
        }

        static const std::wstring& property_key_for_cpp_instance()
        {
            static const std::wstring singleton{ L"C++ Instance" };
            return singleton;
        }

        static gui::widget::widget* p_widget_from(const std::intptr_t widget_handle)
        {
            return reinterpret_cast<gui::widget::widget*>(
                ::GetPropW(reinterpret_cast<::HWND>(widget_handle), property_key_for_cpp_instance().c_str()));
        }


        // functions

        widget_details_ptr_type
        create_button_impl(gui::widget::widget& parent, const bool is_default, const bool is_cancel) const
        {
            assert(!is_default || !is_cancel);

            const ::DWORD create_window_style = is_default ? WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON :
                                                             WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON;
            ::HMENU id = nullptr;
            if (is_default)
            {
                if (::GetDlgItem(
                        reinterpret_cast<::HWND>(as_windows_widget_details(parent.root_ancestor().details()).handle),
                        IDOK))
                    BOOST_THROW_EXCEPTION((std::invalid_argument{ "Default button already exists." }));
                id = reinterpret_cast<::HMENU>(IDOK);
            }
            else if (is_cancel)
            {
                if (::GetDlgItem(
                        reinterpret_cast<::HWND>(as_windows_widget_details(parent.root_ancestor().details()).handle),
                        IDCANCEL))
                    BOOST_THROW_EXCEPTION((std::invalid_argument{ "Cancel button already exists." }));
                id = reinterpret_cast<::HMENU>(IDCANCEL);
            }

            const auto window_handle = ::CreateWindowExW(
                0,
                WC_BUTTONW,
                L"tetengo2_button",
                create_window_style,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                id,
                ::GetModuleHandle(nullptr),
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a button!" }));
            }

            const auto p_original_window_procedure = replace_window_procedure(window_handle);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(p_original_window_procedure),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type create_custom_control_impl(
            gui::widget::widget&        parent,
            const bool                  border,
            const scroll_bar_style_type scroll_bar_style) const
        {
            const auto instance_handle = ::GetModuleHandle(nullptr);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get the instance handle!" }));
            }

            if (!window_class_is_registered(custom_control_class_name(), instance_handle))
                register_window_class_for_custom_control(instance_handle);

            const ::DWORD ex_style = border ? WS_EX_CLIENTEDGE : 0;
            const auto    window_handle = ::CreateWindowExW(
                ex_style,
                custom_control_class_name().c_str(),
                L"",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | WS_CLIPCHILDREN |
                    window_style_for_scroll_bars(
                        static_cast<gui::widget::widget::scroll_bar_style_type>(scroll_bar_style)),
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                nullptr,
                instance_handle,
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a custom control!" }));
            }

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(&::DefWindowProcW),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type create_dialog_impl(gui::widget::widget* const p_parent, const bool file_droppable) const
        {
            const auto instance_handle = ::GetModuleHandle(nullptr);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get the instance handle!" }));
            }

            if (!window_class_is_registered(dialog_class_name(), instance_handle))
                register_window_class_for_dialog(instance_handle);

            ::DWORD ex_style = WS_EX_CONTEXTHELP | WS_EX_DLGMODALFRAME;
            if (file_droppable)
                ex_style |= WS_EX_ACCEPTFILES;
            const auto window_handle = ::CreateWindowExW(
                ex_style,
                dialog_class_name().c_str(),
                dialog_class_name().c_str(),
                WS_POPUPWINDOW | WS_CAPTION,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                p_parent ? reinterpret_cast<::HWND>(as_windows_widget_details(p_parent->details()).handle) :
                           HWND_DESKTOP,
                nullptr,
                instance_handle,
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a dialog!" }));
            }

            delete_system_menus(window_handle);
            if (file_droppable)
                ::DragAcceptFiles(window_handle, TRUE);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(&::DefWindowProcW),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type create_dropdown_box_impl(gui::widget::widget& parent) const
        {
            const auto window_handle = ::CreateWindowExW(
                WS_EX_CLIENTEDGE,
                WC_COMBOBOXW,
                L"",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                nullptr,
                ::GetModuleHandle(nullptr),
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a dropdown box!" }));
            }

            const auto p_original_window_procedure = replace_window_procedure(window_handle);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(p_original_window_procedure),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type create_image_impl(gui::widget::widget& parent) const
        {
            const auto window_handle = ::CreateWindowExW(
                0,
                WC_STATICW,
                L"tetengo2_image",
                WS_CHILD | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                nullptr,
                ::GetModuleHandle(nullptr),
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create an image!" }));
            }

            const auto p_original_window_procedure = replace_window_procedure(window_handle);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(p_original_window_procedure),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type create_label_impl(gui::widget::widget& parent) const
        {
            const auto window_handle = ::CreateWindowExW(
                0,
                WC_STATICW,
                L"tetengo2_label",
                WS_CHILD | WS_VISIBLE | SS_NOTIFY,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                nullptr,
                ::GetModuleHandle(nullptr),
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a label!" }));
            }

            const auto p_original_window_procedure = replace_window_procedure(window_handle);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(p_original_window_procedure),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type
        create_list_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
        {
            const auto window_handle = ::CreateWindowExW(
                WS_EX_CLIENTEDGE,
                WC_LISTBOXW,
                L"",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | LBS_NOTIFY |
                    window_style_for_scroll_bars(
                        static_cast<gui::widget::widget::scroll_bar_style_type>(scroll_bar_style)),
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                nullptr,
                ::GetModuleHandle(nullptr),
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a list box!" }));
            }

            const auto p_original_window_procedure = replace_window_procedure(window_handle);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(p_original_window_procedure),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type
        create_picture_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
        {
            const auto instance_handle = ::GetModuleHandle(nullptr);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get the instance handle!" }));
            }

            if (!window_class_is_registered(picture_box_class_name(), instance_handle))
                register_window_class_for_picture_box(instance_handle);

            const auto window_handle = ::CreateWindowExW(
                WS_EX_CLIENTEDGE,
                picture_box_class_name().c_str(),
                L"",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE |
                    window_style_for_scroll_bars(
                        static_cast<gui::widget::widget::scroll_bar_style_type>(scroll_bar_style)),
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                nullptr,
                instance_handle,
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a picture box!" }));
            }

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(&::DefWindowProcW),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type create_progress_bar_impl(gui::widget::widget& parent) const
        {
            const auto window_handle = ::CreateWindowExW(
                0,
                PROGRESS_CLASSW,
                L"",
                WS_CHILD | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                nullptr,
                ::GetModuleHandle(nullptr),
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a progress bar!" }));
            }

            const auto p_original_window_procedure = replace_window_procedure(window_handle);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(p_original_window_procedure),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type
        create_text_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
        {
            const auto window_handle = ::CreateWindowExW(
                WS_EX_CLIENTEDGE,
                WC_EDITW,
                L"",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL |
                    window_style_for_scroll_bars(
                        static_cast<gui::widget::widget::scroll_bar_style_type>(scroll_bar_style)),
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle),
                nullptr,
                ::GetModuleHandle(nullptr),
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a text box!" }));
            }

            const auto p_original_window_procedure = replace_window_procedure(window_handle);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(p_original_window_procedure),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        widget_details_ptr_type create_window_impl(
            gui::widget::widget* const  p_parent,
            const scroll_bar_style_type scroll_bar_style,
            const bool                  file_droppable) const
        {
            const auto instance_handle = ::GetModuleHandle(nullptr);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get the instance handle!" }));
            }

            if (!window_class_is_registered(window_class_name(), instance_handle))
                register_window_class_for_window(instance_handle);

            ::DWORD ex_style =
                WS_EX_APPWINDOW |
                window_style_for_scroll_bars(static_cast<gui::widget::widget::scroll_bar_style_type>(scroll_bar_style));
            if (file_droppable)
                ex_style |= WS_EX_ACCEPTFILES;
            const auto window_handle = ::CreateWindowExW(
                ex_style,
                window_class_name().c_str(),
                window_class_name().c_str(),
                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                p_parent ? reinterpret_cast<::HWND>(as_windows_widget_details(p_parent->details()).handle) :
                           HWND_DESKTOP,
                nullptr,
                instance_handle,
                nullptr);
            if (!window_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't create a window!" }));
            }

            if (file_droppable)
                ::DragAcceptFiles(window_handle, TRUE);

            return std::make_unique<windows_widget_details_type>(
                reinterpret_cast<std::intptr_t>(window_handle),
                reinterpret_cast<std::intptr_t>(&::DefWindowProcW),
                reinterpret_cast<std::intptr_t>(nullptr));
        }

        void associate_to_native_window_system_impl(gui::widget::widget& widget) const
        {
            auto& widget_details = as_windows_widget_details(widget.details());
            assert(
                !::GetPropW(reinterpret_cast<::HWND>(widget_details.handle), property_key_for_cpp_instance().c_str()));
            const auto result = ::SetPropW(
                reinterpret_cast<::HWND>(widget_details.handle),
                property_key_for_cpp_instance().c_str(),
                reinterpret_cast<::HANDLE>(&widget));
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't set C++ instance." }));
            }
        }

        bool has_parent_impl(const gui::widget::widget& widget) const
        {
            return ::GetParent(reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle)) != nullptr;
        }

        gui::widget::widget& parent_impl(const gui::widget::widget& widget) const
        {
            const auto parent_handle =
                ::GetParent(reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle));
            if (!parent_handle)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "The widget has no parent." }));
            }

            auto* const p_parent = p_widget_from(reinterpret_cast<std::intptr_t>(parent_handle));
            assert(p_parent);
            return *p_parent;
        }

        gui::widget::widget& root_ancestor_impl(const gui::widget::widget& widget) const
        {
            const auto root_ancestor_handle =
                ::GetAncestor(reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), GA_ROOT);
            if (!root_ancestor_handle)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "The widget has no root ancestor." }));
            }

            auto* const p_root_ancestor = p_widget_from(reinterpret_cast<std::intptr_t>(root_ancestor_handle));
            assert(p_root_ancestor);
            return *p_root_ancestor;
        }

        void set_enabled_impl(gui::widget::widget& widget, const bool enabled) const
        {
            ::EnableWindow(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), enabled ? TRUE : FALSE);
        }

        bool enabled_impl(const gui::widget::widget& widget) const
        {
            return ::IsWindowEnabled(reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle)) ==
                   TRUE;
        }

        void set_visible_impl(gui::widget::widget& widget, const bool visible) const
        {
            const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
            int        command = SW_HIDE;
            if (visible)
            {
                if (visible_impl(widget))
                {
                    if (::IsZoomed(widget_handle))
                        command = SW_SHOWMAXIMIZED;
                    else if (::IsIconic(widget_handle))
                        command = SW_MINIMIZE;
                    else
                        command = SW_RESTORE;
                }
                else
                {
                    command = as_windows_widget_details(widget.details()).window_state_when_hidden;
                }
            }
            else
            {
                if (visible_impl(widget))
                {
                    if (::IsZoomed(widget_handle))
                        as_windows_widget_details(widget.details()).window_state_when_hidden = SW_SHOWMAXIMIZED;
                    else if (::IsIconic(widget_handle))
                        as_windows_widget_details(widget.details()).window_state_when_hidden = SW_MINIMIZE;
                    else
                        as_windows_widget_details(widget.details()).window_state_when_hidden = SW_RESTORE;
                }
            }
            ::ShowWindow(widget_handle, command);
            if (visible)
                ::UpdateWindow(widget_handle);
        }

        bool visible_impl(const gui::widget::widget& widget) const
        {
            return ::IsWindowVisible(reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle)) ==
                   TRUE;
        }

        void set_window_state_impl(gui::widget::widget& widget, const window_state_type state) const
        {
            switch (static_cast<gui::widget::abstract_window::window_state_type>(state))
            {
            case gui::widget::abstract_window::window_state_type::normal:
                as_windows_widget_details(widget.details()).window_state_when_hidden = SW_RESTORE;
                break;
            case gui::widget::abstract_window::window_state_type::maximized:
                as_windows_widget_details(widget.details()).window_state_when_hidden = SW_SHOWMAXIMIZED;
                break;
            default:
                assert(
                    static_cast<gui::widget::abstract_window::window_state_type>(state) ==
                    gui::widget::abstract_window::window_state_type::minimized);
                as_windows_widget_details(widget.details()).window_state_when_hidden = SW_MINIMIZE;
                break;
            }

            if (!visible_impl(widget))
                return;

            ::WINDOWPLACEMENT window_placement{};
            window_placement.length = sizeof(::WINDOWPLACEMENT);
            const auto get_result = ::GetWindowPlacement(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), &window_placement);
            if (get_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get window placement." }));
            }

            window_placement.showCmd = as_windows_widget_details(widget.details()).window_state_when_hidden;

            const auto set_result = ::SetWindowPlacement(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), &window_placement);
            if (set_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't set window placement." }));
            }
        }

        window_state_type window_state_impl(const gui::widget::widget& widget) const
        {
            if (visible_impl(widget))
            {
                const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
                if (::IsZoomed(widget_handle))
                    return static_cast<window_state_type>(gui::widget::abstract_window::window_state_type::maximized);
                else if (::IsIconic(widget_handle))
                    return static_cast<window_state_type>(gui::widget::abstract_window::window_state_type::minimized);
                else
                    return static_cast<window_state_type>(gui::widget::abstract_window::window_state_type::normal);
            }
            else
            {
                switch (as_windows_widget_details(widget.details()).window_state_when_hidden)
                {
                case SW_RESTORE:
                    return static_cast<window_state_type>(gui::widget::abstract_window::window_state_type::normal);
                case SW_SHOWMAXIMIZED:
                    return static_cast<window_state_type>(gui::widget::abstract_window::window_state_type::maximized);
                default:
                    assert(as_windows_widget_details(widget.details()).window_state_when_hidden == SW_MINIMIZE);
                    return static_cast<window_state_type>(gui::widget::abstract_window::window_state_type::minimized);
                }
            }
        }

        void move_impl(
            gui::widget::widget&                  widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const
        {
            const auto result = ::MoveWindow(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle),
                static_cast<int>(position.left().to_pixels()),
                static_cast<int>(position.top().to_pixels()),
                static_cast<int>(dimension.width().to_pixels()),
                static_cast<int>(dimension.height().to_pixels()),
                visible_impl(widget) ? TRUE : FALSE);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't move the widget." }));
            }
        }

        gui::type_list::position_type position_impl(const gui::widget::widget& widget) const
        {
            ::RECT rectangle{};
            if (::GetWindowRect(
                    reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get window rectangle." }));
            }

            return { gui::type_list::position_unit_type::from_pixels(rectangle.left),
                     gui::type_list::position_unit_type::from_pixels(rectangle.top) };
        }

        gui::type_list::position_type
        dialog_position_impl(const gui::widget::widget& widget, const gui::widget::widget& parent) const
        {
            ::POINT    point{};
            const auto x_margin = ::GetSystemMetrics(SM_CYFIXEDFRAME) * 2;
            const auto y_margin = ::GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
            if (::ClientToScreen(
                    reinterpret_cast<::HWND>(as_windows_widget_details(parent.details()).handle), &point) == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "Can't get parent window client area position." }));
            }
            point.x += x_margin;
            point.y += y_margin;

            const auto    monitor_handle = ::MonitorFromPoint(point, MONITOR_DEFAULTTONEAREST);
            ::MONITORINFO monitor_info{};
            monitor_info.cbSize = sizeof(::MONITORINFO);
            if (::GetMonitorInfoW(monitor_handle, &monitor_info) == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "Can't get monitor information." }));
            }

            const auto widget_dimension = widget.dimension();
            const auto widget_width = static_cast<::LONG>(widget_dimension.width().to_pixels());
            const auto widget_height = static_cast<::LONG>(widget_dimension.height().to_pixels());
            if (point.x + widget_width + x_margin > monitor_info.rcWork.right)
                point.x = monitor_info.rcWork.right - widget_width - x_margin;
            if (point.y + widget_height + y_margin > monitor_info.rcWork.bottom)
                point.y = monitor_info.rcWork.bottom - widget_height - y_margin;
            if (point.x - x_margin < monitor_info.rcWork.left)
                point.x = monitor_info.rcWork.left + x_margin;
            if (point.y - y_margin < monitor_info.rcWork.top)
                point.y = monitor_info.rcWork.top + y_margin;

            return { gui::type_list::position_unit_type::from_pixels(point.x),
                     gui::type_list::position_unit_type::from_pixels(point.y) };
        }

        gui::type_list::dimension_type dimension_impl(const gui::widget::widget& widget) const
        {
            ::RECT rectangle{};
            if (::GetWindowRect(
                    reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get window rectangle." }));
            }

            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            return { gui::type_list::dimension_unit_type::from_pixels(rectangle.right - rectangle.left),
                     gui::type_list::dimension_unit_type::from_pixels(rectangle.bottom - rectangle.top) };
        }

        void set_client_dimension_impl(
            gui::widget::widget&                  widget,
            const gui::type_list::dimension_type& client_dimension) const
        {
            const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
            const auto pos = position_impl(widget);
            const auto window_style = ::GetWindowLongPtrW(widget_handle, GWL_STYLE);
            const auto extended_window_style = ::GetWindowLongPtrW(widget_handle, GWL_EXSTYLE);
            const auto left = static_cast<::LONG>(pos.left().to_pixels());
            const auto top = static_cast<::LONG>(pos.top().to_pixels());
            const auto width = static_cast<::LONG>(client_dimension.width().to_pixels());
            const auto height = static_cast<::LONG>(client_dimension.height().to_pixels());
            ::RECT     rectangle{ left, top, left + width, top + height };
            if (::AdjustWindowRectEx(
                    &rectangle,
                    static_cast<::DWORD>(window_style),
                    FALSE,
                    static_cast<::DWORD>(extended_window_style)) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't adjust window rectangle." }));
            }

            assert(rectangle.right - rectangle.left > 0);
            assert(rectangle.bottom - rectangle.top > 0);
            const auto result = ::MoveWindow(
                widget_handle,
                rectangle.left,
                rectangle.top,
                rectangle.right - rectangle.left,
                rectangle.bottom - rectangle.top,
                visible_impl(widget) ? TRUE : FALSE);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{
                    std::error_code{ static_cast<int>(::GetLastError()), win32_category() }, "Can't move window." }));
            }
        }

        gui::type_list::dimension_type client_dimension_impl(const gui::widget::widget& widget) const
        {
            ::RECT rectangle{};
            if (::GetClientRect(
                    reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get client rectangle." }));
            }

            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            return { gui::type_list::dimension_unit_type::from_pixels(rectangle.right - rectangle.left),
                     gui::type_list::dimension_unit_type::from_pixels(rectangle.bottom - rectangle.top) };
        }

        gui::type_list::dimension_type normal_dimension_impl(const gui::widget::widget& widget) const
        {
            ::WINDOWPLACEMENT window_placement{};
            window_placement.length = sizeof(::WINDOWPLACEMENT);
            const auto get_result = ::GetWindowPlacement(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), &window_placement);
            if (get_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get window placement." }));
            }

            const auto& rectangle = window_placement.rcNormalPosition;
            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            return { gui::type_list::dimension_unit_type::from_pixels(rectangle.right - rectangle.left),
                     gui::type_list::dimension_unit_type::from_pixels(rectangle.bottom - rectangle.top) };
        }

        void set_text_impl(gui::widget::widget& widget, string_type text) const
        {
            const auto result = ::SetWindowTextW(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle),
                detail::native_widget_encoder().encode(std::move(text)).c_str());
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{
                    std::error_code{ static_cast<int>(::GetLastError()), win32_category() }, "Can't set text!" }));
            }
        }

        string_type text_impl(const gui::widget::widget& widget) const
        {
            const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
            const auto length = ::GetWindowTextLengthW(widget_handle);
            if (length == 0)
                return type_list::string_type{};

            std::vector<wchar_t> text(length + 1, L'\0');
            ::GetWindowTextW(widget_handle, text.data(), length + 1);

            return detail::native_widget_encoder().decode(std::wstring{ text.begin(), text.begin() + length });
        }

        void set_font_impl(gui::widget::widget& widget, const gui::drawing::font& font) const
        {
            const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
            const auto previous_font_handle =
                reinterpret_cast<::HFONT>(::SendMessageW(widget_handle, WM_GETFONT, 0, 0));

            ::LOGFONTW log_font{ -static_cast<::LONG>(font.size()),
                                 0,
                                 0,
                                 0,
                                 font.bold() ? FW_BOLD : FW_NORMAL,
                                 static_cast<::BYTE>(font.italic() ? TRUE : FALSE),
                                 static_cast<::BYTE>(font.underline() ? TRUE : FALSE),
                                 static_cast<::BYTE>(font.strikeout() ? TRUE : FALSE),
                                 static_cast<::BYTE>(DEFAULT_CHARSET),
                                 static_cast<::BYTE>(OUT_DEFAULT_PRECIS),
                                 static_cast<::BYTE>(CLIP_DEFAULT_PRECIS),
                                 static_cast<::BYTE>(DEFAULT_QUALITY),
                                 static_cast<::BYTE>(DEFAULT_PITCH | FF_DONTCARE),
                                 L"" };
            const auto font_family = detail::native_widget_encoder().encode(font.family());
            assert(font_family.length() < LF_FACESIZE);
            std::copy(font_family.begin(), font_family.end(), log_font.lfFaceName);
            log_font.lfFaceName[font_family.length()] = L'\0';
            const auto font_handle = ::CreateFontIndirectW(&log_font);
            if (!font_handle)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "Can't create font." }));
            }
            ::SendMessageW(widget_handle, WM_SETFONT, reinterpret_cast<::WPARAM>(font_handle), MAKELPARAM(TRUE, 0));

            if (previous_font_handle && ::DeleteObject(previous_font_handle) == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "Can't delete previous font." }));
            }
        }

        gui::drawing::font font_impl(const gui::widget::widget& widget) const
        {
            auto font_handle = reinterpret_cast<::HFONT>(::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), WM_GETFONT, 0, 0));
            if (!font_handle)
                font_handle = reinterpret_cast<::HFONT>(::GetStockObject(SYSTEM_FONT));

            ::LOGFONTW log_font;
            const auto byte_count = ::GetObjectW(font_handle, sizeof(::LOGFONTW), &log_font);
            if (byte_count == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "Can't get log font." }));
            }

            return gui::drawing::font{ detail::native_widget_encoder().decode(log_font.lfFaceName),
                                       static_cast<gui::drawing::font::size_type>(
                                           log_font.lfHeight < 0 ? -log_font.lfHeight : log_font.lfHeight),
                                       log_font.lfWeight >= FW_BOLD,
                                       log_font.lfItalic != FALSE,
                                       log_font.lfUnderline != FALSE,
                                       log_font.lfStrikeOut != FALSE };
        }

        std::vector<std::reference_wrapper<gui::widget::widget>> children_impl(gui::widget::widget& widget) const
        {
            std::vector<std::reference_wrapper<gui::widget::widget>> children{};

            ::EnumChildWindows(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle),
                enum_child_procedure,
                reinterpret_cast<::LPARAM>(&children));

            return children;
        }

        void repaint_impl(const gui::widget::widget& widget, const bool immediately) const
        {
            const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
            if (immediately)
            {
                if (::UpdateWindow(widget_handle) == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        (std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                            "Can't repaint a widget immediately." }));
                }
            }
            else
            {
                if (::InvalidateRect(widget_handle, nullptr, FALSE) == 0)
                {
                    BOOST_THROW_EXCEPTION((std::system_error{
                        std::error_code{ ERROR_FUNCTION_FAILED, win32_category() }, "Can't repaint a widget." }));
                }
            }
        }

        void repaint_partially_impl(
            const gui::widget::widget&            widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const
        {
            const auto   left = static_cast<::LONG>(position.left().to_pixels());
            const auto   top = static_cast<::LONG>(position.top().to_pixels());
            const auto   width = static_cast<::LONG>(dimension.width().to_pixels());
            const auto   height = static_cast<::LONG>(dimension.height().to_pixels());
            const ::RECT rectangle{ left, top, left + width, top + height };
            if (::InvalidateRect(
                    reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), &rectangle, FALSE) ==
                0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "Can't repaint a widget." }));
            }
        }

        void activate_impl(gui::widget::widget& widget) const
        {
            ::SetActiveWindow(reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle));
        }

        void set_icon_impl(gui::widget::widget& widget, const gui::icon* const p_icon) const
        {
            ::HICON icon_handle = nullptr;
            ::HICON small_icon_handle = nullptr;
            if (p_icon)
            {
                icon_handle = static_cast<const icon::icon_details_impl_type&>(p_icon->details()).big_icon_handle.get();
                small_icon_handle =
                    static_cast<const icon::icon_details_impl_type&>(p_icon->details()).small_icon_handle.get();
            }

            const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
            ::SendMessageW(widget_handle, WM_SETICON, ICON_BIG, reinterpret_cast<::LPARAM>(icon_handle));
            ::SendMessageW(widget_handle, WM_SETICON, ICON_SMALL, reinterpret_cast<::LPARAM>(small_icon_handle));
        }

        void set_menu_bar_impl(gui::widget::widget& widget, const menu_base_type* const p_menu = nullptr) const
        {
            const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
            const auto result = ::SetMenu(
                widget_handle,
                p_menu ? reinterpret_cast<::HMENU>(
                             static_cast<const menu::windows_menu_details_type&>(p_menu->details()).handle) :
                         reinterpret_cast<::HMENU>(nullptr));
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't set a menu bar." }));
            }

            if (p_menu && ::DrawMenuBar(widget_handle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't draw the menu bar." }));
            }
        }

        bool focusable_impl(const gui::widget::widget& widget) const
        {
            const auto style = ::GetWindowLongW(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), GWL_STYLE);
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get focusable status." }));
            }
            return (style & WS_TABSTOP) != 0;
        }

        void set_focusable_impl(gui::widget::widget& widget, const bool focusable) const
        {
            const auto widget_handle = reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle);
            auto       style = ::GetWindowLongW(widget_handle, GWL_STYLE);
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get focusable status." }));
            }

            auto unsigned_style = style;
            if (focusable)
                unsigned_style |= WS_TABSTOP;
            else
                unsigned_style &= ~WS_TABSTOP;
            style = unsigned_style;

            if (::SetWindowLongW(widget_handle, GWL_STYLE, style) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't set focusable status." }));
            }
        }

        void set_focus_impl(gui::widget::widget& widget) const
        {
            if (::SetFocus(reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle)) == nullptr)
            {
                BOOST_THROW_EXCEPTION((std::system_error{
                    std::error_code{ static_cast<int>(::GetLastError()), win32_category() }, "Can't set focus." }));
            }
        }

        bool read_only_impl(const gui::widget::widget& widget) const
        {
            const auto style = ::GetWindowLongW(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), GWL_STYLE);
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't get read-only status." }));
            }
            return (style & ES_READONLY) != 0;
        }

        void set_read_only_impl(gui::widget::widget& widget, const bool read_only) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle),
                EM_SETREADONLY,
                read_only ? TRUE : FALSE,
                0);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't set read-only status." }));
            }
        }

        void close_impl(gui::widget::widget& widget) const
        {
            const auto result = ::PostMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle), WM_CLOSE, 0, 0);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't close the widget." }));
            }
        }

        size_type dropdown_box_value_count_impl(const gui::widget::dropdown_box& dropdown_box) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(dropdown_box.details()).handle), CB_GETCOUNT, 0, 0);
            if (result == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain the dropdown box value count." }));
            }

            return result;
        }

        string_type dropdown_box_value_impl(const gui::widget::dropdown_box& dropdown_box, const size_type index) const
        {
            const auto dropdown_box_handle =
                reinterpret_cast<::HWND>(as_windows_widget_details(dropdown_box.details()).handle);
            const auto length = ::SendMessageW(dropdown_box_handle, CB_GETLBTEXTLEN, index, 0);
            if (length == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain the dropdown box value length." }));
            }

            std::vector<wchar_t> value(length + 1, 0);
            const auto           result =
                ::SendMessageW(dropdown_box_handle, CB_GETLBTEXT, index, reinterpret_cast<::LPARAM>(value.data()));
            if (length == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain the dropdown box value." }));
            }

            return detail::native_widget_encoder().decode(std::wstring{ value.data() });
        }

        void set_dropdown_box_value_impl(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value) const
        {
            erase_dropdown_box_value_impl(dropdown_box, index);
            insert_dropdown_box_value_impl(dropdown_box, index, std::move(value));
        }

        void insert_dropdown_box_value_impl(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(dropdown_box.details()).handle),
                CB_INSERTSTRING,
                index,
                reinterpret_cast<::LPARAM>(detail::native_widget_encoder().encode(std::move(value)).c_str()));
            if (result == CB_ERR || result == CB_ERRSPACE)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't append a dropdown box value." }));
            }
        }

        void erase_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(dropdown_box.details()).handle),
                CB_DELETESTRING,
                index,
                0);
            if (result == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't delete the old value." }));
            }
        }

        void clear_dropdown_box_impl(gui::widget::dropdown_box& dropdown_box) const
        {
            ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(dropdown_box.details()).handle),
                CB_RESETCONTENT,
                0,
                0);
        }

        tetengo2::stdalt::optional<size_type>
        selected_dropdown_box_value_index_impl(const gui::widget::dropdown_box& dropdown_box) const
        {
            auto index = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(dropdown_box.details()).handle), CB_GETCURSEL, 0, 0);
            return index != CB_ERR ? stdalt::make_optional<type_list::size_type>(std::move(index)) :
                                     TETENGO2_STDALT_NULLOPT;
        }

        void select_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(dropdown_box.details()).handle),
                CB_SETCURSEL,
                index,
                0);
            if (result == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't select a dropdown box value." }));
            }
        }

        size_type list_box_value_count_impl(const gui::widget::list_box& list_box) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(list_box.details()).handle), LB_GETCOUNT, 0, 0);
            if (result == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain the list box value count." }));
            }

            return result;
        }

        string_type list_box_value_impl(const gui::widget::list_box& list_box, const size_type index) const
        {
            const auto list_box_handle = reinterpret_cast<::HWND>(as_windows_widget_details(list_box.details()).handle);
            const auto length = ::SendMessageW(list_box_handle, LB_GETTEXTLEN, index, 0);
            if (length == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain the list box value length." }));
            }

            std::vector<wchar_t> value(length + 1, 0);
            const auto           result =
                ::SendMessageW(list_box_handle, LB_GETTEXT, index, reinterpret_cast<::LPARAM>(value.data()));
            if (length == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain the list box value." }));
            }

            return detail::native_widget_encoder().decode(std::wstring{ value.data() });
        }

        void set_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value) const
        {
            erase_list_box_value_impl(list_box, index);
            insert_list_box_value_impl(list_box, index, std::move(value));
        }

        void insert_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(list_box.details()).handle),
                LB_INSERTSTRING,
                index,
                reinterpret_cast<::LPARAM>(detail::native_widget_encoder().encode(std::move(value)).c_str()));
            if (result == LB_ERR || result == LB_ERRSPACE)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't append a list box value." }));
            }
        }

        void erase_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(list_box.details()).handle),
                LB_DELETESTRING,
                index,
                0);
            if (result == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't delete the old value." }));
            }
        }

        void clear_list_box_impl(gui::widget::list_box& list_box) const
        {
            ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(list_box.details()).handle), LB_RESETCONTENT, 0, 0);
        }

        tetengo2::stdalt::optional<size_type>
        selected_list_box_value_index_impl(const gui::widget::list_box& list_box) const
        {
            auto index = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(list_box.details()).handle), LB_GETCURSEL, 0, 0);
            return index != LB_ERR ? stdalt::make_optional<type_list::size_type>(std::move(index)) :
                                     TETENGO2_STDALT_NULLOPT;
        }

        void select_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(list_box.details()).handle), LB_SETCURSEL, index, 0);
            if (result == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't select a list box value." }));
            }
        }

        size_type progress_bar_goal_impl(const gui::widget::progress_bar& progress_bar) const
        {
            return ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(progress_bar.details()).handle),
                SBM_GETRANGE,
                FALSE,
                reinterpret_cast<::LPARAM>(nullptr));
        }

        void set_progress_bar_goal_impl(gui::widget::progress_bar& progress_bar, const size_type goal) const
        {
            const auto result = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(progress_bar.details()).handle),
                PBM_SETRANGE,
                0,
                MAKELPARAM(0, goal));
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't set progress bar range." }));
            }
        }

        size_type progress_bar_progress_impl(const gui::widget::progress_bar& progress_bar) const
        {
            return ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(progress_bar.details()).handle), PBM_GETPOS, 0, 0);
        }

        void set_progress_bar_progress_impl(gui::widget::progress_bar& progress_bar, const size_type progress) const
        {
            ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(progress_bar.details()).handle),
                PBM_SETPOS,
                progress,
                0);
        }

        progress_bar_state_type progress_bar_state_impl(const gui::widget::progress_bar& progress_bar) const
        {
            const auto state = ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(progress_bar.details()).handle), PBM_GETSTATE, 0, 0);
            switch (state)
            {
            case PBST_NORMAL:
                return static_cast<progress_bar_state_type>(gui::widget::progress_bar::state_type::running);
            case PBST_PAUSED:
                return static_cast<progress_bar_state_type>(gui::widget::progress_bar::state_type::pausing);
            default:
                assert(state == PBST_ERROR);
                return static_cast<progress_bar_state_type>(gui::widget::progress_bar::state_type::error);
            }
        }

        void
        set_progress_bar_state_impl(gui::widget::progress_bar& progress_bar, const progress_bar_state_type state) const
        {
            ::WPARAM native_state = PBST_ERROR;
            switch (static_cast<gui::widget::progress_bar::state_type>(state))
            {
            case gui::widget::progress_bar::state_type::running:
                native_state = PBST_NORMAL;
                break;
            case gui::widget::progress_bar::state_type::pausing:
                native_state = PBST_PAUSED;
                break;
            default:
                assert(
                    static_cast<gui::widget::progress_bar::state_type>(state) ==
                    gui::widget::progress_bar::state_type::error);
                native_state = PBST_ERROR;
                break;
            }
            ::SendMessageW(
                reinterpret_cast<::HWND>(as_windows_widget_details(progress_bar.details()).handle),
                PBM_SETSTATE,
                native_state,
                0);
        }

    private:
        // static functions

        static const windows_widget_details_type& as_windows_widget_details(const widget_details_type& base)
        {
            assert(dynamic_cast<const windows_widget_details_type*>(&base));
            return static_cast<const windows_widget_details_type&>(base);
        }

        static windows_widget_details_type& as_windows_widget_details(widget_details_type& base)
        {
            assert(dynamic_cast<windows_widget_details_type*>(&base));
            return static_cast<windows_widget_details_type&>(base);
        }

        static const std::wstring& custom_control_class_name()
        {
            static const std::wstring singleton{ L"tetengo2_customcontrol" };
            return singleton;
        }

        static const std::wstring& dialog_class_name()
        {
            static const std::wstring singleton{ L"tetengo2_dialog" };
            return singleton;
        }

        static const std::wstring& picture_box_class_name()
        {
            static const std::wstring singleton{ L"tetengo2_picturebox" };
            return singleton;
        }

        static const std::wstring& window_class_name()
        {
            static const std::wstring singleton{ L"tetengo2_window" };
            return singleton;
        }

        static bool window_class_is_registered(const std::wstring& window_class_name, const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class{};
            const auto    result = ::GetClassInfoExW(instance_handle, window_class_name.c_str(), &window_class);

            return result != 0;
        }

        static void register_window_class_for_custom_control(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = instance_handle;
            window_class.hIcon = nullptr;
            window_class.hIconSm = nullptr;
            window_class.hCursor = reinterpret_cast<::HICON>(::LoadImageW(
                0, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR));
            window_class.hbrBackground = reinterpret_cast<::HBRUSH>(::GetSysColorBrush(COLOR_WINDOW));
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = custom_control_class_name().c_str();

            const auto atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't register a window class for a custom control!" }));
            }
        }

        static void register_window_class_for_dialog(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = DLGWINDOWEXTRA;
            window_class.hInstance = instance_handle;
            window_class.hIcon = nullptr;
            window_class.hIconSm = nullptr;
            window_class.hCursor = reinterpret_cast<::HICON>(::LoadImageW(
                0, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR));
            window_class.hbrBackground = reinterpret_cast<::HBRUSH>(::GetSysColorBrush(COLOR_3DFACE));
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = dialog_class_name().c_str();

            const auto atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't register a window class for a dialog!" }));
            }
        }

        static void register_window_class_for_picture_box(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = instance_handle;
            window_class.hIcon = nullptr;
            window_class.hIconSm = nullptr;
            window_class.hCursor = reinterpret_cast<::HICON>(::LoadImageW(
                0, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR));
            window_class.hbrBackground = reinterpret_cast<::HBRUSH>(::GetSysColorBrush(COLOR_WINDOW));
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = picture_box_class_name().c_str();

            const auto atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't register a window class for a picture box!" }));
            }
        }

        static void register_window_class_for_window(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = instance_handle;
            window_class.hIcon = reinterpret_cast<::HICON>(::LoadImageW(
                0, MAKEINTRESOURCEW(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR));
            window_class.hIconSm = reinterpret_cast<::HICON>(::LoadImageW(
                0, MAKEINTRESOURCEW(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR));
            window_class.hCursor = reinterpret_cast<::HICON>(::LoadImageW(
                0, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR));
            window_class.hbrBackground = reinterpret_cast<::HBRUSH>(::GetSysColorBrush(COLOR_WINDOW));
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = window_class_name().c_str();

            const auto atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't register a window class for a window!" }));
            }
        }

        static ::DWORD window_style_for_scroll_bars(const gui::widget::widget::scroll_bar_style_type style)
        {
            switch (style)
            {
            case gui::widget::widget::scroll_bar_style_type::none:
                return 0;
            case gui::widget::widget::scroll_bar_style_type::vertical:
                return WS_VSCROLL;
            case gui::widget::widget::scroll_bar_style_type::horizontal:
                return WS_HSCROLL;
            case gui::widget::widget::scroll_bar_style_type::both:
                return WS_HSCROLL | WS_VSCROLL;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid scroll bar style." }));
            }
        }

        static void delete_system_menus(const ::HWND widget_handle)
        {
            const auto menu_handle = ::GetSystemMenu(widget_handle, FALSE);
            if (!menu_handle)
                return;

            if (::DeleteMenu(menu_handle, SC_SIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_MAXIMIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_MINIMIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_RESTORE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't delete system menu value." }));
            }
        }

        static ::LRESULT CALLBACK window_procedure(
            const ::HWND   window_handle,
            const ::UINT   message,
            const ::WPARAM w_param,
            const ::LPARAM l_param) noexcept
        {
            try
            {
                auto* const p_widget = p_widget_from(reinterpret_cast<std::intptr_t>(window_handle));
                if (p_widget)
                    return window_procedure_impl(*p_widget, message, w_param, l_param);
                else
                    return ::CallWindowProcW(::DefWindowProcW, window_handle, message, w_param, l_param);
            }
            catch (const boost::exception& e)
            {
                gui::alert{ /*window_handle*/ }(e);
                return 0;
            }
            catch (const std::exception& e)
            {
                gui::alert{ /*reinterpret_cast<alert::widget_handle_type>(window_handle)*/ }(e);
                return 0;
            }
            catch (...)
            {
                gui::alert{ /*reinterpret_cast<alert::widget_handle_type>(window_handle)*/ }();
                return 0;
            }
        }

        static ::LRESULT window_procedure_impl(
            gui::widget::widget& widget,
            const ::UINT         message,
            const ::WPARAM       w_param,
            const ::LPARAM       l_param)
        {
            const auto found = widget.message_handler_map().find(message);
            if (found != widget.message_handler_map().end())
            {
                for (const auto& p_handler : found->second)
                {
                    const auto result = static_cast<message_handler::windows_message_handler_type&>(*p_handler)
                                            .function(w_param, l_param);
                    if (result)
                        return *result;
                }
            }

            return ::CallWindowProcW(
                reinterpret_cast<::WNDPROC>(as_windows_widget_details(widget.details()).window_procedure),
                reinterpret_cast<::HWND>(as_windows_widget_details(widget.details()).handle),
                message,
                w_param,
                l_param);
        }

        static ::WNDPROC replace_window_procedure(const ::HWND handle)
        {
#if BOOST_COMP_MSVC && BOOST_ARCH_X86_32
#pragma warning(push)
#pragma warning(disable : 4244)
#endif
            const auto proc = window_procedure;
            const auto result = ::SetWindowLongPtrW(handle, GWLP_WNDPROC, reinterpret_cast<::LONG_PTR>(proc));
#if BOOST_COMP_MSVC && BOOST_ARCH_X86_32
#pragma warning(pop)
#endif
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't replace window procedure." }));
            }

            return reinterpret_cast<::WNDPROC>(result);
        }

        static ::BOOL CALLBACK enum_child_procedure(const ::HWND window_handle, const ::LPARAM parameter)
        {
            auto* const p_children =
                reinterpret_cast<std::vector<std::reference_wrapper<gui::widget::widget>>*>(parameter);

            p_children->push_back(std::ref(*p_widget_from(reinterpret_cast<std::intptr_t>(window_handle))));

            return TRUE;
        }
    };


    widget::windows_widget_details_type::windows_widget_details_type(
        const std::intptr_t handle,
        const std::intptr_t window_procedure,
        const std::intptr_t first_child_handle)
    : handle{ std::move(handle) }, window_procedure{ window_procedure }, first_child_handle{ first_child_handle },
      window_state_when_hidden{ SW_RESTORE }
    {}

    widget::windows_widget_details_type::~windows_widget_details_type() noexcept
    {
        const auto window_handle = reinterpret_cast<::HWND>(handle);
        if (::IsWindow(window_handle))
            ::DestroyWindow(window_handle);
    }

    const widget& widget::instance()
    {
        return impl::instance();
    }

    const std::wstring& widget::property_key_for_cpp_instance()
    {
        return impl::property_key_for_cpp_instance();
    }


    gui::widget::widget* widget::p_widget_from(const std::intptr_t widget_handle)
    {
        return impl::p_widget_from(widget_handle);
    }

    widget::~widget() = default;

    widget::widget() : m_p_impl{ std::make_unique<impl>() } {}

    widget::widget_details_ptr_type
    widget::create_button_impl(gui::widget::widget& parent, const bool is_default, const bool is_cancel) const
    {
        return m_p_impl->create_button_impl(parent, is_default, is_cancel);
    }

    widget::widget_details_ptr_type widget::create_custom_control_impl(
        gui::widget::widget&        parent,
        const bool                  border,
        const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_custom_control_impl(parent, border, scroll_bar_style);
    }

    widget::widget_details_ptr_type
    widget::create_dialog_impl(gui::widget::widget* const p_parent, const bool file_droppable) const
    {
        return m_p_impl->create_dialog_impl(p_parent, file_droppable);
    }

    widget::widget_details_ptr_type widget::create_dropdown_box_impl(gui::widget::widget& parent) const
    {
        return m_p_impl->create_dropdown_box_impl(parent);
    }

    widget::widget_details_ptr_type widget::create_image_impl(gui::widget::widget& parent) const
    {
        return m_p_impl->create_image_impl(parent);
    }

    widget::widget_details_ptr_type widget::create_label_impl(gui::widget::widget& parent) const
    {
        return m_p_impl->create_label_impl(parent);
    }

    widget::widget_details_ptr_type
    widget::create_list_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_list_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type
    widget::create_picture_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_picture_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type widget::create_progress_bar_impl(gui::widget::widget& parent) const
    {
        return m_p_impl->create_progress_bar_impl(parent);
    }

    widget::widget_details_ptr_type
    widget::create_text_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_text_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type widget::create_window_impl(
        gui::widget::widget* const  p_parent,
        const scroll_bar_style_type scroll_bar_style,
        const bool                  file_droppable) const
    {
        return m_p_impl->create_window_impl(p_parent, scroll_bar_style, file_droppable);
    }

    void widget::associate_to_native_window_system_impl(gui::widget::widget& widget) const
    {
        m_p_impl->associate_to_native_window_system_impl(widget);
    }

    bool widget::has_parent_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->has_parent_impl(widget);
    }

    gui::widget::widget& widget::parent_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->parent_impl(widget);
    }

    gui::widget::widget& widget::root_ancestor_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->root_ancestor_impl(widget);
    }

    void widget::set_enabled_impl(gui::widget::widget& widget, const bool enabled) const
    {
        m_p_impl->set_enabled_impl(widget, enabled);
    }

    bool widget::enabled_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->enabled_impl(widget);
    }

    void widget::set_visible_impl(gui::widget::widget& widget, const bool visible) const
    {
        m_p_impl->set_visible_impl(widget, visible);
    }

    bool widget::visible_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->visible_impl(widget);
    }

    void widget::set_window_state_impl(gui::widget::widget& widget, const window_state_type state) const
    {
        m_p_impl->set_window_state_impl(widget, state);
    }

    widget::window_state_type widget::window_state_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->window_state_impl(widget);
    }

    void widget::move_impl(
        gui::widget::widget&                  widget,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->move_impl(widget, position, dimension);
    }

    gui::type_list::position_type widget::position_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->position_impl(widget);
    }

    gui::type_list::position_type
    widget::dialog_position_impl(const gui::widget::widget& widget, const gui::widget::widget& parent) const
    {
        return m_p_impl->dialog_position_impl(widget, parent);
    }

    gui::type_list::dimension_type widget::dimension_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->dimension_impl(widget);
    }

    void widget::set_client_dimension_impl(
        gui::widget::widget&                  widget,
        const gui::type_list::dimension_type& client_dimension) const
    {
        m_p_impl->set_client_dimension_impl(widget, client_dimension);
    }

    gui::type_list::dimension_type widget::client_dimension_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->client_dimension_impl(widget);
    }

    gui::type_list::dimension_type widget::normal_dimension_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->normal_dimension_impl(widget);
    }

    void widget::set_text_impl(gui::widget::widget& widget, string_type text) const
    {
        m_p_impl->set_text_impl(widget, std::move(text));
    }

    widget::string_type widget::text_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->text_impl(widget);
    }

    void widget::set_font_impl(gui::widget::widget& widget, const gui::drawing::font& font) const
    {
        m_p_impl->set_font_impl(widget, font);
    }

    gui::drawing::font widget::font_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->font_impl(widget);
    }

    std::vector<std::reference_wrapper<gui::widget::widget>> widget::children_impl(gui::widget::widget& widget) const
    {
        return m_p_impl->children_impl(widget);
    }

    void widget::repaint_impl(const gui::widget::widget& widget, const bool immediately) const
    {
        m_p_impl->repaint_impl(widget, immediately);
    }

    void widget::repaint_partially_impl(
        const gui::widget::widget&            widget,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->repaint_partially_impl(widget, position, dimension);
    }

    void widget::activate_impl(gui::widget::widget& widget) const
    {
        m_p_impl->activate_impl(widget);
    }

    void widget::set_icon_impl(gui::widget::widget& widget, const gui::icon* const p_icon) const
    {
        m_p_impl->set_icon_impl(widget, p_icon);
    }

    void widget::set_menu_bar_impl(gui::widget::widget& widget, const menu_base_type* const p_menu /*= nullptr*/) const
    {
        m_p_impl->set_menu_bar_impl(widget, p_menu);
    }

    bool widget::focusable_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->focusable_impl(widget);
    }

    void widget::set_focusable_impl(gui::widget::widget& widget, const bool focusable) const
    {
        m_p_impl->set_focusable_impl(widget, focusable);
    }

    void widget::set_focus_impl(gui::widget::widget& widget) const
    {
        m_p_impl->set_focus_impl(widget);
    }

    bool widget::read_only_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->read_only_impl(widget);
    }

    void widget::set_read_only_impl(gui::widget::widget& widget, const bool read_only) const
    {
        m_p_impl->set_read_only_impl(widget, read_only);
    }

    void widget::close_impl(gui::widget::widget& widget) const
    {
        m_p_impl->close_impl(widget);
    }

    widget::size_type widget::dropdown_box_value_count_impl(const gui::widget::dropdown_box& dropdown_box) const
    {
        return m_p_impl->dropdown_box_value_count_impl(dropdown_box);
    }

    widget::string_type
    widget::dropdown_box_value_impl(const gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        return m_p_impl->dropdown_box_value_impl(dropdown_box, index);
    }

    void widget::set_dropdown_box_value_impl(
        gui::widget::dropdown_box& dropdown_box,
        const size_type            index,
        string_type                value) const
    {
        m_p_impl->set_dropdown_box_value_impl(dropdown_box, index, std::move(value));
    }

    void widget::insert_dropdown_box_value_impl(
        gui::widget::dropdown_box& dropdown_box,
        const size_type            index,
        string_type                value) const
    {
        return m_p_impl->insert_dropdown_box_value_impl(dropdown_box, index, std::move(value));
    }

    void widget::erase_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        m_p_impl->erase_dropdown_box_value_impl(dropdown_box, index);
    }

    void widget::clear_dropdown_box_impl(gui::widget::dropdown_box& dropdown_box) const
    {
        m_p_impl->clear_dropdown_box_impl(dropdown_box);
    }

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_dropdown_box_value_index_impl(const gui::widget::dropdown_box& dropdown_box) const
    {
        return m_p_impl->selected_dropdown_box_value_index_impl(dropdown_box);
    }

    void widget::select_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        m_p_impl->select_dropdown_box_value_impl(dropdown_box, index);
    }

    widget::size_type widget::list_box_value_count_impl(const gui::widget::list_box& list_box) const
    {
        return m_p_impl->list_box_value_count_impl(list_box);
    }

    widget::string_type widget::list_box_value_impl(const gui::widget::list_box& list_box, const size_type index) const
    {
        return m_p_impl->list_box_value_impl(list_box, index);
    }

    void
    widget::set_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value) const
    {
        m_p_impl->set_list_box_value_impl(list_box, index, std::move(value));
    }

    void
    widget::insert_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value) const
    {
        m_p_impl->insert_list_box_value_impl(list_box, index, std::move(value));
    }

    void widget::erase_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const
    {
        m_p_impl->erase_list_box_value_impl(list_box, index);
    }

    void widget::clear_list_box_impl(gui::widget::list_box& list_box) const
    {
        m_p_impl->clear_list_box_impl(list_box);
    }

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_list_box_value_index_impl(const gui::widget::list_box& list_box) const
    {
        return m_p_impl->selected_list_box_value_index_impl(list_box);
    }

    void widget::select_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const
    {
        m_p_impl->select_list_box_value_impl(list_box, index);
    }

    widget::size_type widget::progress_bar_goal_impl(const gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_goal_impl(progress_bar);
    }

    void widget::set_progress_bar_goal_impl(gui::widget::progress_bar& progress_bar, const size_type goal) const
    {
        m_p_impl->set_progress_bar_goal_impl(progress_bar, goal);
    }

    widget::size_type widget::progress_bar_progress_impl(const gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_progress_impl(progress_bar);
    }

    void widget::set_progress_bar_progress_impl(gui::widget::progress_bar& progress_bar, const size_type progress) const
    {
        m_p_impl->set_progress_bar_progress_impl(progress_bar, progress);
    }

    widget::progress_bar_state_type widget::progress_bar_state_impl(const gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_state_impl(progress_bar);
    }

    void widget::set_progress_bar_state_impl(
        gui::widget::progress_bar&    progress_bar,
        const progress_bar_state_type state) const
    {
        return m_p_impl->set_progress_bar_state_impl(progress_bar, state);
    }
}
