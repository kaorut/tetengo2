/*! \file
    \brief The definition of tetengo2::gui::message::file_drop_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/file_drop_observer_set.h>


namespace tetengo2::gui::message {
    class file_drop_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using file_dropped_type = file_drop_observer_set::file_dropped_type;

        using file_dropped_signal_type = file_drop_observer_set::file_dropped_signal_type;


        // functions

        const file_dropped_signal_type& file_dropped() const
        {
            return m_file_dropped;
        }

        file_dropped_signal_type& file_dropped()
        {
            return m_file_dropped;
        }


    private:
        // variables

        file_dropped_signal_type m_file_dropped;
    };


    file_drop_observer_set::file_drop_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    file_drop_observer_set::~file_drop_observer_set() = default;

    const file_drop_observer_set::file_dropped_signal_type& file_drop_observer_set::file_dropped() const
    {
        return m_p_impl->file_dropped();
    }

    file_drop_observer_set::file_dropped_signal_type& file_drop_observer_set::file_dropped()
    {
        return m_p_impl->file_dropped();
    }
}
