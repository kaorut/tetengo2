/*! \file
    \brief The definition of tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOG_H)
#define TETENGO2_GUI_WIN32_DIALOG_H

//#include <cassert>
//#include <cstddef>
//#include <exception>
//#include <stdexcept>

//#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include <boost/scope_exit.hpp>
//#include <boost/throw_exception.hpp>
//#include <boost/exception/all.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.abstract_window.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a modal dialog.
 
        \tparam Traits A traits type.
   */
    template <typename Traits>
    class dialog : public abstract_window<typename Traits::base_type>
    {
    public:
        // types

        //! \return The traits type.
        typedef Traits traits_type;

        //! \return The base type.
        typedef abstract_window<typename traits_type::base_type> base_type;

        //! \return The message loop type.
        typedef typename traits_type::message_loop_type message_loop_type;

        //! \return The quit-message-loop type.
        typedef
            typename traits_type::quit_message_loop_type
            quit_message_loop_type;

        //! \return The result type.
        enum result_type
        {
            result_undecided,   //!< The result is not decided yet.
            result_accepted,    //!< The settings are accepted.
            result_canceled,    //!< The settings are canceled.
        };


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param parent A parent window.

            \throw std::runtime_error When a dialog cannot be created.
        */
        explicit dialog(base_type& parent)
        :
        base_type(parent),
        m_handle(create_window(&parent)),
        m_result(result_undecided)
        {
            initialize(this);
        }

        /*!
            \brief Destroys the dialog.
        */
        virtual ~dialog()
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Sets the result.

            \param result A result.
        */
        void set_result(const result_type result)
        {
            m_result = result;
        }

        /*!
            \brief Returns the result.

            \return The result.
        */
        result_type result()
        const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog as modal.

            \return The result.
        */
        result_type do_modal()
        {
            assert(has_parent());
            base_type& parent_window = dynamic_cast<base_type&>(parent());
            parent_window.set_enabled(false);
            BOOST_SCOPE_EXIT((&parent_window))
            {
                parent_window.set_enabled(true);
                parent_window.activate();
            } BOOST_SCOPE_EXIT_END

            window_observer_set().destroyed().connect(
                boost::bind(quit_message_loop_type(), 0)
            );
            set_visible(true);

            message_loop_type()();

            return result();
        }


    protected:
        // virtual functions

        //! \copydoc tetengo2::gui::win32::widget::window_procedure
        virtual ::LRESULT window_procedure(
            const ::UINT    uMsg,
            const ::WPARAM  wParam,
            const ::LPARAM  lParam,
            const ::WNDPROC p_default_window_procedure
        )
        {
            switch (uMsg)
            {
            case WM_COMMAND:
                {
                    const ::WORD hi_wparam = HIWORD(wParam);
                    const ::WORD lo_wparam = LOWORD(wParam);
                    if (
                        hi_wparam == 0 &&
                        (lo_wparam == IDOK || lo_wparam == IDCANCEL)
                    )
                    {
                        const ::HWND window_handle =
                            reinterpret_cast< ::HWND>(lParam);
                        assert(
                            window_handle == ::GetDlgItem(handle(), lo_wparam)
                        );
                        if (window_handle != NULL)
                        {
                            p_widget_from(window_handle)->click();
                        }
                        else
                        {
                            set_result(
                                lo_wparam == IDOK ?
                                result_accepted : result_canceled
                            );
                            close();
                        }
                        return 0;
                    }
                    break;
                }
            }
            return base_type::window_procedure(
                uMsg, wParam, lParam, p_default_window_procedure
            );
        }


    private:
        // static functions

        static const string_type& window_class_name()
        {
            static const string_type singleton =
                L"tetengo2::gui::win32::dialog";
            return singleton;
        }

        static handle_type create_window(const base_type* const p_parent)
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
                register_window_class(instance_handle);
            }

            const handle_type handle = ::CreateWindowExW(
                WS_EX_CONTEXTHELP | WS_EX_DLGMODALFRAME,
                window_class_name().c_str(),
                window_class_name().c_str(),
                WS_POPUPWINDOW | WS_CAPTION,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                p_parent == NULL ? HWND_DESKTOP : p_parent->handle(),
                NULL,
                instance_handle,
                NULL
            );
            if (handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a dialog!")
                );
            }

            delete_system_menus(handle);

            return handle;
        }

        static void register_window_class(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = static_window_procedure;
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
            window_class.lpszClassName = window_class_name().c_str();

            const ::ATOM atom = ::RegisterClassExW(&window_class);
            if (atom == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't register a window class!")
                );
            }
        }

        static void delete_system_menus(const ::HWND window_handle)
        {
            const ::HMENU menu_handle = ::GetSystemMenu(window_handle, FALSE);
            if (menu_handle == NULL) return;

            if (::DeleteMenu(menu_handle, SC_SIZE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
            if (::DeleteMenu(menu_handle, SC_MAXIMIZE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
            if (::DeleteMenu(menu_handle, SC_MINIMIZE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
            if (::DeleteMenu(menu_handle, SC_RESTORE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
        }

        static ::LRESULT CALLBACK static_window_procedure(
            const ::HWND   hWnd,
            const ::UINT   uMsg,
            const ::WPARAM wParam,
            const ::LPARAM lParam
        )
        TETENGO2_NOEXCEPT
        {
            try
            {
                dialog* const p_dialog =
                    boost::polymorphic_downcast<dialog*>(p_widget_from(hWnd));
                if (p_dialog != NULL)
                {
                    return p_dialog->window_procedure(
                        uMsg, wParam, lParam, ::DefDlgProcW
                    );
                }
                else
                {
                    return ::CallWindowProcW(
                        ::DefDlgProcW, hWnd, uMsg, wParam, lParam
                    );
                }
            }
            catch (const boost::exception& e)
            {
                (alert_type(hWnd))(e);
                return 0;
            }
            catch (const std::exception& e)
            {
                (alert_type(hWnd))(e);
                return 0;
            }
            catch (...)
            {
                (alert_type(hWnd))();
                return 0;
            }
        }


        // variables

        const handle_type m_handle;

        result_type m_result;


        // virtual functions

        virtual handle_type handle_impl()
        const
        {
            return m_handle;
        }

        virtual void close_impl()
        {
            const ::BOOL result = ::DestroyWindow(handle());
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't destroy the dialog.")
                );
            }
        }


    };


}}}

#endif
