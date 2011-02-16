/*! \file
    \brief The definition of tetengo2::gui::drawing::widget_canvas.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIDGETCANVAS_H)
#define TETENGO2_GUI_DRAWING_WIDGETCANVAS_H

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.drawing.canvas.h"


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a widget canvas for Win32 platforms.

        \tparam Size           A size type.
        \tparam String         A string type.
        \tparam Dimension      A dimension type.
        \tparam Encoder        An encoder type.
        \tparam Background     A background type.
        \tparam Font           A font type.
        \tparam Picture        A picture type.
        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <
        typename Size,
        typename String,
        typename Dimension,
        typename Encoder,
        typename Background,
        typename Font,
        typename Picture,
        typename DrawingDetails
    >
    class widget_canvas :
        public canvas<
            Size,
            String,
            Dimension,
            Encoder,
            Background,
            Font,
            Picture,
            DrawingDetails
        >
    {
    public:
        // types

        //! The base type.
        typedef
            canvas<
                Size,
                String,
                Dimension,
                Encoder,
                Background,
                Font,
                Picture,
                DrawingDetails
            >
            base_type;


        // constructors and destructor

        /*!
            \brief Creates a widget canvas.
            
            \tparam DeviceContext A device context handle type.

            \param device_context A device context handle.
        */
        template <typename DeviceContext>
        explicit widget_canvas(const DeviceContext device_context)
        :
        base_type(
            base_type::drawing_details_type::create_canvas(device_context)
        )
        {}

        /*!
            \brief Destroys the widget canvas.
        */
        virtual ~widget_canvas()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    };


}}}


#endif
