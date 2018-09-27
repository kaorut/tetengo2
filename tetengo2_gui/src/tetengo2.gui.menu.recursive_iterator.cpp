/*! \file
    \brief The definition of tetengo2::gui::menu::recursive_iterator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <iterator>
#include <memory>
#include <stack>
#include <utility>

#include <tetengo2/gui/menu/menu_base.h> // IWYU pragma: keep
#include <tetengo2/gui/menu/recursive_iterator.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    template <typename MenuBase>
    class recursive_iterator<MenuBase>::impl
    {
    public:
        // types

        using menu_base_type = recursive_iterator<MenuBase>::menu_base_type;


        // constructors and destructor

        impl() : m_p_menu{ nullptr }, m_parents{}
        {
            m_parents.emplace(nullptr, 0);
        }

        explicit impl(menu_base_type* const p_menu) : m_p_menu{ p_menu }, m_parents{}
        {
            m_parents.emplace(nullptr, 0);
        }


        // functions

        recursive_iterator& operator_assign(const recursive_iterator& another, recursive_iterator& self)
        {
            impl temp{ *another.m_p_impl };
            *this = std::move(temp);
            return self;
        }

        recursive_iterator& operator_assign(recursive_iterator&& another, recursive_iterator& self)
        {
            *this = std::move(*another.m_p_impl);
            return self;
        }

        menu_base_type& dereference() const
        {
            return *m_p_menu;
        }

        bool equal(const recursive_iterator& another) const
        {
            return m_p_menu == another.m_p_impl->m_p_menu;
        }

        void increment()
        {
            assert(m_p_menu);

            if (m_parents.top().second < std::distance(m_p_menu->begin(), m_p_menu->end()))
            {
                const auto index = m_parents.top().second;
                m_parents.emplace(m_p_menu, 0);
                m_p_menu = &*std::next(m_p_menu->begin(), index);
                return;
            }

            if (!m_parents.top().first)
            {
                m_p_menu = nullptr;
                return;
            }

            m_p_menu = m_parents.top().first;
            m_parents.pop();
            ++m_parents.top().second;
            increment();
        }


    private:
        // types

        using menu_difference_type = tetengo2::type_list::difference_type;

        using parent_and_index_type = std::pair<menu_base_type*, menu_difference_type>;


        // variables

        menu_base_type* m_p_menu;

        std::stack<parent_and_index_type> m_parents;
    };


    template <typename MenuBase>
    recursive_iterator<MenuBase>::recursive_iterator() : m_p_impl{ std::make_unique<impl>() }
    {}

    template <typename MenuBase>
    recursive_iterator<MenuBase>::recursive_iterator(menu_base_type* const p_menu)
    : m_p_impl{ std::make_unique<impl>(p_menu) }
    {}

    template <typename MenuBase>
    recursive_iterator<MenuBase>::recursive_iterator(const recursive_iterator<MenuBase>& another)
    : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) }
    {}

    template <typename MenuBase>
    recursive_iterator<MenuBase>::recursive_iterator(recursive_iterator<MenuBase>&& another)
    : m_p_impl{ std::make_unique<impl>(std::move(*another.m_p_impl)) }
    {}

    template <typename MenuBase>
    recursive_iterator<MenuBase>::~recursive_iterator() = default;

    template <typename MenuBase>
    recursive_iterator<MenuBase>& recursive_iterator<MenuBase>::operator=(const recursive_iterator<MenuBase>& another)
    {
        return m_p_impl->operator_assign(another, *this);
    }

    template <typename MenuBase>
    recursive_iterator<MenuBase>& recursive_iterator<MenuBase>::operator=(recursive_iterator<MenuBase>&& another)
    {
        return m_p_impl->operator_assign(std::move(another), *this);
    }

    template <typename MenuBase>
    typename recursive_iterator<MenuBase>::menu_base_type& recursive_iterator<MenuBase>::dereference() const
    {
        return m_p_impl->dereference();
    }

    template <typename MenuBase>
    bool recursive_iterator<MenuBase>::equal(const recursive_iterator<MenuBase>& another) const
    {
        return m_p_impl->equal(another);
    }

    template <typename MenuBase>
    void recursive_iterator<MenuBase>::increment()
    {
        m_p_impl->increment();
    }


    template class recursive_iterator<const menu_base>;

    template class recursive_iterator<menu_base>;
}
