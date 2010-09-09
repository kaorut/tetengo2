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
//#include <stdexcept>
#include <string>
//#include <vector>

//#include <boost/throw_exception.hpp>
//#include <boost/ptr_container/ptr_vector.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.menu.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a abstract_popup_menu.

        \tparam Traits A traits type.
   */
    template <typename Traits>
    class abstract_popup_menu : public menu<Traits>
    {
    public:
        // types

        //! \return The traits type.
        typedef Traits traits_type;

        //! \return The base type.
        typedef menu<traits_type> base_type;


        // constructors and destructor

        /*!
            \brief Destroys the abstract_popup_menu.
        */
        virtual ~abstract_popup_menu()
        TETENGO2_NOEXCEPT
        {
            if (::IsMenu(m_handle) != 0)
                ::DestroyMenu(m_handle);
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


        // virtual functions

        virtual handle_type handle_impl()
        const
        {
            return m_handle;
        }

        virtual const_iterator begin_impl()
        const
        {
            return m_children.begin();
        }

        virtual iterator begin_impl()
        {
            return m_children.begin();
        }

        virtual const_iterator end_impl()
        const
        {
            return m_children.end();
        }

        virtual iterator end_impl()
        {
            return m_children.end();
        }

        virtual const_recursive_iterator recursive_begin_impl()
        const
        {
            return const_recursive_iterator(this);
        }

        virtual recursive_iterator recursive_begin_impl()
        {
            return recursive_iterator(this);
        }

        virtual const_recursive_iterator recursive_end_impl()
        const
        {
            return const_recursive_iterator();
        }

        virtual recursive_iterator recursive_end_impl()
        {
            return recursive_iterator();
        }

        virtual void insert_impl(
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

        virtual void erase_impl(const iterator first, const iterator last)
        {
            erase_native_menus(first, last);

            m_children.erase(first, last);
        }


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
