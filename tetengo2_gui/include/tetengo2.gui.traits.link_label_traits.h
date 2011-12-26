/*! \file
    \brief The definition of tetengo2::gui::traits::link_label_traits.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TRAITS_LINKLABELTRAITS_H)
#define TETENGO2_GUI_TRAITS_LINKLABELTRAITS_H


namespace tetengo2 { namespace gui { namespace traits
{
    /*!
        \brief The traits class template for a link label.

        \tparam LabelTraits A traits type for a label.
   */
    template <typename LabelTraits>
    struct link_label_traits
    {
        //types

        //! The base type.
        typedef LabelTraits base_type;


    };


}}}


#endif
