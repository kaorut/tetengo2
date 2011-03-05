/*! \file
    \brief The definition of stub_tetengo2::gui::menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENU_H)
#define STUBTETENGO2_GUI_MENU_H

//#include <cassert>
//#include <cstddef>
#include <stdexcept>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Traits>
    class menu : boost::noncopyable
    {
    public:
        // types

        typedef Traits traits_type;

        typedef typename traits_type::id_type id_type;

        typedef const void* handle_type;

        typedef typename traits_type::string_type string_type;

        typedef typename traits_type::encoder_type encoder_type;

        typedef
            typename traits_type::menu_observer_set_type
            menu_observer_set_type;

        typedef typename boost::ptr_vector<menu>::iterator iterator;

        typedef
            typename boost::ptr_vector<menu>::const_iterator const_iterator;

        typedef
            tetengo2::gui::recursive_menu_iterator<menu> recursive_iterator;

        typedef
            tetengo2::gui::recursive_menu_iterator<const menu>
            const_recursive_iterator;


        // constructors and destructor

        virtual ~menu()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        id_type id()
        const
        {
            return 0;
        }

        handle_type handle()
        const
        {
            return handle_impl();
        }

        const string_type& text()
        const
        {
            return m_text;
        }

        void select()
        {}

        const menu_observer_set_type& menu_observer_set()
        const
        {
            static const menu_observer_set_type dummy;
            return dummy;
        }

        menu_observer_set_type& menu_observer_set()
        {
            static menu_observer_set_type dummy;
            return dummy;
        }

        const_iterator begin()
        const
        {
            return begin_impl();
        }

        iterator begin()
        {
            return begin_impl();
        }

        const_iterator end()
        const
        {
            return end_impl();
        }

        iterator end()
        {
            return end_impl();
        }

        const_recursive_iterator recursive_begin()
        const
        {
            return recursive_begin_impl();
        }

        recursive_iterator recursive_begin()
        {
            return recursive_begin_impl();
        }

        const_recursive_iterator recursive_end()
        const
        {
            return recursive_end_impl();
        }

        recursive_iterator recursive_end()
        {
            return recursive_end_impl();
        }

        void insert(
            const iterator                                   offset,
            typename tetengo2::cpp0x::unique_ptr<menu>::type p_menu
        )
        {
            insert_impl(offset, std::move(p_menu));
        }

        void erase(const iterator first, const iterator last)
        {
            erase_impl(first, last);
        }


    protected:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // constructors

        template <typename S>
        explicit menu(S&& text)
        :
        m_text(std::forward<S>(text))
        {}


    private:
        // variables

        const string_type m_text;


        // virtual functions

        virtual handle_type handle_impl()
        const
        {
            return NULL;
        }

        virtual const_iterator begin_impl()
        const
        {
            return const_iterator();
        }

        virtual iterator begin_impl()
        {
            return iterator();
        }

        virtual const_iterator end_impl()
        const
        {
            return const_iterator();
        }

        virtual iterator end_impl()
        {
            return iterator();
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
            const iterator                                   offset,
            typename tetengo2::cpp0x::unique_ptr<menu>::type p_menu
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
