/*! \file
    \brief The definition of tetengo2::gui::widget::traits::dialog_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_DIALOGTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_DIALOGTRAITS_H


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for a dialog.

        \tparam AbstractWindowTraits A traits type for an abstract window.
   */
    template <typename AbstractWindowTraits>
    struct dialog_traits
    {
        //types

        //! The base type.
        using base_type = AbstractWindowTraits;


    };


}}}}


#endif
