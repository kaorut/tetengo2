/*! \file
    \brief The definition of tetengo2::detail::windows::alert.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ALERT_H)
#define TETENGO2_DETAIL_WINDOWS_ALERT_H

#include <cstddef>
#include <iomanip>
#include <sstream>
#include <string>

#include <boost/scope_exit.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class template for a detail implementation of an alert.

        \tparam String  A string type.
        \tparam Encoder An encoder type.
    */
    template <typename String, typename Encoder>
    class alert
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The widget handle type.
        typedef ::HWND widget_handle_type;


        // static functions

        /*!
            \brief Returns the root ancestor widget handle.

            \param widget_handle A widget handle.

            \return The root ancestor widget handle.
        */
        static widget_handle_type root_ancestor_widget_handle(
            const widget_handle_type widget_handle
        )
        {
            const widget_handle_type root_handle =
                ::GetAncestor(widget_handle, GA_ROOT);

            if (
                !root_handle ||
                ::IsWindow(root_handle) == 0 ||
                ::IsWindowVisible(root_handle) == 0 ||
                ::IsWindowEnabled(root_handle) == 0
            )
            {
                return HWND_DESKTOP;
            }

            return root_handle;
        }

        /*!
            \brief Shows a task dialog.

            \param widget_handle    A widget handle.
            \param caption          A caption.
            \param text1            A text #1.
            \param text2            A text #2.
            \param source_file_name A source file name.
            \param source_file_line A source file line number.
            \param source_function  A source function.
            \param encoder          An encoder.
        */
        static void show_task_dialog(
            const widget_handle_type widget_handle,
            const string_type&       caption,
            const string_type&       text1,
            const string_type&       text2,
            const string_type&       source_file_name,
            const int                source_file_line,
            const string_type&       source_function,
            const encoder_type&      encoder
        )
        {
#if defined(NDEBUG)
            show_task_dialog_impl(
                widget_handle,
                encoder.encode(caption),
                encoder.encode(text1),
                encoder.encode(text2)
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
                widget_handle,
                encoder.encode(caption),
                encoder.encode(text1),
                encoder.encode(text2 + stream.str())
            );
#endif
        }


    private:
        // static functions

        static void show_task_dialog_impl(
            const widget_handle_type widget_handle,
            const std::wstring&      caption,
            const std::wstring&      text1,
            const std::wstring&      text2
        )
        {
            const ::HINSTANCE handle = ::LoadLibraryW(L"COMCTL32.DLL");
            BOOST_SCOPE_EXIT((handle))
            {
                if (handle)
                    ::FreeLibrary(handle);
            } BOOST_SCOPE_EXIT_END;
            if (!handle)
            {
                show_message_box(widget_handle, caption, text1, text2);
                return;
            }

            typedef decltype(::TaskDialog)* task_dialog_ptr_type;
            task_dialog_ptr_type p_task_dialog =
                reinterpret_cast<task_dialog_ptr_type>(
                    ::GetProcAddress(handle, "TaskDialog")
                );
            if (!p_task_dialog)
            {
                show_message_box(widget_handle, caption, text1, text2);
                return;
            }

            p_task_dialog(
                widget_handle,
                ::GetModuleHandle(NULL),
                caption.c_str(),
                text1.c_str(),
                text2.c_str(),
                TDCBF_OK_BUTTON,
                TD_ERROR_ICON,
                NULL
            );
        }

        static void show_message_box(
            const widget_handle_type widget_handle,
            const std::wstring&      caption,
            const std::wstring&      text1,
            const std::wstring&      text2
        )
        {
            const std::wstring text = text1 + L"\n\n" + text2;
            ::MessageBoxW(
                widget_handle,
                text.c_str(),
                caption.c_str(),
                MB_OK | MB_ICONERROR
            );
        }


        // forbidden operations

        alert();


   };


}}}


#endif
