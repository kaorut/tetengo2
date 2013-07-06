/*! \file
    \brief The definition of tetengo2::gui::widget::side_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_SIDEBAR_H)
#define TETENGO2_GUI_WIDGET_SIDEBAR_H

#include <algorithm>
//#include <cassert>
//#include <chrono>
//#include <memory>
//#include <utility>
//#include <vector>

#include <boost/math/constants/constants.hpp>
//#include <boost/optional.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.custom_control.h"
#include "tetengo2.unique.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a side bar.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class side_bar : public custom_control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The solid background type.
        typedef typename traits_type::solid_background_type solid_background_type;

        //! The system color set type.
        typedef typename traits_type::system_color_set_type system_color_set_type;

        //! The mouse capture type.
        typedef typename traits_type::mouse_capture_type mouse_capture_type;

        //! The system cursor type.
        typedef typename traits_type::system_cursor_type system_cursor_type;

        //! The cursor type.
        typedef typename system_cursor_type::base_type cursor_type;

        //! The timer type.
        typedef typename traits_type::timer_type timer_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef
            custom_control<typename traits_type::base_type, widget_details_type, message_handler_details_type>
            base_type;

        //! The widget type.
        typedef typename base_type::base_type::base_type widget_type;

        //! The canvas type.
        typedef typename base_type::canvas_type canvas_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The width type.
        typedef typename gui::dimension<dimension_type>::width_type width_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;


        // constructors and destructor

        /*!
            \brief Creates a side bar.

            \param parent A parent widget.
        */
        explicit side_bar(widget_type& parent)
        :
        base_type(parent, base_type::scroll_bar_style_type::none),
        m_p_caption(),
        m_p_splitter(),
        m_p_mouse_capture(),
        m_p_mouse_captured_item(nullptr),
        m_preferred_width(0),
        m_minimized(false)
        {
            initialize_side_bar(this);
        }

        /*!
            \brief Destroys the side bar.
        */
        virtual ~side_bar()
        TETENGO2_CPP11_NOEXCEPT
        {}


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
            this->size_observer_set().resized()();
            if (this->has_parent())
            {
                this->parent().size_observer_set().resized()();
                this->parent().repaint();
            }
        }


    private:
        // types

        typedef typename base_type::mouse_observer_set_type mouse_observer_set_type;

        typedef typename mouse_observer_set_type::mouse_button_type mouse_button_type;

        typedef typename canvas_type::size_type size_type;

        typedef typename canvas_type::color_type color_type;

        typedef typename gui::position<position_type>::left_type left_type;

        typedef typename gui::position<position_type>::top_type top_type;

        typedef typename gui::dimension<dimension_type>::height_type height_type;

        class item
        {
        public:
            // constructors and destructors

            virtual ~item()
            TETENGO2_CPP11_NOEXCEPT
            {}


            // functions

            const position_type& position()
            const
            {
                return m_position;
            }

            void set_position(position_type position)
            {
                m_position = std::move(position);
            }

            const dimension_type& dimension()
            const
            {
                return m_dimension;
            }

            void set_dimension(dimension_type dimension)
            {
                m_dimension = std::move(dimension);
            }

            void resized()
            {
                resized_impl();
            }

            void draw(canvas_type& canvas)
            {
                draw_impl(canvas);
            }

            void mouse_pressed(const position_type& cursor_position)
            {
                if (!inside(cursor_position))
                    return;

                mouse_pressed_impl(cursor_position);
            }

            void mouse_released(const position_type& cursor_position)
            {
                if (!this->side_bar_().mouse_captured(this) && !inside(cursor_position))
                    return;

                mouse_released_impl(cursor_position);
            }

            void mouse_moved(const position_type& cursor_position)
            {

                if (this->side_bar_().mouse_captured(this) || inside(cursor_position))
                {
                    mouse_moved_impl(cursor_position);
                    if (!m_mouse_inside)
                    {
                        mouse_entered_impl();
                        m_mouse_inside = true;
                    }
                }
                else
                {
                    if (m_mouse_inside)
                    {
                        mouse_left_impl();
                        m_mouse_inside = false;
                    }
                }
            }


        protected:
            // constructors

            item(side_bar& side_bar_, position_type&& position, dimension_type&& dimension)
            :
            m_side_bar(side_bar_),
            m_position(std::move(position)),
            m_dimension(std::move(dimension)),
            m_mouse_inside(false)
            {}


            // functions

            const side_bar& side_bar_()
            const
            {
                return m_side_bar;
            }

            side_bar& side_bar_()
            {
                return m_side_bar;
            }


        private:
            // variables

            side_bar& m_side_bar;

            position_type m_position;

            dimension_type m_dimension;

            bool m_mouse_inside;


            // virtual functions

            virtual void resized_impl()
            {}

            virtual void draw_impl(canvas_type& canvas)
            = 0;

            virtual void mouse_pressed_impl(const position_type& cursor_position)
            {
                suppress_unused_variable_warning(cursor_position);
            }

            virtual void mouse_released_impl(const position_type& cursor_position)
            {
                suppress_unused_variable_warning(cursor_position);
            }

            virtual void mouse_moved_impl(const position_type& cursor_position)
            {
                suppress_unused_variable_warning(cursor_position);
            }

            virtual void mouse_entered_impl()
            {}

            virtual void mouse_left_impl()
            {}


            // functions

            bool inside(const position_type& position)
            const
            {
                const auto& left = gui::position<position_type>::left(m_position);
                const auto right = left + left_type::from(gui::dimension<dimension_type>::width(m_dimension));
                const auto& top = gui::position<position_type>::top(m_position);
                const auto bottom = top + top_type::from(gui::dimension<dimension_type>::height(m_dimension));

                const auto& cursor_left = gui::position<position_type>::left(position);
                const auto& cursor_top = gui::position<position_type>::top(position);

                return (left <= cursor_left && cursor_left < right) && (top <= cursor_top && cursor_top < bottom);
            }


        };

        class state_button : public item
        {
        public:
            // constructors and destructor

            explicit state_button(side_bar& side_bar_)
            :
            item(side_bar_, position_type(left_type(0), top_type(0)), dimension_type(width_type(1), height_type(1))),
            m_p_current_background_color(&background_color()),
            m_p_timer(tetengo2::make_unique<timer_type>(side_bar_, timer_proc, std::chrono::seconds(1)))
            {}


        private:
            // static functions

            static void timer_proc(bool& /*stop*/)
            {

            }

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
                    color_type(
                        static_cast<unsigned char>((0xFF * 3 + base_color.red() * 1) / 4),
                        static_cast<unsigned char>((0xFF * 3 + base_color.green() * 1) / 4),
                        static_cast<unsigned char>((0xFF * 3 + base_color.blue() * 1) / 4)
                    );
            }

            static color_type make_background_color_hovered()
            {
                const color_type& base_color = system_color_set_type::title_bar_background();
                return
                    color_type(
                        static_cast<unsigned char>((0xFF * 7 + base_color.red() * 1) / 8),
                        static_cast<unsigned char>((0xFF * 7 + base_color.green() * 1) / 8),
                        static_cast<unsigned char>((0xFF * 7 + base_color.blue() * 1) / 8)
                    );
            }

            static color_type make_border_color()
            {
                const color_type& base_color = system_color_set_type::title_bar_background();
                return color_type(base_color.red() / 2, base_color.green() / 2, base_color.blue() / 2);
            }


            // variables

            const color_type* m_p_current_background_color;

            std::unique_ptr<timer_type> m_p_timer;


            // virtual functions

            virtual void draw_impl(canvas_type& canvas)
            override
            {
                auto original_color = canvas.color();
                auto original_line_width = canvas.line_width();
                auto original_background = canvas.background().clone();
                canvas.set_color(border_color());
                canvas.set_line_width(size_type(1) / 16);
                canvas.set_background(make_unique<solid_background_type>(*m_p_current_background_color));

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
                suppress_unused_variable_warning(cursor_position);

                this->side_bar_().set_minimized(!this->side_bar_().m_minimized);
            }

            virtual void mouse_entered_impl()
            override
            {
                m_p_current_background_color = &background_color_hovered();
                this->side_bar_().repaint();
            }

            virtual void mouse_left_impl()
            override
            {
                m_p_current_background_color = &background_color();
                this->side_bar_().repaint();
            }


            // functions

            std::vector<position_type> make_triangle()
            const
            {
                const auto& left = gui::position<position_type>::left(this->position());
                const auto& top = gui::position<position_type>::top(this->position());
                const auto& width = gui::dimension<dimension_type>::width(this->dimension());
                const auto& height = gui::dimension<dimension_type>::height(this->dimension());

                std::vector<position_type> positions;
                positions.reserve(3);
                if (this->side_bar_().m_minimized)
                {
                    positions.emplace_back(left, top + top_type::from(height / 2));
                    positions.emplace_back(left + left_type::from(width), top);
                    positions.emplace_back(left + left_type::from(width), top + top_type::from(height));
                }
                else
                {
                    positions.emplace_back(left, top);
                    positions.emplace_back(left + left_type::from(width), top + top_type::from(height / 2));
                    positions.emplace_back(left, top + top_type::from(height));
                }

                return positions;
            }


        };

        class caption : public item
        {
        public:
            // constructors and destructor

            caption(side_bar& side_bar_)
            :
            item(side_bar_, position_type(left_type(0), top_type(0)), dimension_type(width_type(0), height_type(0))),
            m_text_position()
            {}

            virtual ~caption()
            TETENGO2_CPP11_NOEXCEPT
            {}


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
            }

            virtual void draw_impl(canvas_type& canvas)
            override
            {
                calculate_position_and_dimension(canvas);

                auto original_color = canvas.color();
                auto original_background = canvas.background().clone();
                canvas.set_color(system_color_set_type::title_bar_text());
                canvas.set_background(
                    make_unique<solid_background_type>(system_color_set_type::title_bar_background())
                );

                canvas.fill_rectangle(this->position(), this->dimension());

                canvas.draw_text(
                    this->side_bar_().text(),
                    *m_text_position,
                    this->side_bar_().m_minimized ? boost::math::constants::pi<double>() / 2.0 : 0.0
                );

                canvas.set_background(std::move(original_background));
                canvas.set_color(std::move(original_color));
            }


            // functions

            void ensure_dimension_calculated()
            {
                if (m_text_position)
                    return;

                const auto p_canvas = this->side_bar_().create_canvas();
                calculate_position_and_dimension(*p_canvas);
            }

            void calculate_position_and_dimension(const canvas_type& canvas)
            {
                if (m_text_position)
                    return;

                static const auto padding = height_type(1) / 4;
                const auto text_dimension = canvas.calc_text_dimension(this->side_bar_().text());
                this->set_dimension(calculate_dimension(padding, text_dimension));

                this->side_bar_().m_p_state_button->set_position(state_button_position(padding));

                m_text_position = boost::make_optional(text_position(padding, text_dimension));
            }

            dimension_type calculate_dimension(const height_type& padding, const dimension_type& text_dimension)
            const
            {
                const dimension_type client_dimension = this->side_bar_().client_dimension();
                const auto& client_width = gui::dimension<dimension_type>::width(client_dimension);
                const auto& client_height = gui::dimension<dimension_type>::height(client_dimension);

                const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);

                const auto& state_button_width =
                    gui::dimension<dimension_type>::width(this->side_bar_().m_p_state_button->dimension());
                const auto& state_button_height =
                    gui::dimension<dimension_type>::height(this->side_bar_().m_p_state_button->dimension());

                if (this->side_bar_().m_minimized)
                {
                    const auto& width = std::max(width_type::from(text_height), state_button_width); 
                    return dimension_type(width + width_type::from(padding) * 2, client_height);
                }
                else
                {
                    const auto& height = std::max(text_height, state_button_height); 
                    return dimension_type(client_width, height + padding * 2);
                }
            }

            position_type text_position(const height_type& padding, const dimension_type& text_dimension)
            const
            {
                const auto& state_button_left =
                    gui::position<position_type>::left(this->side_bar_().m_p_state_button->position());
                const auto& state_button_top =
                    gui::position<position_type>::left(this->side_bar_().m_p_state_button->position());
                const auto& state_button_width =
                    gui::dimension<dimension_type>::width(this->side_bar_().m_p_state_button->dimension());
                const auto& state_button_height =
                    gui::dimension<dimension_type>::height(this->side_bar_().m_p_state_button->dimension());

                const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);

                if (this->side_bar_().m_minimized)
                {
                    auto left =
                        width_type::from(text_height) < state_button_width ?
                        left_type::from((state_button_width - width_type::from(text_height)) / 2) +
                            left_type::from(padding) +
                            left_type::from(text_height) :
                        left_type::from(padding) + left_type::from(text_height);
                    auto top = state_button_top + top_type::from(state_button_width + padding);
                    return position_type(std::move(left), std::move(top));
                }
                else
                {
                    auto left = state_button_left + left_type::from(state_button_width + padding);
                    auto top =
                        text_height < state_button_height ?
                        top_type::from((state_button_height - text_height) / 2) + top_type::from(padding) :
                        top_type::from(padding);
                    return position_type(std::move(left), std::move(top));
                }
            }

            position_type state_button_position(const height_type& padding)
            const
            {
                const auto& caption_width = gui::dimension<dimension_type>::width(this->dimension());
                const auto& caption_height = gui::dimension<dimension_type>::height(this->dimension());
                const auto& state_button_width =
                    gui::dimension<dimension_type>::width(this->side_bar_().m_p_state_button->dimension());
                const auto& state_button_height =
                    gui::dimension<dimension_type>::height(this->side_bar_().m_p_state_button->dimension());

                if (this->side_bar_().m_minimized)
                {
                    auto left =
                        std::max(
                            (left_type::from(caption_width) - left_type::from(state_button_width)) / 2, left_type(0)
                        );
                    auto top = top_type::from(padding);
                    return position_type(std::move(left), std::move(top));
                }
                else
                {
                    auto left = left_type::from(padding);
                    auto top =
                        std::max(
                            (top_type::from(caption_height) - top_type::from(state_button_height)) / 2, top_type(0)
                        );
                    return position_type(std::move(left), std::move(top));
                }
            }


        };

        class splitter : public item
        {
        public:
            // constructors and destructor

            explicit splitter(side_bar& side_bar_)
            :
            item(side_bar_, position_type(left_type(0), top_type(0)), dimension_type(width_type(0), height_type(0))),
            m_need_size_recalculation(true),
            m_pressed_position(position_type(left_type(0), top_type(0)))
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
            }

            virtual void draw_impl(canvas_type& canvas)
            override
            {
                calculate_position_and_dimension();

                if (this->side_bar_().m_minimized)
                    return;

                auto original_background = canvas.background().clone();
                canvas.set_background(
                    make_unique<solid_background_type>(system_color_set_type::dialog_background())
                );

                canvas.fill_rectangle(this->position(), this->dimension());

                canvas.set_background(std::move(original_background));
            }

            virtual void mouse_pressed_impl(const position_type& cursor_position)
            override
            {
                if (this->side_bar_().m_minimized)
                    return;

                this->side_bar_().set_mouse_capture(this);

                m_pressed_position = cursor_position;
            }

            virtual void mouse_released_impl(const position_type& cursor_position)
            override
            {
                if (this->side_bar_().m_minimized)
                    return;

                this->side_bar_().release_mouse_capture();

                resize_side_bar(cursor_position);
            }

            virtual void mouse_moved_impl(const position_type& cursor_position)
            override
            {
                if (this->side_bar_().m_minimized)
                    return;
                if (!this->side_bar_().mouse_captured(this))
                    return;

                resize_side_bar(cursor_position);
            }

            virtual void mouse_entered_impl()
            override
            {
                if (this->side_bar_().m_minimized)
                    return;

                auto p_cursor = make_unique<system_cursor_type>(system_cursor_type::style_type::horizontal_resize);
                this->side_bar_().set_cursor(std::move(p_cursor));
            }

            virtual void mouse_left_impl()
            override
            {
                if (this->side_bar_().m_minimized)
                    return;

               this->side_bar_().set_cursor(std::unique_ptr<cursor_type>());
            }


            // functions

            void calculate_position_and_dimension()
            {
                if (!m_need_size_recalculation)
                    return;

                if (this->side_bar_().m_minimized)
                {
                    this->set_position(position_type(left_type(0), top_type(0)));
                    this->set_dimension(dimension_type(width_type(0), height_type(0)));
                }
                else
                {
                    const auto& client_height =
                        gui::dimension<dimension_type>::height(this->side_bar_().client_dimension());
                    const auto& caption_height =
                        gui::dimension<dimension_type>::height(this->side_bar_().m_p_caption->dimension());

                    this->set_position(position_type(left_type(0), top_type::from(caption_height)));
                    this->set_dimension(
                        dimension_type(
                            width_type(1) / 2,
                            client_height > caption_height ? client_height - caption_height : height_type(0)
                        )
                    );
                }

                m_need_size_recalculation = false;
            }

            void resize_side_bar(const position_type& current_position)
            {
                if (this->side_bar_().m_minimized)
                    return;

                const auto& width = gui::dimension<dimension_type>::width(this->side_bar_().dimension());

                const auto& pressed_left = gui::position<position_type>::left(m_pressed_position);
                const auto& current_left = gui::position<position_type>::left(current_position);
                auto new_width =
                    width_type::from(
                        std::max(left_type::from(width) + (pressed_left - current_left), left_type(0))
                    );

                this->side_bar_().set_width(std::move(new_width));
            }


        };


        // static functions

        static void initialize_side_bar(side_bar* const p_side_bar)
        {
            p_side_bar->set_dimension(dimension_type(width_type(16), height_type(16)));
            p_side_bar->set_background(
                make_unique<solid_background_type>(system_color_set_type::dialog_background())
            );

            create_items(*p_side_bar);

            set_observers(*p_side_bar);

            p_side_bar->m_preferred_width= gui::dimension<dimension_type>::width(p_side_bar->dimension());
        }

        static void create_items(side_bar& side_bar_)
        {
            side_bar_.m_p_state_button = make_unique<state_button>(side_bar_);
            side_bar_.m_p_caption = make_unique<caption>(side_bar_);

            side_bar_.m_p_splitter = make_unique<splitter>(side_bar_);
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
                    side_bar_.m_p_caption->draw(canvas);
                    side_bar_.m_p_state_button->draw(canvas);
                    side_bar_.m_p_splitter->draw(canvas);
                }
            );

            side_bar_.mouse_observer_set().pressed().connect(
                [&side_bar_](const mouse_button_type button, const position_type& position, bool, bool, bool)
                {
                    if (button != mouse_button_type::left)
                        return;

                    side_bar_.m_p_state_button->mouse_pressed(position);
                    side_bar_.m_p_splitter->mouse_pressed(position);
                }
            );
            side_bar_.mouse_observer_set().released().connect(
                [&side_bar_](const mouse_button_type button, const position_type& position, bool, bool, bool)
                {
                    if (button != mouse_button_type::left)
                        return;

                    side_bar_.m_p_state_button->mouse_released(position);
                    side_bar_.m_p_splitter->mouse_released(position);
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
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), side_bar_.client_dimension());

            return true;
        }


        // variables

        std::unique_ptr<state_button> m_p_state_button;

        std::unique_ptr<caption> m_p_caption;

        std::unique_ptr<splitter> m_p_splitter;

        std::unique_ptr<mouse_capture_type> m_p_mouse_capture;

        const item* m_p_mouse_captured_item;

        width_type m_preferred_width;

        bool m_minimized;


        // functions

        void adjust_preferred_width(width_type& width)
        {
            if (this->has_parent())
            {
                const auto parent_width =
                    gui::dimension<dimension_type>::width(this->parent().client_dimension());

                auto max_width = parent_width > width_type(4) ? parent_width - width_type(4) : parent_width;
                if (width > max_width)
                    width = std::move(max_width);

                auto min_width = std::min(parent_width, width_type(4));
                if (width < min_width)
                    width = std::move(min_width);
            }
            else
            {
                width_type min_width(4);
                if (width < min_width)
                    width = std::move(min_width);
            }
        }

        bool mouse_captured(const item* const p_item)
        const
        {
            return static_cast<bool>(m_p_mouse_capture) && m_p_mouse_captured_item == p_item;
        }

        void set_mouse_capture(const item* const p_item)
        {
            m_p_mouse_capture = tetengo2::make_unique<mouse_capture_type>(*this);
            m_p_mouse_captured_item = p_item;
        }

        void release_mouse_capture()
        {
            m_p_mouse_captured_item = nullptr;
            m_p_mouse_capture.reset();
        }


    };


}}}


#endif
