/*! \file
    \brief The definition of tetengo2::gui::message::file_drop_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_FILEDROPOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_FILEDROPOBSERVERSET_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>

#include <tetengo2/stdalt.h>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a file drop observer set.
    */
    class file_drop_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of file-dropped.

            \param paths Paths.
        */
        using file_dropped_type = void(const std::vector<tetengo2::stdalt::filesystem::path>& paths);

        //! The signal type of file_dropped.
        using file_dropped_signal_type = boost::signals2::signal<file_dropped_type>;


        // constructors and destructor

        /*!
            \brief Creates a file drop observer set.
        */
        file_drop_observer_set();

        /*!
            \brief Destroys the file drop observer set.
        */
        ~file_drop_observer_set();


        // functions

        /*!
            \brief Returns the observer called when files are dropped.

            \return The observer called when files are dropped.
        */
        const file_dropped_signal_type& file_dropped() const;

        /*!
            \brief Returns the observer called when files are dropped.

            \return The observer called when files are dropped.
        */
        file_dropped_signal_type& file_dropped();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
