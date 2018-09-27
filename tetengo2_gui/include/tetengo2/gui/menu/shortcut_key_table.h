/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key_table.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SHORTCUTKEYTABLE_H)
#define TETENGO2_GUI_MENU_SHORTCUTKEYTABLE_H

#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/shortcut_key.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The class for a shortcut key table.
   */
    class shortcut_key_table : private boost::noncopyable
    {
    public:
        // types

        //! The details type.
        using details_type = detail::base::menu::shortcut_key_table_details_type;

        //! The virtual key type.
        using shortcut_key_type = shortcut_key;

        //! The menu base type.
        using menu_base_type = menu_base;

        //! The entry type.
        using entry_type = std::pair<shortcut_key_type, const menu_base_type*>;

        //! The iterator type.
        using iterator = typename std::vector<entry_type>::const_iterator;


        // constructors and destructor

        /*!
            \brief Creates an empty shortcut key table.
        */
        shortcut_key_table();

        /*!
            \brief Creates a shortcut key table.

            \param root_menu A root menu.
        */
        shortcut_key_table(const menu_base_type& root_menu);

        /*!
            \brief Destroys the shortcut key table.
        */
        ~shortcut_key_table();


        // functions

        /*!
            \brief Returns the first immutable iterator to the entries.

            \return The first immutable iterator.
        */
        iterator begin() const;

        /*!
            \brief Returns the last immutable iterator to the entries.

            \return The last immutable iterator.
        */
        iterator end() const;

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


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
