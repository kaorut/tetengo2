/*! \file
    \brief The definition of tetengo2::gui::popup_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_POPUPMENU_H)
#define TETENGO2_GUI_WIN32_POPUPMENU_H

//#include <cstddef>
//#include <stdexcept>
//#include <utility>
//#include <vector>

//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x.h"
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

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef abstract_popup_menu<traits_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \tparam S A string type.

            \param text A text.
        */
        template <typename S>
        explicit popup_menu(S&& text)
        :
        base_type(create_menu(), std::forward<S>(text))
        {}

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup_menu()
        TETENGO2_CPP0X_NOEXCEPT
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
            menu_info.dwTypeData = duplicated_text.data();
            menu_info.wID = id();
            menu_info.hSubMenu = handle();
        }


    };


}}}

#endif
