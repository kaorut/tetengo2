/*! \file
    \brief The definition of stub_tetengo2::gui::menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENU_H)
#define STUBTETENGO2_GUI_MENU_H

#include <cassert>
#include <cstddef>
#include <memory>
#include <stdexcept>
//#include <string>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuObserver.h"
#include "tetengo2.gui.recursive_menu_iterator.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Id,
        typename Handle,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename MenuObserver
    >
    class menu : boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Id>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<String, std::wstring> encode_from_native_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_native_type, String, native_string_type
                >
            ));
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_to_native_type, native_string_type, String
                >
            ));
        };
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuObserver<MenuObserver>
        ));


    public:
        // types

        typedef Id id_type;

        typedef Handle handle_type;

        typedef String string_type;

        typedef Encode<String, std::wstring> encode_from_native_type;

        typedef Encode<std::wstring, String> encode_to_native_type;

        typedef MenuObserver menu_observer_type;

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
        throw ()
        {}


        // functions

        id_type id()
        const
        {
            return 0;
        }

        virtual handle_type handle()
        const
        {
            return NULL;
        }

        const string_type& text()
        const
        {
            return m_text;
        }

        void select()
        {}

        void add_menu_observer(
            std::auto_ptr<menu_observer_type> p_menu_observer
        )
        {}

        virtual const_iterator begin()
        const
        {
            return const_iterator();
        }

        virtual iterator begin()
        {
            return iterator();
        }

        virtual const_iterator end()
        const
        {
            return const_iterator();
        }

        virtual iterator end()
        {
            return iterator();
        }

        virtual const_recursive_iterator recursive_begin()
        const
        {
            return const_recursive_iterator();
        }

        virtual recursive_iterator recursive_begin()
        {
            return recursive_iterator();
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

        virtual void insert(const iterator offset, std::auto_ptr<menu> p_menu)
        {
            assert(false);
            throw std::logic_error("Can't insert any menus.");
        }

        virtual void erase(const iterator first, const iterator last)
        {
            assert(false);
            throw std::logic_error("Can't erase any menus.");
        }


    protected:
        // constructors

        menu(const string_type& text)
        :
        m_text(text)
        {}


    private:
        // variables

        const string_type m_text;


    };


}}

#endif
