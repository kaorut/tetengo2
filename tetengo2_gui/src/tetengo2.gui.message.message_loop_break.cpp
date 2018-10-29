/*! \file
    \brief The definition of tetengo2::gui::message::message_loop_break.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_loop.h>

#include <tetengo2/gui/message/message_loop_break.h>


namespace tetengo2::gui::message {
    void message_loop_break::operator()(const int exit_code) const
    {
        detail::gui_detail_impl_set().message_loop_().break_loop(exit_code);
    }
}
