/*! \file
    \brief The definition of concept_bobura::MainWindow.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MAINWINDOW_H)
#define CONCEPTBOBURA_MAINWINDOW_H

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.Window.h>


namespace concept_bobura
{
    /*!
        \brief The concept check class template for main_window.

        \tparam Type A type.
    */
    template <typename Type>
    class MainWindow : public concept_tetengo2::gui::Window<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::command_type_list_type command_type_list_type;

        typedef
            typename Type::main_window_message_type_list_type
            main_window_message_type_list_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MainWindow)
        {}


#endif
    };


}

#endif
