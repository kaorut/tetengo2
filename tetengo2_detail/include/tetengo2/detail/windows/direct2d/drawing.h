/*! \file
    \brief The definition of tetengo2::detail::windows::direct2d::drawing.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_DIRECT2D_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_DIRECT2D_DRAWING_H

#include <algorithm> // IWYU pragma: keep
#include <cassert>
#include <limits> // IWYU pragma: keep
#include <memory> // IWYU pragma: keep
#include <system_error> // IWYU pragma: keep
#include <utility> // IWYU pragma: keep
#include <vector> // IWYU pragma: keep

#include <boost/core/noncopyable.hpp>
#include <boost/math/constants/constants.hpp> // IWYU pragma: keep
#include <boost/preprocessor.hpp>
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

#include <tetengo2/detail/windows/com_ptr.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/direct2d/error_category.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/font.h>
#include <tetengo2/detail/windows/picture.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text/character_iterator.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/polymorphic.h>
#include <tetengo2/text/encoding/utf8.h> // IWYU pragma: keep


namespace tetengo2::detail::windows::direct2d {
#if !defined(DOCUMENTATION)
    namespace detail {
        // types

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

        class background_details : private boost::noncopyable
        {
        public:
            virtual ~background_details() = default;

            virtual bool is_transparent() const = 0;
        };

        class solid_background_details : public background_details
        {
        public:
            solid_background_details(
                const unsigned char red,
                const unsigned char green,
                const unsigned char blue,
                const unsigned char alpha)
            : m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha }
            {}

            virtual ~solid_background_details() = default;

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

        class transparent_background_details : public background_details
        {
        public:
            virtual ~transparent_background_details() = default;

            virtual bool is_transparent() const override
            {
                return true;
            }
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
        using canvas_details_type = ::ID2D1RenderTarget;

        //! The canvas details pointer type.
        using canvas_details_ptr_type = std::unique_ptr<canvas_details_type, detail::release_render_target>;


        // static functions

        /*!
            \brief Creates a canvas.

            \tparam WidgetDetails A widget details type.

            \param widget_details A widget details.

            \return A unique pointer to a canvas.
        */
        template <typename WidgetDetails>
        static canvas_details_ptr_type create_canvas(const WidgetDetails& widget_details)
        {
            const auto window_handle = widget_details.handle.get();

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
            std::unique_ptr<::ID2D1HwndRenderTarget, detail::release_render_target> p_render_target{ rp_render_target };

            p_render_target->BeginDraw();
            p_render_target->Clear(colorref_to_color_f(::GetSysColor(COLOR_3DFACE)));

            return canvas_details_ptr_type{ std::move(p_render_target) };
        }

        /*!
            \brief Begins a transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \param canvas    A canvas.
            \param dimension A dimension.

            \throw std::logic_error When another transaction has not ended yet.
        */
        static void begin_transaction(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension)
        {}

        /*!
            \brief Ends the transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \param canvas A canvas.

            \throw std::logic_error When no transaction has begun.
        */
        static void end_transaction(TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas) {}

        /*!
            \brief Creates a solid background.


            \param color A color.

            \return A unique pointer to a solid background.
        */
        static background_details_ptr_type create_solid_background(const tetengo2::gui::drawing::color& color)
        {
            return std::make_unique<detail::solid_background_details>(
                color.red(), color.green(), color.blue(), color.alpha());
        }

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        static background_details_ptr_type create_transparent_background()
        {
            return std::make_unique<detail::transparent_background_details>();
        }

        /*!
            \brief Creates a picture.


            \param dimension A dimension.

            \return A unique pointer to a picture.
        */
        static picture_details_ptr_type create_picture(const gui::type_list::dimension_type& dimension)
        {
            return picture::create(dimension);
        }

        /*!
            \brief Reads a picture.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        inline static picture_details_ptr_type read_picture(const tetengo2::stdalt::filesystem::path& path)
        {
            return picture::instance().read(path);
        }

        /*!
            \brief Returns the dimension of a picture.


            \param picture A picture.

            \return The dimension of the picture.
        */
        static gui::type_list::dimension_type picture_dimension(const picture_details_type& picture)
        {
            return picture::instance().dimension(picture);
        }

        /*!
            \brief Draws a line.


            \param canvas A canvas.
            \param from   A beginning position.
            \param to     An ending position.
            \param width  A width.
            \param style  A style.
            \param color  A color.
        */
        static void draw_line(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       from,
            const gui::type_list::position_type&       to,
            const gui::type_list::dimension_unit_type& width,
            const int                                  style,
            const tetengo2::gui::drawing::color&       color)
        {
            const auto p_background_details = create_solid_background(color);
            const auto p_brush = create_brush(canvas, *p_background_details);
            const auto p_stroke_style = create_stroke_style(style);
            canvas.DrawLine(
                position_to_point_2f(from),
                position_to_point_2f(to),
                p_brush.get(),
                size_to_float(width),
                p_stroke_style.get());
        }

        /*!
            \brief Draws a focus indication.


            \param canvas    A canvas.
            \param position  A position of a region.
            \param dimension A dimension of a region.

            \throw std::system_error When the focus indication cannot be drawn.
        */
        static void draw_focus_indication(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension);

        /*!
            \brief Draws a rectangle.


            \param canvas     A canvas.
            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param width      A width.
            \param style      A style.
            \param color      A color.

            \throw std::system_error When the rectangle cannot be filled.
        */
        static void draw_rectangle(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_type&      dimension,
            const gui::type_list::dimension_unit_type& width,
            const int                                  style,
            const tetengo2::gui::drawing::color&       color)
        {
            const auto p_background_details = create_solid_background(color);
            const auto p_brush = create_brush(canvas, *p_background_details);
            const auto p_stroke_style = create_stroke_style(style);
            canvas.DrawRectangle(
                position_and_dimension_to_rect_f(position, dimension),
                p_brush.get(),
                size_to_float(width),
                p_stroke_style.get());
        }

        /*!
            \brief Fills a rectangle region.

            \tparam Background A background type.

            \param canvas     A canvas.
            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param background A background.

            \throw std::system_error When the rectangle cannot be filled.
        */
        template <typename Background>
        static void fill_rectangle(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const Background&                     background)
        {
            const auto& background_details = background.details();
            if (background_details.is_transparent())
                return;

            const auto p_brush = create_brush(canvas, background_details);

            canvas.FillRectangle(position_and_dimension_to_rect_f(position, dimension), p_brush.get());
        }

        /*!
            \brief Draws a polygon.

            \param canvas    A canvas.
            \param positions A positions of a region.
            \param width     A width.
            \param style     A style.
            \param color     A color.

            \throw std::system_error When the polygon cannot be filled.
        */
        static void draw_polygon(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::type_list::dimension_unit_type&        width,
            const int                                         style,
            const tetengo2::gui::drawing::color&              color);

        /*!
            \brief Fills a polygon region.

            \tparam Background       A background type.

            \param canvas     A canvas.
            \param positions  A positions of a region.
            \param background A background.

            \throw std::system_error When the polygon cannot be filled.
        */
        template <typename Background>
        static void fill_polygon(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const Background&                                 background);

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
            return Font{ log_font.lfFaceName,          static_cast<typename Font::size_type>(-log_font.lfHeight),
                         log_font.lfWeight >= FW_BOLD, log_font.lfItalic != 0,
                         log_font.lfUnderline != 0,    log_font.lfStrikeOut != 0 };
        }

        /*!
            \brief Calculates the dimension of a text.

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
        template <typename Font, typename String, typename Encoder>
        static gui::type_list::dimension_type calc_text_dimension(
            TETENGO2_STDALT_MAYBE_UNUSED const canvas_details_type& canvas,
            const Font&                                             font,
            const String&                                           text,
            const Encoder&                                          encoder,
            const gui::type_list::dimension_unit_type&              max_width)
        {
            const auto p_layout = create_text_layout(text, font, encoder, max_width);

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

        /*!
            \brief Calculates the dimension of a vertical text.

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
        template <typename Font, typename String, typename Encoder>
        static gui::type_list::dimension_type calc_vertical_text_dimension(
            const canvas_details_type& canvas,
            const Font&                font,
            const String&              text,
            const Encoder&             encoder)
        {
            const auto chunks = split_to_vertical_text_chunks(text, encoder);

            using dimension_unit_type = gui::type_list::dimension_unit_type;
            dimension_unit_type max_width{};
            dimension_unit_type total_height{};
            for (const auto& chunk : chunks)
            {
                const auto chunk_dimension = calc_text_dimension<gui::type_list::dimension_type>(
                    canvas, font, chunk, encoder, dimension_unit_type{});
                const auto& chunk_width = chunk_dimension.width();
                const auto& chunk_height = chunk_dimension.height();
                if (character_rotation(chunk, encoder) % 2 == 0)
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

        /*!
            \brief Draws a text.

            \tparam Font          A font type.
            \tparam String        A string type.
            \tparam Encoder       An encoder type.

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
        template <typename Font, typename String, typename Encoder>
        static void draw_text(
            canvas_details_type&                       canvas,
            const Font&                                font,
            const String&                              text,
            const Encoder&                             encoder,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_unit_type& max_width,
            const tetengo2::gui::drawing::color&       color,
            const double                               angle)
        {
            const auto p_layout = create_text_layout(text, font, encoder, max_width);

            const auto p_background_details = create_solid_background(color);
            const auto p_brush = create_brush(canvas, *p_background_details);

            auto original_transform = D2D1::Matrix3x2F();
            canvas.GetTransform(&original_transform);
            BOOST_SCOPE_EXIT((&canvas)(&original_transform))
            {
                canvas.SetTransform(original_transform);
            }
            BOOST_SCOPE_EXIT_END;
            auto rotating_transform =
                D2D1::Matrix3x2F::Rotation(radian_to_degree(angle), position_to_point_2f(position));
            canvas.SetTransform(rotating_transform);

            canvas.DrawTextLayout(position_to_point_2f(position), p_layout.get(), p_brush.get());
        }

        /*!
            \brief Draws a vertical text.

            \tparam Font      A font type.
            \tparam String    A string type.
            \tparam Encoder   An encoder type.

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


            >
        static void draw_vertical_text(
            canvas_details_type&                 canvas,
            const Font&                          font,
            const String&                        text,
            const Encoder&                       encoder,
            const gui::type_list::position_type& position,
            const tetengo2::gui::drawing::color& color)
        {
            const auto dimension =
                calc_vertical_text_dimension<gui::type_list::dimension_type>(canvas, font, text, encoder);
            const auto& max_width = dimension.width();

            const auto chunks = split_to_vertical_text_chunks(text, encoder);

            using position_unit_type = gui::type_list::dimension_unit_type;
            using dimension_unit_type = gui::type_list::dimension_unit_type;
            const auto& base_left = position.left();
            const auto& base_top = position.top();
            auto        next_chunk_top = base_top;
            for (const auto& chunk : chunks)
            {
                const auto chunk_dimension = calc_text_dimension<gui::type_list::dimension_type>(
                    canvas, font, chunk, encoder, dimension_unit_type{});
                const auto& chunk_width = chunk_dimension.width();
                const auto& chunk_height = chunk_dimension.height();

                const int    rotation = character_rotation(chunk, encoder);
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


                draw_text<Font, String, Encoder, gui::type_list::position_type, dimension_unit_type, Color>(
                    canvas, font, chunk, encoder, chunk_position, dimension_unit_type{}, color, angle);

                next_chunk_top +=
                    rotation % 2 == 0 ? position_unit_type::from(chunk_height) : position_unit_type::from(chunk_width);
            }
        }

        /*!
            \brief Paints a picture.

            \tparam Picture   A picture type.

            \param canvas    A canvas.
            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.

            \throw std::system_error When the picture cannot be painted.
        */
        template <typename Picture>
        static void paint_picture(
            canvas_details_type&                  canvas,
            const Picture&                        picture,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension)
        {
            auto& picture_details = const_cast<Picture&>(picture).details();

            ::ID2D1Bitmap* rp_bitmap = nullptr;
            const auto     create_bitmap_hr = canvas.CreateBitmapFromWicBitmap(&picture_details, &rp_bitmap);
            if (FAILED(create_bitmap_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ create_bitmap_hr, direct2d_category() },
                                                          "Can't create bitmap." }));
            }
            const unique_com_ptr<::ID2D1Bitmap> p_bitmap{ rp_bitmap };

            canvas.DrawBitmap(p_bitmap.get(), position_and_dimension_to_rect_f(position, dimension));
        }

        /*!
            \brief Paints an icon.

            \tparam Icon     A icon type.

            \param canvas   A canvas.
            \param icon     An icon to paint.
            \param position A position where the picture is painted.

            \throw std::system_error When the icon cannot be painted.
        */
        template <typename Icon>
        static void
        paint_icon(canvas_details_type& canvas, const Icon& icon, const gui::type_list::position_type& position);


    private:
        // types

        using direct2d_factory_ptr_type = unique_com_ptr<::ID2D1Factory>;

        using direct_write_factory_ptr_type = unique_com_ptr<::IDWriteFactory>;


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
            return { left - 0.5f, top - 0.5f };
        }

        static ::D2D1_RECT_F position_and_dimension_to_rect_f(
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension)
        {
            const auto left = to_dip_x(static_cast<::FLOAT>(position.left().to_pixels()));
            const auto top = to_dip_y(static_cast<::FLOAT>(position.top().to_pixels()));
            const auto width = to_dip_x(static_cast<::FLOAT>(dimension.width().to_pixels()));
            const auto height = to_dip_y(static_cast<::FLOAT>(dimension.height().to_pixels()));
            return { left, top, left + width, top + height };
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
            return { static_cast<::FLOAT>(red / 255.0),
                     static_cast<::FLOAT>(green / 255.0),
                     static_cast<::FLOAT>(blue / 255.0),
                     static_cast<::FLOAT>(alpha / 255.0) };
        }

        static unique_com_ptr<::ID2D1Brush>
        create_brush(canvas_details_type& canvas, const background_details_type& background_details)
        {
            const auto* const p_solid = dynamic_cast<const detail::solid_background_details*>(&background_details);
            if (p_solid)
            {
                ::ID2D1SolidColorBrush* rp_brush = nullptr;
                const auto              hr = canvas.CreateSolidColorBrush(
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

            assert(false);
            BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid background details type." }));
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

        template <typename String, typename Font, typename Encoder, Unit>
        static unique_com_ptr<::IDWriteTextLayout> create_text_layout(
            const String&                              text,
            const Font&                                font,
            const Encoder&                             encoder,
            const gui::type_list::dimension_unit_type& max_width)
        {
            ::IDWriteTextFormat* rp_format = nullptr;
            const auto           create_format_hr = direct_write_factory().CreateTextFormat(
                encoder.encode(font.family()).c_str(),
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

            const auto    encoded_text = encoder.encode(text);
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

        template <typename String, typename Encoder>
        static std::vector<String> split_to_vertical_text_chunks(const String& text, const Encoder& encoder)
        {
            using internal_encoding_type = typename Encoder::internal_encoding_type;
            using utf8_encoder_type = text::encoder<internal_encoding_type, text::encoding::utf8>;
            using character_iterator_type = text::character_iterator<String>;

            static const utf8_encoder_type utf8_encoder{};
            std::vector<String>            chunks{};
            String                         tatechuyoko{};
            const character_iterator_type  end{};
            for (auto i = character_iterator_type(
                     text, text::encoding::make_polymorphic<internal_encoding_type>(encoder.internal_encoding()));
                 i != end;
                 ++i)
            {
                const auto& char_as_string = *i;
                if (is_tatechuyoko_character(char_as_string, utf8_encoder))
                {
                    tatechuyoko.append(char_as_string);
                    continue;
                }
                if (!tatechuyoko.empty())
                {
                    chunks.push_back(tatechuyoko);
                    tatechuyoko.clear();
                }

                if (!chunks.empty() && is_dakuten_character(char_as_string, utf8_encoder))
                    chunks.back().append(char_as_string);
                else
                    chunks.push_back(char_as_string);
            }
            if (!tatechuyoko.empty())
                chunks.push_back(tatechuyoko);

            return std::move(chunks);
        }

        template <typename String, typename Utf8Encoder>
        static bool is_tatechuyoko_character(const String& char_as_string, const Utf8Encoder& utf8_encoder)
        {
            const auto char_in_utf8 = utf8_encoder.encode(char_as_string);

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

        template <typename String, typename Utf8Encoder>
        static bool is_dakuten_character(const String& char_as_string, const Utf8Encoder& utf8_encoder)
        {
            const auto char_in_utf8 = utf8_encoder.encode(char_as_string);

            static const std::vector<std::string> dakutens{
                std::string{ to_char(0xEF), to_char(0xBE), to_char(0x9E) }, // halfwidth katakana dakuten
                std::string{ to_char(0xEF), to_char(0xBE), to_char(0x9F) }, // halfwidth katakana handakuten
            };
            if (std::find(dakutens.begin(), dakutens.end(), char_in_utf8) != dakutens.end())
                return true;

            return false;
        }

        template <typename String, typename Encoder>
        static int character_rotation(const String& char_as_string, const Encoder&)
        {
            using internal_encoding_type = typename Encoder::internal_encoding_type;
            using utf8_encoder_type = text::encoder<internal_encoding_type, text::encoding::utf8>;

            static const utf8_encoder_type utf8_encoder{};
            const auto                     char_in_utf8 = utf8_encoder.encode(char_as_string);

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


        // forbidden operations

        drawing() = delete;
    };
}


#endif
