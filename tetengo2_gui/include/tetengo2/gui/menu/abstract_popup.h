/*! \file
    \brief The definition of tetengo2::gui::menu::abstract_popup.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_ABSTRACTPOPUP_H)
#define TETENGO2_GUI_MENU_ABSTRACTPOPUP_H

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/iterator/indirect_iterator.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::menu {
    /*!
        \brief The base class for an abstract popup menu.
   */
    class abstract_popup : public menu_base
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The menu details type.
        using menu_details_type = detail::stub::menu;

        //! The details type.
        using details_type = typename menu_details_type::menu_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename menu_details_type::menu_details_ptr_type;

        //! The base type.
        using base_type = menu_base;

        //! The shortcut key type.
        using shortcut_key_type = typename base_type::shortcut_key_type;

        //! The const iterator type.
        using const_iterator = typename base_type::const_iterator;

        //! The iterator type.
        using iterator = typename base_type::iterator;

        //! The const recursive iterator type.
        using const_recursive_iterator_type = typename base_type::const_recursive_iterator_type;

        //! The recursive iterator type.
        using recursive_iterator_type = typename base_type::recursive_iterator_type;


    protected:
        // constructors and destructor

        /*!
            \brief Creates an abstract popup menu.

            \param text      A text.
            \param p_details A unique pointer to a detail implementation.
        */
        abstract_popup(string_type text, details_ptr_type p_details)
        : base_type{ std::move(text), std::move(p_details) }, m_children{}
        {}

        /*!
            \brief Destroys the abstract_popup.
        */
        virtual ~abstract_popup() = default;


    private:
        // variables

        std::vector<std::unique_ptr<base_type>> m_children;


        // virtual functions

        virtual const_iterator begin_impl() const override
        {
            return { m_children.begin() };
        }

        virtual iterator begin_impl() override
        {
            return { m_children.begin() };
        }

        virtual const_iterator end_impl() const override
        {
            return { m_children.end() };
        }

        virtual iterator end_impl() override
        {
            return { m_children.end() };
        }

        virtual const_recursive_iterator_type recursive_begin_impl() const override
        {
            return const_recursive_iterator_type{ this };
        }

        virtual recursive_iterator_type recursive_begin_impl() override
        {
            return recursive_iterator_type{ this };
        }

        virtual const_recursive_iterator_type recursive_end_impl() const override
        {
            return {};
        }

        virtual recursive_iterator_type recursive_end_impl() override
        {
            return {};
        }

        virtual void insert_impl(const iterator offset, std::unique_ptr<base_type> p_menu) override
        {
            if (!p_menu)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The unique pointer to a menu is nullptr." }));

            menu_details_type::insert_menu(*this, offset, *p_menu);

            m_children.insert(offset.base(), std::move(p_menu));
        }

        virtual void erase_impl(const iterator first, const iterator last) override
        {
            menu_details_type::erase_menus(*this, first, last);

            m_children.erase(first.base(), last.base());
        }
    };
}


#endif
