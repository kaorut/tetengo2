/*! \file
    \brief The definition of tetengo2::gui::message::dialog_message_loop.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_loop.h>
#include <tetengo2/gui/message/dialog_message_loop.h>


namespace tetengo2::gui::message {
    class dialog_message_loop::impl : private boost::noncopyable
    {
    public:
        // types

        using abstract_window_type = dialog_message_loop::abstract_window_type;


        // constructors and destructor

        explicit impl(abstract_window_type& dialog) : m_dialog{ dialog } {}


        // functions

        int operator_paren() const
        {
            return detail::gui_detail_impl_set().message_loop_().dialog_loop(m_dialog);
        }


    private:
        // variables

        abstract_window_type& m_dialog;
    };


    dialog_message_loop::dialog_message_loop(abstract_window_type& dialog) : m_p_impl{ std::make_unique<impl>(dialog) }
    {}

    dialog_message_loop::~dialog_message_loop() = default;

    int dialog_message_loop::operator()() const
    {
        return m_p_impl->operator_paren();
    }
}
