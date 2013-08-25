/*! \file
    \brief The definition of tetengo2::gui::message::file_drop_observer_set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_FILEDROPOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_FILEDROPOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class for a file drop observer set.
    */
    class file_drop_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of file-dropped
        */
        typedef void file_dropped_type();

        //! The signal type of file_dropped.
        typedef boost::signals2::signal<file_dropped_type> file_dropped_signal_type;


        // functions

        /*!
            \brief Returns the observer called when files are dropped.

            \return The observer called when files are dropped.
        */
        const file_dropped_signal_type& file_dropped()
        const
        {
            return m_file_dropped;
        }

        /*!
            \brief Returns the observer called when files are dropped.

            \return The observer called when files are dropped.
        */
        file_dropped_signal_type& file_dropped()
        {
            return m_file_dropped;
        }


    private:
        // variables

        file_dropped_signal_type m_file_dropped;


    };


}}}


#endif
