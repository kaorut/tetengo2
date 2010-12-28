/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::widget_canvas.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_WIDGETCANVAS_H)
#define STUBTETENGO2_GUI_DRAWING_WIDGETCANVAS_H

#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <
        typename Handle,
        typename Size,
        typename String,
        typename Encoder,
        typename WindowHandle,
        typename Font
    >
    class widget_canvas : private boost::noncopyable
    {
    public:
        // types

        typedef Handle handle_type;

        typedef Size size_type;

        typedef String string_type;

        typedef Encoder encoder_type;

        typedef WindowHandle window_handle_type;

        typedef Font font_type;


        // constructors and destructor

        widget_canvas(
            const window_handle_type window_handle,
            const bool               on_paint
        )
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

        template <typename S, typename P>
        void draw_text(S&& text, const P& position)
        {}


    private:
        // variables

        font_type m_font;


    };


}}}


#endif
