/*! \file
    \brief The definition of bobura::message::timetable_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_MODEL_MESSAGE_TIMETABLEOBSERVERSET_H)
#define TETENGO2_MODEL_MESSAGE_TIMETABLEOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace bobura { namespace message
{
    /*!
        \brief The class for a timetable observer set.
    */
    class timetable_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of changed.
        */
        typedef void changed_type();

        //! The signal type of changed.
        typedef boost::signals2::signal<changed_type> changed_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a timetable is changed.

            \return The observer called when a a timetable is changed.
        */
        const changed_signal_type& changed()
        const
        {
            return m_changed;
        }

        /*!
            \brief Returns the observer called when a timetable is changed.

            \return The observer called when a a timetable is changed.
        */
        changed_signal_type& changed()
        {
            return m_changed;
        }


    private:
        // variables

        changed_signal_type m_changed;


    };


}}


#endif
