/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::canvas.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_CANVAS_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_CANVAS_H

//#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
//#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a canvas for Win32 platforms.

        \tparam Handle     A handle type for the native interface.
        \tparam Size       A size type.
        \tparam String     A string type.
        \tparam Dimension  A dimension type.
        \tparam Encoder    An encoder type.
        \tparam Background A background type.
        \tparam Font       A font type.
        \tparam Picture    A picture type.
    */
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

        //! The handle type for the native interface.
        typedef Handle handle_type;

        //! The size type.
        typedef Size size_type;

        //! The string type.
        typedef String string_type;

        //! The dimension type.
        typedef Dimension dimension_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The background type.
        typedef Background background_type;

        //! The font type.
        typedef Font font_type;

        //! The picture type.
        typedef Picture picture_type;


        // constructors and destructor

        /*!
            \brief Destroys the canvas.
        */
        virtual ~canvas()
        TETENGO2_NOEXCEPT
        {}


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
            \brief Returns the installed font families.

            \return The installed font families.
        */
        std::vector<string_type> installed_font_families()
        const
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const ::INT count = font_collection.GetFamilyCount();
            const boost::scoped_array<Gdiplus::FontFamily> p_families(
                new Gdiplus::FontFamily[count]
            );
            ::INT actual_count = 0;

            const Gdiplus::Status status =
                font_collection.GetFamilies(
                    count, p_families.get(), &actual_count
                );
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get installed font families.")
                );
            }

            std::vector<string_type> families;
            families.reserve(actual_count);
            for (::INT i = 0; i < actual_count; ++i)
            {
                wchar_t family_name[LF_FACESIZE];
                const Gdiplus::Status family_name_status =
                    p_families[i].GetFamilyName(family_name);
                if (family_name_status != Gdiplus::Ok)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't get font family name.")
                    );
                }
                families.push_back(family_name);
            }
            return families;
        }

        /*!
            \brief Fills a rectangle region.

            \tparam P A position type.
            \tparam D A dimension type.

            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param background A background.
        */
        template <typename P, typename D>
        void fill_rectangle(
            const P&               position,
            const D&               dimension,
            const background_type& background
        )
        {
            if (background.handle() == NULL) return;

            const Gdiplus::Rect rectangle(
                gui::to_pixels< ::INT>(gui::position<P>::left(position)),
                gui::to_pixels< ::INT>(gui::position<P>::top(position)),
                gui::to_pixels< ::INT>(gui::dimension<D>::width(dimension)),
                gui::to_pixels< ::INT>(gui::dimension<D>::height(dimension))
            );
            m_graphics.FillRectangle(background.handle(), rectangle);
        }

        /*!
            \brief Calculates the dimension of a text.

            \param text A text.

            \return The dimension of the text.
        */
        dimension_type calc_text_dimension(const string_type& text)
        const
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const boost::scoped_ptr<Gdiplus::Font> p_gdiplus_font(
                create_gdiplus_font(m_font, font_collection)
            );

            const Gdiplus::RectF layout(
                0,
                0,
                std::numeric_limits<Gdiplus::REAL>::max(),
                std::numeric_limits<Gdiplus::REAL>::max()
            );
            Gdiplus::RectF bounding;
            const Gdiplus::Status result =
                m_graphics.MeasureString(
                    text.c_str(),
                    static_cast< ::INT>(text.length()),
                    p_gdiplus_font.get(),
                    layout,
                    Gdiplus::StringFormat::GenericTypographic(),
                    &bounding
                );
            if (result != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't measure text!")
                );
            }

            return dimension_type(
                gui::to_unit<
                    typename gui::dimension<dimension_type>::width_type
                >(bounding.Width),
                gui::to_unit<
                    typename gui::dimension<dimension_type>::height_type
                >(bounding.Height)
            );
        }

        /*!
            \brief Draws a text.

            \tparam S A string type.
            \tparam P A position type.

            \param text     A text to draw.
            \param position A position where the text is drawn.

            \throw std::runtime_error When the text cannot be drawn.
        */
        template <typename S, typename P>
        void draw_text(S&& text, const P& position)
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const boost::scoped_ptr<Gdiplus::Font> p_gdiplus_font(
                create_gdiplus_font(m_font, font_collection)
            );
            const Gdiplus::SolidBrush brush(
                Gdiplus::Color(128, 255, 0, 0)
            );

            const std::wstring encoded_text =
                encoder().encode(std::forward<S>(text));
            const Gdiplus::Status result = m_graphics.DrawString(
                encoded_text.c_str(),
                static_cast< ::INT>(encoded_text.length()),
                p_gdiplus_font.get(),
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

        /*!
            \brief Paints a picture.

            \tparam P A position type.
            \tparam D A dimension type.

            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.

            \throw std::runtime_error When the picture cannot be painted.
        */
        template <typename P, typename D /* = typename P::dimension_type */>
        void paint_picture(
            const picture_type& picture,
            const P&            position,
            const D&            dimension /* = picture.dimension() */
        )
        {
            const Gdiplus::Status result =
                m_graphics.DrawImage(
                    &const_cast<picture_type&>(picture).gdiplus_bitmap(),
                    to_pixels< ::INT>(gui::position<P>::left(position)),
                    to_pixels< ::INT>(gui::position<P>::top(position)),
                    to_pixels< ::INT>(gui::dimension<D>::width(dimension)),
                    to_pixels< ::INT>(gui::dimension<D>::height(dimension))
                );
            if (result != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't paint picture!")
                );
            }
        }

#if !defined(DOCUMENTATION)
        template <typename P>
        void paint_picture(const picture_type& picture, const P& position)
        {
            paint_picture(picture, position, picture.dimension());
        }
#endif

        /*!
            \brief Returns the GDI+ graphics.

            \return The GDI+ graphics.
        */
        Gdiplus::Graphics& gdiplus_graphics()
        {
            return m_graphics;
        }

        /*!
            \brief Returns the GDI+ graphics.

            \return The GDI+ graphics.
        */
        const Gdiplus::Graphics& gdiplus_graphics()
        const
        {
            return m_graphics;
        }

        
    protected:
        // constructors

        /*!
            \brief Creates a canvas.

            \tparam DeviceHandle A device handle type.

            \param device_handle A device handle.
        */
        template <typename DeviceHandle>
        canvas(const DeviceHandle device_handle)
        :
        m_graphics(device_handle),
        m_font(font_type::dialog_font())
        {
            m_graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            m_graphics.SetTextRenderingHint(
                Gdiplus::TextRenderingHintClearTypeGridFit
            );
        }


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static std::auto_ptr<Gdiplus::Font> create_gdiplus_font(
            const font_type&               font,
            const Gdiplus::FontCollection& font_collection,
            const size_type                fallback_level = 0
        )
        {
            if (fallback_level > 2)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Font is not available.")
                );
            }

            const string_type& font_family =
                fallback_level < 1 ?
                font.family() : font_type::dialog_font().family();
            const Gdiplus::FontFamily gdiplus_font_family(
                font_family.c_str(), &font_collection
            );
            if (!gdiplus_font_family.IsAvailable())
            {
                return create_gdiplus_font(
                    font, font_collection, fallback_level + 1
                );
            }

            const Gdiplus::REAL font_size =
                fallback_level < 2 ?
                static_cast<Gdiplus::REAL>(font.size()) :
                static_cast<Gdiplus::REAL>(font_type::dialog_font().size());
            const ::INT font_style =
                fallback_level < 2 ?
                get_font_style(font) :
                get_font_style(font_type::dialog_font());
            std::auto_ptr<Gdiplus::Font> p_gdiplus_font(
                new Gdiplus::Font(
                    &gdiplus_font_family,
                    font_size,
                    font_style,
                    Gdiplus::UnitPixel
                )
            );
            if (!p_gdiplus_font->IsAvailable())
            {
                return create_gdiplus_font(
                    font, font_collection, fallback_level + 1
                );
            }

            return p_gdiplus_font;
        }

        static ::INT get_font_style(const font_type& font)
        {
            ::INT style = Gdiplus::FontStyleRegular;

            if (font.bold())
                style |= Gdiplus::FontStyleBold;
            if (font.italic())
                style |= Gdiplus::FontStyleItalic;
            if (font.underline())
                style |= Gdiplus::FontStyleUnderline;
            if (font.strikeout())
                style |= Gdiplus::FontStyleStrikeout;

            return style;
        }


        // variables

        Gdiplus::Graphics m_graphics;

        font_type m_font;


    };


}}}}}


#endif
