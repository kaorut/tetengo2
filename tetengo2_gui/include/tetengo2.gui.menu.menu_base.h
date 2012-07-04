/*! \file
    \brief The definition of tetengo2::gui::menu::menu_base.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_MENUBASE_H)
#define TETENGO2_GUI_MENU_MENUBASE_H

//#include <cassert>
//#include <cstddef>
#include <memory>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/iterator/indirect_iterator.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.gui.menu.recursive_iterator.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The base class template for a menu base.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class menu_base : boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The string type.
        typedef typename traits_type::string_type string_type;

        //! The shortcut key type.
        typedef typename traits_type::shortcut_key_type shortcut_key_type;

        //! The encoder type.
        typedef typename traits_type::encoder_type encoder_type;

        //! The menu observer set type.
        typedef typename traits_type::menu_observer_set_type menu_observer_set_type;

        //! The const iterator type.
        typedef
            boost::indirect_iterator<typename std::vector<std::unique_ptr<menu_base>>::const_iterator> const_iterator;

        //! The iterator type.
        typedef boost::indirect_iterator<typename std::vector<std::unique_ptr<menu_base>>::iterator> iterator;

        //! The const recursive iterator type.
        typedef recursive_iterator<const menu_base> const_recursive_iterator_type;

        //! The recursive iterator type.
        typedef recursive_iterator<menu_base> recursive_iterator_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The detail implementation type.
        typedef typename menu_details_type::menu_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename menu_details_type::menu_details_ptr_type details_ptr_type;

        //! The style type.
        typedef typename menu_details_type::template style_tag<menu_base> style_type;

        //! The state type.
        enum state_type
        {
            state_default,  //!< Default state.
            state_checked,  //!< Checked state.
            state_selected, //!< Selected state.
        };


        // constructors and destructor

        /*!
            \brief Destroys the menu base.
        */
        virtual ~menu_base()
        {}


        // functions

        /*!
            \brief Returns the text.

            \return The text.
        */
        const string_type& text()
        const
        {
            return m_text;
        }

        /*!
            \brief Returns the style.

            \return The style.
        */
        const style_type& style()
        const
        {
            return style_impl();
        }
        
        /*!
            \brief Returns the enabled status.

            \return The enabled status.
        */
        bool enabled()
        const
        {
            return m_enabled;
        }

        /*!
            \brief Sets an enabled status.

            \param enabled An enabled status.
        */
        void set_enabled(const bool enabled)
        {
            menu_details_type::set_enabled(*this, enabled);
            m_enabled = enabled;
        }

        /*!
            \brief Returns the state.

            \return The state.
        */
        state_type state()
        const
        {
            return m_state;
        }

        /*!
            \brief Sets a state.

            \param state.
        */
        void set_state(const state_type state)
        {
            menu_details_type::set_state(*this, state);
            m_state = state;
        }

        /*!
            \brief Checks whether the menu has a shortucut key.

            \retval true  When the menu has a shortcut key.
        */
        bool has_shortcut_key()
        const
        {
            return m_shortcut_key;
        }

        /*!
            \brief Returns the shortcut key.

            \return The shortcut key.

            \throw std::logic_error When the menu has no shortcut key.
        */
        const shortcut_key_type& shortcut_key()
        const
        {
            if (!has_shortcut_key())
                BOOST_THROW_EXCEPTION(std::logic_error("This menu has no shortcut key."));

            return *m_shortcut_key;
        }

        /*!
            \brief Selects this menu.
        */
        void select()
        {
            m_menu_observer_set.selected()();
        }

        /*!
            \brief Returns the menu observer set.

            \return The menu observer set.
        */
        const menu_observer_set_type& menu_observer_set()
        const
        {
            return m_menu_observer_set;
        }

        /*!
            \brief Returns the menu observer set.

            \return The menu observer set.
        */
        menu_observer_set_type& menu_observer_set()
        {
            return m_menu_observer_set;
        }

        /*!
            \brief Returns the first immutable iterator to the children.

            \return The first immutable iterator.
        */
        const_iterator begin()
        const
        {
            return begin_impl();
        }

        /*!
            \brief Returns the first mutable iterator to the children.

            \return The first mutable iterator.
        */
        iterator begin()
        {
            return begin_impl();
        }

        /*!
            \brief Returns the last immutable iterator to the children.

            \return The last immutable iterator.
        */
        const_iterator end()
        const
        {
            return end_impl();
        }

        /*!
            \brief Returns the last mutable iterator to the children.

            \return The last mutable iterator.
        */
        iterator end()
        {
            return end_impl();
        }

        /*!
            \brief Returns the recursive first immutable iterator to this menu and the children.

            The first iterator points to this menu.

            \return The recursive first immutable iterator.
        */
        const_recursive_iterator_type recursive_begin()
        const
        {
            return recursive_begin_impl();
        }

        /*!
            \brief Returns the recursive first mutable iterator to this menu and the children.

            The first iterator points to this menu.

            \return The recursive first mutable iterator.
        */
        recursive_iterator_type recursive_begin()
        {
            return recursive_begin_impl();
        }

        /*!
            \brief Returns the recursive last immutable iterator to this menu and the children.

            \return The recursive last immutable iterator.
        */
        const_recursive_iterator_type recursive_end()
        const
        {
            return recursive_end_impl();
        }

        /*!
            \brief Returns the recursive last mutable iterator to this menu and the children.

            \return The recursive last mutable iterator.
        */
        recursive_iterator_type recursive_end()
        {
            return recursive_end_impl();
        }

        /*!
            \brief Inserts a menu as a child.

            \param offset An offset where a menu is inserted.
            \param p_menu A unique pointer to a menu. It must not be NULL.
        */
        void insert(const iterator offset, std::unique_ptr<menu_base> p_menu)
        {
            insert_impl(offset, std::move(p_menu));
        }

        /*!
            \brief Erases the menus from the children.

            \param first The first iterator to the erased menus.
            \param last  The last iterator to the eraed menus.

            \throw std::logic_error Always.
        */
        void erase(const iterator first, const iterator last)
        {
            erase_impl(first, last);
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<const details_type&> details()
        const
        {
            return boost::make_optional<const details_type&>(static_cast<bool>(m_p_details), *m_p_details);
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<details_type&> details()
        {
            return boost::make_optional<details_type&>(static_cast<bool>(m_p_details), *m_p_details);
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a menu base with a shortcut key.

            \tparam S A string type.

            \param text      A text.
            \param p_details A unique pointer to a detail implementation.
        */
        template <typename S>
        menu_base(S&& text, details_ptr_type p_details)
        :
        m_text(std::forward<S>(text)),
        m_enabled(true),
        m_state(state_default),
        m_shortcut_key(),
        m_menu_observer_set(),
        m_p_details(std::move(p_details))
        {
            set_enabled(true);
            set_state(state_default);
        }

        /*!
            \brief Creates a menu base without a shortcut key.

            \tparam S  A string type.
            \tparam SK A shortcut key type.

            \param text         A text.
            \param shortcut_key A shortcut key.
            \param p_details    A unique pointer to a detail implementation.
        */
        template <typename S, typename SK>
        menu_base(S&& text, SK&& shortcut_key, details_ptr_type p_details)
        :
        m_text(std::forward<S>(text)),
        m_enabled(true),
        m_state(state_default),
        m_shortcut_key(std::forward<SK>(shortcut_key)),
        m_menu_observer_set(),
        m_p_details(std::move(p_details))
        {
            set_enabled(true);
            set_state(state_default);
        }


    private:
        // static functions

        static std::vector<std::unique_ptr<menu_base>>& empty_children()
        {
            static std::vector<std::unique_ptr<menu_base>> singleton;
            assert(singleton.empty());
            return singleton;
        }


        // variables

        const string_type m_text;

        bool m_enabled;

        state_type m_state;

        const boost::optional<shortcut_key_type> m_shortcut_key;

        menu_observer_set_type m_menu_observer_set;

        const details_ptr_type m_p_details;


        // virtual functions

        virtual const style_type& style_impl()
        const = 0;

        virtual const_iterator begin_impl()
        const
        {
            return const_iterator(empty_children().begin());
        }

        virtual iterator begin_impl()
        {
            return iterator(empty_children().begin());
        }

        virtual const_iterator end_impl()
        const
        {
            return const_iterator(empty_children().end());
        }

        virtual iterator end_impl()
        {
            return iterator(empty_children().end());
        }

        virtual const_recursive_iterator_type recursive_begin_impl()
        const
        {
            return const_recursive_iterator_type();
        }

        virtual recursive_iterator_type recursive_begin_impl()
        {
            return recursive_iterator_type();
        }

        virtual const_recursive_iterator_type recursive_end_impl()
        const
        {
            return const_recursive_iterator_type();
        }

        virtual recursive_iterator_type recursive_end_impl()
        {
            return recursive_iterator_type();
        }

        virtual void insert_impl(const iterator offset, std::unique_ptr<menu_base> p_menu)
        {
            BOOST_THROW_EXCEPTION(
                std::logic_error("Can't insert any menus.")
            );
        }

        virtual void erase_impl(const iterator first, const iterator last)
        {
            BOOST_THROW_EXCEPTION(std::logic_error("Can't erase any menus."));
        }


    };


}}}


#endif
