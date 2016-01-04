/*! \file
    \brief The definition of tetengo2::detail::windows::alert.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ALERT_H)
#define TETENGO2_DETAIL_WINDOWS_ALERT_H

#include <iomanip>
#include <sstream>
#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/scope_exit.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>

#include <tetengo2/text.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of an alert.
    */
    class alert : private boost::noncopyable
    {
    public:
        // types

        //! The widget handle type.
        using widget_handle_type = ::HWND;


        // static functions

        /*!
            \brief Returns the root ancestor widget handle.

            \param widget_handle A widget handle.

            \return The root ancestor widget handle.
        */
        static widget_handle_type root_ancestor_widget_handle(const widget_handle_type widget_handle)
        {
            const auto root_handle = ::GetAncestor(widget_handle, GA_ROOT);

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

            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param widget_handle    A widget handle.
            \param caption          A caption.
            \param text1            A text #1.
            \param text2            A text #2.
            \param source_file_name A source file name.
            \param source_file_line A source file line number.
            \param encoder          An encoder.
        */
        template <typename String, typename Encoder>
        static void show_task_dialog(
            const widget_handle_type widget_handle,
            const String&            caption,
            const String&            text1,
            const String&            text2,
            const String&            source_file_name,
            const int                source_file_line,
            const Encoder&           encoder
        )
        {
#if defined(NDEBUG)
            show_task_dialog_impl(
                widget_handle, encoder.encode(caption), encoder.encode(text1), encoder.encode(text2)
            );
#else
            std::basic_ostringstream<typename String::value_type> stream{};
            stream <<
                std::endl <<
                std::endl <<
                TETENGO2_TEXT("in ") <<
                source_file_name <<
                TETENGO2_TEXT(" (") <<
                source_file_line <<
                TETENGO2_TEXT(")");

            show_task_dialog_impl(
                widget_handle, encoder.encode(caption), encoder.encode(text1), encoder.encode(text2 + stream.str())
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
            const auto handle = ::LoadLibraryW(L"COMCTL32.DLL");
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

            using task_dialog_ptr_type = decltype(::TaskDialog)*;
            auto p_task_dialog = reinterpret_cast<task_dialog_ptr_type>(::GetProcAddress(handle, "TaskDialog"));
            if (!p_task_dialog)
            {
                show_message_box(widget_handle, caption, text1, text2);
                return;
            }

            p_task_dialog(
                widget_handle,
                ::GetModuleHandle(nullptr),
                caption.c_str(),
                text1.c_str(),
                text2.c_str(),
                TDCBF_OK_BUTTON,
                TD_ERROR_ICON,
                nullptr
            );
        }

        static void show_message_box(
            const widget_handle_type widget_handle,
            const std::wstring&      caption,
            const std::wstring&      text1,
            const std::wstring&      text2
        )
        {
            const auto text = text1 + L"\n\n" + text2;
            ::MessageBoxW(widget_handle, text.c_str(), caption.c_str(), MB_OK | MB_ICONERROR);
        }


        // forbidden operations

        alert()
        = delete;


   };


}}}


#endif
