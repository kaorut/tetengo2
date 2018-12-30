/*! \file
    \brief The definition of tetengo2::gui::menu::menu_base.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/message/menu_observer_set.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The base class for a menu base.
   */
    class menu_base::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = menu_base::string_type;

        using details_type = menu_base::details_type;

        using details_ptr_type = menu_base::details_ptr_type;

        using shortcut_key_type = menu_base::shortcut_key_type;

        using menu_observer_set_type = menu_base::menu_observer_set_type;

        using const_iterator = menu_base::const_iterator;

        using iterator = menu_base::iterator;

        using const_recursive_iterator_type = menu_base::const_recursive_iterator_type;

        using recursive_iterator_type = menu_base::recursive_iterator_type;

        using style_type = menu_base::style_type;

        using state_type = menu_base::state_type;


        // constructors and destructor

        impl(string_type text, details_ptr_type p_details)
        : m_text{ std::move(text) }, m_enabled{ true }, m_state{ state_type::default_ }, m_shortcut_key{},
          m_menu_observer_set{}, m_p_details{ std::move(p_details) }
        {}

        impl(string_type text, shortcut_key_type shortcut_key, details_ptr_type p_details)
        : m_text{ std::move(text) }, m_enabled{ true }, m_state{ state_type::default_ },
          m_shortcut_key{ std::move(shortcut_key) }, m_menu_observer_set{}, m_p_details{ std::move(p_details) }
        {}


        // functions

        const string_type& text() const
        {
            return m_text;
        }

        const style_type& style(const menu_base& self) const
        {
            return self.style_impl();
        }

        bool enabled() const
        {
            return m_enabled;
        }

        void set_enabled(const bool enabled, menu_base& self)
        {
            detail::gui_detail_impl_set().menu_().set_enabled(self, enabled);
            m_enabled = enabled;
        }

        state_type state() const
        {
            return m_state;
        }

        void set_state(const state_type state, menu_base& self)
        {
            detail::gui_detail_impl_set().menu_().set_state(self, static_cast<detail::base::menu::state_type>(state));
            m_state = state;
        }

        bool has_shortcut_key() const
        {
            return static_cast<bool>(m_shortcut_key);
        }

        const shortcut_key_type& get_shortcut_key() const
        {
            if (!has_shortcut_key())
                BOOST_THROW_EXCEPTION((std::logic_error{ "This menu has no shortcut key." }));

            return *m_shortcut_key;
        }

        void select()
        {
            m_menu_observer_set.selected()();
        }

        const menu_observer_set_type& menu_observer_set() const
        {
            return m_menu_observer_set;
        }

        menu_observer_set_type& menu_observer_set()
        {
            return m_menu_observer_set;
        }

        const_iterator begin(const menu_base& self) const
        {
            return self.begin_impl();
        }

        iterator begin(menu_base& self)
        {
            return self.begin_impl();
        }

        const_iterator end(const menu_base& self) const
        {
            return self.end_impl();
        }

        iterator end(menu_base& self)
        {
            return self.end_impl();
        }

        const_recursive_iterator_type recursive_begin(const menu_base& self) const
        {
            return self.recursive_begin_impl();
        }

        recursive_iterator_type recursive_begin(menu_base& self)
        {
            return self.recursive_begin_impl();
        }

        const_recursive_iterator_type recursive_end(const menu_base& self) const
        {
            return self.recursive_end_impl();
        }

        recursive_iterator_type recursive_end(menu_base& self)
        {
            return self.recursive_end_impl();
        }

        void insert(const iterator offset, std::unique_ptr<menu_base> p_menu, menu_base& self)
        {
            self.insert_impl(offset, std::move(p_menu));
        }

        void erase(const iterator first, const iterator last, menu_base& self)
        {
            self.erase_impl(first, last);
        }

        const details_type& details() const
        {
            assert(m_p_details);
            return *m_p_details;
        }

        details_type& details()
        {
            assert(m_p_details);
            return *m_p_details;
        }

        const_iterator begin_impl() const
        {
            return const_iterator{ empty_children().begin() };
        }

        iterator begin_impl()
        {
            return iterator{ empty_children().begin() };
        }

        const_iterator end_impl() const
        {
            return const_iterator{ empty_children().end() };
        }

        iterator end_impl()
        {
            return iterator{ empty_children().end() };
        }

        const_recursive_iterator_type recursive_begin_impl(const menu_base&) const
        {
            return const_recursive_iterator_type{};
        }

        recursive_iterator_type recursive_begin_impl(menu_base&)
        {
            return recursive_iterator_type{};
        }

        const_recursive_iterator_type recursive_end_impl(const menu_base&) const
        {
            return const_recursive_iterator_type{};
        }

        recursive_iterator_type recursive_end_impl(menu_base&)
        {
            return recursive_iterator_type{};
        }

        void insert_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const iterator offset,
            TETENGO2_STDALT_MAYBE_UNUSED std::unique_ptr<menu_base> p_menu)
        {
            BOOST_THROW_EXCEPTION((std::logic_error{ "Can't insert any menus." }));
        }

        void
        erase_impl(TETENGO2_STDALT_MAYBE_UNUSED const iterator first, TETENGO2_STDALT_MAYBE_UNUSED const iterator last)
        {
            BOOST_THROW_EXCEPTION((std::logic_error{ "Can't erase any menus." }));
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

        const tetengo2::stdalt::optional<shortcut_key_type> m_shortcut_key;

        menu_observer_set_type m_menu_observer_set;

        const details_ptr_type m_p_details;
    };


    menu_base::~menu_base() = default;

    const menu_base::string_type& menu_base::text() const
    {
        return m_p_impl->text();
    }

    const menu_base::style_type& menu_base::style() const
    {
        return m_p_impl->style(*this);
    }

    bool menu_base::enabled() const
    {
        return m_p_impl->enabled();
    }

    void menu_base::set_enabled(const bool enabled)
    {
        m_p_impl->set_enabled(enabled, *this);
    }

    menu_base::state_type menu_base::state() const
    {
        return m_p_impl->state();
    }

    void menu_base::set_state(const state_type state)
    {
        m_p_impl->set_state(state, *this);
    }

    bool menu_base::has_shortcut_key() const
    {
        return m_p_impl->has_shortcut_key();
    }

    const menu_base::shortcut_key_type& menu_base::get_shortcut_key() const
    {
        return m_p_impl->get_shortcut_key();
    }

    void menu_base::select()
    {
        m_p_impl->select();
    }

    const menu_base::menu_observer_set_type& menu_base::menu_observer_set() const
    {
        return m_p_impl->menu_observer_set();
    }

    menu_base::menu_observer_set_type& menu_base::menu_observer_set()
    {
        return m_p_impl->menu_observer_set();
    }

    menu_base::const_iterator menu_base::begin() const
    {
        return m_p_impl->begin(*this);
    }

    menu_base::iterator menu_base::begin()
    {
        return m_p_impl->begin(*this);
    }

    menu_base::const_iterator menu_base::end() const
    {
        return m_p_impl->end(*this);
    }

    menu_base::iterator menu_base::end()
    {
        return m_p_impl->end(*this);
    }

    menu_base::const_recursive_iterator_type menu_base::recursive_begin() const
    {
        return m_p_impl->recursive_begin(*this);
    }

    menu_base::recursive_iterator_type menu_base::recursive_begin()
    {
        return m_p_impl->recursive_begin(*this);
    }

    menu_base::const_recursive_iterator_type menu_base::recursive_end() const
    {
        return m_p_impl->recursive_end(*this);
    }

    menu_base::recursive_iterator_type menu_base::recursive_end()
    {
        return m_p_impl->recursive_end(*this);
    }

    void menu_base::insert(const iterator offset, std::unique_ptr<menu_base> p_menu)
    {
        m_p_impl->insert(offset, std::move(p_menu), *this);
    }

    void menu_base::erase(const iterator first, const iterator last)
    {
        m_p_impl->erase(first, last, *this);
    }

    const menu_base::details_type& menu_base::details() const
    {
        return m_p_impl->details();
    }

    menu_base::details_type& menu_base::details()
    {
        return m_p_impl->details();
    }

    menu_base::menu_base(string_type text, details_ptr_type p_details)
    : m_p_impl{ std::make_unique<impl>(std::move(text), std::move(p_details)) }
    {
        detail::gui_detail_impl_set().menu_().set_enabled(*this, m_p_impl->enabled());
        detail::gui_detail_impl_set().menu_().set_state(
            *this, static_cast<detail::base::menu::state_type>(m_p_impl->state()));
    }

    menu_base::menu_base(string_type text, shortcut_key_type shortcut_key, details_ptr_type p_details)
    : m_p_impl{ std::make_unique<impl>(std::move(text), std::move(shortcut_key), std::move(p_details)) }
    {
        detail::gui_detail_impl_set().menu_().set_enabled(*this, m_p_impl->enabled());
        detail::gui_detail_impl_set().menu_().set_state(
            *this, static_cast<detail::base::menu::state_type>(m_p_impl->state()));
    }

    menu_base::const_iterator menu_base::begin_impl() const
    {
        return m_p_impl->begin_impl();
    }

    menu_base::iterator menu_base::begin_impl()
    {
        return m_p_impl->begin_impl();
    }

    menu_base::const_iterator menu_base::end_impl() const
    {
        return m_p_impl->end_impl();
    }

    menu_base::iterator menu_base::end_impl()
    {
        return m_p_impl->end_impl();
    }

    menu_base::const_recursive_iterator_type menu_base::recursive_begin_impl() const
    {
        return m_p_impl->recursive_begin_impl(*this);
    }

    menu_base::recursive_iterator_type menu_base::recursive_begin_impl()
    {
        return m_p_impl->recursive_begin_impl(*this);
    }

    menu_base::const_recursive_iterator_type menu_base::recursive_end_impl() const
    {
        return m_p_impl->recursive_end_impl(*this);
    }

    menu_base::recursive_iterator_type menu_base::recursive_end_impl()
    {
        return m_p_impl->recursive_end_impl(*this);
    }

    void menu_base::insert_impl(const iterator offset, std::unique_ptr<menu_base> p_menu)
    {
        m_p_impl->insert_impl(offset, std::move(p_menu));
    }

    void menu_base::erase_impl(const iterator first, const iterator last)
    {
        m_p_impl->erase_impl(first, last);
    }
}