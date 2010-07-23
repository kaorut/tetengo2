/*! \file
    \brief The definition of stub_tetengo2::gui::abstract_popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_ABSTRACTPOPUPMENU_H)
#define STUBTETENGO2_GUI_ABSTRACTPOPUPMENU_H

#include <memory>

#include <boost/ptr_container/ptr_vector.hpp>


namespace stub_tetengo2 { namespace gui
{
    template <typename Menu>
    class abstract_popup_menu : public Menu
    {
    public:
        // types

        typedef Menu base_type;

        typedef typename base_type::id_type id_type;

        typedef typename base_type::handle_type handle_type;

        typedef typename base_type::string_type string_type;

        typedef typename base_type::encoder_type encoder_type;

        typedef typename base_type::menu_observer_type menu_observer_type;

        typedef typename base_type::iterator iterator;

        typedef typename base_type::const_iterator const_iterator;

        typedef typename base_type::recursive_iterator recursive_iterator;

        typedef
            typename base_type::const_recursive_iterator
            const_recursive_iterator;


        // constructors and destructor

        virtual ~abstract_popup_menu()
        throw ()
        {}


        // functions

        virtual handle_type handle()
        const
        {
            return m_handle;
        }

        virtual const_iterator begin()
        const
        {
            return m_children.begin();
        }

        virtual iterator begin()
        {
            return m_children.begin();
        }

        virtual const_iterator end()
        const
        {
            return m_children.end();
        }

        virtual iterator end()
        {
            return m_children.end();
        }

        virtual const_recursive_iterator recursive_begin()
        const
        {
            return const_recursive_iterator(this);
        }

        virtual recursive_iterator recursive_begin()
        {
            return recursive_iterator(this);
        }

        virtual const_recursive_iterator recursive_end()
        const
        {
            return const_recursive_iterator();
        }

        virtual recursive_iterator recursive_end()
        {
            return recursive_iterator();
        }

        virtual void insert(
            const iterator           offset,
            std::auto_ptr<base_type> p_menu
        )
        {
            m_children.insert(offset, p_menu);
        }

        virtual void erase(const iterator first, const iterator last)
        {
            m_children.erase(first, last);
        }


    protected:
        // constructors

        abstract_popup_menu(const handle_type handle, const string_type& text)
        :
        base_type(text),
        m_handle(handle),
        m_children()
        {}


    private:
        // variables

        const handle_type m_handle;

        boost::ptr_vector<base_type> m_children;


    };


}}

#endif
