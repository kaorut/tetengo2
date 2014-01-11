/*! \file
    \brief The definition of tetengo2::gui::message::file_drop_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_FILEDROPOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_FILEDROPOBSERVERSET_H

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a file drop observer set.

        \tparam Path A path type.
    */
    template <typename Path>
    class file_drop_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The path type.
        typedef Path path_type;

        /*!
            \brief The observer type of file-dropped.

            \param paths Paths.
        */
        typedef void file_dropped_type(const std::vector<path_type>& paths);

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
