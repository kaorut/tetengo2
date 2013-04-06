/*! \file
    \brief The definition of tetengo2::gui::widget::traits::text_box_traits.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_CUSTOMCONTROLTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_CUSTOMCONTROLTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a custom control.

        \tparam ControlTraits A traits type for a control.
   */
    template <typename ControlTraits>
    struct custom_control_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;


    };


}}}}


#endif
