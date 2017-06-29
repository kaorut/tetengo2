/*! \file
    \brief The definition of tetengo2::gui::cursor::cursor_base.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_CURSOR_H)
#define TETENGO2_GUI_CURSOR_CURSOR_H

#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace cursor
{
    /*!
        \brief The class for a cursor base.
    */
    class cursor_base : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the cursor_base.
        */
        virtual ~cursor_base()
        = default;


    protected:
        // constructors and destructor

        /*!
            \brief Creates a cursor base.
        */
        cursor_base()
        {}


    };


}}}


#endif
