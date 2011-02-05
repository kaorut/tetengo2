/*! \file
    \brief The definition of tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MAINMENU_H)
#define TETENGO2_GUI_WIN32_MAINMENU_H

//#include <cassert>
//#include <cstddef>
//#include <stdexcept>
//#include <vector>

//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.abstract_popup_menu.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a main menu for Win32 platforms.

        \tparam Traits A traits type.
   */
    template <typename Traits>
    class main_menu : public abstract_popup_menu<Traits>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef abstract_popup_menu<traits_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a main menu.
        */
        main_menu()
        :
        base_type(create_menu(), string_type())
        {}

        /*!
            \brief Destroys the main menu.
        */
        virtual ~main_menu()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    private:
        // static functions

        handle_type create_menu()
        {
            const handle_type handle = ::CreateMenu();

            if (handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a main menu.")
                );
            }

            return handle;
        }


        // virtual functions

        virtual void set_menu_info_impl(
            ::MENUITEMINFOW&       menu_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(
                std::logic_error("A main menu cannot be inserted.")
            );
        }


    };


}}}

#endif
