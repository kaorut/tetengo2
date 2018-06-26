/*! \file
    \brief The definition of tetengo2::gui::message::size_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_SIZEOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_SIZEOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a size observer set.
    */
    class size_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of resized
        */
        using resized_type = void();

        //! The signal type of resized.
        using resized_signal_type = boost::signals2::signal<resized_type>;


        // constructors and destructor

        /*!
            \brief Creates a size observer set.
        */
        size_observer_set();

        /*!
            \brief Destroys the size observer set.
        */
        ~size_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a widget is resized.

            \return The observer called when a widget is resized.
        */
        const resized_signal_type& resized() const;

        /*!
            \brief Returns the observer called when a widget is resized.

            \return The observer called when a widget is resized.
        */
        resized_signal_type& resized();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
