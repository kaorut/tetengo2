/*! \file
    \brief The definition of tetengo2::gui::win32::canvas.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CANVAS_H)
#define TETENGO2_GUI_WIN32_CANVAS_H

#include <string>
#include <utility>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>
#include <gdiplus.h>

#include "tetengo2.StringConcept.h"
#include "tetengo2.gui.HandleConcept.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a canvas for Win32 platforms.

        \param Handle       A handle type for the native interface. It must
                            conform to tetengo2::gui::HandleConcept<Handle>.
        \param Size         A size type. It must conform to
                            boost::IntegerConcept<Size>.
        \param String       A string type. It must conform to
                            tetengo2::StringConcept<String>.
        \param Encode       An encoding unary functor type. The type
                            Encode<std::wstring, String> must conform to
                            boost::UnaryFunctionConcept<Encode, std::wstring, String>.
        \param WindowHandle A window handle type for the native interface. It
                            must conform to
                            tetengo2::gui::HandleConcept<WindowHandle>.
    */
    template <
        typename Handle,
        typename Size,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename WindowHandle
    >
    class canvas : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Handle, tetengo2::gui, HandleConcept);
        BOOST_CLASS_REQUIRE(Size, boost, IntegerConcept);
        BOOST_CLASS_REQUIRE(String, tetengo2, StringConcept);
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CLASS_REQUIRE3(
                encode_to_native_type,
                native_string_type,
                String,
                boost,
                UnaryFunctionConcept
            );
        };
        BOOST_CLASS_REQUIRE(WindowHandle, tetengo2::gui, HandleConcept);


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


        // constructors and destructor

        /*!
            \brief Creates a canvas.

            \param window_handle A window handle.
        */
        canvas(const window_handle_type window_handle)
        :
        m_window_handle(window_handle),
        m_paint_info(get_paint_info(window_handle)),
        m_graphics(m_paint_info.hdc)
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
            ::EndPaint(m_window_handle, &m_paint_info);
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
            \brief Draws a text.

            \param text  A text to draw.
            \param point A point where the text is drawn.
        */
        void draw_text(const string_type& text, const point_type& point)
        {
            const Gdiplus::FontFamily font_family(L"Mikachan-P");
            const Gdiplus::Font font(&font_family, 48);
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

        static const ::PAINTSTRUCT get_paint_info(
            const window_handle_type window_handle
        )
        {
            ::PAINTSTRUCT paint_info;

            if (::BeginPaint(window_handle, &paint_info) == NULL)
                throw std::runtime_error("Can't begin paint!");

            return paint_info;
        }


        // variables

        const window_handle_type m_window_handle;

        ::PAINTSTRUCT m_paint_info;

        Gdiplus::Graphics m_graphics;


    };


}}}

#endif
