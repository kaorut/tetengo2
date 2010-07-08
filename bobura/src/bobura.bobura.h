/*! \file
    \brief The definition of bobura::bobura.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "concept_bobura.MainWindow.h"
#include "concept_bobura.Settings.h"


namespace bobura
{
   /*!
        \brief The class template for a bobura application.

        \tparam Settings                A settings type. It must conform to
                                        concept_bobura::Settings<Settings>.
        \tparam MainWindow              A main window type. It must conform to
                                        concept_bobura::MainWindow<MainWindow>.
        \tparam MessageLoop             A message loop type. It must conform
                                        to boost::Generator<MessageLoop, int>.
        \tparam QuitMessageLoop         A quit-message-loop type. It must
                                        conform to
                                        boost::UnaryFunction<MessageLoop, void, int>.
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
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_bobura::Settings<Settings>));
        BOOST_CONCEPT_ASSERT((concept_bobura::MainWindow<MainWindow>));
        BOOST_CONCEPT_ASSERT((boost::Generator<MessageLoop, int>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));


    public:
        // types

        //! \return The settings type.
        typedef Settings settings_type;

        //! \return The main window type.
        typedef MainWindow main_window_type;
        
        //! \return The message loop type.
        typedef MessageLoop message_loop_type;
        
        //! \return The quit-message-loop type.
        typedef QuitMessageLoop quit_message_loop_type;

        //! \return The GUI initializer and finalizer type.
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

        /*!
            \brief Destroys the bobura application.
        */
        ~bobura()
        throw ()
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
