/*! \file
    \brief The definition of tetengo2::gui::menu_traits.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUTRAITS_H)
#define TETENGO2_GUI_MENUTRAITS_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The traits class template for a menu.
 
        \tparam Id              A ID type.
        \tparam Handle          A handle type.
        \tparam String          A string type.
        \tparam Encoder         An encoder type.
        \tparam MenuObserverSet A menu observer set type.
   */
    template <
        typename Id,
        typename Handle,
        typename String,
        typename Encoder,
        typename MenuObserverSet
    >
    struct menu_traits
    {
        //types

        //! \return The ID type.
        typedef Id id_type;

        //! \return The handle type.
        typedef Handle handle_type;

        //! \return The string type.
        typedef String string_type;

        //! \return The encoder type.
        typedef Encoder encoder_type;

        //! \return The menu observer set type.
        typedef MenuObserverSet menu_observer_set_type;


    };




}}


#endif
