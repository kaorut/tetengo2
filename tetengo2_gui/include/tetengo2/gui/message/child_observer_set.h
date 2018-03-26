/*! \file
    \brief The definition of tetengo2::gui::message::child_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_CHILDOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_CHILDOBSERVERSET_H

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2::gui::message {
    /*!
        \brief The class template for a child observer set.

        \tparam Widget A widget type.
    */
    template <typename Widget>
    class child_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        using widget_type = Widget;

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


        // functions

        /*!
            \brief Returns the observer called when a child is created.

            \return The observer called when a child is created.
        */
        const created_signal_type& created() const
        {
            return m_created;
        }

        /*!
            \brief Returns the observer called when a child is created.

            \return The observer called when a child is created.
        */
        created_signal_type& created()
        {
            return m_created;
        }

        /*!
            \brief Returns the observer called when a child is about to be destroyed.

            \return The observer called when a child is about to be destroyed.
        */
        const destroying_signal_type& destroying() const
        {
            return m_destroying;
        }

        /*!
            \brief Returns the observer called when a child is about to be destroyed.

            \return The observer called when a child is about to be destroyed.
        */
        destroying_signal_type& destroying()
        {
            return m_destroying;
        }


    private:
        // variables

        created_signal_type m_created;

        destroying_signal_type m_destroying;
    };
}


#endif
