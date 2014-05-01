/*! \file
    \brief The definition of tetengo2::gui::widget::control.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_CONTROL_H)
#define TETENGO2_GUI_WIDGET_CONTROL_H

#include <cassert>
#include <utility>

#include <boost/optional.hpp>
#include <boost/predef.h>

#include "tetengo2.gui.widget.widget.h"
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a control.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class control : public widget<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
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
        typedef widget<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The widget canvas type.
        typedef typename base_type::widget_canvas_type widget_canvas_type;

        //! The canvas type.
        typedef typename base_type::canvas_type canvas_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The mouse observer set type.
        typedef typename base_type::mouse_observer_set_type mouse_observer_set_type;

        //! The keyboard observer set type.
        typedef typename base_type::keyboard_observer_set_type keyboard_observer_set_type;

        //! The scroll bar type.
        typedef typename base_type::scroll_bar_type scroll_bar_type;

        //! The scroll bar style type.
        typedef typename base_type::scroll_bar_style_type scroll_bar_style_type;

        //! The color type.
        typedef typename traits_type::color_type color_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename widget_details_type::widget_details_ptr_type details_ptr_type;


        // functions

        /*!
            \brief Returns the text color.

            \return The text color.
        */
        const boost::optional<color_type>& text_color()
        const
        {
            return m_text_color;
        }

        /*!
            \brief Sets a text color.

            \param text_color A text color.
        */
        void set_text_color(boost::optional<color_type> text_color = boost::none)
        {
            m_text_color = std::move(text_color);
        }

        /*!
            \brief Checks whether the control accepts a focus.

            \retval true  When the control accepts a focus.
            \retval false Otherwise.
        */
        bool focusable()
        const
        {
            return widget_details_type::focusable(*this);
        }

        /*!
            \brief Sets whether the control accepts a focus.

            \param focusable True when the control accepts a focus.
        */
        void set_focusable(const bool focusable)
        {
            widget_details_type::set_focusable(*this, focusable);
        }


    protected:
        // types

        //! The message handler map type.
        typedef
            typename message_handler_details_type::message_handler_map_type
            message_handler_map_type;


        // constructors and destructor

        /*!
            \brief Creates a control.

            \param scroll_bar_style    A scroll bar style.
            \param message_handler_map A message handler map.
            \param p_details           A unique pointer to a detail implementation.
        */
        control(
            const scroll_bar_style_type scroll_bar_style,
            message_handler_map_type&&                   message_handler_map,
            details_ptr_type                             p_details
        )
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_control_message_handler_map(*this, std::move(message_handler_map))
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_p_details(std::move(p_details)),
        m_text_color()
        {}

        /*!
            \brief Destroys the control.
        */
        virtual ~control()
        = default;


    private:
        // variables

        const details_ptr_type m_p_details;

        boost::optional<color_type> m_text_color;


        // virtual functions

        virtual const details_type& details_impl()
        const override
        {
            assert(m_p_details);
            return *m_p_details;
        }

        virtual details_type& details_impl()
        override
        {
            assert(m_p_details);
            return *m_p_details;
        }


    };


}}}


#endif
