/*! \file
    \brief The definition of tetengo2::detail::windows::widget.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_WIDGET_H)
#define TETENGO2_DETAIL_WINDOWS_WIDGET_H

#include <stdexcept>
#include <type_traits>
#include <utility>

#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>

#include "tetengo2.cpp0x.h"


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
    class widget
    {
    public:
        // types

        //! The widget details type.
        typedef std::remove_pointer< ::HWND>::type widget_details_type;

        //! The widget details pointer type.
        typedef
            cpp0x::unique_ptr<
                widget_details_type, detail::widget_deleter
            >::type
            widget_details_ptr_type;


        // static functions

        /*!
            \brief Creates a window.

            \tparam Widget A widget type.

            \param parent A parent widget.
                          When uninitialized, the window has no parent.

            \return A unique pointer to a window.
        */
        template <typename Widget>
        static widget_details_ptr_type create_window(
            const boost::optional<const Widget&> parent =
                boost::optional<const Widget&>()
        )
        {
            const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
            if (instance_handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get the instance handle!")
                );
            }

            if (
                !window_class_is_registered(
                    window_class_name(), instance_handle
                )
            )
            {
                register_window_class_for_window<Widget>(instance_handle);
            }

            widget_details_ptr_type p_widget(
                ::CreateWindowExW(
                    WS_EX_ACCEPTFILES | WS_EX_APPWINDOW,
                    window_class_name().c_str(),
                    window_class_name().c_str(),
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent ? parent->handle() : HWND_DESKTOP,
                    NULL,
                    instance_handle,
                    NULL
                )
            );
            if (p_widget.get() == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a window!")
                );
            }

            return std::move(p_widget);
        }

        /*!
            \brief Creates a dialog.

            \tparam Widget A widget type.

            \param parent A parent widget.
                          When uninitialized, the dialog has no parent.

            \return A unique pointer to a dialog.
        */
        template <typename Widget>
        static widget_details_ptr_type create_dialog(
            const boost::optional<const Widget&> parent
        )
        {
            const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
            if (instance_handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get the instance handle!")
                );
            }

            if (
                !window_class_is_registered(
                    dialog_class_name(), instance_handle
                )
            )
            {
                register_window_class_for_dialog<Widget>(instance_handle);
            }

            widget_details_ptr_type p_widget(
                ::CreateWindowExW(
                    WS_EX_CONTEXTHELP | WS_EX_DLGMODALFRAME,
                    dialog_class_name().c_str(),
                    dialog_class_name().c_str(),
                    WS_POPUPWINDOW | WS_CAPTION,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    parent ? parent->handle() : HWND_DESKTOP,
                    NULL,
                    instance_handle,
                    NULL
                )
            );
            if (p_widget.get() == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a dialog!")
                );
            }

            delete_system_menus(p_widget.get());

            return std::move(p_widget);
        }


    private:
        // static functions

        static const std::wstring& window_class_name()
        {
            static const std::wstring singleton = L"tetengo2_window";
            return singleton;
        }

        static const std::wstring& dialog_class_name()
        {
            static const std::wstring singleton = L"tetengo2_dialog";
            return singleton;
        }

        static bool window_class_is_registered(
            const std::wstring& window_class_name,
            const ::HINSTANCE   instance_handle
        )
        {
            ::WNDCLASSEXW window_class = {};
            const ::BOOL result = ::GetClassInfoExW(
                instance_handle, window_class_name.c_str(), &window_class
            );

            return result != 0;
        }

        template <typename Widget>
        static void register_window_class_for_window(
            const ::HINSTANCE instance_handle
        )
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure<Widget>;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
            window_class.hInstance = instance_handle;
            window_class.hIcon = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OIC_WINLOGO),
                    IMAGE_ICON,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hIconSm = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OIC_WINLOGO),
                    IMAGE_ICON,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hCursor = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OCR_NORMAL),
                    IMAGE_CURSOR,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(
                ::GetSysColorBrush(COLOR_3DFACE)
            );
            window_class.lpszMenuName = NULL;
            window_class.lpszClassName = window_class_name().c_str();

            const ::ATOM atom = ::RegisterClassExW(&window_class);
            if (atom == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error(
                        "Can't register a window class for a window!"
                    )
                );
            }
        }

        template <typename Widget>
        static void register_window_class_for_dialog(
            const ::HINSTANCE instance_handle
        )
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = window_procedure<Widget>;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = DLGWINDOWEXTRA;
            window_class.hInstance = instance_handle;
            window_class.hIcon = NULL;
            window_class.hIconSm = NULL;
            window_class.hCursor = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OCR_NORMAL),
                    IMAGE_CURSOR,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(
                ::GetSysColorBrush(COLOR_3DFACE)
            );
            window_class.lpszMenuName = NULL;
            window_class.lpszClassName = dialog_class_name().c_str();

            const ::ATOM atom = ::RegisterClassExW(&window_class);
            if (atom == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error(
                        "Can't register a window class for a dialog!"
                    )
                );
            }
        }

        static void delete_system_menus(const ::HWND widget_handle)
        {
            const ::HMENU menu_handle = ::GetSystemMenu(widget_handle, FALSE);
            if (menu_handle == NULL) return;

            if (
                ::DeleteMenu(menu_handle, SC_SIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_MAXIMIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_MINIMIZE, MF_BYCOMMAND) == 0 ||
                ::DeleteMenu(menu_handle, SC_RESTORE, MF_BYCOMMAND) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
        }

        static const std::wstring& property_key_for_cpp_instance()
        {
            static const std::wstring singleton(L"C++ Instance");
            return singleton;
        }

        template <typename Widget>
        static Widget* p_widget_from(const ::HWND widget_handle)
        {
            return reinterpret_cast<Widget*>(
                ::GetPropW(
                    widget_handle, property_key_for_cpp_instance().c_str()
                )
            );
        }

        template <typename Widget>
        static ::LRESULT CALLBACK window_procedure(
            const ::HWND   hWnd,
            const ::UINT   uMsg,
            const ::WPARAM wParam,
            const ::LPARAM lParam
        )
        TETENGO2_CPP0X_NOEXCEPT
        {
            try
            {
                Widget* const p_widget = p_widget_from<Widget>(hWnd);
                if (p_widget != NULL)
                {
                    return p_widget->window_procedure(uMsg, wParam, lParam);
                }
                else
                {
                    return ::CallWindowProcW(
                        ::DefWindowProcW, hWnd, uMsg, wParam, lParam
                    );
                }
            }
            catch (const boost::exception& e)
            {
                (typename Widget::alert_type(hWnd))(e);
                return 0;
            }
            catch (const std::exception& e)
            {
                (typename Widget::alert_type(hWnd))(e);
                return 0;
            }
            catch (...)
            {
                (typename Widget::alert_type(hWnd))();
                return 0;
            }
        }


        // forbidden operations

        widget();


   };


}}}


#endif
