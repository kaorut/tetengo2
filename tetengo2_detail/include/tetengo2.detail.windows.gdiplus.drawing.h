/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::drawing.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H

//#include <cassert>
//#include <cstddef>
#include <limits>
//#include <memory>
//#include <string>
//#include <system_error>
//#include <type_traits>
//#include <utility>

//#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>
//#if !defined(min) && !defined(DOCUMENTATION)
//#   define min(a, b) ((a) < (b) ? (a) : (b))
//#endif
//#if !defined(max) && !defined(DOCUMENTATION)
//#   define max(a, b) ((a) > (b) ? (a) : (b))
//#endif
//#include <GdiPlus.h>
//#undef min
//#undef max
#include <wincodec.h>

#include "tetengo2.detail.windows.com_ptr.h"
#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.detail.windows.font.h"
#include "tetengo2.detail.windows.gdiplus.error_category.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace windows { namespace gdiplus
{
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing : private boost::noncopyable
    {
    public:
        // types

        //! The background details type.
        typedef Gdiplus::Brush background_details_type;

        //! The background details pointer type.
        typedef std::unique_ptr<background_details_type> background_details_ptr_type;

        //! The picture details type.
        typedef ::IWICBitmapSource picture_details_type;

        //! The picture details pointer type.
        typedef unique_com_ptr<picture_details_type>::type picture_details_ptr_type;

        //! The canvas details type.
        typedef Gdiplus::Graphics canvas_details_type;

        //! The canvas details pointer type.
        typedef std::unique_ptr<canvas_details_type> canvas_details_ptr_type;


        // static functions

        /*!
            \brief Creates a canvas.

            \tparam HandleOrWidgetDetails A handle type or a widget details type.

            \param handle_or_widget_details A handle or a widget details.

            \return A unique pointer to a canvas.
        */
        template <typename HandleOrWidgetDetails>
        static std::unique_ptr<canvas_details_type> create_canvas(
            const HandleOrWidgetDetails& handle_or_widget_details
        )
        {
            return create_canvas_impl(handle_or_widget_details);
        }

        /*!
            \brief Creates a solid background.

            \tparam Color A color type.

            \param color A color.

            \return A unique pointer to a solid background.
        */
        template <typename Color>
        static std::unique_ptr<background_details_type> create_solid_background(const Color& color)
        {
            return
                make_unique<Gdiplus::SolidBrush>(
                    Gdiplus::Color(color.alpha(), color.red(), color.green(), color.blue())
                );
        }

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        static std::unique_ptr<background_details_type> create_transparent_background()
        {
            return std::unique_ptr<background_details_type>();
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
        static picture_details_ptr_type create_picture(const Dimension& dimension, const Canvas& canvas)
        {
            ::IWICBitmap* rp_bitmap = NULL;
            const ::HRESULT hr =
                wic_imaging_factory().CreateBitmap(
                    gui::to_pixels< ::INT>(gui::dimension<Dimension>::width(dimension)),
                    gui::to_pixels< ::INT>(gui::dimension<Dimension>::height(dimension)),
                    ::GUID_WICPixelFormat32bppRGBA,
                    WICBitmapCacheOnDemand,
                    &rp_bitmap
                );
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(hr, win32_category()), "Can't create WIC bitmap.")
                );
            }

            return picture_details_ptr_type(rp_bitmap);
        }

        /*!
            \brief Reads a picture.

            \tparam Path A path type.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        template <typename Path>
        static picture_details_ptr_type read_picture(const Path& path)
        {
            ::IWICBitmapDecoder* rp_decoder = NULL;
            const ::HRESULT create_decoder_hr =
                wic_imaging_factory().CreateDecoderFromFilename(
                    path.c_str(),
                    NULL,
                    GENERIC_READ,
                    WICDecodeMetadataCacheOnDemand,
                    &rp_decoder
                );
            if (FAILED(create_decoder_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(create_decoder_hr, win32_category()), "Can't create WIC decoder."
                    )
                );
            }
            const typename unique_com_ptr< ::IWICBitmapDecoder>::type p_decoder(rp_decoder);

            ::IWICBitmapFrameDecode* rp_frame = NULL;
            const ::HRESULT get_frame_hr = p_decoder->GetFrame(0, &rp_frame);
            if (FAILED(get_frame_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(get_frame_hr, win32_category()), "Can't create bitmap frame.")
                );
            }
            const typename unique_com_ptr< ::IWICBitmapFrameDecode>::type p_frame(rp_frame);

            ::IWICFormatConverter* rp_format_converter = NULL;
            const ::HRESULT create_format_converter_hr =
                wic_imaging_factory().CreateFormatConverter(&rp_format_converter);
            if (FAILED(create_format_converter_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(create_format_converter_hr, win32_category()), "Can't create format converter."
                    )
                );
            }
            typename unique_com_ptr< ::IWICFormatConverter>::type p_format_converter(rp_format_converter);

            const ::HRESULT initialize_hr =
                p_format_converter->Initialize(
                    p_frame.get(),
                    ::GUID_WICPixelFormat32bppPBGRA,
                    WICBitmapDitherTypeNone,
                    NULL,
                    0.0,
                    WICBitmapPaletteTypeCustom
                );
            if (FAILED(initialize_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(initialize_hr, win32_category()), "Can't initialize format converter."
                    )
                );
            }

            return picture_details_ptr_type(std::move(p_format_converter));
        }

        /*!
            \brief Returns the dimension of a picture.

            \tparam Dimension A dimension type.

            \param picture A picture.

            \return The dimension of the picture.
        */
        template <typename Dimension>
        static Dimension picture_dimension(const picture_details_type& picture)
        {
            ::UINT width = 0;
            ::UINT height = 0;
            const ::HRESULT hr = const_cast<picture_details_type&>(picture).GetSize(&width, &height);
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(hr, win32_category()), "Can't get size of picture.")
                );
            }

            return
                Dimension(
                    gui::to_unit<typename gui::dimension<Dimension>::width_type>(width),
                    gui::to_unit<typename gui::dimension<Dimension>::height_type>(height)
                );
        }

        /*!
            \brief Draws a focus indication.

            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param canvas    A canvas.
            \param position  A position of a region.
            \param dimension A dimension of a region.

            \throw std::system_error When the focus indication cannot be drawn.
        */
        template <typename Position, typename Dimension>
        static void draw_focus_indication(
            canvas_details_type& canvas,
            const Position&      position,
            const Dimension&     dimension
        )
        {
            const ::RECT rect = {
                0,
                0,
                gui::to_pixels< ::LONG>(gui::dimension<Dimension>::width(dimension)),
                gui::to_pixels< ::LONG>(gui::dimension<Dimension>::height(dimension))
            };
            if (::DrawFocusRect(canvas.GetHDC(), &rect) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(Gdiplus::Win32Error, gdiplus_category()), "Can't draw a focus rectangle."
                    )
                );
            }
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

            \throw std::system_error When the rectangle cannot be filled.
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
                gui::to_pixels< ::INT>(gui::position<Position>::left(position)),
                gui::to_pixels< ::INT>(gui::position<Position>::top(position)),
                gui::to_pixels< ::INT>(gui::dimension<Dimension>::width(dimension)),
                gui::to_pixels< ::INT>(gui::dimension<Dimension>::height(dimension))
            );
            const Gdiplus::Status status = canvas.FillRectangle(&*background_details, rectangle);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(status, gdiplus_category()), "Can't fill a rectangle.")
                );
            }
        }

        /*!
            \brief Makes a dialog font.

            \tparam Font A font type.

            \return A dialog font.
        */
        template <typename Font>
        static Font make_dialog_font()
        {
            const ::LOGFONTW log_font = get_message_font();

            assert(log_font.lfHeight < 0);
            return
                Font(
                    log_font.lfFaceName,
                    -log_font.lfHeight,
                    log_font.lfWeight >= FW_BOLD,
                    log_font.lfItalic != 0,
                    log_font.lfUnderline != 0,
                    log_font.lfStrikeOut != 0
                );
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

            \throw std::system_error When the dimention of a text cannot be calculated.
        */
        template <typename Dimension, typename Font, typename String, typename Encoder>
        static Dimension calc_text_dimension(
            const canvas_details_type& canvas,
            const Font&                font,
            const String&              text,
            const Encoder&             encoder
        )
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const std::unique_ptr<Gdiplus::Font> p_gdiplus_font(
                create_gdiplus_font<String>(font, font_collection, encoder)
            );

            const Gdiplus::RectF layout(
                0, 0, std::numeric_limits<Gdiplus::REAL>::max(), std::numeric_limits<Gdiplus::REAL>::max()
            );
            Gdiplus::RectF bounding;
            const Gdiplus::Status status =
                canvas.MeasureString(
                    encoder.encode(text).c_str(),
                    static_cast< ::INT>(text.length()),
                    p_gdiplus_font.get(),
                    layout,
                    Gdiplus::StringFormat::GenericTypographic(),
                    &bounding
                );
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(status, gdiplus_category()), "Can't measure text!")
                );
            }

            return
                Dimension(
                    gui::to_unit<typename gui::dimension<Dimension>::width_type>(bounding.Width),
                    gui::to_unit<typename gui::dimension<Dimension>::height_type>(bounding.Height)
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

            \throw std::system_error When the text cannot be drawn.
        */
        template <typename Font, typename String, typename Encoder, typename Position>
        static void draw_text(
            canvas_details_type& canvas,
            const Font&          font,
            const String&        text,
            const Encoder&       encoder,
            const Position&      position
        )
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const std::unique_ptr<Gdiplus::Font> p_gdiplus_font(
                create_gdiplus_font<String>(font, font_collection, encoder)
            );
            const Gdiplus::SolidBrush brush(Gdiplus::Color(128, 255, 0, 0));

            const std::wstring encoded_text = encoder.encode(text);
            const Gdiplus::Status status =
                canvas.DrawString(
                    encoded_text.c_str(),
                    static_cast< ::INT>(encoded_text.length()),
                    p_gdiplus_font.get(),
                    Gdiplus::PointF(
                        gui::to_pixels<Gdiplus::REAL>(gui::position<Position>::left(position)),
                        gui::to_pixels<Gdiplus::REAL>(gui::position<Position>::top(position))
                    ),
                    &brush
                );
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(status, gdiplus_category()), "Can't draw text!")
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

            \throw std::system_error When the picture cannot be painted.
        */
        template <typename Picture, typename Position, typename Dimension>
        static void paint_picture(
            canvas_details_type& canvas,
            const Picture&       picture,
            const Position&      position,
            const Dimension&     dimension
        )
        {
            const boost::optional<typename Picture::details_type&> picture_details(
                const_cast<Picture&>(picture).details()
            );
            if (!picture_details) return;

            ::WICPixelFormatGUID pixel_format_guid = {};
            const ::HRESULT get_pixel_format_hr = picture_details->GetPixelFormat(&pixel_format_guid);
            if (FAILED(get_pixel_format_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(get_pixel_format_hr, win32_category()), "Can't get pixel format."
                    )
                );
            }

            ::UINT width = 0;
            ::UINT height = 0;
            const ::HRESULT get_size_hr = picture_details->GetSize(&width, &height);
            if (FAILED(get_size_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(get_size_hr, win32_category()), "Can't get size of picture.")
                );
            }
            const ::UINT stride = width * sizeof(Gdiplus::ARGB);
            const ::UINT buffer_size = stride * height;
            std::vector< ::BYTE> buffer(buffer_size, 0);

            const ::WICRect rectangle = { 0, 0, width, height };
            const ::HRESULT copy_pixels_hr =
                picture_details->CopyPixels(&rectangle, stride, buffer_size, buffer.data());
            if (FAILED(copy_pixels_hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(copy_pixels_hr, win32_category()), "Can't copy pixels of picture."
                    )
                );
            }

            Gdiplus::Bitmap bitmap(width, height, stride, PixelFormat32bppRGB, buffer.data());
            const Gdiplus::Status status =
                canvas.DrawImage(
                    &bitmap,
                    gui::to_pixels< ::INT>(gui::position<Position>::left(position)),
                    gui::to_pixels< ::INT>(gui::position<Position>::top(position)),
                    gui::to_pixels< ::INT>(gui::dimension<Dimension>::width(dimension)),
                    gui::to_pixels< ::INT>(gui::dimension<Dimension>::height(dimension))
                );
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(status, gdiplus_category()), "Can't paint picture!")
                );
            }
        }


    private:
        // types

        typedef unique_com_ptr< ::IWICImagingFactory>::type wic_imaging_factory_ptr_type;


        // static functions

        static ::IWICImagingFactory& wic_imaging_factory()
        {
            static const wic_imaging_factory_ptr_type p_factory(create_wic_imaging_factory());
            return *p_factory;
        }

        static wic_imaging_factory_ptr_type create_wic_imaging_factory()
        {
            ::IWICImagingFactory* rp_factory = NULL;
            const ::HRESULT hr =
                ::CoCreateInstance(::CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&rp_factory));
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(hr, win32_category()), "Can't create WIC imaging factory.")
                );
            }

            return wic_imaging_factory_ptr_type(rp_factory);
        }

        template <typename HandleOrWidgetDetails>
        static std::unique_ptr<canvas_details_type> create_canvas_impl(
            const HandleOrWidgetDetails& handle,
            typename std::enable_if<std::is_convertible<HandleOrWidgetDetails, ::HDC>::value>::type* = NULL
        )
        {
            std::unique_ptr<canvas_details_type> p_canvas(make_unique<Gdiplus::Graphics>(handle));

            initialize_canvas(*p_canvas);

            return std::move(p_canvas);
        }

        template <typename HandleOrWidgetDetails>
        static std::unique_ptr<canvas_details_type> create_canvas_impl(
            const HandleOrWidgetDetails& widget_details,
            typename std::enable_if<
                std::is_convertible<typename HandleOrWidgetDetails::first_type::pointer, ::HWND>::value
            >::type* = NULL
        )
        {
            std::unique_ptr<canvas_details_type> p_canvas(make_unique<Gdiplus::Graphics>(widget_details.first.get()));

            initialize_canvas(*p_canvas);

            return std::move(p_canvas);
        }

        static void initialize_canvas(canvas_details_type& canvas)
        {
            canvas.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            canvas.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
        }

        template <typename String, typename Font, typename Encoder>
        static std::unique_ptr<Gdiplus::Font> create_gdiplus_font(
            const Font&                    font,
            const Gdiplus::FontCollection& font_collection,
            const Encoder&                 encoder,
            const std::size_t              fallback_level = 0
        )
        {
            if (fallback_level > 2)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(Gdiplus::FontFamilyNotFound, gdiplus_category()), "Font is not available."
                    )
                );
            }

            const String& font_family = fallback_level < 1 ? font.family() : Font::dialog_font().family();
            const Gdiplus::FontFamily gdiplus_font_family(encoder.encode(font_family).c_str(), &font_collection);
            if (!gdiplus_font_family.IsAvailable())
            {
                return create_gdiplus_font<String>(font, font_collection, encoder, fallback_level + 1);
            }

            const Gdiplus::REAL font_size =
                fallback_level < 2 ?
                static_cast<Gdiplus::REAL>(font.size()) : static_cast<Gdiplus::REAL>(Font::dialog_font().size());
            const ::INT font_style =
                fallback_level < 2 ? get_font_style(font) : get_font_style(Font::dialog_font());
            std::unique_ptr<Gdiplus::Font> p_gdiplus_font(
                make_unique<Gdiplus::Font>(&gdiplus_font_family, font_size, font_style, Gdiplus::UnitPixel)
            );
            if (!p_gdiplus_font->IsAvailable())
                return create_gdiplus_font<String>(font, font_collection, encoder, fallback_level + 1);

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
