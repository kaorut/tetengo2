/*! \file
    \brief The definition of tetengo2::gui::win32::menu_command.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUCOMMAND_H)
#define TETENGO2_GUI_WIN32_MENUCOMMAND_H

//#include <cstddef>
//#include <utility>
//#include <vector>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.menu.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a menu command.

        The handle is NULL.

        \tparam Traits A traits type.
   */
    template <typename Traits>
    class menu_command : public menu<Traits>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef menu<traits_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command.

            \tparam S A string type.

            \param text A text.
        */
        template <typename S>
        explicit menu_command(S&& text)
        :
        base_type(std::forward<S>(text))
        {}

        /*!
            \brief Destroys the menu command.
        */
        virtual ~menu_command()
        TETENGO2_NOEXCEPT
        {}


    private:
        // virtual functions

        virtual void set_menu_info_impl(
            ::MENUITEMINFOW&       menu_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const
        {
            menu_info.fMask = MIIM_STRING | MIIM_ID;
            menu_info.dwTypeData = duplicated_text.data();
            menu_info.wID = id();
        }


    };


}}}

#endif
