/*! \file
    \brief The definition of tetengo2::gui::widget::traits::link_label_traits.

    Copyright (C) 2007-2014 kaoru

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
        \tparam Shell           A shell type.
   */
    template <typename LabelTraits, typename SolidBackground, typename SystemColorSet, typename Shell>
    struct link_label_traits
    {
        //types

        //! The base type.
        using base_type = LabelTraits;

        //! The solid background type.
        using solid_background_type = SolidBackground;

        //! The system color set type.
        using system_color_set_type = SystemColorSet;

        //! The shell type.
        using shell_type = Shell;


    };


}}}}


#endif
