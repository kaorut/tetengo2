/*! \file
    \brief The definition of tetengo2::detail::windows::menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MENU_H)
#define TETENGO2_DETAIL_WINDOWS_MENU_H

#include <type_traits>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp0x.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        struct menu_deleter
        {
            void operator()(::HMENU gdi_menu_handle)
            const
            {
                if (::IsMenu(gdi_menu_handle))
                    ::DestroyMenu(gdi_menu_handle);
            }


        };


    }
#endif

    /*!
        \brief The class for a detail implementation of a menu.
    */
    class menu
    {
    public:
        // types

        //! The detail implementation type of a menu.
        typedef std::remove_pointer< ::HMENU>::type menu_details_type;

        //! The menu handle type.
        typedef
            cpp0x::unique_ptr<menu_details_type, detail::menu_deleter>::type
            menu_handle_type;


        // static functions

        /*!
            \brief Creates a men menu.
        */
        menu_handle_type create_main_menu()
        {
            return menu_handle_type();
        }


    private:
        // forbidden operations

        menu();


   };


}}}


#endif
