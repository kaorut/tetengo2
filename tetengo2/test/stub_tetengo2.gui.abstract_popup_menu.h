/*! \file
    \brief The definition of stub_tetengo2::gui::abstract_popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ABSTRACTPOPUPMENU_H)
#define STUBTETENGO2_GUI_ABSTRACTPOPUPMENU_H

//#include <memory>

//#include <boost/ptr_container/ptr_vector.hpp>

#include "stub_tetengo2.gui.menu.h"


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
        throw ()
        {}


        // functions

        virtual typename abstract_popup_menu::handle_type handle()
        const
        {
            return m_handle;
        }

        virtual typename abstract_popup_menu::const_iterator begin()
        const
        {
            return m_children.begin();
        }

        virtual typename abstract_popup_menu::iterator begin()
        {
            return m_children.begin();
        }

        virtual typename abstract_popup_menu::const_iterator end()
        const
        {
            return m_children.end();
        }

        virtual typename abstract_popup_menu::iterator end()
        {
            return m_children.end();
        }

        virtual typename abstract_popup_menu::const_recursive_iterator
        recursive_begin()
        const
        {
            return typename abstract_popup_menu::const_recursive_iterator(
                this
            );
        }

        virtual typename abstract_popup_menu::recursive_iterator
        recursive_begin()
        {
            return typename abstract_popup_menu::recursive_iterator(this);
        }

        virtual typename abstract_popup_menu::const_recursive_iterator
        recursive_end()
        const
        {
            return typename abstract_popup_menu::const_recursive_iterator();
        }

        virtual typename abstract_popup_menu::recursive_iterator
        recursive_end()
        {
            return typename abstract_popup_menu::recursive_iterator();
        }

        virtual void insert(
            const typename abstract_popup_menu::iterator offset,
            std::auto_ptr<base_type>                     p_menu
        )
        {
            m_children.insert(offset, p_menu);
        }

        virtual void erase(
            const typename abstract_popup_menu::iterator first,
            const typename abstract_popup_menu::iterator last
        )
        {
            m_children.erase(first, last);
        }


    protected:
        // constructors

        abstract_popup_menu(
            const typename abstract_popup_menu::handle_type  handle,
            const typename abstract_popup_menu::string_type& text
        )
        :
        base_type(text),
        m_handle(handle),
        m_children()
        {}


    private:
        // variables

        const typename abstract_popup_menu::handle_type m_handle;

        boost::ptr_vector<base_type> m_children;


    };


}}

#endif
