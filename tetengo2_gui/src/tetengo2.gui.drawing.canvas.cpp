/*! \file
    \brief The definition of tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/color.h> // IWYU pragma: keep
#include <tetengo2/gui/drawing/font.h> // IWYU pragma: keep
#include <tetengo2/gui/drawing/picture.h> // IWYU pragma: keep
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/unit/em.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a canvas.
    */
    class canvas::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = canvas::string_type;

        using position_type = canvas::position_type;

        using dimension_type = canvas::dimension_type;

        using dimension_unit_type = canvas::dimension_unit_type;

        using drawing_details_type = canvas::drawing_details_type;

        using details_type = canvas::details_type;

        using details_ptr_type = canvas::details_ptr_type;

        using background_type = canvas::background_type;

        using font_type = canvas::font_type;

        using picture_type = canvas::picture_type;

        using icon_type = canvas::icon_type;

        using color_type = canvas::color_type;

        using line_style_type = canvas::line_style_type;


        // constructors and destructor

        impl(const drawing_details_type& drawing_details, details_ptr_type p_details)
        : m_drawing_details(drawing_details), m_p_details{ std::move(p_details) }, m_color{ 0, 0, 0, 255 },
          m_p_background{
              std::make_unique<const solid_background_type>(m_drawing_details, color_type{ 255, 255, 255, 255 })
          },
          m_line_width{ dimension_unit_type{ 1 } }, m_line_style{ line_style_type::solid }, m_font{
              font_type::dialog_font()
          }
        {
            if (!m_p_details)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The detail implementation is nullptr." }));
        }

        // functions

        void begin_transaction(const dimension_type& dimension)
        {
            m_drawing_details.begin_transaction(*m_p_details, dimension);
        }

        void end_transaction()
        {
            m_drawing_details.end_transaction(*m_p_details);
        }

        const color_type& get_color() const
        {
            return m_color;
        }

        void set_color(color_type color)
        {
            m_color = std::move(color);
        }

        const background_type& get_background() const
        {
            assert(m_p_background);
            return *m_p_background;
        }

        void set_background(std::unique_ptr<const background_type> p_background)
        {
            if (!p_background)
            {
                BOOST_THROW_EXCEPTION(std::invalid_argument{ "The specified background is nullptr." });
            }
            if (&p_background->drawing_details() != &m_drawing_details)
            {
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument{ "The drawing detail implementations mismatch." });
            }
            m_p_background = std::move(p_background);
        }

        const dimension_unit_type& line_width() const
        {
            return m_line_width;
        }

        void set_line_width(dimension_unit_type line_width)
        {
            m_line_width = std::move(line_width);
        }

        line_style_type line_style() const
        {
            return m_line_style;
        }

        void set_line_style(const line_style_type line_style)
        {
            m_line_style = line_style;
        }

        const font_type& get_font() const
        {
            return m_font;
        }

        void set_font(font_type font)
        {
            m_font = std::move(font);
        }

        void draw_line(const position_type& from, const position_type& to)
        {
            m_drawing_details.draw_line(*m_p_details, from, to, m_line_width, static_cast<int>(m_line_style), m_color);
        }

        void draw_focus_indication(const position_type& position, const dimension_type& dimension)
        {
            m_drawing_details.draw_focus_indication(*m_p_details, position, dimension);
        }

        void draw_rectangle(const position_type& position, const dimension_type& dimension)
        {
            assert(m_p_background);
            m_drawing_details.draw_rectangle(
                *m_p_details, position, dimension, m_line_width, static_cast<int>(m_line_style), m_color);
        }

        void fill_rectangle(const position_type& position, const dimension_type& dimension)
        {
            assert(m_p_background);
            m_drawing_details.fill_rectangle(*m_p_details, position, dimension, *m_p_background);
        }

        void draw_polygon(const std::vector<position_type>& positions)
        {
            m_drawing_details.draw_polygon(
                *m_p_details, positions, m_line_width, static_cast<int>(m_line_style), m_color);
        }

        void fill_polygon(const std::vector<position_type>& positions)
        {
            assert(m_p_background);
            m_drawing_details.fill_polygon(*m_p_details, positions, *m_p_background);
        }

        dimension_type calc_text_dimension(const string_type& text) const
        {
            return calc_text_dimension(text, dimension_unit_type{});
        }

        dimension_type calc_text_dimension(const string_type& text, const dimension_unit_type& max_width) const
        {
            return m_drawing_details.calc_text_dimension(*m_p_details, m_font, text, max_width);
        }

        dimension_type calc_vertical_text_dimension(const string_type& text) const
        {
            return m_drawing_details.calc_vertical_text_dimension(*m_p_details, m_font, text);
        }

        void draw_text(const string_type& text, const position_type& position, const double angle)
        {
            draw_text(text, position, dimension_unit_type{}, angle);
        }

        void draw_text(
            const string_type&         text,
            const position_type&       position,
            const dimension_unit_type& max_width,
            const double               angle)
        {
            m_drawing_details.draw_text(*m_p_details, m_font, text, position, max_width, m_color, angle);
        }

        void draw_vertical_text(const string_type& text, const position_type& position)
        {
            m_drawing_details.draw_vertical_text(*m_p_details, m_font, text, position, m_color);
        }

        void paint_picture(const picture_type& picture, const position_type& position, const dimension_type& dimension)
        {
            if (&picture.drawing_details() != &m_drawing_details)
            {
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument{ "The picture detail implementations mismatch." });
            }
            m_drawing_details.paint_picture(*m_p_details, picture, position, dimension);
        }

        void paint_picture(const picture_type& picture, const position_type& position)
        {
            paint_picture(picture, position, picture.dimension());
        }

        void paint_icon(const icon_type& icon, const position_type& position)
        {
            m_drawing_details.paint_icon(*m_p_details, icon, position);
        }

        const drawing_details_type& drawing_details() const
        {
            return m_drawing_details;
        }

        const details_type& details() const
        {
            assert(m_p_details);
            return *m_p_details;
        }

        details_type& details()
        {
            assert(m_p_details);
            return *m_p_details;
        }


    private:
        // types

        using solid_background_type = solid_background;


        // variables

        const drawing_details_type& m_drawing_details;

        const details_ptr_type m_p_details;

        color_type m_color;

        std::unique_ptr<const background_type> m_p_background;

        dimension_unit_type m_line_width;

        line_style_type m_line_style;

        font_type m_font;
    };


    canvas::~canvas() = default;

    void canvas::begin_transaction(const dimension_type& dimension)
    {
        m_p_impl->begin_transaction(dimension);
    }

    void canvas::end_transaction()
    {
        m_p_impl->end_transaction();
    }

    const canvas::color_type& canvas::get_color() const
    {
        return m_p_impl->get_color();
    }

    void canvas::set_color(color_type color)
    {
        m_p_impl->set_color(std::move(color));
    }

    const canvas::background_type& canvas::get_background() const
    {
        return m_p_impl->get_background();
    }

    void canvas::set_background(std::unique_ptr<const background_type> p_background)
    {
        m_p_impl->set_background(std::move(p_background));
    }

    const canvas::dimension_unit_type& canvas::line_width() const
    {
        return m_p_impl->line_width();
    }

    void canvas::set_line_width(dimension_unit_type line_width)
    {
        m_p_impl->set_line_width(std::move(line_width));
    }

    canvas::line_style_type canvas::line_style() const
    {
        return m_p_impl->line_style();
    }

    void canvas::set_line_style(const line_style_type line_style)
    {
        m_p_impl->set_line_style(line_style);
    }

    const canvas::font_type& canvas::get_font() const
    {
        return m_p_impl->get_font();
    }

    void canvas::set_font(font_type font)
    {
        m_p_impl->set_font(std::move(font));
    }

    void canvas::draw_line(const position_type& from, const position_type& to)
    {
        m_p_impl->draw_line(from, to);
    }

    void canvas::draw_focus_indication(const position_type& position, const dimension_type& dimension)
    {
        m_p_impl->draw_focus_indication(position, dimension);
    }

    void canvas::draw_rectangle(const position_type& position, const dimension_type& dimension)
    {
        m_p_impl->draw_rectangle(position, dimension);
    }

    void canvas::fill_rectangle(const position_type& position, const dimension_type& dimension)
    {
        m_p_impl->fill_rectangle(position, dimension);
    }

    void canvas::draw_polygon(const std::vector<position_type>& positions)
    {
        m_p_impl->draw_polygon(positions);
    }

    void canvas::fill_polygon(const std::vector<position_type>& positions)
    {
        m_p_impl->fill_polygon(positions);
    }

    canvas::dimension_type canvas::calc_text_dimension(const string_type& text) const
    {
        return m_p_impl->calc_text_dimension(text);
    }

    canvas::dimension_type
    canvas::calc_text_dimension(const string_type& text, const dimension_unit_type& max_width) const
    {
        return m_p_impl->calc_text_dimension(text, max_width);
    }

    canvas::dimension_type canvas::calc_vertical_text_dimension(const string_type& text) const
    {
        return m_p_impl->calc_vertical_text_dimension(text);
    }

    void canvas::draw_text(const string_type& text, const position_type& position, const double angle /*= 0.0*/)
    {
        m_p_impl->draw_text(text, position, angle);
    }

    void canvas::draw_text(
        const string_type&         text,
        const position_type&       position,
        const dimension_unit_type& max_width,
        const double               angle /*= 0.0*/)
    {
        m_p_impl->draw_text(text, position, max_width, angle);
    }

    void canvas::draw_vertical_text(const string_type& text, const position_type& position)
    {
        m_p_impl->draw_vertical_text(text, position);
    }

    void
    canvas::paint_picture(const picture_type& picture, const position_type& position, const dimension_type& dimension)
    {
        m_p_impl->paint_picture(picture, position, dimension);
    }

    void canvas::paint_picture(const picture_type& picture, const position_type& position)
    {
        m_p_impl->paint_picture(picture, position);
    }

    void canvas::paint_icon(const icon_type& icon, const position_type& position)
    {
        m_p_impl->paint_icon(icon, position);
    }

    const canvas::drawing_details_type& canvas::drawing_details() const
    {
        return m_p_impl->drawing_details();
    }

    const canvas::details_type& canvas::details() const
    {
        return m_p_impl->details();
    }

    canvas::details_type& canvas::details()
    {
        return m_p_impl->details();
    }

    canvas::canvas(const drawing_details_type& drawing_details, details_ptr_type p_details)
    : m_p_impl{ std::make_unique<impl>(drawing_details, std::move(p_details)) }
    {}
}
