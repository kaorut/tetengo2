/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::widget_canvas.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_WIDGETCANVAS_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_WIDGETCANVAS_H

#include "tetengo2.gui.drawing.win32.gdiplus.canvas.h"


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a widget canvas for Win32 platforms.

        \tparam Handle  A handle type for the native interface.
        \tparam Size    A size type.
        \tparam String  A string type.
        \tparam Encoder An encoder type.
        \tparam Font    A font type.
        \tparam Picture A picture type.
    */
    template <
        typename Handle,
        typename Size,
        typename String,
        typename Encoder,
        typename Font,
        typename Picture
    >
    class widget_canvas :
        public canvas<Handle, Size, String, Encoder, Font, Picture>
    {
    public:
        // types

        //! The base type.
        typedef
            canvas<Handle, Size, String, Encoder, Font, Picture> base_type;


        // constructors and destructor

        /*!
            \brief Creates a widget canvas.
            
            \tparam DeviceHandle A device handle type.

            \param device_handle A device handle.
        */
        template <typename DeviceHandle>
        widget_canvas(const DeviceHandle device_handle)
        :
        base_type(device_handle)
        {}


    };


}}}}}


#endif
