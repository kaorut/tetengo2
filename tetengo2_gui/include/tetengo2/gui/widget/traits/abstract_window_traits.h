/*! \file
    \brief The definition of tetengo2::gui::widget::traits::abstract_window_traits.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TRAITS_ABSTRACTWINDOWTRAITS_H)
#define TETENGO2_GUI_WIDGET_TRAITS_ABSTRACTWINDOWTRAITS_H

#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/shortcut_key.h>
#include <tetengo2/gui/menu/shortcut_key_table.h>
#include <tetengo2/gui/menu/traits.h>
#include <tetengo2/gui/message/menu_observer_set.h>
#include <tetengo2/gui/message/window_observer_set.h>
#include <tetengo2/gui/message/file_drop_observer_set.h>


namespace tetengo2 { namespace gui { namespace widget { namespace traits
{
    /*!
        \brief The traits class template for an abstract window.

        \tparam WidgetTraits A traits type for a GUI widget.
        \tparam MenuDetails  A menu details type.
   */
    template <typename WidgetTraits, typename MenuDetails>
    struct abstract_window_traits
    {
        //types

        //! The base type.
        using base_type = WidgetTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The shortcut key type.
        using shortcut_key_type = gui::menu::shortcut_key<typename base_type::virtual_key_type>;

        //! The menu observer set type.
        using menu_observer_set_type = gui::message::menu_observer_set;

        //! The menu traits type.
        using menu_traits_type =
            gui::menu::traits<
                typename base_type::string_type,
                shortcut_key_type,
                typename base_type::encoder_type,
                menu_observer_set_type
            >;

        //! The menu base type.
        using menu_base_type = gui::menu::menu_base<menu_traits_type, menu_details_type>;

        //! The shortcut key table type.
        using shortcut_key_table_type =
            gui::menu::shortcut_key_table<shortcut_key_type, menu_base_type, menu_details_type>;

        //! The menu bar type.
        using menu_bar_type = gui::menu::menu_bar<menu_traits_type, shortcut_key_table_type, menu_details_type>;

        //! The window observer set type.
        using window_observer_set_type = gui::message::window_observer_set;

        //! The file drop observer set type.
        using file_drop_observer_set_type = gui::message::file_drop_observer_set<typename base_type::path_type>;


    };


}}}}


#endif
