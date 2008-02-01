/*! \file
    \brief The definition of stub_tetengo2::gui::gui_initializer_finalizer.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIINITIALIZERFINALIZER_H)
#define TETENGO2_GUI_GUIINITIALIZERFINALIZER_H

#include <boost/noncopyable.hpp>


namespace stub_tetengo2 { namespace gui
{
    class gui_initializer_finalizer : private boost::noncopyable
    {
    public:
        // constructors and destructor

        gui_initializer_finalizer()
        {}

        ~gui_initializer_finalizer()
        throw ()
        {}


    };


}}

#endif
