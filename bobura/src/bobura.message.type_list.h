/*! \file
    \brief The definition of bobura::message::type.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELIST_H)
#define BOBURA_MESSAGE_TYPELIST_H


namespace bobura { namespace message
{
    namespace timetable_model
    {
        namespace type
        {
            struct reset;      //!< The reset observer type.
            struct changed;    //!< The changed observer type.
        }
    }

    namespace main_window
    {
        namespace type
        {
            struct menu;       //!< The menu observer type.
            struct paint;      //!< The paint observer type.
            struct window;     //!< The window observer type.
        }
    }

    namespace file_property_dialog
    {
        namespace type
        {
            struct ok_button_mouse; //!< The OK button mouse observer type.
            struct cancel_button_mouse; //!< The cancel button mouse observer
                                        //!< type.
        }
    }

    namespace about_dialog
    {
        namespace type
        {
            struct ok_button_mouse; //!< The OK button mouse observer type.
        }
    }


}}


#endif
