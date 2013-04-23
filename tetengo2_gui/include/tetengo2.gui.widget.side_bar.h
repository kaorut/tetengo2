/*! \file
    \brief The definition of tetengo2::gui::widget::side_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_SIDEBAR_H)
#define TETENGO2_GUI_WIDGET_SIDEBAR_H

#include <algorithm>
#include <memory>

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

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;


        // constructors and destructor

        /*!
            \brief Creates a side bar.

            \param parent A parent widget.
        */
        explicit side_bar(widget_type& parent)
        :
        base_type(parent, base_type::scroll_bar_style_type::none)
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

        typedef typename canvas_type::font_type font_type;

        typedef typename gui::position<position_type>::left_type left_type;

        typedef typename gui::position<position_type>::top_type top_type;

        typedef typename gui::dimension<dimension_type>::width_type width_type;

        typedef typename gui::dimension<dimension_type>::height_type height_type;


        // static functions

        static void initialize_side_bar(side_bar* const p_side_bar)
        {
            p_side_bar->set_background(
                make_unique<solid_background_type>(system_color_set_type::dialog_background())
            );

            p_side_bar->paint_observer_set().paint_background().disconnect_all_slots();
            p_side_bar->paint_observer_set().paint_background().connect(
                [p_side_bar](canvas_type& canvas) { return paint_background(*p_side_bar, canvas); }
            );
            p_side_bar->paint_observer_set().paint().connect(
                [p_side_bar](canvas_type& canvas) { draw_caption(*p_side_bar, canvas); }
            );
        }

        static const dimension_type& state_button_dimension()
        {
            static const dimension_type singleton(width_type(3), height_type(3));
            return singleton;
        }

        static bool paint_background(const side_bar& side_bar, canvas_type& canvas)
        {
            if (!side_bar.background())
                return false;

            canvas.set_background(side_bar.background()->clone());
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), side_bar.client_dimension());

            return true;
        }

        static void draw_caption(const side_bar& side_bar, canvas_type& canvas)
        {
            auto original_color = canvas.color();
            auto original_background = canvas.background().clone();
            canvas.set_color(system_color_set_type::title_bar_text());
            canvas.set_background(make_unique<solid_background_type>(system_color_set_type::title_bar_background()));

            static const height_type padding = height_type(1) / 4;

            const auto text_dimension = canvas.calc_text_dimension(side_bar.text());
            const auto& client_dimension = side_bar.client_dimension();
            canvas.fill_rectangle(
                position_type(left_type(0), top_type(0)), caption_dimension(client_dimension, text_dimension, padding)
            );

            canvas.draw_text(side_bar.text(), position_type(left_type::from(padding), top_type::from(padding)));

            canvas.set_background(std::move(original_background));
            canvas.set_color(std::move(original_color));
        }

        static dimension_type caption_dimension(
            const dimension_type& client_dimension,
            const dimension_type& text_dimension,
            const height_type&    padding
        )
        {

            const height_type& height =
                std::max(
                    gui::dimension<dimension_type>::height(text_dimension),
                    gui::dimension<dimension_type>::height(state_button_dimension())
                ); 
            return
                dimension_type(
                    gui::dimension<dimension_type>::width(client_dimension),
                    height + padding * 2
                );
        }


    };


}}}


#endif
