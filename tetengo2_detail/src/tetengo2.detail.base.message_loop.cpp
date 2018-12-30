/*! \file
    \brief The definition of tetengo2::detail::base::message_loop.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/message_loop.h>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
}}}


namespace tetengo2::detail::base {
    class message_loop::impl : private boost::noncopyable
    {
    public:
        // functions

        int loop(gui::widget::abstract_window& window, const message_loop& self) const
        {
            return self.loop_impl(window);
        }

        int dialog_loop(gui::widget::abstract_window& dialog, const message_loop& self) const
        {
            return self.dialog_loop_impl(dialog);
        }

        void break_loop(const int exit_code, const message_loop& self) const
        {
            self.break_loop_impl(exit_code);
        }
    };


    message_loop::~message_loop() = default;

    message_loop::message_loop() : m_p_impl{ std::make_unique<impl>() } {}

    int message_loop::loop(gui::widget::abstract_window& window) const
    {
        return m_p_impl->loop(window, *this);
    }

    int message_loop::dialog_loop(gui::widget::abstract_window& dialog) const
    {
        return m_p_impl->dialog_loop(dialog, *this);
    }

    void message_loop::break_loop(int exit_code) const
    {
        m_p_impl->break_loop(exit_code, *this);
    }
}
