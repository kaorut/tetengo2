/*! \file
    \brief The definition of tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_CANVAS_H)
#define TETENGO2_GUI_DRAWING_CANVAS_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/drawing.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a canvas.
    */
    class canvas : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The position type.
        using position_type = gui::type_list::position_type;

        //! The dimension type.
        using dimension_type = gui::type_list::dimension_type;

        //! The dimension unit type.
        using dimension_unit_type = dimension_type::unit_type;

        //! The drawing details type.
        using drawing_details_type = detail::base::drawing;

        //! The details type.
        using details_type = typename drawing_details_type::canvas_details_type;

        //! The detail implementation pointer type.
        using details_ptr_type = typename drawing_details_type::canvas_details_ptr_type;

        //! The background type.
        using background_type = background;

        //! The font type.
        using font_type = font;

        //! The picture type.
        using picture_type = picture;

        //! The icon type.
        using icon_type = gui::icon;

        //! The color type.
        using color_type = color;

        //! The line style type.
        enum class line_style_type
        {
            solid, //!< Solid.
            dashed, //!< Dashed.
            dotted, //!< Dotted.
            dot_dashed, //!< Dot-Dashed.
        };


        // constructors and destructor

        /*!
            \brief Destroys the canvas.
        */
        virtual ~canvas();


        // functions

        /*!
            \brief Begins a transaction.

            \param dimension A dimension.
        */
        void begin_transaction(const dimension_type& dimension);

        /*!
            \brief Ends a transaction.
        */
        void end_transaction();

        /*!
            \brief Returns the color.

            \return The color.
        */
        const color_type& get_color() const;

        /*!
            \brief Sets a color.

            \param color A color.
        */
        void set_color(color_type color);

        /*!
            \brief Returns the background.

            \return The background.
        */
        const background_type& get_background() const;

        /*!
            \brief Sets a background.

            \param p_background A unique pointer to a background.
        */
        void set_background(std::unique_ptr<const background_type> p_background);

        /*!
            \brief Returns the line width.

            \return The line_width.
        */
        const dimension_unit_type& line_width() const;

        /*!
            \brief Sets a line width.

            \param line_width A line width.
        */
        void set_line_width(dimension_unit_type line_width);

        /*!
            \brief Returns the line style.

            \return The line_width.
        */
        line_style_type line_style() const;

        /*!
            \brief Sets a line style.

            \tparam S A size type.

            \param line_style A line width.
        */
        void set_line_style(line_style_type line_style);

        /*!
            \brief Returns the font.

            \return The font.
        */
        const font_type& get_font() const;

        /*!
            \brief Sets a font.

            \tparam F A font type.

            \param font A font.
        */
        void set_font(font_type font);

        /*!
            \brief Draws a line.

            \param from A beginning position.
            \param to   An ending position.
        */
        void draw_line(const position_type& from, const position_type& to);

        /*!
            \brief Draws a focus indication.

            \param position  A position of a region.
            \param dimension A dimension of a region.
        */
        void draw_focus_indication(const position_type& position, const dimension_type& dimension);

        /*!
            \brief Draws a rectangle.

            \param position   A position of a region.
            \param dimension  A dimension of a region.
        */
        void draw_rectangle(const position_type& position, const dimension_type& dimension);

        /*!
            \brief Fills a rectangle region.

            \param position   A position of a region.
            \param dimension  A dimension of a region.
        */
        void fill_rectangle(const position_type& position, const dimension_type& dimension);

        /*!
            \brief Draws a polygon.

            \param positions Positions of a region.
        */
        void draw_polygon(const std::vector<position_type>& positions);

        /*!
            \brief Fills a polygon region.

            \param positions Positions of a region.
        */
        void fill_polygon(const std::vector<position_type>& positions);

        /*!
            \brief Calculates the dimension of a text.

            The maximum width is unlimited.

            \param text A text.

            \return The dimension of the text.
        */
        dimension_type calc_text_dimension(const string_type& text) const;

        /*!
            \brief Calculates the dimension of a text.

            \param text      A text.
            \param max_width A maximum width.

            \return The dimension of the text.
        */
        dimension_type calc_text_dimension(const string_type& text, const dimension_unit_type& max_width) const;

        /*!
            \brief Calculates the dimension of a vertical text.

            \param text A vertical text.

            \return The dimension of the vertical text.
        */
        dimension_type calc_vertical_text_dimension(const string_type& text) const;

        /*!
            \brief Draws a text.

            The maximum width is unlimited.

            The text is rotated around the argument position.

            \param text     A text to draw.
            \param position A position where the text is drawn.
            \param angle    A clockwise angle in radians.
        */
        void draw_text(const string_type& text, const position_type& position, double angle = 0.0);

        /*!
            \brief Draws a text.

            The text is rotated around the argument position.

            \param text      A text to draw.
            \param position  A position where the text is drawn.
            \param max_width A maximum width.
            \param angle     A clockwise angle in radians.
        */
        void draw_text(
            const string_type&         text,
            const position_type&       position,
            const dimension_unit_type& max_width,
            double                     angle = 0.0);

        /*!
            \brief Draws a vertical text.

            The text is rotated around the argument position.

            \param text     A text to draw.
            \param position A position where the text is drawn.
        */
        void draw_vertical_text(const string_type& text, const position_type& position);

        /*!
            \brief Paints a picture.

            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.
        */
        void paint_picture(const picture_type& picture, const position_type& position, const dimension_type& dimension);

        /*!
            \brief Paints a picture.

            \param picture  A picture to paint.
            \param position A position where the picture is painted.
        */
        void paint_picture(const picture_type& picture, const position_type& position);

        /*!
            \brief Paints an icon.

            \param icon     An icon to paint.
            \param position A position where the picture is painted.
        */
        void paint_icon(const icon_type& icon, const position_type& position);

        /*!\
            \brief Returns the detail implentation of a drawing.

            \return The detail implementation of a drawing.
        */
        const drawing_details_type& drawing_details() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details();


    protected:
        // constructors and destructor

        /*!
            \brief Creates a canvas.

            The initial foreground color is black.
            The initial background is a solid white color background.
            The initlai font is a dialog font.

            \param drawing_details A detail implementation of a drawing.
            \param p_details       A detail implementation.

            \throw std::invalid_argument When p_details is nullptr.
        */
        canvas(const drawing_details_type& drawing_details, details_ptr_type p_details);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
