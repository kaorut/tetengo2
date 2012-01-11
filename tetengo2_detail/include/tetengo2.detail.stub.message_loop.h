/*! \file
    \brief The definition of tetengo2::detail::stub::message_loop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MESSAGELOOP_H)
#define TETENGO2_DETAIL_STUB_MESSAGELOOP_H


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a message loop.
    */
    class message_loop
    {
    public:
        // static functions

        /*!
            \brief Run the message loop.

            \tparam AbstractWindow An abstract window type.

            \param window A window.

            \return The exit code.
        */
        template <typename AbstractWindow>
        static int loop(AbstractWindow& window)
        {
            return 0;
        }

        /*!
            \brief Run the message loop for a dialog.

            \return The exit code.
        */
        static int dialog_loop()
        {
            return 0;
        }

        /*!
            \brief Breaks the message loop.

            \param exit_code An exit code.
        */
        static void break_loop(const int exit_code)
        {}


    private:
        // forbidden operations

        message_loop();


    };


}}}


#endif
