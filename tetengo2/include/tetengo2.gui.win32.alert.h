/*! \file
    \brief The definition of tetengo2::gui::win32::alert.

    Copyright (C) 2007-2010 kaoru

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

//#include <boost/concept_check.hpp>
#include <boost/scope_exit.hpp>
#include <boost/exception/all.hpp>
#include <boost/exception/exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>

#include "concept_tetengo2.gui.Handle.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The unary functor class template for an alert for Win32
               platforms.

        \tparam WindowHandle A window handle type. It must conform to
                             concept_tetengo2::gui::Handle<WindowHandle>.
        \tparam Encode       An encoding unary functor type. The type
                             Encode<std::wstring, std::string> must conform to
                             boost::UnaryFunction<Encode, std::wstring, std::string>.
    */
    template <
        typename WindowHandle,
        template <typename Target, typename Source> class Encode
    >
    class alert :
        public std::unary_function<std::exception, void>
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<WindowHandle>));
        struct concept_check_Encode
        {
            typedef std::wstring task_dialog_string_type;
            typedef std::string exception_what_type;
            typedef
                Encode<task_dialog_string_type, exception_what_type>
                encode_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_type, task_dialog_string_type, exception_what_type
                >
            ));
        };


    public:
        // types

        //! The window handle type.
        typedef WindowHandle window_handle_type;


        // constructors

        /*!
            \brief Creates an alert.

            \param window_handle A window handle.
        */
        explicit alert(const window_handle_type window_handle = NULL)
        throw ()
        :
        m_window_handle(actual_parent_window_handle(window_handle))
        {}


        // functions

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(const boost::exception& exception)
        const
        throw ()
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
                        L"Alert",
                        encode_type()(typeid(*p_std_exception).name()),
                        encode_type()(p_std_exception->what()),
                        p_file != NULL ? *p_file : "",
                        p_line != NULL ? *p_line : 0,
                        p_function != NULL ? *p_function : ""
                    );
                }
                else
                {
                    show_task_dialog(
                        L"Alert",
                        encode_type()(typeid(exception).name()),
                        encode_type()(
                            boost::diagnostic_information(exception)
                        )
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
        throw ()
        {
            try
            {
                show_task_dialog(
                    L"Alert",
                    encode_type()(typeid(exception).name()),
                    encode_type()(exception.what())
                );
            }
            catch (...)
            {}
        }


    private:
        // types

        typedef Encode<std::wstring, std::string> encode_type;


        // static function

        static window_handle_type actual_parent_window_handle(
            const window_handle_type window_handle
        )
        {
            const window_handle_type actual_parent_handle =
                ::GetAncestor(window_handle, GA_ROOT);

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


        // variables

        const window_handle_type m_window_handle;


        // functions

        void show_task_dialog(
            const std::wstring& caption,
            const std::wstring& text1,
            const std::wstring& text2,
            const std::string&  source_file_name = "",
            const int           source_file_line = 0,
            const std::string&  source_function = ""
        )
        const
        {
#if defined(NDEBUG)
            show_task_dialog_impl(caption, text1, text2);
#else
            std::stringstream stream;
            stream <<
                std::endl <<
                std::endl <<
                "in " <<
                source_file_name <<
                "(" <<
                source_file_line <<
                "):" <<
                std::endl <<
                source_function;

            show_task_dialog_impl(
                caption, text1, text2 + encode_type()(stream.str())
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
            } BOOST_SCOPE_EXIT_END
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
                m_window_handle,
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
                m_window_handle,
                text.c_str(),
                caption.c_str(),
                MB_OK | MB_ICONERROR
            );
        }

    };


}}}

#endif
