/*! \file
    \brief The definition of tetengo2::gui::widget::traits::text_box_traits.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_PICTUREBOXTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_PICTUREBOXTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a picture box.

        \tparam ControlTraits A traits type for a control.
   */
    template <typename ControlTraits>
    struct picture_box_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;


    };


}}}}


#endif
