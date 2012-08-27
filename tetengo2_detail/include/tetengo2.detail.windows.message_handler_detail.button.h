/*! \file
    \brief The definition of
           tetengo2::detail::windows::message_handler_detail::button.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_BUTTON_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_BUTTON_H

#include <memory>
#include <system_error>
#include <tuple>

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


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail
{
    namespace button
    {
        template <typename Button>
        boost::optional< ::LRESULT> on_tetengo2_command(
            Button&        button,
            const ::WPARAM w_param,
            const ::LPARAM l_param
        )
        {
            button.mouse_observer_set().clicked()();

            return boost::make_optional< ::LRESULT>(0);
        }


    }


}}}}


#endif
#endif
