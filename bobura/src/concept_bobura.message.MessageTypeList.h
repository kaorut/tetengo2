/*! \file
    \brief The definition of concept_bobura::message::MessageTypeList.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MESSAGE_MESSAGETYPELIST_H)
#define CONCEPTBOBURA_MESSAGE_MESSAGETYPELIST_H

#include <boost/concept_check.hpp>


namespace concept_bobura { namespace message
{
    /*!
        \brief The concept check class template for a command type list.

        \tparam Type A type.
    */
    template <typename Type>
    class MessageTypeList
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef
            typename Type::main_window_menu_observer_type
            main_window_menu_observer_type;

        typedef
            typename Type::main_window_paint_observer_type
            main_window_paint_observer_type;

        typedef
            typename Type::main_window_window_observer_type
            main_window_window_observer_type;

        typedef
            typename Type::about_dialog_ok_button_mouse_observer_type
            about_dialog_ok_button_mouse_observer_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MessageTypeList)
        {}

        
#endif
    };


}}

#endif
