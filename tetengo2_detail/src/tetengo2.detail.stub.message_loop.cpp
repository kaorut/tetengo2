/*! \file
    \brief The definition of tetengo2::detail::stub::message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/message_loop.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
}}}


namespace tetengo2::detail::stub {
    class message_loop::impl : private boost::noncopyable
    {
    public:
        // static functions

        static const message_loop& instance()
        {
            static const message_loop singleton;
            return singleton;
        }


        // functions

        int loop_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::abstract_window& window) const
        {
            return 0;
        }

        int dialog_loop_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::abstract_window& dialog) const
        {
            return 0;
        }

        void break_loop_impl(TETENGO2_STDALT_MAYBE_UNUSED const int exit_code) const {}
    };


    const message_loop& message_loop::instance()
    {
        return impl::instance();
    }

    message_loop::~message_loop() = default;

    message_loop::message_loop() : m_p_impl{ std::make_unique<impl>() } {}

    int message_loop::loop_impl(gui::widget::abstract_window& window) const
    {
        return m_p_impl->loop_impl(window);
    }

    int message_loop::dialog_loop_impl(gui::widget::abstract_window& dialog) const
    {
        return m_p_impl->dialog_loop_impl(dialog);
    }

    void message_loop::break_loop_impl(int exit_code) const
    {
        m_p_impl->break_loop_impl(exit_code);
    }
}
