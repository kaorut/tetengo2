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

#include "tetengo2.nothrow.h"
#include "tetengo2.gui.HandleConcept.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The unary functor class template for an alert for Win32
               platforms.

        \param WindowHandle A window handle type. It must conform to
                            tetengo2::gui::HandleConcept<WindowHandle>.
        \param Encode       An encoding unary functor type. The type
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
        alert(const window_handle_type window_handle = NULL)
        TETENGO2_NOTHROW
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
        TETENGO2_NOTHROW
        {
            try
            {
                ::TaskDialog(
                    m_window_handle,
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


    private:
        // types

        typedef Encode<std::wstring, std::string> encode_type;


        // variables

        const window_handle_type m_window_handle;


    };


}}}

#endif
