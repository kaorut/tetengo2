/*! \file
    \brief The definition of tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_CANVAS_H)
#define TETENGO2_GUI_DRAWING_CANVAS_H

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/measure.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a canvas.

        \tparam Traits         A traits type.
        \tparam DrawingDetails A detail implementation type of a drawing.
        \tparam IconDetails    An icon details type.
    */
    template <typename Traits, typename DrawingDetails, typename IconDetails>
    class canvas : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The size type.
        using size_type = typename traits_type::size_type;

        //! The unit size type.
        using unit_size_type = typename traits_type::unit_size_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The position type.
        using position_type = typename traits_type::position_type;

        //! The dimension type.
        using dimension_type = typename traits_type::dimension_type;

        //! The width type.
        using width_type = typename gui::dimension<dimension_type>::width_type;

        //! The encoder type.
        using encoder_type = typename traits_type::encoder_type;

        //! The drawing details type.
        using drawing_details_type = DrawingDetails;

        //! The details type.
        using details_type = typename drawing_details_type::canvas_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename drawing_details_type::canvas_details_ptr_type;

        //! The background type.
        using background_type = background<drawing_details_type>;

        //! The solid background type.
        using solid_background_type = solid_background<drawing_details_type>;

        //! The font type.
        using font_type = font<string_type, size_type, drawing_details_type>;

        //! The picture type.
        using picture_type = picture<dimension_type, drawing_details_type>;

        //! The icon details type.
        using icon_details_type = IconDetails;

        //! The icon type.
        using icon_type = gui::icon<dimension_type, icon_details_type>;

        //! The color type.
        using color_type = color;

        //! The line style type.
        enum class line_style_type
        {
            solid,      //!< Solid.
            dashed,     //!< Dashed.
            dotted,     //!< Dotted.
            dot_dashed, //!< Dot-Dashed.
        };


        // constructors and destructor

        /*!
            \brief Destroys the canvas.
        */
        virtual ~canvas()
        = default;


        // functions
        
        /*!
            \brief Begins a transaction.

            \param dimension A dimension.
        */
        void begin_transaction(const dimension_type& dimension)
        {
            drawing_details_type::begin_transaction(*m_p_details, dimension);
        }
            
        /*!
            \brief Ends a transaction.
        */
        void end_transaction()
        {
            drawing_details_type::end_transaction(*m_p_details);
        }
            
        /*!
            \brief Returns the color.

            \return The color.
        */
        const color_type& get_color()
        const
        {
            return m_color;
        }

        /*!
            \brief Sets a color.

            \param color A color.
        */
        void set_color(color_type color)
        {
            m_color = std::move(color);
        }

        /*!
            \brief Returns the background.

            \return The background.
        */
        const background_type& get_background()
        const
        {
            assert(m_p_background);
            return *m_p_background;
        }

        /*!
            \brief Sets a background.

            \param p_background A unique pointer to a background.
        */
        void set_background(std::unique_ptr<const background_type> p_background)
        {
            m_p_background = std::move(p_background);
        }

        /*!
            \brief Returns the line width.

            \return The line_width.
        */
        const unit_size_type& line_width()
        const
        {
            return m_line_width;
        }

        /*!
            \brief Sets a line width.

            \param line_width A line width.
        */
        void set_line_width(unit_size_type line_width)
        {
            m_line_width = std::move(line_width);
        }

        /*!
            \brief Returns the line style.

            \return The line_width.
        */
        line_style_type line_style()
        const
        {
            return m_line_style;
        }

        /*!
            \brief Sets a line style.

            \tparam S A size type.

            \param line_style A line width.
        */
        void set_line_style(const line_style_type line_style)
        {
            m_line_style = line_style;
        }

        /*!
            \brief Returns the font.

            \return The font.
        */
        const font_type& get_font()
        const
        {
            return m_font;
        }

        /*!
            \brief Sets a font.

            \tparam F A font type.

            \param font A font.
        */
        void set_font(font_type font)
        {
            m_font = std::move(font);
        }

        /*!
            \brief Draws a line.

            \param from A beginning position.
            \param to   An ending position.
        */
        void draw_line(const position_type& from, const position_type& to)
        {
            drawing_details_type::draw_line(
                *m_p_details, from, to, m_line_width, static_cast<int>(m_line_style), m_color
            );
        }

        /*!
            \brief Draws a focus indication.

            \param position  A position of a region.
            \param dimension A dimension of a region.
        */
        void draw_focus_indication(const position_type& position, const dimension_type& dimension)
        {
            drawing_details_type::draw_focus_indication(*m_p_details, position, dimension);
        }

        /*!
            \brief Draws a rectangle.

            \param position   A position of a region.
            \param dimension  A dimension of a region.
        */
        void draw_rectangle(const position_type& position, const dimension_type& dimension)
        {
            assert(m_p_background);
            drawing_details_type::draw_rectangle(
                *m_p_details, position, dimension, m_line_width, static_cast<int>(m_line_style), m_color
            );
        }

        /*!
            \brief Fills a rectangle region.

            \param position   A position of a region.
            \param dimension  A dimension of a region.
        */
        void fill_rectangle(const position_type& position, const dimension_type& dimension)
        {
            assert(m_p_background);
            drawing_details_type::fill_rectangle(*m_p_details, position, dimension, *m_p_background);
        }

        /*!
            \brief Draws a polygon.

            \tparam PositionIterator A position iterator type.

            \param position_first A first position.
            \param position_last  A last position.
        */
        template <typename PositionIterator>
        void draw_polygon(const PositionIterator position_first, const PositionIterator position_last)
        {
            drawing_details_type::draw_polygon(
                *m_p_details, position_first, position_last, m_line_width, static_cast<int>(m_line_style), m_color
            );
        }

        /*!
            \brief Fills a polygon region.

            \tparam PositionIterator A position iterator type.

            \param position_first A first position of a region.
            \param position_last  A last position of a region.
        */
        template <typename PositionIterator>
        void fill_polygon(const PositionIterator position_first, const PositionIterator position_last)
        {
            assert(m_p_background);
            drawing_details_type::fill_polygon(*m_p_details, position_first, position_last, *m_p_background);
        }

        /*!
            \brief Calculates the dimension of a text.

            The maximum width is unlimited.

            \param text A text.

            \return The dimension of the text.
        */
        dimension_type calc_text_dimension(const string_type& text)
        const
        {
            return calc_text_dimension(text, width_type{ 0 });
        }

        /*!
            \brief Calculates the dimension of a text.

            \param text      A text.
            \param max_width A maximum width.

            \return The dimension of the text.
        */
        dimension_type calc_text_dimension(const string_type& text, const width_type& max_width)
        const
        {
            return
                drawing_details_type::template calc_text_dimension<dimension_type>(
                    *m_p_details, m_font, text, encoder(), max_width
                );
        }

        /*!
            \brief Calculates the dimension of a vertical text.

            \param text A vertical text.

            \return The dimension of the vertical text.
        */
        dimension_type calc_vertical_text_dimension(const string_type& text)
        const
        {
            return
                drawing_details_type::template calc_vertical_text_dimension<dimension_type>(
                    *m_p_details, m_font, text, encoder()
                );
        }

        /*!
            \brief Draws a text.

            The maximum width is unlimited.

            The text is rotated around the argument position.

            \param text     A text to draw.
            \param position A position where the text is drawn.
            \param angle    A clockwise angle in radians.
        */
        void draw_text(const string_type& text, const position_type& position, const double angle = 0.0)
        {
            draw_text(text, position, width_type{ 0 }, angle);
        }

        /*!
            \brief Draws a text.

            The text is rotated around the argument position.

            \param text      A text to draw.
            \param position  A position where the text is drawn.
            \param max_width A maximum width.
            \param angle     A clockwise angle in radians.
        */
        void draw_text(
            const string_type&   text,
            const position_type& position,
            const width_type&    max_width,
            const double         angle = 0.0
        )
        {
            drawing_details_type::draw_text(
                *m_p_details, m_font, text, encoder(), position, max_width, m_color, angle
            );
        }

        /*!
            \brief Draws a vertical text.

            The text is rotated around the argument position.

            \param text     A text to draw.
            \param position A position where the text is drawn.
        */
        void draw_vertical_text(const string_type& text, const position_type& position)
        {
            drawing_details_type::template draw_vertical_text<
                font_type, string_type, encoder_type, position_type, dimension_type
            >(*m_p_details, m_font, text, encoder(), position, m_color);
        }

        /*!
            \brief Paints a picture.

            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.
        */
        void paint_picture(
            const picture_type&   picture,
            const position_type&  position,
            const dimension_type& dimension
        )
        {
            drawing_details_type::paint_picture(*m_p_details, picture, position, dimension);
        }

        /*!
            \brief Paints a picture.

            \param picture  A picture to paint.
            \param position A position where the picture is painted.
        */
        void paint_picture(const picture_type& picture, const position_type& position)
        {
            paint_picture(picture, position, picture.dimension());
        }

        /*!
            \brief Paints an icon.

            \param icon     An icon to paint.
            \param position A position where the picture is painted.
        */
        void paint_icon(const icon_type& icon, const position_type& position)
        {
            drawing_details_type::paint_icon(*m_p_details, icon, position);
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
        {
            assert(m_p_details);
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            assert(m_p_details);
            return *m_p_details;
        }


    protected:
        // constructors and destructor

        /*!
            \brief Creates a canvas.

            The initial foreground color is black.
            The initial background is a solid white color background.
            The initlai font is a dialog font.

            \param p_details A detail implementation.

            \throw std::invalid_argument When p_details is nullptr.
        */
        explicit canvas(details_ptr_type p_details)
        :
        m_p_details(std::move(p_details)),
        m_color(0, 0, 0, 255),
        m_p_background(stdalt::make_unique<const solid_background_type>(color_type{ 255, 255, 255, 255 })),
        m_line_width(1),
        m_line_style(line_style_type::solid),
        m_font(font_type::dialog_font())
        {
            if (!m_p_details)
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "The detail implementation is nullptr." }));
        }


    private:
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{
                typename encoder_type::internal_encoding_type{}, typename encoder_type::external_encoding_type{}
            };
            return singleton;
        }


        // variables

        const details_ptr_type m_p_details;

        color_type m_color;

        std::unique_ptr<const background_type> m_p_background;

        unit_size_type m_line_width;

        line_style_type m_line_style;

        font_type m_font;


    };


}}}


#endif
