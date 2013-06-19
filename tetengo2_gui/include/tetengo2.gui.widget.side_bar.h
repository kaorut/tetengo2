/*! \file
    \brief The definition of tetengo2::gui::widget::side_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_SIDEBAR_H)
#define TETENGO2_GUI_WIDGET_SIDEBAR_H

#include <algorithm>
//#include <cassert>
//#include <memory>
//#include <utility>
//#include <vector>

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
        m_p_items()
        {
            initialize_side_bar(this);
        }

        /*!
            \brief Destroys the side bar.
        */
        virtual ~side_bar()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename canvas_type::size_type size_type;

        typedef typename canvas_type::color_type color_type;

        typedef typename gui::position<position_type>::left_type left_type;

        typedef typename gui::position<position_type>::top_type top_type;

        typedef typename gui::dimension<dimension_type>::width_type width_type;

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


        protected:
            // constructors

            item(const side_bar& side_bar_, position_type&& position, dimension_type&& dimension)
            :
            m_side_bar(side_bar_),
            m_position(std::move(position)),
            m_dimension(std::move(dimension))
            {}


            // functions

            const side_bar& side_bar_()
            const
            {
                return m_side_bar;
            }


        private:
            // variables

            const side_bar& m_side_bar;

            position_type m_position;

            dimension_type m_dimension;


            // virtual functions

            virtual void resized_impl()
            = 0;

            virtual void draw_impl(canvas_type& canvas)
            = 0;


        };

        class state_button : public item
        {
        public:
            // constructors and destructor

            explicit state_button(const side_bar& side_bar_)
            :
            item(side_bar_, position_type(left_type(0), top_type(0)), dimension_type(width_type(1), height_type(1)))
            {}


        private:
            // static functions

            static const color_type& background_color()
            {
                static const color_type singleton = make_background_color();
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

            static color_type make_border_color()
            {
                const color_type& base_color = system_color_set_type::title_bar_background();
                return color_type(base_color.red() / 2, base_color.green() / 2, base_color.blue() / 2);
            }


            // virtual functions

            virtual void resized_impl()
            override
            {}

            virtual void draw_impl(canvas_type& canvas)
            override
            {
                auto original_color = canvas.color();
                auto original_line_width = canvas.line_width();
                auto original_background = canvas.background().clone();
                canvas.set_color(border_color());
                canvas.set_line_width(size_type(1) / 16);
                canvas.set_background(make_unique<solid_background_type>(background_color()));

                const auto& left = gui::position<position_type>::left(this->position());
                const auto& top = gui::position<position_type>::top(this->position());
                const auto& width = gui::dimension<dimension_type>::width(this->dimension());
                const auto& height = gui::dimension<dimension_type>::height(this->dimension());
                std::vector<position_type> positions;
                positions.emplace_back(left, top);
                positions.emplace_back(left + left_type::from(width), top + top_type::from(height / 2));
                positions.emplace_back(left, top + top_type::from(height));

                canvas.fill_polygon(positions.begin(), positions.end());
                canvas.draw_polygon(positions.begin(), positions.end());

                canvas.set_background(std::move(original_background));
                canvas.set_line_width(std::move(original_line_width));
                canvas.set_color(std::move(original_color));
            }


        };

        class caption : public item
        {
        public:
            // constructors and destructor

            caption(const side_bar& side_bar_, std::unique_ptr<item> p_state_button)
            :
            item(side_bar_, position_type(left_type(0), top_type(0)), dimension_type(width_type(0), height_type(0))),
            m_p_state_button(std::move(p_state_button)),
            m_text_position()
            {}

            virtual ~caption()
            TETENGO2_CPP11_NOEXCEPT
            {}


        private:
            // variables

            const std::unique_ptr<item> m_p_state_button;

            boost::optional<position_type> m_text_position;


            // virtual functions

            virtual void resized_impl()
            override
            {
                m_text_position = boost::none;

                m_p_state_button->resized();
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

                m_p_state_button->draw(canvas);

                canvas.draw_text(this->side_bar_().text(), *m_text_position);

                canvas.set_background(std::move(original_background));
                canvas.set_color(std::move(original_color));
            }


            // functions

            void calculate_position_and_dimension(const canvas_type& canvas)
            {
                if (m_text_position)
                    return;

                static const auto padding = height_type(1) / 4;
                const auto text_dimension = canvas.calc_text_dimension(this->side_bar_().text());
                this->set_dimension(calculate_dimension(padding, text_dimension));

                m_p_state_button->set_position(state_button_position(padding));

                m_text_position = boost::make_optional(text_position(padding, text_dimension));
            }

            dimension_type calculate_dimension(const height_type& padding, const dimension_type& text_dimension)
            const
            {
                const dimension_type client_dimension = this->side_bar_().client_dimension();

                const auto& width = gui::dimension<dimension_type>::width(client_dimension);

                const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);
                const auto& status_button_height =
                    gui::dimension<dimension_type>::height(m_p_state_button->dimension());
                const auto& height = std::max(text_height, status_button_height); 
            
                return dimension_type(width, height + padding * 2);
            }

            position_type text_position(const height_type& padding, const dimension_type& text_dimension)
            const
            {
                const auto& state_button_left = gui::position<position_type>::left(m_p_state_button->position());
                const auto& state_button_width = gui::dimension<dimension_type>::width(m_p_state_button->dimension());
                auto left = state_button_left + left_type::from(state_button_width + padding);

                const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);
                const auto& status_button_height =
                    gui::dimension<dimension_type>::height(m_p_state_button->dimension());
                auto top =
                    text_height < status_button_height ?
                    top_type::from((status_button_height - text_height) / 2) + top_type::from(padding) :
                    top_type::from(padding);
            
                return position_type(std::move(left), std::move(top));
            }

            position_type state_button_position(const height_type& padding)
            const
            {
                auto left = left_type::from(padding);

                const auto& height = gui::dimension<dimension_type>::height(this->dimension());
                const auto& state_button_height =
                    gui::dimension<dimension_type>::height(m_p_state_button->dimension());
                assert(height >= state_button_height + padding * 2);
                auto top = top_type::from((height - state_button_height) / 2);

                return position_type(std::move(left), std::move(top));
            }


        };


        // static functions

        static void initialize_side_bar(side_bar* const p_side_bar)
        {
            p_side_bar->set_background(
                make_unique<solid_background_type>(system_color_set_type::dialog_background())
            );

            std::unique_ptr<item> p_state_button = make_unique<state_button>(*p_side_bar);
            std::unique_ptr<item> p_caption = make_unique<caption>(*p_side_bar, std::move(p_state_button));
            p_side_bar->m_p_items.push_back(std::move(p_caption));

            p_side_bar->paint_observer_set().paint_background().disconnect_all_slots();
            p_side_bar->paint_observer_set().paint_background().connect(
                [p_side_bar](canvas_type& canvas) { return paint_background(*p_side_bar, canvas); }
            );
            p_side_bar->paint_observer_set().paint().connect(
                [p_side_bar](canvas_type& canvas)
                {
                    std::for_each(
                        p_side_bar->m_p_items.begin(),
                        p_side_bar->m_p_items.end(),
                        [&canvas](const std::unique_ptr<item>& p_item)
                        {
                            p_item->resized();
                            p_item->draw(canvas);
                        }
                    );
                }
            );
        }

        static bool paint_background(const side_bar& side_bar, canvas_type& canvas)
        {
            if (!side_bar.background())
                return false;

            canvas.set_background(side_bar.background()->clone());
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), side_bar.client_dimension());

            return true;
        }


        // variables

        std::vector<std::unique_ptr<item>> m_p_items;


    };


}}}


#endif
