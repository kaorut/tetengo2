/*! \file
    \brief The definition of tetengo2::gui::timer.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TIMER_H)
#define TETENGO2_GUI_TIMER_H

#include <chrono>
#include <functional>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui {
    /*!
        \brief The class for a timer.
    */
    class timer : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        using widget_type = widget::widget;

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
        timer(const widget_type& widget, procedure_type procedure, const inteval_type& interval, bool once_only);

        /*!
            \brief Destroys the timer.
        */
        ~timer();


        // functions

        /*!
            \brief Returns the stopped status.

            \return The stopped status.
        */
        bool stopped() const;

        /*!
            \brief Stops the timer.
        */
        void stop();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}

#endif
