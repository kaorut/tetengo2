/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::drawing.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H

#include <cassert>
//#include <cstddef>
#include <limits>
#include <string>
//#include <utility>
#include <vector>
//#include <stdexcept>
//#include <type_traits>

#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max

#include "tetengo2.cpp0x.h"
#include "tetengo2.detail.windows.font.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows { namespace gdiplus
{
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing
    {
    public:
        // types

        //! The background details type.
        typedef Gdiplus::Brush background_details_type;

        //! The background details pointer type.
        typedef
            cpp0x::unique_ptr<background_details_type>::type
            background_details_ptr_type;

        //! The picture details type.
        typedef Gdiplus::Bitmap picture_details_type;

        //! The picture details pointer type.
        typedef
            cpp0x::unique_ptr<picture_details_type>::type
            picture_details_ptr_type;

        //! The canvas details type.
        typedef Gdiplus::Graphics canvas_details_type;

        //! The canvas details pointer type.
        typedef
            cpp0x::unique_ptr<canvas_details_type>::type
            canvas_details_ptr_type;


        // static functions

        /*!
            \brief Creates a solid background.

            \tparam Color A color type.

            \param color A color.

            \return A unique pointer to a solid background.
        */
        template <typename Color>
        static cpp0x::unique_ptr<background_details_type>::type
        create_solid_background(const Color& color)
        {
            return unique_ptr_upcast<background_details_type>(
                make_unique<Gdiplus::SolidBrush>(
                    Gdiplus::Color(
                        color.alpha(),
                        color.red(),
                        color.green(),
                        color.blue()
                    )
                )
            );
        }

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        static cpp0x::unique_ptr<background_details_type>::type
        create_transparent_background()
        {
            return cpp0x::unique_ptr<background_details_type>::type();
        }

        /*!
            \brief Creates a picture.

            \tparam Dimension A dimension type.
            \tparam Canvas    A canvas type.

            \param dimension A dimension.
            \param canvas    A canvas.

            \return A unique pointer to a picture.
        */
        template <typename Dimension, typename Canvas>
        static cpp0x::unique_ptr<picture_details_type>::type
        create_picture(const Dimension& dimension, const Canvas& canvas)
        {
            cpp0x::unique_ptr<picture_details_type>::type p_picture(
                unique_ptr_upcast<picture_details_type>(
                    make_unique<Gdiplus::Bitmap>(
                        to_pixels< ::INT>(
                            gui::dimension<Dimension>::width(dimension)
                        ),
                        to_pixels< ::INT>(
                            gui::dimension<Dimension>::height(dimension)
                        ),
                        &const_cast<Canvas&>(canvas).gdiplus_graphics()
                    )
                )
            );

            return std::move(p_picture);
        }

        /*!
            \brief Reads a picture.

            \tparam Path A path type.

            \param path A path.

            \return A unique pointer to a picture.
        */
        template <typename Path>
        static cpp0x::unique_ptr<picture_details_type>::type
        read_picture(const Path& path)
        {
            cpp0x::unique_ptr<picture_details_type>::type p_picture(
                unique_ptr_upcast<picture_details_type>(
                    make_unique<Gdiplus::Bitmap>(path.c_str())
                )
            );
            if (p_picture->GetLastStatus() != S_OK)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't read a picture.")
                );
            }

            return std::move(p_picture);
        }

        /*!
            \brief Returns the dimension of a picture.

            \tparam Dimension A dimension type.

            \param picture A picture.

            \return The dimension of the picture.
        */
        template <typename Dimension>
        static Dimension picture_dimension(
            const picture_details_type& picture
        )
        {
            return Dimension(
                gui::to_unit<typename gui::dimension<Dimension>::width_type>(
                    const_cast<picture_details_type&>(picture).GetWidth()
                ),
                gui::to_unit<typename gui::dimension<Dimension>::height_type>(
                    const_cast<picture_details_type&>(picture).GetHeight()
                )
            );
        }

        /*!
            \brief Creates a canvas.

            \tparam HandleOrWidgetDetails A handle type or a widget details
                                          type.

            \param handle_or_widget_details A handle or a widget details.

            \return A unique pointer to a canvas.
        */
        template <typename HandleOrWidgetDetails>
        static cpp0x::unique_ptr<canvas_details_type>::type
        create_canvas(const HandleOrWidgetDetails& handle_or_widget_details)
        {
            return create_canvas_impl(handle_or_widget_details);
        }

        /*!
            \brief Fills a rectangle region.

            \tparam Position   A position type.
            \tparam Dimension  A dimension type.
            \tparam Background A background type.

            \param canvas     A canvas.
            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param background A background.
        */
        template <typename Position, typename Dimension, typename Background>
        static void fill_rectangle(
            canvas_details_type& canvas,
            const Position&      position,
            const Dimension&     dimension,
            const Background&    background
        )
        {
            const boost::optional<const typename Background::details_type&>
            background_details = background.details();
            if (!background_details) return;

            const Gdiplus::Rect rectangle(
                gui::to_pixels< ::INT>(
                    gui::position<Position>::left(position)
                ),
                gui::to_pixels< ::INT>(
                    gui::position<Position>::top(position)
                ),
                gui::to_pixels< ::INT>(
                    gui::dimension<Dimension>::width(dimension)
                ),
                gui::to_pixels< ::INT>(
                    gui::dimension<Dimension>::height(dimension)
                )
            );
            canvas.FillRectangle(&*background_details, rectangle);
        }

        /*!
            \brief Makes a dialog font.

            \tparam Font A font type.

            \return A dialog font.
        */
        template <typename Font>
        static Font make_dialog_font()
        {
            const ::LOGFONTW log_font =
                tetengo2::detail::windows::get_message_font();

            assert(log_font.lfHeight < 0);
            return Font(
                log_font.lfFaceName,
                -log_font.lfHeight,
                log_font.lfWeight >= FW_BOLD,
                log_font.lfItalic != 0,
                log_font.lfUnderline != 0,
                log_font.lfStrikeOut != 0
            );
        }

        /*!
            \brief Returns the installed font families.

            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param encoder An encoder.

            \return The installed font families.
        */
        template <typename String, typename Encoder>
        static std::vector<String> installed_font_families(
            const Encoder& encoder
        )
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const ::INT count = font_collection.GetFamilyCount();
            std::vector<Gdiplus::FontFamily> gdiplus_families(
                count, Gdiplus::FontFamily()
            );
            ::INT actual_count = 0;

            const Gdiplus::Status status =
                font_collection.GetFamilies(
                    count, gdiplus_families.data(), &actual_count
                );
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get installed font families.")
                );
            }

            std::vector<String> families;
            families.reserve(actual_count);
            for (::INT i = 0; i < actual_count; ++i)
            {
                wchar_t family_name[LF_FACESIZE];
                const Gdiplus::Status family_name_status =
                    gdiplus_families[i].GetFamilyName(family_name);
                if (family_name_status != Gdiplus::Ok)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't get font family name.")
                    );
                }
                families.push_back(encoder.decode(family_name));
            }
            return families;
        }

        /*!
            \brief Calculates the dimension of a text.

            \tparam Dimension A dimension type.
            \tparam Font      A font type.
            \tparam String    A string type.
            \tparam Encoder   An encoder type.

            \param canvas  A canvas.
            \param font    A font.
            \param text    A text.
            \param encoder An encoder.

            \return The dimension of the text.
        */
        template <
            typename Dimension,
            typename Font,
            typename String,
            typename Encoder
        >
        static Dimension calc_text_dimension(
            const canvas_details_type& canvas,
            const Font&                font,
            const String&              text,
            const Encoder&             encoder
        )
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const typename cpp0x::unique_ptr<Gdiplus::Font>::type
            p_gdiplus_font(
                create_gdiplus_font<String>(font, font_collection, encoder)
            );

            const Gdiplus::RectF layout(
                0,
                0,
                std::numeric_limits<Gdiplus::REAL>::max(),
                std::numeric_limits<Gdiplus::REAL>::max()
            );
            Gdiplus::RectF bounding;
            const Gdiplus::Status result =
                canvas.MeasureString(
                    encoder.encode(text).c_str(),
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

            return Dimension(
                gui::to_unit<typename gui::dimension<Dimension>::width_type>(
                    bounding.Width
                ),
                gui::to_unit<typename gui::dimension<Dimension>::height_type>(
                    bounding.Height
                )
            );
        }

        /*!
            \brief Draws a text.

            \tparam Font     A font type.
            \tparam String   A string type.
            \tparam Encoder  An encoder type.
            \tparam Position A position type.

            \param canvas   A canvas.
            \param font     A font.
            \param text     A text to draw.
            \param encoder  An encoder.
            \param position A position where the text is drawn.

            \throw std::runtime_error When the text cannot be drawn.
        */
        template <
            typename Font,
            typename String,
            typename Encoder,
            typename Position
        >
        static void draw_text(
            canvas_details_type& canvas,
            const Font&          font,
            const String&        text,
            const Encoder&       encoder,
            const Position&      position
        )
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const typename cpp0x::unique_ptr<Gdiplus::Font>::type
            p_gdiplus_font(
                create_gdiplus_font<String>(font, font_collection, encoder)
            );
            const Gdiplus::SolidBrush brush(
                Gdiplus::Color(128, 255, 0, 0)
            );

            const std::wstring encoded_text = encoder.encode(text);
            const Gdiplus::Status result = canvas.DrawString(
                encoded_text.c_str(),
                static_cast< ::INT>(encoded_text.length()),
                p_gdiplus_font.get(),
                Gdiplus::PointF(
                    gui::to_pixels<Gdiplus::REAL>(
                        gui::position<Position>::left(position)
                    ),
                    gui::to_pixels<Gdiplus::REAL>(
                        gui::position<Position>::top(position)
                    )
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

            \tparam Picture   A picture type.
            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param canvas    A canvas.
            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.

            \throw std::runtime_error When the picture cannot be painted.
        */
        template <typename Picture, typename Position, typename Dimension>
        static void paint_picture(
            canvas_details_type& canvas,
            const Picture&       picture,
            const Position&      position,
            const Dimension&     dimension
        )
        {
            const boost::optional<typename Picture::details_type&>
            picture_details(const_cast<Picture&>(picture).details());
            if (!picture_details) return;

            const Gdiplus::Status result =
                canvas.DrawImage(
                    &*picture_details,
                    gui::to_pixels< ::INT>(
                        gui::position<Position>::left(position)
                    ),
                    gui::to_pixels< ::INT>(
                        gui::position<Position>::top(position)
                    ),
                    gui::to_pixels< ::INT>(
                        gui::dimension<Dimension>::width(dimension)
                    ),
                    gui::to_pixels< ::INT>(
                        gui::dimension<Dimension>::height(dimension)
                    )
                );
            if (result != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't paint picture!")
                );
            }
        }


    private:
        // static functions

        template <typename HandleOrWidgetDetails>
        static cpp0x::unique_ptr<canvas_details_type>::type
        create_canvas_impl(
            const HandleOrWidgetDetails& handle,
            typename std::enable_if<
                std::is_convertible<HandleOrWidgetDetails, ::HDC>::value
            >::type* = NULL
        )
        {
            cpp0x::unique_ptr<canvas_details_type>::type p_canvas(
                unique_ptr_upcast<canvas_details_type>(
                    make_unique<Gdiplus::Graphics>(handle)
                )
            );

            initialize_canvas(*p_canvas);

            return std::move(p_canvas);
        }

        template <typename HandleOrWidgetDetails>
        static cpp0x::unique_ptr<canvas_details_type>::type
        create_canvas_impl(
            const HandleOrWidgetDetails& widget_details,
            typename std::enable_if<
                std::is_convertible<
                    typename HandleOrWidgetDetails::first_type::pointer,
                    ::HWND
                >::value
            >::type* = NULL
        )
        {
            cpp0x::unique_ptr<canvas_details_type>::type p_canvas(
                unique_ptr_upcast<canvas_details_type>(
                    make_unique<Gdiplus::Graphics>(widget_details.first.get())
                )
            );

            initialize_canvas(*p_canvas);

            return std::move(p_canvas);
        }

        static void initialize_canvas(canvas_details_type& canvas)
        {
            canvas.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            canvas.SetTextRenderingHint(
                Gdiplus::TextRenderingHintClearTypeGridFit
            );
        }

        template <typename String, typename Font, typename Encoder>
        static typename cpp0x::unique_ptr<Gdiplus::Font>::type
        create_gdiplus_font(
            const Font&                    font,
            const Gdiplus::FontCollection& font_collection,
            const Encoder&                 encoder,
            const std::size_t              fallback_level = 0
        )
        {
            if (fallback_level > 2)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Font is not available.")
                );
            }

            const String& font_family =
                fallback_level < 1 ?
                font.family() : Font::dialog_font().family();
            const Gdiplus::FontFamily gdiplus_font_family(
                encoder.encode(font_family).c_str(), &font_collection
            );
            if (!gdiplus_font_family.IsAvailable())
            {
                return create_gdiplus_font<String>(
                    font, font_collection, encoder, fallback_level + 1
                );
            }

            const Gdiplus::REAL font_size =
                fallback_level < 2 ?
                static_cast<Gdiplus::REAL>(font.size()) :
                static_cast<Gdiplus::REAL>(Font::dialog_font().size());
            const ::INT font_style =
                fallback_level < 2 ?
                get_font_style(font) :
                get_font_style(Font::dialog_font());
            typename cpp0x::unique_ptr<Gdiplus::Font>::type p_gdiplus_font(
                make_unique<Gdiplus::Font>(
                    &gdiplus_font_family,
                    font_size,
                    font_style,
                    Gdiplus::UnitPixel
                )
            );
            if (!p_gdiplus_font->IsAvailable())
            {
                return create_gdiplus_font<String>(
                    font, font_collection, encoder, fallback_level + 1
                );
            }

            return std::move(p_gdiplus_font);
        }

        template <typename Font>
        static ::INT get_font_style(const Font& font)
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


        // forbidden operations

        drawing();


   };


}}}}


#endif
