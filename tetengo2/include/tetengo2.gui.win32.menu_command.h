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
//#include <Windows.h>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.win32.menu.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a menu command.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class menu_command : public menu<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef menu<traits_type, menu_details_type> base_type;


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
        TETENGO2_CPP0X_NOEXCEPT
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
