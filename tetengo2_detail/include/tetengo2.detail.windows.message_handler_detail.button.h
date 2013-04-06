/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::button.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_BUTTON_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_BUTTON_H

#include <system_error>

#include <boost/optional.hpp>
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
        boost::optional< ::LRESULT> on_timer(Button& button, const ::WPARAM w_param, const ::LPARAM l_param)
        {
            suppress_unused_variable_warning(l_param);

            if (w_param == WM_LBUTTONDOWN)
            {
                if (
                    button.mouse_observer_set().clicked().empty() &&
                    button.mouse_observer_set().doubleclicked().empty()
                )
                {
                    return boost::none;
                }

                const auto result = ::KillTimer(button.details()->handle.get(), WM_LBUTTONDOWN);
                if (result == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(::GetLastError(), win32_category()), "Can't kill a timer for mouse clicks."
                        )
                    );
                }

                return boost::make_optional< ::LRESULT>(0);
            }

            return boost::none;
        }

        template <typename Button>
        boost::optional< ::LRESULT> on_tetengo2_command(Button& button, const ::WPARAM w_param, const ::LPARAM l_param)
        {
            suppress_unused_variable_warning(w_param, l_param);

            button.mouse_observer_set().clicked()();

            return boost::make_optional< ::LRESULT>(0);
        }


    }


}}}}


#endif
#endif
