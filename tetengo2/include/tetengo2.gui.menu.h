/*! \file
    \brief The definition of tetengo2::gui::menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_H)
#define TETENGO2_GUI_MENU_H

//#include <cassert>
//#include <cstddef>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/iterator/indirect_iterator.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class template for a menu.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class menu : boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The string type.
        typedef typename traits_type::string_type string_type;

        //! The encoder type.
        typedef typename traits_type::encoder_type encoder_type;

        //! The menu observer set type.
        typedef
            typename traits_type::menu_observer_set_type
            menu_observer_set_type;

        //! The const iterator type.
        typedef
            boost::indirect_iterator<
                typename std::vector<
                    typename cpp0x::unique_ptr<menu>::type
                >::const_iterator
            >
            const_iterator;

        //! The iterator type.
        typedef
            boost::indirect_iterator<
                typename std::vector<
                    typename cpp0x::unique_ptr<menu>::type
                >::iterator
            >
            iterator;

        //! The const recursive iterator type.
        typedef recursive_menu_iterator<const menu> const_recursive_iterator;

        //! The recursive iterator type.
        typedef recursive_menu_iterator<menu> recursive_iterator;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The detail implementation type.
        typedef typename menu_details_type::menu_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename menu_details_type::menu_details_ptr_type
            details_ptr_type;

        //! The style type.
        typedef typename menu_details_type::style_tag style_type;


        // constructors and destructor

        /*!
            \brief Destroys the menu.
        */
        virtual ~menu()
        TETENGO2_CPP0X_NOEXCEPT
        {}


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
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<const details_type&> details()
        const
        {
            return boost::make_optional<const details_type&>(
                static_cast<bool>(m_p_details), *m_p_details
            );
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        boost::optional<details_type&> details()
        {
            return boost::make_optional<details_type&>(
                static_cast<bool>(m_p_details), *m_p_details
            );
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a menu.

            \tparam S A string type.

            \param text      A text.
            \param p_details A unique pointer to a detail implementation.
        */
        template <typename S>
        menu(S&& text, details_ptr_type p_details)
        :
        m_text(std::forward<S>(text)),
        m_menu_observer_set(),
        m_p_details(std::move(p_details))
        {}


    private:
        // static functions

        static std::vector<typename cpp0x::unique_ptr<menu>::type>&
        empty_children()
        {
            static std::vector<typename cpp0x::unique_ptr<menu>::type>
            singleton;
            assert(singleton.empty());
            return singleton;
        }


        // variables

        string_type m_text;

        menu_observer_set_type m_menu_observer_set;

        const details_ptr_type m_p_details;


        // virtual functions

        virtual const style_type& style_impl()
        const = 0;

        virtual const_iterator begin_impl()
        const
        {
            return const_iterator(empty_children().begin());
        }

        virtual iterator begin_impl()
        {
            return iterator(empty_children().begin());
        }

        virtual const_iterator end_impl()
        const
        {
            return const_iterator(empty_children().end());
        }

        virtual iterator end_impl()
        {
            return iterator(empty_children().end());
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


}}


#endif
