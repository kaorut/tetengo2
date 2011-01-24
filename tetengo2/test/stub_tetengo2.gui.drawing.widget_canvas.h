/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::widget_canvas.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_WIDGETCANVAS_H)
#define STUBTETENGO2_GUI_DRAWING_WIDGETCANVAS_H

#include "stub_tetengo2.gui.drawing.canvas.h"


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <
        typename Handle,
        typename Size,
        typename String,
        typename Dimension,
        typename Encoder,
        typename Background,
        typename Font,
        typename Picture
    >
    class widget_canvas :
        public canvas<
            Handle,
            Size,
            String,
            Dimension,
            Encoder,
            Background,
            Font,
            Picture
        >
    {
    public:
        // types

        typedef
            canvas<
                Handle,
                Size,
                String,
                Dimension,
                Encoder,
                Background,
                Font,
                Picture
            >
            base_type;


        // constructors and destructor

        template <typename DeviceHandle>
        widget_canvas(const DeviceHandle device_handle)
        :
        base_type(device_handle)
        {}


    };


}}}


#endif
