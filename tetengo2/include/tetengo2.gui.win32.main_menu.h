/*! \file
    \brief The definition of tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MAINMENU_H)
#define TETENGO2_GUI_WIN32_MAINMENU_H

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.Menu.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a main menu for Win32 platforms.

        \tparam Menu A menu type. It must conform to
                     concept_tetengo2::gui::Menu<Menu>
   */
    template <typename Menu>
    class main_menu : public Menu
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::Menu<Menu, typename Menu::base_type>
        ));


    public:
        // types

        //! \return The base type.
        typedef Menu base_type;

        //! \copydoc tetengo2::gui::win32::menu::id_type
        typedef typename base_type::id_type id_type;

        //! \copydoc tetengo2::gui::win32::menu::handle_type
        typedef typename base_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::menu::string_type
        typedef typename base_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::menu::encoder_type
        typedef typename base_type::encoder_type encoder_type;

        //! \copydoc tetengo2::gui::win32::menu::menu_observer_type
        typedef typename base_type::menu_observer_type menu_observer_type;

        //! \copydoc tetengo2::gui::win32::menu::iterator
        typedef typename base_type::iterator iterator;

        //! \copydoc tetengo2::gui::win32::menu::const_iterator
        typedef typename base_type::const_iterator const_iterator;

        //! \copydoc tetengo2::gui::win32::menu::recursive_iterator
        typedef typename base_type::recursive_iterator recursive_iterator;

        //! \copydoc tetengo2::gui::win32::menu::const_recursive_iterator
        typedef
            typename base_type::const_recursive_iterator
            const_recursive_iterator;


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
            assert(false);
            BOOST_THROW_EXCEPTION(
                std::logic_error("A main menu cannot be inserted.")
            );
        }


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


    };


}}}

#endif
