/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include <algorithm>
//#include <memory>
//#include <utility>

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.Dialog.h>

#include "bobura.message.main_window_window_observer.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam Dialog          A dialog type. It must conform to
                                concept_tetengo2::gui::Dialog<Dialog>.
        \tparam Window          A window type. It must conform to
                                concept_tetengo2::gui::Window<Window>.
        \tparam MessageLoop     A generator type for a message loop. It must
                                conform to
                                boost::Generator<MessageLoop, int>.
        \tparam QuitMessageLoop A unary functor type for quitting the message
                                loop. It must conform to
                                boost::UnaryFunction<QuitMessageLoop, void, int>
    */
    template <
        typename Dialog,
        typename Window,
        typename MessageLoop,
        typename QuitMessageLoop
    >
    class about
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));
        BOOST_CONCEPT_ASSERT((boost::Generator<MessageLoop, int>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));


    public:
        // types

        //! The dialog type.
        typedef Dialog dialog_type;

        //! The window type.
        typedef Window window_type;

        //! The message loop type.
        typedef MessageLoop message_loop_type;

        //! The quit message loop type.
        typedef QuitMessageLoop quit_message_loop_type;


        // constructors and destructor

        /*!
            \brief Creates an about command.

            \param window A window.
        */
        explicit about(window_type& window)
        :
        m_p_window(&window)
        {}

        /*!
            \brief Copies an about command.

            \param another Another about command object.
        */
        about(const about& another)
        :
        m_p_window(another.m_p_window)
        {}

        /*!
            \brief Destroys the about command.
        */
        ~about()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another about command object.

            \param another Another about command object.
        */
        void swap(about& another)
        throw ()
        {
            std::swap(m_p_window, another.m_p_window);
        }

        /*!
            \brief Assigns another about command object.

            \param another Another about command object.

            \return this object.
        */
        about& operator=(const about& another)
        {
            about(another).swap(*this);
            return *this;
        }

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            m_p_window->set_enabled(false);

            dialog_type dialog(*m_p_window);

            const typename window_type::position_type& window_position =
                m_p_window->position();
            dialog.set_dimension(std::make_pair(384, 256));
            dialog.set_position(
                std::make_pair(
                    window_position.first + 64, window_position.second + 64
                )
            );

            dialog.add_window_observer(
                std::auto_ptr<window_observer_type> (
                    new message::main_window_window_observer<
                        quit_message_loop_type
                    >(quit_message_loop_type())
                )
            );

            dialog.set_visible(true);
            dialog.activate();

            message_loop_type()();

            m_p_window->set_enabled(true);
            m_p_window->activate();
        }


    private:
        // types

        typedef
            typename window_type::window_observer_type
            window_observer_type;


        // variables

        window_type* m_p_window;


    };


}}

namespace std
{
    /*!
        \brief Swaps two about objects.

        \tparam Dialog          A dialog type. It must conform to
                                concept_tetengo2::gui::Dialog<Dialog>.
        \tparam Window          A window type. It must conform to
                                concept_tetengo2::gui::Window<Window>.
        \tparam MessageLoop     A generator type for a message loop. It must
                                conform to
                                boost::Generator<MessageLoop, int>.
        \tparam QuitMessageLoop A unary functor type for quitting the message
                                loop. It must conform to
                                boost::UnaryFunction<QuitMessageLoop, void, int>

        \param about1 An about object #1.
        \param about2 An about object #2.
    */
    template <
        typename Dialog,
        typename Window,
        typename MessageLoop,
        typename QuitMessageLoop
    >
    void swap(
        bobura::command::about<
            Dialog, Window, MessageLoop, QuitMessageLoop
        >& about1,
        bobura::command::about<
            Dialog, Window, MessageLoop, QuitMessageLoop
        >& about2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));
        BOOST_CONCEPT_ASSERT((boost::Generator<MessageLoop, int>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
        ));

        about1.swap(about2);
    }


}

#endif
