/*! \file
    \brief The definition of tetengo2::gui::message::dialog_message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_DIALOGMESSAGELOOP_H)
#define TETENGO2_GUI_MESSAGE_DIALOGMESSAGELOOP_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/message_loop.h>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a message loop for dialogs.
    */
    class dialog_message_loop : private boost::noncopyable
    {
    public:
        // types

        //! The abstract window type.
        using abstract_window_type = widget::abstract_window;


        // constructors and destructor

        /*!
            \brief Creats a message loop.

            \param dialog A dialog.
        */
        explicit dialog_message_loop(abstract_window_type& dialog);

        /*!
            \brief Destroys the message loop.
        */
        ~dialog_message_loop();


        // functions

        /*!
            \brief Runs the message loop.

            \return The exit status code.
        */
        int operator()() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
