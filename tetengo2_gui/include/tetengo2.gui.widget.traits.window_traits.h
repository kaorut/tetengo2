/*! \file
    \brief The definition of tetengo2::gui::widget::traits::window_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_WINDOWTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_WINDOWTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a window.

        \tparam AbstractWindowTraits A traits type for an abstract window.
   */
    template <typename AbstractWindowTraits>
    struct window_traits
    {
        //types

        //! The base type.
        typedef AbstractWindowTraits base_type;


    };


}}}}


#endif
