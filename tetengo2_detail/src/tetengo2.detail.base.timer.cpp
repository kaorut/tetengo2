/*! \file
    \brief The definition of tetengo2::detail::base::timer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <chrono>
#include <functional>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/timer.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::base {
    class timer::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED std::function<void(bool&)> procedure,
            TETENGO2_STDALT_MAYBE_UNUSED const std::chrono::milliseconds& interval,
            TETENGO2_STDALT_MAYBE_UNUSED const bool                       once_only)
        {}


        // functions

        bool stopped(const timer& self) const
        {
            return self.stopped_impl();
        }

        void stop(timer& self)
        {
            self.stop_impl();
        }
    };


    timer::timer(
        const gui::widget::widget&       widget,
        std::function<void(bool&)>       procedure,
        const std::chrono::milliseconds& interval,
        const bool                       once_only)
    : m_p_impl{ std::make_unique<impl>(widget, std::move(procedure), interval, once_only) }
    {}

    timer::~timer() = default;

    bool timer::stopped() const
    {
        return m_p_impl->stopped(*this);
    }

    void timer::stop()
    {
        m_p_impl->stop(*this);
    }
}
