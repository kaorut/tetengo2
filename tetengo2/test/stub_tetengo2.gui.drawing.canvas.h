/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_CANVAS_H)
#define STUBTETENGO2_GUI_DRAWING_CANVAS_H

#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include "tetengo2.gui.measure.h"


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <
        typename Handle,
        typename Size,
        typename String,
        typename Dimension,
        typename Encoder,
        typename Background,
        typename Font,
        typename Picture
    >
    class canvas : private boost::noncopyable
    {
    public:
        // types

        typedef Handle handle_type;

        typedef Size size_type;

        typedef String string_type;

        typedef Dimension dimension_type;

        typedef Encoder encoder_type;

        typedef Background background_type;

        typedef Font font_type;

        typedef Picture picture_type;


        // constructors and destructor

        canvas()
        :
        m_font(font_type::dialog_font())
        {}


        // functions

        handle_type handle()
        const
        {
            return 0;
        }

        const font_type& font()
        const
        {
            return m_font;
        }

        template <typename F>
        void set_font(F&& font)
        {
            m_font = std::forward<F>(font);
        }

        std::vector<string_type> installed_font_families()
        const
        {
            return std::vector<string_type>();
        }

        template <typename P, typename D>
        void fill_rectangle(
            const P&               position,
            const D&               dimension,
            const background_type& background
        )
        {}

        template <typename S, typename P>
        void draw_text(S&& text, const P& position)
        {}

        template <typename P, typename D /* = typename P::dimension_type */>
        void paint_picture(
            const picture_type& picture,
            const P&            position,
            const D&            dimension /* = picture.dimension() */
        )
        {}

#if !defined(DOCUMENTATION)
        template <typename P>
        void paint_picture(const picture_type& picture, const P& position)
        {
            paint_picture(picture, position, picture.dimension());
        }
#endif


    private:
        // variables

        font_type m_font;


    };


}}}


#endif
