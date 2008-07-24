/*! \file
    \brief The definition of tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MAINMENU_H)
#define TETENGO2_GUI_WIN32_MAINMENU_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Handle.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a main menu for Win32 platforms.

        \tparam Handle A handle type to the native interface. It must conform
                       to concept_tetengo2::gui::Handle<Handle>.
   */
    template <typename Handle>
    class main_menu
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));


    public:
        // types

        //! The handle type.
        typedef Handle handle_type;


        // constructors and destructor

        /*!
            \brief Creates a main menu.
        */
        main_menu()
        :
        m_handle(::CreateMenu())
        {}

        /*!
            \brief Destroys the main menu.
        */
        virtual ~main_menu()
        throw ()
        {
            ::DestroyMenu(m_handle);
        }


        // functions

        /*!
            \brief Returns the handle.

            \return The handle.
        */
        virtual handle_type handle()
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
