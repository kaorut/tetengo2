/*! \file
    \brief The definition of tetengo2::detail::base::cursor.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/cursor.h>


namespace tetengo2::detail::base {
    class cursor::impl : private boost::noncopyable
    {
    public:
        // types

        using cursor_details_type = cursor::cursor_details_type;

        using cursor_details_ptr_type = cursor::cursor_details_ptr_type;

        using system_cursor_style_type = cursor::system_cursor_style_type;


        // functions

        cursor_details_ptr_type create_system_cursor(const system_cursor_style_type style, const cursor& base) const
        {
            return base.create_system_cursor_impl(style);
        }


    private:
    };


    cursor::~cursor() = default;

    cursor::cursor_details_ptr_type cursor::create_system_cursor(const system_cursor_style_type style) const
    {
        return m_p_impl->create_system_cursor(style, *this);
    }

    cursor::cursor() : m_p_impl{ std::make_unique<impl>() } {}
}
