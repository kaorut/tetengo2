/*! \file
    \brief The definition of tetengo2::gui::timer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TIMER_H)
#define TETENGO2_GUI_TIMER_H

#include <chrono>
#include <functional>
#include <utility>

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui
{
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
        typedef Widget widget_type;

        //! The detail implementation type of a timer.
        typedef TimerDetails timer_details_type;

        /*!
            \brief The procedure type.

            \param stop Assign true to stop the timer.
        */
        typedef std::function<void (bool& stop)> procedure_type;

        //! The interval type.
        typedef std::chrono::milliseconds inteval_type;


        // constructors and destructor

        /*!
            \brief Creates a timer.

            \param widget    A widget.
            \param procedure A procedure called by this timer.
            \param interval  An interval.
        */
        timer(const widget_type& widget, procedure_type procedure, inteval_type interval)
        :
        m_timer_details(widget, std::move(procedure), std::move(interval))
        {}


        // functions

        /*!
            \brief Returns the stopped status.

            \return The stopped status.
        */
        bool stopped()
        const
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
