/*! \file
    \brief The definition of tetengo2::detail::windows::gui_fixture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory> // IWYU pragma: keep
#include <system_error> // IWYU pragma: keep

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <ObjBase.h>
#include <Windows.h>
#// prevent sort by ClangFormat
#include <CommCtrl.h>

#include <tetengo2/detail/windows/error_category.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/gdiplus/gui_fixture.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/gui_fixture.h>
#include <tetengo2/detail/windows/windows_version.h>


namespace tetengo2::detail::windows {
    class gui_fixture::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        impl() : m_p_gdiplus_gui_fixture{}
        {
            check_platform();
            setup_common_controls();
            setup_com();
            setup_gdiplus();
        }


    private:
        // static functions

        static void check_platform()
        {
            if (!on_windows_vista_or_later())
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_OLD_WIN_VERSION, win32_category() },
                                                          "This program can't run on this platform." }));
            }
        }

        static void setup_common_controls()
        {
            ::INITCOMMONCONTROLSEX enabled_common_controls{};
            enabled_common_controls.dwSize = sizeof(::INITCOMMONCONTROLSEX);
            enabled_common_controls.dwICC = ICC_WIN95_CLASSES | ICC_DATE_CLASSES | ICC_COOL_CLASSES |
                                            ICC_INTERNET_CLASSES | ICC_PAGESCROLLER_CLASS | ICC_NATIVEFNTCTL_CLASS |
                                            ICC_STANDARD_CLASSES | ICC_LINK_CLASS;
            if (::InitCommonControlsEx(&enabled_common_controls) == FALSE)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "Can't initialize common controls!" }));
            }
        }

        static void setup_com()
        {
            const auto result = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
            if (result != S_OK)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ result, win32_category() }, "Can't initlaize COM." }));
            }
        }


        // variables

        std::unique_ptr<base::gui_fixture> m_p_gdiplus_gui_fixture;


        // functions

        void setup_gdiplus()
        {
            m_p_gdiplus_gui_fixture = std::make_unique<gdiplus::gui_fixture>();
        }
    };


    gui_fixture::gui_fixture() : m_p_impl{ std::make_unique<impl>() } {}

    gui_fixture::~gui_fixture() = default;
}
