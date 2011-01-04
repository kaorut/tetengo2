/*! \file
    \brief The definition of tetengo2::gui::traits::button_traits.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TRAITS_BUTTONTRAITS_H)
#define TETENGO2_GUI_TRAITS_BUTTONTRAITS_H


namespace tetengo2 { namespace gui { namespace traits
{
    /*!
        \brief The traits class template for a button.
 
        \tparam ControlTraits A traits type for a control.
   */
    template <typename ControlTraits>
    struct button_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;


    };


}}}


#endif
