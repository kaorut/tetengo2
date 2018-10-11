/*! \file
    \brief The definition of tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/picture_box.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class picture_box::impl : private boost::noncopyable
    {
    public:
        // types

        using fast_canvas_type = picture_box::fast_canvas_type;

        using fast_paint_observer_set_type = picture_box::fast_paint_observer_set_type;


        // constructors and destructor

        impl() : m_fast_paint_observer_set{} {}


        // functions

        std::unique_ptr<fast_canvas_type> create_fast_canvas(const picture_box& self) const
        {
            return std::make_unique<fast_widget_canvas_type>(
                detail::gui_detail_impl_set().fast_drawing(), self.details());
        }

        const fast_paint_observer_set_type& fast_paint_observer_set() const
        {
            return m_fast_paint_observer_set;
        }

        fast_paint_observer_set_type& fast_paint_observer_set()
        {
            return m_fast_paint_observer_set;
        }


    private:
        // types

        using fast_widget_canvas_type = gui::drawing::widget_canvas;


        // variables

        fast_paint_observer_set_type m_fast_paint_observer_set;
    };


    picture_box::picture_box(widget& parent, const scroll_bar_style_type scroll_bar_style)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ scroll_bar_style,
               detail::gui_detail_impl_set().message_handler_().make_picture_box_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_picture_box(
                   parent,
                   static_cast<widget_details_type::scroll_bar_style_type>(scroll_bar_style)) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>() }
    {
        control::initialize(this);

        parent.child_observer_set().created()(*this);

        this->paint_observer_set().paint_background().connect([](typename control::canvas_type&) { return true; });
    }

    picture_box::~picture_box() noexcept
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

    std::unique_ptr<picture_box::fast_canvas_type> picture_box::create_fast_canvas() const
    {
        return m_p_impl->create_fast_canvas(*this);
    }

    const picture_box::fast_paint_observer_set_type& picture_box::fast_paint_observer_set() const
    {
        return m_p_impl->fast_paint_observer_set();
    }

    picture_box::fast_paint_observer_set_type& picture_box::fast_paint_observer_set()
    {
        return m_p_impl->fast_paint_observer_set();
    }
}
