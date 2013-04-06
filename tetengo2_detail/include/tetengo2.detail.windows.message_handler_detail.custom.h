/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::custom_control.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_CUSTOMCONTROL_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_CUSTOMCONTROL_H

#include <memory>
#include <system_error>

#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.utility.h"


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail
{
    namespace custom_control
    {
        template <typename CustomControl>
        boost::optional< ::LRESULT> on_erase_background(
            CustomControl& custom_control,
            const ::WPARAM w_param,
            const ::LPARAM l_param
        )
        {
            suppress_unused_variable_warning(w_param, l_param);

            if (custom_control.paint_observer_set().paint().empty())
                return boost::none;

            return boost::make_optional< ::LRESULT>(TRUE);
        }

        template <typename CustomControl>
        boost::optional< ::LRESULT> on_paint(CustomControl& custom_control, const ::WPARAM w_param, const ::LPARAM l_param)
        {
            suppress_unused_variable_warning(w_param, l_param);

            if (custom_control.paint_observer_set().paint().empty())
                return boost::none;

            ::PAINTSTRUCT paint_struct = {};
            if (!::BeginPaint(custom_control.details()->handle.get(), &paint_struct))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't begin paint.")
                );
            }
            BOOST_SCOPE_EXIT((&custom_control)(&paint_struct))
            {
                ::EndPaint(custom_control.details()->handle.get(), &paint_struct);
            } BOOST_SCOPE_EXIT_END;

            const std::unique_ptr<typename CustomControl::canvas_type> p_canvas = custom_control.create_canvas();

            custom_control.paint_observer_set().paint()(*p_canvas);

            return boost::make_optional< ::LRESULT>(0);
        }


    }


}}}}


#endif
#endif
