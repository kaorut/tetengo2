/*! \file
    \brief The definition of tetengo2::detail::stub::menu.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MENU_H)
#define TETENGO2_DETAIL_STUB_MENU_H

#include <memory>
#include <system_error>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>

#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a menu.
    */
    class menu : private boost::noncopyable
    {
    public:
        // types

        //! The menu details type.
        struct menu_details_type {};

        //! The menu details pointer type.
        using menu_details_ptr_type = std::unique_ptr<menu_details_type>;

        //! The shortcut key table details type.
        struct shortcut_key_table_details_type {};

        //! The shortcut key table details pointer type.
        using shortcut_key_table_details_ptr_type = std::unique_ptr<shortcut_key_table_details_type>;

        /*!
            \brief The style tag type.

            \tparam MenuBase A menu base type.
        */
        template <typename MenuBase>
        struct style_tag {};


        // static functions

        /*!
            \brief Creates a menu bar.

            \return A unque pointer to a menu bar.

            \throw std::system_error When a menu bar cannot be created.
        */
        static menu_details_ptr_type create_menu_bar()
        {
            return stdalt::make_unique<menu_details_type>();
        }

        /*!
            \brief Creates a popup menu.

            \return A unque pointer to a popup menu.

            \throw std::system_error When a popup menu cannot be created.
        */
        static menu_details_ptr_type create_popup_menu()
        {
            return stdalt::make_unique<menu_details_type>();
        }

        /*!
            \brief Creates a menu.

            \return A unque pointer to a menu.
        */
        static menu_details_ptr_type create_menu()
        {
            return stdalt::make_unique<menu_details_type>();
        }

        /*!
            \brief Sets an enabled status.

            \tparam MenuBase A menu base type.

            \param menu    A menu.
            \param enabled An enabled status.
        */
        template <typename MenuBase>
        static void set_enabled(MenuBase& menu, const bool enabled)
        {
            boost::ignore_unused(menu, enabled);
        }

        /*!
            \brief Sets a state.

            \tparam MenuBase A menu base type.

            \param menu  A menu.
            \param state A status.
        */
        template <typename MenuBase>
        static void set_state(MenuBase& menu, const typename MenuBase::state_type state)
        {
            boost::ignore_unused(menu, state);
        }

        /*!
            \brief Creates an empty shortcut key table.

            \tparam Entry A shortcut key table entry type.

            \return A unique pointer to a shortcut key table.
        */
        template <typename Entry>
        static shortcut_key_table_details_ptr_type create_shortcut_key_table()
        {
            return stdalt::make_unique<shortcut_key_table_details_type>();
        }

        /*!
            \brief Creates a shortcut key table.

            \tparam InputIterator An input iterator type.

            \param first A first position among shortcut keys.
            \param last  A last position among shortcut keys.

            \return A unique pointer to a shortcut key table.

            \throw std::system_error When a shortcut key table cannot be
                                     created.
        */
        template <typename InputIterator>
        static shortcut_key_table_details_ptr_type create_shortcut_key_table(
            const InputIterator first,
            const InputIterator last
        )
        {
            boost::ignore_unused(first, last);
            return stdalt::make_unique<shortcut_key_table_details_type>();
        }

        /*!
            \brief Inserts a menu.

            \tparam PopupMenu       A popup menu type.
            \tparam ForwardIterator An forward iterator type.
            \tparam MenuBase        A menu base type.
            \tparam Encoder         An encoder type.

            \param popup_menu A popup menu to which a menu is inserted.
            \param offset     An offset.
            \param menu       A menu to insert.
            \param encoder    An encoder.

            \throw std::system_error When a menu cannot be inserted.
        */
        template <typename PopupMenu, typename ForwardIterator, typename MenuBase, typename Encoder>
        static void insert_menu(
            PopupMenu&            popup_menu,
            const ForwardIterator offset,
            MenuBase&             menu,
            const Encoder&        encoder
        )
        {
            boost::ignore_unused(popup_menu, offset, menu, encoder);
        }

        /*!
            \brief Erases a menu.

            \tparam PopupMenu       A popup menu type.
            \tparam ForwardIterator An forward iterator type.

            \param popup_menu A popup menu to which a menu is inserted.
            \param first      A first position to erase.
            \param last       A last position to erase.

            \throw std::system_error When a menu cannot be erased.
        */
        template <typename PopupMenu, typename ForwardIterator>
        static void erase_menus(PopupMenu& popup_menu, const ForwardIterator first, const ForwardIterator last)
        {
            boost::ignore_unused(popup_menu, first, last);
        }

        /*!
            \brief Returns the menu bar style.

            \tparam MenuBase A menu base type.

            \return The menu bar style.
        */
        template <typename MenuBase>
        static const style_tag<MenuBase>& menu_bar_style()
        {
            static const auto singleton = style_tag<MenuBase>();
            return singleton;
        }

        /*!
            \brief Returns the popup menu style.

            \tparam MenuBase A menu base type.

            \return The popup menu style.
        */
        template <typename MenuBase>
        static const style_tag<MenuBase>& popup_menu_style()
        {
            static const auto singleton = style_tag<MenuBase>();
            return singleton;
        }

        /*!
            \brief Returns the menu command style.

            \tparam MenuBase A menu base type.

            \return The menu command style.
        */
        template <typename MenuBase>
        static const style_tag<MenuBase>& menu_command_style()
        {
            static const auto singleton = style_tag<MenuBase>();
            return singleton;
        }

        /*!
            \brief Returns the menu separator style.

            \tparam MenuBase A menu base type.

            \return The menu separator style.
        */
        template <typename MenuBase>
        static const style_tag<MenuBase>& menu_separator_style()
        {
            static const auto singleton = style_tag<MenuBase>();
            return singleton;
        }


    private:
        // forbidden operations

        menu()
        = delete;


    };


}}}


#endif
