/*! \file
    \brief The definition of tetengo2::gui::win32::menu_separator.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUSEPARATOR_H)
#define TETENGO2_GUI_WIN32_MENUSEPARATOR_H

//#include <cstddef>
//#include <vector>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.menu.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a menu separator.

        The handle is NULL. The text is empty.

        \tparam Traits A traits type.
   */
    template <typename Traits>
    class menu_separator : public menu<Traits>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef menu<traits_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a menu separator.
        */
        menu_separator()
        :
        base_type(string_type())
        {}

        /*!
            \brief Destroys the menu separator.
        */
        virtual ~menu_separator()
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
            menu_info.fMask = MIIM_FTYPE;
            menu_info.fType = MFT_SEPARATOR;
        }


    };


}}}

#endif
