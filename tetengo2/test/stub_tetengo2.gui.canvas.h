/*! \file
    \brief The definition of stub_tetengo2::gui::canvas.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_CANVAS_H)
#define STUBTETENGO2_GUI_CANVAS_H

//#include <string>
#include <utility>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Font.h"
#include "concept_tetengo2.gui.Handle.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Handle,
        typename Size,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename WindowHandle,
        typename Font
    >
    class canvas : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_to_native_type, native_string_type, String
                >
            ));
        };
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<WindowHandle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Font<Font>));


    public:
        // types

        typedef Handle handle_type;

        typedef Size size_type;

        typedef std::pair<size_type, size_type> point_type;

        typedef std::pair<point_type, point_type> rectangle_type;

        typedef String string_type;

        typedef Encode<String, String> encode_to_native_type;

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
        throw ()
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
