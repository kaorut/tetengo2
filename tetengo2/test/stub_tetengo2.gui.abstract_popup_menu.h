/*! \file
    \brief The definition of stub_tetengo2::gui::abstract_popup_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ABSTRACTPOPUPMENU_H)
#define STUBTETENGO2_GUI_ABSTRACTPOPUPMENU_H

//#include <memory>
//#include <utility>

//#include <boost/ptr_container/ptr_vector.hpp>

#include "stub_tetengo2.gui.menu.h"
#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class abstract_popup_menu : public menu<Traits>
    {
    public:
        // types

        typedef Traits traits_type;

        typedef menu<traits_type> base_type;


        // constructors and destructor

        virtual ~abstract_popup_menu()
        TETENGO2_NOEXCEPT
        {}


    protected:
        // constructors
        
        template <typename S>
        abstract_popup_menu(
            const typename abstract_popup_menu::handle_type handle,
            S&&                                             text
        )
        :
        base_type(std::forward<S>(text)),
        m_handle(handle),
        m_children()
        {}


    private:
        // variables

        const typename abstract_popup_menu::handle_type m_handle;

        boost::ptr_vector<base_type> m_children;


        // virtual functions

        virtual typename abstract_popup_menu::handle_type handle_impl()
        const
        {
            return m_handle;
        }

        virtual typename abstract_popup_menu::const_iterator begin_impl()
        const
        {
            return m_children.begin();
        }

        virtual typename abstract_popup_menu::iterator begin_impl()
        {
            return m_children.begin();
        }

        virtual typename abstract_popup_menu::const_iterator end_impl()
        const
        {
            return m_children.end();
        }

        virtual typename abstract_popup_menu::iterator end_impl()
        {
            return m_children.end();
        }

        virtual typename abstract_popup_menu::const_recursive_iterator
        recursive_begin_impl()
        const
        {
            return typename abstract_popup_menu::const_recursive_iterator(
                this
            );
        }

        virtual typename abstract_popup_menu::recursive_iterator
        recursive_begin_impl()
        {
            return typename abstract_popup_menu::recursive_iterator(this);
        }

        virtual typename abstract_popup_menu::const_recursive_iterator
        recursive_end_impl()
        const
        {
            return typename abstract_popup_menu::const_recursive_iterator();
        }

        virtual typename abstract_popup_menu::recursive_iterator
        recursive_end_impl()
        {
            return typename abstract_popup_menu::recursive_iterator();
        }

        virtual void insert_impl(
            const typename abstract_popup_menu::iterator offset,
            std::auto_ptr<base_type>                     p_menu
        )
        {
            m_children.insert(offset, p_menu);
        }

        virtual void erase_impl(
            const typename abstract_popup_menu::iterator first,
            const typename abstract_popup_menu::iterator last
        )
        {
            m_children.erase(first, last);
        }


    };


}}

#endif
