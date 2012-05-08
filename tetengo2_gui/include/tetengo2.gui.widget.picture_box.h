/*! \file
    \brief The definition of tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PICTUREBOX_H)
#define TETENGO2_GUI_WIDGET_PICTUREBOX_H

#include "tetengo2.gui.widget.control.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a picture box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class picture_box : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The fast draw widget canvas type.
        typedef typename Traits::fast_draw_widget_canvas_type fast_draw_widget_canvas_type;

        //! The fast draw canvas type.
        typedef typename Traits::fast_draw_canvas_type fast_draw_canvas_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef control<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename widget_details_type::widget_details_ptr_type details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a picture box.

            \param parent A parent widget.
        */
        explicit picture_box(widget_type& parent)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            message_handler_details_type::make_picture_box_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_picture_box(parent)
        )
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        {
            initialize(this);
        }

        /*!
            \brief Destroys the picture box.
        */
        virtual ~picture_box()
        {}


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


    };


}}}


#endif
