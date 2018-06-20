/*! \file
    \brief The definition of tetengo2::gui::drawing::canvas_traits.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_CANVASTRAITS_H)
#define TETENGO2_GUI_DRAWING_CANVASTRAITS_H

#include <tetengo2/gui/type_list.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/type_list.h>

namespace tetengo2::text::encoding {
    template <typename String>
    class locale;
}


namespace tetengo2::gui::drawing {
    /*!
        \brief The traits class for a canvas.
    */
    class canvas_traits
    {
    public:
        // types

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The position type.
        using position_type = gui::type_list::position_type;

        //! The dimension type.
        using dimension_type = gui::type_list::dimension_type;

        //! The encoder type.
        using encoder_type =
            text::encoder<tetengo2::type_list::internal_encoding_type, text::encoding::locale<string_type>>;
    };
}


#endif
