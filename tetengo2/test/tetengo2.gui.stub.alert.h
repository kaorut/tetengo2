/*! \file
    \brief The definition of tetengo2::gui::stub::alert.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_STUB_ALERT_H)
#define TETENGO2_GUI_STUB_ALERT_H

#include <exception>
#include <functional>

#include <boost/concept_check.hpp>

#include "tetengo2.gui.HandleConcept.h"


namespace tetengo2 { namespace gui { namespace stub
{
    /*!
        \brief The unary functor class template for an alert for testing.

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
        throw ()
        {}


        // functions

        /*!
            \brief Alerts a fatal error.

            Does nothing actually.

            \param exception An exception.
        */
        void operator()(
            const std::exception& exception =
                std::runtime_error("Unknown Error!")
        )
        const
        throw ()
        {}


    };


}}}

#endif
