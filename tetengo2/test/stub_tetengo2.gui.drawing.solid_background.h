/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H)
#define STUBTETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H

#include <cstddef>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.drawing.background.h"


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <typename Handle>
    class solid_background :
        public tetengo2::gui::drawing::background<Handle>
    {
    public:
        // types

        typedef tetengo2::gui::drawing::background<Handle> base_type;


        // constructors and destructor

        solid_background()
        :
        base_type()
        {}

        virtual ~solid_background()
        TETENGO2_NOEXCEPT
        {}


    private:
        // virtual functions

        virtual typename base_type::handle_type handle_impl()
        const
        {
            return NULL;
        }


    };


}}}


#endif
