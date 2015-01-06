/*! \file
    \brief The definition of tetengo2::gui::message::text_box_observer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_TEXTBOXOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_TEXTBOXOBSERVERSET_H

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class for a text box observer set.
    */
    class text_box_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of a change.
        */
        using changed_type = void ();

        //! The signal type of a change.
        using changed_signal_type = boost::signals2::signal<changed_type>;


        // functions

        /*!
            \brief Returns the observer called when a text is changed.

            \return The observer called when a text is changed.
        */
        const changed_signal_type& changed()
        const
        {
            return m_changed;
        }

        /*!
            \brief Returns the observer called when a text is changed.

            \return The observer called when a text is changed.
        */
        changed_signal_type& changed()
        {
            return m_changed;
        }


    private:
        // variables

        changed_signal_type m_changed;


    };


}}}


#endif
