/*! \file
    \brief The definition of tetengo2::gui::widget::traits::side_bar_traits.

    Copyright (C) 2007-2013 kaoru

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
        \tparam MouseCapture        A mouse capture type.
        \tparam Timer               A timer type.
   */
    template <
        typename CustomControlTraits,
        typename SolidBackground,
        typename SystemColorSet,
        typename MouseCapture,
        typename Timer
    >
    struct side_bar_traits
    {
        //types

        //! The base type.
        typedef CustomControlTraits base_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;

        //! The system color set type.
        typedef SystemColorSet system_color_set_type;

        //! The mouse capture type.
        typedef MouseCapture mouse_capture_type;

        //! The system cursor type.
        typedef typename base_type::base_type::base_type::system_cursor_type system_cursor_type;

        //! The timer type.
        typedef Timer timer_type;


    };


}}}}


#endif
