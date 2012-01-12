/*! \file
    \brief The definition of tetengo2::gui::message::dialog_message_loop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_DIALOGMESSAGELOOP_H)
#define TETENGO2_GUI_MESSAGE_DIALOGMESSAGELOOP_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a message loop for dialogs.

        \tparam AbstractWindow     An abstract window type.
        \tparam MessageLoopDetails The detail implementation type of a message
                                   loop.
    */
    template <typename AbstractWindow, typename MessageLoopDetails>
    class dialog_message_loop
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The detail implementation type of a message loop.
        typedef MessageLoopDetails message_loop_details_type;


        // constructors and destructor

        /*!
            \brief Creats a message loop.

            \param dialog A dialog.
        */
        dialog_message_loop(abstract_window_type& dialog)
        :
        m_dialog(dialog)
        {}


        // functions

        /*!
            \brief Runs the message loop.

            \return The exit status code.
        */
        int operator()()
        const
        {
            return message_loop_details_type::dialog_loop(m_dialog);
        }


    private:
        // variables

        abstract_window_type& m_dialog;


    };


}}}


#endif
