/*! \file
    \brief The definition of tetengo2::gui::cursor::cursor_base.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/cursor/cursor_base.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace cursor {
    class cursor_base::impl : private boost::noncopyable
    {
    public:
        // types

        using cursor_details_type = cursor_base::cursor_details_type;

        using details_type = cursor_base::details_type;

        using details_ptr_type = cursor_base::details_ptr_type;


        // functions

        const details_type& details(const cursor_base& base) const
        {
            return base.details_impl();
        }

        details_type& details(cursor_base& base)
        {
            return base.details_impl();
        }
    };


    cursor_base::~cursor_base() = default;

    const cursor_base::details_type& cursor_base::details() const
    {
        return m_p_impl->details(*this);
    }

    cursor_base::details_type& cursor_base::details()
    {
        return m_p_impl->details(*this);
    }

    cursor_base::cursor_base() : m_p_impl{ stdalt::make_unique<impl>() } {}


}}}
