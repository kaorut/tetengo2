/*! \file
    \brief The definition of tetengo2::gui::widget::text_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TEXTBOX_H)
#define TETENGO2_GUI_WIDGET_TEXTBOX_H

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.control.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a text box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class text_box : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

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

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;


        // constructors and destructor

        /*!
            \brief Creates a text box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        text_box(widget_type& parent, const scroll_bar_style_type scroll_bar_style)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_text_box_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_text_box(parent, scroll_bar_style)
        )
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        {
            initialize(this);
        }

        /*!
            \brief Destroys the text box.
        */
        virtual ~text_box()
        {}


        // functions

        /*!
            \brief Checks whether the text box is read-only.

            \retval true  When the text box is read-only.
            \retval false Otherwise.
        */
        bool read_only()
        const
        {
            return widget_details_type::read_only(*this);
        }

        /*!
            \brief Sets a read-only status.

            \param read_only A read-only status.
        */
        void set_read_only(const bool read_only)
        {
            widget_details_type::set_read_only(*this, read_only);
        }


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


    };


}}}


#endif
