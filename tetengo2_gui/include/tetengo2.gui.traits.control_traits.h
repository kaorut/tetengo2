/*! \file
    \brief The definition of tetengo2::gui::traits::control_traits.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TRAITS_CONTROLTRAITS_H)
#define TETENGO2_GUI_TRAITS_CONTROLTRAITS_H


namespace tetengo2 { namespace gui { namespace traits
{
    /*!
        \brief The traits class template for a control.

        \tparam WidgetTraits A traits type for a GUI widget.
        \tparam Color        A color type.
   */
    template <typename WidgetTraits, typename Color>
    struct control_traits
    {
        //types

        //! The base type.
        typedef WidgetTraits base_type;

        //! The color type.
        typedef Color color_type;


    };


}}}


#endif
