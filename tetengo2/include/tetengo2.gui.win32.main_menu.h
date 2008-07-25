/*! \file
    \brief The definition of tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MAINMENU_H)
#define TETENGO2_GUI_WIN32_MAINMENU_H

#include <cstddef>
#include <stdexcept>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuItem.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a main menu for Win32 platforms.

        \tparam Handle   A handle type to the native interface. It must
                         conform to concept_tetengo2::gui::Handle<Handle>.
        \tparam MenuItem A menu item type. It musto conform to
                         concept_tetengo2::gui::MenuItem<MenuItem>.
   */
    template <typename Handle, typename MenuItem>
    class main_menu
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        //! The handle type.
        typedef Handle handle_type;

        //! The menu item type.
        typedef MenuItem menu_item_type;


        // constructors and destructor

        /*!
            \brief Creates a main menu.
        */
        main_menu()
        :
        m_handle(::CreateMenu())
        {
            if (m_handle == NULL)
                throw std::runtime_error("Can't create a main menu.");
        }

        /*!
            \brief Destroys the main menu.
        */
        ~main_menu()
        throw ()
        {
            ::DestroyMenu(m_handle);
        }


        // functions

        /*!
            \brief Returns the handle.

            \return The handle.
        */
        handle_type handle()
        const
        {
            return m_handle;
        }


    private:
        // variables

        const handle_type m_handle;


    };


}}}

#endif
