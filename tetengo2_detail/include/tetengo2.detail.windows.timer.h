/*! \file
    \brief The definition of tetengo2::detail::windows::timer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_TIMER_H)
#define TETENGO2_DETAIL_WINDOWS_TIMER_H

//#include <cassert>
//#include <chrono>
#include <functional>
//#include <system_error>
//#include <utility>

//#include <boost/noncopyable.hpp>
//#include <boost/throw_exception.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
//#include <intsafe.h>
//#include <stdint.h>
//#pragma warning(pop)
//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a timer.
    */
    class timer : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a timer.

            \tparam Widget A widget type.

            \param widget    A widget.
            \param procedure A procedure called by this timer.
            \param interval  An interval.
        */
        template <typename Widget>
        timer(const Widget& widget, std::function<void ()> procedure, std::chrono::milliseconds interval)
        :
        m_window_handle(widget.details()->handle.get()),
        m_procedure(std::move(procedure)),
        m_id(
            ::SetTimer(
                m_window_handle,
                reinterpret_cast< ::UINT_PTR>(&m_procedure),
                static_cast< ::UINT>(interval.count()),
                timer_proc
            )
        )
        {
            if (m_id == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(::GetLastError(), win32_category()), "Can't start timer.")
                );
            }
        }

        /*!
            \brief Destroys the detail implementation of a timer.
        */
        ~timer()
        TETENGO2_CPP11_NOEXCEPT
        {
            ::KillTimer(m_window_handle, m_id);
        }


    private:
        // static functions

        static void CALLBACK timer_proc(
            const ::HWND     window_handle,
            const ::UINT     message,
            const ::UINT_PTR id,
            const ::DWORD    elapsed_time
        )
        {
            suppress_unused_variable_warning(window_handle, message, elapsed_time);

            const std::function<void ()>* const p_procedure = reinterpret_cast<const std::function<void ()>*>(id);
            assert(p_procedure);

            (*p_procedure)();
        }


        // variables

        const ::HWND m_window_handle;

        const std::function<void ()> m_procedure;

        const ::UINT_PTR m_id;


    };


}}}


#endif
