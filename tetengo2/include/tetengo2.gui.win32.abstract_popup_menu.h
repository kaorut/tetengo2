/*! \file
    \brief The definition of tetengo2::gui::win32::abstract_popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ABSTRACTPOPUPMENU_H)
#define TETENGO2_GUI_WIN32_ABSTRACTPOPUPMENU_H

#include <algorithm>
//#include <cstddef>
#include <cstring>
//#include <iterator>
//#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/throw_exception.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.Menu.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a abstract_popup_menu.

        \tparam Menu A menu type. It must conform to
                     concept_tetengo2::gui::Menu<Menu>
   */
    template <typename Menu>
    class abstract_popup_menu : public Menu
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Menu<Menu, Menu>));


    public:
        // types

        //! \return The base type.
        typedef Menu base_type;

        //! \copydoc tetengo2::gui::win32::menu::id_type
        typedef typename base_type::id_type id_type;

        //! \copydoc tetengo2::gui::win32::menu::handle_type
        typedef typename base_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::menu::string_type
        typedef typename base_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::menu::encoder_type
        typedef typename base_type::encoder_type encoder_type;

        //! \copydoc tetengo2::gui::win32::menu::menu_observer_type
        typedef typename base_type::menu_observer_type menu_observer_type;

        //! \copydoc tetengo2::gui::win32::menu::iterator
        typedef typename base_type::iterator iterator;

        //! \copydoc tetengo2::gui::win32::menu::const_iterator
        typedef typename base_type::const_iterator const_iterator;

        //! \copydoc tetengo2::gui::win32::menu::recursive_iterator
        typedef typename base_type::recursive_iterator recursive_iterator;

        //! \copydoc tetengo2::gui::win32::menu::const_recursive_iterator
        typedef
            typename base_type::const_recursive_iterator
            const_recursive_iterator;


        // constructors and destructor

        /*!
            \brief Destroys the abstract_popup_menu.
        */
        virtual ~abstract_popup_menu()
        throw ()
        {
            if (::IsMenu(m_handle) != 0)
                ::DestroyMenu(m_handle);
        }


        // functions

        /*!
            \brief Returns the handle.

            \return The handle. It may be NULL.
        */
        virtual handle_type handle()
        const
        {
            return m_handle;
        }

        /*!
            \brief Returns the first immutable iterator to the children.

            \return The first immutable iterator.
        */
        virtual const_iterator begin()
        const
        {
            return m_children.begin();
        }

        /*!
            \brief Returns the first mutable iterator to the children.

            \return The first mutable iterator.
        */
        virtual iterator begin()
        {
            return m_children.begin();
        }

        /*!
            \brief Returns the last immutable iterator to the children.

            \return The last immutable iterator.
        */
        virtual const_iterator end()
        const
        {
            return m_children.end();
        }

        /*!
            \brief Returns the last mutable iterator to the children.

            \return The last mutable iterator.
        */
        virtual iterator end()
        {
            return m_children.end();
        }

        /*!
            \brief Returns the recursive first immutable iterator to this menu
                   and the children.

            The first iterator points to this abstract_popup_menu.

            \return The recursive first immutable iterator.
        */
        virtual const_recursive_iterator recursive_begin()
        const
        {
            return const_recursive_iterator(this);
        }

        /*!
            \brief Returns the recursive first mutable iterator to this menu
                   and the children.

            The first iterator points to this abstract_popup_menu.

            \return The recursive first mutable iterator.
        */
        virtual recursive_iterator recursive_begin()
        {
            return recursive_iterator(this);
        }

        /*!
            \brief Returns the recursive last immutable iterator to this menu
                   and the children.

            \return The recursive last immutable iterator.
        */
        virtual const_recursive_iterator recursive_end()
        const
        {
            return const_recursive_iterator();
        }

        /*!
            \brief Returns the recursive last mutable iterator to this menu
                   and the children.

            \return The recursive last mutable iterator.
        */
        virtual recursive_iterator recursive_end()
        {
            return recursive_iterator();
        }

        /*!
            \brief Inserts a menu as a child.

            \param offset An offset where a menu is inserted.
            \param p_menu An auto pointer to a menu. It must not be NULL.
        */
        virtual void insert(
            const iterator           offset,
            std::auto_ptr<base_type> p_menu
        )
        {
            if (p_menu.get() == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The auto pointer to a menu is NULL."
                    )
                );
            }

            insert_native_menu(offset, *p_menu);

            m_children.insert(offset, p_menu);
        }

        /*!
            \brief Erases the menus from the children.

            \param first The first iterator to the erased menus.
            \param last  The last iterator to the eraed menus.
        */
        virtual void erase(const iterator first, const iterator last)
        {
            erase_native_menus(first, last);

            m_children.erase(first, last);
        }


    protected:
        // constructors

        /*!
            \brief Creates a abstract_popup_menu.

            \param handle  A handle.
            \param text    A text.
        */
        abstract_popup_menu(const handle_type handle, const string_type& text)
        :
        base_type(text),
        m_handle(handle),
        m_children()
        {}


    private:
        // variables

        handle_type m_handle;

        boost::ptr_vector<base_type> m_children;


        // functions

        std::vector< ::WCHAR> duplicate_text(const string_type& text)
        const
        {
            const std::wstring native_string = encoder().encode(text);

            std::vector< ::WCHAR> duplicated;
            duplicated.reserve(native_string.length() + 1);
            std::copy(
                native_string.begin(),
                native_string.end(),
                std::back_inserter(duplicated)
            );
            duplicated.push_back(L'\0');

            return duplicated;
        }

        void insert_native_menu(const const_iterator offset, base_type& menu)
        const
        {
            ::MENUITEMINFOW menu_info;
            std::memset(&menu_info, 0, sizeof(::MENUITEMINFO));
            menu_info.cbSize = sizeof(::MENUITEMINFO);
            std::vector< ::WCHAR> duplicated_text =
                duplicate_text(menu.text());
            menu.set_menu_info(menu_info, duplicated_text);

            const ::BOOL result = ::InsertMenuItem(
                m_handle,
                static_cast< ::UINT>(
                    std::distance(m_children.begin(), offset)
                ),
                TRUE,
                &menu_info
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't insert a native menu.")
                );
            }
        }

        void erase_native_menus(const_iterator first, const_iterator last)
        const
        {
            for (const_iterator i = first; i != last; ++i)
                erase_native_menu(i);
        }

        void erase_native_menu(const_iterator offset)
        const
        {
            ::RemoveMenu(
                m_handle,
                static_cast< ::UINT>(
                    std::distance(m_children.begin(), offset)
                ),
                MF_BYPOSITION
            );
        }


    };


}}}

#endif
