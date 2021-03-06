/*! \file
    \brief The definition of tetengo2::detail::stub::cursor.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::stub {
    class cursor::impl : private boost::noncopyable
    {
    public:
        // types

        using cursor_details_type = cursor::cursor_details_type;

        using cursor_details_ptr_type = cursor::cursor_details_ptr_type;

        using system_cursor_style_type = cursor::system_cursor_style_type;


        // static functions

        static const cursor& instance()
        {
            static const cursor singleton;
            return singleton;
        }


        // functions

        cursor_details_ptr_type
        create_system_cursor_impl(TETENGO2_STDALT_MAYBE_UNUSED const system_cursor_style_type style) const
        {
            return cursor_details_ptr_type{ new cursor_details_type{}, delete_details };
        }


    private:
        // static functions

        static void delete_details(cursor_details_type* const p_details)
        {
            static const std::default_delete<cursor_details_type> deleter{};
            deleter(p_details);
        }
    };


    const cursor& cursor::instance()
    {
        return impl::instance();
    }

    cursor::~cursor() = default;

    cursor::cursor() : m_p_impl{ std::make_unique<impl>() } {}

    cursor::cursor_details_ptr_type cursor::create_system_cursor_impl(const system_cursor_style_type style) const
    {
        return m_p_impl->create_system_cursor_impl(style);
    }
}
