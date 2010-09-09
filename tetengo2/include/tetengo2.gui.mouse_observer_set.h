/*! \file
    \brief The definition of tetengo2::gui::mouse_observer_set.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MOUSEOBSERVERSET_H)
#define TETENGO2_GUI_MOUSEOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>

#include "tetengo2.cpp0x_keyword.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a mouse observer set.
    */
    class mouse_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of clicked.
        */
        typedef void clicked_type();

        //! \return The signal type of clicked.
        typedef boost::signals2::signal<clicked_type> clicked_signal_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse observer set.
        */
        mouse_observer_set()
        :
        m_clicked()
        {}

        /*!
            \brief Destroys the mouse observer set.
        */
        ~mouse_observer_set()
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the observer called when a mouse button is clicked.

            \return The observer called when a mouse button is clicked.
        */
        const clicked_signal_type& clicked()
        const
        {
            return m_clicked;
        }

        /*!
            \brief Returns the observer called when a mouse button is clicked.

            \return The observer called when a mouse button is clicked.
        */
        clicked_signal_type& clicked()
        {
            return m_clicked;
        }


    private:
        // variables

        clicked_signal_type m_clicked;


    };


}}

#endif
