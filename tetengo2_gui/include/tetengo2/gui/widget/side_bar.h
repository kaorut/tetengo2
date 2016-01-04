/*! \file
    \brief The definition of tetengo2::gui::widget::side_bar.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_SIDEBAR_H)
#define TETENGO2_GUI_WIDGET_SIDEBAR_H

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include <boost/math/constants/constants.hpp>
#include <boost/optional.hpp>

#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a side bar.

        \tparam Traits              A traits type.
        \tparam DetailsTraits       A detail implementation type traits.
        \tparam MouseCaptureDetails A detail implementation type of a mouse capture.
        \tparam SystemColorDetails  A detail implementation type of system colors.
        \tparam TimerDetails        A detail implementation type of a timer.
    */
    template <
        typename Traits,
        typename DetailsTraits,
        typename MouseCaptureDetails,
        typename SystemColorDetails,
        typename TimerDetails
    >
    class side_bar : public custom_control<Traits, DetailsTraits, MouseCaptureDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The drawing details type.
        using drawing_details_type = typename details_traits_type::drawing_details_type;

        //! The mouse capture details type.
        using mouse_capture_details_type = MouseCaptureDetails;

        //! The system color details type.
        using system_color_details_type = SystemColorDetails;

        //! THe timer details type.
        using timer_details_type = TimerDetails;

        //! The base type.
        using base_type = custom_control<traits_type, details_traits_type, mouse_capture_details_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type::base_type;

        //! The cursor type.
        using cursor_type = typename base_type::cursor_type;

        //! The system cursor type.
        using system_cursor_type = typename base_type::system_cursor_type;

        //! The canvas type.
        using canvas_type = typename base_type::canvas_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The width type.
        using width_type = typename gui::dimension<dimension_type>::width_type;

        //! The solid background type.
        using solid_background_type = gui::drawing::solid_background<drawing_details_type>;

        //! The system color set type.
        using system_color_set_type = gui::drawing::system_color_set<system_color_details_type>;

        //! The timer type.
        using timer_type = gui::timer<widget_type, timer_details_type>;


        // constructors and destructor

        /*!
            \brief Creates a side bar.

            \param parent A parent widget.
        */
        explicit side_bar(widget_type& parent)
        :
        base_type(parent, false, scroll_bar_style_type::none),
        m_p_caption(),
        m_p_splitter(),
        m_preferred_width(0),
        m_minimized(false)
        {
            initialize_side_bar(*this);
        }

        /*!
            \brief Destroys the side bar.
        */
        virtual ~side_bar()
        = default;


        // functions

        /*!
            \brief Returns the preferred width.

            \return The preferred width.
        */
        const width_type& preferred_width()
        {
            if (m_minimized)
            {
                return m_p_caption->width();
            }
            else
            {
                adjust_preferred_width(m_preferred_width);
                return m_preferred_width;
            }
        }

        /*!
            \brief Returns the normal preferred width.

            The normal preferred width is the width when the side bar is not minimized.

            \return The normal preferred width.
        */
        const width_type& normal_preferred_width()
        {
            adjust_preferred_width(m_preferred_width);
            return m_preferred_width;
        }

        /*!
            \brief Sets a width.

            \param width A width.
        */
        void set_width(width_type width)
        {
            const auto& previous_width = gui::dimension<dimension_type>::width(this->dimension());

            adjust_preferred_width(width);

            if (width == previous_width)
                return;

            m_preferred_width = std::move(width);
            if (this->has_parent())
            {
                this->parent().size_observer_set().resized()();
                this->parent().repaint(true);
            }
        }

        /*!
            \brief Returns the minimized status.

            \return The minimized status.
        */
        bool minimized()
        const
        {
            return m_minimized;
        }

        /*!
            \brief Sets a minimized status.

            \param minimized A minimized status.
        */
        void set_minimized(const bool minimized)
        {
            m_minimized = minimized;

            if (!m_minimized)
            {
                this->set_dimension(
                    dimension_type{ m_preferred_width, gui::dimension<dimension_type>::height(this->dimension()) }
                );
            }

            this->size_observer_set().resized()();
            if (this->has_parent())
            {
                this->parent().size_observer_set().resized()();
                this->parent().repaint();
            }
        }

        /*!
            \brief Returns the child control area position.

            \return The child control area position.
        */
        position_type child_control_area_position()
        const
        {
            const auto& caption_dimension = m_p_caption->dimension();
            const auto& splitter_dimension = m_p_splitter->dimension();

            return
                {
                    left_type::from(gui::dimension<dimension_type>::width(splitter_dimension)),
                    top_type::from(gui::dimension<dimension_type>::height(caption_dimension))
                };
        }

        /*!
            \brief Returns the child control area dimension.

            \return The child control area dimension.
        */
        dimension_type child_control_area_dimension()
        const
        {
            const auto client_dimension = this->client_dimension();
            const auto& client_width = gui::dimension<dimension_type>::width(client_dimension);
            const auto& client_height = gui::dimension<dimension_type>::height(client_dimension);
            const auto& caption_dimension = m_p_caption->dimension();
            const auto& caption_height = gui::dimension<dimension_type>::height(caption_dimension);
            const auto& splitter_dimension = m_p_splitter->dimension();
            const auto& splitter_width = gui::dimension<dimension_type>::width(splitter_dimension);

            auto width = client_width > splitter_width ? client_width - splitter_width : width_type{ 0 };
            auto height = client_height > caption_height ? client_height - caption_height : height_type{ 0 };

            return { std::move(width), std::move(height) };
        }


    private:
        // types

        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;

        using unit_size_type = typename canvas_type::unit_size_type;

        using color_type = typename canvas_type::color_type;

        using left_type = typename gui::position<position_type>::left_type;

        using top_type = typename gui::position<position_type>::top_type;

        using height_type = typename gui::dimension<dimension_type>::height_type;

        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        using inner_item_type = typename base_type::inner_item_type;

        class state_button : public inner_item_type
        {
        public:
            // constructors and destructor

            explicit state_button(side_bar& side_bar_)
            :
            inner_item_type(
                side_bar_,
                position_type{ left_type{ 0 }, top_type{ 0 } },
                dimension_type{ width_type{ 1 }, height_type{ 1 } }
            ),
            m_p_current_background_color(&background_color()),
            m_p_timer(),
            m_animation_step(0)
            {}


        private:
            // static functions

            static const color_type& background_color()
            {
                static const color_type singleton = make_background_color();
                return singleton;
            }

            static const color_type& background_color_hovered()
            {
                static const color_type singleton = make_background_color_hovered();
                return singleton;
            }

            static const color_type& border_color()
            {
                static const color_type singleton = make_border_color();
                return singleton;
            }

            static color_type make_background_color()
            {
                const color_type& base_color = system_color_set_type::title_bar_background();
                return
                    {
                        static_cast<unsigned char>((0xFF * 3 + base_color.red() * 1) / 4),
                        static_cast<unsigned char>((0xFF * 3 + base_color.green() * 1) / 4),
                        static_cast<unsigned char>((0xFF * 3 + base_color.blue() * 1) / 4)
                    };
            }

            static color_type make_background_color_hovered()
            {
                const color_type& base_color = system_color_set_type::title_bar_background();
                return
                    {
                        static_cast<unsigned char>((0xFF * 7 + base_color.red() * 1) / 8),
                        static_cast<unsigned char>((0xFF * 7 + base_color.green() * 1) / 8),
                        static_cast<unsigned char>((0xFF * 7 + base_color.blue() * 1) / 8)
                    };
            }

            static color_type make_border_color()
            {
                const color_type& base_color = system_color_set_type::title_bar_background();
                return
                    {
                        static_cast<unsigned char>(base_color.red() / 2), 
                        static_cast<unsigned char>(base_color.green() / 2),
                        static_cast<unsigned char>(base_color.blue() / 2)
                    };
            }

            static const std::chrono::milliseconds& animation_duration()
            {
                static const std::chrono::milliseconds singleton{ 250 };
                return singleton;
            }

            static const std::chrono::milliseconds& animation_finish_wait_duration()
            {
                static const std::chrono::milliseconds singleton{ 50 };
                return singleton;
            }

            static std::size_t max_animation_step()
            {
                return 8;
            }

            static position_type triangle_vertex_position(const std::size_t animation_step, const std::size_t vertex)
            {
                const double angle =
                    (
                        static_cast<double>(animation_step) / max_animation_step() + (2.0 / 3.0) * vertex
                    ) * boost::math::constants::pi<double>();

                const double x = std::cos(angle);
                const double y = std::sin(angle);
                return
                    {
                        left_type{ static_cast<std::ptrdiff_t>(x * 256) } / 256,
                        top_type{ static_cast<std::ptrdiff_t>(y * 256) } / 256
                    };
            }


            // variables

            const color_type* m_p_current_background_color;

            std::unique_ptr<timer_type> m_p_timer;

            std::size_t m_animation_step;


            // virtual functions

            virtual void paint_impl(canvas_type& canvas)
            const override
            {
                auto original_color = canvas.get_color();
                auto original_line_width = canvas.line_width();
                auto original_background = canvas.get_background().clone();
                canvas.set_color(border_color());
                canvas.set_line_width(unit_size_type{ 1 } / 16);
                canvas.set_background(stdalt::make_unique<solid_background_type>(*m_p_current_background_color));

                const auto triangle = make_triangle();
                canvas.fill_polygon(triangle.begin(), triangle.end());
                canvas.draw_polygon(triangle.begin(), triangle.end());

                canvas.set_background(std::move(original_background));
                canvas.set_line_width(std::move(original_line_width));
                canvas.set_color(std::move(original_color));
            }

            virtual void mouse_released_impl(const position_type& cursor_position)
            override
            {
                if (!this->inside(cursor_position))
                    return;

                if (m_animation_step > 0)
                    return;

                m_p_timer =
                    stdalt::make_unique<timer_type>(
                        this->parent(),
                        [this](bool& stop) { this->timer_proc(stop); },
                        animation_duration() / max_animation_step(),
                        false
                    );
                {
                    bool dummy_stop = false;
                    timer_proc(dummy_stop);
                }
            }

            virtual void mouse_entered_impl()
            override
            {
                m_p_current_background_color = &background_color_hovered();
                this->parent().repaint_partially(this->position(), this->dimension());
            }

            virtual void mouse_left_impl()
            override
            {
                m_p_current_background_color = &background_color();
                this->parent().repaint_partially(this->position(), this->dimension());
            }


            // functions

            void timer_proc(bool& stop)
            {
                if (m_animation_step < max_animation_step())
                {
                    ++m_animation_step;
                    this->parent().repaint_partially(this->position(), this->dimension());
                    return;
                }
                if (
                    m_animation_step <
                    max_animation_step() + animation_finish_wait_duration().count() / max_animation_step()
                )
                {
                    ++m_animation_step;
                    return;
                }

                this->template parent_to<side_bar>().set_minimized(!this->template parent_to<side_bar>().m_minimized);
                m_animation_step = 0;
                stop = true;
            }

            std::vector<position_type> make_triangle()
            const
            {
                const auto& left = gui::position<position_type>::left(this->position());
                const auto& top = gui::position<position_type>::top(this->position());
                const auto& width = gui::dimension<dimension_type>::width(this->dimension());
                const auto& height = gui::dimension<dimension_type>::height(this->dimension());

                std::vector<position_type> positions{};
                positions.reserve(3);
                for (std::size_t i = 0; i < 3; ++i)
                {
                    const std::size_t step_ =
                        this->template parent_to<side_bar>().m_minimized ?
                            (m_animation_step < max_animation_step() ? max_animation_step() - m_animation_step : 0) :
                            (m_animation_step < max_animation_step() ? m_animation_step : max_animation_step());
                    const position_type vertex_position = triangle_vertex_position(step_, i);
                    left_type vertex_left =
                        left +
                        (gui::position<position_type>::left(vertex_position) + left_type{ 1 }) *
                            left_type::from(width).value() /
                            2;
                    top_type vertex_top =
                        top +
                        (gui::position<position_type>::top(vertex_position) + top_type{ 1 }) *
                            top_type::from(height).value() /
                            2;
                    positions.emplace_back(std::move(vertex_left), std::move(vertex_top));
                }

                return positions;
            }


        };

        class caption : public inner_item_type
        {
        public:
            // constructors and destructor

            explicit caption(side_bar& side_bar_)
            :
            inner_item_type(
                side_bar_,
                position_type{ left_type{ 0 }, top_type{ 0 } },
                dimension_type{ width_type{ 0 }, height_type{ 0 } }
            ),
            m_text_position()
            {}

            virtual ~caption()
            = default;


            // functions

            const width_type& width()
            {
                ensure_dimension_calculated();
                return gui::dimension<dimension_type>::width(this->dimension());
            }


        private:
            // variables

            boost::optional<position_type> m_text_position;


            // virtual functions

            virtual void resized_impl()
            override
            {
                m_text_position = boost::none;

                ensure_dimension_calculated();
            }

            virtual void paint_impl(canvas_type& canvas)
            const override
            {
                auto original_color = canvas.get_color();
                auto p_original_background = canvas.get_background().clone();
                canvas.set_color(system_color_set_type::title_bar_text());
                canvas.set_background(
                    stdalt::make_unique<solid_background_type>(system_color_set_type::title_bar_background())
                );

                canvas.fill_rectangle(this->position(), this->dimension());

                canvas.draw_text(
                    this->parent().text(),
                    *m_text_position,
                    this->template parent_to<side_bar>().m_minimized ? boost::math::constants::pi<double>() / 2.0 : 0.0
                );

                canvas.set_background(std::move(p_original_background));
                canvas.set_color(std::move(original_color));
            }


            // functions

            void ensure_dimension_calculated()
            {
                if (m_text_position)
                    return;

                const auto p_canvas = this->parent().create_canvas();
                calculate_position_and_dimension(*p_canvas);
            }

            void calculate_position_and_dimension(const canvas_type& canvas)
            {
                if (m_text_position)
                    return;

                static const auto padding = height_type{ 1 } / 4;
                const auto text_dimension = canvas.calc_text_dimension(this->parent().text());
                this->set_dimension(calculate_dimension(padding, text_dimension));

                this->template parent_to<side_bar>().m_p_state_button->set_position(state_button_position(padding));

                m_text_position = boost::make_optional(text_position(padding, text_dimension));
            }

            dimension_type calculate_dimension(const height_type& padding, const dimension_type& text_dimension)
            const
            {
                const dimension_type client_dimension = this->parent().client_dimension();
                const auto& client_width = gui::dimension<dimension_type>::width(client_dimension);
                const auto& client_height = gui::dimension<dimension_type>::height(client_dimension);

                const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);

                const auto& state_button_width =
                    gui::dimension<dimension_type>::width(
                        this->template parent_to<side_bar>().m_p_state_button->dimension()
                    );
                const auto& state_button_height =
                    gui::dimension<dimension_type>::height(
                        this->template parent_to<side_bar>().m_p_state_button->dimension()
                    );

                if (this->template parent_to<side_bar>().m_minimized)
                {
                    const auto& width = std::max(width_type::from(text_height), state_button_width); 
                    return { width + width_type::from(padding) * 2, client_height };
                }
                else
                {
                    const auto& height = std::max(text_height, state_button_height); 
                    return { client_width, height + padding * 2 };
                }
            }

            position_type text_position(const height_type& padding, const dimension_type& text_dimension)
            const
            {
                const auto& state_button_left =
                    gui::position<position_type>::left(
                    this->template parent_to<side_bar>().m_p_state_button->position()
                );
                const auto& state_button_top =
                    gui::position<position_type>::left(
                    this->template parent_to<side_bar>().m_p_state_button->position()
                );
                const auto& state_button_width =
                    gui::dimension<dimension_type>::width(
                    this->template parent_to<side_bar>().m_p_state_button->dimension()
                );
                const auto& state_button_height =
                    gui::dimension<dimension_type>::height(
                    this->template parent_to<side_bar>().m_p_state_button->dimension()
                );

                const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);

                if (this->template parent_to<side_bar>().m_minimized)
                {
                    auto left =
                        width_type::from(text_height) < state_button_width ?
                        left_type::from((state_button_width - width_type::from(text_height)) / 2) +
                            left_type::from(padding) +
                            left_type::from(text_height) :
                        left_type::from(padding) + left_type::from(text_height);
                    auto top = state_button_top + top_type::from(state_button_width + padding);
                    return { std::move(left), std::move(top) };
                }
                else
                {
                    auto left = state_button_left + left_type::from(state_button_width + padding);
                    auto top =
                        text_height < state_button_height ?
                        top_type::from((state_button_height - text_height) / 2) + top_type::from(padding) :
                        top_type::from(padding);
                    return { std::move(left), std::move(top) };
                }
            }

            position_type state_button_position(const height_type& padding)
            const
            {
                const auto& caption_width = gui::dimension<dimension_type>::width(this->dimension());
                const auto& caption_height = gui::dimension<dimension_type>::height(this->dimension());
                const auto& state_button_width =
                    gui::dimension<dimension_type>::width(
                    this->template parent_to<side_bar>().m_p_state_button->dimension()
                );
                const auto& state_button_height =
                    gui::dimension<dimension_type>::height(
                    this->template parent_to<side_bar>().m_p_state_button->dimension()
                );

                if (this->template parent_to<side_bar>().m_minimized)
                {
                    auto left =
                        std::max(
                            (left_type::from(caption_width) - left_type::from(state_button_width)) / 2, left_type{ 0 }
                        );
                    auto top = top_type::from(padding);
                    return { std::move(left), std::move(top) };
                }
                else
                {
                    auto left = left_type::from(padding);
                    auto top =
                        std::max(
                            (top_type::from(caption_height) - top_type::from(state_button_height)) / 2, top_type{ 0 }
                        );
                    return { std::move(left), std::move(top) };
                }
            }


        };

        class splitter : public inner_item_type
        {
        public:
            // constructors and destructor

            explicit splitter(side_bar& side_bar_)
            :
            inner_item_type(
                side_bar_,
                position_type{ left_type{ 0 }, top_type{ 0 } },
                dimension_type{ width_type{ 0 }, height_type{ 0 } }
            ),
            m_need_size_recalculation(true),
            m_pressed_position(position_type{ left_type{ 0 }, top_type{ 0 } })
            {}


        private:
            // variables

            bool m_need_size_recalculation;

            position_type m_pressed_position;


            // virtual functions

            virtual void resized_impl()
            override
            {
                m_need_size_recalculation = true;

                calculate_position_and_dimension();
            }

            virtual void paint_impl(canvas_type& canvas)
            const override
            {
                if (this->template parent_to<side_bar>().m_minimized)
                    return;

                auto original_background = canvas.get_background().clone();
                canvas.set_background(
                    stdalt::make_unique<solid_background_type>(system_color_set_type::dialog_background())
                );

                canvas.fill_rectangle(this->position(), this->dimension());

                canvas.set_background(std::move(original_background));
            }

            virtual void mouse_pressed_impl(const position_type& cursor_position)
            override
            {
                if (this->template parent_to<side_bar>().m_minimized)
                    return;

                m_pressed_position = cursor_position;
            }

            virtual void mouse_released_impl(const position_type& cursor_position)
            override
            {
                if (this->template parent_to<side_bar>().m_minimized)
                    return;

                resize_side_bar(cursor_position);
            }

            virtual void mouse_moved_impl(const position_type& cursor_position)
            override
            {
                if (this->template parent_to<side_bar>().m_minimized)
                    return;
                if (!this->parent().mouse_captured(this))
                    return;

                resize_side_bar(cursor_position);
            }

            virtual void mouse_entered_impl()
            override
            {
                if (this->template parent_to<side_bar>().m_minimized)
                    return;

                auto p_cursor =
                    stdalt::make_unique<system_cursor_type>(system_cursor_type::style_type::horizontal_resize);
                this->template parent_to<side_bar>().set_cursor(std::move(p_cursor));
            }

            virtual void mouse_left_impl()
            override
            {
                if (this->template parent_to<side_bar>().m_minimized)
                    return;

                this->template parent_to<side_bar>().set_cursor(std::unique_ptr<cursor_type>{});
            }


            // functions

            void calculate_position_and_dimension()
            {
                if (!m_need_size_recalculation)
                    return;

                if (this->template parent_to<side_bar>().m_minimized)
                {
                    this->set_position(position_type{ left_type{ 0 }, top_type{ 0 } });
                    this->set_dimension(dimension_type{ width_type{ 0 }, height_type{ 0 } });
                }
                else
                {
                    const auto& client_height =
                        gui::dimension<dimension_type>::height(this->parent().client_dimension());
                    const auto& caption_height =
                        gui::dimension<dimension_type>::height(
                            this->template parent_to<side_bar>().m_p_caption->dimension()
                        );

                    this->set_position(position_type{ left_type{ 0 }, top_type::from(caption_height) });
                    this->set_dimension(
                        dimension_type{
                            width_type{ 1 } / 2,
                            client_height > caption_height ? client_height - caption_height : height_type{ 0 }
                        }
                    );
                }

                m_need_size_recalculation = false;
            }

            void resize_side_bar(const position_type& current_position)
            {
                if (this->template parent_to<side_bar>().m_minimized)
                    return;

                const auto& width = gui::dimension<dimension_type>::width(this->parent().dimension());

                const auto& pressed_left = gui::position<position_type>::left(m_pressed_position);
                const auto& current_left = gui::position<position_type>::left(current_position);
                auto new_width =
                    width_type::from(
                        std::max(left_type::from(width) + (pressed_left - current_left), left_type{ 0 })
                    );

                this->template parent_to<side_bar>().set_width(std::move(new_width));
            }


        };


        // static functions

        static void initialize_side_bar(side_bar& side_bar_)
        {
            side_bar_.set_dimension(dimension_type{ width_type{ 16 }, height_type{ 16 } });
            side_bar_.set_background(
                stdalt::make_unique<solid_background_type>(system_color_set_type::dialog_background())
            );

            create_items(side_bar_);

            set_observers(side_bar_);

            side_bar_.m_preferred_width= gui::dimension<dimension_type>::width(side_bar_.dimension());
        }

        static void create_items(side_bar& side_bar_)
        {
            side_bar_.m_p_state_button = stdalt::make_unique<state_button>(side_bar_);
            side_bar_.m_p_caption = stdalt::make_unique<caption>(side_bar_);

            side_bar_.m_p_splitter = stdalt::make_unique<splitter>(side_bar_);
        }

        static void set_observers(side_bar& side_bar_)
        {
            assert(side_bar_.m_p_caption);
            assert(side_bar_.m_p_splitter);

            side_bar_.size_observer_set().resized().connect(
                [&side_bar_]()
                {
                    side_bar_.m_p_state_button->resized();
                    side_bar_.m_p_caption->resized();
                    side_bar_.m_p_splitter->resized();
                }
            );

            side_bar_.paint_observer_set().paint_background().disconnect_all_slots();
            side_bar_.paint_observer_set().paint_background().connect(
                [&side_bar_](canvas_type& canvas) { return paint_background(side_bar_, canvas); }
            );
            side_bar_.paint_observer_set().paint().connect(
                [&side_bar_](canvas_type& canvas)
                {
                    canvas.begin_transaction(side_bar_.client_dimension());

                    side_bar_.m_p_caption->paint(canvas);
                    side_bar_.m_p_state_button->paint(canvas);
                    side_bar_.m_p_splitter->paint(canvas);

                    canvas.end_transaction();
                }
            );

            side_bar_.mouse_observer_set().pressed().connect(
                [&side_bar_](const mouse_button_type button, const position_type& position, bool, bool, bool)
                {
                    if (button != mouse_button_type::left)
                        return;

                    side_bar_.m_p_state_button->mouse_pressed(button, position);
                    side_bar_.m_p_splitter->mouse_pressed(button, position);
                }
            );
            side_bar_.mouse_observer_set().released().connect(
                [&side_bar_](const mouse_button_type button, const position_type& position, bool, bool, bool)
                {
                    if (button != mouse_button_type::left)
                        return;

                    side_bar_.m_p_state_button->mouse_released(button, position);
                    side_bar_.m_p_splitter->mouse_released(button, position);
                }
            );
            side_bar_.mouse_observer_set().moved().connect(
                [&side_bar_](const position_type& position, bool, bool, bool)
                {
                    side_bar_.m_p_state_button->mouse_moved(position);
                    side_bar_.m_p_splitter->mouse_moved(position);
                }
            );
        }

        static bool paint_background(const side_bar& side_bar_, canvas_type& canvas)
        {
            if (!side_bar_.background())
                return false;

            canvas.set_background(side_bar_.background()->clone());
            canvas.fill_rectangle(position_type{ left_type{ 0 }, top_type{ 0 } }, side_bar_.client_dimension());

            return true;
        }


        // variables

        std::unique_ptr<state_button> m_p_state_button;

        std::unique_ptr<caption> m_p_caption;

        std::unique_ptr<splitter> m_p_splitter;

        width_type m_preferred_width;

        bool m_minimized;


        // functions

        void adjust_preferred_width(width_type& width)
        {
            if (this->has_parent())
            {
                const auto parent_width =
                    gui::dimension<dimension_type>::width(this->parent().client_dimension());

                auto max_width = parent_width > width_type{ 4 } ? parent_width - width_type{ 4 } : parent_width;
                if (width > max_width)
                    width = std::move(max_width);

                auto min_width = std::min(parent_width, width_type{ 4 });
                if (width < min_width)
                    width = std::move(min_width);
            }
            else
            {
                width_type min_width{ 4 };
                if (width < min_width)
                    width = std::move(min_width);
            }
        }


    };


}}}


#endif
