/*! \file
    \brief The definition of tetengo2::gui::message::message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_loop.h>

#include <tetengo2/gui/message/message_loop.h>


namespace tetengo2::gui::message {
    class message_loop::impl : private boost::noncopyable
    {
    public:
        // types

        using abstract_window_type = message_loop::abstract_window_type;


        // constructors and destructor

        explicit impl(abstract_window_type& window) : m_window{ window } {}


        // functions

        int operator_paren() const
        {
            return detail::gui_detail_impl_set().message_loop_().loop(m_window);
        }


    private:
        // variables

        abstract_window_type& m_window;
    };


    message_loop::message_loop(abstract_window_type& window) : m_p_impl{ std::make_unique<impl>(window) } {}

    message_loop::~message_loop() = default;

    int message_loop::operator()() const
    {
        return m_p_impl->operator_paren();
    }
}
