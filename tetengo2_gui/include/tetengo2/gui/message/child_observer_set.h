/*! \file
    \brief The definition of tetengo2::gui::message::child_observer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_CHILDOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_CHILDOBSERVERSET_H

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class for a child observer set.
    */
    class child_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of child creation.
        */
        using created_type = void ();

        //! The signal type of child creation.
        using created_signal_type = boost::signals2::signal<created_type>;


        // functions

        /*!
            \brief Returns the observer called when a child is created.

            \return The observer called when a child is created.
        */
        const created_signal_type& created()
        const
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


    private:
        // variables

        created_signal_type m_created;


    };


}}}


#endif
