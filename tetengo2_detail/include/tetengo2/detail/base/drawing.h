/*! \file
    \brief The definition of tetengo2::detail::base::drawing.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_DRAWING_H)
#define TETENGO2_DETAIL_STUB_DRAWING_H

#include <cstdint>
#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>

namespace tetengo2::gui {
    class icon;

    namespace drawing {
        class background;
        class color;
        class font;
        class picture;
    }
}


namespace tetengo2::detail::base {
    class widget;


    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing : private boost::noncopyable
    {
    public:
        // types

        //! The background details type.
        struct background_details_type
        {
            /*!
                \brief Destroys the detail implementation.
            */
            virtual ~background_details_type();
        };

        //! The background details pointer type.
        using background_details_ptr_type = std::unique_ptr<background_details_type>;

        //! The picture details type.
        struct picture_details_type
        {
            /*!
                \brief Destroys the detail implementation.
            */
            virtual ~picture_details_type();
        };

        //! The picture details pointer type.
        using picture_details_ptr_type = std::unique_ptr<picture_details_type>;

        //! The canvas details type.
        struct canvas_details_type
        {
            /*!
                \brief Destroys the detail implementation.
            */
            virtual ~canvas_details_type();
        };

        //! The canvas details pointer type.
        using canvas_details_ptr_type = std::unique_ptr<canvas_details_type>;


        // constructors and destructors

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~drawing();


        // functions

        /*!
            \brief Creates a canvas.

            \param widget_details A detail implementation of a widget.

            \return A unique pointer to a canvas.
        */
        std::unique_ptr<canvas_details_type> create_canvas(const widget& widget_details) const;

        /*!
            \brief Creates a canvas.

            \param canvas_handle A canvas handle.

            \return A unique pointer to a canvas.
        */
        std::unique_ptr<canvas_details_type> create_canvas(std::intptr_t canvas_handle) const;

        /*!
            \brief Begins a transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \param canvas    A canvas.
            \param dimension A dimension.

            \throw std::logic_error When another transaction has not ended yet.
        */
        void begin_transaction(canvas_details_type& canvas, const gui::type_list::dimension_type& dimension) const;

        /*!
            \brief Ends the transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \param canvas A canvas.

            \throw std::logic_error When no transaction has begun.
        */
        void end_transaction(canvas_details_type& canvas) const;

        /*!
            \brief Creates a solid background.

            \param color A color.

            \return A unique pointer to a solid background.
        */
        std::unique_ptr<background_details_type> create_solid_background(const gui::drawing::color& color) const;

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        std::unique_ptr<background_details_type> create_transparent_background() const;

        /*!
            \brief Creates a picture.

            \param dimension A dimension.

            \return A unique pointer to a picture.
        */
        std::unique_ptr<picture_details_type> create_picture(const gui::type_list::dimension_type& dimension) const;

        /*!
            \brief Reads a picture.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        std::unique_ptr<picture_details_type> read_picture(const tetengo2::stdalt::filesystem::path& path) const;

        /*!
            \brief Returns the dimension of a picture.

            \param picture A picture.

            \return The dimension of the picture.
        */
        gui::type_list::dimension_type picture_dimension(const picture_details_type& picture) const;

        /*!
            \brief Draws a line.

            \param canvas A canvas.
            \param from   A beginning position.
            \param to     An ending position.
            \param width  A width.
            \param style  A style.
            \param color  A color.
        */
        void draw_line(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       from,
            const gui::type_list::position_type&       to,
            const gui::type_list::dimension_unit_type& width,
            int                                        style,
            const gui::drawing::color&                 color) const;

        /*!
            \brief Draws a focus indication.

            \param canvas    A canvas.
            \param position  A position of a region.
            \param dimension A dimension of a region.

            \throw std::system_error When the focus indication cannot be drawn.
        */
        void draw_focus_indication(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const;

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
        void draw_rectangle(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_type&      dimension,
            const gui::type_list::dimension_unit_type& width,
            int                                        style,
            const gui::drawing::color&                 color) const;

        /*!
            \brief Fills a rectangle region.

            \param canvas     A canvas.
            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param background A background.

            \throw std::system_error When the rectangle cannot be filled.
        */
        void fill_rectangle(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const gui::drawing::background&       background) const;

        /*!
            \brief Draws a polygon.

            \param canvas    A canvas.
            \param positions A positions of a region.
            \param width     A width.
            \param style     A style.
            \param color     A color.

            \throw std::system_error When the polygon cannot be filled.
        */
        void draw_polygon(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::type_list::dimension_unit_type&        width,
            int                                               style,
            const gui::drawing::color&                        color) const;

        /*!
            \brief Fills a polygon region.

            \param canvas     A canvas.
            \param positions  A positions of a region.
            \param background A background.

            \throw std::system_error When the polygon cannot be filled.
        */
        void fill_polygon(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::drawing::background&                   background) const;

        /*!
            \brief Makes a dialog font.

            \tparam Font A font type.

            \return A dialog font.
        */
        gui::drawing::font make_dialog_font() const;

        /*!
            \brief Calculates the dimension of a text.

            \param canvas    A canvas.
            \param font      A font.
            \param text      A text.
            \param max_width A maximum width. When 0 is specified, the width is infinite.

            \return The dimension of the text.

            \throw std::system_error When the dimention of a text cannot be calculated.
        */
        gui::type_list::dimension_type calc_text_dimension(
            const canvas_details_type&                 canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::dimension_unit_type& max_width) const;

        /*!
            \brief Calculates the dimension of a vertical text.

            \param canvas A canvas.
            \param font   A font.
            \param text   A text.

            \return The dimension of the vertical text.

            \throw std::system_error When the dimention of a vertical text cannot be calculated.
        */
        gui::type_list::dimension_type calc_vertical_text_dimension(
            const canvas_details_type&    canvas,
            const gui::drawing::font&     font,
            const type_list::string_type& text) const;

        /*!
            \brief Draws a text.

            \param canvas    A canvas.
            \param font      A font.
            \param text      A text to draw.
            \param position  A position where the text is drawn.
            \param max_width A maximum width. When 0 is specified, the width is infinite.
            \param color     A color.
            \param angle     A clockwise angle in radians.

            \throw std::system_error When the text cannot be drawn.
        */
        void draw_text(
            canvas_details_type&                       canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_unit_type& max_width,
            const gui::drawing::color&                 color,
            double                                     angle) const;

        /*!
            \brief Draws a vertical text.

            \param canvas   A canvas.
            \param font     A font.
            \param text     A text to draw.
            \param position A position where the text is drawn.
            \param color    A color.

            \throw std::system_error When the text cannot be drawn.
        */
        void draw_vertical_text(
            canvas_details_type&                 canvas,
            const gui::drawing::font&            font,
            const type_list::string_type&        text,
            const gui::type_list::position_type& position,
            const gui::drawing::color&           color) const;

        /*!
            \brief Paints a picture.

            \param canvas    A canvas.
            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.

            \throw std::system_error When the picture cannot be painted.
        */
        void paint_picture(
            canvas_details_type&                  canvas,
            const gui::drawing::picture&          picture,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const;

        /*!
            \brief Paints an icon.

            \param canvas   A canvas.
            \param icon     An icon to paint.
            \param position A position where the picture is painted.

            \throw std::system_error When the icon cannot be painted.
        */
        void paint_icon(
            canvas_details_type&                 canvas,
            const gui::icon&                     icon,
            const gui::type_list::position_type& position) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        drawing();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual std::unique_ptr<canvas_details_type> create_canvas_impl(const widget& widget_details) const = 0;

        virtual std::unique_ptr<canvas_details_type> create_canvas_impl(std::intptr_t canvas_handle) const = 0;

        virtual void
        begin_transaction_impl(canvas_details_type& canvas, const gui::type_list::dimension_type& dimension) const = 0;

        virtual void end_transaction_impl(canvas_details_type& canvas) const = 0;

        virtual std::unique_ptr<background_details_type>
        create_solid_background_impl(const gui::drawing::color& color) const = 0;

        virtual std::unique_ptr<background_details_type> create_transparent_background_impl() const = 0;

        virtual std::unique_ptr<picture_details_type>
        create_picture_impl(const gui::type_list::dimension_type& dimension) const = 0;

        virtual std::unique_ptr<picture_details_type>
        read_picture_impl(const tetengo2::stdalt::filesystem::path& path) const = 0;

        virtual gui::type_list::dimension_type picture_dimension_impl(const picture_details_type& picture) const = 0;

        virtual void draw_line_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       from,
            const gui::type_list::position_type&       to,
            const gui::type_list::dimension_unit_type& width,
            int                                        style,
            const gui::drawing::color&                 color) const = 0;

        virtual void draw_focus_indication_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const = 0;

        virtual void draw_rectangle_impl(
            canvas_details_type&                       canvas,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_type&      dimension,
            const gui::type_list::dimension_unit_type& width,
            int                                        style,
            const gui::drawing::color&                 color) const = 0;

        virtual void fill_rectangle_impl(
            canvas_details_type&                  canvas,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const gui::drawing::background&       background) const = 0;

        virtual void draw_polygon_impl(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::type_list::dimension_unit_type&        width,
            int                                               style,
            const gui::drawing::color&                        color) const = 0;

        virtual void fill_polygon_impl(
            canvas_details_type&                              canvas,
            const std::vector<gui::type_list::position_type>& positions,
            const gui::drawing::background&                   background) const = 0;

        virtual gui::drawing::font make_dialog_font_impl() const = 0;

        virtual gui::type_list::dimension_type calc_text_dimension_impl(
            const canvas_details_type&                 canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::dimension_unit_type& max_width) const = 0;

        virtual gui::type_list::dimension_type calc_vertical_text_dimension_impl(
            const canvas_details_type&    canvas,
            const gui::drawing::font&     font,
            const type_list::string_type& text) const = 0;

        virtual void draw_text_impl(
            canvas_details_type&                       canvas,
            const gui::drawing::font&                  font,
            const type_list::string_type&              text,
            const gui::type_list::position_type&       position,
            const gui::type_list::dimension_unit_type& max_width,
            const gui::drawing::color&                 color,
            double                                     angle) const = 0;

        virtual void draw_vertical_text_impl(
            canvas_details_type&                 canvas,
            const gui::drawing::font&            font,
            const type_list::string_type&        text,
            const gui::type_list::position_type& position,
            const gui::drawing::color&           color) const = 0;

        virtual void paint_picture_impl(
            canvas_details_type&                  canvas,
            const gui::drawing::picture&          picture,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const = 0;

        virtual void paint_icon_impl(
            canvas_details_type&                 canvas,
            const gui::icon&                     icon,
            const gui::type_list::position_type& position) const = 0;
    };
}


#endif
