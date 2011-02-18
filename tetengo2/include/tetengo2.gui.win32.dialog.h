/*! \file
    \brief The definition of tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOG_H)
#define TETENGO2_GUI_WIN32_DIALOG_H

//#include <cassert>
//#include <cstddef>
//#include <stdexcept>
//#include <utility>

//#include <boost/bind.hpp>
//#include <boost/optional.hpp>
//#include <boost/scope_exit.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x.h"
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

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef abstract_window<typename traits_type::base_type> base_type;

        //! The message loop type.
        typedef typename traits_type::message_loop_type message_loop_type;

        //! The quit-message-loop type.
        typedef
            typename traits_type::quit_message_loop_type
            quit_message_loop_type;

        //! The result type.
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
        base_type(make_message_handler_map(message_handler_map_type())),
        m_handle(create_window(&parent)),
        m_result(result_undecided)
        {
            initialize(this);
        }

        /*!
            \brief Destroys the dialog.
        */
        virtual ~dialog()
        TETENGO2_CPP0X_NOEXCEPT
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
            } BOOST_SCOPE_EXIT_END;

            window_observer_set().destroyed().connect(
                boost::bind(quit_message_loop_type(), 0)
            );
            set_visible(true);

            message_loop_type()();

            return result();
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
            window_class.lpfnWndProc =
                base_type::base_type::p_static_window_procedure();
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

        static void delete_system_menus(const ::HWND widget_handle)
        {
            const ::HMENU menu_handle = ::GetSystemMenu(widget_handle, FALSE);
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


        // functions

        message_handler_map_type make_message_handler_map(
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[WM_COMMAND].push_back(
                boost::bind(&dialog::on_command, this, _1, _2)
            );

            return map;
        }

        boost::optional< ::LRESULT> on_command(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            const ::WORD hi_wparam = HIWORD(wParam);
            const ::WORD lo_wparam = LOWORD(wParam);
            if (
                hi_wparam == 0 &&
                (lo_wparam == IDOK || lo_wparam == IDCANCEL)
            )
            {
                const ::HWND widget_handle =
                    reinterpret_cast< ::HWND>(lParam);
                assert(
                    widget_handle == ::GetDlgItem(handle(), lo_wparam)
                );
                if (widget_handle != NULL)
                {
                    p_widget_from(widget_handle)->click();
                }
                else
                {
                    set_result(
                        lo_wparam == IDOK ?
                        result_accepted : result_canceled
                    );
                    close();
                }
                return boost::optional< ::LRESULT>(0);
            }

            return boost::optional< ::LRESULT>();
        }


    };


}}}

#endif
