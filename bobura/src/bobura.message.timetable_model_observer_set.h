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

        \tparam Timetable A timetable type.
        \tparam Path      A path type.
    */
    template <typename Timetable, typename Path>
    class timetable_model_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path type.
        typedef Path path_type;

        /*!
            \brief The observer type of reset.

            \param timetable A timetable.
            \param path      A path.
        */
        typedef
            void reset_type(
                const timetable_type& timetable,
                const path_type&      path
            );

        //! The signal type of reset.
        typedef boost::signals2::signal<reset_type> reset_signal_type;

        /*!
            \brief The observer type of changed.

            \param changed A changed status.
        */
        typedef void changed_type(bool changed);

        //! The signal type of reset.
        typedef boost::signals2::signal<changed_type> changed_signal_type;


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

        /*!
            \brief Returns the observer called when a timetable model is
                   changed.

            \return The observer called when a a timetable model is changed.
        */
        const changed_signal_type& changed()
        const
        {
            return m_changed;
        }

        /*!
            \brief Returns the observer called when a timetable model is
                   changed.

            \return The observer called when a a timetable model is changed.
        */
        changed_signal_type& changed()
        {
            return m_changed;
        }


    private:
        // variables

        reset_signal_type m_reset;

        changed_signal_type m_changed;


    };


}}


#endif
