/*! \file
    \brief The definition of tetengo2::gui::timer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TIMER_H)
#define TETENGO2_GUI_TIMER_H

#include <chrono>
#include <functional>
#include <utility>

#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace gui {
    /*!
        \brief The class template for a timer.

        \tparam Widget       A widget type.
        \tparam TimerDetails A detail implementation type of a timer.
    */
    template <typename Widget, typename TimerDetails>
    class timer : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        using widget_type = Widget;

        //! The timer details type.
        using timer_details_type = TimerDetails;

        /*!
            \brief The procedure type.

            \param stop Assign true to stop the timer.
        */
        using procedure_type = std::function<void(bool& stop)>;

        //! The interval type.
        using inteval_type = std::chrono::milliseconds;


        // constructors and destructor

        /*!
            \brief Creates a timer.

            \param widget    A widget.
            \param procedure A procedure called by this timer.
            \param interval  An interval.
            \param once_only Set true to execute the procedure once only.
        */
        timer(const widget_type& widget, procedure_type procedure, const inteval_type& interval, const bool once_only)
        : m_timer_details{ widget, std::move(procedure), interval, once_only }
        {}


        // functions

        /*!
            \brief Returns the stopped status.

            \return The stopped status.
        */
        bool stopped() const
        {
            return m_timer_details.stopped();
        }

        /*!
            \brief Stops the timer.
        */
        void stop()
        {
            m_timer_details.stop();
        }


    private:
        // variables

        timer_details_type m_timer_details;
    };


}}

#endif
