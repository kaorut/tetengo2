/*! \file
    \brief The definition of tetengo2::gui::popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_POPUPMENU_H)
#define TETENGO2_GUI_WIN32_POPUPMENU_H

//#include <cstddef>
//#include <stdexcept>
//#include <vector>

//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.abstract_popup_menu.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a popup menu.

        \tparam Traits A traits type.
   */
    template <typename Traits>
    class popup_menu : public abstract_popup_menu<Traits>
    {
    public:
        // types

        //! \return The traits type.
        typedef Traits traits_type;

        //! \return The base type.
        typedef abstract_popup_menu<traits_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \param text A text.
        */
        explicit popup_menu(const string_type& text)
        :
        base_type(create_menu(), text)
        {}

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup_menu()
        TETENGO2_NOEXCEPT
        {}


    private:
        // static functions

        handle_type create_menu()
        {
            const handle_type handle = ::CreatePopupMenu();

            if (handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a popup menu.")
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
            menu_info.fMask = MIIM_STRING | MIIM_ID | MIIM_SUBMENU;
            menu_info.dwTypeData = &duplicated_text[0];
            menu_info.wID = id();
            menu_info.hSubMenu = handle();
        }


    };


}}}

#endif
