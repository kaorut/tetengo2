/*! \file
    \brief The definition of tetengo2::gui::win32::alert.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ALERT_H)
#define TETENGO2_GUI_WIN32_ALERT_H

#include <exception>
#include <functional>
#include <sstream>
#include <string>

#include <boost/concept_check.hpp>
#include <boost/format.hpp>

#define OEMRESOURCE
#include <windows.h>
#include <commctrl.h>

#include "tetengo2.gui.HandleConcept.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an alert for Win32 platforms.

        \param WindowHandle A window handle type. It must conform to
                            tetengo2::gui::HandleConcept<WindowHandle>.
        \param Encode       An encoding unary functor type. It must conform to
                            boost::AdaptableUnaryFunctionConcept<Encode, std::wstring, std::string>.
    */
    template <
        typename WindowHandle,
        template <typename Target, typename Source>
        class    Encode
    >
    class alert :
        public std::binary_function<WindowHandle, std::exception, void>
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
                AdaptableUnaryFunctionConcept
            );
        };


    public:
        // types

        //! The window handle type.
        typedef WindowHandle window_handle_type;

        //! The encoding unary functor type.
        typedef Encode<std::wstring, std::string> encode_type;


       // constructors and destructor

        /*!
            \brief Alerts a fatal error.

            \param window_handle A window handle.
            \param exception     An exception.
        */
        void operator()(
            const window_handle_type window_handle,
            const std::exception&    exception =
                std::runtime_error("Unknown Error!")
        )
        const
        throw ()
        {
            try
            {
                ::TaskDialog(
                    window_handle,
                    ::GetModuleHandle(NULL),
                    L"Alert",
                    encode_type()(typeid(exception).name()).c_str(),
                    encode_type()(exception.what()).c_str(),
                    TDCBF_OK_BUTTON,
                    TD_ERROR_ICON,
                    NULL
                );
            }
            catch (...)
            {}

        }

    };
}}}

#endif
