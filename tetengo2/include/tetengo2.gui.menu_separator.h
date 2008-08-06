/*! \file
    \brief The definition of tetengo2::gui::menu_separator.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUSEPARATOR_H)
#define TETENGO2_GUI_MENUSEPARATOR_H

//#include <cstddef>

//#include <boost/concept_check.hpp>

#include "tetengo2.gui.menu_item.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a menu separator.

        The handle is NULL. The text is empty.

        \tparam Id           A ID type. It must conform to
                             boost::UnsignedInteger<Id>.
        \tparam Handle       A handle type. It must conform to
                             concept_tetengo2::gui::Handle<Handle>.
        \tparam String       A string type. It must conform to
                             concept_tetengo2::String<String>.
        \tparam MenuObserver A menu observer type. It must conform to
                             concept_tetengo2::gui::MenuObserver<MenuObserver>.
   */
    template <
        typename Id,
        typename Handle,
        typename String,
        typename MenuObserver
    >
    class menu_separator : public menu_item<Id, Handle, String, MenuObserver>
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
        // constructors and destructor

        /*!
            \brief Creates a menu separator.
        */
        menu_separator()
        :
        menu_item(string_type())
        {}

        /*!
            \brief Destroys the menu separator.
        */
        virtual ~menu_separator()
        throw ()
        {}


        // functions

        // The document will be derived from
        // tetengo2::gui::menu_item::is_command.
        virtual bool is_command()
        const
        {
            return false;
        }

        // The document will be derived from
        // tetengo2::gui::menu_item::is_popup.
        virtual bool is_popup()
        const
        {
            return false;
        }

        // The document will be derived from
        // tetengo2::gui::menu_item::is_separator.
        virtual bool is_separator()
        const
        {
            return true;
        }

        // The document will be derived from
        // tetengo2::gui::menu_item::handle.
        virtual handle_type handle()
        const
        {
            return NULL;
        }


    };


}}

#endif
