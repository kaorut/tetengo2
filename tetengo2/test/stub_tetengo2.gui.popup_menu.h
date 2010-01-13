/*! \file
    \brief The definition of stub_tetengo2::gui::popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_POPUPMENU_H)
#define STUBTETENGO2_GUI_POPUPMENU_H

//#include <cstddef>
//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename MenuItem>
    class popup_menu : public MenuItem
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        typedef MenuItem menu_item_type;

        typedef typename menu_item_type::id_type id_type;

        typedef typename menu_item_type::handle_type handle_type;

        typedef typename menu_item_type::string_type string_type;

        typedef
            typename menu_item_type::encode_from_native_type
            encode_from_native_type;

        typedef
            typename menu_item_type::encode_to_native_type
            encode_to_native_type;

        typedef
            typename menu_item_type::menu_observer_type menu_observer_type;

        typedef typename menu_item_type::iterator iterator;

        typedef typename menu_item_type::const_iterator const_iterator;


        // constructors and destructor

        popup_menu(const string_type& text)
        :
        menu_item_type(NULL, text)
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


    };


}}

#endif
