/*! \file
    \brief The definition of tetengo2::gui::popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_POPUPMENU_H)
#define TETENGO2_GUI_WIN32_POPUPMENU_H

//#include <cstddef>
#include <stdexcept>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a popup menu.

        \tparam MenuItem A menu item type. It must conform to
                         concept_tetengo2::gui::MenuItem<MenuItem>
   */
    template <typename MenuItem>
    class popup_menu : public MenuItem
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
            typename menu_item_type::menu_observer_type menu_observer_type;

        //! \copydoc tetengo2::gui::win32::menu_item::iterator
        typedef typename menu_item_type::iterator iterator;

        //! \copydoc tetengo2::gui::win32::menu_item::const_iterator
        typedef typename menu_item_type::const_iterator const_iterator;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \param text A text.
        */
        popup_menu(const string_type& text)
        :
        menu_item(create_menu(), text)
        {}

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup_menu()
        throw ()
        {
            if (::IsMenu(handle()) != 0)
                ::DestroyMenu(handle());
        }


        // functions

        //! \copydoc tetengo2::gui::win32::menu_item::is_command
        virtual bool is_command()
        const
        {
            return false;
        }

        //! \copydoc tetengo2::gui::win32::menu_item::is_popup
        virtual bool is_popup()
        const
        {
            return true;
        }

        //! \copydoc tetengo2::gui::win32::menu_item::is_separator
        virtual bool is_separator()
        const
        {
            return false;
        }


    private:
        // static functions

        handle_type create_menu()
        {
            const handle_type handle = ::CreatePopupMenu();

            if (handle == NULL)
                throw std::runtime_error("Can't create a main menu.");

            return handle;
        }


    };


}}}

#endif
