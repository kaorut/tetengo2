/*! \file
    \brief The definition of tetengo2::gui::widget::label.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class label::impl : private boost::noncopyable
    {
    public:
        // types

        using dimension_unit_type = label::dimension_unit_type;

        class paint_background
        {
        public:
            paint_background(label& self) : m_self{ self } {}

            bool operator()(canvas_type& canvas) const
            {
                if (!m_self.p_background())
                    return false;

                canvas.set_background(m_self.p_background()->clone());
                canvas.fill_rectangle(position_type{}, m_self.client_dimension());

                return true;
            }

        private:
            label& m_self;
        };


        // functions

        void fit_to_content(label& self)
        {
            if (self.text().empty())
                return;

            self.set_client_dimension(calc_text_dimension(self));
        }

        void fit_to_content(dimension_unit_type max_width, label& self)
        {
            if (self.text().empty() || max_width == dimension_unit_type{})
                return;

            auto       one_line_dimension = calc_text_dimension(self);
            const auto line_count = dimension_unit_type{ one_line_dimension.width() / max_width };
            if (line_count <= dimension_unit_type{ 1 })
            {
                self.set_client_dimension(std::move(one_line_dimension));
                return;
            }

            const auto int_line_count = static_cast<std::size_t>(
                std::ceil(static_cast<double>(line_count.to_pixels()) / dimension_unit_type{ 1 }.to_pixels()));
            auto height = one_line_dimension.height() * int_line_count;
            self.set_client_dimension(dimension_type{ std::move(max_width), std::move(height) });
        }


    private:
        // types


        // static functions

        static void initialize_label(label* const p_label)
        {
            control::initialize(p_label);

            p_label->paint_observer_set().paint_background().disconnect_all_slots();
            p_label->paint_observer_set().paint_background().connect(paint_background(*p_label));
        }

        // functions

        dimension_type calc_text_dimension(const label& self) const
        {
            std::unique_ptr<canvas_type> p_canvas = self.create_canvas();
            return p_canvas->calc_text_dimension(self.text());
        }
    };


    label::label(widget& parent)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ control::scroll_bar_style_type::none,
               detail::gui_detail_impl_set().message_handler_().make_label_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_label(parent) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>() }
    {
        control::initialize(this);

        this->paint_observer_set().paint_background().disconnect_all_slots();
        this->paint_observer_set().paint_background().connect(impl::paint_background(*this));

        parent.child_observer_set().created()(*this);
    }

    label::~label() noexcept
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

    void label::fit_to_content()
    {
        m_p_impl->fit_to_content(*this);
    }

    void label::fit_to_content(dimension_unit_type max_width)
    {
        m_p_impl->fit_to_content(std::move(max_width), *this);
    }
}
