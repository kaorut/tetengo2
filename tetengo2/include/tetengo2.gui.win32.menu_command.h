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


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a menu command.

        The handle is NULL.

        \tparam Menu A menu type.
   */
    template <typename Menu>
    class menu_command : public Menu
    {
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

        //! \copydoc tetengo2::gui::win32::menu::menu_observer_set_type
        typedef
            typename base_type::menu_observer_set_type menu_observer_set_type;

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
