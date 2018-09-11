/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::drawing.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/operators.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max
#include <wincodec.h>

#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/font.h>
#include <tetengo2/detail/windows/gdiplus/drawing.h>
#include <tetengo2/detail/windows/gdiplus/error_category.h>
#include <tetengo2/detail/windows/icon.h>
#include <tetengo2/detail/windows/picture.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui {
    class icon;

    namespace drawing {
        class background;
        class picture;
    }
}}


namespace tetengo2::detail::windows::gdiplus {
    class drawing::impl : private boost::noncopyable
    {
    public:
        // types

        using background_details_type = drawing::background_details_type;

        using background_details_ptr_type = drawing::background_details_ptr_type;

        using picture_details_type = drawing::picture_details_type;

        using picture_details_ptr_type = drawing::picture_details_ptr_type;

        using canvas_details_type = drawing::canvas_details_type;

        using canvas_details_ptr_type = drawing::canvas_details_ptr_type;


        // static functions

        static const drawing& instance()
        {
            static const drawing singleton{};
            return singleton;
        }


        // functions

        std::unique_ptr<canvas_details_type>
        create_canvas_impl(const base::widget::widget_details_type& widget_details) const
        {
            return std::make_unique<gdiplus_canvas_details_type>(widget_details);
        }

        std::unique_ptr<canvas_details_type> create_canvas_impl(const std::intptr_t canvas_handle) const
        {
            return std::make_unique<gdiplus_canvas_details_type>(canvas_handle);
        }

        void begin_transaction_impl(canvas_details_type& canvas, const gui::type_list::dimension_type& dimension) const
        {
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            static_cast<gdiplus_canvas_details_type&>(canvas).begin_transaction(
                static_cast<::INT>(dimension.width().to_pixels()), static_cast<::INT>(dimension.height().to_pixels()));
        }

        void end_transaction_impl(canvas_details_type& canvas) const
        {
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            static_cast<gdiplus_canvas_details_type&>(canvas).end_transaction();
        }

        std::unique_ptr<background_details_type> create_solid_background_impl(const gui::drawing::color& color) const
        {
            return std::make_unique<gdiplus_background_details_type>(std::make_unique<Gdiplus::SolidBrush>(
                Gdiplus::Color(color.alpha(), color.red(), color.green(), color.blue())));
        }

        std::unique_ptr<background_details_type> create_transparent_background_impl() const
        {
            return std::make_unique<gdiplus_background_details_type>();
        }

        std::unique_ptr<picture_details_type> create_picture_impl(const gui::type_list::dimension_type& dimension) const
        {
            return std::make_unique<gdiplus_picture_details_type>(dimension);
        }

        std::unique_ptr<picture_details_type> read_picture_impl(const tetengo2::stdalt::filesystem::path& path) const
        {
            return std::make_unique<gdiplus_picture_details_type>(path);
        }

        gui::type_list::dimension_type picture_dimension_impl(const picture_details_type& picture) const
        {
            assert(dynamic_cast<const gdiplus_picture_details_type*>(&picture));
            return picture::instance().dimension(*static_cast<const gdiplus_picture_details_type&>(picture).p_details);
        }

        void draw_line_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       from,
            const gui::type_list::position_type&       to,
            const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED const int     style,
            const gui::drawing::color&                 color) const
        {
            const Gdiplus::Pen    pen{ Gdiplus::Color{ color.alpha(), color.red(), color.green(), color.blue() },
                                    static_cast<Gdiplus::REAL>(width.to_pixels()) };
            const Gdiplus::PointF gdiplus_from{ static_cast<Gdiplus::REAL>(from.left().to_pixels()),
                                                static_cast<Gdiplus::REAL>(from.top().to_pixels()) };
            const Gdiplus::PointF gdiplus_to{ static_cast<Gdiplus::REAL>(to.left().to_pixels()),
                                              static_cast<Gdiplus::REAL>(to.top().to_pixels()) };
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            const auto status =
                static_cast<gdiplus_canvas_details_type&>(canvas).get().DrawLine(&pen, gdiplus_from, gdiplus_to);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't draw a line." }));
            }
        }

        void draw_focus_indication_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const
        {
            const ::RECT rect{ static_cast<::LONG>(position.left().to_pixels()),
                               static_cast<::LONG>(position.top().to_pixels()),
                               static_cast<::LONG>(dimension.width().to_pixels()),
                               static_cast<::LONG>(dimension.height().to_pixels()) };
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            if (::DrawFocusRect(static_cast<gdiplus_canvas_details_type&>(canvas).get().GetHDC(), &rect) == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ Gdiplus::Win32Error, gdiplus_category() },
                                                          "Can't draw a focus rectangle." }));
            }
        }

        void draw_rectangle_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED int                                        style,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::color& color) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error{ "Not implemented." });
        }

        void fill_rectangle_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const gui::drawing::background&       background) const
        {
            assert(dynamic_cast<const gdiplus_background_details_type*>(&background.details()));
            const auto& background_details = static_cast<const gdiplus_background_details_type&>(background.details());
            if (!background_details.get())
                return;

            const Gdiplus::Rect rectangle{ static_cast<::INT>(position.left().to_pixels()),
                                           static_cast<::INT>(position.top().to_pixels()),
                                           static_cast<::INT>(dimension.width().to_pixels()),
                                           static_cast<::INT>(dimension.height().to_pixels()) };
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            const auto status = static_cast<gdiplus_canvas_details_type&>(canvas).get().FillRectangle(
                background_details.get(), rectangle);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't fill a rectangle." }));
            }
        }

        void draw_polygon_impl(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::type_list::dimension_unit_type&        width,
            TETENGO2_STDALT_MAYBE_UNUSED const int            style,
            const gui::drawing::color&                        color) const
        {
            const Gdiplus::Pen pen{ Gdiplus::Color{ color.alpha(), color.red(), color.green(), color.blue() },
                                    static_cast<Gdiplus::REAL>(width.to_pixels()) };
            const auto         points = to_gdiplus_points(positions);
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            const auto status = static_cast<gdiplus_canvas_details_type&>(canvas).get().DrawPolygon(
                &pen, points.data(), static_cast<::INT>(points.size()));
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't draw a polygon." }));
            }
        }

        void fill_polygon_impl(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::drawing::background&                   background) const
        {
            assert(dynamic_cast<const gdiplus_background_details_type*>(&background.details()));
            const auto& background_details = static_cast<const gdiplus_background_details_type&>(background.details());
            if (!background_details.get())
                return;

            const auto points = to_gdiplus_points(positions);
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            const auto status = static_cast<gdiplus_canvas_details_type&>(canvas).get().FillPolygon(
                background_details.get(), points.data(), static_cast<::INT>(points.size()));
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't fill a polygon." }));
            }
        }

        gui::drawing::font make_dialog_font_impl() const
        {
            const auto log_font = get_message_font();

            assert(log_font.lfHeight < 0);
            return gui::drawing::font{
                log_font.lfFaceName,          static_cast<gui::drawing::font::size_type>(-log_font.lfHeight),
                log_font.lfWeight >= FW_BOLD, log_font.lfItalic != 0,
                log_font.lfUnderline != 0,    log_font.lfStrikeOut != 0
            };
        }

        gui::type_list::dimension_type calc_text_dimension_impl(
            const canvas_details_type&                 canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::dimension_unit_type& max_width) const
        {
            const auto encoded_text = native_drawing_encoder().encode(text);

            const Gdiplus::InstalledFontCollection font_collection;
            const auto                             p_gdiplus_font = create_gdiplus_font(font, font_collection);

            const Gdiplus::REAL gdiplus_max_width = max_width == gui::type_list::dimension_unit_type{} ?
                                                        std::numeric_limits<Gdiplus::REAL>::max() :
                                                        static_cast<Gdiplus::REAL>(max_width.to_pixels());
            const Gdiplus::RectF layout{ 0, 0, gdiplus_max_width, std::numeric_limits<Gdiplus::REAL>::max() };
            Gdiplus::RectF       bounding;
            assert(dynamic_cast<const gdiplus_canvas_details_type*>(&canvas));
            const auto status = static_cast<const gdiplus_canvas_details_type&>(canvas).get().MeasureString(
                encoded_text.c_str(),
                static_cast<::INT>(encoded_text.length()),
                p_gdiplus_font.get(),
                layout,
                Gdiplus::StringFormat::GenericTypographic(),
                &bounding);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't measure text!" }));
            }

            return gui::type_list::dimension_type{
                gui::type_list::dimension_unit_type::from_pixels(static_cast<type_list::size_type>(bounding.Width)),
                gui::type_list::dimension_unit_type::from_pixels(static_cast<type_list::size_type>(bounding.Height))
            };
        }

        gui::type_list::dimension_type calc_vertical_text_dimension_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error{ "Not implemented." });
        }

        void draw_text_impl(
            canvas_details_type&                       canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_unit_type& max_width,
            const gui::drawing::color&                 color,
            const double                               angle) const
        {
            const auto encoded_text = native_drawing_encoder().encode(text);

            const Gdiplus::InstalledFontCollection font_collection;
            const auto                             p_gdiplus_font = create_gdiplus_font(font, font_collection);

            const auto p_solid_brush = create_solid_background_impl(color);

            const Gdiplus::PointF gdiplus_point{ static_cast<Gdiplus::REAL>(position.left().to_pixels()),
                                                 static_cast<Gdiplus::REAL>(position.top().to_pixels()) };
            const Gdiplus::REAL   gdiplus_max_width = max_width == gui::type_list::dimension_unit_type{} ?
                                                        std::numeric_limits<Gdiplus::REAL>::max() :
                                                        static_cast<Gdiplus::REAL>(max_width.to_pixels());
            const Gdiplus::RectF layout{
                gdiplus_point.X, gdiplus_point.Y, gdiplus_max_width, std::numeric_limits<Gdiplus::REAL>::max()
            };

            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            auto&           canvas_details = static_cast<gdiplus_canvas_details_type&>(canvas);
            Gdiplus::Matrix original_matrix;
            const auto      get_transform_status = canvas_details.get().GetTransform(&original_matrix);
            if (get_transform_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ get_transform_status, gdiplus_category() },
                                                          "Can't get transform!" }));
            }
            Gdiplus::Matrix rotating_matrix;
            rotating_matrix.RotateAt(radian_to_degree(angle), gdiplus_point);
            const auto set_transform_status = canvas_details.get().SetTransform(&rotating_matrix);
            if (set_transform_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ set_transform_status, gdiplus_category() },
                                                          "Can't set transform!" }));
            }
            BOOST_SCOPE_EXIT((&canvas_details)(&original_matrix))
            {
                canvas_details.get().SetTransform(&original_matrix);
            }
            BOOST_SCOPE_EXIT_END;

            assert(dynamic_cast<const gdiplus_background_details_type*>(p_solid_brush.get()));
            const auto draw_string_status = canvas_details.get().DrawString(
                encoded_text.c_str(),
                static_cast<::INT>(encoded_text.length()),
                p_gdiplus_font.get(),
                layout,
                Gdiplus::StringFormat::GenericTypographic(),
                static_cast<const gdiplus_background_details_type&>(*p_solid_brush).get());
            if (draw_string_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ draw_string_status, gdiplus_category() },
                                                          "Can't draw text!" }));
            }
        }

        void draw_vertical_text_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::color& color) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error{ "Not implemented." });
        }

        void paint_picture_impl(
            canvas_details_type&                  canvas,
            const gui::drawing::picture&          picture,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const
        {
            assert(dynamic_cast<gdiplus_picture_details_type*>(&const_cast<gui::drawing::picture&>(picture).details()));
            auto& picture_details =
                static_cast<gdiplus_picture_details_type&>(const_cast<gui::drawing::picture&>(picture).details());

            ::WICPixelFormatGUID pixel_format_guid{};
            const auto           get_pixel_format_hr = picture_details.p_details->GetPixelFormat(&pixel_format_guid);
            if (FAILED(get_pixel_format_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ get_pixel_format_hr, wic_category() },
                                                          "Can't get pixel format." }));
            }

            ::UINT     width = 0;
            ::UINT     height = 0;
            const auto get_size_hr = picture_details.p_details->GetSize(&width, &height);
            if (FAILED(get_size_hr))
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ get_size_hr, wic_category() }, "Can't get size of picture." }));
            }
            const ::UINT        stride = width * sizeof(Gdiplus::ARGB);
            const ::UINT        buffer_size = stride * height;
            std::vector<::BYTE> buffer(buffer_size, 0);

            const ::WICRect rectangle{ 0, 0, static_cast<::INT>(width), static_cast<::INT>(height) };
            const auto      copy_pixels_hr =
                picture_details.p_details->CopyPixels(&rectangle, stride, buffer_size, buffer.data());
            if (FAILED(copy_pixels_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ copy_pixels_hr, wic_category() },
                                                          "Can't copy pixels of picture." }));
            }

            Gdiplus::Bitmap bitmap{ static_cast<::INT>(width),
                                    static_cast<::INT>(height),
                                    static_cast<::INT>(stride),
                                    PixelFormat32bppRGB,
                                    buffer.data() };
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            const auto status = static_cast<gdiplus_canvas_details_type&>(canvas).get().DrawImage(
                &bitmap,
                static_cast<::INT>(position.left().to_pixels()),
                static_cast<::INT>(position.top().to_pixels()),
                static_cast<::INT>(dimension.width().to_pixels()),
                static_cast<::INT>(dimension.height().to_pixels()));
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't paint picture!" }));
            }
        }

        void paint_icon_impl(
            canvas_details_type&                 canvas,
            const gui::icon&                     icon,
            const gui::type_list::position_type& position) const
        {
            assert(dynamic_cast<gdiplus_canvas_details_type*>(&canvas));
            const ::BOOL result = ::DrawIconEx(
                static_cast<gdiplus_canvas_details_type&>(canvas).get().GetHDC(),
                static_cast<int>(position.left().to_pixels()),
                static_cast<int>(position.top().to_pixels()),
                static_cast<const icon::icon_details_impl_type&>(icon.details()).big_icon_handle.get(),
                static_cast<int>(icon.dimension().width().to_pixels()),
                static_cast<int>(icon.dimension().width().to_pixels()),
                0,
                nullptr,
                DI_NORMAL);
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ Gdiplus::Win32Error, gdiplus_category() },
                                                          "Can't paint icon!" }));
            }
        }


    private:
        // types

        class gdiplus_background_details_type : public background_details_type
        {
        public:
            gdiplus_background_details_type() : m_p_brush{} {}

            explicit gdiplus_background_details_type(std::unique_ptr<Gdiplus::Brush> p_brush)
            : m_p_brush{ std::move(p_brush) }
            {}

            virtual ~gdiplus_background_details_type() = default;

            const Gdiplus::Brush* get() const
            {
                return m_p_brush.get();
            }

        private:
            const std::unique_ptr<Gdiplus::Brush> m_p_brush;
        };

        struct gdiplus_picture_details_type : public picture_details_type
        {
            picture::details_ptr_type p_details;

            gdiplus_picture_details_type(const gui::type_list::dimension_type& dimension)
            : p_details{ picture::instance().create(dimension) }
            {}

            gdiplus_picture_details_type(const tetengo2::stdalt::filesystem::path& path)
            : p_details{ picture::instance().read(path) }
            {}

            virtual ~gdiplus_picture_details_type() = default;
        };

        class gdiplus_canvas_details_type : public canvas_details_type
        {
        public:
            gdiplus_canvas_details_type(const base::widget::widget_details_type& widget_details)
            : m_p_widget_graphics{ create_canvas_impl(widget_details) }, m_p_memory_image{}, m_p_memory_graphics{}
            {}

            gdiplus_canvas_details_type(const std::intptr_t handle)
            : m_p_widget_graphics{ create_canvas_impl(handle) }, m_p_memory_image{}, m_p_memory_graphics{}
            {}

            virtual ~gdiplus_canvas_details_type() = default;

            Gdiplus::Graphics& get() const
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

                m_p_memory_image = std::make_unique<Gdiplus::Bitmap>(width, height, m_p_widget_graphics.get());
                m_p_memory_graphics = std::make_unique<Gdiplus::Graphics>(m_p_memory_image.get());
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
                    BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ status, gdiplus_category() },
                                                              "Can't paint the memory image to the widget surface." }));
                }

                m_p_memory_graphics.reset();
                m_p_memory_image.reset();
            }

        private:
            static std::unique_ptr<Gdiplus::Graphics>
            create_canvas_impl(const base::widget::widget_details_type& widget_details)
            {
                auto p_canvas = std::make_unique<Gdiplus::Graphics>(reinterpret_cast<::HWND>(
                    static_cast<const windows::widget::windows_widget_details_type&>(widget_details).handle));

                initialize_canvas(*p_canvas);

                return std::move(p_canvas);
            }

            static std::unique_ptr<Gdiplus::Graphics> create_canvas_impl(const std::intptr_t handle)
            {
                auto p_canvas = std::make_unique<Gdiplus::Graphics>(reinterpret_cast<::HDC>(handle));

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

        using native_drawing_encoder_type =
            text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::wstring>>;


        // static functions

        static std::vector<Gdiplus::PointF>
        to_gdiplus_points(const std::vector<gui::type_list::position_type>& positions)
        {
            std::vector<Gdiplus::PointF> points{};
            points.reserve(positions.size());

            std::transform(
                positions.begin(),
                positions.end(),
                std::back_inserter(points),
                [](const gui::type_list::position_type& position) {
                    return Gdiplus::PointF(
                        static_cast<Gdiplus::REAL>(position.left().to_pixels()),
                        static_cast<Gdiplus::REAL>(position.top().to_pixels()));
                });

            return points;
        }

        static std::unique_ptr<Gdiplus::Font> create_gdiplus_font(
            const gui::drawing::font&      font,
            const Gdiplus::FontCollection& font_collection,
            const std::size_t              fallback_level = 0)
        {
            if (fallback_level > 2)
            {
                BOOST_THROW_EXCEPTION((std::system_error{
                    std::error_code{ Gdiplus::FontFamilyNotFound, gdiplus_category() }, "Font is not available." }));
            }

            const auto& font_family = fallback_level < 1 ? font.family() : gui::drawing::font::dialog_font().family();
            const Gdiplus::FontFamily gdiplus_font_family{ native_drawing_encoder().encode(font_family).c_str(),
                                                           &font_collection };
            if (!gdiplus_font_family.IsAvailable())
            {
                return create_gdiplus_font(font, font_collection, fallback_level + 1);
            }

            const auto font_size = fallback_level < 2 ?
                                       static_cast<Gdiplus::REAL>(font.size()) :
                                       static_cast<Gdiplus::REAL>(gui::drawing::font::dialog_font().size());
            const auto font_style =
                fallback_level < 2 ? get_font_style(font) : get_font_style(gui::drawing::font::dialog_font());
            auto p_gdiplus_font =
                std::make_unique<Gdiplus::Font>(&gdiplus_font_family, font_size, font_style, Gdiplus::UnitPixel);
            if (!p_gdiplus_font->IsAvailable())
                return create_gdiplus_font(font, font_collection, fallback_level + 1);

            return std::move(p_gdiplus_font);
        }

        static ::INT get_font_style(const gui::drawing::font& font)
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

        static const native_drawing_encoder_type& native_drawing_encoder()
        {
            static const native_drawing_encoder_type singleton;
            return singleton;
        }

        static Gdiplus::REAL radian_to_degree(const double radian)
        {
            return static_cast<Gdiplus::REAL>(radian * 180.0 / boost::math::constants::pi<double>());
        }
    };


    const drawing& drawing::instance()
    {
        return impl::instance();
    }

    drawing::~drawing() = default;

    drawing::drawing() : m_p_impl{ std::make_unique<impl>() } {}

    std::unique_ptr<drawing::canvas_details_type>
    drawing::create_canvas_impl(const base::widget::widget_details_type& widget_details) const
    {
        return m_p_impl->create_canvas_impl(widget_details);
    }

    std::unique_ptr<drawing::canvas_details_type> drawing::create_canvas_impl(const std::intptr_t canvas_handle) const
    {
        return m_p_impl->create_canvas_impl(canvas_handle);
    }

    void
    drawing::begin_transaction_impl(canvas_details_type& canvas, const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->begin_transaction_impl(canvas, dimension);
    }

    void drawing::end_transaction_impl(canvas_details_type& canvas) const
    {
        m_p_impl->end_transaction_impl(canvas);
    }

    std::unique_ptr<drawing::background_details_type>
    drawing::create_solid_background_impl(const gui::drawing::color& color) const
    {
        return m_p_impl->create_solid_background_impl(color);
    }

    std::unique_ptr<drawing::background_details_type> drawing::create_transparent_background_impl() const
    {
        return m_p_impl->create_transparent_background_impl();
    }

    std::unique_ptr<drawing::picture_details_type>
    drawing::create_picture_impl(const gui::type_list::dimension_type& dimension) const
    {
        return m_p_impl->create_picture_impl(dimension);
    }

    std::unique_ptr<drawing::picture_details_type>
    drawing::read_picture_impl(const tetengo2::stdalt::filesystem::path& path) const
    {
        return m_p_impl->read_picture_impl(path);
    }

    gui::type_list::dimension_type drawing::picture_dimension_impl(const picture_details_type& picture) const
    {
        return m_p_impl->picture_dimension_impl(picture);
    }

    void drawing::draw_line_impl(
        canvas_details_type&                       canvas,
        const gui::type_list::position_type&       from,
        const gui::type_list::position_type&       to,
        const gui::type_list::dimension_unit_type& width,
        const int                                  style,
        const gui::drawing::color&                 color) const
    {
        m_p_impl->draw_line_impl(canvas, from, to, width, style, color);
    }

    void drawing::draw_focus_indication_impl(
        canvas_details_type&                  canvas,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->draw_focus_indication_impl(canvas, position, dimension);
    }

    void drawing::draw_rectangle_impl(
        canvas_details_type&                       canvas,
        const gui::type_list::position_type&       position,
        const gui::type_list::dimension_type&      dimension,
        const gui::type_list::dimension_unit_type& width,
        const int                                  style,
        const gui::drawing::color&                 color) const
    {
        m_p_impl->draw_rectangle_impl(canvas, position, dimension, width, style, color);
    }

    void drawing::fill_rectangle_impl(
        canvas_details_type&                  canvas,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension,
        const gui::drawing::background&       background) const
    {
        m_p_impl->fill_rectangle_impl(canvas, position, dimension, background);
    }

    void drawing::draw_polygon_impl(
        canvas_details_type&                              canvas,
        const std::vector<gui::type_list::position_type>& positions,
        const gui::type_list::dimension_unit_type&        width,
        const int                                         style,
        const gui::drawing::color&                        color) const
    {
        m_p_impl->draw_polygon_impl(canvas, positions, width, style, color);
    }

    void drawing::fill_polygon_impl(
        canvas_details_type&                              canvas,
        const std::vector<gui::type_list::position_type>& positions,
        const gui::drawing::background&                   background) const
    {
        m_p_impl->fill_polygon_impl(canvas, positions, background);
    }

    gui::drawing::font drawing::make_dialog_font_impl() const
    {
        return m_p_impl->make_dialog_font_impl();
    }

    gui::type_list::dimension_type drawing::calc_text_dimension_impl(
        const canvas_details_type&                 canvas,
        const gui::drawing::font&                  font,
        const type_list::string_type&              text,
        const gui::type_list::dimension_unit_type& max_width) const
    {
        return m_p_impl->calc_text_dimension_impl(canvas, font, text, max_width);
    }

    gui::type_list::dimension_type drawing::calc_vertical_text_dimension_impl(
        const canvas_details_type&    canvas,
        const gui::drawing::font&     font,
        const type_list::string_type& text) const
    {
        return m_p_impl->calc_vertical_text_dimension_impl(canvas, font, text);
    }

    void drawing::draw_text_impl(
        canvas_details_type&                       canvas,
        const gui::drawing::font&                  font,
        const type_list::string_type&              text,
        const gui::type_list::position_type&       position,
        const gui::type_list::dimension_unit_type& max_width,
        const gui::drawing::color&                 color,
        const double                               angle) const
    {
        m_p_impl->draw_text_impl(canvas, font, text, position, max_width, color, angle);
    }

    void drawing::draw_vertical_text_impl(
        canvas_details_type&                 canvas,
        const gui::drawing::font&            font,
        const type_list::string_type&        text,
        const gui::type_list::position_type& position,
        const gui::drawing::color&           color) const
    {
        m_p_impl->draw_vertical_text_impl(canvas, font, text, position, color);
    }

    void drawing::paint_picture_impl(
        canvas_details_type&                  canvas,
        const gui::drawing::picture&          picture,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->paint_picture_impl(canvas, picture, position, dimension);
    }

    void drawing::paint_icon_impl(
        canvas_details_type&                 canvas,
        const gui::icon&                     icon,
        const gui::type_list::position_type& position) const
    {
        m_p_impl->paint_icon_impl(canvas, icon, position);
    }
}
