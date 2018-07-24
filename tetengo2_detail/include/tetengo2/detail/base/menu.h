/*! \file
    \brief The definition of tetengo2::detail::base::menu.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_MENU_H)
#define TETENGO2_DETAIL_BASE_MENU_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/iterator/indirect_iterator.hpp>

namespace tetengo2 { namespace gui { namespace menu {
    class abstract_popup;
    class menu_base;
}}}


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a menu.
    */
    class menu : private boost::noncopyable
    {
    public:
        // types

        //! The menu details type.
        struct menu_details_type
        {
            /*!
                \brief Destroys the menu details.
            */
            virtual ~menu_details_type();
        };

        //! The menu details pointer type.
        using menu_details_ptr_type = std::unique_ptr<menu_details_type>;

        //! The shortcut key table details type.
        struct shortcut_key_table_details_type
        {
            /*!
                \brief Destroys the shortcut key table details.
            */
            virtual ~shortcut_key_table_details_type();
        };

        //! The shortcut key table details pointer type.
        using shortcut_key_table_details_ptr_type = std::unique_ptr<shortcut_key_table_details_type>;

        //! The style tag type.
        struct style_tag
        {
            /*!
                \brief Destroys the style tag.
            */
            virtual ~style_tag();
        };

        //! The state type.
        using state_type = int;

        //! The iterator type.
        using iterator =
            boost::indirect_iterator<typename std::vector<std::unique_ptr<gui::menu::menu_base>>::const_iterator>;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~menu();


        // functions

        /*!
            \brief Creates a menu bar.

            \return A unque pointer to a menu bar.

            \throw std::system_error When a menu bar cannot be created.
        */
        menu_details_ptr_type create_menu_bar() const;

        /*!
            \brief Creates a popup menu.

            \return A unque pointer to a popup menu.

            \throw std::system_error When a popup menu cannot be created.
        */
        menu_details_ptr_type create_popup_menu() const;

        /*!
            \brief Creates a menu.

            \return A unque pointer to a menu.
        */
        menu_details_ptr_type create_menu() const;

        /*!
            \brief Sets an enabled status.

            \param menu    A menu.
            \param enabled An enabled status.
        */
        void set_enabled(gui::menu::menu_base& menu, bool enabled) const;

        /*!
            \brief Sets a state.

            \param menu  A menu.
            \param state A status.
        */
        void set_state(gui::menu::menu_base& menu, state_type state) const;

        /*!
            \brief Creates an empty shortcut key table.

            \return A unique pointer to a shortcut key table.
        */
        shortcut_key_table_details_ptr_type create_shortcut_key_table() const;

        /*!
            \brief Creates a shortcut key table.

            \param root_menu A root menu

            \return A unique pointer to a shortcut key table.

            \throw std::system_error When a shortcut key table cannot be
                                     created.
        */
        shortcut_key_table_details_ptr_type create_shortcut_key_table(const gui::menu::menu_base& root_menu) const;

        /*!
            \brief Inserts a menu.

            \param popup_menu A popup menu to which a menu is inserted.
            \param offset     An offset.
            \param menu       A menu to insert.

            \throw std::system_error When a menu cannot be inserted.
        */
        void
        insert_menu(gui::menu::abstract_popup& popup_menu, const iterator& offset, gui::menu::menu_base& menu) const;

        /*!
            \brief Erases a menu.

            \param popup_menu A popup menu to which a menu is inserted.
            \param first      A first position to erase.
            \param last       A last position to erase.

            \throw std::system_error When a menu cannot be erased.
        */
        void erase_menus(gui::menu::abstract_popup& popup_menu, const iterator& first, const iterator& last) const;


        /*!
            \brief Returns the menu bar style.

            \return The menu bar style.
        */
        const style_tag& menu_bar_style() const;

        /*!
            \brief Returns the popup menu style.

            \return The popup menu style.
        */
        const style_tag& popup_menu_style() const;

        /*!
            \brief Returns the menu command style.

            \return The menu command style.
        */
        const style_tag& menu_command_style() const;

        /*!
            \brief Returns the menu separator style.

            \return The menu separator style.
        */
        const style_tag& menu_separator_style() const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        menu();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual menu_details_ptr_type create_menu_bar_impl() const = 0;

        virtual menu_details_ptr_type create_popup_menu_impl() const = 0;

        virtual menu_details_ptr_type create_menu_impl() const = 0;

        virtual void set_enabled_impl(gui::menu::menu_base& menu, bool enabled) const = 0;

        virtual void set_state_impl(gui::menu::menu_base& menu, state_type state) const = 0;

        virtual shortcut_key_table_details_ptr_type create_shortcut_key_table_impl() const = 0;

        virtual shortcut_key_table_details_ptr_type
        create_shortcut_key_table_impl(const gui::menu::menu_base& root_menu) const = 0;

        virtual void insert_menu_impl(
            gui::menu::abstract_popup& popup_menu,
            const iterator&            offset,
            gui::menu::menu_base&      menu) const = 0;

        virtual void
        erase_menus_impl(gui::menu::abstract_popup& popup_menu, const iterator& first, const iterator& last) const = 0;

        virtual const style_tag& menu_bar_style_impl() const = 0;

        virtual const style_tag& popup_menu_style_impl() const = 0;

        virtual const style_tag& menu_command_style_impl() const = 0;

        virtual const style_tag& menu_separator_style_impl() const = 0;
    };
}


#endif
