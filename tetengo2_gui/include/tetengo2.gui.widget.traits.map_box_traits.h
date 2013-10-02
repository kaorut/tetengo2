/*! \file
    \brief The definition of tetengo2::gui::widget::traits::map_box_traits.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_MAPBOXTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_MAPBOXTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a map box.

        \tparam CustomControlTraits      A traits type for a custom control.
        \tparam IntSize                  A integer size type.
        \tparam SolidBackground          A solid background type.
        \tparam SystemColorSet           A system color set type.
        \tparam MouseCapture             A mouse capture type.
        \tparam ListSelectionObserverSet A list selection observer set type.
   */
    template <
        typename CustomControlTraits,
        typename IntSize,
        typename SolidBackground,
        typename SystemColorSet,
        typename MouseCapture,
        typename ListSelectionObserverSet
    >
    struct map_box_traits
    {
        //types

        //! The base type.
        typedef CustomControlTraits base_type;

        //! The integer size type.
        typedef IntSize int_size_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;

        //! The system color set type.
        typedef SystemColorSet system_color_set_type;

        //! The mouse capture type.
        typedef MouseCapture mouse_capture_type;

        //! The system cursor type.
        typedef typename base_type::base_type::base_type::system_cursor_type system_cursor_type;

        //! The list selection observer set type.
        typedef ListSelectionObserverSet list_selection_observer_set_type;


    };


}}}}


#endif
