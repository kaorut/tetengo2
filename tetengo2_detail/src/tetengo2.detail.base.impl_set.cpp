/*! \file
    \brief The definition of tetengo2::detail::base::impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_fixture.h>
#include <tetengo2/detail/base/impl_set.h>


namespace tetengo2::detail::base {
    class alert;
    class cursor;
    class encoding;
    class icon;
    class shell;
    class unit;
}


namespace tetengo2::detail {
    namespace base {
        impl_set::~impl_set() = default;

        const alert& impl_set::alert_() const
        {
            return alert_impl();
        }

        const cursor& impl_set::cursor_() const
        {
            return cursor_impl();
        }

        const encoding& impl_set::encoding_() const
        {
            return encoding_impl();
        }

        std::unique_ptr<gui_fixture> impl_set::create_gui_fixture() const
        {
            return create_gui_fixture_impl();
        }

        const icon& impl_set::icon_() const
        {
            return icon_impl();
        }

        const shell& impl_set::shell_() const
        {
            return shell_impl();
        }

        const unit& impl_set::unit_() const
        {
            return unit_impl();
        }

        impl_set::impl_set() = default;
    }


    namespace {
        const base::impl_set* g_p_impl_set = nullptr;
    }

    const base::impl_set& detail_impl_set()
    {
        if (!g_p_impl_set)
            BOOST_THROW_EXCEPTION(std::logic_error{ "No detail implementation set is set yet." });

        return *g_p_impl_set;
    }

    void set_detail_impl_set(const base::impl_set& impl_set)
    {
        g_p_impl_set = &impl_set;
    }
}