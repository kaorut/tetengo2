/*! \file
    \brief The definition of tetengo2::detail::base::cursor.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/cursor.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace base
{
    class cursor::impl : private boost::noncopyable
    {
    public:
        // types

        using cursor_details_type = cursor::cursor_details_type;

        using cursor_details_ptr_type = cursor::cursor_details_ptr_type;


        // functions

        cursor_details_ptr_type create_system_cursor(const int style, const cursor& base)
        const
        {
            return base.create_system_cursor_impl(style);
        }


    private:


    };


    cursor::~cursor()
    = default;

    cursor::cursor_details_ptr_type cursor::create_system_cursor(const int style)
    const
    {
        return m_p_impl->create_system_cursor(style, *this);
    }

    cursor::cursor()
    :
    m_p_impl(stdalt::make_unique<impl>())
    {}


}}}
