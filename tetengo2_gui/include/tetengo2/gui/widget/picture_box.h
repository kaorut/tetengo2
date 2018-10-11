/*! \file
    \brief The definition of tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PICTUREBOX_H)
#define TETENGO2_GUI_WIDGET_PICTUREBOX_H

#include <memory>

#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a picture box.
    */
    class picture_box : public control
    {
    public:
        // types

        //! The fast canvas type.
        using fast_canvas_type = gui::drawing::canvas;

        //! The fast paint observer set type.
        using fast_paint_observer_set_type = gui::message::paint_observer_set;


        // constructors and destructor

        /*!
            \brief Creates a picture box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        picture_box(widget& parent, scroll_bar_style_type scroll_bar_style);

        /*!
            \brief Destroys the picture box.
        */
        virtual ~picture_box() noexcept;


        // functions

        /*!
            \brief Creates a fast canvas.

            \return The unique pointer to a fast canvas.
        */
        std::unique_ptr<fast_canvas_type> create_fast_canvas() const;

        /*!
            \brief Returns the fast paint observer set.

            \return The fast paint observer set.
        */
        const fast_paint_observer_set_type& fast_paint_observer_set() const;

        /*!
            \brief Returns the fast paint observer set.

            \return The fast paint observer set.
        */
        fast_paint_observer_set_type& fast_paint_observer_set();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
