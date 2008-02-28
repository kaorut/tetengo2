/*! \file
    \brief The definition of tetengo2::gui::win32::gui_initializer_finalizer.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIINITIALIZERFINALIZER_H)
#define TETENGO2_GUI_GUIINITIALIZERFINALIZER_H

#include <cstddef>
#include <stdexcept>

#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class for a GUI initialization and finalization management.
    */
    class gui_initializer_finalizer : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a GUI initialization and finalization management.

            \throw std::runtime_error When a GUI cannot be initialized.
        */
        gui_initializer_finalizer()
        :
        m_gdiplus_token(get_gdiplus_token())
        {
            initialize_common_controls();
        }

        /*!
            \brief Destroys the GUI initialization and finalization
                   management.
        */
        ~gui_initializer_finalizer()
        throw ()
        {
            Gdiplus::GdiplusShutdown(m_gdiplus_token);
        }


    private:
        // static functions

        static ::ULONG_PTR get_gdiplus_token()
        {
            const Gdiplus::GdiplusStartupInput input;
            ::ULONG_PTR token = NULL;

            if (Gdiplus::GdiplusStartup(&token, &input, NULL) != Gdiplus::Ok)
                throw std::runtime_error("Can't start up GDI+!");

            return token;
        }

        static void initialize_common_controls()
        {
            ::INITCOMMONCONTROLSEX enabled_common_controls;
            enabled_common_controls.dwSize = sizeof(::INITCOMMONCONTROLSEX);
            enabled_common_controls.dwICC =
                ICC_WIN95_CLASSES |
                ICC_DATE_CLASSES |
                ICC_COOL_CLASSES |
                ICC_INTERNET_CLASSES |
                ICC_PAGESCROLLER_CLASS |
                ICC_NATIVEFNTCTL_CLASS |
                ICC_STANDARD_CLASSES |
                ICC_LINK_CLASS;
            if (::InitCommonControlsEx(&enabled_common_controls) == 0)
                throw std::runtime_error("Can't initialize common controls!");
        }


        // variables

        const ::ULONG_PTR m_gdiplus_token;


    };


}}}

#endif
