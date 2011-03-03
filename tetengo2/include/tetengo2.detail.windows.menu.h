/*! \file
    \brief The definition of tetengo2::detail::windows::menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MENU_H)
#define TETENGO2_DETAIL_WINDOWS_MENU_H

#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include <boost/throw_exception.hpp>

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

        //! The menu details type.
        typedef std::remove_pointer< ::HMENU>::type menu_details_type;

        //! The menu details pointer type.
        typedef
            cpp0x::unique_ptr<menu_details_type, detail::menu_deleter>::type
            menu_details_ptr_type;


        // static functions

        /*!
            \brief Creates a main menu.

            \return A unque pointer to a main menu.
        */
        static menu_details_ptr_type create_main_menu()
        {
            menu_details_ptr_type p_menu(::CreateMenu());
            if (p_menu.get() == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a main menu.")
                );
            }

            return std::move(p_menu);
        }

        /*!
            \brief Creates a popup menu.

            \return A unque pointer to a popup menu.
        */
        static menu_details_ptr_type create_popup_menu()
        {
            menu_details_ptr_type p_menu(::CreatePopupMenu());
            if (p_menu.get() == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a popup menu.")
                );
            }

            return std::move(p_menu);
        }


    private:
        // forbidden operations

        menu();


   };


}}}


#endif
