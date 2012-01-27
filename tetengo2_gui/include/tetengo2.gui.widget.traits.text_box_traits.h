/*! \file
    \brief The definition of tetengo2::gui::widget::traits::textbox_traits.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_TEXTBOXTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_TEXTBOXTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a text box.

        \tparam ControlTraits A traits type for a control.
   */
    template <typename ControlTraits>
    struct textbox_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;


    };


}}}}


#endif
