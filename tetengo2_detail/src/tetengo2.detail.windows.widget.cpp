/*! \file
    \brief The definition of tetengo2::detail::windows::widget.

    Copyright (C) 2007-2018 kaoru

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

#include <tetengo2/detail/windows/error_category.h>
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

        using font_type = widget::font_type;

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

        void set_text_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget, string_type text) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        string_type text_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_font_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const font_type& font) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        font_type font_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        std::vector<std::reference_wrapper<gui::widget::widget>>
        children_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void repaint_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const bool                 immediately) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void repaint_partially_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void activate_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const {}

        void set_icon_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::icon* const p_icon) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_menu_bar_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const menu_base_type* const p_menu = nullptr) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        bool focusable_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_focusable_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const bool           focusable) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_focus_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const {}

        bool read_only_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_read_only_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const bool           read_only) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void close_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const {}

        size_type
        dropdown_box_value_count_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::dropdown_box& dropdown_box) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        string_type dropdown_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::dropdown_box& dropdown_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_dropdown_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::dropdown_box& dropdown_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index,
            TETENGO2_STDALT_MAYBE_UNUSED string_type value) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void insert_dropdown_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::dropdown_box& dropdown_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index,
            TETENGO2_STDALT_MAYBE_UNUSED string_type value) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void erase_dropdown_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::dropdown_box& dropdown_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void clear_dropdown_box_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::dropdown_box& dropdown_box) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        tetengo2::stdalt::optional<size_type> selected_dropdown_box_value_index_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::dropdown_box& dropdown_box) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void select_dropdown_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::dropdown_box& dropdown_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        size_type list_box_value_count_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::list_box& list_box) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        string_type list_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::list_box& list_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_list_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index,
            TETENGO2_STDALT_MAYBE_UNUSED string_type value) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void insert_list_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index,
            TETENGO2_STDALT_MAYBE_UNUSED string_type value) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void erase_list_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void clear_list_box_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        tetengo2::stdalt::optional<size_type>
        selected_list_box_value_index_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::list_box& list_box) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void select_list_box_value_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type index) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        size_type
        progress_bar_goal_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::progress_bar& progress_bar) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_progress_bar_goal_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::progress_bar& progress_bar,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type goal) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        size_type
        progress_bar_progress_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::progress_bar& progress_bar) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_progress_bar_progress_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::progress_bar& progress_bar,
            TETENGO2_STDALT_MAYBE_UNUSED const size_type progress) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        progress_bar_state_type
        progress_bar_state_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::progress_bar& progress_bar) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
        }

        void set_progress_bar_state_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::progress_bar& progress_bar,
            TETENGO2_STDALT_MAYBE_UNUSED const progress_bar_state_type state) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Implement it."));
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

        template <typename Child>
        static ::BOOL CALLBACK enum_child_procedure(const ::HWND window_handle, const ::LPARAM parameter)
        {
            auto* const p_children = reinterpret_cast<std::vector<std::reference_wrapper<Child>>*>(parameter);

            p_children->push_back(std::ref(*p_widget_from<Child>(window_handle)));

            return TRUE;
        }

#if 0
        static const std::wstring& property_key_for_cpp_instance()
        {
            static const std::wstring singleton{ L"C++ Instance" };
            return singleton;
        }

        static gui::widget::widget* p_widget_from(const ::HWND widget_handle)
        {
            return reinterpret_cast<gui::widget::widget*>(
                ::GetPropW(widget_handle, property_key_for_cpp_instance().c_str()));
        }

        static ::LRESULT CALLBACK window_procedure(
            const ::HWND   window_handle,
            const ::UINT   message,
            const ::WPARAM w_param,
            const ::LPARAM l_param) noexcept
        {
            try
            {
                auto* const p_widget = p_widget_from(window_handle);
                if (p_widget)
                    return window_procedure_impl(*p_widget, message, w_param, l_param);
                else
                    return ::CallWindowProcW(::DefWindowProcW, window_handle, message, w_param, l_param);
            }
            catch (const boost::exception& e)
            {
                tetengo2::gui::alert{ reinterpret_cast<tetengo2::gui::alert::widget_handle_type>(window_handle) }(e);
                return 0;
            }
            catch (const std::exception& e)
            {
                tetengo2::gui::alert{ reinterpret_cast<tetengo2::gui::alert::widget_handle_type>(window_handle) }(e);
                return 0;
            }
            catch (...)
            {
                tetengo2::gui::alert{ reinterpret_cast<tetengo2::gui::alert::widget_handle_type>(window_handle) }();
                return 0;
            }
        }

        static ::LRESULT window_procedure_impl(
            gui::widget::widget& widget_,
            const ::UINT         message,
            const ::WPARAM       w_param,
            const ::LPARAM       l_param)
        {
            const auto found = widget_.message_handler_map().find(message);
            if (found != widget_.message_handler_map().end())
            {
                for (const auto& handler : found->second)
                {
                    const auto result = handler(w_param, l_param);
                    if (result)
                        return *result;
                }
            }

            return ::CallWindowProcW(
                as_windows_widget_details(widget_.details()).window_procedure,
                const_cast<::HWND>(as_windows_widget_details(widget_.details()).handle.get()),
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
            const auto result =
                ::SetWindowLongPtrW(handle, GWLP_WNDPROC, reinterpret_cast<::LONG_PTR>(window_procedure));
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
#endif
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

    widget::widget_details_ptr_type widget::create_button_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent,
        const bool                                        is_default,
        const bool                                        is_cancel) const
    {
        return m_p_impl->create_button_impl(parent, is_default, is_cancel);
    }

    widget::widget_details_ptr_type widget::create_custom_control_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent,
        const bool                                        border,
        const scroll_bar_style_type                       scroll_bar_style) const
    {
        return m_p_impl->create_custom_control_impl(parent, border, scroll_bar_style);
    }

    widget::widget_details_ptr_type
    widget::create_dialog_impl(gui::widget::widget* const p_parent, const bool file_droppable) const
    {
        return m_p_impl->create_dialog_impl(p_parent, file_droppable);
    }

    widget::widget_details_ptr_type
    widget::create_dropdown_box_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent) const
    {
        return m_p_impl->create_dropdown_box_impl(parent);
    }

    widget::widget_details_ptr_type
    widget::create_image_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent) const
    {
        return m_p_impl->create_image_impl(parent);
    }

    widget::widget_details_ptr_type
    widget::create_label_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent) const
    {
        return m_p_impl->create_label_impl(parent);
    }

    widget::widget_details_ptr_type widget::create_list_box_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent,
        const scroll_bar_style_type                       scroll_bar_style) const
    {
        return m_p_impl->create_list_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type widget::create_picture_box_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent,
        const scroll_bar_style_type                       scroll_bar_style) const
    {
        return m_p_impl->create_picture_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type
    widget::create_progress_bar_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent) const
    {
        return m_p_impl->create_progress_bar_impl(parent);
    }

    widget::widget_details_ptr_type widget::create_text_box_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& parent,
        const scroll_bar_style_type                       scroll_bar_style) const
    {
        return m_p_impl->create_text_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type widget::create_window_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget* const p_parent,
        const scroll_bar_style_type                             scroll_bar_style,
        const bool                                              file_droppable) const
    {
        return m_p_impl->create_window_impl(p_parent, scroll_bar_style, file_droppable);
    }

    void widget::associate_to_native_window_system_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const
    {
        m_p_impl->associate_to_native_window_system_impl(widget);
    }

    bool widget::has_parent_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->has_parent_impl(widget);
    }

    TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget&
                                 widget::parent_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->parent_impl(widget);
    }

    TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget&
                                 widget::root_ancestor_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->root_ancestor_impl(widget);
    }

    void widget::set_enabled_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget, const bool enabled) const
    {
        m_p_impl->set_enabled_impl(widget, enabled);
    }

    bool widget::enabled_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->enabled_impl(widget);
    }

    void widget::set_visible_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget, const bool visible) const
    {
        m_p_impl->set_visible_impl(widget, visible);
    }

    bool widget::visible_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->visible_impl(widget);
    }

    void widget::set_window_state_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
        const window_state_type                           state) const
    {
        m_p_impl->set_window_state_impl(widget, state);
    }

    widget::window_state_type
    widget::window_state_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->window_state_impl(widget);
    }

    void widget::move_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
        const gui::type_list::position_type&              position,
        const gui::type_list::dimension_type&             dimension) const
    {
        m_p_impl->move_impl(widget, position, dimension);
    }

    gui::type_list::position_type
    widget::position_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->position_impl(widget);
    }

    gui::type_list::position_type widget::dialog_position_impl(
        TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
        const gui::widget::widget&                              parent) const
    {
        return m_p_impl->dialog_position_impl(widget, parent);
    }

    gui::type_list::dimension_type
    widget::dimension_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->dimension_impl(widget);
    }

    void widget::set_client_dimension_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
        const gui::type_list::dimension_type&             client_dimension) const
    {
        m_p_impl->set_client_dimension_impl(widget, client_dimension);
    }

    gui::type_list::dimension_type
    widget::client_dimension_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->client_dimension_impl(widget);
    }

    gui::type_list::dimension_type
    widget::normal_dimension_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->normal_dimension_impl(widget);
    }

    void widget::set_text_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget, string_type text) const
    {
        m_p_impl->set_text_impl(widget, std::move(text));
    }

    widget::string_type widget::text_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->text_impl(widget);
    }

    void widget::set_font_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget, const font_type& font) const
    {
        m_p_impl->set_font_impl(widget, font);
    }

    widget::font_type widget::font_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->font_impl(widget);
    }

    std::vector<std::reference_wrapper<gui::widget::widget>>
    widget::children_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const
    {
        return m_p_impl->children_impl(widget);
    }

    void
    widget::repaint_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget, const bool immediately) const
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

    void widget::activate_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const
    {
        m_p_impl->activate_impl(widget);
    }

    void
    widget::set_icon_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget, const gui::icon* const p_icon) const
    {
        m_p_impl->set_icon_impl(widget, p_icon);
    }

    void widget::set_menu_bar_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
        const menu_base_type* const                       p_menu /*= nullptr*/) const
    {
        m_p_impl->set_menu_bar_impl(widget, p_menu);
    }

    bool widget::focusable_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->focusable_impl(widget);
    }

    void
    widget::set_focusable_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget, const bool focusable) const
    {
        m_p_impl->set_focusable_impl(widget, focusable);
    }

    void widget::set_focus_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const
    {
        m_p_impl->set_focus_impl(widget);
    }

    bool widget::read_only_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget) const
    {
        return m_p_impl->read_only_impl(widget);
    }

    void
    widget::set_read_only_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget, const bool read_only) const
    {
        m_p_impl->set_read_only_impl(widget, read_only);
    }

    void widget::close_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const
    {
        m_p_impl->close_impl(widget);
    }

    widget::size_type widget::dropdown_box_value_count_impl(
        TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::dropdown_box& dropdown_box) const
    {
        return m_p_impl->dropdown_box_value_count_impl(dropdown_box);
    }

    widget::string_type widget::dropdown_box_value_impl(
        TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::dropdown_box& dropdown_box,
        const size_type                                               index) const
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

    void widget::erase_dropdown_box_value_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::dropdown_box& dropdown_box,
        const size_type                                         index) const
    {
        m_p_impl->erase_dropdown_box_value_impl(dropdown_box, index);
    }

    void widget::clear_dropdown_box_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::dropdown_box& dropdown_box) const
    {
        m_p_impl->clear_dropdown_box_impl(dropdown_box);
    }

    tetengo2::stdalt::optional<widget::size_type> widget::selected_dropdown_box_value_index_impl(
        TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::dropdown_box& dropdown_box) const
    {
        return m_p_impl->selected_dropdown_box_value_index_impl(dropdown_box);
    }

    void widget::select_dropdown_box_value_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::dropdown_box& dropdown_box,
        const size_type                                         index) const
    {
        m_p_impl->select_dropdown_box_value_impl(dropdown_box, index);
    }

    widget::size_type
    widget::list_box_value_count_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::list_box& list_box) const
    {
        return m_p_impl->list_box_value_count_impl(list_box);
    }

    widget::string_type widget::list_box_value_impl(
        TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::list_box& list_box,
        const size_type                                           index) const
    {
        return m_p_impl->list_box_value_impl(list_box, index);
    }

    void widget::set_list_box_value_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box,
        const size_type                                     index,
        string_type                                         value) const
    {
        m_p_impl->set_list_box_value_impl(list_box, index, std::move(value));
    }

    void widget::insert_list_box_value_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box,
        const size_type                                     index,
        string_type                                         value) const
    {
        m_p_impl->insert_list_box_value_impl(list_box, index, std::move(value));
    }

    void widget::erase_list_box_value_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box,
        const size_type                                     index) const
    {
        m_p_impl->erase_list_box_value_impl(list_box, index);
    }

    void widget::clear_list_box_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box) const
    {
        m_p_impl->clear_list_box_impl(list_box);
    }

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_list_box_value_index_impl(TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::list_box& list_box) const
    {
        return m_p_impl->selected_list_box_value_index_impl(list_box);
    }

    void widget::select_list_box_value_impl(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::list_box& list_box,
        const size_type                                     index) const
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
