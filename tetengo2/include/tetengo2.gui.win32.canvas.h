/*! \file
    \brief The definition of tetengo2::gui::win32::canvas.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CANVAS_H)
#define TETENGO2_GUI_WIN32_CANVAS_H

//#include <cstddef>
#include <stdexcept>
//#include <string>
#include <memory>
#include <utility>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <gdiplus.h>
#undef min
#undef max

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Font.h"
#include "concept_tetengo2.gui.Handle.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a canvas for Win32 platforms.

        \tparam Handle       A handle type for the native interface. It must
                             conform to concept_tetengo2::gui::Handle<Handle>.
        \tparam Size         A size type. It must conform to
                             boost::UnsignedInteger<Size>.
        \tparam String       A string type. It must conform to
                             concept_tetengo2::String<String>.
        \tparam Encode       An encoding unary functor type. The type
                             Encode<std::wstring, String> must conform to
                             boost::UnaryFunction<Encode, std::wstring, String>.
        \tparam WindowHandle A window handle type for the native interface. It
                             must conform to
                             concept_tetengo2::gui::Handle<WindowHandle>.
        \tparam Font         A font type. It must conform to
                             concept_tetengo2::gui::Font<Font>.
    */
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

        //! The handle type for the native interface.
        typedef Handle handle_type;

        //! The size type.
        typedef Size size_type;

        //! The point type.
        typedef std::pair<size_type, size_type> point_type;

        //! The rectangle type.
        typedef std::pair<point_type, point_type> rectangle_type;

        //! The string type.
        typedef String string_type;

        //! The unary functor type for encoding to the native.
        typedef Encode<std::wstring, String> encode_to_native_type;

        //! The window handle type for the native interface.
        typedef WindowHandle window_handle_type;

        //! The font type.
        typedef Font font_type;


        // constructors and destructor

        /*!
            \brief Creates a canvas.

            \param window_handle A window handle.
            \param on_paint      Whether this constructor is called in the
                                 window repaint procedure.

            \throw std::runtime_error When a canvas cannot be created.
        */
        canvas(
            const window_handle_type window_handle,
            const bool               on_paint
        )
        :
        m_window_handle(window_handle),
        m_on_paint(on_paint),
        m_p_paint_info(
            on_paint ?
            create_paint_info(window_handle) : std::auto_ptr< ::PAINTSTRUCT>()
        ),
        m_device_context(on_paint ? NULL : get_device_context(window_handle)),
        m_graphics(on_paint ? m_p_paint_info->hdc : m_device_context),
        m_font(font_type::dialog_font())
        {
            m_graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            m_graphics.SetTextRenderingHint(
                Gdiplus::TextRenderingHintClearTypeGridFit
            );
        }

        /*!
            \brief Destroys the canvas.
        */
        ~canvas()
        throw ()
        {
            if (m_on_paint)
                ::EndPaint(m_window_handle, m_p_paint_info.get());
            else
                ::ReleaseDC(m_window_handle, m_device_context);
        }


        // functions

        /*!
            \brief Returns the handle.

            \return The handle.
        */
        handle_type handle()
        const
        {
            return &m_graphics;
        }

        /*!
            \brief Returns the font.

            \return The font.
        */
        const font_type& font()
        const
        {
            return m_font;
        }

        /*!
            \brief Sets a font.

            \param font A font.
        */
        void set_font(const font_type& font)
        {
            m_font = font;
        }

        /*!
            \brief Draws a text.

            \param text  A text to draw.
            \param point A point where the text is drawn.

            \throw std::runtime_error When the text cannot be drawn.
        */
        void draw_text(const string_type& text, const point_type& point)
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const Gdiplus::FontFamily font_family(
                m_font.family().c_str(), &font_collection
            );
            if (!font_family.IsAvailable())
                throw std::runtime_error("Font family is not available.");
            const Gdiplus::Font font(
                &font_family,
                static_cast<Gdiplus::REAL>(m_font.size()),
                get_font_style(),
                Gdiplus::UnitPixel
            );
            if (!font.IsAvailable())
                throw std::runtime_error("Font is not available.");
            const Gdiplus::SolidBrush brush(
                Gdiplus::Color(128, 255, 0, 0)
            );

            const std::wstring encoded_text = encode_to_native_type()(text);
            const Gdiplus::Status result = m_graphics.DrawString(
                encoded_text.c_str(),
                static_cast< ::INT>(encoded_text.length()),
                &font,
                Gdiplus::PointF(
                    static_cast<Gdiplus::REAL>(point.first),
                    static_cast<Gdiplus::REAL>(point.second)
                ),
                &brush
            );
            if (result != Gdiplus::Ok)
                throw std::runtime_error("Can't draw text!");
        }


    private:
        // static functions

        static std::auto_ptr< ::PAINTSTRUCT> create_paint_info(
            const window_handle_type window_handle
        )
        {
            std::auto_ptr< ::PAINTSTRUCT> p_paint_info(new ::PAINTSTRUCT());

            if (::BeginPaint(window_handle, p_paint_info.get()) == NULL)
                throw std::runtime_error("Can't begin paint!");

            return p_paint_info;
        }

        static ::HDC get_device_context(
            const window_handle_type window_handle
        )
        {
            const ::HDC device_context = ::GetDC(window_handle);
            if (device_context == NULL)
                throw std::runtime_error("Can't get device context!");

            return device_context;
        }

        ::INT get_font_style()
        {
            ::INT style = Gdiplus::FontStyleRegular;

            if (m_font.bold())
                style |= Gdiplus::FontStyleBold;
            if (m_font.italic())
                style |= Gdiplus::FontStyleItalic;
            if (m_font.underline())
                style |= Gdiplus::FontStyleUnderline;
            if (m_font.strikeout())
                style |= Gdiplus::FontStyleStrikeout;

            return style;
        }


        // variables

        const window_handle_type m_window_handle;

        const bool m_on_paint;

        const std::auto_ptr< ::PAINTSTRUCT> m_p_paint_info;

        const ::HDC m_device_context;

        Gdiplus::Graphics m_graphics;

        font_type m_font;


    };


}}}

#endif
