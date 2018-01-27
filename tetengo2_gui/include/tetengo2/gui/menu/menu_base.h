/*! \file
    \brief The definition of tetengo2::gui::menu::menu_base.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_MENUBASE_H)
#define TETENGO2_GUI_MENU_MENUBASE_H

#include <cassert>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/menu/recursive_iterator.h>
#include <tetengo2/gui/menu/shortcut_key.h>
#include <tetengo2/gui/message/menu_observer_set.h>


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The base class template for a menu base.

        \tparam String            A string type.
        \tparam Encoder           An encoder type.
        \tparam MenuDetails       A detail implementation type of a menu.
        \tparam VirtualKeyDetails A detail implementation type of a virtual key.
   */
    template <typename String, typename Encoder, typename MenuDetails, typename VirtualKeyDetails>
    class menu_base : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The details type.
        using details_type = typename menu_details_type::menu_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename menu_details_type::menu_details_ptr_type;

        //! The virtual key details type.
        using virtual_key_details_type = VirtualKeyDetails;

        //! The shortcut key type.
        using shortcut_key_type = shortcut_key<string_type, virtual_key_details_type>;

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
        using style_type = typename menu_details_type::template style_tag<menu_base>;

        //! The state type.
        enum class state_type
        {
            default_,  //!< Default state.
            checked,   //!< Checked state.
            selected,  //!< Selected state.
        };


        // constructors and destructor

        /*!
            \brief Destroys the menu base.
        */
        virtual ~menu_base()
        = default;


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

            \param state A state.
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
            return static_cast<bool>(m_shortcut_key);
        }

        /*!
            \brief Returns the shortcut key.

            \return The shortcut key.

            \throw std::logic_error When the menu has no shortcut key.
        */
        const shortcut_key_type& get_shortcut_key()
        const
        {
            if (!has_shortcut_key())
                BOOST_THROW_EXCEPTION((std::logic_error{ "This menu has no shortcut key." }));

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
            \param p_menu A unique pointer to a menu. It must not be nullptr.
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
        const details_type& details()
        const
        {
            assert(m_p_details);
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            assert(m_p_details);
            return *m_p_details;
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a menu base with a shortcut key.

            \param text      A text.
            \param p_details A unique pointer to a detail implementation.
        */
        menu_base(string_type text, details_ptr_type p_details)
        :
        m_text(std::move(text)),
        m_enabled(true),
        m_state(state_type::default_),
        m_shortcut_key(),
        m_menu_observer_set(),
        m_p_details(std::move(p_details))
        {
            set_enabled(true);
            set_state(state_type::default_);
        }

        /*!
            \brief Creates a menu base without a shortcut key.

            \param text         A text.
            \param shortcut_key A shortcut key.
            \param p_details    A unique pointer to a detail implementation.
        */
        menu_base(string_type text, shortcut_key_type shortcut_key, details_ptr_type p_details)
        :
        m_text(std::move(text)),
        m_enabled(true),
        m_state(state_type::default_),
        m_shortcut_key(std::move(shortcut_key)),
        m_menu_observer_set(),
        m_p_details(std::move(p_details))
        {
            set_enabled(true);
            set_state(state_type::default_);
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
            return { empty_children().begin() };
        }

        virtual iterator begin_impl()
        {
            return { empty_children().begin() };
        }

        virtual const_iterator end_impl()
        const
        {
            return { empty_children().end() };
        }

        virtual iterator end_impl()
        {
            return { empty_children().end() };
        }

        virtual const_recursive_iterator_type recursive_begin_impl()
        const
        {
            return {};
        }

        virtual recursive_iterator_type recursive_begin_impl()
        {
            return {};
        }

        virtual const_recursive_iterator_type recursive_end_impl()
        const
        {
            return {};
        }

        virtual recursive_iterator_type recursive_end_impl()
        {
            return {};
        }

        virtual void insert_impl(const iterator offset, std::unique_ptr<menu_base> p_menu)
        {
            boost::ignore_unused(offset, p_menu);

            BOOST_THROW_EXCEPTION((std::logic_error{ "Can't insert any menus." }));
        }

        virtual void erase_impl(const iterator first, const iterator last)
        {
            boost::ignore_unused(first, last);

            BOOST_THROW_EXCEPTION((std::logic_error{ "Can't erase any menus." }));
        }


    };


}}}


#endif
