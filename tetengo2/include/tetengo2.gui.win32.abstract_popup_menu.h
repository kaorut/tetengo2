/*! \file
    \brief The definition of tetengo2::gui::win32::abstract_popup_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ABSTRACTPOPUPMENU_H)
#define TETENGO2_GUI_WIN32_ABSTRACTPOPUPMENU_H

//#include <cstddef>
//#include <stdexcept>
//#include <utility>

#include <boost/optional.hpp>
//#include <boost/ptr_container/ptr_vector.hpp>
//#include <boost/throw_exception.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.win32.menu.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace tetengo2 { namespace gui { namespace win32
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

        //! The detail implementation type.
        typedef typename menu_details_type::menu_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename menu_details_type::menu_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the abstract_popup_menu.
        */
        virtual ~abstract_popup_menu()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    protected:
        // constructors

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


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        boost::ptr_vector<base_type> m_children;


        // virtual functions

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
            const iterator                              offset,
            typename cpp0x::unique_ptr<base_type>::type p_menu
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

            menu_details_type::insert_menu(*this, offset, *p_menu, encoder());

            m_children.insert(offset, p_menu.release());
        }

        virtual void erase_impl(const iterator first, const iterator last)
        {
            menu_details_type::erase_menus(*this, first, last);

            m_children.erase(first, last);
        }


    };


}}}

#endif
