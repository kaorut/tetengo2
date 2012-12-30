/*! \file
    \brief The definition of tetengo2::gui::widget::window.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WINDOW_H)
#define TETENGO2_GUI_WIDGET_WINDOW_H

//#include <boost/optional.hpp>

#include "tetengo2.gui.widget.abstract_window.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a window.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class window : public abstract_window<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
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
        typedef
            abstract_window<typename traits_type::base_type, widget_details_type, message_handler_details_type>
            base_type;

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
            \brief Creates a top level window.

            \param scroll_bar_style A scroll bar style.
        */
        explicit window(
            const typename scroll_bar_style_type::enum_t scroll_bar_style = base_type::scroll_bar_style_type::none
        )
        :
        base_type(scroll_bar_style, message_handler_map_type()),
        m_p_details(
            widget_details_type::template create_window<typename base_type::base_type>(boost::none, scroll_bar_style)
        )
        {
            initialize(this);
        }

        /*!
            \brief Creates a owned window.

            \param parent           A parent window.
            \param scroll_bar_style A scroll bar style.
        */
        window(base_type& parent, const typename scroll_bar_style_type::enum_t scroll_bar_style)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_window_message_handler_map(*this, message_handler_map_type())
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_p_details(
            widget_details_type::template create_window<typename base_type::base_type>(parent, scroll_bar_style)
        )
        {
            initialize(this);
        }

        /*!
            \brief Destroys the window.
        */
        virtual ~window()
        {}


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


        // variables

        const details_ptr_type m_p_details;


        // virtual functions

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return boost::make_optional<const details_type&>(*m_p_details);
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return boost::make_optional<details_type&>(*m_p_details);
        }


    };


}}}


#endif
