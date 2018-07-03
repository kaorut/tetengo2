/*! \file
    \brief The definition of tetengo2::gui::widget::widget_traits.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_WIDGETTRAITS_H)
#define TETENGO2_GUI_WIDGET_WIDGETTRAITS_H

#include <tetengo2/gui/type_list.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The traits class for a GUI widget.
   */
    struct widget_traits
    {
        // types

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The difference type.
        using difference_type = tetengo2::type_list::difference_type;

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The position type.
        using position_type = gui::type_list::position_type;

        //! The dimension type.
        using dimension_type = gui::type_list::dimension_type;
    };
}


#endif
