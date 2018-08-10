/*! \file
    \brief The definition of tetengo2::detail::windows::direct2d::drawing.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/


#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
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
#include <Unknwn.h>
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <dxgiformat.h>
#include <wincodec.h>

#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/windows/com_ptr.h>
#include <tetengo2/detail/windows/direct2d/drawing.h>
#include <tetengo2/detail/windows/direct2d/error_category.h>
#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/font.h>
#include <tetengo2/detail/windows/picture.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/character_iterator.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/text/encoding/utf8.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui {
    class icon;

    namespace drawing {
        class background;
        class picture;
    }
}}


namespace tetengo2::detail::windows::direct2d {
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
            const auto window_handle = reinterpret_cast<::HWND>(
                static_cast<const windows::widget::windows_widget_details_type&>(widget_details).handle);

            auto props = D2D1::RenderTargetProperties();
            props.pixelFormat = D2D1::PixelFormat(::DXGI_FORMAT_B8G8R8A8_UNORM, ::D2D1_ALPHA_MODE_PREMULTIPLIED);
            props.usage = ::D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE;

            ::D2D1_HWND_RENDER_TARGET_PROPERTIES hwnd_props{};
            {
                ::RECT     rect{};
                const auto result = ::GetClientRect(window_handle, &rect);
                if (result == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                            "Can't get client rectangle." }));
                }
                hwnd_props = D2D1::HwndRenderTargetProperties(
                    window_handle, D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top));
            }

            ::ID2D1HwndRenderTarget* rp_render_target = nullptr;
            const auto hr = direct2d_factory().CreateHwndRenderTarget(props, hwnd_props, &rp_render_target);
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ hr, direct2d_category() },
                                                          "Can't create HWND render target." }));
            }
            auto p_canvas_details = std::make_unique<direct2d_canvas_details_type>(rp_render_target);

            p_canvas_details->render_target().BeginDraw();
            p_canvas_details->render_target().Clear(colorref_to_color_f(::GetSysColor(COLOR_3DFACE)));

            return canvas_details_ptr_type{ std::move(p_canvas_details) };
        }

        std::unique_ptr<canvas_details_type>
        create_canvas_impl(TETENGO2_STDALT_MAYBE_UNUSED std::intptr_t canvas_handle) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error{ "Not implemented." });
        }

        void begin_transaction_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension) const
        {}

        void end_transaction_impl(TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas) const {}

        std::unique_ptr<background_details_type> create_solid_background_impl(const gui::drawing::color& color) const
        {
            return std::make_unique<direct2d_solid_background_details_type>(
                color.red(), color.green(), color.blue(), color.alpha());
        }

        std::unique_ptr<background_details_type> create_transparent_background_impl() const
        {
            return std::make_unique<direct2d_transparent_background_details_type>();
        }

        std::unique_ptr<picture_details_type> create_picture_impl(const gui::type_list::dimension_type& dimension) const
        {
            return std::make_unique<direct2d_picture_details_type>(dimension);
        }

        std::unique_ptr<picture_details_type> read_picture_impl(const tetengo2::stdalt::filesystem::path& path) const
        {
            return std::make_unique<direct2d_picture_details_type>(path);
        }

        gui::type_list::dimension_type picture_dimension_impl(const picture_details_type& picture) const
        {
            return picture::instance().dimension(*static_cast<const direct2d_picture_details_type&>(picture).p_details);
        }

        void draw_line_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       from,
            const gui::type_list::position_type&       to,
            const gui::type_list::dimension_unit_type& width,
            const int                                  style,
            const gui::drawing::color&                 color) const
        {
            const auto p_background_details = create_solid_background_impl(color);
            const auto p_brush = create_brush(canvas, *p_background_details);
            const auto p_stroke_style = create_stroke_style(style);
            static_cast<direct2d_canvas_details_type&>(canvas).render_target().DrawLine(
                position_to_point_2f(from),
                position_to_point_2f(to),
                p_brush.get(),
                size_to_float(width),
                p_stroke_style.get());
        }

        void draw_focus_indication_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error{ "Not implemented." });
        }

        void draw_rectangle_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_type&      dimension,
            const gui::type_list::dimension_unit_type& width,
            const int                                  style,
            const gui::drawing::color&                 color) const
        {
            const auto p_background_details = create_solid_background_impl(color);
            const auto p_brush = create_brush(canvas, *p_background_details);
            const auto p_stroke_style = create_stroke_style(style);
            static_cast<direct2d_canvas_details_type&>(canvas).render_target().DrawRectangle(
                position_and_dimension_to_rect_f(position, dimension),
                p_brush.get(),
                size_to_float(width),
                p_stroke_style.get());
        }

        void fill_rectangle_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const gui::drawing::background&       background) const
        {
            const auto& background_details = background.details();
            if (static_cast<const direct2d_background_details_type&>(background_details).is_transparent())
                return;

            const auto p_brush = create_brush(canvas, background_details);

            static_cast<direct2d_canvas_details_type&>(canvas).render_target().FillRectangle(
                position_and_dimension_to_rect_f(position, dimension), p_brush.get());
        }

        void draw_polygon_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const std::vector<gui::type_list::position_type>& positions,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED const int                                  style,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::color& color) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error{ "Not implemented." });
        }

        void fill_polygon_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const std::vector<gui::type_list::position_type>& positions,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::background& background) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error{ "Not implemented." });
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
            TETENGO2_STDALT_MAYBE_UNUSED const canvas_details_type& canvas,
            const gui::drawing::font&                               font,
            const type_list::string_type&                           text,
            const gui::type_list::dimension_unit_type&              max_width) const
        {
            const auto p_layout = create_text_layout(text, font, max_width);

            ::DWRITE_TEXT_METRICS metrics{};
            const auto            get_metrics_hr = p_layout->GetMetrics(&metrics);
            if (FAILED(get_metrics_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ get_metrics_hr, win32_category() },
                                                          "Can't get text metrics." }));
            }

            return { gui::type_list::dimension_unit_type::from_pixels(to_ddp_x(metrics.width)),
                     gui::type_list::dimension_unit_type::from_pixels(to_ddp_y(metrics.height)) };
        }

        gui::type_list::dimension_type calc_vertical_text_dimension_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const canvas_details_type& canvas,
            const gui::drawing::font&                               font,
            const type_list::string_type&                           text) const
        {
            const auto chunks = split_to_vertical_text_chunks(text);

            using dimension_unit_type = gui::type_list::dimension_unit_type;
            dimension_unit_type max_width{};
            dimension_unit_type total_height{};
            for (const auto& chunk : chunks)
            {
                const auto  chunk_dimension = calc_text_dimension_impl(canvas, font, chunk, dimension_unit_type{});
                const auto& chunk_width = chunk_dimension.width();
                const auto& chunk_height = chunk_dimension.height();
                if (character_rotation(chunk) % 2 == 0)
                {
                    if (chunk_width > max_width)
                        max_width = chunk_width;
                    total_height += chunk_height;
                }
                else
                {
                    if (chunk_height > max_width)
                        max_width = chunk_height;
                    total_height += chunk_width;
                }
            }

            return gui::type_list::dimension_type{ max_width, total_height };
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
            const auto p_layout = create_text_layout(text, font, max_width);

            const auto p_background_details = create_solid_background_impl(color);
            const auto p_brush = create_brush(canvas, *p_background_details);

            auto& render_target = static_cast<direct2d_canvas_details_type&>(canvas).render_target();
            auto  original_transform = D2D1::Matrix3x2F{};
            render_target.GetTransform(&original_transform);
            BOOST_SCOPE_EXIT((&render_target)(&original_transform))
            {
                render_target.SetTransform(original_transform);
            }
            BOOST_SCOPE_EXIT_END;
            auto rotating_transform =
                D2D1::Matrix3x2F::Rotation(radian_to_degree(angle), position_to_point_2f(position));
            render_target.SetTransform(rotating_transform);

            render_target.DrawTextLayout(position_to_point_2f(position), p_layout.get(), p_brush.get());
        }

        void draw_vertical_text_impl(
            canvas_details_type&                 canvas,
            const gui::drawing::font&            font,
            const type_list::string_type&        text,
            const gui::type_list::position_type& position,
            const gui::drawing::color&           color) const
        {
            const auto  dimension = calc_vertical_text_dimension_impl(canvas, font, text);
            const auto& max_width = dimension.width();

            const auto chunks = split_to_vertical_text_chunks(text);

            using position_unit_type = gui::type_list::dimension_unit_type;
            using dimension_unit_type = gui::type_list::dimension_unit_type;
            const auto& base_left = position.left();
            const auto& base_top = position.top();
            auto        next_chunk_top = base_top;
            for (const auto& chunk : chunks)
            {
                const auto  chunk_dimension = calc_text_dimension_impl(canvas, font, chunk, dimension_unit_type{});
                const auto& chunk_width = chunk_dimension.width();
                const auto& chunk_height = chunk_dimension.height();

                const int    rotation = character_rotation(chunk);
                const double angle = rotation * boost::math::constants::pi<double>() / 2.0;

                const auto chunk_left = rotation % 2 == 0 ?
                                            base_left + position_unit_type::from(max_width - chunk_width) / 2 :
                                            base_left + position_unit_type::from(max_width - chunk_height) / 2;

                gui::type_list::position_type chunk_position{ chunk_left, next_chunk_top };
                if (rotation == 1)
                {
                    chunk_position = gui::type_list::position_type{ chunk_left + position_unit_type::from(chunk_height),
                                                                    next_chunk_top };
                }
                else if (rotation == 2)
                {
                    chunk_position =
                        gui::type_list::position_type{ chunk_left + position_unit_type::from(chunk_width),
                                                       next_chunk_top + position_unit_type::from(chunk_height) };
                }
                else
                {
                    assert(rotation == 0);
                }


                draw_text_impl(canvas, font, chunk, chunk_position, dimension_unit_type{}, color, angle);

                next_chunk_top +=
                    rotation % 2 == 0 ? position_unit_type::from(chunk_height) : position_unit_type::from(chunk_width);
            }
        }

        void paint_picture_impl(
            canvas_details_type&                  canvas,
            const gui::drawing::picture&          picture,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const
        {
            auto& picture_details =
                static_cast<direct2d_picture_details_type&>(const_cast<gui::drawing::picture&>(picture).details());

            auto&          render_target = static_cast<direct2d_canvas_details_type&>(canvas).render_target();
            ::ID2D1Bitmap* rp_bitmap = nullptr;
            const auto     create_bitmap_hr =
                render_target.CreateBitmapFromWicBitmap(picture_details.p_details.get(), &rp_bitmap);
            if (FAILED(create_bitmap_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ create_bitmap_hr, direct2d_category() },
                                                          "Can't create bitmap." }));
            }
            const unique_com_ptr<::ID2D1Bitmap> p_bitmap{ rp_bitmap };

            render_target.DrawBitmap(p_bitmap.get(), position_and_dimension_to_rect_f(position, dimension));
        }

        void paint_icon_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::icon& icon,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position) const
        {
            assert(false);
            BOOST_THROW_EXCEPTION(std::logic_error{ "Not implemented." });
        }


    private:
        // types

        struct direct2d_background_details_type : public background_details_type
        {
            virtual ~direct2d_background_details_type() = default;

            virtual bool is_transparent() const = 0;
        };

        class direct2d_solid_background_details_type : public direct2d_background_details_type
        {
        public:
            direct2d_solid_background_details_type(
                const unsigned char red,
                const unsigned char green,
                const unsigned char blue,
                const unsigned char alpha)
            : m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha }
            {}

            virtual ~direct2d_solid_background_details_type() = default;

            virtual bool is_transparent() const override
            {
                return false;
            }

            unsigned char red() const
            {
                return m_red;
            }

            unsigned char green() const
            {
                return m_green;
            }

            unsigned char blue() const
            {
                return m_blue;
            }

            unsigned char alpha() const
            {
                return m_alpha;
            }


        private:
            const unsigned char m_red;

            const unsigned char m_green;

            const unsigned char m_blue;

            const unsigned char m_alpha;
        };

        class direct2d_transparent_background_details_type : public direct2d_background_details_type
        {
        public:
            virtual ~direct2d_transparent_background_details_type() = default;

            virtual bool is_transparent() const override
            {
                return true;
            }
        };

        struct direct2d_picture_details_type : public picture_details_type
        {
            picture::details_ptr_type p_details;

            direct2d_picture_details_type(const gui::type_list::dimension_type& dimension)
            : p_details{ picture::instance().create(dimension) }
            {}

            direct2d_picture_details_type(const tetengo2::stdalt::filesystem::path& path)
            : p_details{ picture::instance().read(path) }
            {}

            virtual ~direct2d_picture_details_type() = default;
        };

        class direct2d_canvas_details_type : public canvas_details_type
        {
        public:
            direct2d_canvas_details_type(::ID2D1HwndRenderTarget* const p_render_target)
            : m_p_render_target{ p_render_target }
            {}

            virtual ~direct2d_canvas_details_type() = default;

            const ::ID2D1RenderTarget& render_target() const
            {
                return *m_p_render_target;
            }

            ::ID2D1RenderTarget& render_target()
            {
                return *m_p_render_target;
            }


        private:
            struct release_render_target
            {
                void operator()(::ID2D1RenderTarget* p_render_target) const
                {
                    if (p_render_target)
                    {
                        const auto hr = p_render_target->EndDraw();
                        if (hr == D2DERR_RECREATE_TARGET)
                        {
                            assert(false);
                        }
                        p_render_target->Release();
                        p_render_target = nullptr;
                    }
                }
            };

            const std::unique_ptr<::ID2D1RenderTarget, release_render_target> m_p_render_target;
        };

        using direct2d_factory_ptr_type = unique_com_ptr<::ID2D1Factory>;

        using direct_write_factory_ptr_type = unique_com_ptr<::IDWriteFactory>;

        using native_drawing_encoder_type =
            text::encoder<type_list::internal_encoding_type, text::encoding::locale<std::wstring>>;


        // static functions

        static ::ID2D1Factory& direct2d_factory()
        {
            static const direct2d_factory_ptr_type p_factory{ create_direct2d_factory() };
            return *p_factory;
        }

        static direct2d_factory_ptr_type create_direct2d_factory()
        {
            ::ID2D1Factory* rp_factory = nullptr;
            const auto      hr = ::D2D1CreateFactory(::D2D1_FACTORY_TYPE_SINGLE_THREADED, &rp_factory);
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ hr, direct2d_category() }, "Can't create Direct2D factory." }));
            }

            return direct2d_factory_ptr_type{ rp_factory };
        }

        static ::IDWriteFactory& direct_write_factory()
        {
            static const direct_write_factory_ptr_type p_factory{ create_direct_write_factory() };
            return *p_factory;
        }

        static direct_write_factory_ptr_type create_direct_write_factory()
        {
            ::IDWriteFactory* rp_factory = nullptr;
            const auto        hr = ::DWriteCreateFactory(
                ::DWRITE_FACTORY_TYPE_SHARED, __uuidof(::IDWriteFactory), reinterpret_cast<::IUnknown**>(&rp_factory));
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ hr, win32_category() },
                                                          "Can't create Direct Write factory." }));
            }

            return direct_write_factory_ptr_type{ rp_factory };
        }

        static const std::pair<::FLOAT, ::FLOAT>& dpi()
        {
            static const auto singleton = calculate_dpi();
            return singleton;
        }

        static std::pair<::FLOAT, ::FLOAT> calculate_dpi()
        {
            std::pair<::FLOAT, ::FLOAT> dpi{};

            direct2d_factory().GetDesktopDpi(&dpi.first, &dpi.second);
            assert(dpi.first != 0 && dpi.second != 0);

            return dpi;
        }

        static ::FLOAT to_ddp_x(const ::FLOAT dip)
        {
            return dip * dpi().first / 96.0f;
        }

        static ::FLOAT to_ddp_y(const ::FLOAT dip)
        {
            return dip * dpi().second / 96.0f;
        }

        static ::FLOAT to_dip_x(const ::FLOAT ddp)
        {
            return ddp * 96.0f / dpi().first;
        }

        static ::FLOAT to_dip_y(const ::FLOAT ddp)
        {
            return ddp * 96.0f / dpi().second;
        }

        static ::FLOAT size_to_float(const gui::type_list::dimension_unit_type& size)
        {
            return to_dip_y(static_cast<::FLOAT>(size.to_pixels()));
        }

        static ::D2D1_POINT_2F position_to_point_2f(const gui::type_list::position_type& position)
        {
            const auto left = to_dip_x(static_cast<::FLOAT>(position.left().to_pixels()));
            const auto top = to_dip_y(static_cast<::FLOAT>(position.top().to_pixels()));
            return ::D2D1_POINT_2F{ left - 0.5f, top - 0.5f };
        }

        static ::D2D1_RECT_F position_and_dimension_to_rect_f(
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension)
        {
            const auto left = to_dip_x(static_cast<::FLOAT>(position.left().to_pixels()));
            const auto top = to_dip_y(static_cast<::FLOAT>(position.top().to_pixels()));
            const auto width = to_dip_x(static_cast<::FLOAT>(dimension.width().to_pixels()));
            const auto height = to_dip_y(static_cast<::FLOAT>(dimension.height().to_pixels()));
            return ::D2D1_RECT_F{ left, top, left + width, top + height };
        }

        static ::D2D1_COLOR_F colorref_to_color_f(const ::COLORREF colorref)
        {
            return rgba_to_color_f(GetRValue(colorref), GetGValue(colorref), GetBValue(colorref), 255);
        }

        static ::D2D1_COLOR_F rgba_to_color_f(
            const unsigned char red,
            const unsigned char green,
            const unsigned char blue,
            const unsigned char alpha)
        {
            return ::D2D1_COLOR_F{ static_cast<::FLOAT>(red / 255.0),
                                   static_cast<::FLOAT>(green / 255.0),
                                   static_cast<::FLOAT>(blue / 255.0),
                                   static_cast<::FLOAT>(alpha / 255.0) };
        }

        static const native_drawing_encoder_type& native_drawing_encoder()
        {
            static const native_drawing_encoder_type singleton;
            return singleton;
        }

        using utf8_encoder_type = text::encoder<type_list::internal_encoding_type, text::encoding::utf8>;

        static const utf8_encoder_type& utf8_encoder()
        {
            static const utf8_encoder_type singleton;
            return singleton;
        }

        static unique_com_ptr<::ID2D1Brush>
        create_brush(canvas_details_type& canvas, const background_details_type& background_details)
        {
            const auto* const p_solid = static_cast<const direct2d_solid_background_details_type*>(&background_details);
            if (!p_solid)
            {
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid background details type." }));
            }
            ::ID2D1SolidColorBrush* rp_brush = nullptr;
            const auto hr = static_cast<direct2d_canvas_details_type&>(canvas).render_target().CreateSolidColorBrush(
                rgba_to_color_f(p_solid->red(), p_solid->green(), p_solid->blue(), p_solid->alpha()),
                D2D1::BrushProperties(),
                &rp_brush);
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ hr, direct2d_category() },
                                                          "Can't create solid color brush." }));
            }
            return unique_com_ptr<::ID2D1Brush>{ rp_brush };
        }

        static unique_com_ptr<::ID2D1StrokeStyle> create_stroke_style(const int style)
        {
            ::ID2D1StrokeStyle* rp_stroke_style = nullptr;
            const auto          hr = direct2d_factory().CreateStrokeStyle(
                D2D1::StrokeStyleProperties(
                    ::D2D1_CAP_STYLE_ROUND,
                    ::D2D1_CAP_STYLE_ROUND,
                    ::D2D1_CAP_STYLE_ROUND,
                    ::D2D1_LINE_JOIN_ROUND,
                    1.0f,
                    to_stroke_dash_style(style)),
                nullptr,
                0,
                &rp_stroke_style);
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ hr, direct2d_category() }, "Can't create stroke style." }));
            }
            return unique_com_ptr<::ID2D1StrokeStyle>{ rp_stroke_style };
        }

        static ::D2D1_DASH_STYLE to_stroke_dash_style(const int style)
        {
            switch (style)
            {
            case 0:
                return ::D2D1_DASH_STYLE_SOLID;
            case 1:
                return ::D2D1_DASH_STYLE_DASH;
            case 2:
                return ::D2D1_DASH_STYLE_DOT;
            case 3:
                return ::D2D1_DASH_STYLE_DASH_DOT;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Unknown stroke dash style." }));
            }
        }

        static unique_com_ptr<::IDWriteTextLayout> create_text_layout(
            const type_list::string_type&              text,
            const gui::drawing::font&                  font,
            const gui::type_list::dimension_unit_type& max_width)
        {
            ::IDWriteTextFormat* rp_format = nullptr;
            const auto           create_format_hr = direct_write_factory().CreateTextFormat(
                native_drawing_encoder().encode(font.family()).c_str(),
                nullptr,
                font.bold() ? ::DWRITE_FONT_WEIGHT_BOLD : ::DWRITE_FONT_WEIGHT_NORMAL,
                font.italic() ? ::DWRITE_FONT_STYLE_ITALIC : ::DWRITE_FONT_STYLE_NORMAL,
                ::DWRITE_FONT_STRETCH_NORMAL,
                static_cast<::FLOAT>(font.size()),
                L"",
                &rp_format);
            if (FAILED(create_format_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ create_format_hr, win32_category() },
                                                          "Can't create text format." }));
            }
            const typename unique_com_ptr<::IDWriteTextFormat> p_format{ rp_format };

            const auto    encoded_text = native_drawing_encoder().encode(text);
            const ::FLOAT max_width_in_dip = max_width == gui::type_list::dimension_unit_type{} ?
                                                 std::numeric_limits<::FLOAT>::max() :
                                                 to_dip_x(static_cast<::FLOAT>(max_width.to_pixels()));
            ::IDWriteTextLayout* rp_layout = nullptr;
            const auto           create_layout_hr = direct_write_factory().CreateTextLayout(
                encoded_text.c_str(),
                static_cast<::UINT32>(encoded_text.length()),
                p_format.get(),
                max_width_in_dip,
                std::numeric_limits<::FLOAT>::max(),
                &rp_layout);
            if (FAILED(create_layout_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ create_layout_hr, win32_category() },
                                                          "Can't create text layout." }));
            }
            typename unique_com_ptr<::IDWriteTextLayout> p_layout{ rp_layout };

            const ::DWRITE_TEXT_RANGE range{ 0, static_cast<::UINT32>(encoded_text.length()) };
            p_layout->SetUnderline(font.underline() ? TRUE : FALSE, range);
            p_layout->SetStrikethrough(font.strikeout() ? TRUE : FALSE, range);

            return std::move(p_layout);
        }

        static std::vector<type_list::string_type> split_to_vertical_text_chunks(const type_list::string_type& text)
        {
            using character_iterator_type = text::character_iterator<type_list::string_type>;

            std::vector<type_list::string_type> chunks{};
            type_list::string_type              tatechuyoko{};
            const character_iterator_type       end{};
            for (auto i = character_iterator_type{ text,
                                                   text::encoding::make_polymorphic<type_list::internal_encoding_type>(
                                                       native_drawing_encoder().internal_encoding()) };
                 i != end;
                 ++i)
            {
                const auto& char_as_string = *i;
                if (is_tatechuyoko_character(char_as_string))
                {
                    tatechuyoko.append(char_as_string);
                    continue;
                }
                if (!tatechuyoko.empty())
                {
                    chunks.push_back(tatechuyoko);
                    tatechuyoko.clear();
                }

                if (!chunks.empty() && is_dakuten_character(char_as_string))
                    chunks.back().append(char_as_string);
                else
                    chunks.push_back(char_as_string);
            }
            if (!tatechuyoko.empty())
                chunks.push_back(tatechuyoko);

            return std::move(chunks);
        }

        static bool is_tatechuyoko_character(const type_list::string_type& char_as_string)
        {
            const auto char_in_utf8 = utf8_encoder().encode(char_as_string);

            static const std::vector<std::string> digits{
                std::string{ to_char(0x30) }, // 0
                std::string{ to_char(0x31) }, // 1
                std::string{ to_char(0x32) }, // 2
                std::string{ to_char(0x33) }, // 3
                std::string{ to_char(0x34) }, // 4
                std::string{ to_char(0x35) }, // 5
                std::string{ to_char(0x36) }, // 6
                std::string{ to_char(0x37) }, // 7
                std::string{ to_char(0x38) }, // 8
                std::string{ to_char(0x39) }, // 9
            };
            if (std::find(digits.begin(), digits.end(), char_in_utf8) != digits.end())
                return true;

            return false;
        }

        static bool is_dakuten_character(const type_list::string_type& char_as_string)
        {
            const auto char_in_utf8 = utf8_encoder().encode(char_as_string);

            static const std::vector<std::string> dakutens{
                std::string{ to_char(0xEF), to_char(0xBE), to_char(0x9E) }, // halfwidth katakana dakuten
                std::string{ to_char(0xEF), to_char(0xBE), to_char(0x9F) }, // halfwidth katakana handakuten
            };
            if (std::find(dakutens.begin(), dakutens.end(), char_in_utf8) != dakutens.end())
                return true;

            return false;
        }

        static int character_rotation(const type_list::string_type& char_as_string)
        {
            const auto char_in_utf8 = utf8_encoder().encode(char_as_string);

            static const std::vector<std::string> r90degs{
                std::string{ to_char(0x29) }, // right parenthesis
                std::string{ to_char(0x2D) }, // hyphen-minus
                std::string{ to_char(0x5B) }, // left square bracket
                std::string{ to_char(0x5D) }, // right square bracket
                std::string{ to_char(0x7B) }, // left curly bracket
                std::string{ to_char(0x7D) }, // left curly bracket
                std::string{ to_char(0x28) }, // left parenthesis
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x88) }, // left angle bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x89) }, // right angle bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x8A) }, // left double angle bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x8B) }, // right double angle bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x8C) }, // left corner bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x8D) }, // right corner bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x8E) }, // left white corner bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x8F) }, // right white corner bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x90) }, // left black lenticular bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x91) }, // right black lenticular bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x94) }, // left tortoise shell bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x95) }, // right tortoise shell bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x96) }, // left white lenticular bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x97) }, // right white lenticular bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x98) }, // left white tortoise shell bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x99) }, // right white tortoise shell bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x9A) }, // left white square bracket
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x9B) }, // right white square bracket
                std::string{ to_char(0xE3), to_char(0x83), to_char(0xBC) }, // choon
                std::string{ to_char(0xEF), to_char(0xBC), to_char(0x88) }, // fullwidth left parenthesis
                std::string{ to_char(0xEF), to_char(0xBC), to_char(0x89) }, // fullwidth right parenthesis
                std::string{ to_char(0xEF), to_char(0xBC), to_char(0x8D) }, // fullwidth hyphen-minus
                std::string{ to_char(0xEF), to_char(0xBC), to_char(0xBB) }, // fullwidth left bracket
                std::string{ to_char(0xEF), to_char(0xBC), to_char(0xBD) }, // fullwidth right bracket
                std::string{ to_char(0xEF), to_char(0xBD), to_char(0x9B) }, // fullwidth left curly bracket
                std::string{ to_char(0xEF), to_char(0xBD), to_char(0x9D) }, // fullwidth right curly bracket
                std::string{ to_char(0xEF), to_char(0xBD), to_char(0x9E) }, // fullwidth tilde
                std::string{ to_char(0xEF), to_char(0xBD), to_char(0xA2) }, // halfwidth left corner bracket
                std::string{ to_char(0xEF), to_char(0xBD), to_char(0xA3) }, // halfwidth right corner bracket
                std::string{ to_char(0xEF), to_char(0xBD), to_char(0xB0) }, // halfwidth choon
            };
            static const std::vector<std::string> r180degs{
                std::string{ to_char(0x2C) }, // comma
                std::string{ to_char(0x2E) }, // full stop
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x81) }, // toten
                std::string{ to_char(0xE3), to_char(0x80), to_char(0x82) }, // kuten
                std::string{ to_char(0xEF), to_char(0xBC), to_char(0x8C) }, // fullwidth comma
                std::string{ to_char(0xEF), to_char(0xBC), to_char(0x8E) }, // fullwidth full stop
                std::string{ to_char(0xEF), to_char(0xBD), to_char(0xA1) }, // halfwidth kuten
                std::string{ to_char(0xEF), to_char(0xBD), to_char(0xA4) }, // halfwidth toten
            };
            if (std::find(r90degs.begin(), r90degs.end(), char_in_utf8) != r90degs.end())
            {
                return 1;
            }
            else if (std::find(r180degs.begin(), r180degs.end(), char_in_utf8) != r180degs.end())
            {
                return 2;
            }
            else
            {
                return 0;
            }
        }

        template <typename C>
        static char to_char(C c)
        {
            return static_cast<char>(c);
        }

        static ::FLOAT radian_to_degree(const double radian)
        {
            return static_cast<::FLOAT>(radian * 180.0 / boost::math::constants::pi<double>());
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
