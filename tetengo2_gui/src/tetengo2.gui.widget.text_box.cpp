/*! \file
    \brief The definition of tetengo2::gui::widget::text_box.

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
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/text_box.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class text_box::impl : private boost::noncopyable
    {
    public:
        // types

        using text_box_observer_set_type = text_box::text_box_observer_set_type;


        // constructors and destructor

        impl() : m_text_box_observer_set{} {}


        // functions

        bool read_only(const text_box& self) const
        {
            return widget_details().read_only(self);
        }

        void set_read_only(const bool read_only, text_box& self)
        {
            widget_details().set_read_only(self, read_only);
        }

        const text_box_observer_set_type& text_box_observer_set() const
        {
            return m_text_box_observer_set;
        }

        text_box_observer_set_type& text_box_observer_set()
        {
            return m_text_box_observer_set;
        }


    private:
        // variables

        text_box_observer_set_type m_text_box_observer_set;
    };


    text_box::text_box(widget& parent, const scroll_bar_style_type scroll_bar_style)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ scroll_bar_style,
               detail::gui_detail_impl_set().message_handler_().make_text_box_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_text_box(
                   parent,
                   static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style)) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>() }
    {
        control::initialize(this);

        parent.child_observer_set().created()(*this);
    }

    text_box::~text_box() noexcept
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

    bool text_box::read_only() const
    {
        return m_p_impl->read_only(*this);
    }

    void text_box::set_read_only(const bool read_only)
    {
        m_p_impl->set_read_only(read_only, *this);
    }

    const text_box::text_box_observer_set_type& text_box::text_box_observer_set() const
    {
        return m_p_impl->text_box_observer_set();
    }

    text_box::text_box_observer_set_type& text_box::text_box_observer_set()
    {
        return m_p_impl->text_box_observer_set();
    }
}
