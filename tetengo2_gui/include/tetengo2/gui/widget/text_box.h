/*! \file
    \brief The definition of tetengo2::gui::widget::text_box.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TEXTBOX_H)
#define TETENGO2_GUI_WIDGET_TEXTBOX_H

#include <boost/predef.h>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/widget/control.h>
#include "tetengo2.stdalt.h"


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
        using traits_type = Traits;

        //! The text box observer set type.
        using text_box_observer_set_type = typename traits_type::text_box_observer_set_type;

        //! The detail implementation type of a widget.
        using widget_details_type = WidgetDetails;

        //! The detail implementation type of a message handler.
        using message_handler_details_type = MessageHandlerDetails;

        //! The base type.
        using base_type = control<typename traits_type::base_type, widget_details_type, message_handler_details_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The detail implementation type.
        using details_type = typename widget_details_type::widget_details_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;


        // constructors and destructor

        /*!
            \brief Creates a text box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        text_box(widget_type& parent, const scroll_bar_style_type scroll_bar_style)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_text_box_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_text_box(parent, scroll_bar_style)
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_text_box_observer_set()
        {
            this->initialize(this);
        }

        /*!
            \brief Destroys the text box.
        */
        virtual ~text_box()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION


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

        /*!
            \brief Returns the text box observer set.

            \return The text box observer set.
        */
        const text_box_observer_set_type& text_box_observer_set()
        const
        {
            return m_text_box_observer_set;
        }

        /*!
            \brief Returns the text box observer set.

            \return The text box observer set.
        */
        text_box_observer_set_type& text_box_observer_set()
        {
            return m_text_box_observer_set;
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        text_box_observer_set_type m_text_box_observer_set;


    };


}}}


#endif
