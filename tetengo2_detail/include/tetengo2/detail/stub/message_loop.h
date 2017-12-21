/*! \file
    \brief The definition of tetengo2::detail::stub::message_loop.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MESSAGELOOP_H)
#define TETENGO2_DETAIL_STUB_MESSAGELOOP_H

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a message loop.
    */
    class message_loop : private boost::noncopyable
    {
    public:
        // static functions

        /*!
            \brief Run the message loop.

            \tparam AbstractWindow An abstract window type.

            \param window A window.

            \return The exit code.

            \throw std::system_error When a message loop error has happened.
        */
        template <typename AbstractWindow>
        static int loop(AbstractWindow& window)
        {
            boost::ignore_unused(window);

            return 0;
        }

        /*!
            \brief Run the message loop for a dialog.

            \tparam AbstractWindow An abstract window type.

            \param dialog A dialog.

            \return The exit status code.

            \throw std::system_error When a message loop error has happened.
        */
        template <typename AbstractWindow>
        static int dialog_loop(AbstractWindow& dialog)
        {
            boost::ignore_unused(dialog);

            return 0;
        }

        /*!
            \brief Breaks the message loop.

            \param exit_code An exit code.
        */
        static void break_loop(const int exit_code)
        {
            boost::ignore_unused(exit_code);
        }


    private:
        // forbidden operations

        message_loop()
        = delete;


    };


}}}


#endif
