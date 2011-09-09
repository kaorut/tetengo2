/*! \file
    \brief The definition of tetengo2::gui::abstract_popup_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ABSTRACTPOPUPMENU_H)
#define TETENGO2_GUI_ABSTRACTPOPUPMENU_H

//#include <cstddef>
#include <memory>
//#include <stdexcept>
//#include <utility>
//#include <vector>

//#include <boost/throw_exception.hpp>

#include "tetengo2.gui.menu.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class template for a abstract_popup_menu.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class abstract_popup_menu : public menu<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef menu<traits_type, menu_details_type> base_type;

        //! The const iterator type.
        typedef typename base_type::const_iterator const_iterator;

        //! The iterator type.
        typedef typename base_type::iterator iterator;

        //! The const recursive iterator type.
        typedef
            typename base_type::const_recursive_iterator
            const_recursive_iterator;

        //! The recursive iterator type.
        typedef typename base_type::recursive_iterator recursive_iterator;

        //! The detail implementation type.
        typedef typename menu_details_type::menu_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename menu_details_type::menu_details_ptr_type
            details_ptr_type;


    protected:
        // constructors and destructor

        /*!
            \brief Creates a abstract_popup_menu.

            \tparam S A string type.

            \param text      A text.
            \param p_details A unique pointer to a detail implementation.
        */
        template <typename S>
        abstract_popup_menu(S&& text, details_ptr_type p_details)
        :
        base_type(std::forward<S>(text), std::move(p_details)),
        m_children()
        {}

        /*!
            \brief Destroys the abstract_popup_menu.
        */
        virtual ~abstract_popup_menu()
        TETENGO2_CPP0X_NOEXCEPT
        {}


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
        const
        {
            return const_iterator(m_children.begin());
        }

        virtual iterator begin_impl()
        {
            return iterator(m_children.begin());
        }

        virtual const_iterator end_impl()
        const
        {
            return const_iterator(m_children.end());
        }

        virtual iterator end_impl()
        {
            return iterator(m_children.end());
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
            const iterator             offset,
            std::unique_ptr<base_type> p_menu
        )
        {
            if (!p_menu)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The auto pointer to a menu is NULL."
                    )
                );
            }

            menu_details_type::insert_menu(*this, offset, *p_menu, encoder());

            m_children.insert(offset.base(), std::move(p_menu));
        }

        virtual void erase_impl(const iterator first, const iterator last)
        {
            menu_details_type::erase_menus(*this, first, last);

            m_children.erase(first.base(), last.base());
        }


    };


}}


#endif
