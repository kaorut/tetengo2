/*! \file
    \brief The definition of the type list for tetengo2::gui.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_TYPELIST_H)
#define TETENGO2_GUI_TYPELIST_H

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/position.h>


namespace tetengo2::gui::type_list {
    //! The type for position.
    using position_type = gui::em_position;

    //! The type for dimension.
    using dimension_type = gui::em_dimension;
}


#endif
