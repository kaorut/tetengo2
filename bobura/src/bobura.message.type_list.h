/*! \file
    \brief The definition of bobura::message::type.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELIST_H)
#define BOBURA_MESSAGE_TYPELIST_H


namespace bobura { namespace message
{
    namespace main_window
    {
        namespace type
        {
            struct menu_observer; //!< The menu observer type.
            struct paint;      //!< The paint observer type.
        }
    }

    namespace about_dialog
    {
        namespace type
        {
            struct ok_button_mouse_observer; //!< The OK button mouse observer
                                             //!< type.
        }
    }


}}


#endif
