/*! \file
    \brief The definition of tetengo2::detail::windows::alert.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

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

#include <tetengo2/detail/windows/alert.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>


namespace tetengo2 { namespace detail { namespace windows
{
    class alert::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = alert::string_type;

        using widget_handle_type = alert::widget_handle_type;


        // static functions

        static const alert& instance()
        {
            static const alert singleton{};
            return singleton;
        }


        // constructors and destructor

        impl()
        :
        m_encoder(type_list::internal_encoding_type{}, text::encoding::locale<std::wstring>{})
        {}


        // functions

        widget_handle_type root_ancestor_widget_handle_impl(const widget_handle_type widget_handle)
        const
        {
            const auto root_handle = ::GetAncestor(to_hwnd(widget_handle), GA_ROOT);

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

        virtual void show_task_dialog_impl(
            const widget_handle_type widget_handle,
            const string_type&       caption,
            const string_type&       text1,
            const string_type&       text2,
            const string_type&       source_file_name,
            const int                source_file_line
        )
        const
        {
#if defined(NDEBUG)
            show_task_dialog_impl(
                widget_handle, m_encoder.encode(caption), m_encoder.encode(text1), m_encoder.encode(text2)
            );
#else
            std::basic_ostringstream<string_type::value_type> stream{};
            stream <<
                std::endl <<
                std::endl <<
                TETENGO2_TEXT("in ") <<
                source_file_name <<
                TETENGO2_TEXT(" (") <<
                source_file_line <<
                TETENGO2_TEXT(")");

            show_task_dialog_impl(
                widget_handle,
                m_encoder.encode(caption),
                m_encoder.encode(text1),
                m_encoder.encode(text2 + stream.str())
            );
#endif
        }


    private:
        // types

        using encoder_type = text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::wstring>>;


        // static functions

        static ::HWND to_hwnd(const void* handle)
        {
            return reinterpret_cast< ::HWND>(const_cast<void*>(handle));
        }

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
                to_hwnd(widget_handle),
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
            ::MessageBoxW(to_hwnd(widget_handle), text.c_str(), caption.c_str(), MB_OK | MB_ICONERROR);
        }


        // variables

        const encoder_type m_encoder;


    };


    const alert& alert::instance()
    {
        return impl::instance();
    }

    alert::~alert()
    = default;

    alert::alert()
    :
    m_p_impl(stdalt::make_unique<impl>())
    {}

    alert::widget_handle_type alert::root_ancestor_widget_handle_impl(const widget_handle_type widget_handle)
    const
    {
        return m_p_impl->root_ancestor_widget_handle_impl(widget_handle);
    }

    void alert::show_task_dialog_impl(
        const widget_handle_type widget_handle,
        const string_type&       caption,
        const string_type&       text1,
        const string_type&       text2,
        const string_type&       source_file_name,
        const int                source_file_line
    )
    const
    {
        m_p_impl->show_task_dialog_impl(widget_handle, caption, text1, text2, source_file_name, source_file_line);
    }


}}}
