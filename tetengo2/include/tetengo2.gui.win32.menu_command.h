/*! \file
    \brief The definition of tetengo2::gui::win32::menu_command.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUCOMMAND_H)
#define TETENGO2_GUI_WIN32_MENUCOMMAND_H

#include <cstddef>
#include <vector>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

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

        //! \return The traits type.
        typedef Traits traits_type;

        //! \return The base type.
        typedef menu<traits_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command.

            \param text A text.
        */
        explicit menu_command(const string_type& text)
        :
        base_type(text)
        {}

        /*!
            \brief Destroys the menu command.
        */
        virtual ~menu_command()
        throw ()
        {}


        // functions

        //! \copydoc tetengo2::gui::win32::menu::set_menu_info
        virtual void set_menu_info(
            ::MENUITEMINFOW&       menu_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const
        {
            menu_info.fMask = MIIM_STRING | MIIM_ID;
            menu_info.dwTypeData = &duplicated_text[0];
            menu_info.wID = id();
        }


    };


}}}

#endif
