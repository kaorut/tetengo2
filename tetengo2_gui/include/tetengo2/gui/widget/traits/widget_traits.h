/*! \file
    \brief The definition of tetengo2::gui::widget::traits::widget_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_WIDGETTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_WIDGETTRAITS_H

#include <tetengo2/gui/alert.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/canvas_traits.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/message/focus_observer_set.h>
#include <tetengo2/gui/message/keyboard_observer_set.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/message/scroll_bar_observer_set.h>
#include <tetengo2/gui/message/size_observer_set.h>
#include <tetengo2/gui/scroll_bar.h>
#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/virtual_key.h>


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a GUI widget.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam Position          A position type.
        \tparam Dimension         A dimension type.
        \tparam Path              A paht type.
        \tparam Encoder           An encoder type.
        \tparam ExceptionEncoder  An exception encoder type.
        \tparam DrawingDetails    A drawing details type.
        \tparam IconDetails       An icon details type.
        \tparam AlertDetails      An alert details type.
        \tparam CursorDetails     A cursor details type.
        \tparam ScrollDetails     A scroll details type.
        \tparam VirtualKeyDetails A virtual key details type.
   */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename Position,
        typename Dimension,
        typename Path,
        typename Encoder,
        typename ExceptionEncoder,
        typename DrawingDetails,
        typename IconDetails,
        typename AlertDetails,
        typename CursorDetails,
        typename ScrollDetails,
        typename VirtualKeyDetails
    >
    struct widget_traits
    {
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The position type.
        using position_type = Position;

        //! The dimension type.
        using dimension_type = Dimension;

        //! The path type.
        using path_type = Path;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The exception encoder type.
        using exception_encoder_type = ExceptionEncoder;

        //! The drawing details type.
        using drawing_details_type = DrawingDetails;

        //! The color type.
        using color_type = gui::drawing::color<unsigned char>;

        //! The background type.
        using background_type = gui::drawing::background<drawing_details_type>;

        //! The solid background type.
        using solid_background_type = gui::drawing::solid_background<color_type, drawing_details_type>;

        //! The font type.
        using font_type = gui::drawing::font<string_type, size_type, drawing_details_type>;

        //! The picture type.
        using picture_type = gui::drawing::picture<dimension_type, drawing_details_type>;

        //! The icon details type.
        using icon_details_type = IconDetails;

        //! The icon type.
        using icon_type = gui::icon<path_type, dimension_type, icon_details_type>;

        //! The canvas traits type.
        using canvas_traits_type =
            gui::drawing::canvas_traits<
                size_type,
                string_type,
                position_type,
                dimension_type,
                encoder_type,
                color_type,
                background_type,
                solid_background_type,
                font_type,
                picture_type,
                icon_type
            >;

        //! The canvas type.
        using canvas_type = gui::drawing::canvas<canvas_traits_type, drawing_details_type>;

        //! The widget canvas type.
        using widget_canvas_type = gui::drawing::widget_canvas<canvas_traits_type, drawing_details_type>;

        //! The alert details type.
        using alert_details_type = AlertDetails;

        //! The alert type.
        using alert_type = gui::alert<encoder_type, exception_encoder_type, alert_details_type>;

        //! The cursor details type.
        using cursor_details_type = CursorDetails;

        //! The system cursor type.
        using system_cursor_type = gui::cursor::system<cursor_details_type>;

        //! The scroll bar observer set type.
        using scroll_bar_observer_set_type = gui::message::scroll_bar_observer_set<size_type>;

        //! The scroll details type.
        using scroll_details_type = ScrollDetails;

        //! The scroll bar type.
        using scroll_bar_type = gui::scroll_bar<size_type, scroll_bar_observer_set_type, scroll_details_type>;

        //! The size observer set type.
        using size_observer_set_type = gui::message::size_observer_set;

        //! The focus observer set type.
        using focus_observer_set_type = gui::message::focus_observer_set;

        //! The paint observer set type.
        using paint_observer_set_type = gui::message::paint_observer_set<canvas_type>;

        //! The virtual key details type;
        using virtual_key_details_type = VirtualKeyDetails;

        //! The virtual key type.
        using virtual_key_type = gui::virtual_key<string_type, virtual_key_details_type>;

        //! The keyboard observer set type.
        using keyboard_observer_set_type =
            gui::message::keyboard_observer_set<virtual_key_type, typename string_type::value_type>;

        //! The mouse observer set type.
        using mouse_observer_set_type = gui::message::mouse_observer_set<position_type, difference_type>;


    };


}}}}


#endif
