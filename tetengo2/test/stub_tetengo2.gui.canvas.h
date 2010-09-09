/*! \file
    \brief The definition of stub_tetengo2::gui::canvas.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_CANVAS_H)
#define STUBTETENGO2_GUI_CANVAS_H

#include <utility>

#include <boost/noncopyable.hpp>

#include "tetengo2.cpp0x_keyword.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Handle,
        typename Size,
        typename String,
        typename Encoder,
        typename WindowHandle,
        typename Font
    >
    class canvas : private boost::noncopyable
    {
    public:
        // types

        typedef Handle handle_type;

        typedef Size size_type;

        typedef std::pair<size_type, size_type> point_type;

        typedef std::pair<point_type, point_type> rectangle_type;

        typedef String string_type;

        typedef Encoder encoder_type;

        typedef WindowHandle window_handle_type;

        typedef Font font_type;


        // constructors and destructor

        canvas(
            const window_handle_type window_handle,
            const bool               on_paint
        )
        :
        m_font(font_type::dialog_font())
        {}

        ~canvas()
        TETENGO2_NOEXCEPT
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

        void set_font(const font_type& font)
        {
            m_font = font;
        }

        void draw_text(const string_type& text, const point_type& point)
        {}


    private:
        // variables

        font_type m_font;


    };


}}

#endif
