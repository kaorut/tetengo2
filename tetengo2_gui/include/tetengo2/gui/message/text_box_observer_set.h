/*! \file
    \brief The definition of tetengo2::gui::message::text_box_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_TEXTBOXOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_TEXTBOXOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2::gui::message {
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
        using changed_type = void();

        //! The signal type of a change.
        using changed_signal_type = boost::signals2::signal<changed_type>;


        // constructors and destructor

        /*!
            \brief Creates a text box observer set.
        */
        text_box_observer_set();

        /*!
            \brief Destroys the text box observer set.
        */
        ~text_box_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a text is changed.

            \return The observer called when a text is changed.
        */
        const changed_signal_type& changed() const;

        /*!
            \brief Returns the observer called when a text is changed.

            \return The observer called when a text is changed.
        */
        changed_signal_type& changed();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
