/*! \file
    \brief The definition of tetengo2::gui::widget::traits::map_box_traits.

    Copyright (C) 2007-2014 kaoru

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
        \tparam ListSelectionObserverSet A list selection observer set type.
   */
    template <
        typename CustomControlTraits,
        typename IntSize,
        typename SolidBackground,
        typename SystemColorSet,
        typename ListSelectionObserverSet
    >
    struct map_box_traits
    {
        //types

        //! The base type.
        using base_type = CustomControlTraits;

        //! The integer size type.
        using int_size_type = IntSize;

        //! The solid background type.
        using solid_background_type = SolidBackground;

        //! The system color set type.
        using system_color_set_type = SystemColorSet;

        //! The system cursor type.
        using system_cursor_type = typename base_type::base_type::base_type::system_cursor_type;

        //! The list selection observer set type.
        using list_selection_observer_set_type = ListSelectionObserverSet;


    };


}}}}


#endif
