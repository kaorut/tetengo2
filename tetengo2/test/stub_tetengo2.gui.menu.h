/*! \file
    \brief The definition of stub_tetengo2::gui::menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENU_H)
#define STUBTETENGO2_GUI_MENU_H

#include <cstddef>
#include <memory>
//#include <string>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuObserver.h"


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

        typedef menu* iterator;

        typedef const menu* const_iterator;


        // constructors and destructor

        virtual ~menu()
        throw ()
        {}


        // functions

        virtual bool is_command()
        const = 0;

        virtual bool is_popup()
        const = 0;

        virtual bool is_separator()
        const = 0;

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

        void set_text(const string_type& text)
        {}

        void select()
        {}

        void add_menu_observer(
            std::auto_ptr<menu_observer_type> p_menu_observer
        )
        {}

        const_iterator begin()
        const
        {
            return const_iterator();
        }

        iterator begin()
        {
            return iterator();
        }

        const_iterator end()
        const
        {
            return const_iterator();
        }

        iterator end()
        {
            return iterator();
        }

        const menu* find_by_id(const id_type id)
        const
        {
            return NULL;
        }

        menu* find_by_id(const id_type id)
        {
            return NULL;
        }

        const menu* find_by_handle(const handle_type handle)
        const
        {
            return NULL;
        }

        menu* find_by_handle(const handle_type handle)
        {
            return NULL;
        }

        void insert(
            const iterator           offset,
            std::auto_ptr<menu> p_menu_item
        )
        {}

        void erase(const iterator first, const iterator last)
        {}


    protected:
        // constructors

        menu(const handle_type handle, const string_type& text)
        :
        m_handle(handle),
        m_text(text)
        {}


    private:
        // variables

        const handle_type m_handle;

        const string_type m_text;


    };


}}

#endif
