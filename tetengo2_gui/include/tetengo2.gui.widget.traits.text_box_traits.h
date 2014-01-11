/*! \file
    \brief The definition of tetengo2::gui::widget::traits::text_box_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_TEXTBOXTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_TEXTBOXTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a text box.

        \tparam ControlTraits      A traits type for a control.
        \tparam TextBoxObserverSet A text box observer set type.
   */
    template <typename ControlTraits, typename TextBoxObserverSet>
    struct text_box_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;

        //! The text box observer set type.
        typedef TextBoxObserverSet text_box_observer_set_type;


    };


}}}}


#endif
