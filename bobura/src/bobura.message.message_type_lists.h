/*! \file
    \brief The definition of bobura::message::message_type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MESSAGETYPELIST_H)
#define BOBURA_MESSAGE_MESSAGETYPELIST_H

#include "bobura.message.about_dialog_observers.h"
#include "bobura.message.main_window_observers.h"


namespace bobura { namespace message
{
    /*!
        \brief The class template for a message type list of the main window.

        \tparam Command         A command type.
        \tparam Canvas          A canvas type of the main window.
        \tparam QuitMessageLoop A unary functor type for quitting the message
                                loop.
    */
    template <typename Command, typename Canvas, typename QuitMessageLoop>
    class main_window_message_type_list
    {
    public:
        // types

        //! \return The main window menu observer type.
        typedef
            main_window_menu_observer<Command> main_window_menu_observer_type;

        //! \return The main window paint observer type.
        typedef
            main_window_paint_observer<Canvas>
            main_window_paint_observer_type;

        //! \return The main window window observer type.
        typedef
            main_window_window_observer<QuitMessageLoop>
            main_window_window_observer_type;


    private:
        // forbidden operations

        main_window_message_type_list();


    };


    /*!
        \brief The class template for a message type list of the about dialog.

        \tparam Dialog A dialog type.
    */
    template <typename Dialog>
    class about_dialog_message_type_list
    {
    public:
        // types

        //! \return The about dialog OK button mouse observer type.
        typedef
            about_dialog_ok_button_mouse_observer<Dialog>
            about_dialog_ok_button_mouse_observer_type;


    private:
        // forbidden operations

        about_dialog_message_type_list();


    };


}}

#endif
