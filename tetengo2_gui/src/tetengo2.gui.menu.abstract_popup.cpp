/*! \file
    \brief The definition of tetengo2::gui::menu::abstract_popup.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/abstract_popup.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The base class for an abstract popup menu.
   */
    class abstract_popup::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = abstract_popup::string_type;

        using details_ptr_type = abstract_popup::details_ptr_type;

        using base_type = abstract_popup::base_type;

        using shortcut_key_type = abstract_popup::shortcut_key_type;

        using const_iterator = abstract_popup::const_iterator;

        using iterator = abstract_popup::iterator;

        using const_recursive_iterator_type = abstract_popup::const_recursive_iterator_type;

        using recursive_iterator_type = abstract_popup::recursive_iterator_type;


        // constructors and destructor

        impl() : m_children{} {}


        // functions

        const_iterator begin_impl() const
        {
            return { m_children.begin() };
        }

        iterator begin_impl()
        {
            return { m_children.begin() };
        }

        const_iterator end_impl() const
        {
            return { m_children.end() };
        }

        iterator end_impl()
        {
            return { m_children.end() };
        }

        const_recursive_iterator_type recursive_begin_impl(const abstract_popup& self) const
        {
            return const_recursive_iterator_type{ &self };
        }

        recursive_iterator_type recursive_begin_impl(abstract_popup& self)
        {
            return recursive_iterator_type{ &self };
        }

        const_recursive_iterator_type recursive_end_impl(const abstract_popup&) const
        {
            return const_recursive_iterator_type{};
        }

        recursive_iterator_type recursive_end_impl(abstract_popup&)
        {
            return recursive_iterator_type{};
        }

        void insert_impl(const iterator offset, std::unique_ptr<base_type> p_menu, abstract_popup& self)
        {
            if (!p_menu)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The unique pointer to a menu is nullptr." }));

            detail::gui_detail_impl_set().menu_().insert_menu(self, offset, *p_menu);

            m_children.insert(offset.base(), std::move(p_menu));
        }

        void erase_impl(const iterator first, const iterator last, abstract_popup& self)
        {
            detail::gui_detail_impl_set().menu_().erase_menus(self, first, last);

            m_children.erase(first.base(), last.base());
        }


    private:
        // variables

        std::vector<std::unique_ptr<base_type>> m_children;
    };


    abstract_popup::~abstract_popup() = default;

    abstract_popup::abstract_popup(string_type text, details_ptr_type p_details)
    : base_type{ std::move(text), std::move(p_details) }, m_p_impl{ std::make_unique<impl>() }
    {}

    abstract_popup::const_iterator abstract_popup::begin_impl() const
    {
        return m_p_impl->begin_impl();
    }

    abstract_popup::iterator abstract_popup::begin_impl()
    {
        return m_p_impl->begin_impl();
    }

    abstract_popup::const_iterator abstract_popup::end_impl() const
    {
        return m_p_impl->end_impl();
    }

    abstract_popup::iterator abstract_popup::end_impl()
    {
        return m_p_impl->end_impl();
    }

    abstract_popup::const_recursive_iterator_type abstract_popup::recursive_begin_impl() const
    {
        return m_p_impl->recursive_begin_impl(*this);
    }

    abstract_popup::recursive_iterator_type abstract_popup::recursive_begin_impl()
    {
        return m_p_impl->recursive_begin_impl(*this);
    }

    abstract_popup::const_recursive_iterator_type abstract_popup::recursive_end_impl() const
    {
        return m_p_impl->recursive_end_impl(*this);
    }

    abstract_popup::recursive_iterator_type abstract_popup::recursive_end_impl()
    {
        return m_p_impl->recursive_end_impl(*this);
    }

    void abstract_popup::insert_impl(const iterator offset, std::unique_ptr<base_type> p_menu)
    {
        m_p_impl->insert_impl(offset, std::move(p_menu), *this);
    }

    void abstract_popup::erase_impl(const iterator first, const iterator last)
    {
        m_p_impl->erase_impl(first, last, *this);
    }
}
