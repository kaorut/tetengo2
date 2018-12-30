/*! \file
    \brief The definition of tetengo2::gui::timer.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/timer.h>
#include <tetengo2/gui/timer.h>


namespace tetengo2::gui {
    class timer::impl : private boost::noncopyable
    {
    public:
        // types

        using widget_type = timer::widget_type;

        using procedure_type = timer::procedure_type;

        //! The interval type.
        using inteval_type = timer::inteval_type;


        // constructors and destructor

        impl(const widget_type& widget, procedure_type procedure, const inteval_type& interval, const bool once_only)
        : m_p_timer_details{
              detail::gui_detail_impl_set().crate_timer(widget, std::move(procedure), interval, once_only)
          }
        {}


        // functions

        bool stopped() const
        {
            return m_p_timer_details->stopped();
        }

        void stop()
        {
            m_p_timer_details->stop();
        }


    private:
        // types

        using timer_details_type = detail::base::timer;


        // variables

        const std::unique_ptr<timer_details_type> m_p_timer_details;
    };


    timer::timer(
        const widget_type&  widget,
        procedure_type      procedure,
        const inteval_type& interval,
        const bool          once_only)
    : m_p_impl{ std::make_unique<impl>(widget, std::move(procedure), interval, once_only) }
    {}

    timer::~timer() = default;

    bool timer::stopped() const
    {
        return m_p_impl->stopped();
    }

    void timer::stop()
    {
        m_p_impl->stop();
    }
}
