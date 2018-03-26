/*! \file
    \brief The definition of tetengo2::gui::message::menu_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MENUOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_MENUOBSERVERSET_H

#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a menu observer set.
    */
    class menu_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of selected.
        */
        using selected_type = void();

        //! The signal type of selected.
        using selected_signal_type = boost::signals2::signal<selected_type>;


        // functions

        /*!
            \brief Returns the observer called when a menu item is selected.

            \return The observer called when a menu item is selected.
        */
        const selected_signal_type& selected() const
        {
            return m_selected;
        }

        /*!
            \brief Returns the observer called when a menu item is selected.

            \return The observer called when a menu item is selected.
        */
        selected_signal_type& selected()
        {
            return m_selected;
        }


    private:
        // variables

        selected_signal_type m_selected;
    };
}


#endif
