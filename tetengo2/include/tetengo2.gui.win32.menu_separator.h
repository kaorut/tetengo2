/*! \file
    \brief The definition of tetengo2::gui::win32::menu_separator.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUSEPARATOR_H)
#define TETENGO2_GUI_WIN32_MENUSEPARATOR_H

#include <cstddef>

//#include <boost/concept_check.hpp>

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

        //! \copydoc tetengo2::gui::win32::menu::encode_from_native_type
        typedef
            typename base_type::encode_from_native_type
            encode_from_native_type;

        //! \copydoc tetengo2::gui::win32::menu::encode_to_native_type
        typedef
            typename base_type::encode_to_native_type
            encode_to_native_type;

        //! \copydoc tetengo2::gui::win32::menu::menu_observer_type
        typedef
            typename base_type::menu_observer_type menu_observer_type;

        //! \copydoc tetengo2::gui::win32::menu::iterator
        typedef typename base_type::iterator iterator;

        //! \copydoc tetengo2::gui::win32::menu::const_iterator
        typedef typename base_type::const_iterator const_iterator;


        // constructors and destructor

        /*!
            \brief Creates a menu separator.
        */
        menu_separator()
        :
        base_type(NULL, string_type())
        {}

        /*!
            \brief Destroys the menu separator.
        */
        virtual ~menu_separator()
        throw ()
        {}


        // functions

        //! \copydoc tetengo2::gui::win32::menu::is_command
        virtual bool is_command()
        const
        {
            return false;
        }

        //! \copydoc tetengo2::gui::win32::menu::is_popup
        virtual bool is_popup()
        const
        {
            return false;
        }

        //! \copydoc tetengo2::gui::win32::menu::is_separator
        virtual bool is_separator()
        const
        {
            return true;
        }


    };


}}}

#endif
