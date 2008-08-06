/*! \file
    \brief The definition of stub_tetengo2::gui::popup_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_POPUPMENU_H)
#define STUBTETENGO2_GUI_POPUPMENU_H

#include <cstddef>
#include <memory>
//#include <string>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuItem.h"
#include "concept_tetengo2.gui.MenuItemList.h"
#include "tetengo2.gui.menu_item.h"
#include "tetengo2.gui.win32.menu_item_list.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Id,
        typename Handle,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename MenuItemList,
        typename MenuObserver
    >
    class popup_menu :
        public tetengo2::gui::menu_item<
            Id,
            Handle,
            String,
            Encode,
            MenuObserver
        >
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
            concept_tetengo2::gui::MenuItemList<MenuItemList>
        ));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuObserver<MenuObserver>
        ));


    public:
        // types

        typedef
            menu_item<
                id_type, handle_type, string_type, Encode, menu_observer_type
            >
            menu_item_type;

        typedef MenuItemList menu_items_type;

        typedef typename menu_items_type::iterator menu_item_iterator;

        typedef
            typename menu_items_type::const_iterator const_menu_item_iterator;


        // constructors and destructor

        popup_menu(const string_type& text)
        :
        menu_item(text)
        {}

        virtual ~popup_menu()
        throw ()
        {}


        // functions

        virtual bool is_command()
        const
        {
            return false;
        }

        virtual bool is_popup()
        const
        {
            return false;
        }

        virtual bool is_separator()
        const
        {
            return false;
        }

        virtual handle_type handle()
        const
        {
            return NULL;
        }

        const_menu_item_iterator menu_item_begin()
        const
        {
            return NULL;
        }

        menu_item_iterator menu_item_begin()
        {
            return NULL;
        }

        const_menu_item_iterator menu_item_end()
        const
        {
            return NULL;
        }

        menu_item_iterator menu_item_end()
        {
            return NULL;
        }

        void insert(
            menu_item_iterator            offset,
            std::auto_ptr<menu_item_type> p_menu_item
        )
        {}

        void erase(menu_item_iterator first, menu_item_iterator last)
        {}

        const menu_item_type* find_by_id(const id_type id)
        const
        {
            return NULL;
        }

        menu_item_type* find_by_id(const id_type id)
        {
            return NULL;
        }

        const menu_item_type* find_by_handle(const handle_type handle)
        const
        {
            return NULL;
        }

        menu_item_type* find_by_handle(const handle_type handle)
        {
            return NULL;
        }


    };


}}

#endif
