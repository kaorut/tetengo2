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
#include <tetengo2/detail/windows/picture.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& from,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& to,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED int                                        style,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::color& color) const
        {}

        void draw_focus_indication_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension) const
        {}

        void draw_rectangle_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED int                                        style,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::color& color) const
        {}

        void fill_rectangle_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::background& background) const
        {}

        void draw_polygon_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const std::vector<gui::type_list::position_type>& positions,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED int                                        style,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::color& color) const
        {}

        void fill_polygon_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const std::vector<gui::type_list::position_type>& positions,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::background& background) const
        {}

        gui::drawing::font make_dialog_font_impl() const
        {
            return gui::drawing::font{
                gui::drawing::font::string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false
            };
        }

        gui::type_list::dimension_type calc_text_dimension_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text,
            const gui::type_list::dimension_unit_type&                 max_width) const
        {
            using dimension_unit_type = gui::type_list::dimension_unit_type;
            return max_width == dimension_unit_type{} || max_width >= dimension_unit_type{ 123 } ?
                       gui::type_list::dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } } :
                       gui::type_list::dimension_type{ dimension_unit_type{ 46 }, dimension_unit_type{ 890 } };
        }

        gui::type_list::dimension_type calc_vertical_text_dimension_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text) const
        {
            using dimension_unit_type = gui::type_list::dimension_unit_type;
            return gui::type_list::dimension_type{ dimension_unit_type{ 456 }, dimension_unit_type{ 123 } };
        }

        void draw_text_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& max_width,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::color& color,
            TETENGO2_STDALT_MAYBE_UNUSED double                     angle) const
        {}

        void draw_vertical_text_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::color& color) const
        {}

        void paint_picture_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::drawing::picture& picture,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension) const
        {}

        void paint_icon_impl(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::icon& icon,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position) const
        {}


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
        int                                               style,
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
        double                                     angle) const
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
