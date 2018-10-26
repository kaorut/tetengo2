/*! \file
    \brief The definition of tetengo2::gui::widget::window.

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
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/gui/widget/window.h>


namespace tetengo2::gui::widget {
    class window::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        impl(const scroll_bar_style_type scroll_bar_style, const bool file_droppable)
        : m_p_details{ widget_details().create_window(
              nullptr,
              static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style),
              file_droppable) }
        {}

        impl(abstract_window& parent, const scroll_bar_style_type scroll_bar_style, const bool file_droppable)
        : m_p_details{ widget_details().create_window(
              &parent,
              static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style),
              file_droppable) }
        {}


        // functions

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

        // using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        const typename widget_details_type::widget_details_ptr_type m_p_details;
    };


    window::window(
        const scroll_bar_style_type scroll_bar_style /*= abstract_window::scroll_bar_style_type::none*/,
        const bool                  file_droppable /*= false*/)
    : abstract_window{ scroll_bar_style, file_droppable, message_handler_map_type{} }, m_p_impl{
          std::make_unique<impl>(scroll_bar_style, file_droppable)
      }
    {
        abstract_window::initialize(this);
    }

    window::window(abstract_window& parent, const scroll_bar_style_type scroll_bar_style, const bool file_droppable)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      abstract_window{ scroll_bar_style,
                       file_droppable,
                       detail::gui_detail_impl_set().message_handler_().make_window_message_handler_map(
                           *this,
                           message_handler_map_type{}) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>(parent, scroll_bar_style, file_droppable) }
    {
        abstract_window::initialize(this);

        parent.child_observer_set().created()(*this);
    }

    window::~window() noexcept
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

    const window::details_type& window::details_impl() const
    {
        return m_p_impl->details_impl();
    }

    window::details_type& window::details_impl()
    {
        return m_p_impl->details_impl();
    }
}
