/*! \file
    \brief The definition of tetengo2::gui::widget::traits::abstract_window_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_ABSTRACTWINDOWTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_ABSTRACTWINDOWTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for an abstract window.

        \tparam WidgetTraits A traits type for a GUI widget.
   */
    template <typename WidgetTraits>
    struct abstract_window_traits
    {
        //types

        //! The base type.
        using base_type = WidgetTraits;


    };


}}}}


#endif
