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
        \tparam MessageLoop          A message loop type.
        \tparam MessageLoopBreak     A message loop break type.
   */
    template <typename AbstractWindowTraits, typename MessageLoop, typename MessageLoopBreak>
    struct dialog_traits
    {
        //types

        //! The base type.
        using base_type = AbstractWindowTraits;

        //! The message loop type.
        using message_loop_type = MessageLoop;

        //! The message loop break type.
        using message_loop_break_type = MessageLoopBreak;


    };


}}}}


#endif
