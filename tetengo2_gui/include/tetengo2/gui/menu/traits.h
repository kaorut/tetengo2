/*! \file
    \brief The definition of tetengo2::gui::menu::traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_TRAITS_H)
#define TETENGO2_GUI_MENU_TRAITS_H

#include <tetengo2/gui/menu/shortcut_key.h>
#include <tetengo2/gui/message/menu_observer_set.h>


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The traits class template for a menu.

        \tparam String            A string type.
        \tparam Encoder           An encoder type.
        \tparam VirtualKeyDetails A virtual key detail implementation type.
   */
    template <typename String, typename Encoder, typename VirtualKeyDetails>
    struct traits
    {
        //types

        //! The string type.
        using string_type = String;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The virtual key details type.
        using virtual_key_details_type = VirtualKeyDetails;

        //! The shortcut key type.
        using shortcut_key_type = shortcut_key<string_type, virtual_key_details_type>;

        //! The menu observer set type.
        using menu_observer_set_type = gui::message::menu_observer_set;


    };




}}}


#endif
