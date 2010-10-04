/*! \file
    \brief The definition of tetengo2::gui::menu_observer_set.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUOBSERVERSET_H)
#define TETENGO2_GUI_MENUOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a paint observer set.
    */
    class menu_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of selected.
        */
        typedef void selected_type();

        //! \return The signal type of selected.
        typedef boost::signals2::signal<selected_type> selected_signal_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer set.
        */
        menu_observer_set()
        :
        m_selected()
        {}


        // functions

        /*!
            \brief Returns the observer called when a menu item is selected.

            \return The observer called when a menu item is selected.
        */
        const selected_signal_type& selected()
        const
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


}}

#endif
