/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

//#include <cstddef>
//#include <string>

#include <boost/function.hpp>

#include <tetengo2.gui.win32.gui_type_list.h>

#include "bobura.bobura.h"
#include "bobura.settings.h"


namespace bobura
{
    /*!
        \brief The class for a type list of bobura.
    */
    class type_list
    {
    public:
        // types

        //! The size type.
        typedef std::size_t size_type;

        //! The string type.
        typedef std::wstring string_type;

        //! The type list type to create platform specific GUI components.
        typedef
            tetengo2::gui::win32::gui_type_list<size_type, string_type>
            gui_type_list_type;

        //! The GUI initialization and finalization manager type.
        typedef
            gui_type_list_type::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        //! The binary functor type of the alert.
        typedef gui_type_list_type::alert_type alert_type;

        //! The settings type.
        typedef settings<string_type> settings_type;

        //! The Bobura application type.
        typedef
            bobura<
                settings_type, gui_type_list_type, boost::function<void ()>
            >
            bobura_type;


    private:
        // forbidden operations

        type_list();


    };


}

#endif
