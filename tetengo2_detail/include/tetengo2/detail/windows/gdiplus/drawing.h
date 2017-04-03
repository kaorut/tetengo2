/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::drawing.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
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
#include <wincodec.h>

#include <tetengo2/detail/windows/com_ptr.h>
#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/font.h>
#include <tetengo2/detail/windows/gdiplus/error_category.h>
#include <tetengo2/detail/windows/picture.h>
#include <tetengo2/gui/measure.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace windows { namespace gdiplus
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        class background_details : private boost::noncopyable
        {
        public:
            background_details()
            :
            m_p_brush()
            {}

            explicit background_details(std::unique_ptr<Gdiplus::Brush> p_brush)
            :
            m_p_brush(std::move(p_brush))
            {}

            const Gdiplus::Brush* get()
            const
            {
                return m_p_brush.get();
            }

        private:
            const std::unique_ptr<Gdiplus::Brush> m_p_brush;

        };

        class canvas_details : private boost::noncopyable
        {
        public:
            template <typename HandleOrWidgetDetails>
            canvas_details(const HandleOrWidgetDetails& handle_or_widget_details)
            :
            m_p_widget_graphics(create_canvas_impl(handle_or_widget_details)),
            m_p_memory_image(),
            m_p_memory_graphics()
            {}

            Gdiplus::Graphics& get()
            const
            {
                if (m_p_memory_graphics)
                    return *m_p_memory_graphics;
                else
                    return *m_p_widget_graphics;
            }

            void begin_transaction(const ::INT width, const ::INT height)
            {
                if (m_p_memory_graphics)
                {
                    BOOST_THROW_EXCEPTION((std::logic_error{ "Another transaction has already begun." }));
                }

                m_p_memory_image = stdalt::make_unique<Gdiplus::Bitmap>(width, height, m_p_widget_graphics.get());
                m_p_memory_graphics = stdalt::make_unique<Gdiplus::Graphics>(m_p_memory_image.get());
                initialize_canvas(*m_p_memory_graphics);
            }

            void end_transaction()
            {
                if (!m_p_memory_graphics)
                {
                    BOOST_THROW_EXCEPTION((std::logic_error{ "No transaction has begun yet." }));
                }

                const auto status = m_p_widget_graphics->DrawImage(m_p_memory_image.get(), 0, 0);
                if (status != Gdiplus::Ok)
                {
                    BOOST_THROW_EXCEPTION((
                        std::system_error{
                            std::error_code{ status, gdiplus_category() },
                            "Can't paint the memory image to the widget surface."
                        }
                    ));
                }

                m_p_memory_graphics.reset();
                m_p_memory_image.reset();
            }

        private:
            template <typename HandleOrWidgetDetails>
            static std::unique_ptr<Gdiplus::Graphics> create_canvas_impl(
                const HandleOrWidgetDetails& handle,
                typename std::enable_if<std::is_convertible<HandleOrWidgetDetails, ::HDC>::value>::type* = nullptr
            )
            {
                auto p_canvas = stdalt::make_unique<Gdiplus::Graphics>(handle);

                initialize_canvas(*p_canvas);

                return std::move(p_canvas);
            }

            template <typename HandleOrWidgetDetails>
            static std::unique_ptr<Gdiplus::Graphics> create_canvas_impl(
                const HandleOrWidgetDetails& widget_details,
                typename std::enable_if<!std::is_convertible<HandleOrWidgetDetails, ::HDC>::value>::type* = nullptr
            )
            {
                auto p_canvas = stdalt::make_unique<Gdiplus::Graphics>(widget_details.handle.get());

                initialize_canvas(*p_canvas);

                return std::move(p_canvas);
            }

            static void initialize_canvas(Gdiplus::Graphics& canvas)
            {
                canvas.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
                canvas.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
            }

            const std::unique_ptr<Gdiplus::Graphics> m_p_widget_graphics;

            std::unique_ptr<Gdiplus::Image> m_p_memory_image;

            std::unique_ptr<Gdiplus::Graphics> m_p_memory_graphics;

        };

    }
#endif


    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing : private boost::noncopyable
    {
    public:
        // types

        //! The background details type.
        using background_details_type = detail::background_details;

        //! The background details pointer type.
        using background_details_ptr_type = std::unique_ptr<background_details_type>;

        //! The picture details type.
        using picture_details_type = picture::details_type;

        //! The picture details pointer type.
        using picture_details_ptr_type = picture::details_ptr_type;

        //! The canvas details type.
        using canvas_details_type = detail::canvas_details;

        //! The canvas details pointer type.
        using canvas_details_ptr_type = std::unique_ptr<canvas_details_type>;


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
            return stdalt::make_unique<canvas_details_type>(handle_or_widget_details);
        }

        /*!
            \brief Begins a transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \tparam Dimension A dimension type.

            \param canvas    A canvas.
            \param dimension A dimension.

            \throw std::logic_error When another transaction has not ended yet.
        */
        template <typename Dimension>
        static void begin_transaction(canvas_details_type& canvas, const Dimension& dimension)
        {
            canvas.begin_transaction(
                gui::to_pixels< ::INT>(gui::dimension<Dimension>::width(dimension)),
                gui::to_pixels< ::INT>(gui::dimension<Dimension>::height(dimension))
            );
        }

        /*!
            \brief Ends the transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \param canvas A canvas.

            \throw std::logic_error When no transaction has begun.
        */
        static void end_transaction(canvas_details_type& canvas)
        {
            canvas.end_transaction();
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
                stdalt::make_unique<background_details_type>(
                    stdalt::make_unique<Gdiplus::SolidBrush>(
                        Gdiplus::Color(color.alpha(), color.red(), color.green(), color.blue())
                    )
                );
        }

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        static std::unique_ptr<background_details_type> create_transparent_background()
        {
            return stdalt::make_unique<background_details_type>();
        }

        /*!
            \brief Creates a picture.

            \tparam Dimension A dimension type.

            \param dimension A dimension.

            \return A unique pointer to a picture.
        */
        template <typename Dimension>
        static picture_details_ptr_type create_picture(const Dimension& dimension)
        {
            return picture::create(dimension);
        }

        /*!
            \brief Reads a picture.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        inline static picture_details_ptr_type read_picture(const boost::filesystem::path& path)
        {
            return picture::read(path);
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
            return picture::dimension<Dimension>(picture);
        }

        /*!
            \brief Draws a line.

            \tparam Position A position type.
            \tparam Size     A size type.
            \tparam Color    A color type.

            \param canvas A canvas.
            \param from   A beginning position.
            \param to     An ending position.
            \param width  A width.
            \param style  A style.
            \param color  A color.
        */
        template <typename Position, typename Size, typename Color>
        static void draw_line(
            canvas_details_type& canvas,
            const Position&      from,
            const Position&      to,
            const Size           width,
            const int            style,
            const Color&         color
        )
        {
            const Gdiplus::Pen pen{
                Gdiplus::Color{ color.alpha(), color.red(), color.green(), color.blue() },
                gui::to_pixels<Gdiplus::REAL>(width)
            };
            const Gdiplus::PointF gdiplus_from{
                gui::to_pixels<Gdiplus::REAL>(gui::position<Position>::left(from)),
                gui::to_pixels<Gdiplus::REAL>(gui::position<Position>::top(from))
            };
            const Gdiplus::PointF gdiplus_to{
                gui::to_pixels<Gdiplus::REAL>(gui::position<Position>::left(to)),
                gui::to_pixels<Gdiplus::REAL>(gui::position<Position>::top(to))
            };
            const auto status = canvas.get().DrawLine(&pen, gdiplus_from, gdiplus_to);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't draw a line." }
                ));
            }
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
            const ::RECT rect{
                gui::to_pixels< ::LONG>(gui::position<Position>::left(position)),
                gui::to_pixels< ::LONG>(gui::position<Position>::top(position)),
                gui::to_pixels< ::LONG>(gui::dimension<Dimension>::width(dimension)),
                gui::to_pixels< ::LONG>(gui::dimension<Dimension>::height(dimension))
            };
            if (::DrawFocusRect(canvas.get().GetHDC(), &rect) == 0)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ Gdiplus::Win32Error, gdiplus_category() }, "Can't draw a focus rectangle."
                    }
                ));
            }
        }

        /*!
            \brief Draws a rectangle.

            \tparam Position   A position type.
            \tparam Dimension  A dimension type.
            \tparam Size       A size type.
            \tparam Color      A color type.

            \param canvas     A canvas.
            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param width      A width.
            \param style      A style.
            \param color      A color.

            \throw std::system_error When the rectangle cannot be filled.
        */
        template <typename Position, typename Dimension, typename Size, typename Color>
        static void draw_rectangle(
            canvas_details_type& canvas,
            const Position&      position,
            const Dimension&     dimension,
            const Size           width,
            const int            style,
            const Color&         color
        );

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
            const auto& background_details = background.details();
            if (!background_details.get()) return;

            const Gdiplus::Rect rectangle{
                gui::to_pixels< ::INT>(gui::position<Position>::left(position)),
                gui::to_pixels< ::INT>(gui::position<Position>::top(position)),
                gui::to_pixels< ::INT>(gui::dimension<Dimension>::width(dimension)),
                gui::to_pixels< ::INT>(gui::dimension<Dimension>::height(dimension))
            };
            const auto status = canvas.get().FillRectangle(background_details.get(), rectangle);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't fill a rectangle." }
                ));
            }
        }

        /*!
            \brief Draws a polygon.

            \tparam PositionIterator A position iterator type.
            \tparam Size             A size type.
            \tparam Color            A color type.

            \param canvas         A canvas.
            \param position_first A first position of a region.
            \param position_last  A last position of a region.
            \param width          A width.
            \param style          A style.
            \param color          A color.

            \throw std::system_error When the polygon cannot be filled.
        */
        template <typename PositionIterator, typename Size, typename Color>
        static void draw_polygon(
            canvas_details_type&   canvas,
            const PositionIterator position_first,
            const PositionIterator position_last,
            const Size             width,
            const int              style,
            const Color&           color
        )
        {
            const Gdiplus::Pen pen{
                Gdiplus::Color{ color.alpha(), color.red(), color.green(), color.blue() },
                gui::to_pixels<Gdiplus::REAL>(width)
            };
            const auto points = to_gdiplus_points(position_first, position_last);
            const auto status = canvas.get().DrawPolygon(&pen, points.data(), static_cast< ::INT>(points.size()));
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't draw a polygon." }
                ));
            }
        }

        /*!
            \brief Fills a polygon region.

            \tparam PositionIterator A position iterator type.
            \tparam Background       A background type.

            \param canvas         A canvas.
            \param position_first A first position of a region.
            \param position_last  A last position of a region.
            \param background     A background.

            \throw std::system_error When the polygon cannot be filled.
        */
        template <typename PositionIterator, typename Background>
        static void fill_polygon(
            canvas_details_type&   canvas,
            const PositionIterator position_first,
            const PositionIterator position_last,
            const Background&      background
        )
        {
            const auto& background_details = background.details();
            if (!background_details.get()) return;

            const auto points = to_gdiplus_points(position_first, position_last);
            const auto status =
                canvas.get().FillPolygon(background_details.get(), points.data(), static_cast< ::INT>(points.size()));
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't fill a polygon." }
                ));
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
            const auto log_font = get_message_font();

            assert(log_font.lfHeight < 0);
            return
                Font{
                    log_font.lfFaceName,
                    static_cast<typename Font::size_type>(-log_font.lfHeight),
                    log_font.lfWeight >= FW_BOLD,
                    log_font.lfItalic != 0,
                    log_font.lfUnderline != 0,
                    log_font.lfStrikeOut != 0
                };
        }

        /*!
            \brief Calculates the dimension of a text.

            \tparam Dimension A dimension type.
            \tparam Font      A font type.
            \tparam String    A string type.
            \tparam Encoder   An encoder type.

            \param canvas    A canvas.
            \param font      A font.
            \param text      A text.
            \param encoder   An encoder.
            \param max_width A maximum width. When 0 is specified, the width is infinite.

            \return The dimension of the text.

            \throw std::system_error When the dimention of a text cannot be calculated.
        */
        template <typename Dimension, typename Font, typename String, typename Encoder>
        static Dimension calc_text_dimension(
            const canvas_details_type&                            canvas,
            const Font&                                           font,
            const String&                                         text,
            const Encoder&                                        encoder,
            const typename gui::dimension<Dimension>::width_type& max_width
        )
        {
            const auto encoded_text = encoder.encode(text);

            const Gdiplus::InstalledFontCollection font_collection;
            const auto p_gdiplus_font = create_gdiplus_font<String>(font, font_collection, encoder);

            const Gdiplus::REAL gdiplus_max_width =
                max_width == typename gui::dimension<Dimension>::width_type{ 0 } ?
                std::numeric_limits<Gdiplus::REAL>::max() : gui::to_pixels<Gdiplus::REAL>(max_width);
            const Gdiplus::RectF layout{
                0, 0, gdiplus_max_width, std::numeric_limits<Gdiplus::REAL>::max()
            };
            Gdiplus::RectF bounding;
            const auto status =
                canvas.get().MeasureString(
                    encoded_text.c_str(),
                    static_cast< ::INT>(encoded_text.length()),
                    p_gdiplus_font.get(),
                    layout,
                    Gdiplus::StringFormat::GenericTypographic(),
                    &bounding
                );
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't measure text!" }
                ));
            }

            return
                {
                    gui::to_unit<typename gui::dimension<Dimension>::width_type>(bounding.Width),
                    gui::to_unit<typename gui::dimension<Dimension>::height_type>(bounding.Height)
                };
        }

        /*!
            \brief Calculates the dimension of a vertical text.

            \tparam Dimension A dimension type.
            \tparam Font      A font type.
            \tparam String    A string type.
            \tparam Encoder   An encoder type.

            \param canvas  A canvas.
            \param font    A font.
            \param text    A text.
            \param encoder An encoder.

            \return The dimension of the vertical text.

            \throw std::system_error When the dimention of a vertical text cannot be calculated.
        */
        template <typename Dimension, typename Font, typename String, typename Encoder>
        static Dimension calc_vertical_text_dimension(
            const canvas_details_type& canvas,
            const Font&                font,
            const String&              text,
            const Encoder&             encoder
        );

        /*!
            \brief Draws a text.

            \tparam Font     A font type.
            \tparam String   A string type.
            \tparam Encoder  An encoder type.
            \tparam Position A position type.
            \tparam Width    A width type.
            \tparam Color    A color type.

            \param canvas    A canvas.
            \param font      A font.
            \param text      A text to draw.
            \param encoder   An encoder.
            \param position  A position where the text is drawn.
            \param max_width A maximum width. When 0 is specified, the width is infinite.
            \param color     A color.
            \param angle     A clockwise angle in radians.

            \throw std::system_error When the text cannot be drawn.
        */
        template <typename Font, typename String, typename Encoder, typename Position, typename Width, typename Color>
        static void draw_text(
            canvas_details_type& canvas,
            const Font&          font,
            const String&        text,
            const Encoder&       encoder,
            const Position&      position,
            const Width&         max_width,
            const Color&         color,
            const double         angle
        )
        {
            const auto encoded_text = encoder.encode(text);

            const Gdiplus::InstalledFontCollection font_collection;
            const auto p_gdiplus_font = create_gdiplus_font<String>(font, font_collection, encoder);

            const auto p_solid_brush = create_solid_background(color);

            const Gdiplus::PointF gdiplus_point{
                gui::to_pixels<Gdiplus::REAL>(gui::position<Position>::left(position)),
                gui::to_pixels<Gdiplus::REAL>(gui::position<Position>::top(position))
            };
            const Gdiplus::REAL gdiplus_max_width =
                max_width == Width{ 0 } ?
                std::numeric_limits<Gdiplus::REAL>::max() : gui::to_pixels<Gdiplus::REAL>(max_width);
            const Gdiplus::RectF layout{
                gdiplus_point.X, gdiplus_point.Y, gdiplus_max_width, std::numeric_limits<Gdiplus::REAL>::max()
            };

            Gdiplus::Matrix original_matrix;
            const auto get_transform_status = canvas.get().GetTransform(&original_matrix);
            if (get_transform_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ get_transform_status, gdiplus_category() }, "Can't get transform!"
                    }
                ));
            }
            Gdiplus::Matrix rotating_matrix;
            rotating_matrix.RotateAt(radian_to_degree(angle), gdiplus_point);
            const auto set_transform_status = canvas.get().SetTransform(&rotating_matrix);
            if (set_transform_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ set_transform_status, gdiplus_category() }, "Can't set transform!"
                    }
                ));
            }
            BOOST_SCOPE_EXIT((&canvas)(&original_matrix))
            {
                canvas.get().SetTransform(&original_matrix);
            } BOOST_SCOPE_EXIT_END;

            const auto draw_string_status =
                canvas.get().DrawString(
                    encoded_text.c_str(),
                    static_cast< ::INT>(encoded_text.length()),
                    p_gdiplus_font.get(), 
                    layout,
                    Gdiplus::StringFormat::GenericTypographic(),
                    p_solid_brush->get()
                );
            if (draw_string_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ draw_string_status, gdiplus_category() }, "Can't draw text!" }
                ));
            }
        }

        /*!
            \brief Draws a vertical text.

            \tparam Font      A font type.
            \tparam String    A string type.
            \tparam Encoder   An encoder type.
            \tparam Position  A position type.
            \tparam Dimension A dimension type.
            \tparam Color     A color type.

            \param canvas   A canvas.
            \param font     A font.
            \param text     A text to draw.
            \param encoder  An encoder.
            \param position A position where the text is drawn.
            \param color    A color.

            \throw std::system_error When the text cannot be drawn.
        */
        template <
            typename Font,
            typename String,
            typename Encoder,
            typename Position,
            typename Dimension,
            typename Color
        >
        static void draw_vertical_text(
            canvas_details_type& canvas,
            const Font&          font,
            const String&        text,
            const Encoder&       encoder,
            const Position&      position,
            const Color&         color
        );

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
            auto& picture_details = const_cast<Picture&>(picture).details();

            ::WICPixelFormatGUID pixel_format_guid{};
            const auto get_pixel_format_hr = picture_details.GetPixelFormat(&pixel_format_guid);
            if (FAILED(get_pixel_format_hr))
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ get_pixel_format_hr, wic_category() }, "Can't get pixel format."
                    }
                ));
            }

            ::UINT width = 0;
            ::UINT height = 0;
            const auto get_size_hr = picture_details.GetSize(&width, &height);
            if (FAILED(get_size_hr))
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ get_size_hr, wic_category() }, "Can't get size of picture." }
                ));
            }
            const ::UINT stride = width * sizeof(Gdiplus::ARGB);
            const ::UINT buffer_size = stride * height;
            std::vector< ::BYTE> buffer(buffer_size, 0);

            const ::WICRect rectangle{ 0, 0, static_cast< ::INT>(width), static_cast< ::INT>(height) };
            const auto copy_pixels_hr = picture_details.CopyPixels(&rectangle, stride, buffer_size, buffer.data());
            if (FAILED(copy_pixels_hr))
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ copy_pixels_hr, wic_category() }, "Can't copy pixels of picture."
                    }
                ));
            }

            Gdiplus::Bitmap bitmap{
                static_cast< ::INT>(width),
                static_cast< ::INT>(height),
                static_cast< ::INT>(stride),
                PixelFormat32bppRGB,
                buffer.data()
            };
            const auto status =
                canvas.get().DrawImage(
                    &bitmap,
                    gui::to_pixels< ::INT>(gui::position<Position>::left(position)),
                    gui::to_pixels< ::INT>(gui::position<Position>::top(position)),
                    gui::to_pixels< ::INT>(gui::dimension<Dimension>::width(dimension)),
                    gui::to_pixels< ::INT>(gui::dimension<Dimension>::height(dimension))
                );
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't paint picture!" }
                ));
            }
        }

        /*!
            \brief Paints an icon.

            \tparam Icon     A icon type.
            \tparam Position A position type.

            \param canvas   A canvas.
            \param icon     An icon to paint.
            \param position A position where the picture is painted.

            \throw std::system_error When the icon cannot be painted.
        */
        template <typename Icon, typename Position>
        static void paint_icon(canvas_details_type& canvas, const Icon& icon, const Position& position)
        {
            using dimension_type = typename Icon::dimension_type;
            const ::BOOL result =
                ::DrawIconEx(
                    canvas.get().GetHDC(),
                    gui::to_pixels<int>(gui::position<Position>::left(position)),
                    gui::to_pixels<int>(gui::position<Position>::top(position)),
                    icon.details().big_icon_handle.get(),
                    gui::to_pixels<int>(gui::dimension<dimension_type>::width(icon.dimension())),
                    gui::to_pixels<int>(gui::dimension<dimension_type>::height(icon.dimension())),
                    0,
                    nullptr,
                    DI_NORMAL
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ Gdiplus::Win32Error, gdiplus_category() }, "Can't paint icon!"
                    }
                ));
            }
        }


    private:
        // static functions

        template <typename Iterator>
        static std::vector<Gdiplus::PointF> to_gdiplus_points(const Iterator first, const Iterator last)
        {
            std::vector<Gdiplus::PointF> points{};
            points.reserve(std::distance(first, last));

            using position_type = typename Iterator::value_type;
            std::transform(
                first,
                last,
                std::back_inserter(points),
                [] (const position_type& position)
                {
                    return
                        Gdiplus::PointF(
                            gui::to_pixels<Gdiplus::REAL>(gui::position<position_type>::left(position)),
                            gui::to_pixels<Gdiplus::REAL>(gui::position<position_type>::top(position))
                        );
                }
            );

            return points;
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
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ Gdiplus::FontFamilyNotFound, gdiplus_category() }, "Font is not available."
                    }
                ));
            }

            const auto& font_family = fallback_level < 1 ? font.family() : Font::dialog_font().family();
            const Gdiplus::FontFamily gdiplus_font_family{ encoder.encode(font_family).c_str(), &font_collection };
            if (!gdiplus_font_family.IsAvailable())
            {
                return create_gdiplus_font<String>(font, font_collection, encoder, fallback_level + 1);
            }

            const auto font_size =
                fallback_level < 2 ?
                static_cast<Gdiplus::REAL>(font.size()) : static_cast<Gdiplus::REAL>(Font::dialog_font().size());
            const auto font_style = fallback_level < 2 ? get_font_style(font) : get_font_style(Font::dialog_font());
            auto p_gdiplus_font =
                stdalt::make_unique<Gdiplus::Font>(&gdiplus_font_family, font_size, font_style, Gdiplus::UnitPixel);
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

        static Gdiplus::REAL radian_to_degree(const double radian)
        {
            return static_cast<Gdiplus::REAL>(radian * 180.0 / boost::math::constants::pi<double>());
        }


        // forbidden operations

        drawing()
        = delete;


   };


}}}}


#endif
