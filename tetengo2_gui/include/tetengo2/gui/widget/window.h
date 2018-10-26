/*! \file
    \brief The definition of tetengo2::gui::widget::window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WINDOW_H)
#define TETENGO2_GUI_WIDGET_WINDOW_H

#include <memory>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a window.
    */
    class window : public abstract_window
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a top level window.

            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.
        */
        explicit window(
            scroll_bar_style_type scroll_bar_style = abstract_window::scroll_bar_style_type::none,
            bool                  file_droppable = false);

        /*!
            \brief Creates a owned window.

            \param parent           A parent window.
            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.
        */
        window(abstract_window& parent, scroll_bar_style_type scroll_bar_style, bool file_droppable);

        /*!
            \brief Destroys the window.
        */
        virtual ~window() noexcept;


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
