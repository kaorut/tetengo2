/*! \file
    \brief The definition of tetengo2::gui::win32::menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENU_H)
#define TETENGO2_GUI_WIN32_MENU_H

//#include <cassert>
//#include <cstddef>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a menu.

        \tparam Traits A traits type.
   */
    template <typename Traits>
    class menu : boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The ID type.
        typedef typename traits_type::id_type id_type;

        //! The handle type.
        typedef typename traits_type::handle_type handle_type;

        //! The string type.
        typedef typename traits_type::string_type string_type;

        //! The encoder type.
        typedef typename traits_type::encoder_type encoder_type;

        //! The menu observer set type.
        typedef
            typename traits_type::menu_observer_set_type
            menu_observer_set_type;

        //! The iterator type.
        typedef typename boost::ptr_vector<menu>::iterator iterator;

        //! The const iterator type.
        typedef
            typename boost::ptr_vector<menu>::const_iterator const_iterator;

        //! The recursive iterator type.
        typedef recursive_menu_iterator<menu> recursive_iterator;

        //! The const recursive iterator type.
        typedef recursive_menu_iterator<const menu> const_recursive_iterator;


        // constructors and destructor

        /*!
            \brief Destroys the menu.
        */
        virtual ~menu()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the ID.

            \return The ID.
        */
        id_type id()
        const
        {
            return m_id;
        }

        /*!
            \brief Returns the handle.

            \return Always NULL.
        */
        handle_type handle()
        const
        {
            return handle_impl();
        }

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
            \brief Returns the recursive first immutable iterator to this menu
                   and the children.

            The first iterator points to this menu.

            \return The recursive first immutable iterator.
        */
        const_recursive_iterator recursive_begin()
        const
        {
            return recursive_begin_impl();
        }

        /*!
            \brief Returns the recursive first mutable iterator to this menu
                   and the children.

            The first iterator points to this menu.

            \return The recursive first mutable iterator.
        */
        recursive_iterator recursive_begin()
        {
            return recursive_begin_impl();
        }

        /*!
            \brief Returns the recursive last immutable iterator to this menu
                   and the children.

            \return The recursive last immutable iterator.
        */
        const_recursive_iterator recursive_end()
        const
        {
            return recursive_end_impl();
        }

        /*!
            \brief Returns the recursive last mutable iterator to this menu
                   and the children.

            \return The recursive last mutable iterator.
        */
        recursive_iterator recursive_end()
        {
            return recursive_end_impl();
        }

        /*!
            \brief Inserts a menu as a child.

            \param offset An offset where a menu is inserted.
            \param p_menu A unique pointer to a menu. It must not be NULL.
        */
        void insert(
            const iterator                         offset,
            typename cpp0x::unique_ptr<menu>::type p_menu
        )
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
            \brief Sets the Win32 menu information.

            \param menu_info       A menu information.
            \param duplicated_text A duplicated text.
        */
        void set_menu_info(
            ::MENUITEMINFOW&       menu_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const
        {
            set_menu_info_impl(menu_info, duplicated_text);
        }


    protected:
        // static functions

        /*!
            \brief Returns the encoder.

            \return The encoder.
        */
        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // constructors

        /*!
            \brief Creates a menu.

            \tparam S A string type.

            \param text A text.
        */
        template <typename S>
        explicit menu(S&& text)
        :
        m_id(get_and_increment_id()),
        m_text(std::forward<S>(text)),
        m_menu_observer_set()
        {}


    private:
        // static functions

        static id_type get_and_increment_id()
        {
            static id_type id = 40001;

            return id++;
        }

        static boost::ptr_vector<menu>& empty_children()
        {
            static boost::ptr_vector<menu> singleton;
            assert(singleton.empty());
            return singleton;
        }


        // variables

        id_type m_id;

        string_type m_text;

        menu_observer_set_type m_menu_observer_set;


        // virtual functions

        virtual handle_type handle_impl()
        const
        {
            return NULL;
        }

        virtual void set_menu_info_impl(
            ::MENUITEMINFOW&       menu_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const = 0;

        virtual const_iterator begin_impl()
        const
        {
            return empty_children().begin();
        }

        virtual iterator begin_impl()
        {
            return empty_children().begin();
        }

        virtual const_iterator end_impl()
        const
        {
            return empty_children().end();
        }

        virtual iterator end_impl()
        {
            return empty_children().end();
        }

        virtual const_recursive_iterator recursive_begin_impl()
        const
        {
            return const_recursive_iterator();
        }

        virtual recursive_iterator recursive_begin_impl()
        {
            return recursive_iterator();
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
            const iterator                         offset,
            typename cpp0x::unique_ptr<menu>::type p_menu
        )
        {
            assert(false);
            BOOST_THROW_EXCEPTION(
                std::logic_error("Can't insert any menus.")
            );
        }

        virtual void erase_impl(const iterator first, const iterator last)
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error("Can't erase any menus."));
        }


    };


}}}

#endif
