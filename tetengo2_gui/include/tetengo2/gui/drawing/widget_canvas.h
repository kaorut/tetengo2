/*! \file
    \brief The definition of tetengo2::gui::drawing::widget_canvas.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIDGETCANVAS_H)
#define TETENGO2_GUI_DRAWING_WIDGETCANVAS_H

#include <tetengo2/gui/drawing/canvas.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class template for a widget canvas.

        \tparam Traits         A traits type.
        \tparam DrawingDetails A detail implementation type of a drawing.
        \tparam IconDetails    An icon details type.
    */
    template <typename Traits, typename DrawingDetails, typename IconDetails>
    class widget_canvas : public canvas<Traits, DrawingDetails, IconDetails>
    {
    public:
        // types

        //! The base type.
        using base_type = canvas<Traits, DrawingDetails, IconDetails>;


        // constructors and destructor

        /*!
            \brief Creates a widget canvas.

            \tparam HandleOrWidgetDetails A handle type or a widget details type.

            \param handle_or_widget_details A handle or a widget details.
        */
        template <typename HandleOrWidgetDetails>
        explicit widget_canvas(const HandleOrWidgetDetails& handle_or_widget_details)
        : base_type{ base_type::drawing_details_type::create_canvas(handle_or_widget_details) }
        {}

        /*!
            \brief Destroys the widget canvas.
        */
        virtual ~widget_canvas() = default;
    };
}


#endif
