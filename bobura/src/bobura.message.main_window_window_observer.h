/*! \file
    \brief The definition of bobura::message::main_window_window_observer.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOWWINDOWOBSERVER_H)
#define BOBURA_MESSAGE_MAINWINDOWWINDOWOBSERVER_H

#include <boost/concept_check.hpp>

#include <tetengo2.gui.window_observer.h>


namespace bobura { namespace message
{
    /*!
        \brief The class template for a window observer of the main window.

        \tparam QuitMessageLoop A unary functor type for quitting the message
                                loop. It must conform to
                               boost::UnaryFunction<QuitMessageLoop, void, int>
    */
    template <typename QuitMessageLoop>
    class main_window_window_observer : public tetengo2::gui::window_observer
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));


    public:
        // types

        //! The unary functor type for quitting the message loop.
        typedef QuitMessageLoop quit_message_loop_type;


        // constructors and destructor

        /*!
            \brief Creates a window observer of the main window.

            \param quit_message_loop A unary functor for quitting the message
                                     loop.
        */
        explicit main_window_window_observer(
            const quit_message_loop_type& quit_message_loop
        )
        :
        m_quit_message_loop(quit_message_loop)
        {}

        /*!
            \brief Destroys the window observer of the main window.
        */
        virtual ~main_window_window_observer()
        throw ()
        {}


        // functions

        // The document will be derived from
        // tetengo2::gui::window_observer::destroyed.
        virtual void destroyed()
        {
            m_quit_message_loop(0);
        }


    private:
        // variables

        const quit_message_loop_type m_quit_message_loop;


    };


}}

#endif
