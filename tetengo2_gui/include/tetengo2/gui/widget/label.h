/*! \file
    \brief The definition of tetengo2::gui::widget::label.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LABEL_H)
#define TETENGO2_GUI_WIDGET_LABEL_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>

#include <boost/operators.hpp>
#include <boost/predef.h>
#include <boost/signals2.hpp>

#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/stub/message_handler.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a label.
    */
    class label : public control
    {
    public:
        // types

        //! The dimension unit type.
        using dimension_unit_type = typename dimension_type::unit_type;


        // constructors and destructor

        /*!
            \brief Creates a label.

            \param parent A parent widget.
        */
        explicit label(widget& parent)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          control
        {
            control::scroll_bar_style_type::none,
                message_handler_details_type::instance().make_label_message_handler_map(
                    *this, message_handler_map_type{}),
                widget_details().create_label(parent)
        }
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
        {
            initialize_label(this);

            parent.child_observer_set().created()(*this);
        }

        /*!
            \brief Destroys the label.
        */
        virtual ~label() noexcept
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


        // functions

        /*!
            \brief Fit the dimension to the dimension of the text.
        */
        void fit_to_content()
        {
            if (this->text().empty())
                return;

            this->set_client_dimension(calc_text_dimension());
        }

        /*!
            \brief Fit the dimension to the dimension of the text.

            \param max_width A maximum width.
        */
        void fit_to_content(dimension_unit_type max_width)
        {
            if (this->text().empty() || max_width == dimension_unit_type{})
                return;

            auto       one_line_dimension = calc_text_dimension();
            const auto line_count = dimension_unit_type{ one_line_dimension.width() / max_width };
            if (line_count <= dimension_unit_type{ 1 })
            {
                this->set_client_dimension(std::move(one_line_dimension));
                return;
            }

            const auto int_line_count = static_cast<std::size_t>(
                std::ceil(static_cast<double>(line_count.to_pixels()) / dimension_unit_type{ 1 }.to_pixels()));
            auto height = one_line_dimension.height() * int_line_count;
            this->set_client_dimension(dimension_type{ std::move(max_width), std::move(height) });
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;

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


        // static functions

        static void initialize_label(label* const p_label)
        {
            control::initialize(p_label);

            p_label->paint_observer_set().paint_background().disconnect_all_slots();
            p_label->paint_observer_set().paint_background().connect(paint_background(*p_label));
        }

        // functions

        dimension_type calc_text_dimension() const
        {
            std::unique_ptr<canvas_type> p_canvas = create_canvas();
            return p_canvas->calc_text_dimension(this->text());
        }
    };
}


#endif
