/*! \file
    \brief The definition of tetengo2::detail::windows::widget.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_WIDGET_H)
#define TETENGO2_DETAIL_WINDOWS_WIDGET_H

#include <algorithm>
//#include <cassert>
#include <exception>
#include <functional>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <system_error>
//#include <type_traits>
//#include <utility>
//#include <vector>

#include <boost/exception/all.hpp>
//#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
//#include <boost/throw_exception.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
//#include <intsafe.h>
//#include <stdint.h>
//#pragma warning(pop)
//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct widget_deleter
        {
            void operator()(const ::HWND window_handle)
            const
            {
                if (::IsWindow(window_handle))
                    ::DestroyWindow(window_handle);
            }


        };


    }
#endif


    /*!
        \brief The class for a detail implementation of a widget.
    */
    class widget : boost::noncopyable
    {
    public:
        // types

        //! The string type.
        typedef std::wstring string_type;

        //! The widget details type.
        struct widget_details_type
        {
#if !defined(DOCUMENTATION)
            typedef std::unique_ptr<typename std::remove_pointer< ::HWND>::type, detail::widget_deleter> handle_type;
            handle_type handle;
            ::WNDPROC window_procedure;
            ::HWND first_child_handle;
            int window_state_when_hidden;

            widget_details_type(
                handle_type     handle,
                const ::WNDPROC window_procedure,
                const ::HWND    first_child_handle
            )
            :
            handle(std::move(handle)),
            window_procedure(window_procedure),
            first_child_handle(first_child_handle),
            window_state_when_hidden(SW_RESTORE)
            {}
#endif

        };

        //! The widget details pointer type.
        typedef std::unique_ptr<widget_details_type> widget_details_ptr_type;


        // static functions

        /*!
            \brief Creates a button.

            \tparam Widget A widget type.

            \param parent     A parent widget.
            \param is_default Set true to create a default button.
            \param is_cancel  Set true to create a cancel button.

            \return A unique pointer to a button.

            \throw std::invalid_argument When a default button already exists and is_default is true.
            \throw std::invalid_argument When a cancel button already exists and is_cancel is true.
            \throw std::system_error     When a button cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_button(Widget& parent, const bool is_default, const bool is_cancel)
        {
            assert(!is_default || !is_cancel);

            const ::DWORD create_window_style =
                is_default ?
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON :
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON;
            ::HMENU id = nullptr;
            if (is_default)
            {
                if (::GetDlgItem(parent.root_ancestor().details()->handle.get(), IDOK))
                    BOOST_THROW_EXCEPTION(std::invalid_argument("Default button already exists."));
                id = reinterpret_cast< ::HMENU>(IDOK);
            }
            else if (is_cancel)
            {
                if (::GetDlgItem(parent.root_ancestor().details()->handle.get(), IDCANCEL))
                    BOOST_THROW_EXCEPTION(std::invalid_argument("Cancel button already exists."));
                id = reinterpret_cast< ::HMENU>(IDCANCEL);
            }

            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    0,
                    WC_BUTTONW,
                    L"tetengo2_button",
                    create_window_style,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent.details()->handle.get(),
                    id,
                    ::GetModuleHandle(nullptr),
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't create a button!")
                );
            }

            const auto p_original_window_procedure = replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(std::move(p_widget), p_original_window_procedure, nullptr);
        }

        /*!
            \brief Creates a custom control.

            \tparam Widget A widget type.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a custom control.

            \throw std::system_error When a custom control cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_custom_control(
            Widget&                                      parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            const auto instance_handle = ::GetModuleHandle(nullptr);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get the instance handle!"
                    )
                );
            }

            if (!window_class_is_registered(custom_control_class_name(), instance_handle))
                register_window_class_for_custom_control<Widget>(instance_handle);

            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    0,
                    custom_control_class_name().c_str(),
                    L"",
                    WS_CHILD | WS_TABSTOP | WS_VISIBLE | window_style_for_scroll_bars<Widget>(scroll_bar_style),
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent.details()->handle.get(),
                    nullptr,
                    instance_handle,
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't create a custom control!"
                    )
                );
            }

            return make_unique<widget_details_type>(std::move(p_widget), &::DefWindowProcW, nullptr);
        }

        /*!
            \brief Creates a dialog.

            \tparam Widget A widget type.

            \param parent A parent widget. When uninitialized, the dialog has no parent.

            \return A unique pointer to a dialog.

            \throw std::system_error When a dialog cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_dialog(const boost::optional<Widget&>& parent)
        {
            const auto instance_handle = ::GetModuleHandle(nullptr);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get the instance handle!"
                    )
                );
            }

            if (!window_class_is_registered(dialog_class_name(), instance_handle))
                register_window_class_for_dialog<Widget>(instance_handle);

            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    WS_EX_CONTEXTHELP | WS_EX_DLGMODALFRAME,
                    dialog_class_name().c_str(),
                    dialog_class_name().c_str(),
                    WS_POPUPWINDOW | WS_CAPTION,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent ? parent->details()->handle.get() : HWND_DESKTOP,
                    nullptr,
                    instance_handle,
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't create a dialog!")
                );
            }

            delete_system_menus(p_widget.get());

            return make_unique<widget_details_type>(std::move(p_widget), &::DefWindowProcW, nullptr);
        }

        /*!
            \brief Creates a dropdown box.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to a dropdown box.

            \throw std::system_error When a dropdown box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_dropdown_box(Widget& parent)
        {
            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    WS_EX_CLIENTEDGE,
                    WC_COMBOBOXW,
                    L"",
                    WS_CHILD |
                        WS_TABSTOP |
                        WS_VISIBLE |
                        CBS_DROPDOWNLIST,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent.details()->handle.get(),
                    nullptr,
                    ::GetModuleHandle(nullptr),
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't create a dropdown box!"
                    )
                );
            }

            const auto p_original_window_procedure = replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(std::move(p_widget), p_original_window_procedure, nullptr);
        }

        /*!
            \brief Creates an image.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to an image.

            \throw std::system_error When an image cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_image(Widget& parent)
        {
            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    0,
                    WC_STATICW,
                    L"tetengo2_image",
                    WS_CHILD | WS_VISIBLE,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent.details()->handle.get(),
                    nullptr,
                    ::GetModuleHandle(nullptr),
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't create an image!")
                );
            }

            const auto p_original_window_procedure = replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(std::move(p_widget), p_original_window_procedure, nullptr);
        }

        /*!
            \brief Creates a label.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to a label.

            \throw std::system_error When a label cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_label(Widget& parent)
        {
            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    0,
                    WC_STATICW,
                    L"tetengo2_label",
                    WS_CHILD | WS_VISIBLE | SS_NOTIFY,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent.details()->handle.get(),
                    nullptr,
                    ::GetModuleHandle(nullptr),
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't create a label!")
                );
            }

            const auto p_original_window_procedure = replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(std::move(p_widget), p_original_window_procedure, nullptr);
        }

        /*!
            \brief Creates a list box.

            \tparam Widget A widget type.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a list box.

            \throw std::system_error When a list box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_list_box(
            Widget&                                      parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    WS_EX_CLIENTEDGE,
                    WC_LISTBOXW,
                    L"",
                    WS_CHILD |
                        WS_TABSTOP |
                        WS_VISIBLE |
                        LBS_NOTIFY |
                        window_style_for_scroll_bars<Widget>(scroll_bar_style),
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent.details()->handle.get(),
                    nullptr,
                    ::GetModuleHandle(nullptr),
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't create a list box!")
                );
            }

            const auto p_original_window_procedure = replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(std::move(p_widget), p_original_window_procedure, nullptr);
        }

        /*!
            \brief Creates a picture box.

            \tparam Widget A widget type.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a picture box.

            \throw std::system_error When a picture box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_picture_box(
            Widget&                                      parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            const auto instance_handle = ::GetModuleHandle(nullptr);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get the instance handle!"
                    )
                );
            }

            if (!window_class_is_registered(picture_box_class_name(), instance_handle))
                register_window_class_for_picture_box<Widget>(instance_handle);

            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    WS_EX_CLIENTEDGE,
                    picture_box_class_name().c_str(),
                    L"",
                    WS_CHILD | WS_TABSTOP | WS_VISIBLE | window_style_for_scroll_bars<Widget>(scroll_bar_style),
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent.details()->handle.get(),
                    nullptr,
                    instance_handle,
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't create a picture box!"
                    )
                );
            }

            return make_unique<widget_details_type>(std::move(p_widget), &::DefWindowProcW, nullptr);
        }

        /*!
            \brief Creates a text box.

            \tparam Widget A widget type.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a text box.

            \throw std::system_error When a text box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_text_box(
            Widget&                                      parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    WS_EX_CLIENTEDGE,
                    WC_EDITW,
                    L"",
                    WS_CHILD |
                        WS_TABSTOP |
                        WS_VISIBLE |
                        ES_AUTOHSCROLL |
                        window_style_for_scroll_bars<Widget>(scroll_bar_style),
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent.details()->handle.get(),
                    nullptr,
                    ::GetModuleHandle(nullptr),
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't create a text box!")
                );
            }

            const auto p_original_window_procedure = replace_window_procedure<Widget>(p_widget.get());

            return make_unique<widget_details_type>(std::move(p_widget), p_original_window_procedure, nullptr);
        }

        /*!
            \brief Creates a window.

            \tparam Widget A widget type.

            \param parent           A parent widget. When uninitialized, the window has no parent.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a window.

            \throw std::system_error When a window cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_window(
            const boost::optional<Widget&>&              parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            const auto instance_handle = ::GetModuleHandle(nullptr);
            if (!instance_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get the instance handle!"
                    )
                );
            }

            if (!window_class_is_registered(window_class_name(), instance_handle))
                register_window_class_for_window<Widget>(instance_handle);

            typename widget_details_type::handle_type p_widget(
                ::CreateWindowExW(
                    WS_EX_ACCEPTFILES | WS_EX_APPWINDOW | window_style_for_scroll_bars<Widget>(scroll_bar_style),
                    window_class_name().c_str(),
                    window_class_name().c_str(),
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent ? parent->details()->handle.get() : HWND_DESKTOP,
                    nullptr,
                    instance_handle,
                    nullptr
                )
            );
            if (!p_widget)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't create a window!")
                );
            }

            return
                make_unique<widget_details_type>(std::move(p_widget), &::DefWindowProcW, nullptr);
        }

        /*!
            \brief Associates a widget to the native window system.

            \tparam Widget A widget type.

            \param widget A widget.

            \throw std::system_error When the widget cannot be associated.
        */
        template <typename Widget>
        static void associate_to_native_window_system(Widget& widget)
        {
            assert(!::GetPropW(widget.details()->handle.get(), property_key_for_cpp_instance().c_str()));
            const auto result =
                ::SetPropW(
                    widget.details()->handle.get(),
                    property_key_for_cpp_instance().c_str(),
                    reinterpret_cast< ::HANDLE>(&widget)
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't set C++ instance.")
                );
            }
        }

        /*!
            \brief Returns whether the widget has a parent.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        template <typename Widget>
        static bool has_parent(const Widget& widget)
        {
            return ::GetParent(const_cast< ::HWND>(widget.details()->handle.get())) != nullptr;
        }

        /*!
            \brief Returns the parent.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The parent.

            \throw std::system_error When the widget has no parent.
        */
        template <typename Widget>
        static Widget& parent(Widget& widget)
        {
            const auto parent_handle = ::GetParent(widget.details()->handle.get());
            if (!parent_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "The widget has no parent.")
                );
            }

            auto* const p_parent = p_widget_from<Widget>(parent_handle);
            assert(p_parent);
            return *p_parent;
        }

        /*!
            \brief Returns the root ancestor.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The root ancestor.

            \throw std::system_error When the widget has no root ancestor.
        */
        template <typename Widget>
        static Widget& root_ancestor(Widget& widget)
        {
            const auto root_ancestor_handle = ::GetAncestor(widget.details()->handle.get(), GA_ROOT);
            if (!root_ancestor_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "The widget has no root ancestor."
                    )
                );
            }

            auto* const p_root_ancestor = p_widget_from<Widget>(root_ancestor_handle);
            assert(p_root_ancestor);
            return *p_root_ancestor;
        }

        /*!
            \brief Sets an enabled status.

            \tparam Widget A widget type.

            \param widget A widget.
            \param enabled An enabled status.
        */
        template <typename Widget>
        static void set_enabled(Widget& widget, const bool enabled)
        {
            ::EnableWindow(widget.details()->handle.get(), enabled ? TRUE : FALSE);
        }

        /*!
            \brief Returns the enabled status.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The enabled status.
        */
        template <typename Widget>
        static bool enabled(const Widget& widget)
        {
            return ::IsWindowEnabled(const_cast< ::HWND>(widget.details()->handle.get())) == TRUE;
        }

        /*!
            \brief Sets a visible status.

            \tparam Widget A widget type.

            \param widget   A widget.
            \param visible_ A visible status.
        */
        template <typename Widget>
        static void set_visible(Widget& widget, const bool visible_)
        {
            int command = SW_HIDE;
            if (visible_)
            {
                if (visible(widget))
                {
                    if (::IsZoomed(widget.details()->handle.get()))
                        command = SW_SHOWMAXIMIZED;
                    else if (::IsIconic(widget.details()->handle.get()))
                        command = SW_MINIMIZE;
                    else
                        command = SW_RESTORE;
                }
                else
                {
                    command = widget.details()->window_state_when_hidden;
                }
            }
            else
            {
                if (visible(widget))
                {
                    if (::IsZoomed(widget.details()->handle.get()))
                        widget.details()->window_state_when_hidden = SW_SHOWMAXIMIZED;
                    else if (::IsIconic(widget.details()->handle.get()))
                        widget.details()->window_state_when_hidden = SW_MINIMIZE;
                    else
                        widget.details()->window_state_when_hidden = SW_RESTORE;
                }
            }
            ::ShowWindow(widget.details()->handle.get(), command);
            if (visible_)
                ::UpdateWindow(widget.details()->handle.get());
        }

        /*!
            \brief Returns the visible status.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The visible status.
        */
        template <typename Widget>
        static bool visible(const Widget& widget)
        {
            return ::IsWindowVisible(const_cast< ::HWND>(widget.details()->handle.get())) == TRUE;
        }

        /*!
            \brief Sets a window state.

            \tparam WindowState A window state type.
            \tparam Widget      A widget type.

            \param widget A widget.
            \param state  A window state.

            \throw std::system_error When a window state cannot be set.
        */
        template <typename WindowState, typename Widget>
        static void set_window_state(Widget& widget, const WindowState state)
        {
            switch (state)
            {
            case WindowState::normal:
                widget.details()->window_state_when_hidden = SW_RESTORE;
                break;
            case WindowState::maximized:
                widget.details()->window_state_when_hidden = SW_SHOWMAXIMIZED;
                break;
            default:
                assert(state == WindowState::minimized);
                widget.details()->window_state_when_hidden = SW_MINIMIZE;
                break;
            }

            if (!visible(widget))
                return;

            ::WINDOWPLACEMENT window_placement = {};
            window_placement.length = sizeof(::WINDOWPLACEMENT);
            const auto get_result = ::GetWindowPlacement(widget.details()->handle.get(), &window_placement);
            if (get_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get window placement."
                    )
                );
            }

            window_placement.showCmd = widget.details()->window_state_when_hidden;

            const auto set_result = ::SetWindowPlacement(widget.details()->handle.get(), &window_placement);
            if (set_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't set window placement."
                    )
                );
            }
        }

        /*!
            \brief Returns the window state.

            \tparam WindowState A window state type.
            \tparam Widget      A widget type.

            \param widget A widget.

            \return The window state.
        */
        template <typename WindowState, typename Widget>
        static WindowState window_state(const Widget& widget)
        {
            if (visible(widget))
            {
                if      (::IsZoomed(const_cast< ::HWND>(widget.details()->handle.get())))
                    return WindowState::maximized;
                else if (::IsIconic(const_cast< ::HWND>(widget.details()->handle.get())))
                    return WindowState::minimized;
                else
                    return WindowState::normal;
            }
            else
            {
                switch (widget.details()->window_state_when_hidden)
                {
                case SW_RESTORE:
                    return WindowState::normal;
                case SW_SHOWMAXIMIZED:
                    return WindowState::maximized;
                default:
                    assert(widget.details()->window_state_when_hidden == SW_MINIMIZE);
                    return WindowState::minimized;
                }
            }
        }

        /*!
            \brief Moves a widget.

            \tparam Widget    A widget type.
            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param widget    A widget.
            \param position  A position.
            \param dimension A dimension.

            \throw std::system_error When the widget cannot be moved.
        */
        template <typename Widget, typename Position, typename Dimension>
        static void move(Widget& widget, const Position& position, const Dimension& dimension)
        {
            const auto result =
                ::MoveWindow(
                    widget.details()->handle.get(),
                    gui::to_pixels<int>(gui::position<Position>::left(position)),
                    gui::to_pixels<int>(gui::position<Position>::top(position)),
                    gui::to_pixels<int>(gui::dimension<Dimension>::width(dimension)),
                    gui::to_pixels<int>(gui::dimension<Dimension>::height(dimension)),
                    visible(widget) ? TRUE : FALSE
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't move the widget.")
                );
            }
        }

        /*!
            \brief Returns the position.

            \tparam Position  A position type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The position.

            \throw std::system_error When the position cannot be obtained.
        */
        template <typename Position, typename Widget>
        static Position position(const Widget& widget)
        {
            ::RECT rectangle = {};
            if (::GetWindowRect(const_cast< ::HWND>(widget.details()->handle.get()), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get window rectangle."
                    )
                );
            }

            typedef gui::position<Position> position_traits_type;
            return
                position_traits_type::make(
                    gui::to_unit<typename position_traits_type::left_type>(rectangle.left),
                    gui::to_unit<typename position_traits_type::top_type>(rectangle.top)
                );
        }

        /*!
            \brief Calculates a position suitable for a dialog.

            \tparam Position     A position type.
            \tparam Widget       A widget type.
            \tparam ParentWidget A parent widget type.

            \param widget A widget.
            \param parent A parent widget.

            \return A position.

            \throw std::system_error When a position cannot be calculated.
        */
        template <typename Position, typename Widget, typename ParentWidget>
        static Position dialog_position(const Widget& widget, const ParentWidget& parent)
        {
            ::POINT point = {};
            const auto x_margin = ::GetSystemMetrics(SM_CYFIXEDFRAME) * 2;
            const auto y_margin = ::GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
            if (::ClientToScreen(const_cast< ::HWND>(parent.details()->handle.get()), &point) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(ERROR_FUNCTION_FAILED, win32_category()),
                        "Can't get parent window client area position."
                    )
                );
            }
            point.x += x_margin;
            point.y += y_margin;

            const auto monitor_handle = ::MonitorFromPoint(point, MONITOR_DEFAULTTONEAREST);
            ::MONITORINFO monitor_info = {};
            monitor_info.cbSize = sizeof(::MONITORINFO);
            if (::GetMonitorInfoW(monitor_handle, &monitor_info) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't get monitor information."
                    )
                );
            }

            const auto widget_dimension = widget.dimension();
            const auto widget_width = gui::to_pixels< ::LONG>(widget_dimension.first);
            const auto widget_height = gui::to_pixels< ::LONG>(widget_dimension.second);
            if (point.x + widget_width + x_margin > monitor_info.rcWork.right)
                point.x = monitor_info.rcWork.right - widget_width - x_margin;
            if (point.y + widget_height + y_margin > monitor_info.rcWork.bottom)
                point.y = monitor_info.rcWork.bottom - widget_height - y_margin;
            if (point.x - x_margin < monitor_info.rcWork.left)
                point.x = monitor_info.rcWork.left + x_margin;
            if (point.y - y_margin < monitor_info.rcWork.top)
                point.y = monitor_info.rcWork.top + y_margin;

            typedef gui::position<Position> position_traits_type;
            return
                position_traits_type::make(
                    gui::to_unit<typename position_traits_type::left_type>(point.x),
                    gui::to_unit<typename position_traits_type::top_type>(point.y)
                );
        }

        /*!
            \brief Returns the dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The dimension.

            \throw std::system_error When the dimension cannot be obtained.
        */
        template <typename Dimension, typename Widget>
        static Dimension dimension(const Widget& widget)
        {
            ::RECT rectangle = {};
            if (::GetWindowRect(const_cast< ::HWND>(widget.details()->handle.get()), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get window rectangle."
                    )
                );
            }

            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            typedef gui::dimension<Dimension> dimension_traits_type;
            return
                dimension_traits_type::make(
                    gui::to_unit<typename dimension_traits_type::width_type>(rectangle.right - rectangle.left),
                    gui::to_unit<typename dimension_traits_type::height_type>(rectangle.bottom - rectangle.top)
                );
        }

        /*!
            \brief Sets a client dimension.

            \tparam Position  A position type.
            \tparam Widget    A widget type.
            \tparam Dimension A dimension type.

            \param widget           A widget.
            \param client_dimension A client dimension.

            \throw std::system_error When a client dimension cannot be set.
        */
        template <typename Position, typename Widget, typename Dimension>
        static void set_client_dimension(Widget& widget, const Dimension& client_dimension)
        {
            assert(
                gui::dimension<Dimension>::width(client_dimension) > 0 &&
                gui::dimension<Dimension>::height(client_dimension) > 0
            );

            const auto pos = position<Position>(widget);
            const auto window_style = ::GetWindowLongPtrW(widget.details()->handle.get(), GWL_STYLE);
            const auto extended_window_style = ::GetWindowLongPtrW(widget.details()->handle.get(), GWL_EXSTYLE);
            const auto left = gui::to_pixels< ::LONG>(gui::position<Position>::left(pos));
            const auto top =  gui::to_pixels< ::LONG>(gui::position<Position>::top(pos));
            const auto width = gui::to_pixels< ::LONG>(gui::dimension<Dimension>::width(client_dimension));
            const auto height =gui::to_pixels< ::LONG>(gui::dimension<Dimension>::height(client_dimension));
            ::RECT rectangle = { left, top, left + width, top + height };
            if (
                ::AdjustWindowRectEx(
                    &rectangle,
                    static_cast< ::DWORD>(window_style),
                    FALSE,
                    static_cast< ::DWORD>(extended_window_style)
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't adjust window rectangle."
                    )
                );
            }

            assert(rectangle.right - rectangle.left > 0);
            assert(rectangle.bottom - rectangle.top > 0);
            const auto result =
                ::MoveWindow(
                    widget.details()->handle.get(),
                    rectangle.left,
                    rectangle.top,
                    rectangle.right - rectangle.left,
                    rectangle.bottom - rectangle.top,
                    visible(widget) ? TRUE : FALSE
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't move window.")
                );
            }
        }

        /*!
            \brief Returns the client dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The client dimension.

            \throw std::system_error When the client dimension cannot be obtained.
        */
        template <typename Dimension, typename Widget>
        static Dimension client_dimension(const Widget& widget)
        {
            ::RECT rectangle = {};
            if (::GetClientRect(const_cast< ::HWND>(widget.details()->handle.get()), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get client rectangle."
                    )
                );
            }

            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            typedef gui::dimension<Dimension> dimension_traits_type;
            return
                dimension_traits_type::make(
                    gui::to_unit<typename dimension_traits_type::width_type>(rectangle.right - rectangle.left),
                    gui::to_unit<typename dimension_traits_type::height_type>(rectangle.bottom - rectangle.top)
                );
        }

        /*!
            \brief Returns the normal dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The normal dimension.

            \throw std::system_error When the normal dimension cannot be obtained.
        */
        template <typename Dimension, typename Widget>
        static Dimension normal_dimension(const Widget& widget)
        {
            ::WINDOWPLACEMENT window_placement = {};
            window_placement.length = sizeof(::WINDOWPLACEMENT);
            const auto get_result = ::GetWindowPlacement(widget.details()->handle.get(), &window_placement);
            if (get_result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get window placement."
                    )
                );
            }

            const auto& rectangle = window_placement.rcNormalPosition;
            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            typedef gui::dimension<Dimension> dimension_traits_type;
            return
                dimension_traits_type::make(
                    gui::to_unit<typename dimension_traits_type::width_type>(rectangle.right - rectangle.left),
                    gui::to_unit<typename dimension_traits_type::height_type>(rectangle.bottom - rectangle.top)
                );
        }

        /*!
            \brief Sets a text.

            \tparam Widget  A widget type.
            \tparam String  A string type.
            \tparam Encoder An eocder type.

            \param widget  A widget.
            \param text    A text.
            \param encoder An encoder.

            \throw std::system_error When the text cannot be set.
        */
        template <typename Widget, typename String, typename Encoder>
        static void set_text(Widget& widget, String text, const Encoder& encoder)
        {
            const auto result =
                ::SetWindowTextW(widget.details()->handle.get(), encoder.encode(std::move(text)).c_str());
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't set text!")
                );
            }
        }

        /*!
            \brief Retuns the text.

            \tparam String  A string type.
            \tparam Widget  A widget type.
            \tparam Encoder An eocder type.

            \param widget  A widget.
            \param encoder An encoder.

            \return The text.
        */
        template <typename String, typename Widget, typename Encoder>
        static String text(const Widget& widget, const Encoder& encoder)
        {
            const auto length = ::GetWindowTextLengthW(const_cast< ::HWND>(widget.details()->handle.get()));
            if (length == 0) return String();

            std::vector<wchar_t> text(length + 1, L'\0');
            ::GetWindowTextW(const_cast< ::HWND>(widget.details()->handle.get()), text.data(), length + 1);

            return encoder.decode(std::wstring(text.begin(), text.begin() + length));
        }

        /*!
            \brief Sets a font.

            \tparam Widget  A widget type.
            \tparam Font    A font type.
            \tparam Encoder An encoder type.

            \param widget A widget.
            \param font   A font.
            \param encoder An encoder.

            \throw std::system_error When the font cannot be set.
        */
        template <typename Widget, typename Font, typename Encoder>
        static void set_font(Widget& widget, const Font& font, const Encoder& encoder)
        {
            const auto previous_font_handle =
                reinterpret_cast< ::HFONT>(::SendMessageW(widget.details()->handle.get(), WM_GETFONT, 0, 0));

            ::LOGFONTW log_font = {
                -static_cast< ::LONG>(font.size()),
                0,
                0,
                0,
                font.bold() ? FW_BOLD : FW_NORMAL,
                font.italic() ? TRUE : FALSE,
                font.underline() ? TRUE : FALSE,
                font.strikeout() ? TRUE : FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L""
            };
            const auto font_family = encoder.encode(font.family());
            assert(font_family.length() < LF_FACESIZE);
            std::copy(font_family.begin(), font_family.end(), log_font.lfFaceName);
            log_font.lfFaceName[font_family.length()] = L'\0';
            const auto font_handle = ::CreateFontIndirectW(&log_font);
            if (!font_handle)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't create font.")
                );
            }
            ::SendMessageW(
                widget.details()->handle.get(),
                WM_SETFONT,
                reinterpret_cast< ::WPARAM>(font_handle),
                MAKELPARAM(TRUE, 0)
            );

            if (previous_font_handle && ::DeleteObject(previous_font_handle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't delete previous font."
                    )
                );
            }
        }

        /*!
            \brief Retuns the font.

            \tparam Font    A font type.
            \tparam Widget  A widget type.
            \tparam Encoder An encoder type.

            \param widget  A widget.
            \param encoder An encoder.

            \return The font.

            \throw std::system_error When the font cannot be obtained.
        */
        template <typename Font, typename Widget, typename Encoder>
        static Font font(const Widget& widget, const Encoder& encoder)
        {
            auto font_handle =
                reinterpret_cast< ::HFONT>(
                    ::SendMessageW(const_cast< ::HWND>(widget.details()->handle.get()), WM_GETFONT, 0, 0)
                );
            if (!font_handle)
                font_handle = reinterpret_cast< ::HFONT>(::GetStockObject(SYSTEM_FONT));

            ::LOGFONTW log_font;
            const auto byte_count = ::GetObjectW(font_handle, sizeof(::LOGFONTW), &log_font);
            if (byte_count == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't get log font.")
                );
            }

            return
                Font(
                    encoder.decode(log_font.lfFaceName),
                    log_font.lfHeight < 0 ? -log_font.lfHeight : log_font.lfHeight,
                    log_font.lfWeight >= FW_BOLD,
                    log_font.lfItalic != FALSE,
                    log_font.lfUnderline != FALSE,
                    log_font.lfStrikeOut != FALSE
                );
        }

        /*!
            \brief Returns the children.

            \tparam Child A child type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The children.
        */
        template <typename Child, typename Widget>
        static std::vector<std::reference_wrapper<Child>> children(Widget& widget)
        {
            std::vector<std::reference_wrapper<Child>> children;

            ::EnumChildWindows(
                widget.details()->handle.get(),
                enum_child_procedure<Child>,
                reinterpret_cast< ::LPARAM>(&children)
            );

            return children;
        }

        /*!
            \brief Repaints a widget.

            \tparam Widget A widget type.

            \param widget      A widget.
            \param immediately Set true to request an immediate repaint.

            \throw std::system_error When the widget cannot be repainted.
        */
        template <typename Widget>
        static void repaint(Widget& widget, const bool immediately)
        {
            if (::InvalidateRect(widget.details()->handle.get(), nullptr, TRUE) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't repaint a widget."
                    )
                );
            }
            if (immediately)
            {
                if (::UpdateWindow(widget.details()->handle.get()) == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(ERROR_FUNCTION_FAILED, win32_category()),
                            "Can't repaint a widget immediately."
                        )
                    );
                }
            }
        }

        /*!
            \brief Uses a widget canvas.

            \tparam Result   A result type.
            \tparam Widget   A widget type.
            \tparam Function A function type.

            \param widget   A widget.
            \param function A function.

            \return A result.
        */
        template <typename Result, typename Widget, typename Function>
        static Result use_canvas(const Widget&  widget, const Function function)
        {
            const auto window_handle = const_cast< ::HWND>(widget.details()->handle.get());
            const auto device_context_handle = ::GetDC(window_handle);
            BOOST_SCOPE_EXIT((window_handle)(device_context_handle))
            {
                ::ReleaseDC(window_handle, device_context_handle);
            } BOOST_SCOPE_EXIT_END;
            typename Widget::widget_canvas_type canvas(device_context_handle);

            return function(canvas);
        }

        /*!
            \brief Activates a widget.

            \tparam Widget A widget type.

            \param widget A widget.
        */
        template <typename Widget>
        static void activate(Widget& widget)
        {
            ::SetActiveWindow(widget.details()->handle.get());
        }

        /*!
            \brief Assigns a menu bar on a widget.

            \tparam Widget   A widget type.
            \tparam MenuBase A menu base type.

            \param widget A widget.
            \param menu   A menu. It may be uninitialized to remove a menu bar.

            \throw std::system_error When a menu bar cannot be set.
        */
        template <typename Widget, typename MenuBase>
        static void set_menu_bar(Widget& widget, const boost::optional<const MenuBase&>& menu = boost::none)
        {
            const auto result =
                ::SetMenu(widget.details()->handle.get(), menu ? menu->details()->handle.get() : nullptr);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't set a menu bar.")
                );
            }

            if (menu && ::DrawMenuBar(widget.details()->handle.get()) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't draw the menu bar.")
                );
            }
        }

        /*!
            \brief Checks whether a widget accepts a focus.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget accepts a focus.
            \retval false Otherwise.

            \throw std::system_error When the focusable status cannot be obtained.
        */
        template <typename Widget>
        static bool focusable(const Widget& widget)
        {
            const auto style = ::GetWindowLongW(const_cast< ::HWND>(widget.details()->handle.get()), GWL_STYLE);
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get focusable status."
                    )
                );
            }
            return (style & WS_TABSTOP) != 0;
        }

        /*!
            \brief Sets whether a control accepts a focus.

            \tparam Widget A widget type.

            \param widget    A widget.
            \param focusable True when the widget accepts a focus.

            \throw std::system_error When a focusable status cannot be set.
        */
        template <typename Widget>
        static void set_focusable(Widget& widget, const bool focusable)
        {
            auto style = ::GetWindowLongW(widget.details()->handle.get(), GWL_STYLE);
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get focusable status."
                    )
                );
            }

            auto unsigned_style = style;
            if (focusable)
                unsigned_style |= WS_TABSTOP;
            else
                unsigned_style &= ~WS_TABSTOP;
            style = unsigned_style;

            if (::SetWindowLongW(widget.details()->handle.get(), GWL_STYLE, style) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't set focusable status."
                    )
                );
            }
        }

        /*!
            \brief Focuses on a widget.

            \param widget A widget.
        */
        template <typename Widget>
        static void set_focus(Widget& widget)
        {
            if (::SetFocus(widget.details()->handle.get()) == nullptr)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't set focus.")
                );
            }
        }

        /*!
            \brief Checks whether a widget is read-only.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget is read-only.
            \retval false Otherwise.

            \throw std::system_error When the read-only status cannot be obtained.
        */
        template <typename Widget>
        static bool read_only(const Widget& widget)
        {
            const auto style = ::GetWindowLongW(const_cast< ::HWND>(widget.details()->handle.get()), GWL_STYLE);
            if (style == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't get read-only status."
                    )
                );
            }
            return (style & ES_READONLY) != 0;
        }

        /*!
            \brief Sets whether a widget is read-only.

            \tparam Widget A widget type.

            \param widget    A widget.
            \param read_only True when the widget is read-only.

            \throw std::system_error When the read-only status cannot be set.
        */
        template <typename Widget>
        static void set_read_only(Widget& widget, const bool read_only)
        {
            const auto result =
                ::SendMessageW(widget.details()->handle.get(), EM_SETREADONLY, read_only ? TRUE : FALSE, 0);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't set read-only status."
                    )
                );
            }
        }

        /*!
            \brief Closes a widget.

            \tparam Widget A widget type.

            \param widget A widget.

            \throw std::system_error When the widget cannot be closed.
        */
        template <typename Widget>
        static void close(Widget& widget)
        {
            const auto result = ::PostMessageW(widget.details()->handle.get(), WM_CLOSE, 0, 0);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't close the widget.")
                );
            }
        }

        /*!
            \brief Opens a target.

            \tparam Widget A widget type.
            \tparam String A string type.

            \param widget A widget.
            \param target A target.

            \throw std::system_error When the target cannot be opened.
        */
        template <typename Widget, typename String>
        static void open_target(const Widget& widget, const String& target)
        {
            const auto result =
                ::ShellExecuteW(
                    widget.has_parent() ?
                        const_cast< ::HWND>(widget.root_ancestor().details()->handle.get()) : nullptr,
                    L"open",
                    target.c_str(),
                    nullptr,
                    nullptr,
                    SW_SHOWNORMAL
                );
            if (reinterpret_cast< ::UINT_PTR>(result) <= 32)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(static_cast<int>(reinterpret_cast< ::UINT_PTR>(result)), win32_category()),
                        "Can't open target."
                    )
                );
            }
        }

        /*!
            \brief Returns the dropdown box item count.

            \tparam Size        A size type.
            \tparam DropdownBox A dropdown box type.

            \param dropdown_box A dropdown box.

            \return The dropdown box item count.

            \throw std::system_error When the item cannot be obtained.
        */
        template <typename Size, typename DropdownBox>
        static Size dropdown_box_item_count(const DropdownBox& dropdown_box)
        {
            const auto result = ::SendMessageW(dropdown_box.details()->handle.get(), CB_GETCOUNT, 0, 0);
            if (result == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't obtain the dropdown box item count."
                    )
                );
            }

            return result;
        }

        /*!
            \brief Returns the dropdown box item.

            \tparam String      A string type.
            \tparam DropdownBox A dropdown box type.
            \tparam Size        A size type.
            \tparam Encoder     An encoder type.

            \param dropdown_box A dropdown box.
            \param index        An index.
            \param encoder      An encoder.

            \return The dropdown box item.

            \throw std::system_error When the item cannot be obtained.
        */
        template <typename String, typename DropdownBox, typename Size, typename Encoder>
        static String dropdown_box_item(const DropdownBox& dropdown_box, const Size index, const Encoder& encoder)
        {
            const auto length = ::SendMessageW(dropdown_box.details()->handle.get(), CB_GETLBTEXTLEN, index, 0);
            if (length == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't obtain the dropdown box item length."
                    )
                );
            }

            std::vector<wchar_t> item(length + 1, 0);
            const auto result =
                ::SendMessageW(
                    dropdown_box.details()->handle.get(),
                    CB_GETLBTEXT,
                    index,
                    reinterpret_cast< ::LPARAM>(item.data())
                );
            if (length == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't obtain the dropdown box item."
                    )
                );
            }

            return encoder.decode(std::wstring(item.data()));
        }

        /*!
            \brief Sets a dropdown box item.

            \tparam DropdownBox A dropdown box type.
            \tparam Size        A size type.
            \tparam String      A string type.
            \tparam Encoder     An encoder type.

            \param dropdown_box A dropdown box.
            \param index        An index.
            \param item         An item.
            \param encoder      An encoder.

            \throw std::system_error When the item cannot be set.
        */
        template <typename DropdownBox, typename Size, typename String, typename Encoder>
        static void set_dropdown_box_item(
            DropdownBox&   dropdown_box,
            const Size     index,
            String         item,
            const Encoder& encoder
        )
        {
            erase_dropdown_box_item(dropdown_box, index);
            insert_dropdown_box_item(dropdown_box, index, std::move(item), encoder);
        }

        /*!
            \brief Inserts a dropdown box item.

            \tparam DropdownBox A dropdown box type.
            \tparam Size        A size type.
            \tparam String      A string type.
            \tparam Encoder     An encoder type.

            \param dropdown_box A dropdown box.
            \param index        An index.
            \param item         An item.
            \param encoder      An encoder.

            \throw std::system_error When the item cannot be inserted.
        */
        template <typename DropdownBox, typename Size, typename String, typename Encoder>
        static void insert_dropdown_box_item(
            DropdownBox&   dropdown_box,
            const Size     index,
            String         item,
            const Encoder& encoder
        )
        {
            const auto result =
                ::SendMessageW(
                    dropdown_box.details()->handle.get(),
                    CB_INSERTSTRING,
                    index,
                    reinterpret_cast< ::LPARAM>(encoder.encode(std::move(item)).c_str())
                );
            if (result == CB_ERR || result == CB_ERRSPACE)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't append a dropdown box item."
                    )
                );
            }
        }

        /*!
            \brief Erases a dropdown box item.

            \tparam DropdownBox A dropdown box type.
            \tparam Size    A size type.

            \param dropdown_box A dropdown box.
            \param index    An index.

            \throw std::system_error When the item cannot be erased.
        */
        template <typename DropdownBox, typename Size>
        static void erase_dropdown_box_item(DropdownBox& dropdown_box, const Size index)
        {
            const auto result = ::SendMessageW(dropdown_box.details()->handle.get(), CB_DELETESTRING, index, 0);
            if (result == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't delete the old item."
                    )
                );
            }
        }

        /*!
            \brief Clears a dropdown box.

            \tparam DropdownBox A dropdown box type.

            \param dropdown_box A dropdown box.

            \throw std::system_error When the dropdown box cannot be cleared.
        */
        template <typename DropdownBox>
        static void clear_dropdown_box(DropdownBox& dropdown_box)
        {
            ::SendMessageW(dropdown_box.details()->handle.get(), CB_RESETCONTENT, 0, 0);
        }

        /*!
            \brief Returns the selected dropdown box item index.

            \tparam Size    A size type.
            \tparam DropdownBox A dropdown box type.

            \param dropdown_box A dropdown box.

            \return The selected dropdown box item index.

            \throw std::system_error When the selected item index cannot be obtained.
        */
        template <typename Size, typename DropdownBox>
        static boost::optional<Size> selected_dropdown_box_item_index(const DropdownBox& dropdown_box)
        {
            const auto index = ::SendMessageW(dropdown_box.details()->handle.get(), CB_GETCURSEL, 0, 0);
            return boost::make_optional<Size>(index != CB_ERR, index);
        }

        /*!
            \brief Selects a dropdown box item.

            \tparam DropdownBox A dropdown box type.
            \tparam Size    A size type.

            \param dropdown_box A dropdown box.
            \param index    An index.

            \throw std::system_error When the item cannot be selected.
        */
        template <typename DropdownBox, typename Size>
        static void select_dropdown_box_item(DropdownBox& dropdown_box, const Size index)
        {
            const auto result = ::SendMessageW(dropdown_box.details()->handle.get(), CB_SETCURSEL, index, 0);
            if (result == CB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't select a dropdown box item."
                    )
                );
            }
        }

        /*!
            \brief Returns the list box item count.

            \tparam Size    A size type.
            \tparam ListBox A list box type.

            \param list_box A list box.

            \return The list box item count.

            \throw std::system_error When the item cannot be obtained.
        */
        template <typename Size, typename ListBox>
        static Size list_box_item_count(const ListBox& list_box)
        {
            const auto result = ::SendMessageW(list_box.details()->handle.get(), LB_GETCOUNT, 0, 0);
            if (result == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't obtain the list box item count."
                    )
                );
            }

            return result;
        }

        /*!
            \brief Returns the list box item.

            \tparam String  A string type.
            \tparam ListBox A list box type.
            \tparam Size    A size type.
            \tparam Encoder An encoder type.

            \param list_box A list box.
            \param index    An index.
            \param encoder  An encoder.

            \return The list box item.

            \throw std::system_error When the item cannot be obtained.
        */
        template <typename String, typename ListBox, typename Size, typename Encoder>
        static String list_box_item(const ListBox& list_box, const Size index, const Encoder& encoder)
        {
            const auto length = ::SendMessageW(list_box.details()->handle.get(), LB_GETTEXTLEN, index, 0);
            if (length == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't obtain the list box item length."
                    )
                );
            }

            std::vector<wchar_t> item(length + 1, 0);
            const auto result =
                ::SendMessageW(
                    list_box.details()->handle.get(),
                    LB_GETTEXT,
                    index,
                    reinterpret_cast< ::LPARAM>(item.data())
                );
            if (length == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't obtain the list box item."
                    )
                );
            }

            return encoder.decode(std::wstring(item.data()));
        }

        /*!
            \brief Sets a list box item.

            \tparam ListBox A list box type.
            \tparam Size    A size type.
            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param list_box A list box.
            \param index    An index.
            \param item     An item.
            \param encoder  An encoder.

            \throw std::system_error When the item cannot be set.
        */
        template <typename ListBox, typename Size, typename String, typename Encoder>
        static void set_list_box_item(ListBox& list_box, const Size index, String item, const Encoder& encoder)
        {
            erase_list_box_item(list_box, index);
            insert_list_box_item(list_box, index, std::move(item), encoder);
        }

        /*!
            \brief Inserts a list box item.

            \tparam ListBox A list box type.
            \tparam Size    A size type.
            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param list_box A list box.
            \param index    An index.
            \param item     An item.
            \param encoder  An encoder.

            \throw std::system_error When the item cannot be inserted.
        */
        template <typename ListBox, typename Size, typename String, typename Encoder>
        static void insert_list_box_item(ListBox& list_box, const Size index, String item, const Encoder& encoder)
        {
            const auto result =
                ::SendMessageW(
                    list_box.details()->handle.get(),
                    LB_INSERTSTRING,
                    index,
                    reinterpret_cast< ::LPARAM>(encoder.encode(std::move(item)).c_str())
                );
            if (result == LB_ERR || result == LB_ERRSPACE)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't append a list box item."
                    )
                );
            }
        }

        /*!
            \brief Erases a list box item.

            \tparam ListBox A list box type.
            \tparam Size    A size type.

            \param list_box A list box.
            \param index    An index.

            \throw std::system_error When the item cannot be erased.
        */
        template <typename ListBox, typename Size>
        static void erase_list_box_item(ListBox& list_box, const Size index)
        {
            const auto result = ::SendMessageW(list_box.details()->handle.get(), LB_DELETESTRING, index, 0);
            if (result == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't delete the old item."
                    )
                );
            }
        }

        /*!
            \brief Clears a list box.

            \tparam ListBox A list box type.

            \param list_box A list box.

            \throw std::system_error When the list box cannot be cleared.
        */
        template <typename ListBox>
        static void clear_list_box(ListBox& list_box)
        {
            ::SendMessageW(list_box.details()->handle.get(), LB_RESETCONTENT, 0, 0);
        }

        /*!
            \brief Returns the selected list box item index.

            \tparam Size    A size type.
            \tparam ListBox A list box type.

            \param list_box A list box.
            
            \return The selected list box item index.

            \throw std::system_error When the selected item index cannot be obtained.
        */
        template <typename Size, typename ListBox>
        static boost::optional<Size> selected_list_box_item_index(const ListBox& list_box)
        {
            const auto index = ::SendMessageW(list_box.details()->handle.get(), LB_GETCURSEL, 0, 0);
            return boost::make_optional<Size>(index != LB_ERR, index);
        }

        /*!
            \brief Selects a list box item.

            \tparam ListBox A list box type.
            \tparam Size    A size type.

            \param list_box A list box.
            \param index    An index.

            \throw std::system_error When the item cannot be selected.
        */
        template <typename ListBox, typename Size>
        static void select_list_box_item(ListBox& list_box, const Size index)
        {
            const auto result = ::SendMessageW(list_box.details()->handle.get(), LB_SETCURSEL, index, 0);
            if (result == LB_ERR)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't select a list box item."
                    )
                );
            }
        }

        /*!
            \brief Returns the window property key.

            This function is for an internal use.

            \return The window property key.
        */
        static const std::wstring& property_key_for_cpp_instance()
        {
            static const std::wstring singleton(L"C++ Instance");
            return singleton;
        }

        /*!
            \brief Returns a pointer to a widget by a widget handle.

            This function is for an internal use.

            \tparam Widget A widget type.

            \param widget_handle A widget handle.

            \return A pointer to a widget.
        */
        template <typename Widget>
        static Widget* p_widget_from(const ::HWND widget_handle)
        {
            return reinterpret_cast<Widget*>(::GetPropW(widget_handle, property_key_for_cpp_instance().c_str()));
        }


    private:
        // static functions

        static const std::wstring& custom_control_class_name()
        {
            static const std::wstring singleton(L"tetengo2_customcontrol");
            return singleton;
        }

        static const std::wstring& dialog_class_name()
        {
            static const std::wstring singleton(L"tetengo2_dialog");
            return singleton;
        }

        static const std::wstring& picture_box_class_name()
        {
            static const std::wstring singleton(L"tetengo2_picturebox");
            return singleton;
        }

        static const std::wstring& window_class_name()
        {
            static const std::wstring singleton(L"tetengo2_window");
            return singleton;
        }

        static bool window_class_is_registered(
            const std::wstring& window_class_name,
            const ::HINSTANCE   instance_handle
        )
        {
            ::WNDCLASSEXW window_class = {};
            const auto result = ::GetClassInfoExW(instance_handle, window_class_name.c_str(), &window_class);

            return result != 0;
        }

        template <typename Widget>
        static void register_window_class_for_custom_control(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure<Widget>;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = instance_handle;
            window_class.hIcon = nullptr;
            window_class.hIconSm = nullptr;
            window_class.hCursor =
                reinterpret_cast< ::HICON>(
                    ::LoadImageW(
                        0, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(::GetSysColorBrush(COLOR_WINDOW));
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = custom_control_class_name().c_str();

            const auto atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't register a window class for a custom control!"
                    )
                );
            }
        }

        template <typename Widget>
        static void register_window_class_for_dialog(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure<Widget>;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = DLGWINDOWEXTRA;
            window_class.hInstance = instance_handle;
            window_class.hIcon = nullptr;
            window_class.hIconSm = nullptr;
            window_class.hCursor =
                reinterpret_cast< ::HICON>(
                    ::LoadImageW(
                        0, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(::GetSysColorBrush(COLOR_3DFACE));
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = dialog_class_name().c_str();

            const auto atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't register a window class for a dialog!"
                    )
                );
            }
        }

        template <typename Widget>
        static void register_window_class_for_picture_box(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure<Widget>;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = instance_handle;
            window_class.hIcon = nullptr;
            window_class.hIconSm = nullptr;
            window_class.hCursor =
                reinterpret_cast< ::HICON>(
                    ::LoadImageW(
                        0, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(::GetSysColorBrush(COLOR_WINDOW));
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = picture_box_class_name().c_str();

            const auto atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't register a window class for a picture box!"
                    )
                );
            }
        }

        template <typename Widget>
        static void register_window_class_for_window(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure<Widget>;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = instance_handle;
            window_class.hIcon =
                reinterpret_cast< ::HICON>(
                    ::LoadImageW(
                        0, MAKEINTRESOURCEW(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                );
            window_class.hIconSm =
                reinterpret_cast< ::HICON>(
                    ::LoadImageW(
                        0, MAKEINTRESOURCEW(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                );
            window_class.hCursor =
                reinterpret_cast< ::HICON>(
                    ::LoadImageW(
                        0, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                    )
                );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(::GetSysColorBrush(COLOR_WINDOW));
            window_class.lpszMenuName = nullptr;
            window_class.lpszClassName = window_class_name().c_str();

            const auto atom = ::RegisterClassExW(&window_class);
            if (!atom)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()),
                        "Can't register a window class for a window!"
                    )
                );
            }
        }

        template <typename Widget>
        static ::DWORD window_style_for_scroll_bars(const typename Widget::scroll_bar_style_type style)
        {
            switch (style)
            {
            case Widget::scroll_bar_style_type::none:
                return 0;
            case Widget::scroll_bar_style_type::vertical:
                return WS_VSCROLL;
            case Widget::scroll_bar_style_type::horizontal:
                return WS_HSCROLL;
            case Widget::scroll_bar_style_type::both:
                return WS_HSCROLL | WS_VSCROLL;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid scroll bar style."));
            }
        }

        static void delete_system_menus(const ::HWND widget_handle)
        {
            const auto menu_handle = ::GetSystemMenu(widget_handle, FALSE);
            if (!menu_handle) return;

            if (
                ::DeleteMenu(menu_handle, SC_SIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_MAXIMIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_MINIMIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_RESTORE, MF_BYCOMMAND) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't delete system menu item."
                    )
                );
            }
        }

        template <typename Widget>
        static ::LRESULT CALLBACK window_procedure(
            const ::HWND   window_handle,
            const ::UINT   message,
            const ::WPARAM w_param,
            const ::LPARAM l_param
        )
        TETENGO2_CPP11_NOEXCEPT
        {
            try
            {
                auto* const p_widget = p_widget_from<Widget>(window_handle);
                if (p_widget)
                    return window_procedure_impl(*p_widget, message, w_param, l_param);
                else
                    return ::CallWindowProcW(::DefWindowProcW, window_handle, message, w_param, l_param);
            }
            catch (const boost::exception& e)
            {
                (typename Widget::alert_type(window_handle))(e);
                return 0;
            }
            catch (const std::exception& e)
            {
                (typename Widget::alert_type(window_handle))(e);
                return 0;
            }
            catch (...)
            {
                (typename Widget::alert_type(window_handle))();
                return 0;
            }
        }

        template <typename Widget>
        static ::LRESULT window_procedure_impl(
            Widget&        widget,
            const ::UINT   message,
            const ::WPARAM w_param,
            const ::LPARAM l_param
        )
        {
            const auto found = widget.message_handler_map().find(message);
            if (found != widget.message_handler_map().end())
            {
                for (const auto& handler: found->second)
                {
                    const auto result = handler(w_param, l_param);
                    if (result)
                        return *result;
                }
            }

            return
                ::CallWindowProcW(
                    widget.details()->window_procedure,
                    const_cast< ::HWND>(widget.details()->handle.get()),
                    message,
                    w_param,
                    l_param
                );
        }

        template <typename Widget>
        static ::WNDPROC replace_window_procedure(const ::HWND handle)
        {
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(push)
#    pragma warning(disable: 4244)
#endif
            const auto proc = window_procedure<Widget>;
            const auto result = ::SetWindowLongPtrW(handle, GWLP_WNDPROC, reinterpret_cast< ::LONG_PTR>(proc));
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(pop)
#endif
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't replace window procedure."
                    )
                );
            }

            return reinterpret_cast< ::WNDPROC>(result);
        }

        template <typename Child>
        static ::BOOL CALLBACK enum_child_procedure(const ::HWND window_handle, const ::LPARAM parameter)
        {
            auto* const p_children = reinterpret_cast<std::vector<std::reference_wrapper<Child>>*>(parameter);

            p_children->push_back(std::ref(*p_widget_from<Child>(window_handle)));

            return TRUE;
        }


   };


}}}


#endif
