/*! \file
    \brief The definition of tetengo2::gui::widget::control.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::widget {
    class control::impl : private boost::noncopyable
    {
    public:
        // types

        using color_type = control::color_type;

        using message_handler_map_type = control::message_handler_map_type;


        // constructors and destructor

        impl(typename widget_details_type::widget_details_ptr_type p_details)
        : m_p_details{ std::move(p_details) }, m_text_color{}
        {}


        // functions

        const tetengo2::stdalt::optional<color_type>& text_color() const
        {
            return m_text_color;
        }

        void set_text_color(tetengo2::stdalt::optional<color_type> text_color)
        {
            m_text_color = std::move(text_color);
        }

        bool focusable(const control& self) const
        {
            return widget_details().focusable(self);
        }

        void set_focusable(const bool focusable, control& self)
        {
            widget_details().set_focusable(self, focusable);
        }

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
        // variables

        const typename widget_details_type::widget_details_ptr_type m_p_details;

        tetengo2::stdalt::optional<color_type> m_text_color;
    };


    control::~control() = default;

    const tetengo2::stdalt::optional<control::color_type>& control::text_color() const
    {
        return m_p_impl->text_color();
    }

    void control::set_text_color(tetengo2::stdalt::optional<color_type> text_color /*= TETENGO2_STDALT_NULLOPT*/)
    {
        m_p_impl->set_text_color(std::move(text_color));
    }

    bool control::focusable() const
    {
        return m_p_impl->focusable(*this);
    }

    void control::set_focusable(const bool focusable)
    {
        m_p_impl->set_focusable(focusable, *this);
    }

    control::control(
        const scroll_bar_style_type                           scroll_bar_style,
        message_handler_map_type&&                            message_handler_map,
        typename widget_details_type::widget_details_ptr_type p_details)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      widget{ scroll_bar_style,
              detail::gui_detail_impl_set().message_handler_().make_control_message_handler_map(
                  *this,
                  std::move(message_handler_map)) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>(std::move(p_details)) }
    {}

    const control::details_type& control::details_impl() const
    {
        return m_p_impl->details_impl();
    }

    control::details_type& control::details_impl()
    {
        return m_p_impl->details_impl();
    }
}
