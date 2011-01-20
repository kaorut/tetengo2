/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::transparent_background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H)
#define STUBTETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H

#include <cstddef>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.drawing.background.h"


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <typename Handle>
    class transparent_background :
        public tetengo2::gui::drawing::background<Handle>
    {
    public:
        // types

        typedef tetengo2::gui::drawing::background<Handle> base_type;


        // constructors and destructor

        transparent_background()
        :
        base_type(NULL)
        {}

        virtual ~transparent_background()
        TETENGO2_NOEXCEPT
        {}


    };


}}}


#endif
