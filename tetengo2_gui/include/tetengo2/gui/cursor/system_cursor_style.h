/*! \file
    \brief The definition of tetengo2::gui::cursor::system.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CURSOR_SYSTEMCURSORSTYLE_H)
#define TETENGO2_GUI_CURSOR_SYSTEMCURSORSTYLE_H


namespace tetengo2 { namespace gui { namespace cursor
{
        /*!
            \brief The enumeration type for the sysctem cursor style.
        */
        enum class system_cursor_style
        {
            default_,          //!< A default style.
            hand,              //!< A hand style.
            horizontal_resize, //!< A horizontal resize style.
            vertical_resize,   //!< A vertical resize style.
        };


}}}


#endif
