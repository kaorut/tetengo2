/*! \file
    \brief The definition of tetengo2::gui::widget::button.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_BUTTON_H)
#define TETENGO2_GUI_WIDGET_BUTTON_H

#include <stdexcept>

#include <boost/predef.h>

#include <tetengo2/gui/widget/control.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a button.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class button : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

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

        //! The style type.
        enum class style_type
        {
            normal,   //!< A normal button.
            default_, //!< A default button.
            cancel    //!< A cancel button.
        };


        // constructors and destructor

        /*!
            \brief Creates a button.

            The window cannot have plural buttons with style_type::default_. And so is style_type::cancel.
            When creating a second button with style_type::default_ or style_type::cancel, std::runtime_error is
            thrown.

            \param parent A parent widget.
            \param style  A style.
        */
        explicit button(widget_type& parent, const style_type style = style_type::normal)
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            message_handler_details_type::make_button_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_button(parent, style == style_type::default_, style == style_type::cancel)
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_style(style)
        {
            this->initialize(this);
        }

        /*!
            \brief Destroys the button.
        */
        virtual ~button()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Returns the style.

            \return The style.
        */
        style_type style()
        const
        {
            return m_style;
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        const style_type m_style;


    };


}}}


#endif
