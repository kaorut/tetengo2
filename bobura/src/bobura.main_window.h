/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MAINWINDOW_H)
#define BOBURA_MAINWINDOW_H

//#include <memory>
//#include <utility>

#include <boost/mpl/at.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.command.type_list.h"
#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the main window.

        \tparam Window                    A window type.
        \tparam MessageCatalog            A message catalog type.
        \tparam Settings                  A settings type.
        \tparam MessageLoopBreak          A message loop break type.
        \tparam MainWindowMessageTypeList A message type.
    */
    template <
        typename Window,
        typename MessageCatalog,
        typename Settings,
        typename MessageLoopBreak,
        typename MainWindowMessageTypeList
    >
    class main_window : public Window
    {
    public:
        // types

        //! The base type.
        typedef Window base_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The settings type.
        typedef Settings settings_type;

        //! The message loop break type.
        typedef MessageLoopBreak message_loop_break_type;

        //! The message type list type.
        typedef MainWindowMessageTypeList main_window_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a main window.

            \param message_catalog A message catalog.
            \param settings        Settings.
        */
        main_window(
            const message_catalog_type& message_catalog,
            const settings_type&        settings
        )
        :
        base_type(),
        m_message_catalog(message_catalog),
        m_settings(settings)
        {
            initialize_window();
        }

        /*!
            \brief Destroys the main window.
        */
        virtual ~main_window()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


        // functions

        void initialize_window()
        {
            set_message_observers();

            set_text(m_message_catalog.get(TETENGO2_TEXT("App:Bobura")));
        }

        void set_message_observers()
        {
            this->window_observer_set().destroyed().connect(
                TETENGO2_CPP11_BIND(message_loop_break_type(), 0)
            );

            this->paint_observer_set().paint().connect(
                typename boost::mpl::at<
                    main_window_message_type_list_type,
                    message::main_window::type::paint
                >::type(m_settings.image_directory_path())
            );
        }


    };


}

#endif
