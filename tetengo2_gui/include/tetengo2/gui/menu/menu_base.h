/*! \file
    \brief The definition of tetengo2::gui::menu::menu_base.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_MENUBASE_H)
#define TETENGO2_GUI_MENU_MENUBASE_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/iterator/indirect_iterator.hpp>

#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/recursive_iterator.h>
#include <tetengo2/gui/menu/shortcut_key.h>
#include <tetengo2/gui/message/menu_observer_set.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The base class for a menu base.
   */
    class menu_base : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The details type.
        using details_type = detail::base::menu::menu_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = detail::base::menu::menu_details_ptr_type;

        //! The shortcut key type.
        using shortcut_key_type = shortcut_key;

        //! The menu observer set type.
        using menu_observer_set_type = gui::message::menu_observer_set;

        //! The const iterator type.
        using const_iterator =
            boost::indirect_iterator<typename std::vector<std::unique_ptr<menu_base>>::const_iterator>;

        //! The iterator type.
        using iterator = boost::indirect_iterator<typename std::vector<std::unique_ptr<menu_base>>::iterator>;

        //! The const recursive iterator type.
        using const_recursive_iterator_type = recursive_iterator<const menu_base>;

        //! The recursive iterator type.
        using recursive_iterator_type = recursive_iterator<menu_base>;

        //! The style type.
        using style_type = detail::base::menu::style_tag;

        //! The state type.
        enum class state_type
        {
            default_, //!< Default state.
            checked, //!< Checked state.
            selected, //!< Selected state.
        };


        // constructors and destructor

        /*!
            \brief Destroys the menu base.
        */
        virtual ~menu_base();


        // functions

        /*!
            \brief Returns the text.

            \return The text.
        */
        const string_type& text() const;

        /*!
            \brief Returns the style.

            \return The style.
        */
        const style_type& style() const;

        /*!
            \brief Returns the enabled status.

            \return The enabled status.
        */
        bool enabled() const;

        /*!
            \brief Sets an enabled status.

            \param enabled An enabled status.
        */
        void set_enabled(const bool enabled);

        /*!
            \brief Returns the state.

            \return The state.
        */
        state_type state() const;

        /*!
            \brief Sets a state.

            \param state A state.
        */
        void set_state(const state_type state);

        /*!
            \brief Checks whether the menu has a shortucut key.

            \retval true  When the menu has a shortcut key.
        */
        bool has_shortcut_key() const;

        /*!
            \brief Returns the shortcut key.

            \return The shortcut key.

            \throw std::logic_error When the menu has no shortcut key.
        */
        const shortcut_key_type& get_shortcut_key() const;

        /*!
            \brief Selects this menu.
        */
        void select();

        /*!
            \brief Returns the menu observer set.

            \return The menu observer set.
        */
        const menu_observer_set_type& menu_observer_set() const;

        /*!
            \brief Returns the menu observer set.

            \return The menu observer set.
        */
        menu_observer_set_type& menu_observer_set();

        /*!
            \brief Returns the first immutable iterator to the children.

            \return The first immutable iterator.
        */
        const_iterator begin() const;

        /*!
            \brief Returns the first mutable iterator to the children.

            \return The first mutable iterator.
        */
        iterator begin();

        /*!
            \brief Returns the last immutable iterator to the children.

            \return The last immutable iterator.
        */
        const_iterator end() const;

        /*!
            \brief Returns the last mutable iterator to the children.

            \return The last mutable iterator.
        */
        iterator end();

        /*!
            \brief Returns the recursive first immutable iterator to this menu and the children.

            The first iterator points to this menu.

            \return The recursive first immutable iterator.
        */
        const_recursive_iterator_type recursive_begin() const;

        /*!
            \brief Returns the recursive first mutable iterator to this menu and the children.

            The first iterator points to this menu.

            \return The recursive first mutable iterator.
        */
        recursive_iterator_type recursive_begin();

        /*!
            \brief Returns the recursive last immutable iterator to this menu and the children.

            \return The recursive last immutable iterator.
        */
        const_recursive_iterator_type recursive_end() const;

        /*!
            \brief Returns the recursive last mutable iterator to this menu and the children.

            \return The recursive last mutable iterator.
        */
        recursive_iterator_type recursive_end();

        /*!
            \brief Inserts a menu as a child.

            \param offset An offset where a menu is inserted.
            \param p_menu A unique pointer to a menu. It must not be nullptr.
        */
        void insert(const iterator offset, std::unique_ptr<menu_base> p_menu);

        /*!
            \brief Erases the menus from the children.

            \param first The first iterator to the erased menus.
            \param last  The last iterator to the eraed menus.

            \throw std::logic_error Always.
        */
        void erase(const iterator first, const iterator last);

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details();


    protected:
        // constructors and destructor

        /*!
            \brief Creates a menu base with a shortcut key.

            \param text      A text.
            \param p_details A unique pointer to a detail implementation.
        */
        menu_base(string_type text, details_ptr_type p_details);

        /*!
            \brief Creates a menu base without a shortcut key.

            \param text         A text.
            \param shortcut_key A shortcut key.
            \param p_details    A unique pointer to a detail implementation.
        */
        menu_base(string_type text, shortcut_key_type shortcut_key, details_ptr_type p_details);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual const style_type& style_impl() const = 0;

        virtual const_iterator begin_impl() const;

        virtual iterator begin_impl();

        virtual const_iterator end_impl() const;

        virtual iterator end_impl();

        virtual const_recursive_iterator_type recursive_begin_impl() const;

        virtual recursive_iterator_type recursive_begin_impl();

        virtual const_recursive_iterator_type recursive_end_impl() const;

        virtual recursive_iterator_type recursive_end_impl();

        virtual void insert_impl(const iterator offset, std::unique_ptr<menu_base> p_menu);

        virtual void erase_impl(const iterator first, const iterator last);
    };
}


#endif
