/*! \file
    \brief The definition of tetengo2::detail::base::drawing.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cstdint>
#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>

namespace tetengo2::gui {
    class icon;

    namespace drawing {
        class background;
        class color;
        class picture;
    }
}


namespace tetengo2::detail::base {
    class widget;

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


        // functions

        std::unique_ptr<canvas_details_type> create_canvas(const widget& widget_details, const drawing& self) const
        {
            return self.create_canvas_impl(widget_details);
        }

        std::unique_ptr<canvas_details_type> create_canvas(std::intptr_t canvas_handle, const drawing& self) const
        {
            return self.create_canvas_impl(canvas_handle);
        }

        void begin_transaction(
            canvas_details_type&                  canvas,
            const gui::type_list::dimension_type& dimension,
            const drawing&                        self) const
        {
            self.begin_transaction_impl(canvas, dimension);
        }

        void end_transaction(canvas_details_type& canvas, const drawing& self) const
        {
            self.end_transaction_impl(canvas);
        }

        std::unique_ptr<background_details_type>
        create_solid_background(const gui::drawing::color& color, const drawing& self) const
        {
            return self.create_solid_background_impl(color);
        }

        std::unique_ptr<background_details_type> create_transparent_background(const drawing& self) const
        {
            return self.create_transparent_background_impl();
        }

        std::unique_ptr<picture_details_type>
        create_picture(const gui::type_list::dimension_type& dimension, const drawing& self) const
        {
            return self.create_picture_impl(dimension);
        }

        std::unique_ptr<picture_details_type>
        read_picture(const tetengo2::stdalt::filesystem::path& path, const drawing& self) const
        {
            return self.read_picture_impl(path);
        }

        gui::type_list::dimension_type picture_dimension(const picture_details_type& picture, const drawing& self) const
        {
            return self.picture_dimension_impl(picture);
        }

        void draw_line(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       from,
            const gui::type_list::position_type&       to,
            const gui::type_list::dimension_unit_type& width,
            const int                                  style,
            const gui::drawing::color&                 color,
            const drawing&                             self) const
        {
            self.draw_line_impl(canvas, from, to, width, style, color);
        }

        void draw_focus_indication(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const drawing&                        self) const
        {
            self.draw_focus_indication_impl(canvas, position, dimension);
        }

        void draw_rectangle(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_type&      dimension,
            const gui::type_list::dimension_unit_type& width,
            const int                                  style,
            const gui::drawing::color&                 color,
            const drawing&                             self) const
        {
            self.draw_rectangle_impl(canvas, position, dimension, width, style, color);
        }

        void fill_rectangle(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const gui::drawing::background&       background,
            const drawing&                        self) const
        {
            self.fill_rectangle_impl(canvas, position, dimension, background);
        }

        void draw_polygon(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::type_list::dimension_unit_type&        width,
            const int                                         style,
            const gui::drawing::color&                        color,
            const drawing&                                    self) const
        {
            self.draw_polygon_impl(canvas, positions, width, style, color);
        }

        void fill_polygon(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::drawing::background&                   background,
            const drawing&                                    self) const
        {
            self.fill_polygon_impl(canvas, positions, background);
        }

        gui::drawing::font make_dialog_font(const drawing& self) const
        {
            return self.make_dialog_font_impl();
        }

        gui::type_list::dimension_type calc_text_dimension(
            const canvas_details_type&                 canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::dimension_unit_type& max_width,
            const drawing&                             self) const
        {
            return self.calc_text_dimension_impl(canvas, font, text, max_width);
        }

        gui::type_list::dimension_type calc_vertical_text_dimension(
            const canvas_details_type&    canvas,
            const gui::drawing::font&     font,
            const type_list::string_type& text,
            const drawing&                self) const
        {
            return self.calc_vertical_text_dimension_impl(canvas, font, text);
        }

        void draw_text(
            canvas_details_type&                       canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_unit_type& max_width,
            const gui::drawing::color&                 color,
            const double                               angle,
            const drawing&                             self) const
        {
            self.draw_text_impl(canvas, font, text, position, max_width, color, angle);
        }

        void draw_vertical_text(
            canvas_details_type&                 canvas,
            const gui::drawing::font&            font,
            const type_list::string_type&        text,
            const gui::type_list::position_type& position,
            const gui::drawing::color&           color,
            const drawing&                       self) const
        {
            self.draw_vertical_text_impl(canvas, font, text, position, color);
        }

        void paint_picture(
            canvas_details_type&                  canvas,
            const gui::drawing::picture&          picture,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const drawing&                        self) const
        {
            self.paint_picture_impl(canvas, picture, position, dimension);
        }

        void paint_icon(
            canvas_details_type&                 canvas,
            const gui::icon&                     icon,
            const gui::type_list::position_type& position,
            const drawing&                       self) const
        {
            self.paint_icon_impl(canvas, icon, position);
        }
    };


    drawing::background_details_type::~background_details_type() = default;

    drawing::picture_details_type::~picture_details_type() = default;

    drawing::canvas_details_type::~canvas_details_type() = default;

    drawing::~drawing() = default;

    std::unique_ptr<drawing::canvas_details_type> drawing::create_canvas(const widget& widget_details) const
    {
        return m_p_impl->create_canvas(widget_details, *this);
    }

    std::unique_ptr<drawing::canvas_details_type> drawing::create_canvas(const std::intptr_t canvas_handle) const
    {
        return m_p_impl->create_canvas(canvas_handle, *this);
    }

    void drawing::begin_transaction(canvas_details_type& canvas, const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->begin_transaction(canvas, dimension, *this);
    }

    void drawing::end_transaction(canvas_details_type& canvas) const
    {
        m_p_impl->end_transaction(canvas, *this);
    }

    std::unique_ptr<drawing::background_details_type>
    drawing::create_solid_background(const gui::drawing::color& color) const
    {
        return m_p_impl->create_solid_background(color, *this);
    }

    std::unique_ptr<drawing::background_details_type> drawing::create_transparent_background() const
    {
        return m_p_impl->create_transparent_background(*this);
    }

    std::unique_ptr<drawing::picture_details_type>
    drawing::create_picture(const gui::type_list::dimension_type& dimension) const
    {
        return m_p_impl->create_picture(dimension, *this);
    }

    std::unique_ptr<drawing::picture_details_type>
    drawing::read_picture(const tetengo2::stdalt::filesystem::path& path) const
    {
        return m_p_impl->read_picture(path, *this);
    }

    gui::type_list::dimension_type drawing::picture_dimension(const picture_details_type& picture) const
    {
        return m_p_impl->picture_dimension(picture, *this);
    }

    void drawing::draw_line(
        canvas_details_type&                       canvas,
        const gui::type_list::position_type&       from,
        const gui::type_list::position_type&       to,
        const gui::type_list::dimension_unit_type& width,
        const int                                  style,
        const gui::drawing::color&                 color) const
    {
        m_p_impl->draw_line(canvas, from, to, width, style, color, *this);
    }

    void drawing::draw_focus_indication(
        canvas_details_type&                  canvas,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->draw_focus_indication(canvas, position, dimension, *this);
    }

    void drawing::draw_rectangle(
        canvas_details_type&                       canvas,
        const gui::type_list::position_type&       position,
        const gui::type_list::dimension_type&      dimension,
        const gui::type_list::dimension_unit_type& width,
        const int                                  style,
        const gui::drawing::color&                 color) const
    {
        m_p_impl->draw_rectangle(canvas, position, dimension, width, style, color, *this);
    }

    void drawing::fill_rectangle(
        canvas_details_type&                  canvas,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension,
        const gui::drawing::background&       background) const
    {
        m_p_impl->fill_rectangle(canvas, position, dimension, background, *this);
    }

    void drawing::draw_polygon(
        canvas_details_type&                              canvas,
        const std::vector<gui::type_list::position_type>& positions,
        const gui::type_list::dimension_unit_type&        width,
        const int                                         style,
        const gui::drawing::color&                        color) const
    {
        m_p_impl->draw_polygon(canvas, positions, width, style, color, *this);
    }

    void drawing::fill_polygon(
        canvas_details_type&                              canvas,
        const std::vector<gui::type_list::position_type>& positions,
        const gui::drawing::background&                   background) const
    {
        m_p_impl->fill_polygon(canvas, positions, background, *this);
    }

    gui::drawing::font drawing::make_dialog_font() const
    {
        return m_p_impl->make_dialog_font(*this);
    }

    gui::type_list::dimension_type drawing::calc_text_dimension(
        const canvas_details_type&                 canvas,
        const gui::drawing::font&                  font,
        const type_list::string_type&              text,
        const gui::type_list::dimension_unit_type& max_width) const
    {
        return m_p_impl->calc_text_dimension(canvas, font, text, max_width, *this);
    }

    gui::type_list::dimension_type drawing::calc_vertical_text_dimension(
        const canvas_details_type&    canvas,
        const gui::drawing::font&     font,
        const type_list::string_type& text) const
    {
        return m_p_impl->calc_vertical_text_dimension(canvas, font, text, *this);
    }

    void drawing::draw_text(
        canvas_details_type&                       canvas,
        const gui::drawing::font&                  font,
        const type_list::string_type&              text,
        const gui::type_list::position_type&       position,
        const gui::type_list::dimension_unit_type& max_width,
        const gui::drawing::color&                 color,
        const double                               angle) const
    {
        m_p_impl->draw_text(canvas, font, text, position, max_width, color, angle, *this);
    }

    void drawing::draw_vertical_text(
        canvas_details_type&                 canvas,
        const gui::drawing::font&            font,
        const type_list::string_type&        text,
        const gui::type_list::position_type& position,
        const gui::drawing::color&           color) const
    {
        m_p_impl->draw_vertical_text(canvas, font, text, position, color, *this);
    }

    void drawing::paint_picture(
        canvas_details_type&                  canvas,
        const gui::drawing::picture&          picture,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->paint_picture(canvas, picture, position, dimension, *this);
    }

    void drawing::paint_icon(
        canvas_details_type&                 canvas,
        const gui::icon&                     icon,
        const gui::type_list::position_type& position) const
    {
        m_p_impl->paint_icon(canvas, icon, position, *this);
    }

    drawing::drawing() : m_p_impl{ std::make_unique<impl>() } {}
}
