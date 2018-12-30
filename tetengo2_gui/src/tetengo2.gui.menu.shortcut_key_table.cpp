/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key_table.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <iterator>
#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/recursive_iterator.h>
#include <tetengo2/gui/menu/shortcut_key_table.h>


namespace tetengo2::gui::menu {
    class shortcut_key_table::impl : private boost::noncopyable
    {
    public:
        // types

        using details_type = shortcut_key_table::details_type;

        using menu_base_type = shortcut_key_table::menu_base_type;

        using iterator = shortcut_key_table::iterator;


        // constructors and destructor

        impl() : m_entries{}, m_p_details{ detail::gui_detail_impl_set().menu_().create_shortcut_key_table() } {}

        impl(const menu_base_type& root_menu)
        : m_entries{ build_entries(root_menu.recursive_begin(), root_menu.recursive_end()) }, m_p_details{
              detail::gui_detail_impl_set().menu_().create_shortcut_key_table(root_menu)
          }
        {}


        // functions

        iterator begin() const
        {
            return m_entries.begin();
        }

        iterator end() const
        {
            return m_entries.end();
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


    private:
        // types

        using details_ptr_type = detail::base::menu::shortcut_key_table_details_ptr_type;

        using entry_type = shortcut_key_table::entry_type;


        // static functions

        template <typename ForwardIterator>
        static std::vector<entry_type> build_entries(const ForwardIterator first, const ForwardIterator last)
        {
            std::vector<entry_type> entries{};
            entries.reserve(std::distance(first, last));

            for (ForwardIterator i = first; i != last; ++i)
            {
                if (!i->has_shortcut_key())
                    continue;

                entries.emplace_back(i->get_shortcut_key(), &*i);
            }

            return entries;
        }


        // variables

        std::vector<entry_type> m_entries;

        details_ptr_type m_p_details;
    };


    shortcut_key_table::shortcut_key_table() : m_p_impl{ std::make_unique<impl>() } {}

    shortcut_key_table::shortcut_key_table(const menu_base_type& root_menu)
    : m_p_impl{ std::make_unique<impl>(root_menu) }
    {}

    shortcut_key_table::~shortcut_key_table() = default;

    shortcut_key_table::iterator shortcut_key_table::begin() const
    {
        return m_p_impl->begin();
    }

    shortcut_key_table::iterator shortcut_key_table::end() const
    {
        return m_p_impl->end();
    }

    const shortcut_key_table::details_type& shortcut_key_table::details() const
    {
        return m_p_impl->details();
    }

    shortcut_key_table::details_type& shortcut_key_table::details()
    {
        return m_p_impl->details();
    }
}
