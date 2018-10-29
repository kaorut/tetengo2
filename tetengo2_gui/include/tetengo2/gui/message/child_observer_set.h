/*! \file
    \brief The definition of tetengo2::gui::message::child_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_CHILDOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_CHILDOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp> // IWYU pragma: keep

#if !defined(IWYU)
namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}
#endif


namespace tetengo2::gui::message {
    /*!
        \brief The class for a child observer set.
    */
    class child_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        using widget_type = gui::widget::widget;

        /*!
            \brief The observer type of child creation.

            \param child A child.
        */
        using created_type = void(widget_type& child);

        //! The signal type of child creation.
        using created_signal_type = boost::signals2::signal<created_type>;

        /*!
            \brief The observer type of child destruction.

            \param child A child.
        */
        using destroying_type = void(widget_type& child);

        //! The signal type of child destruction.
        using destroying_signal_type = boost::signals2::signal<destroying_type>;


        // constructors and destructor

        /*!
            \brief Creates a child observer set.
        */
        child_observer_set();

        /*!
            \brief Destroys the child observer set.
        */
        ~child_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a child is created.

            \return The observer called when a child is created.
        */
        const created_signal_type& created() const;

        /*!
            \brief Returns the observer called when a child is created.

            \return The observer called when a child is created.
        */
        created_signal_type& created();

        /*!
            \brief Returns the observer called when a child is about to be destroyed.

            \return The observer called when a child is about to be destroyed.
        */
        const destroying_signal_type& destroying() const;

        /*!
            \brief Returns the observer called when a child is about to be destroyed.

            \return The observer called when a child is about to be destroyed.
        */
        destroying_signal_type& destroying();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
