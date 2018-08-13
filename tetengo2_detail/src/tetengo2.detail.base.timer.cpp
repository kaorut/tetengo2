/*! \file
    \brief The definition of tetengo2::detail::base::timer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/timer.h>


namespace tetengo2::detail::base {
    class timer::impl : private boost::noncopyable
    {
    public:
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


    timer::timer() : m_p_impl{ std::make_unique<impl>() } {}

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
