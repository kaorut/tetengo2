/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::drawing.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H

#include <cstdint>
#include <memory>
#include <vector>

#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui {
    class icon;

    namespace drawing {
        class background;
        class font;
        class picture;
    }
}}


namespace tetengo2::detail::windows::gdiplus {
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing : public base::drawing
    {
    public:
        // types

        //! The background details type.
        using background_details_type = base::drawing::background_details_type;

        //! The background details pointer type.
        using background_details_ptr_type = base::drawing::background_details_ptr_type;

        //! The picture details type.
        using picture_details_type = base::drawing::picture_details_type;

        //! The picture details pointer type.
        using picture_details_ptr_type = base::drawing::picture_details_ptr_type;

        //! The canvas details type.
        using canvas_details_type = base::drawing::canvas_details_type;

        //! The canvas details pointer type.
        using canvas_details_ptr_type = base::drawing::canvas_details_ptr_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const drawing& instance();


        // constructors and destructors

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~drawing();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        drawing();


        // virtual functions

        virtual std::unique_ptr<canvas_details_type>
        create_canvas_impl(const base::widget::widget_details_type& widget_details) const override;

        virtual std::unique_ptr<canvas_details_type> create_canvas_impl(std::intptr_t canvas_handle) const override;

        virtual void begin_transaction_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::dimension_type& dimension) const override;

        virtual void end_transaction_impl(canvas_details_type& canvas) const override;

        virtual std::unique_ptr<background_details_type>
        create_solid_background_impl(const gui::drawing::color& color) const override;

        virtual std::unique_ptr<background_details_type> create_transparent_background_impl() const override;

        virtual std::unique_ptr<picture_details_type>
        create_picture_impl(const gui::type_list::dimension_type& dimension) const override;

        virtual std::unique_ptr<picture_details_type>
        read_picture_impl(const tetengo2::stdalt::filesystem::path& path) const override;

        virtual gui::type_list::dimension_type
        picture_dimension_impl(const picture_details_type& picture) const override;

        virtual void draw_line_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       from,
            const gui::type_list::position_type&       to,
            const gui::type_list::dimension_unit_type& width,
            int                                        style,
            const gui::drawing::color&                 color) const override;

        virtual void draw_focus_indication_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const override;

        virtual void draw_rectangle_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_type&      dimension,
            const gui::type_list::dimension_unit_type& width,
            int                                        style,
            const gui::drawing::color&                 color) const override;

        virtual void fill_rectangle_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const gui::drawing::background&       background) const override;

        virtual void draw_polygon_impl(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::type_list::dimension_unit_type&        width,
            int                                               style,
            const gui::drawing::color&                        color) const override;

        virtual void fill_polygon_impl(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::drawing::background&                   background) const override;

        virtual gui::drawing::font make_dialog_font_impl() const override;

        virtual gui::type_list::dimension_type calc_text_dimension_impl(
            const canvas_details_type&                 canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::dimension_unit_type& max_width) const override;

        virtual gui::type_list::dimension_type calc_vertical_text_dimension_impl(
            const canvas_details_type&    canvas,
            const gui::drawing::font&     font,
            const type_list::string_type& text) const override;

        virtual void draw_text_impl(
            canvas_details_type&                       canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_unit_type& max_width,
            const gui::drawing::color&                 color,
            double                                     angle) const override;

        virtual void draw_vertical_text_impl(
            canvas_details_type&                 canvas,
            const gui::drawing::font&            font,
            const type_list::string_type&        text,
            const gui::type_list::position_type& position,
            const gui::drawing::color&           color) const override;

        virtual void paint_picture_impl(
            canvas_details_type&                  canvas,
            const gui::drawing::picture&          picture,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const override;

        virtual void paint_icon_impl(
            canvas_details_type&                 canvas,
            const gui::icon&                     icon,
            const gui::type_list::position_type& position) const override;
    };
}


#if 0
#include <algorithm> // IWYU pragma: keep
#include <cassert>
#include <cstddef> // IWYU pragma: keep
#include <iterator> // IWYU pragma: keep
#include <limits> // IWYU pragma: keep
#include <memory> // IWYU pragma: keep
#include <stdexcept> // IWYU pragma: keep
#include <system_error> // IWYU pragma: keep
#include <type_traits> // IWYU pragma: keep
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

#include <tetengo2/detail/windows/error_category.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/font.h>
#include <tetengo2/detail/windows/gdiplus/error_category.h> // IWYU pragma: keep
#include <tetengo2/detail/windows/icon.h>
#include <tetengo2/detail/windows/picture.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/type_list.h>


namespace tetengo2::detail::windows::gdiplus {
#if !defined(DOCUMENTATION)
    namespace detail {
        class background_details : private boost::noncopyable
        {
        public:
            background_details() : m_p_brush{} {}

            explicit background_details(std::unique_ptr<Gdiplus::Brush> p_brush) : m_p_brush{ std::move(p_brush) } {}

            const Gdiplus::Brush* get() const
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
            : m_p_widget_graphics{ create_canvas_impl(handle_or_widget_details) }, m_p_memory_image{},
              m_p_memory_graphics{}
            {}

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
            template <typename HandleOrWidgetDetails>
            static std::unique_ptr<Gdiplus::Graphics> create_canvas_impl(
                const HandleOrWidgetDetails& handle,
                typename std::enable_if<std::is_convertible<HandleOrWidgetDetails, ::HDC>::value>::type* = nullptr)
            {
                auto p_canvas = std::make_unique<Gdiplus::Graphics>(handle);

                initialize_canvas(*p_canvas);

                return std::move(p_canvas);
            }

            template <typename HandleOrWidgetDetails>
            static std::unique_ptr<Gdiplus::Graphics> create_canvas_impl(
                const HandleOrWidgetDetails& widget_details,
                typename std::enable_if<!std::is_convertible<HandleOrWidgetDetails, ::HDC>::value>::type* = nullptr)
            {
                auto p_canvas = std::make_unique<Gdiplus::Graphics>(widget_details.handle.get());

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

        inline const native_drawing_encoder_type& native_drawing_encoder()
        {
            static const native_drawing_encoder_type singleton;
            return singleton;
        }
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
        static std::unique_ptr<canvas_details_type> create_canvas(const HandleOrWidgetDetails& handle_or_widget_details)
        {
            return std::make_unique<canvas_details_type>(handle_or_widget_details);
        }

        /*!
            \brief Begins a transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \param canvas    A canvas.
            \param dimension A dimension.

            \throw std::logic_error When another transaction has not ended yet.
        */
        static void begin_transaction(canvas_details_type& canvas, const gui::type_list::dimension_type& dimension)
        {
            canvas.begin_transaction(
                static_cast<::INT>(dimension.width().to_pixels()), static_cast<::INT>(dimension.height().to_pixels()));
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


            \param color A color.

            \return A unique pointer to a solid background.
        */
        static std::unique_ptr<background_details_type>
        create_solid_background(const tetengo2::gui::drawing::color& color)
        {
            return std::make_unique<background_details_type>(std::make_unique<Gdiplus::SolidBrush>(
                Gdiplus::Color(color.alpha(), color.red(), color.green(), color.blue())));
        }

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        static std::unique_ptr<background_details_type> create_transparent_background()
        {
            return std::make_unique<background_details_type>();
        }

        /*!
            \brief Creates a picture.


            \param dimension A dimension.

            \return A unique pointer to a picture.
        */
        static picture_details_ptr_type create_picture(const gui::type_list::dimension_type& dimension)
        {
            return picture::instance().create(dimension);
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
            TETENGO2_STDALT_MAYBE_UNUSED const int     style,
            const tetengo2::gui::drawing::color&       color)
        {
            const Gdiplus::Pen    pen{ Gdiplus::Color{ color.alpha(), color.red(), color.green(), color.blue() },
                                    static_cast<Gdiplus::REAL>(width.to_pixels()) };
            const Gdiplus::PointF gdiplus_from{ static_cast<Gdiplus::REAL>(from.left().to_pixels()),
                                                static_cast<Gdiplus::REAL>(from.top().to_pixels()) };
            const Gdiplus::PointF gdiplus_to{ static_cast<Gdiplus::REAL>(to.left().to_pixels()),
                                              static_cast<Gdiplus::REAL>(to.top().to_pixels()) };
            const auto            status = canvas.get().DrawLine(&pen, gdiplus_from, gdiplus_to);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't draw a line." }));
            }
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
            const gui::type_list::dimension_type& dimension)
        {
            const ::RECT rect{ static_cast<::LONG>(position.left().to_pixels()),
                               static_cast<::LONG>(position.top().to_pixels()),
                               static_cast<::LONG>(dimension.width().to_pixels()),
                               static_cast<::LONG>(dimension.height().to_pixels()) };
            if (::DrawFocusRect(canvas.get().GetHDC(), &rect) == 0)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ Gdiplus::Win32Error, gdiplus_category() },
                                                          "Can't draw a focus rectangle." }));
            }
        }

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
            const tetengo2::gui::drawing::color&       color);

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
            if (!background_details.get())
                return;

            const Gdiplus::Rect rectangle{ static_cast<::INT>(position.left().to_pixels()),
                                           static_cast<::INT>(position.top().to_pixels()),
                                           static_cast<::INT>(dimension.width().to_pixels()),
                                           static_cast<::INT>(dimension.height().to_pixels()) };
            const auto          status = canvas.get().FillRectangle(background_details.get(), rectangle);
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't fill a rectangle." }));
            }
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
            TETENGO2_STDALT_MAYBE_UNUSED const int            style,
            const tetengo2::gui::drawing::color&              color)
        {
            const Gdiplus::Pen pen{ Gdiplus::Color{ color.alpha(), color.red(), color.green(), color.blue() },
                                    static_cast<Gdiplus::REAL>(width.to_pixels()) };
            const auto         points = to_gdiplus_points(positions);
            const auto status = canvas.get().DrawPolygon(&pen, points.data(), static_cast<::INT>(points.size()));
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't draw a polygon." }));
            }
        }

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
            const Background&                                 background)
        {
            const auto& background_details = background.details();
            if (!background_details.get())
                return;

            const auto points = to_gdiplus_points(positions);
            const auto status =
                canvas.get().FillPolygon(background_details.get(), points.data(), static_cast<::INT>(points.size()));
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ status, gdiplus_category() }, "Can't fill a polygon." }));
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
            return Font{ log_font.lfFaceName,          static_cast<typename Font::size_type>(-log_font.lfHeight),
                         log_font.lfWeight >= FW_BOLD, log_font.lfItalic != 0,
                         log_font.lfUnderline != 0,    log_font.lfStrikeOut != 0 };
        }

        /*!
            \brief Calculates the dimension of a text.

            \tparam Font A font type.

            \param canvas    A canvas.
            \param font      A font.
            \param text      A text.
            \param max_width A maximum width. When 0 is specified, the width is infinite.

            \return The dimension of the text.

            \throw std::system_error When the dimention of a text cannot be calculated.
        */
        template <typename Font>
        static gui::type_list::dimension_type calc_text_dimension(
            const canvas_details_type&                 canvas,
            const Font&                                font,
            const type_list::string_type&              text,
            const gui::type_list::dimension_unit_type& max_width)
        {
            const auto encoded_text = detail::native_drawing_encoder().encode(text);

            const Gdiplus::InstalledFontCollection font_collection;
            const auto                             p_gdiplus_font = create_gdiplus_font(font, font_collection);

            const Gdiplus::REAL gdiplus_max_width = max_width == gui::type_list::dimension_unit_type{} ?
                                                        std::numeric_limits<Gdiplus::REAL>::max() :
                                                        static_cast<Gdiplus::REAL>(max_width.to_pixels());
            const Gdiplus::RectF layout{ 0, 0, gdiplus_max_width, std::numeric_limits<Gdiplus::REAL>::max() };
            Gdiplus::RectF       bounding;
            const auto           status = canvas.get().MeasureString(
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

            return { gui::type_list::dimension_unit_type::from_pixels(bounding.Width),
                     gui::type_list::dimension_unit_type::from_pixels(bounding.Height) };
        }

        /*!
            \brief Calculates the dimension of a vertical text.

            \tparam Font A font type.

            \param canvas A canvas.
            \param font   A font.
            \param text   A text.

            \return The dimension of the vertical text.

            \throw std::system_error When the dimention of a vertical text cannot be calculated.
        */
        template <typename Font>
        static gui::type_list::dimension_type calc_vertical_text_dimension(
            const canvas_details_type&    canvas,
            const Font&                   font,
            const type_list::string_type& text);

        /*!
            \brief Draws a text.

            \tparam Font A font type.

            \param canvas    A canvas.
            \param font      A font.
            \param text      A text to draw.
            \param position  A position where the text is drawn.
            \param max_width A maximum width. When 0 is specified, the width is infinite.
            \param color     A color.
            \param angle     A clockwise angle in radians.

            \throw std::system_error When the text cannot be drawn.
        */
        template <typename Font>
        static void draw_text(
            canvas_details_type&                       canvas,
            const Font&                                font,
            const type_list::string_type&              text,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_unit_type& max_width,
            const tetengo2::gui::drawing::color&       color,
            const double                               angle)
        {
            const auto encoded_text = detail::native_drawing_encoder().encode(text);

            const Gdiplus::InstalledFontCollection font_collection;
            const auto                             p_gdiplus_font = create_gdiplus_font(font, font_collection);

            const auto p_solid_brush = create_solid_background(color);

            const Gdiplus::PointF gdiplus_point{ static_cast<Gdiplus::REAL>(position.left().to_pixels()),
                                                 static_cast<Gdiplus::REAL>(position.top().to_pixels()) };
            const Gdiplus::REAL   gdiplus_max_width = max_width == gui::type_list::dimension_unit_type{} ?
                                                        std::numeric_limits<Gdiplus::REAL>::max() :
                                                        static_cast<Gdiplus::REAL>(max_width.to_pixels());
            const Gdiplus::RectF layout{
                gdiplus_point.X, gdiplus_point.Y, gdiplus_max_width, std::numeric_limits<Gdiplus::REAL>::max()
            };

            Gdiplus::Matrix original_matrix;
            const auto      get_transform_status = canvas.get().GetTransform(&original_matrix);
            if (get_transform_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ get_transform_status, gdiplus_category() },
                                                          "Can't get transform!" }));
            }
            Gdiplus::Matrix rotating_matrix;
            rotating_matrix.RotateAt(radian_to_degree(angle), gdiplus_point);
            const auto set_transform_status = canvas.get().SetTransform(&rotating_matrix);
            if (set_transform_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ set_transform_status, gdiplus_category() },
                                                          "Can't set transform!" }));
            }
            BOOST_SCOPE_EXIT((&canvas)(&original_matrix))
            {
                canvas.get().SetTransform(&original_matrix);
            }
            BOOST_SCOPE_EXIT_END;

            const auto draw_string_status = canvas.get().DrawString(
                encoded_text.c_str(),
                static_cast<::INT>(encoded_text.length()),
                p_gdiplus_font.get(),
                layout,
                Gdiplus::StringFormat::GenericTypographic(),
                p_solid_brush->get());
            if (draw_string_status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ draw_string_status, gdiplus_category() },
                                                          "Can't draw text!" }));
            }
        }

        /*!
            \brief Draws a vertical text.

            \tparam Font A font type.

            \param canvas   A canvas.
            \param font     A font.
            \param text     A text to draw.
            \param position A position where the text is drawn.
            \param color    A color.

            \throw std::system_error When the text cannot be drawn.
        */
        template <typename Font>
        static void draw_vertical_text(
            canvas_details_type&                 canvas,
            const Font&                          font,
            const type_list::string_type&        text,
            const gui::type_list::position_type& position,
            const tetengo2::gui::drawing::color& color);

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

            ::WICPixelFormatGUID pixel_format_guid{};
            const auto           get_pixel_format_hr = picture_details.GetPixelFormat(&pixel_format_guid);
            if (FAILED(get_pixel_format_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ get_pixel_format_hr, wic_category() },
                                                          "Can't get pixel format." }));
            }

            ::UINT     width = 0;
            ::UINT     height = 0;
            const auto get_size_hr = picture_details.GetSize(&width, &height);
            if (FAILED(get_size_hr))
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ get_size_hr, wic_category() }, "Can't get size of picture." }));
            }
            const ::UINT        stride = width * sizeof(Gdiplus::ARGB);
            const ::UINT        buffer_size = stride * height;
            std::vector<::BYTE> buffer(buffer_size, 0);

            const ::WICRect rectangle{ 0, 0, static_cast<::INT>(width), static_cast<::INT>(height) };
            const auto      copy_pixels_hr = picture_details.CopyPixels(&rectangle, stride, buffer_size, buffer.data());
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
            const auto      status = canvas.get().DrawImage(
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

        /*!
            \brief Paints an icon.

            \param canvas   A canvas.
            \param icon     An icon to paint.
            \param position A position where the picture is painted.

            \throw std::system_error When the icon cannot be painted.
        */
        static void
        paint_icon(canvas_details_type& canvas, const gui::icon& icon, const gui::type_list::position_type& position)
        {
            const ::BOOL result = ::DrawIconEx(
                canvas.get().GetHDC(),
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

        template <typename Font>
        static std::unique_ptr<Gdiplus::Font> create_gdiplus_font(
            const Font&                    font,
            const Gdiplus::FontCollection& font_collection,
            const std::size_t              fallback_level = 0)
        {
            if (fallback_level > 2)
            {
                BOOST_THROW_EXCEPTION((std::system_error{
                    std::error_code{ Gdiplus::FontFamilyNotFound, gdiplus_category() }, "Font is not available." }));
            }

            const auto&               font_family = fallback_level < 1 ? font.family() : Font::dialog_font().family();
            const Gdiplus::FontFamily gdiplus_font_family{ detail::native_drawing_encoder().encode(font_family).c_str(),
                                                           &font_collection };
            if (!gdiplus_font_family.IsAvailable())
            {
                return create_gdiplus_font(font, font_collection, fallback_level + 1);
            }

            const auto font_size = fallback_level < 2 ? static_cast<Gdiplus::REAL>(font.size()) :
                                                        static_cast<Gdiplus::REAL>(Font::dialog_font().size());
            const auto font_style = fallback_level < 2 ? get_font_style(font) : get_font_style(Font::dialog_font());
            auto       p_gdiplus_font =
                std::make_unique<Gdiplus::Font>(&gdiplus_font_family, font_size, font_style, Gdiplus::UnitPixel);
            if (!p_gdiplus_font->IsAvailable())
                return create_gdiplus_font(font, font_collection, fallback_level + 1);

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

        drawing() = delete;
    };
}
#endif


#endif
