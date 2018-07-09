/*! \file
    \brief The definition of tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PICTUREBOX_H)
#define TETENGO2_GUI_WIDGET_PICTUREBOX_H

#include <memory>

#include <boost/predef.h>

#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class template for a picture box.

        \tparam FastDrawingDetails A detail implementation type of fast drawing.
    */
    template <typename FastDrawingDetails>
    class picture_box : public control
    {
    public:
        // types

        //! The widget details type.
        using widget_details_type = control::widget_details_type;

        //! The message handler details type.
        using message_handler_details_type = control::message_handler_details_type;

        //! The fast drawing details type.
        using fast_drawing_details_type = FastDrawingDetails;

        //! The base type.
        using base_type = control;

        //! The widget type.
        using widget_type = widget;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        //! The fast canvas type.
        using fast_canvas_type = gui::drawing::canvas<fast_drawing_details_type>;

        //! The fast widget canvas type.
        using fast_widget_canvas_type = gui::drawing::widget_canvas<fast_drawing_details_type>;

        //! The fast paint observer set type.
        using fast_paint_observer_set_type = gui::message::paint_observer_set<fast_canvas_type>;


        // constructors and destructor

        /*!
            \brief Creates a picture box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style type.
        */
        picture_box(widget_type& parent, const scroll_bar_style_type scroll_bar_style)
        :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
          base_type{
              scroll_bar_style,
              message_handler_details_type::make_picture_box_message_handler_map(*this, message_handler_map_type{}),
              widget_details_type::create_picture_box(parent, scroll_bar_style)
          },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
          m_fast_paint_observer_set{}
        {
            base_type::initialize(this);

            parent.child_observer_set().created()(*this);

            this->paint_observer_set().paint_background().connect(
                [](typename base_type::canvas_type&) { return true; });
        }

        /*!
            \brief Destroys the picture box.
        */
        virtual ~picture_box() noexcept
        {
            try
            {
                if (this->has_parent())
                    this->parent().child_observer_set().destroying()(*this);
            }
            catch (...)
            {
            }
        }


        // functions

        /*!
            \brief Creates a fast canvas.

            \return The unique pointer to a fast canvas.
        */
        std::unique_ptr<fast_canvas_type> create_fast_canvas() const
        {
            return std::make_unique<fast_widget_canvas_type>(this->details());
        }

        /*!
            \brief Returns the fast paint observer set.

            \return The fast paint observer set.
        */
        const fast_paint_observer_set_type& fast_paint_observer_set() const
        {
            return m_fast_paint_observer_set;
        }

        /*!
            \brief Returns the fast paint observer set.

            \return The fast paint observer set.
        */
        fast_paint_observer_set_type& fast_paint_observer_set()
        {
            return m_fast_paint_observer_set;
        }


    private:
        // types

        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // variables

        fast_paint_observer_set_type m_fast_paint_observer_set;
    };
}


#endif
