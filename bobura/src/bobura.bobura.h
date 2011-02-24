/*! \file
    \brief The definition of bobura::bobura.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

#include <boost/noncopyable.hpp>


namespace bobura
{
   /*!
        \brief The class template for a bobura application.

        \tparam Settings        A settings type.
        \tparam MessageCatalog  A message catalog type.
        \tparam MainWindow      A main window type.
        \tparam MessageLoop     A message loop type.
        \tparam QuitMessageLoop A quit-message-loop type.
        \tparam GuiFixture      A GUI fixture type.
    */
    template <
        typename Settings,
        typename MessageCatalog,
        typename MainWindow,
        typename MessageLoop,
        typename QuitMessageLoop,
        typename GuiFixture
    >
    class bobura : private boost::noncopyable
    {
    public:
        // types

        //! The settings type.
        typedef Settings settings_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The main window type.
        typedef MainWindow main_window_type;
        
        //! The message loop type.
        typedef MessageLoop message_loop_type;
        
        //! The quit-message-loop type.
        typedef QuitMessageLoop quit_message_loop_type;

        //! The GUI fixture type.
        typedef GuiFixture gui_fixture_type;


        // constructors and destructor

        /*!
            \brief Creates a bobura application.

            \param settings Settings of the bobura.
        */
        explicit bobura(const settings_type& settings)
        :
        m_gui_fixture(),
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
            const message_catalog_type message_catalog;

            main_window_type main_window(message_catalog, m_settings);
            main_window.set_visible(true);

            return message_loop_type()();
        }


    private:
        // variables

        const gui_fixture_type m_gui_fixture;

        const settings_type& m_settings;


    };


}

#endif
