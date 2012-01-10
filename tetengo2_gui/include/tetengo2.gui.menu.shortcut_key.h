/*! \file
    \brief The definition of tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENU_SHORTCUTKEY_H)
#define TETENGO2_GUI_MENU_SHORTCUTKEY_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace menu
{
    /*!
        \brief The class template for a shortcut key.

        \tparam VirtualKey A virtual key type.
   */
    template <typename VirtualKey>
    class shortcut_key : private boost::noncopyable
    {
    public:
        // types

        //! The virtual key type.
        typedef VirtualKey virtual_key_type;


        // constructors and destructor

        /*!
            \brief Creates a shortcut key.
        */
        shortcut_key()
        {}


    private:
        // types


    };


}}}


#endif
