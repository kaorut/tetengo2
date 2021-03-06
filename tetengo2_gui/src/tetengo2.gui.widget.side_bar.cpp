/*! \file
    \brief The definition of tetengo2::gui::widget::side_bar.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/operators.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/position.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/side_bar.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::widget {
    class side_bar::impl : private boost::noncopyable
    {
    public:
        // types

        //! The dimension unit type.
        using dimension_unit_type = side_bar::dimension_unit_type;


        // static functions

        static void initialize_side_bar(side_bar& side_bar_)
        {
            side_bar_.set_dimension(dimension_type{ dimension_unit_type{ 16 }, dimension_unit_type{ 16 } });
            side_bar_.set_background(std::make_unique<solid_background_type>(

                system_color_set_type::instance().dialog_background()));

            create_items(side_bar_);

            set_observers(side_bar_);

            side_bar_.m_p_impl->m_preferred_width = side_bar_.dimension().width();
        }

        static void create_items(side_bar& side_bar_)
        {
            side_bar_.m_p_impl->m_p_state_button = std::make_unique<state_button>(side_bar_);
            side_bar_.m_p_impl->m_p_caption = std::make_unique<caption>(side_bar_);

            side_bar_.m_p_impl->m_p_splitter = std::make_unique<splitter>(side_bar_);
        }

        static void set_observers(side_bar& side_bar_)
        {
            assert(side_bar_.m_p_impl->m_p_caption);
            assert(side_bar_.m_p_impl->m_p_splitter);

            side_bar_.size_observer_set().resized().connect([&side_bar_]() {
                side_bar_.m_p_impl->m_p_state_button->resized();
                side_bar_.m_p_impl->m_p_caption->resized();
                side_bar_.m_p_impl->m_p_splitter->resized();
            });

            side_bar_.paint_observer_set().paint_background().disconnect_all_slots();
            side_bar_.paint_observer_set().paint_background().connect([](canvas_type&) { return true; });
            side_bar_.paint_observer_set().paint().connect([&side_bar_](canvas_type& canvas) {
                canvas.begin_transaction(side_bar_.client_dimension());

                side_bar_.m_p_impl->m_p_caption->paint(canvas);
                side_bar_.m_p_impl->m_p_state_button->paint(canvas);
                side_bar_.m_p_impl->m_p_splitter->paint(canvas);

                canvas.end_transaction();
            });

            side_bar_.mouse_observer_set().pressed().connect(
                [&side_bar_](const mouse_button_type button, const position_type& position, bool, bool, bool) {
                    if (button != mouse_button_type::left)
                        return;

                    side_bar_.m_p_impl->m_p_state_button->mouse_pressed(button, position);
                    side_bar_.m_p_impl->m_p_splitter->mouse_pressed(button, position);
                });
            side_bar_.mouse_observer_set().released().connect(
                [&side_bar_](const mouse_button_type button, const position_type& position, bool, bool, bool) {
                    if (button != mouse_button_type::left)
                        return;

                    side_bar_.m_p_impl->m_p_state_button->mouse_released(button, position);
                    side_bar_.m_p_impl->m_p_splitter->mouse_released(button, position);
                });
            side_bar_.mouse_observer_set().moved().connect(
                [&side_bar_](const position_type& position, bool, bool, bool) {
                    side_bar_.m_p_impl->m_p_state_button->mouse_moved(position);
                    side_bar_.m_p_impl->m_p_splitter->mouse_moved(position);
                });
        }


        // constructors and destructor

        impl() : m_p_caption{}, m_p_splitter{}, m_preferred_width{ dimension_unit_type{} }, m_minimized{ false } {}


        // functions

        const dimension_unit_type& preferred_width(side_bar& self)
        {
            if (m_minimized)
            {
                return m_p_caption->width();
            }
            else
            {
                adjust_preferred_width(m_preferred_width, self);
                return m_preferred_width;
            }
        }

        const dimension_unit_type& normal_preferred_width(side_bar& self)
        {
            adjust_preferred_width(m_preferred_width, self);
            return m_preferred_width;
        }

        void set_width(dimension_unit_type width, side_bar& self)
        {
            const auto& previous_width = self.dimension().width();

            adjust_preferred_width(width, self);

            if (width == previous_width)
                return;

            m_preferred_width = std::move(width);
            if (self.has_parent())
            {
                self.parent().size_observer_set().resized()();
                self.parent().repaint(true);
            }
        }

        bool minimized() const
        {
            return m_minimized;
        }

        void set_minimized(const bool minimized, side_bar& self)
        {
            m_minimized = minimized;

            if (!m_minimized)
                self.set_dimension(dimension_type{ m_preferred_width, self.dimension().height() });

            self.size_observer_set().resized()();
            if (self.has_parent())
            {
                self.parent().size_observer_set().resized()();
                self.parent().repaint();
            }
        }

        position_type child_control_area_position() const
        {
            const auto& caption_dimension = m_p_caption->dimension();
            const auto& splitter_dimension = m_p_splitter->dimension();

            return { position_unit_type::from(splitter_dimension.width()),
                     position_unit_type::from(caption_dimension.height()) };
        }

        dimension_type child_control_area_dimension(const side_bar& self) const
        {
            const auto  client_dimension = self.client_dimension();
            const auto& client_width = client_dimension.width();
            const auto& client_height = client_dimension.height();
            const auto& caption_dimension = m_p_caption->dimension();
            const auto& caption_height = caption_dimension.height();
            const auto& splitter_dimension = m_p_splitter->dimension();
            const auto& splitter_width = splitter_dimension.width();

            auto width = client_width > splitter_width ? client_width - splitter_width : dimension_unit_type{};
            auto height = client_height > caption_height ? client_height - caption_height : dimension_unit_type{};

            return { std::move(width), std::move(height) };
        }


    private:
        // types

        using timer_type = gui::timer;

        using solid_background_type = gui::drawing::solid_background;

        using system_color_set_type = gui::drawing::system_color_set;

        using mouse_observer_set_type = typename custom_control::mouse_observer_set_type;

        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;

        using color_type = typename canvas_type::color_type;

        using position_unit_type = typename position_type::unit_type;

        using scroll_bar_style_type = typename custom_control::scroll_bar_style_type;

        class state_button : public inner_item
        {
        public:
            // constructors and destructor

            explicit state_button(side_bar& side_bar_)
            : inner_item{ side_bar_,
                          position_type{},
                          dimension_type{ dimension_unit_type{ 1 }, dimension_unit_type{ 1 } } },
              m_p_current_background_color{ &background_color() }, m_p_timer{}, m_animation_step{ 0 }
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
                const color_type& base_color = system_color_set_type::instance().title_bar_background();
                return { static_cast<unsigned char>((0xFF * 3 + base_color.red() * 1) / 4),
                         static_cast<unsigned char>((0xFF * 3 + base_color.green() * 1) / 4),
                         static_cast<unsigned char>((0xFF * 3 + base_color.blue() * 1) / 4) };
            }

            static color_type make_background_color_hovered()
            {
                const color_type& base_color = system_color_set_type::instance().title_bar_background();
                return { static_cast<unsigned char>((0xFF * 7 + base_color.red() * 1) / 8),
                         static_cast<unsigned char>((0xFF * 7 + base_color.green() * 1) / 8),
                         static_cast<unsigned char>((0xFF * 7 + base_color.blue() * 1) / 8) };
            }

            static color_type make_border_color()
            {
                const color_type& base_color = system_color_set_type::instance().title_bar_background();
                return { static_cast<unsigned char>(base_color.red() / 2),
                         static_cast<unsigned char>(base_color.green() / 2),
                         static_cast<unsigned char>(base_color.blue() / 2) };
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
                    (static_cast<double>(animation_step) / max_animation_step() + (2.0 / 3.0) * vertex) *
                    boost::math::constants::pi<double>();

                const double x = std::cos(angle);
                const double y = std::sin(angle);
                return { position_unit_type{ static_cast<std::ptrdiff_t>(x * 256) } / 256,
                         position_unit_type{ static_cast<std::ptrdiff_t>(y * 256) } / 256 };
            }


            // variables

            const color_type* m_p_current_background_color;

            std::unique_ptr<timer_type> m_p_timer;

            std::size_t m_animation_step;


            // virtual functions

            virtual void paint_impl(canvas_type& canvas) const override
            {
                auto original_color = canvas.get_color();
                auto original_line_width = canvas.line_width();
                auto original_background = canvas.get_background().clone();
                canvas.set_color(border_color());
                canvas.set_line_width(dimension_unit_type{ 1 } / 16);
                canvas.set_background(
                    std::make_unique<solid_background_type>(canvas.drawing_details(), *m_p_current_background_color));

                const auto triangle = make_triangle();
                canvas.fill_polygon(triangle);
                canvas.draw_polygon(triangle);

                canvas.set_background(std::move(original_background));
                canvas.set_line_width(std::move(original_line_width));
                canvas.set_color(std::move(original_color));
            }

            virtual void mouse_released_impl(const position_type& cursor_position) override
            {
                if (!this->inside(cursor_position))
                    return;

                if (m_animation_step > 0)
                    return;

                m_p_timer = std::make_unique<timer_type>(
                    this->parent(),
                    [this](bool& stop) { this->timer_proc(stop); },
                    animation_duration() / max_animation_step(),
                    false);
                {
                    bool dummy_stop = false;
                    timer_proc(dummy_stop);
                }
            }

            virtual void mouse_entered_impl() override
            {
                m_p_current_background_color = &background_color_hovered();
                this->parent().repaint_partially(this->position(), this->dimension());
            }

            virtual void mouse_left_impl() override
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
                if (m_animation_step <
                    max_animation_step() + animation_finish_wait_duration().count() / max_animation_step())
                {
                    ++m_animation_step;
                    return;
                }

                this->template parent_as<side_bar>().set_minimized(
                    !this->template parent_as<side_bar>().m_p_impl->m_minimized);
                m_animation_step = 0;
                stop = true;
            }

            std::vector<position_type> make_triangle() const
            {
                const auto& left = this->position().left();
                const auto& top = this->position().top();
                const auto& width = this->dimension().width();
                const auto& height = this->dimension().height();

                std::vector<position_type> positions{};
                positions.reserve(3);
                for (std::size_t i = 0; i < 3; ++i)
                {
                    const std::size_t step_ =
                        this->template parent_as<side_bar>().m_p_impl->m_minimized ?
                            (m_animation_step < max_animation_step() ? max_animation_step() - m_animation_step : 0) :
                            (m_animation_step < max_animation_step() ? m_animation_step : max_animation_step());
                    const position_type vertex_position = triangle_vertex_position(step_, i);
                    position_unit_type  vertex_left = left + (vertex_position.left() + position_unit_type{ 1 }) *
                                                                position_unit_type::from(width).value() / 2;
                    position_unit_type vertex_top = top + (vertex_position.top() + position_unit_type{ 1 }) *
                                                              position_unit_type::from(height).value() / 2;
                    positions.emplace_back(std::move(vertex_left), std::move(vertex_top));
                }

                return positions;
            }
        };

        class caption : public inner_item
        {
        public:
            // constructors and destructor

            explicit caption(side_bar& side_bar_)
            : inner_item{ side_bar_, position_type{}, dimension_type{} }, m_text_position{}
            {}

            virtual ~caption() = default;


            // functions

            const dimension_unit_type& width()
            {
                ensure_dimension_calculated();
                return this->dimension().width();
            }


        private:
            // variables

            tetengo2::stdalt::optional<position_type> m_text_position;


            // virtual functions

            virtual void resized_impl() override
            {
                m_text_position = TETENGO2_STDALT_NULLOPT;

                ensure_dimension_calculated();
            }

            virtual void paint_impl(canvas_type& canvas) const override
            {
                auto original_color = canvas.get_color();
                auto p_original_background = canvas.get_background().clone();
                canvas.set_color(system_color_set_type::instance().title_bar_text());
                canvas.set_background(std::make_unique<solid_background_type>(
                    canvas.drawing_details(), system_color_set_type::instance().title_bar_background()));

                canvas.fill_rectangle(this->position(), this->dimension());

                canvas.draw_text(
                    this->parent().text(),
                    *m_text_position,
                    this->template parent_as<side_bar>().m_p_impl->m_minimized ?
                        boost::math::constants::pi<double>() / 2.0 :
                        0.0);

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

                static const auto padding = dimension_unit_type{ 1 } / 4;
                const auto        text_dimension = canvas.calc_text_dimension(this->parent().text());
                this->set_dimension(calculate_dimension(padding, text_dimension));

                this->template parent_as<side_bar>().m_p_impl->m_p_state_button->set_position(
                    state_button_position(padding));

                m_text_position = tetengo2::stdalt::make_optional(text_position(padding, text_dimension));
            }

            dimension_type
            calculate_dimension(const dimension_unit_type& padding, const dimension_type& text_dimension) const
            {
                const dimension_type client_dimension = this->parent().client_dimension();
                const auto&          client_width = client_dimension.width();
                const auto&          client_height = client_dimension.height();

                const auto& text_height = text_dimension.height();

                const auto& state_button_width =
                    this->template parent_as<side_bar>().m_p_impl->m_p_state_button->dimension().width();
                const auto& state_button_height =
                    this->template parent_as<side_bar>().m_p_impl->m_p_state_button->dimension().height();

                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                {
                    const auto& width = std::max(dimension_unit_type::from(text_height), state_button_width);
                    return { width + dimension_unit_type::from(padding) * 2, client_height };
                }
                else
                {
                    const auto& height = std::max(text_height, state_button_height);
                    return { client_width, height + padding * 2 };
                }
            }

            position_type text_position(const dimension_unit_type& padding, const dimension_type& text_dimension) const
            {
                const auto& state_button_left =
                    this->template parent_as<side_bar>().m_p_impl->m_p_state_button->position().left();
                const auto& state_button_top =
                    this->template parent_as<side_bar>().m_p_impl->m_p_state_button->position().top();
                const auto& state_button_width =
                    this->template parent_as<side_bar>().m_p_impl->m_p_state_button->dimension().width();
                const auto& state_button_height =
                    this->template parent_as<side_bar>().m_p_impl->m_p_state_button->dimension().height();

                const auto& text_height = text_dimension.height();

                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                {
                    auto left = dimension_unit_type::from(text_height) < state_button_width ?
                                    position_unit_type::from(
                                        (state_button_width - dimension_unit_type::from(text_height)) / 2) +
                                        position_unit_type::from(padding) + position_unit_type::from(text_height) :
                                    position_unit_type::from(padding) + position_unit_type::from(text_height);
                    auto top = state_button_top + position_unit_type::from(state_button_width + padding);
                    return { std::move(left), std::move(top) };
                }
                else
                {
                    auto left = state_button_left + position_unit_type::from(state_button_width + padding);
                    auto top = text_height < state_button_height ?
                                   position_unit_type::from((state_button_height - text_height) / 2) +
                                       position_unit_type::from(padding) :
                                   position_unit_type::from(padding);
                    return { std::move(left), std::move(top) };
                }
            }

            position_type state_button_position(const dimension_unit_type& padding) const
            {
                const auto& caption_width = this->dimension().width();
                const auto& caption_height = this->dimension().height();
                const auto& state_button_width =
                    this->template parent_as<side_bar>().m_p_impl->m_p_state_button->dimension().width();
                const auto& state_button_height =
                    this->template parent_as<side_bar>().m_p_impl->m_p_state_button->dimension().height();

                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                {
                    auto left = std::max(
                        (position_unit_type::from(caption_width) - position_unit_type::from(state_button_width)) / 2,
                        position_unit_type{});
                    auto top = position_unit_type::from(padding);
                    return { std::move(left), std::move(top) };
                }
                else
                {
                    auto left = position_unit_type::from(padding);
                    auto top = std::max(
                        (position_unit_type::from(caption_height) - position_unit_type::from(state_button_height)) / 2,
                        position_unit_type{});
                    return { std::move(left), std::move(top) };
                }
            }
        };

        class splitter : public inner_item
        {
        public:
            // constructors and destructor

            explicit splitter(side_bar& side_bar_)
            : inner_item{ side_bar_, position_type{}, dimension_type{} }, m_need_size_recalculation{ true },
              m_pressed_position{ position_type{} }
            {}


        private:
            // types

            using system_cursor_type = cursor::system;


            // variables

            bool m_need_size_recalculation;

            position_type m_pressed_position;


            // virtual functions

            virtual void resized_impl() override
            {
                m_need_size_recalculation = true;

                calculate_position_and_dimension();
            }

            virtual void paint_impl(canvas_type& canvas) const override
            {
                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                    return;

                auto original_background = canvas.get_background().clone();
                canvas.set_background(std::make_unique<solid_background_type>(
                    canvas.drawing_details(), system_color_set_type::instance().dialog_background()));

                canvas.fill_rectangle(this->position(), this->dimension());

                canvas.set_background(std::move(original_background));
            }

            virtual void mouse_pressed_impl(const position_type& cursor_position) override
            {
                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                    return;

                m_pressed_position = cursor_position;
            }

            virtual void mouse_released_impl(const position_type& cursor_position) override
            {
                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                    return;

                resize_side_bar(cursor_position);
            }

            virtual void mouse_moved_impl(const position_type& cursor_position) override
            {
                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                    return;
                if (!this->parent().mouse_captured(this))
                    return;

                resize_side_bar(cursor_position);
            }

            virtual void mouse_entered_impl() override
            {
                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                    return;

                auto p_cursor = std::make_unique<system_cursor_type>(system_cursor_type::style_type::horizontal_resize);
                this->template parent_as<side_bar>().set_cursor(std::move(p_cursor));
            }

            virtual void mouse_left_impl() override
            {
                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                    return;

                this->template parent_as<side_bar>().set_cursor(std::unique_ptr<cursor_type>{});
            }


            // functions

            void calculate_position_and_dimension()
            {
                if (!m_need_size_recalculation)
                    return;

                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                {
                    this->set_position(position_type{});
                    this->set_dimension(dimension_type{});
                }
                else
                {
                    const auto& client_height = this->parent().client_dimension().height();
                    const auto& caption_height =
                        this->template parent_as<side_bar>().m_p_impl->m_p_caption->dimension().height();

                    this->set_position(position_type{ position_unit_type{}, position_unit_type::from(caption_height) });
                    this->set_dimension(dimension_type{
                        dimension_unit_type{ 1 } / 2,
                        client_height > caption_height ? client_height - caption_height : dimension_unit_type{} });
                }

                m_need_size_recalculation = false;
            }

            void resize_side_bar(const position_type& current_position)
            {
                if (this->template parent_as<side_bar>().m_p_impl->m_minimized)
                    return;

                const auto& width = this->parent().dimension().width();

                const auto& pressed_left = m_pressed_position.left();
                const auto& current_left = current_position.left();
                auto        new_width = dimension_unit_type::from(
                    std::max(position_unit_type::from(width) + (pressed_left - current_left), position_unit_type{}));

                this->template parent_as<side_bar>().set_width(std::move(new_width));
            }
        };


        // variables

        std::unique_ptr<state_button> m_p_state_button;

        std::unique_ptr<caption> m_p_caption;

        std::unique_ptr<splitter> m_p_splitter;

        dimension_unit_type m_preferred_width;

        bool m_minimized;


        // functions

        void adjust_preferred_width(dimension_unit_type& width, side_bar& self)
        {
            if (self.has_parent())
            {
                const auto parent_width = self.parent().client_dimension().width();

                auto max_width =
                    parent_width > dimension_unit_type{ 4 } ? parent_width - dimension_unit_type{ 4 } : parent_width;
                if (width > max_width)
                    width = std::move(max_width);

                auto min_width = std::min(parent_width, dimension_unit_type{ 4 });
                if (width < min_width)
                    width = std::move(min_width);
            }
            else
            {
                auto min_width = dimension_unit_type{ 4 };
                if (width < min_width)
                    width = std::move(min_width);
            }
        }
    };


    side_bar::side_bar(widget& parent)
    : custom_control{ parent, false, scroll_bar_style_type::none }, m_p_impl{ std::make_unique<impl>() }
    {
        impl::initialize_side_bar(*this);
    }

    side_bar::~side_bar() = default;

    const side_bar::dimension_unit_type& side_bar::preferred_width()
    {
        return m_p_impl->preferred_width(*this);
    }

    const side_bar::dimension_unit_type& side_bar::normal_preferred_width()
    {
        return m_p_impl->normal_preferred_width(*this);
    }

    void side_bar::set_width(dimension_unit_type width)
    {
        m_p_impl->set_width(std::move(width), *this);
    }

    bool side_bar::minimized() const
    {
        return m_p_impl->minimized();
    }

    void side_bar::set_minimized(const bool minimized)
    {
        m_p_impl->set_minimized(minimized, *this);
    }

    side_bar::position_type side_bar::child_control_area_position() const
    {
        return m_p_impl->child_control_area_position();
    }

    side_bar::dimension_type side_bar::child_control_area_dimension() const
    {
        return m_p_impl->child_control_area_dimension(*this);
    }
}
