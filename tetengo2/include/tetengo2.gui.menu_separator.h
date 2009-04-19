/*! \file
    \brief The definition of tetengo2::gui::menu_separator.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUSEPARATOR_H)
#define TETENGO2_GUI_MENUSEPARATOR_H

#include <cstddef>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a menu separator.

        The handle is NULL. The text is empty.

        \tparam MenuItem A menu item type. It must conform to
                         concept_tetengo2::gui::MenuItem<MenuItem>
   */
    template <typename MenuItem>
    class menu_separator : public MenuItem
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        //! The ID type.
        typedef typename MenuItem::id_type id_type;

        //! The handle type.
        typedef typename MenuItem::handle_type handle_type;

        //! The string type.
        typedef typename MenuItem::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename MenuItem::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename MenuItem::encode_to_native_type encode_to_native_type;

        //! The menu observer type.
        typedef typename MenuItem::menu_observer_type menu_observer_type;


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

        /*!
            \brief Returns whether the menu item is a menu command.

            \retval true  When the menu item is a menu command.
            \retval false Otherwise.
        */
        virtual bool is_command()
        const
        {
            return false;
        }

        /*!
            \brief Returns whether the menu item is a popup menu.

            \retval true  When the menu item is a popup menu.
            \retval false Otherwise.
        */
        virtual bool is_popup()
        const
        {
            return false;
        }

        /*!
            \brief Returns whether the menu item is a menu separator.

            \retval true  When the menu item is a menu separator.
            \retval false Otherwise.
        */
        virtual bool is_separator()
        const
        {
            return true;
        }

        /*!
            \brief Returns the handle.

            If the value of is_popup() is false, this function may return
            NULL.

            \return The handle.
        */
        virtual handle_type handle()
        const
        {
            return NULL;
        }


    };


}}

#endif
