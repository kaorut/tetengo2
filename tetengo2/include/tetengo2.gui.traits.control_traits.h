/*! \file
    \brief The definition of tetengo2::gui::traits::control_traits.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TRAITS_CONTROLTRAITS_H)
#define TETENGO2_GUI_TRAITS_CONTROLTRAITS_H


namespace tetengo2 { namespace gui { namespace traits
{
    /*!
        \brief The traits class template for a control.
 
        \tparam WidgetTraits A traits type for a GUI widget.
   */
    template <typename WidgetTraits>
    struct control_traits
    {
        //types

        //! The base type.
        typedef WidgetTraits base_type;


    };


}}}


#endif
