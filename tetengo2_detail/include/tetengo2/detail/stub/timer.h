/*! \file
    \brief The definition of tetengo2::detail::stub::timer.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_TIMER_H)
#define TETENGO2_DETAIL_STUB_TIMER_H

#include <chrono>
#include <functional>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/utility.h>


namespace tetengo2 { namespace detail { namespace stub
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
        {
            suppress_unused_variable_warning(widget, procedure, interval, once_only);
        }


        // functions

        /*!
            \brief Returns the stopped status.

            \return The stopped status.
        */
        bool stopped()
        const
        {
            return true;
        }

        /*!
            \brief Stops the timer.
        */
        void stop()
        {}


    };


}}}


#endif
