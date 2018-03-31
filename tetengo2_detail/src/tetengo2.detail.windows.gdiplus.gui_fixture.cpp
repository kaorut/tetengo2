/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::gui_fixture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

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
#include <Windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max

#include <tetengo2/detail/windows/gdiplus/error_category.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/gdiplus/gui_fixture.h>


namespace tetengo2::detail::windows::gdiplus {
    class gui_fixture::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        impl() : m_gdiplus_token{ setup_gdiplus() } {}

        ~impl() noexcept
        {
            teardown_gdiplus(m_gdiplus_token);
        }


    private:
        // static functions

        static ::ULONG_PTR setup_gdiplus()
        {
            const Gdiplus::GdiplusStartupInput input;
            ::ULONG_PTR                        token = 0;

            const auto status = Gdiplus::GdiplusStartup(&token, &input, nullptr);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't start up GDI+!" }));
            }

            return token;
        }

        static void teardown_gdiplus(const ::ULONG_PTR gdiplus_token) noexcept
        {
            Gdiplus::GdiplusShutdown(gdiplus_token);
        }


        // variables

        const ::ULONG_PTR m_gdiplus_token;
    };


    gui_fixture::gui_fixture() : m_p_impl{ stdalt::make_unique<impl>() } {}

    gui_fixture::~gui_fixture() = default;
}
