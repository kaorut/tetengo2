/*! \file
    \brief The definition of tetengo2::gui::widget::traits::link_label_traits.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_LINKLABELTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_LINKLABELTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a link label.

        \tparam LabelTraits     A traits type for a label.
        \tparam SolidBackground A solid background type.
        \tparam SystemColorSet  A system color set type.
   */
    template <
        typename LabelTraits,
        typename SolidBackground,
        typename SystemColorSet
    >
    struct link_label_traits
    {
        //types

        //! The base type.
        typedef LabelTraits base_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;

        //! The system color set.
        typedef SystemColorSet system_color_set_type;


    };


}}}}


#endif
