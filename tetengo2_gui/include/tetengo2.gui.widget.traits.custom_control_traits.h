/*! \file
    \brief The definition of tetengo2::gui::widget::traits::text_box_traits.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_PICTUREBOXTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_PICTUREBOXTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a picture box.

        \tparam ControlTraits        A traits type for a control.
        \tparam FastWidgetCanvas     A fast widget canvas type.
        \tparam FastPaintObserverSet A fast paint observer set type.
   */
    template <typename ControlTraits, typename FastWidgetCanvas, typename FastPaintObserverSet>
    struct picture_box_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;

        //! The fast widget canvas type.
        typedef FastWidgetCanvas fast_widget_canvas_type;

        //! The fast canvas type.
        typedef typename fast_widget_canvas_type::base_type fast_canvas_type;

        //! The fast paint observer set type.
        typedef FastPaintObserverSet fast_paint_observer_set_type;


    };


}}}}


#endif
