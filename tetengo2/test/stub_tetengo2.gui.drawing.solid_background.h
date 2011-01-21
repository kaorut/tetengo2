/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H)
#define STUBTETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H

#include <cstddef>
#include <utility>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.drawing.background.h"


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <typename Color, typename Handle>
    class solid_background :
        public tetengo2::gui::drawing::background<Handle>
    {
    public:
        // types

        typedef tetengo2::gui::drawing::background<Handle> base_type;

        typedef Color color_type;


        // constructors and destructor

        template <typename C>
        solid_background(C&& color)
        :
        base_type(),
        m_color(std::forward<C>(color))
        {}

        virtual ~solid_background()
        TETENGO2_NOEXCEPT
        {}


        // functions

        const color_type& color()
        const
        {
            return m_color;
        }


    private:
        // variables

        const color_type m_color;


        // virtual functions

        virtual typename base_type::handle_type handle_impl()
        const
        {
            return NULL;
        }


    };


}}}


#endif
