/*! \file
    \brief The definition of tetengo2::gui::widget::traits::list_box_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_LISTBOXTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_LISTBOXTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a list box.

        \tparam ControlTraits            A traits type for a control.
        \tparam IntSize                  A integer size type.
        \tparam ListSelectionObserverSet A list selection observer set type.
   */
    template <typename ControlTraits, typename IntSize, typename ListSelectionObserverSet>
    struct list_box_traits
    {
        //types

        //! The base type.
        using base_type = ControlTraits;

        //! The integer size type.
        using int_size_type = IntSize;

        //! The list selection observer set type.
        using list_selection_observer_set_type = ListSelectionObserverSet;


    };


}}}}


#endif
