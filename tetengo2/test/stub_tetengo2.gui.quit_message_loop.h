/*! \file
    \brief The definition of stub_tetengo2::gui::quit_message_loop.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_QUITMESSAGELOOP_H)
#define STUBTETENGO2_GUI_QUITMESSAGELOOP_H //!< !! Include Guard !!

#include <functional>


namespace stub_tetengo2 { namespace gui
{
    class quit_message_loop : public std::unary_function<int, void>
    {
    public:
        // functions

        void operator()(const int exit_code)
        const
        {}


    };


}}

#endif
