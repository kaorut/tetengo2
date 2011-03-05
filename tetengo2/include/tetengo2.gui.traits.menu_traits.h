/*! \file
    \brief The definition of tetengo2::gui::traits::menu_traits.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TRAITS_MENUTRAITS_H)
#define TETENGO2_GUI_TRAITS_MENUTRAITS_H


namespace tetengo2 { namespace gui { namespace traits
{
    /*!
        \brief The traits class template for a menu.
 
        \tparam Id              A ID type.
        \tparam String          A string type.
        \tparam Encoder         An encoder type.
        \tparam MenuObserverSet A menu observer set type.
   */
    template <
        typename Id,
        typename String,
        typename Encoder,
        typename MenuObserverSet
    >
    struct menu_traits
    {
        //types

        //! The ID type.
        typedef Id id_type;

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The menu observer set type.
        typedef MenuObserverSet menu_observer_set_type;


    };




}}}


#endif
