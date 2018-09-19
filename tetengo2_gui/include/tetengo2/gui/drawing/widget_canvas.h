/*! \file
    \brief The definition of tetengo2::gui::drawing::widget_canvas.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIDGETCANVAS_H)
#define TETENGO2_GUI_DRAWING_WIDGETCANVAS_H

#include <cstdint>

#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/drawing/canvas.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a widget canvas.
    */
    class widget_canvas : public canvas
    {
    public:
        // types

        //! The base type.
        using base_type = canvas;

        //! The drawing details type.
        using drawing_details_type = base_type::drawing_details_type;

        //! The widget details type.
        using widget_details_type = detail::base::widget::widget_details_type;


        // constructors and destructor

        /*!
            \brief Creates a widget canvas.

            \param drawing_details A detail implementation of a drawing.
            \param widget_details  A detail implementation of a widget.
        */
        widget_canvas(const drawing_details_type& drawing_details, const widget_details_type& widget_details);

        /*!
            \brief Creates a widget canvas.

            \param drawing_details A detail implementation of a drawing.
            \param handle          A handle.
        */
        widget_canvas(const drawing_details_type& drawing_details, std::intptr_t handle);

        /*!
            \brief Destroys the widget canvas.
        */
        virtual ~widget_canvas();
    };
}


#endif
