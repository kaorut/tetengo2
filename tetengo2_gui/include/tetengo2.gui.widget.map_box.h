/*! \file
    \brief The definition of tetengo2::gui::widget::map_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_MAPBOX_H)
#define TETENGO2_GUI_WIDGET_MAPBOX_H

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.custom_control.h"
#include "tetengo2.stdalt.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a map box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class map_box : public custom_control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
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

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;


        // constructors and destructor

        /*!
            \brief Creates a map box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        map_box(widget_type& parent, const scroll_bar_style_type scroll_bar_style)
        :
        base_type(parent, scroll_bar_style)
        {
            initialize_map_box(this);
        }

        /*!
            \brief Destroys the map box.
        */
        virtual ~map_box()
        TETENGO2_STDALT_NOEXCEPT
        {}


    private:
        // types

        typedef typename base_type::canvas_type canvas_type;

        typedef typename base_type::position_type position_type;

        typedef typename gui::position<position_type>::left_type left_type;

        typedef typename gui::position<position_type>::top_type top_type;


        // static functions

        static void initialize_map_box(map_box* const p_map_box)
        {
            p_map_box->set_background(
                stdalt::make_unique<solid_background_type>(system_color_set_type::hyperlink_text())
            );

            p_map_box->paint_observer_set().paint_background().disconnect_all_slots();
            p_map_box->paint_observer_set().paint_background().connect(
                [p_map_box](canvas_type& canvas) { return paint_background(*p_map_box, canvas); }
            );
        }

        static bool paint_background(const map_box& map_box, canvas_type& canvas)
        {
            if (!map_box.background())
                return false;

            canvas.set_background(map_box.background()->clone());
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), map_box.client_dimension());

            return true;
        }


    };


}}}


#endif
