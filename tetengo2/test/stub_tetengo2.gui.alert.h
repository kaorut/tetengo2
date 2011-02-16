/*! \file
    \brief The definition of stub_tetengo2::gui::alert.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ALERT_H)
#define STUBTETENGO2_GUI_ALERT_H

#include <cstddef>
#include <exception>
#include <functional>
#include <stdexcept>

#include <boost/exception/all.hpp>

#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename WidgetHandle,
        typename UiEncoder,
        typename ExceptionEncoder
    >
    class alert : public std::unary_function<std::exception, void>
    {
    public:
        // types

        typedef WidgetHandle widget_handle_type;

        typedef UiEncoder ui_encoder_type;

        typedef ExceptionEncoder exception_encoder_type;


        // constructors

        explicit alert(const widget_handle_type widget_handle = NULL)
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        void operator()(const boost::exception& exception)
        const
        TETENGO2_CPP0X_NOEXCEPT
        {}

        void operator()(
            const std::exception& exception =
                std::runtime_error("Unknown Error!")
        )
        const
        TETENGO2_CPP0X_NOEXCEPT
        {}


    };


}}

#endif
