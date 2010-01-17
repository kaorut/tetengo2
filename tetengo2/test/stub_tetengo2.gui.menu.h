/*! \file
    \brief The definition of stub_tetengo2::gui::menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENU_H)
#define STUBTETENGO2_GUI_MENU_H

#include <memory>
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
            return m_handle;
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

        const_iterator begin()
        const
        {
            return m_children.begin();
        }

        iterator begin()
        {
            return m_children.begin();
        }

        const_iterator end()
        const
        {
            return m_children.end();
        }

        iterator end()
        {
            return m_children.end();
        }

        const_recursive_iterator recursive_begin()
        const
        {
            return const_recursive_iterator(this);
        }

        recursive_iterator recursive_begin()
        {
            return recursive_iterator(this);
        }

        const_recursive_iterator recursive_end()
        const
        {
            return const_recursive_iterator();
        }

        recursive_iterator recursive_end()
        {
            return recursive_iterator();
        }

        void insert(const iterator offset, std::auto_ptr<menu> p_menu)
        {
            m_children.insert(offset, p_menu.release());
        }

        void erase(const iterator first, const iterator last)
        {
            m_children.erase(first, last);
        }


    protected:
        // constructors

        menu(const handle_type handle, const string_type& text)
        :
        m_handle(handle),
        m_text(text),
        m_children()
        {}


    private:
        // variables

        const handle_type m_handle;

        const string_type m_text;

        boost::ptr_vector<menu> m_children;


    };


}}

#endif
