/*! \file
    \brief The definition of tetengo2::gui::widget::button.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/widget/button.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class button::impl : private boost::noncopyable
    {
    public:
        // types

        using style_type = button::style_type;


        // constructors and destructor

        impl(widget& parent, const style_type style, button& self) : m_style{ style }
        {
            parent.child_observer_set().created()(self);
        }


        // functions

        style_type style() const
        {
            return m_style;
        }


    private:
        // variables

        const style_type m_style;
    };


    button::button(widget& parent, const style_type style /*= style_type::normal*/)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ control::scroll_bar_style_type::none,
               detail::gui_detail_impl_set().message_handler_().make_button_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_button(parent, style == style_type::default_, style == style_type::cancel) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>(parent, style, *this) }
    {
        control::initialize(this);
    }

    button::~button() noexcept
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

    button::style_type button::style() const
    {
        return m_p_impl->style();
    }
}
