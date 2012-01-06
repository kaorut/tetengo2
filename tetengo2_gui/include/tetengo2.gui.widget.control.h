/*! \file
    \brief The definition of tetengo2::gui::widget::control.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_CONTROL_H)
#define TETENGO2_GUI_WIDGET_CONTROL_H

//#include <utility>

//#include <boost/optional.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.widget.widget.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a control.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a
                                      widget.
        \tparam MessageHandlerDetails A detail implementation type of a
                                      message handler.
   */
    template <
        typename Traits,
        typename WidgetDetails,
        typename MessageHandlerDetails
    >
    class control :
        public widget<
            typename Traits::base_type, WidgetDetails, MessageHandlerDetails
        >
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
            widget<
                typename traits_type::base_type,
                widget_details_type,
                message_handler_details_type
            >
            base_type;

        //! The color type.
        typedef typename traits_type::color_type color_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


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

            \tparam C A color type.

            \param text_color A text color.
        */
        template <typename C /* = boost::optional<color_type> */>
        void set_text_color(
            C&& text_color /* = boost::none */
        )
        {
            m_text_color = std::forward<C>(text_color);
        }

#if !defined(DOCUMENTATION)
        void set_text_color()
        {
            m_text_color = boost::none;
        }
#endif


    protected:
        // types

        //! The message handler map type.
        typedef
            typename message_handler_details_type::message_handler_map_type
            message_handler_map_type;


        // constructors and destructor

        /*!
            \brief Creates a control.

            \param message_handler_map A message handler map.
            \param p_details           A unique pointer to a detail
                                       implementation.
        */
        control(
            message_handler_map_type&& message_handler_map,
            details_ptr_type           p_details
        )
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            message_handler_details_type::make_control_message_handler_map(
                *this,
                std::forward<message_handler_map_type>(message_handler_map)
            )
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_p_details(std::move(p_details)),
        m_text_color()
        {}

        /*!
            \brief Destroys the control.
        */
        virtual ~control()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // variables

        const details_ptr_type m_p_details;

        boost::optional<color_type> m_text_color;


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