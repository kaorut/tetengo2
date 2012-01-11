/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key_table.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SHORTCUTKEYTABLE_H)
#define TETENGO2_GUI_MENU_SHORTCUTKEYTABLE_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a shortcut key table.

        \tparam ShortcutKey A shortcut key type.
   */
    template <typename ShortcutKey>
    class shortcut_key_table : private boost::noncopyable
    {
    public:
        // types

        //! The virtual key type.
        typedef ShortcutKey shortcut_key_type;


        // constructors and destructor

        /*!
            \brief Creates a shortcut key table.
        */
        shortcut_key_table()
        {}

        
        // functions


    private:
        // variables


    };


}}}


#endif
