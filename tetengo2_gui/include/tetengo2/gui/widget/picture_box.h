/*! \file
    \brief The definition of tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2014 kaoru

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
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a picture box.

        \tparam Traits             A traits type.
        \tparam DetailsTraits      A detail implementation type traits.
        \tparam FastDrawingDetails A detail implementation type of fast drawing.
    */
    template <typename Traits, typename DetailsTraits, typename FastDrawingDetails>
    class picture_box : public control<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The detail implementation type of a widget.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The detail implementation type.
        using details_type = typename widget_details_type::widget_details_type;

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

        //! The fast drawing details type.
        using fast_drawing_details_type = FastDrawingDetails;

        //! The base type.
        using base_type = control<traits_type, details_traits_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The system cursor type.
        using system_cursor_type = typename base_type::system_cursor_type;

        //! The cursor type.
        using cursor_type = typename base_type::cursor_type;

        //! The scroll bar type.
        using scroll_bar_type = typename base_type::scroll_bar_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        //! The mouse observer set type.
        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        //! The fast canvas traits type.
        using canvas_traits_type = typename base_type::canvas_traits_type;

        //! The fast widget canvas type.
        using fast_widget_canvas_type =
            gui::drawing::widget_canvas<canvas_traits_type, fast_drawing_details_type, icon_details_type>;

        //! The fast canvas type.
        using fast_canvas_type =
            gui::drawing::canvas<canvas_traits_type, fast_drawing_details_type, icon_details_type>;

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
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_picture_box_message_handler_map(*this, message_handler_map_type{}),
            widget_details_type::create_picture_box(parent, scroll_bar_style)
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_fast_paint_observer_set()
        {
            this->initialize(this);
            this->paint_observer_set().paint_background().connect(
                [](typename base_type::canvas_type&) { return true; }
            );
        }

        /*!
            \brief Destroys the picture box.
        */
        virtual ~picture_box()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Creates a fast canvas.

            \return The unique pointer to a fast canvas.
        */
        std::unique_ptr<fast_canvas_type> create_fast_canvas()
        const
        {
            return stdalt::make_unique<fast_widget_canvas_type>(this->details());
        }

        /*!
            \brief Returns the fast paint observer set.

            \return The fast paint observer set.
        */
        const fast_paint_observer_set_type& fast_paint_observer_set()
        const
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


}}}


#endif
