/*! \file
    \brief The definition of tetengo2::gui::win32::canvas.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CANVAS_H)
#define TETENGO2_GUI_WIN32_CANVAS_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <memory>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/throw_exception.hpp>

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

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a canvas for Win32 platforms.

        \tparam Handle       A handle type for the native interface.
        \tparam Size         A size type.
        \tparam String       A string type.
        \tparam Encoder      An encoder type.
        \tparam WindowHandle A window handle type for the native interface.
        \tparam Font         A font type.
    */
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

        //! The handle type.for the native interface.
        typedef Handle handle_type;

        //! The size type.
        typedef Size size_type;

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The window handle type.for the native interface.
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
        TETENGO2_NOEXCEPT
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

            \tparam F A font type.

            \param font A font.
        */
        template <typename F>
        void set_font(F&& font)
        {
            m_font = std::forward<F>(font);
        }

        /*!
            \brief Draws a text.

            \tparam S A string type.
            \tparam P A position type.

            \param text  A text to draw.
            \param position A position where the text is drawn.

            \throw std::runtime_error When the text cannot be drawn.
        */
        template <typename S, typename P>
        void draw_text(S&& text, P&& position)
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const Gdiplus::FontFamily font_family(
                m_font.family().c_str(), &font_collection
            );
            if (!font_family.IsAvailable())
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Font family is not available.")
                );
            }
            const Gdiplus::Font font(
                &font_family,
                static_cast<Gdiplus::REAL>(m_font.size()),
                get_font_style(),
                Gdiplus::UnitPixel
            );
            if (!font.IsAvailable())
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Font is not available.")
                );
            }
            const Gdiplus::SolidBrush brush(
                Gdiplus::Color(128, 255, 0, 0)
            );

            const std::wstring encoded_text =
                encoder().encode(std::forward<S>(text));
            const Gdiplus::Status result = m_graphics.DrawString(
                encoded_text.c_str(),
                static_cast< ::INT>(encoded_text.length()),
                &font,
                Gdiplus::PointF(
                    to_pixels<Gdiplus::REAL>(
                        gui::position<P>::left(position)
                    ),
                    to_pixels<Gdiplus::REAL>(gui::position<P>::top(position))
                ),
                &brush
            );
            if (result != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't draw text!")
                );
            }
        }


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static std::auto_ptr< ::PAINTSTRUCT> create_paint_info(
            const window_handle_type window_handle
        )
        {
            std::auto_ptr< ::PAINTSTRUCT> p_paint_info(new ::PAINTSTRUCT());

            if (::BeginPaint(window_handle, p_paint_info.get()) == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't begin paint!")
                );
            }

            return p_paint_info;
        }

        static ::HDC get_device_context(
            const window_handle_type window_handle
        )
        {
            const ::HDC device_context = ::GetDC(window_handle);
            if (device_context == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get device context!")
                );
            }

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

        const boost::scoped_ptr< ::PAINTSTRUCT> m_p_paint_info;

        const ::HDC m_device_context;

        Gdiplus::Graphics m_graphics;

        font_type m_font;


    };


}}}

#endif
