/*! \file
    \brief The definition of tetengo2::gui::traits::image_traits.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TRAITS_IMAGETRAITS_H)
#define TETENGO2_GUI_TRAITS_IMAGETRAITS_H


namespace tetengo2 { namespace gui { namespace traits
{
    /*!
        \brief The traits class template for an image.

        \tparam ControlTraits A traits type for a control.
        \tparam Picture       A picture type.
   */
    template <typename ControlTraits, typename Picture>
    struct image_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;

        //! The picture type.
        typedef Picture picture_type;


    };


}}}


#endif
