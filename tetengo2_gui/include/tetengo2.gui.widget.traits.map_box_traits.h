/*! \file
    \brief The definition of tetengo2::gui::widget::traits::map_box_traits.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_MAPBOXTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_MAPBOXTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a map box.

        \tparam CustomControlTraits A traits type for a custom control.
   */
    template <typename CustomControlTraits>
    struct map_box_traits
    {
        //types

        //! The base type.
        typedef CustomControlTraits base_type;


    };


}}}}


#endif
