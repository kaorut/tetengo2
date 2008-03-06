/*! \file
    \brief The definition of tetengo2::gui::win32::alert.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ALERT_H)
#define TETENGO2_GUI_WIN32_ALERT_H

//#include <cstddef>
#include <exception>
#include <functional>
#include <stdexcept>
#include <string>

//#include <boost/concept_check.hpp>

#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>

#include "tetengo2.gui.HandleConcept.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The unary functor class template for an alert for Win32
               platforms.

        \tparam WindowHandle A window handle type. It must conform to
                             tetengo2::gui::HandleConcept<WindowHandle>.
        \tparam Encode       An encoding unary functor type. The type
                             Encode<std::wstring, std::string> must conform to
                             boost::UnaryFunctionConcept<Encode, std::wstring, std::string>.
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

        BOOST_CLASS_REQUIRE(WindowHandle, tetengo2::gui, HandleConcept);
        struct concept_check_Encode
        {
            typedef std::wstring task_dialog_string_type;
            typedef std::string exception_what_type;
            typedef
                Encode<task_dialog_string_type, exception_what_type>
                encode_type;
            BOOST_CLASS_REQUIRE3(
                encode_type,
                task_dialog_string_type,
                exception_what_type,
                boost,
                UnaryFunctionConcept
            );
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
        m_window_handle(window_handle)
        {}


        // functions

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


        // variables

        const window_handle_type m_window_handle;


        // functions

        void show_task_dialog(
            const std::wstring& caption,
            const std::wstring& text1,
            const std::wstring& text2
        )
        const
        {
            struct library_loader_class
            {
                const ::HINSTANCE m_handle;

                library_loader_class()
                :
                m_handle(::LoadLibraryW(L"COMCTL32.DLL"))
                { }

                ~library_loader_class()
                throw ()
                {
                    if (m_handle != NULL)
                        ::FreeLibrary(m_handle);
                }
            } library_loader;
            if (library_loader.m_handle == NULL)
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
                ::GetProcAddress(library_loader.m_handle, "TaskDialog")
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
