/*! \file
    \brief The definition of tetengo2::gui::menu_command.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUCOMMAND_H)
#define TETENGO2_GUI_MENUCOMMAND_H

#include <cstddef>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a menu command.

        The handle is NULL.

        \tparam MenuItem A menu item type. It must conform to
                         concept_tetengo2::gui::MenuItem<MenuItem>
   */
    template <typename MenuItem>
    class menu_command : public MenuItem
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        //! The menu item type.
        typedef MenuItem menu_item_type;

        //! \copydoc tetengo2::gui::win32::menu_item::id_type
        typedef typename menu_item_type::id_type id_type;

        //! \copydoc tetengo2::gui::win32::menu_item::handle_type
        typedef typename menu_item_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::menu_item::string_type
        typedef typename menu_item_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::menu_item::encode_from_native_type
        typedef
            typename menu_item_type::encode_from_native_type
            encode_from_native_type;

        //! \copydoc tetengo2::gui::win32::menu_item::encode_to_native_type
        typedef
            typename menu_item_type::encode_to_native_type
            encode_to_native_type;

        //! \copydoc tetengo2::gui::win32::menu_item::menu_observer_type
        typedef
            typename menu_item_type::menu_observer_type
            menu_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command.

            \param text A text.
        */
        explicit menu_command(const string_type& text)
        :
        menu_item(text)
        {}

        /*!
            \brief Destroys the menu command.
        */
        virtual ~menu_command()
        throw ()
        {}


        // functions

        //! \copydoc tetengo2::gui::win32::menu_item::is_command
        virtual bool is_command()
        const
        {
            return true;
        }

        //! \copydoc tetengo2::gui::win32::menu_item::is_popup
        virtual bool is_popup()
        const
        {
            return false;
        }

        //! \copydoc tetengo2::gui::win32::menu_item::is_separator
        virtual bool is_separator()
        const
        {
            return false;
        }

        //! \copydoc tetengo2::gui::win32::menu_item::handle
        virtual handle_type handle()
        const
        {
            return NULL;
        }


    };


}}

#endif
