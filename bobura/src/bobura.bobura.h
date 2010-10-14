/*! \file
    \brief The definition of bobura::bobura.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

#include <boost/noncopyable.hpp>


namespace bobura
{
   /*!
        \brief The class template for a bobura application.

        \tparam Settings                A settings type.
        \tparam MainWindow              A main window type.
        \tparam MessageLoop             A message loop type.
        \tparam QuitMessageLoop         A quit-message-loop type.
        \tparam GuiInitializerFinalizer A GUI initializer and finalizer type.
    */
    template <
        typename Settings,
        typename MainWindow,
        typename MessageLoop,
        typename QuitMessageLoop,
        typename GuiInitializerFinalizer
    >
    class bobura : private boost::noncopyable
    {
    public:
        // types

        //! The settings type.
        typedef Settings settings_type;

        //! The main window type.
        typedef MainWindow main_window_type;
        
        //! The message loop type.
        typedef MessageLoop message_loop_type;
        
        //! The quit-message-loop type.
        typedef QuitMessageLoop quit_message_loop_type;

        //! The GUI initializer and finalizer type.
        typedef GuiInitializerFinalizer gui_initializer_finalizer_type;


        // constructors and destructor

        /*!
            \brief Creates a bobura application.

            \param settings Settings of the bobura.
        */
        explicit bobura(const settings_type& settings)
        :
        m_gui_initializer_finalizer(),
        m_settings(settings)
        {}


        // functions

        /*!
            \brief Runs the main process of the application.

            \return The exit status code.
        */
        int run()
        const
        {
            main_window_type main_window;
            main_window.set_visible(true);

            return message_loop_type()();
        }


    private:
        // variables

        const gui_initializer_finalizer_type m_gui_initializer_finalizer;

        const settings_type& m_settings;


    };


}

#endif
