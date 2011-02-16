/*! \file
    \brief The definition of tetengo2::gui::win32::alert.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ALERT_H)
#define TETENGO2_GUI_WIN32_ALERT_H

#include <cstddef>
#include <exception>
#include <functional>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <string>

#include <boost/exception/all.hpp>
#include <boost/scope_exit.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The unary functor class template for an alert for Win32
               platforms.

        \tparam WidgetHandle     A widget handle type.
        \tparam UiEncoder        An encoder type for the user interface.
        \tparam ExceptionEncoder An encoder type for the user interface.
    */
    template <
        typename WidgetHandle,
        typename UiEncoder,
        typename ExceptionEncoder
    >
    class alert :
        public std::unary_function<std::exception, void>
    {
    public:
        // types

        //! The widget handle type.
        typedef WidgetHandle widget_handle_type;

        //! The encoder type for the user interface.
        typedef UiEncoder ui_encoder_type;

        //! The encoder type for exceptions.
        typedef ExceptionEncoder exception_encoder_type;


        // constructors

        /*!
            \brief Creates an alert.

            \param widget_handle     A widget handle.
        */
        explicit alert(const widget_handle_type widget_handle = NULL)
        TETENGO2_CPP0X_NOEXCEPT
        :
        m_widget_handle(actual_parent_widget_handle(widget_handle))
        {}


        // functions

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(const boost::exception& exception)
        const
        TETENGO2_CPP0X_NOEXCEPT
        {
            try
            {
                const std::exception* const p_std_exception =
                    dynamic_cast<const std::exception*>(&exception);
                if (p_std_exception != NULL)
                {
                    const char* const* const p_file =
                        boost::get_error_info<boost::throw_file>(
                            exception
                        );
                    const int* const p_line =
                        boost::get_error_info<boost::throw_line>(
                            exception
                        );
                    const char* const* const p_function =
                        boost::get_error_info<boost::throw_function>(
                            exception
                        );
                    show_task_dialog(
                        string_type(TETENGO2_TEXT("Alert")),
                        exception_encoder().decode(
                            typeid(*p_std_exception).name()
                        ),
                        exception_encoder().decode(p_std_exception->what()),
                        p_file != NULL ?
                            exception_encoder().decode(*p_file) :
                            string_type(),
                        p_line != NULL ? *p_line : 0,
                        p_function != NULL ?
                            exception_encoder().decode(*p_function) :
                            string_type()
                    );
                }
                else
                {
                    show_task_dialog(
                        string_type(TETENGO2_TEXT("Alert")),
                        exception_encoder().decode(typeid(exception).name()),
                        exception_encoder().decode(
                            boost::diagnostic_information(exception)
                        ),
                        string_type(),
                        0,
                        string_type()
                    );
                }
            }
            catch (...)
            {}
        }

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(
            const std::exception& exception =
                std::runtime_error("Unknown Error!")
        )
        const
        TETENGO2_CPP0X_NOEXCEPT
        {
            try
            {
                show_task_dialog(
                    L"Alert",
                    ui_encoder().encode(
                        exception_encoder().decode(typeid(exception).name())
                    ),
                    ui_encoder().encode(
                        exception_encoder().decode(exception.what())
                    ),
                    string_type(),
                    0,
                    string_type()
                );
            }
            catch (...)
            {}
        }


    private:
        // types

        typedef typename ui_encoder_type::internal_string_type string_type;


        // static functions

        static widget_handle_type actual_parent_widget_handle(
            const widget_handle_type widget_handle
        )
        {
            const widget_handle_type actual_parent_handle =
                ::GetAncestor(widget_handle, GA_ROOT);

            if (
                actual_parent_handle == NULL ||
                ::IsWindow(actual_parent_handle) == 0 ||
                ::IsWindowVisible(actual_parent_handle) == 0 ||
                ::IsWindowEnabled(actual_parent_handle) == 0
            )
            {
                return HWND_DESKTOP;
            }

            return actual_parent_handle;
        }

        static const ui_encoder_type& ui_encoder()
        {
            static const ui_encoder_type singleton;
            return singleton;
        }

        static const exception_encoder_type& exception_encoder()
        {
            static const exception_encoder_type singleton;
            return singleton;
        }


        // variables

        const widget_handle_type m_widget_handle;


        // functions

        void show_task_dialog(
            const string_type& caption,
            const string_type& text1,
            const string_type& text2,
            const string_type& source_file_name,
            const int          source_file_line,
            const string_type& source_function
        )
        const
        {
#if defined(NDEBUG)
            show_task_dialog_impl(
                ui_encoder().encode(caption),
                ui_encoder().encode(text1),
                ui_encoder().encode(text2)
            );
#else
            std::basic_ostringstream<typename string_type::value_type> stream;
            stream <<
                std::endl <<
                std::endl <<
                TETENGO2_TEXT("in ") <<
                source_file_name <<
                TETENGO2_TEXT("(") <<
                source_file_line <<
                TETENGO2_TEXT("):") <<
                std::endl <<
                source_function;

            show_task_dialog_impl(
                ui_encoder().encode(caption),
                ui_encoder().encode(text1),
                ui_encoder().encode(text2 + stream.str())
            );
#endif
        }

        void show_task_dialog_impl(
            const std::wstring& caption,
            const std::wstring& text1,
            const std::wstring& text2
        )
        const
        {
            const ::HINSTANCE handle = ::LoadLibraryW(L"COMCTL32.DLL");
            BOOST_SCOPE_EXIT((handle))
            {
                if (handle != NULL)
                    ::FreeLibrary(handle);
            } BOOST_SCOPE_EXIT_END;
            if (handle == NULL)
            {
                show_message_box(caption, text1, text2);
                return;
            }

            typedef ::HRESULT (WINAPI * task_dialog)(
                ::HWND,
                ::HINSTANCE,
                ::PCWSTR,
                ::PCWSTR,
                ::PCWSTR,
                ::TASKDIALOG_COMMON_BUTTON_FLAGS,
                ::PCWSTR,
                int*
            ); 
            task_dialog p_task_dialog = reinterpret_cast<task_dialog>(
                ::GetProcAddress(handle, "TaskDialog")
            );
            if (p_task_dialog == NULL)
            {
                show_message_box(caption, text1, text2);
                return;
            }

            p_task_dialog(
                m_widget_handle,
                ::GetModuleHandle(NULL),
                caption.c_str(),
                text1.c_str(),
                text2.c_str(),
                TDCBF_OK_BUTTON,
                TD_ERROR_ICON,
                NULL
            );
        }

        void show_message_box(
            const std::wstring& caption,
            const std::wstring& text1,
            const std::wstring& text2
        )
        const
        {
            const std::wstring text = text1 + L"\n\n" + text2;
            ::MessageBoxW(
                m_widget_handle,
                text.c_str(),
                caption.c_str(),
                MB_OK | MB_ICONERROR
            );
        }

    };


}}}

#endif
