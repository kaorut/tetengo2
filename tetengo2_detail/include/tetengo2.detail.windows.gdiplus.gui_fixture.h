/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::gui_fixture.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GDIPLUS_GUIFIXTURE_H)
#define TETENGO2_DETAIL_WINDOWS_GDIPLUS_GUIFIXTURE_H

#include <cstddef>
#include <stdexcept>
#include <system_error>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max

#include "tetengo2.cpp11.h"


namespace tetengo2 { namespace detail { namespace windows { namespace gdiplus
{
    /*!
        \brief The class for a detail implementation of a GUI fixture.
    */
    class gui_fixture : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a GUI fixture.

            \throw std::system_error When an initialization fails.
        */
        gui_fixture()
        :
        m_gdiplus_token(setup_gdiplus())
        {}

        /*!
            \brief Destroys the detail implementation of a GUI fixture.
        */
        ~gui_fixture()
        TETENGO2_CPP11_NOEXCEPT
        {
            teardown_gdiplus(m_gdiplus_token);
        }


    private:
        // static functions

        static ::ULONG_PTR setup_gdiplus()
        {
            const Gdiplus::GdiplusStartupInput input;
            ::ULONG_PTR token = NULL;

            if (Gdiplus::GdiplusStartup(&token, &input, NULL) != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::errc::io_error,
                        std::generic_category(),
                        "Can't start up GDI+!"
                    )
                );
            }

            return token;
        }

        static void teardown_gdiplus(const ::ULONG_PTR gdiplus_token)
        TETENGO2_CPP11_NOEXCEPT
        {
            Gdiplus::GdiplusShutdown(gdiplus_token);
        }


        // variables

        const ::ULONG_PTR m_gdiplus_token;


    };


}}}}


#endif
