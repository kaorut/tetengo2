/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key_table.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SHORTCUTKEYTABLE_H)
#define TETENGO2_GUI_MENU_SHORTCUTKEYTABLE_H

#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a shortcut key table.

        \tparam ShortcutKey A shortcut key type.
        \tparam MenuBase    A menu base type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename ShortcutKey, typename MenuBase, typename MenuDetails>
    class shortcut_key_table : private boost::noncopyable
    {
    public:
        // types

        //! The virtual key type.
        using shortcut_key_type = ShortcutKey;

        //! The menu base type.
        using menu_base_type = MenuBase;

        //! The detail implementation type of a menu.
        using menu_details_type = MenuDetails;

        //! The detail implementation type.
        using details_type = typename menu_details_type::shortcut_key_table_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename menu_details_type::shortcut_key_table_details_ptr_type;

        //! The entry type.
        using entry_type = std::pair<shortcut_key_type, const menu_base_type*>;

        //! The iterator type.
        using iterator = typename std::vector<entry_type>::const_iterator;


        // constructors and destructor

        /*!
            \brief Creates an empty shortcut key table.
        */
        shortcut_key_table()
        :
        m_entries(),
        m_p_details(menu_details_type::template create_shortcut_key_table<entry_type>())
        {}

        /*!
            \brief Creates a shortcut key table.

            \tparam ForwardIterator A forward iterator type.

            \param first A first position among menus.
            \param last  A last position among menus.
        */
        template <typename ForwardIterator>
        shortcut_key_table(const ForwardIterator first, const ForwardIterator last)
        :
        m_entries(build_entries(first, last)),
        m_p_details(menu_details_type::create_shortcut_key_table(first, last))
        {}

        
        // functions

        /*!
            \brief Returns the first immutable iterator to the entries.

            \return The first immutable iterator.
        */
        iterator begin()
        const
        {
            return m_entries.begin();
        }

        /*!
            \brief Returns the last immutable iterator to the entries.

            \return The last immutable iterator.
        */
        iterator end()
        const
        {
            return m_entries.end();
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


    private:
        // static functions

        template <typename ForwardIterator>
        static std::vector<entry_type> build_entries(const ForwardIterator first, const ForwardIterator last)
        {
            std::vector<entry_type> entries{};
            entries.reserve(std::distance(first, last));

            for (ForwardIterator i = first; i != last; ++i)
            {
                if (!i->has_shortcut_key()) continue;

                entries.push_back(entry_type(i->shortcut_key(), &*i));
            }

            return entries;
        }


        // variables

        std::vector<entry_type> m_entries;

        details_ptr_type m_p_details;


    };


}}}


#endif
