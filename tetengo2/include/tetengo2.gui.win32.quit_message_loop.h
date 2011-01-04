/*! \file
    \brief The definition of tetengo2::gui::win32::quit_message_loop.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_QUITMESSAGELOOP_H)
#define TETENGO2_GUI_WIN32_QUITMESSAGELOOP_H

#include <functional>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The unary functor class for a message loop for Win32 platforms.
    */
    class quit_message_loop : public std::unary_function<int, void>
    {
    public:
        // functions

        /*!
            \brief Quits the message loop.

            \param exit_code An exit code.
        */
        void operator()(const int exit_code)
        const
        {
            ::PostQuitMessage(exit_code);
        }


    };


}}}

#endif
