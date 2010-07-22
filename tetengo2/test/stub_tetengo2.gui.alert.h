/*! \file
    \brief The definition of stub_tetengo2::gui::alert.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ALERT_H)
#define STUBTETENGO2_GUI_ALERT_H

#include <cstddef>
#include <exception>
#include <functional>
#include <stdexcept>

#include <boost/exception/all.hpp>


namespace stub_tetengo2 { namespace gui
{
    template <
        typename WindowHandle,
        typename UiEncoder,
        typename ExceptionEncoder
    >
    class alert : public std::unary_function<std::exception, void>
    {
    public:
        // types

        typedef WindowHandle window_handle_type;

        typedef UiEncoder ui_encoder_type;

        typedef ExceptionEncoder exception_encoder_type;


        // constructors

        alert(const window_handle_type window_handle = NULL)
        throw ()
        {}


        // functions

        void operator()(const boost::exception& exception)
        const
        throw ()
        {}

        void operator()(
            const std::exception& exception =
                std::runtime_error("Unknown Error!")
        )
        const
        throw ()
        {}


    };


}}

#endif
