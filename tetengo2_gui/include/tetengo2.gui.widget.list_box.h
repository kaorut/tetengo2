/*! \file
    \brief The definition of tetengo2::gui::widget::list_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LISTBOX_H)
#define TETENGO2_GUI_WIDGET_LISTBOX_H

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.control.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a list box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class list_box : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
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

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename widget_details_type::widget_details_ptr_type details_ptr_type;

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;


        // constructors and destructor

        /*!
            \brief Creates a list box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        list_box(widget_type& parent, const typename scroll_bar_style_type::enum_t scroll_bar_style)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_text_box_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_list_box(parent, scroll_bar_style)
        )
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        {
            initialize(this);
        }

        /*!
            \brief Destroys the list box.
        */
        virtual ~list_box()
        {}


        // functions

        /*!
            \brief Appends an item.

            \param text A text.
        */
        void append_item(const string_type& text)
        {
            widget_details_type::append_list_box_item(*this, text);
        }


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


    };


}}}


#endif
