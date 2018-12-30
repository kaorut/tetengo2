/*! \file
    \brief The definition of tetengo2::detail::stub::timer.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_TIMER_H)
#define TETENGO2_DETAIL_STUB_TIMER_H

#include <chrono>
#include <functional>
#include <memory>

#include <tetengo2/detail/base/timer.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::stub {
    /*!
        \brief The class for a detail implementation of a timer.
    */
    class timer : public base::timer
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a timer.

            \param widget    A widget.
            \param procedure A procedure called by this timer.
            \param interval  An interval.
            \param once_only Set true to execute the procedure once only.
        */
        timer(
            const gui::widget::widget&       widget,
            std::function<void(bool&)>       procedure,
            const std::chrono::milliseconds& interval,
            bool                             once_only);

        /*!
            \brief Destroys the detail implementation of a timer.
        */
        virtual ~timer();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool stopped_impl() const override;

        virtual void stop_impl() override;
    };
}


#endif
