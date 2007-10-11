/*! \file
    \brief The definition of tetengo2::gui::gui_initializer_finalizer.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIINITIALIZERFINALIZER_H)
#define TETENGO2_GUI_GUIINITIALIZERFINALIZER_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace stub
{
    /*!
        \brief The class for a GUI initialization and finalization management.
    */
    class gui_initializer_finalizer : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a GUI initialization and finalization management.
        */
        gui_initializer_finalizer()
        {}

        /*!
            \brief Destroys the GUI initialization and finalization
                   management.
        */
        ~gui_initializer_finalizer()
        throw ()
        {}


    };


}}}

#endif
