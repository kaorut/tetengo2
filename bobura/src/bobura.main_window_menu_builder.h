/*! \file
    \brief The definition of bobura::main_window_menu_builder.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOWMENUBUILDER_H)
#define BOBURA_MAINWINDOWMENUBUILDER_H

//#include <memory>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>

#include <tetengo2.stdalt.h>

#include "bobura.type_list.h"


namespace bobura
{
    /*!
        \brief The class for the main window menu builder.
    */
    class main_window_menu_builder : private boost::noncopyable
    {
    public:
        // types

        //! The menu bar type.
        typedef boost::mpl::at<ui_type_list, type::ui::menu_bar>::type menu_bar_type;

        //! The command set type.
        typedef boost::mpl::at<main_window_type_list, type::main_window::command_set>::type command_set_type;

        //! The model type.
        typedef boost::mpl::at<model_type_list, type::model::model>::type model_type;

        //! The main window type.
        typedef boost::mpl::at<main_window_type_list, type::main_window::main_window>::type main_window_type;

        //! The message catalog type.
        typedef boost::mpl::at<locale_type_list, type::locale::message_catalog>::type message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a main window menu builder.

            \param command_set     A command set.
            \param model           A model.
            \param main_window     A main window.
            \param message_catalog A message catalog.
        */
        main_window_menu_builder(
            const command_set_type&     command_set,
            model_type&                 model,
            main_window_type&           main_window,
            const message_catalog_type& message_catalog
        );

        /*!
            \brief Destroys the main window menu builder.
        */
        ~main_window_menu_builder()
        TETENGO2_CPP11_NOEXCEPT;


        // functions

        /*!
            \brief Builds a main window menu bar.

            \return A main window menu bar.
        */
        std::unique_ptr<menu_bar_type> build()
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}


#endif
