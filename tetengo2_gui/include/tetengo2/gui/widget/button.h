/*! \file
    \brief The definition of tetengo2::gui::widget::button.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_BUTTON_H)
#define TETENGO2_GUI_WIDGET_BUTTON_H

#include <memory>

#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a button.
    */
    class button : public control
    {
    public:
        // types

        //! The style type.
        enum class style_type
        {
            normal, //!< A normal button.
            default_, //!< A default button.
            cancel //!< A cancel button.
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
        explicit button(widget& parent, style_type style = style_type::normal);

        /*!
            \brief Destroys the button.
        */
        virtual ~button() noexcept;


        // functions

        /*!
            \brief Returns the style.

            \return The style.
        */
        style_type style() const;


    private:
        // types

        class impl;

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
