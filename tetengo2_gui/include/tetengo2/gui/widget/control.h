/*! \file
    \brief The definition of tetengo2::gui::widget::control.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_CONTROL_H)
#define TETENGO2_GUI_WIDGET_CONTROL_H

#include <memory>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a control.
    */
    class control : public widget
    {
    public:
        // types

        //! The color type.
        using color_type = gui::drawing::color;


        // constructors and destructor

        /*!
            \brief Destroys the control.
        */
        virtual ~control();


        // functions

        /*!
            \brief Returns the text color.

            \return The text color.
        */
        const tetengo2::stdalt::optional<color_type>& text_color() const;

        /*!
            \brief Sets a text color.

            \param text_color A text color.
        */
        void set_text_color(tetengo2::stdalt::optional<color_type> text_color = TETENGO2_STDALT_NULLOPT);

        /*!
            \brief Checks whether the control accepts a focus.

            \retval true  When the control accepts a focus.
            \retval false Otherwise.
        */
        bool focusable() const;

        /*!
            \brief Sets whether the control accepts a focus.

            \param focusable True when the control accepts a focus.
        */
        void set_focusable(const bool focusable);


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
            const scroll_bar_style_type                           scroll_bar_style,
            message_handler_map_type&&                            message_handler_map,
            typename widget_details_type::widget_details_ptr_type p_details);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const details_type& details_impl() const override;

        virtual details_type& details_impl() override;
    };
}


#endif
