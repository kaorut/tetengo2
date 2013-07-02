/*! \file
    \brief The definition of tetengo2::gui::timer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TIMER_H)
#define TETENGO2_GUI_TIMER_H

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


        // constructors and destructor

        /*!
            \brief Creates a timer.

            \param widget A widget.
        */
        explicit timer(const widget_type& widget)
        :
        m_timer_details(widget)
        {}


    private:
        // variables

        const timer_details_type m_timer_details;


    };


}}

#endif
