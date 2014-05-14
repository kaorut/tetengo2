/*! \file
    \brief The definition of tetengo2::gui::widget::traits::image_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_IMAGETRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_IMAGETRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for an image.

        \tparam ControlTraits A traits type for a control.
        \tparam Picture       A picture type.
        \tparam Icon          An icon type.
   */
    template <typename ControlTraits, typename Picture, typename Icon>
    struct image_traits
    {
        //types

        //! The base type.
        using base_type = ControlTraits;

        //! The picture type.
        using picture_type = Picture;

        //! The icon type.
        using icon_type = Icon;


    };


}}}}


#endif
