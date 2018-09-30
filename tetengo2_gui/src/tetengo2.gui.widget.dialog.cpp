/*! \file
    \brief The definition of tetengo2::gui::widget::dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/message/dialog_message_loop.h>
#include <tetengo2/gui/message/message_loop_break.h>
#include <tetengo2/gui/message/window_observer_set.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class dialog::impl : private boost::noncopyable
    {
    public:
        // types

        using result_type = dialog::result_type;


        // constructors and destructor

        impl(abstract_window& parent, const bool file_droppable)
        : m_result{ result_type::undecided }, m_p_details{ widget_details().create_dialog(&parent, file_droppable) }
        {}


        // functions

        result_type result() const
        {
            return m_result;
        }

        void set_result(const result_type result, dialog& self)
        {
            if (result == result_type::accepted)
                self.set_result_impl();
            m_result = result;
        }

        void do_modal(dialog& self)
        {
            self.do_modal_impl();

            assert(self.has_parent());
            auto& parent_window = dynamic_cast<abstract_window&>(self.parent());
            parent_window.set_enabled(false);

            self.window_observer_set().closing().connect([this](bool& cancel) { this->on_close_impl(cancel); });
            self.window_observer_set().destroyed().connect([]() { message_loop_break_type{}(0); });
            self.set_position(widget_details().dialog_position(self, parent_window));
            self.set_visible(true);

            message_loop_type{ self }();

            parent_window.set_enabled(true);
            parent_window.activate();
        }

        void set_result_impl() {}

        void do_modal_impl() {}

        void on_close_impl(bool&) {}

        const details_type& details_impl() const
        {
            assert(m_p_details);
            return *static_cast<const details_type*>(m_p_details.get());
        }

        details_type& details_impl()
        {
            assert(m_p_details);
            return *static_cast<details_type*>(m_p_details.get());
        }


    private:
        // types

        using message_loop_type = gui::message::dialog_message_loop;

        using message_loop_break_type = gui::message::message_loop_break;

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        result_type m_result;

        const typename widget_details_type::widget_details_ptr_type m_p_details;
    };


    dialog::dialog(abstract_window& parent, const bool file_droppable /*= false*/)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      abstract_window{ abstract_window::scroll_bar_style_type::none,
                       file_droppable,
                       detail::gui_detail_impl_set().message_handler_().make_dialog_message_handler_map(
                           *this,
                           message_handler_map_type{}) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>(parent, file_droppable) }
    {
        abstract_window::initialize(this);

        parent.child_observer_set().created()(*this);
    }

    dialog::~dialog() noexcept
    {
        try
        {
            if (this->has_parent())
                this->parent().child_observer_set().destroying()(*this);
        }
        catch (...)
        {
        }
    }

    dialog::result_type dialog::result() const
    {
        return m_p_impl->result();
    }

    void dialog::set_result(const result_type result)
    {
        m_p_impl->set_result(result, *this);
    }

    void dialog::do_modal()
    {
        m_p_impl->do_modal(*this);
    }

    void dialog::set_result_impl()
    {
        m_p_impl->set_result_impl();
    }

    void dialog::do_modal_impl()
    {
        m_p_impl->do_modal_impl();
    }

    void dialog::on_close_impl(bool& cancel)
    {
        m_p_impl->on_close_impl(cancel);
    }

    const dialog::details_type& dialog::details_impl() const
    {
        return m_p_impl->details_impl();
    }

    dialog::details_type& dialog::details_impl()
    {
        return m_p_impl->details_impl();
    }
}
