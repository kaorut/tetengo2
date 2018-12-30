/*! \file
    \brief The definition of tetengo2::gui::message::list_selection_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_LISTSELECTIONOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_LISTSELECTIONOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a list selection observer set.
    */
    class list_selection_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of a selection change.
        */
        using selection_changed_type = void();

        //! The signal type of a selection change.
        using selection_changed_signal_type = boost::signals2::signal<selection_changed_type>;


        // constructors and destructor

        /*!
            \brief Creates a list selection observer set.
        */
        list_selection_observer_set();

        /*!
            \brief Destroys the list selection observer set.
        */
        ~list_selection_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a selection is changed.

            \return The observer called when a selection is changed.
        */
        const selection_changed_signal_type& selection_changed() const;

        /*!
            \brief Returns the observer called when a selection is changed.

            \return The observer called when a selection is changed.
        */
        selection_changed_signal_type& selection_changed();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
