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

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a control.

        \tparam Traits        A traits type.
        \tparam DetailsTraits A detail implementation type traits.
    */
    template <typename Traits, typename DetailsTraits>
    class control : public widget<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The detail implementation type of a widget.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The drawing details type.
        using drawing_details_type = typename details_traits_type::drawing_details_type;

        //! The icon details type.
        using icon_details_type = typename details_traits_type::icon_details_type;

        //! The alert details type.
        using alert_details_type = typename details_traits_type::alert_details_type;

        //! The cursor details type.
        using cursor_details_type = typename details_traits_type::cursor_details_type;

        //! The scroll details type.
        using scroll_details_type = typename details_traits_type::scroll_details_type;

        //! The message handler details type.
        using message_handler_details_type = typename details_traits_type::message_handler_details_type;

        //! The virtual key details type.
        using virtual_key_details_type = typename details_traits_type::virtual_key_details_type;

        //! The base type.
        using base_type = widget<traits_type, details_traits_type>;

        //! The widget canvas type.
        using widget_canvas_type = typename base_type::widget_canvas_type;

        //! The canvas type.
        using canvas_type = typename base_type::canvas_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The mouse observer set type.
        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        //! The keyboard observer set type.
        using keyboard_observer_set_type = typename base_type::keyboard_observer_set_type;

        //! The scroll bar type.
        using scroll_bar_type = typename base_type::scroll_bar_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        //! The color type.
        using color_type = gui::drawing::color;

        //! The detail implementation type.
        using details_type = typename widget_details_type::widget_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename widget_details_type::widget_details_ptr_type;


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
        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


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
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


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
