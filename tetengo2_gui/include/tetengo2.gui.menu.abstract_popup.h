/*! \file
    \brief The definition of tetengo2::gui::menu::abstract_popup.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_ABSTRACTPOPUP_H)
#define TETENGO2_GUI_MENU_ABSTRACTPOPUP_H

#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/throw_exception.hpp>

#include "tetengo2.gui.menu.menu_base.h"
#include "tetengo2.gui.menu.recursive_iterator.h"
#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The base class template for an abstract popup menu.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class abstract_popup : public menu_base<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef menu_base<traits_type, menu_details_type> base_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The shortcut key type.
        typedef typename base_type::shortcut_key_type shortcut_key_type;

        //! The const iterator type.
        typedef typename base_type::const_iterator const_iterator;

        //! The iterator type.
        typedef typename base_type::iterator iterator;

        //! The const recursive iterator type.
        typedef typename base_type::const_recursive_iterator_type const_recursive_iterator_type;

        //! The recursive iterator type.
        typedef typename base_type::recursive_iterator_type recursive_iterator_type;

        //! The detail implementation type.
        typedef typename menu_details_type::menu_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename menu_details_type::menu_details_ptr_type details_ptr_type;


    protected:
        // constructors and destructor

        /*!
            \brief Creates an abstract popup menu.

            \param text      A text.
            \param p_details A unique pointer to a detail implementation.
        */
        abstract_popup(string_type text, details_ptr_type p_details)
        :
        base_type(std::move(text), std::move(p_details)),
        m_children()
        {}

        /*!
            \brief Destroys the abstract_popup.
        */
        virtual ~abstract_popup()
        TETENGO2_STDALT_NOEXCEPT = default;


    private:
        // types

        typedef typename traits_type::encoder_type encoder_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        std::vector<std::unique_ptr<base_type>> m_children;


        // virtual functions

        virtual const_iterator begin_impl()
        const override
        {
            return const_iterator(m_children.begin());
        }

        virtual iterator begin_impl()
        override
        {
            return iterator(m_children.begin());
        }

        virtual const_iterator end_impl()
        const override
        {
            return const_iterator(m_children.end());
        }

        virtual iterator end_impl()
        override
        {
            return iterator(m_children.end());
        }

        virtual const_recursive_iterator_type recursive_begin_impl()
        const override
        {
            return const_recursive_iterator_type(this);
        }

        virtual recursive_iterator_type recursive_begin_impl()
        override
        {
            return recursive_iterator_type(this);
        }

        virtual const_recursive_iterator_type recursive_end_impl()
        const override
        {
            return const_recursive_iterator_type();
        }

        virtual recursive_iterator_type recursive_end_impl()
        override
        {
            return recursive_iterator_type();
        }

        virtual void insert_impl(const iterator offset, std::unique_ptr<base_type> p_menu)
        override
        {
            if (!p_menu)
                BOOST_THROW_EXCEPTION(std::invalid_argument("The unique pointer to a menu is nullptr."));

            menu_details_type::insert_menu(*this, offset, *p_menu, encoder());

            m_children.insert(offset.base(), std::move(p_menu));
        }

        virtual void erase_impl(const iterator first, const iterator last)
        override
        {
            menu_details_type::erase_menus(*this, first, last);

            m_children.erase(first.base(), last.base());
        }


    };


}}}


#endif
