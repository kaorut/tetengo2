/*! \file
    \brief The definition of bobura::message::main_window_menu_observer.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOWMENUOBSERVER_H)
#define BOBURA_MESSAGE_MAINWINDOWMENUOBSERVER_H

//#include <boost/concept_check.hpp>

#include <windows.h>

#include <concept_tetengo2.String.h>
#include <tetengo2.gui.menu_observer.h>


namespace bobura { namespace message
{
    /*!
        \brief The class template for a menu observer of the main window.
        
        \tparam Command A command type. It must conform to
                        concept_tetengo2::String<Command>.
    */
    template <typename Command>
    class main_window_menu_observer : public tetengo2::gui::menu_observer
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Command>));


    public:
        // types

        //! The command type.
        typedef Command command_type;


        // constructors and destructor

        /*!
            \brief Creates a menu observer of the main window.

            \param command A command.
        */
        explicit main_window_menu_observer(const command_type& command)
        :
        m_command(command)
        {}

        /*!
            \brief Destroys the menu observer of the main window.
        */
        virtual ~main_window_menu_observer()
        throw ()
        {}


        // functions

        // The document will be derived from
        // tetengo2::gui::menu_observer::selected.
        virtual void selected()
        {
            command_type message(L"Menu Selected: ");
            message += m_command;
            message.push_back(L'\n');
            ::OutputDebugStringW(message.c_str());
        }


    private:
        // variables

        const command_type m_command;


    };


}}

#endif
