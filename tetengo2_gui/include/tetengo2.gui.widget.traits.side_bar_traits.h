/*! \file
    \brief The definition of tetengo2::gui::widget::traits::side_bar_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_SIDEBARTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_SIDEBARTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a side bar.

        \tparam CustomControlTraits A traits type for a custom control.
        \tparam SolidBackground     A solid background type.
        \tparam SystemColorSet      A system color set type.
        \tparam Timer               A timer type.
   */
    template <typename CustomControlTraits, typename SolidBackground, typename SystemColorSet, typename Timer>
    struct side_bar_traits
    {
        //types

        //! The base type.
        using base_type = CustomControlTraits;

        //! The solid background type.
        using solid_background_type = SolidBackground;

        //! The system color set type.
        using system_color_set_type = SystemColorSet;

        //! The system cursor type.
        using system_cursor_type = typename base_type::base_type::base_type::system_cursor_type;

        //! The timer type.
        using timer_type = Timer;


    };


}}}}


#endif
