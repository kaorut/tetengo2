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
   */
    template <typename CustomControlTraits>
    struct side_bar_traits
    {
        //types

        //! The base type.
        using base_type = CustomControlTraits;


    };


}}}}


#endif
