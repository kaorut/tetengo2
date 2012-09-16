/*! \file
    \brief The definition of tetengo2::gui::message::list_box_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_LISTBOXOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_LISTBOXOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class for a list box observer set.
    */
    class list_box_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of a selection change.
        */
        typedef void selection_changed_type();

        //! The signal type of scrolling.
        typedef boost::signals2::signal<selection_changed_type> selection_changed_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a selection is changed.

            \return The observer called when a selection is changed.
        */
        const selection_changed_signal_type& selection_changed()
        const
        {
            return m_selection_changed;
        }

        /*!
            \brief Returns the observer called when a selection is changed.

            \return The observer called when a selection is changed.
        */
        selection_changed_signal_type& selection_changed()
        {
            return m_selection_changed;
        }


    private:
        // variables

        selection_changed_signal_type m_selection_changed;


    };


}}}


#endif
