/*! \file
    \brief The definition of tetengo2::gui::widget::side_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_SIDEBAR_H)
#define TETENGO2_GUI_WIDGET_SIDEBAR_H

#include <algorithm>
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

            item(position_type&& position, dimension_type&& dimension)
            :
            m_position(std::move(position)),
            m_dimension(std::move(dimension))
            {}


            // functions

            const position_type& position()
            const
            {
                return m_position;
            }

            const dimension_type& dimension()
            const
            {
                return m_dimension;
            }

            void set_position_and_dimension(position_type position, dimension_type dimension)
            {
                m_position = std::move(position);
                m_dimension = std::move(dimension);
            }


        private:
            // variables

            position_type m_position;

            dimension_type m_dimension;


            // virtual functions

            virtual void resized_impl()
            = 0;

            virtual void draw_impl(canvas_type& canvas)
            = 0;


        };

        class caption : public item
        {
        public:
            // constructors and destructor

            explicit caption(const side_bar& side_bar_)
            :
            item(position_type(left_type(0), top_type(0)), dimension_type(width_type(0), height_type(0))),
            m_side_bar(side_bar_),
            m_dimension(),
            m_text_position()
            {}

            virtual ~caption()
            TETENGO2_CPP11_NOEXCEPT
            {}


        private:
            // static functions

            static const dimension_type& state_button_dimension()
            {
                static const dimension_type singleton(width_type(1), height_type(1));
                return singleton;
            }


            // variables

            const side_bar& m_side_bar;

            boost::optional<dimension_type> m_dimension;

            boost::optional<position_type> m_text_position;


            // virtual functions

            virtual void resized_impl()
            override
            {
                m_dimension = boost::none;
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

                //draw_state_button(canvas, padding);

                canvas.draw_text(m_side_bar.text(), *m_text_position);

                canvas.set_background(std::move(original_background));
                canvas.set_color(std::move(original_color));
            }


            // functions

            void calculate_position_and_dimension(const canvas_type& canvas)
            {
                if (m_dimension && m_text_position)
                    return;

                static const auto padding = height_type(1) / 4;
                const auto text_dimension = canvas.calc_text_dimension(m_side_bar.text());

                m_dimension = boost::make_optional(calculate_dimension(padding, text_dimension));
                this->set_position_and_dimension(position_type(left_type(0), top_type(0)), *m_dimension);

                m_text_position = boost::make_optional(text_position(padding, text_dimension));
            }

            dimension_type calculate_dimension(const height_type& padding, const dimension_type& text_dimension)
            const
            {
                const dimension_type client_dimension = m_side_bar.client_dimension();

                const auto& width = gui::dimension<dimension_type>::width(client_dimension);

                const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);
                const auto& status_button_height = gui::dimension<dimension_type>::height(state_button_dimension());
                const auto& height = std::max(text_height, status_button_height); 
            
                return dimension_type(width, height + padding * 2);
            }

            position_type text_position(const height_type& padding, const dimension_type& text_dimension)
            {
                auto left =
                    left_type::from(gui::dimension<dimension_type>::width(state_button_dimension()) + padding * 2);

                const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);
                const auto& status_button_height = gui::dimension<dimension_type>::height(state_button_dimension());
                auto top =
                    text_height < status_button_height ?
                    top_type::from((status_button_height - text_height) / 2) + top_type::from(padding) :
                    top_type::from(padding);
            
                return position_type(std::move(left), std::move(top));
            }


        };


        // static functions

        static void initialize_side_bar(side_bar* const p_side_bar)
        {
            p_side_bar->set_background(
                make_unique<solid_background_type>(system_color_set_type::dialog_background())
            );

            p_side_bar->m_p_items.push_back(make_unique<caption>(*p_side_bar));

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

        //static void draw_caption(const side_bar& side_bar, canvas_type& canvas)
        //{
        //    auto original_color = canvas.color();
        //    auto original_background = canvas.background().clone();
        //    canvas.set_color(system_color_set_type::title_bar_text());
        //    canvas.set_background(make_unique<solid_background_type>(system_color_set_type::title_bar_background()));

        //    static const height_type padding = height_type(1) / 4;

        //    const auto text_dimension = canvas.calc_text_dimension(side_bar.text());
        //    const auto& client_dimension = side_bar.client_dimension();
        //    canvas.fill_rectangle(
        //        position_type(left_type(0), top_type(0)), caption_dimension(client_dimension, text_dimension, padding)
        //    );

        //    draw_state_button(canvas, padding);

        //    canvas.draw_text(side_bar.text(), text_position(text_dimension, padding));

        //    canvas.set_background(std::move(original_background));
        //    canvas.set_color(std::move(original_color));
        //}

        //static void draw_state_button(canvas_type& canvas, const height_type& padding)
        //{
        //    auto original_color = canvas.color();
        //    auto original_line_width = canvas.line_width();
        //    auto original_background = canvas.background().clone();
        //    canvas.set_color(color_type(0, 0, 0));
        //    canvas.set_line_width(size_type(1) / 16);
        //    canvas.set_background(make_unique<solid_background_type>(color_type(255, 255, 255)));

        //    static const auto& width = gui::dimension<dimension_type>::width(state_button_dimension());
        //    static const auto& height = gui::dimension<dimension_type>::height(state_button_dimension());
        //    std::vector<position_type> positions;
        //    positions.emplace_back(left_type::from(padding), top_type::from(padding));
        //    positions.emplace_back(left_type::from(padding + width), top_type::from(padding + height / 2));
        //    positions.emplace_back(left_type::from(padding), top_type::from(padding + height));

        //    canvas.fill_polygon(positions.begin(), positions.end());
        //    canvas.draw_polygon(positions.begin(), positions.end());

        //    canvas.set_background(std::move(original_background));
        //    canvas.set_line_width(std::move(original_line_width));
        //    canvas.set_color(std::move(original_color));
        //}

        //static position_type text_position(const dimension_type& text_dimension, const height_type& padding)
        //{
        //    left_type left =
        //        left_type::from(gui::dimension<dimension_type>::width(state_button_dimension()) + padding * 2);

        //    const auto& text_height = gui::dimension<dimension_type>::height(text_dimension);
        //    const auto& status_button_height = gui::dimension<dimension_type>::height(state_button_dimension());
        //    top_type top =
        //        text_height < status_button_height ?
        //        top_type::from((status_button_height - text_height) / 2) + top_type::from(padding) :
        //        top_type::from(padding);
        //    
        //    return position_type(std::move(left), std::move(top));
        //}


        // variables

        std::vector<std::unique_ptr<item>> m_p_items;


    };


}}}


#endif
