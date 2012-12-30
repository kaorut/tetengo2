/*! \file
    \brief The definition of tetengo2::gui::widget::traits::list_box_traits.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_LISTBOXTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_LISTBOXTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a list box.

        \tparam ControlTraits      A traits type for a control.
        \tparam IntSize            A integer size type.
        \tparam ListBoxObserverSet A list box observer set type.
   */
    template <typename ControlTraits, typename IntSize, typename ListBoxObserverSet>
    struct list_box_traits
    {
        //types

        //! The base type.
        typedef ControlTraits base_type;

        //! The integer size type.
        typedef IntSize int_size_type;

        //! The list box observer set type.
        typedef ListBoxObserverSet list_box_observer_set_type;


    };


}}}}


#endif
