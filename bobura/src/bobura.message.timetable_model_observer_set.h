/*! \file
    \brief The definition of bobura::message::timetable_model_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_TIMETABLEMODELOBSERVERSET_H)
#define TETENGO2_MESSAGE_TIMETABLEMODELOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace bobura { namespace message
{
    /*!
        \brief The class template for a timetable model observer set.
    */
    template <typename Timetable>
    class timetable_model_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        /*!
            \brief The observer type of reset.

            \param timetable A timetable.
        */
        typedef void reset_type(const timetable_type& timetable);

        //! The signal type of reset.
        typedef boost::signals2::signal<reset_type> reset_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a timetable model is
                   reset.

            \return The observer called when a a timetable model is reset.
        */
        const reset_signal_type& reset()
        const
        {
            return m_reset;
        }

        /*!
            \brief Returns the observer called when a timetable model is
                   reset.

            \return The observer called when a a timetable model is reset.
        */
        reset_signal_type& reset()
        {
            return m_reset;
        }


    private:
        // variables

        reset_signal_type m_reset;


    };


}}


#endif