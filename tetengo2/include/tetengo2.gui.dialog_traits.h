/*! \file
    \brief The definition of tetengo2::gui::dialog_traits.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DIALOGTRAITS_H)
#define TETENGO2_GUI_DIALOGTRAITS_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The traits class template for a dialog.
 
        \tparam AbstractWindowTraits A traits type for an abstract window.
        \tparam MessageLoop          A generator type for a message loop.
        \tparam QuitMessageLoop      A unary functor type for quitting the
                                     message loop.
   */
    template <
        typename AbstractWindowTraits,
        typename MessageLoop,
        typename QuitMessageLoop
    >
    struct dialog_traits
    {
        //types

        //! \return The base type.
        typedef AbstractWindowTraits base_type;

        //! \return The message loop type.
        typedef MessageLoop message_loop_type;

        //! \return The quit-message-loop type.
        typedef QuitMessageLoop quit_message_loop_type;


    };


}}


#endif
