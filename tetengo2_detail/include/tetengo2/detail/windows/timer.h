/*! \file
    \brief The definition of tetengo2::detail::windows::timer.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_TIMER_H)
#define TETENGO2_DETAIL_WINDOWS_TIMER_H

#include <cassert>
#include <chrono>
#include <functional>
#include <system_error>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
//#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/utility.h>


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
            \param once_only Set true to execute the procedure once only.
        */
        template <typename Widget>
        timer(
            const Widget&                    widget,
            std::function<void (bool&)>      procedure,
            const std::chrono::milliseconds& interval,
            const bool                       once_only
        )
        :
        m_window_handle(widget.details().handle.get()),
        m_procedure(std::move(procedure)),
        m_once_only(once_only),
        m_id(
            ::SetTimer(
                m_window_handle,
                reinterpret_cast< ::UINT_PTR>(this),
                static_cast< ::UINT>(interval.count()),
                timer_proc
            )
        )
        {
            if (stopped())
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error{ std::error_code{ ::GetLastError(), win32_category() }, "Can't start timer." }
                );
            }
        }

        /*!
            \brief Destroys the detail implementation of a timer.
        */
        ~timer()
        TETENGO2_STDALT_NOEXCEPT
        {
            stop();
        }


        // functions

        /*!
            \brief Returns the stopped status.

            \return The stopped status.
        */
        bool stopped()
        const
        {
            return m_id == 0;
        }

        /*!
            \brief Stops the timer.
        */
        void stop()
        {
            ::KillTimer(m_window_handle, m_id);
            m_id = 0;
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

            timer* const p_timer = reinterpret_cast<timer*>(id);
            assert(p_timer);

            if (p_timer->m_once_only)
                p_timer->stop();

            bool stop_ = false;
            p_timer->m_procedure(stop_);
            if (!p_timer->stopped() && stop_)
                p_timer->stop();
        }


        // variables

        const ::HWND m_window_handle;

        const std::function<void (bool&)> m_procedure;

        const bool m_once_only;

        ::UINT_PTR m_id;


    };


}}}


#endif
