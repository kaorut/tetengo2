/*! \file
    \brief The definition of tetengo2::gui::widget::text_box.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TEXTBOX_H)
#define TETENGO2_GUI_WIDGET_TEXTBOX_H

#include <memory>

#include <tetengo2/gui/message/text_box_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a text box.
    */
    class text_box : public control
    {
    public:
        // types

        //! The text box observer set type.
        using text_box_observer_set_type = gui::message::text_box_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a text box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        text_box(widget& parent, scroll_bar_style_type scroll_bar_style);

        /*!
            \brief Destroys the text box.
        */
        virtual ~text_box() noexcept;


        // functions

        /*!
            \brief Checks whether the text box is read-only.

            \retval true  When the text box is read-only.
            \retval false Otherwise.
        */
        bool read_only() const;

        /*!
            \brief Sets a read-only status.

            \param read_only A read-only status.
        */
        void set_read_only(bool read_only);

        /*!
            \brief Returns the text box observer set.

            \return The text box observer set.
        */
        const text_box_observer_set_type& text_box_observer_set() const;

        /*!
            \brief Returns the text box observer set.

            \return The text box observer set.
        */
        text_box_observer_set_type& text_box_observer_set();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
