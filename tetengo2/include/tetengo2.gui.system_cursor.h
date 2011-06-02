/*! \file
    \brief The definition of tetengo2::gui::system_cursor.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SYSTEMCURSOR_H)
#define TETENGO2_GUI_SYSTEMCURSOR_H

#include "tetengo2.gui.cursor.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a system cursor.

        \tparam CursorDetails A detail implementation type of a cursor.
    */
    template <typename CursorDetails>
    class system_cursor : public cursor<CursorDetails>
    {
    public:
        // types

        //! The detail implemetation type of a cursor.
        typedef CursorDetails cursor_details_type;


        // constructors and destructor


    };


}}


#endif
