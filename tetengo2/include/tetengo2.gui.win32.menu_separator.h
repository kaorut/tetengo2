/*! \file
    \brief The definition of tetengo2::gui::win32::menu_separator.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUSEPARATOR_H)
#define TETENGO2_GUI_WIN32_MENUSEPARATOR_H

#include <cstddef>
#include <vector>

//#include <boost/concept_check.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.Menu.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a menu separator.

        The handle is NULL. The text is empty.

        \tparam Menu A menu type. It must conform to
                     concept_tetengo2::gui::Menu<Menu>
   */
    template <typename Menu>
    class menu_separator : public Menu
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Menu<Menu>));


    public:
        // types

        //! The base type.
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
            \brief Creates a menu separator.

            \param encoder An encoder.
        */
        explicit menu_separator(const encoder_type& encoder)
        :
        base_type(string_type(), encoder)
        {}

        /*!
            \brief Destroys the menu separator.
        */
        virtual ~menu_separator()
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
            menu_info.fMask = MIIM_FTYPE;
            menu_info.fType = MFT_SEPARATOR;
        }


    };


}}}

#endif
