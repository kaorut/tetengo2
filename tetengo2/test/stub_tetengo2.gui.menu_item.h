/*! \file
    \brief The definition of stub_tetengo2::gui::menu_item.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENUITEM_H)
#define STUBTETENGO2_GUI_MENUITEM_H

#include <memory>

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
        typename MenuObserver
    >
    class menu_item : boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Id>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuObserver<MenuObserver>
        ));


    public:
        // types

        typedef Id id_type;

        typedef Handle handle_type;

        typedef String string_type;

        typedef MenuObserver menu_observer_type;


        // constructors and destructor

        virtual ~menu_item()
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
        const = 0;

        const string_type& text()
        const
        {
            static const string_type dummy;
            return dummy;
        }

        void set_text(const string_type& text)
        {}

        void select()
        {}

        void add_menu_observer(
            std::auto_ptr<menu_observer_type> p_menu_observer
        )
        {}


    protected:
        // constructors

        menu_item(const string_type& text)
        {}


    };


}}

#endif
