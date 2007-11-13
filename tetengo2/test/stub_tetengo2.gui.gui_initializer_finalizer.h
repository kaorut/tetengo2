/*! \file
    \brief The definition of tetengo2::gui::gui_initializer_finalizer.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIINITIALIZERFINALIZER_H)
#define TETENGO2_GUI_GUIINITIALIZERFINALIZER_H

#include <boost/noncopyable.hpp>

#include "tetengo2.nothrow.h"


namespace stub_tetengo2 { namespace gui
{
    class gui_initializer_finalizer : private boost::noncopyable
    {
    public:
        // constructors and destructor

        gui_initializer_finalizer()
        {}

        ~gui_initializer_finalizer()
        TETENGO2_NOTHROW
        {}


    };


}}

#endif
