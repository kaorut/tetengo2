/*! \file
    \brief The definition of tetengo2::detail::windows::timer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <chrono>
#include <functional>
#include <system_error>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/timer.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows {
    class timer::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        impl(
            const gui::widget::widget&       widget,
            std::function<void(bool&)>       procedure,
            const std::chrono::milliseconds& interval,
            const bool                       once_only)
        : m_window_handle{ reinterpret_cast<::HWND>(
              static_cast<const widget::windows_widget_details_type&>(widget.details()).handle) },
          m_procedure{ std::move(procedure) }, m_once_only{ once_only }, m_id{ ::SetTimer(
                                                                             m_window_handle,
                                                                             reinterpret_cast<::UINT_PTR>(this),
                                                                             static_cast<::UINT>(interval.count()),
                                                                             timer_proc) }
        {
            if (stopped_impl())
            {
                BOOST_THROW_EXCEPTION((std::system_error{
                    std::error_code{ static_cast<int>(::GetLastError()), win32_category() }, "Can't start timer." }));
            }
        }

        ~impl() noexcept
        {
            stop_impl();
        }

        // functions

        bool stopped_impl() const
        {
            return m_id == 0;
        }

        void stop_impl()
        {
            ::KillTimer(m_window_handle, m_id);
            m_id = 0;
        }


    private:
        // static functions

        static void CALLBACK timer_proc(
            TETENGO2_STDALT_MAYBE_UNUSED const ::HWND  window_handle,
            TETENGO2_STDALT_MAYBE_UNUSED const ::UINT  message,
            const ::UINT_PTR                           id,
            TETENGO2_STDALT_MAYBE_UNUSED const ::DWORD elapsed_time)
        {
            auto* const p_timer = reinterpret_cast<impl*>(id);
            assert(p_timer);

            if (p_timer->m_once_only)
                p_timer->stop_impl();

            bool stop_ = false;
            p_timer->m_procedure(stop_);
            if (!p_timer->stopped_impl() && stop_)
                p_timer->stop_impl();
        }


        // variables

        const ::HWND m_window_handle;

        const std::function<void(bool&)> m_procedure;

        const bool m_once_only;

        ::UINT_PTR m_id;
    };


    timer::timer(
        const gui::widget::widget&       widget,
        std::function<void(bool&)>       procedure,
        const std::chrono::milliseconds& interval,
        const bool                       once_only)
    : m_p_impl{ std::make_unique<impl>(widget, std::move(procedure), interval, once_only) }
    {}

    timer::~timer() = default;

    bool timer::stopped_impl() const
    {
        return m_p_impl->stopped_impl();
    }

    void timer::stop_impl()
    {
        m_p_impl->stop_impl();
    }
}
