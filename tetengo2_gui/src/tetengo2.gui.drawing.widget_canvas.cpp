/*! \file
    \brief The definition of tetengo2::gui::drawing::widget_canvas.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cstdint>

#include <tetengo2/gui/drawing/widget_canvas.h>


namespace tetengo2::gui::drawing {
    widget_canvas::widget_canvas(const drawing_details_type& drawing_details, const widget_details_type& widget_details)
    : base_type{ drawing_details, drawing_details.create_canvas(widget_details) }
    {}

    widget_canvas::widget_canvas(const drawing_details_type& drawing_details, const std::intptr_t handle)
    : base_type{ drawing_details, drawing_details.create_canvas(handle) }
    {}

    widget_canvas::~widget_canvas() = default;
}
