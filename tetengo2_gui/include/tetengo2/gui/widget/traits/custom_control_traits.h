/*! \file
    \brief The definition of tetengo2::gui::widget::traits::custom_control_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_CUSTOMCONTROLTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_CUSTOMCONTROLTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a custom control.

        \tparam ControlTraits A traits type for a control.
        \tparam MouseCapture  A mouse capture type.
   */
    template <typename ControlTraits, typename MouseCapture>
    struct custom_control_traits
    {
        //types

        //! The base type.
        using base_type = ControlTraits;

        //! The mouse capture type.
        using mouse_capture_type = MouseCapture;


    };


}}}}


#endif
