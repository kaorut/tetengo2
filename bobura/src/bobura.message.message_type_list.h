/*! \file
    \brief The definition of bobura::message::message_type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MESSAGETYPELIST_H)
#define BOBURA_MESSAGE_MESSAGETYPELIST_H

//#include <boost/concept_check.hpp>

#include "bobura.message.about_dialog_observers.h"
#include "bobura.message.main_window_observers.h"


namespace bobura { namespace message
{
    /*!
        \brief The class template for a message type list of the main window.

        \tparam Command         A command type. It must conform to
                                boost::Generator<Command, void>.
        \tparam Canvas          A canvas type of the main window. It must
                                conform to
                                concept_tetengo2::gui::Canvas<Canvas>.
        \tparam QuitMessageLoop A unary functor type for quitting the message
                                loop. It must conform to
                                boost::UnaryFunction<QuitMessageLoop, void, int>.
    */
    template <typename Command, typename Canvas, typename QuitMessageLoop>
    class message_type_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::Generator<Command, void>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Canvas<Canvas>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));


    public:
        // types

        //! The main window menu observer type;
        typedef
            main_window_menu_observer<Command> main_window_menu_observer_type;

        //! The main window paint observer type;
        typedef
            main_window_paint_observer<Canvas>
            main_window_paint_observer_type;

        //! The main window window observer type;
        typedef
            main_window_window_observer<QuitMessageLoop>
            main_window_window_observer_type;


    private:
        // forbidden operations

        message_type_list();


    };


    /*!
        \brief The class template for a message type list of the about dialog.

        \tparam Dialog A dialog type. It must conform to
                       concept_tetengo2::gui::Dialog<Dialog>.
    */
    template <typename Dialog>
    class about_dialog_message_type_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));


    public:
        // types

        //! The about dialog OK button mouse observer type.
        typedef
            about_dialog_ok_button_mouse_observer<Dialog>
            about_dialog_ok_button_mouse_observer_type;


    private:
        // forbidden operations

        about_dialog_message_type_list();


    };


}}

#endif
