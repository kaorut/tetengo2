/*! \file
    \brief The definition of tetengo2::detail::stub::drawing.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_DRAWING_H)
#define TETENGO2_DETAIL_STUB_DRAWING_H

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/operators.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/type_list.h>

namespace tetengo2::gui {
    class icon;
}


namespace tetengo2::detail::stub {
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
        };

        //! The background details pointer type.
        using background_details_ptr_type = std::unique_ptr<background_details_type>;

        //! The picture details type.
        struct picture_details_type
        {
            // constructors and destructor

            /*!
                \brief Creates a picture details type.

                \param width A width.
                \param height A height.
            */
            picture_details_type(const std::size_t width, const std::size_t height) : m_dimension{ width, height } {}

            /*!
                \brief Returns the dimension.

                \return The dimension.
            */
            const std::pair<std::size_t, std::size_t>& dimension() const
            {
                return m_dimension;
            }


        private:
            // variables

            std::pair<std::size_t, std::size_t> m_dimension;
        };

        //! The picture details pointer type.
        using picture_details_ptr_type = std::unique_ptr<picture_details_type>;

        //! The canvas details type.
        struct canvas_details_type
        {
        };

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
        static std::unique_ptr<canvas_details_type>
        create_canvas(TETENGO2_STDALT_MAYBE_UNUSED const HandleOrWidgetDetails& handle_or_widget_details)
        {
            return std::make_unique<canvas_details_type>();
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
        static std::unique_ptr<background_details_type>
        create_solid_background(TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::gui::drawing::color& color)
        {
            return std::make_unique<background_details_type>();
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
        static std::unique_ptr<picture_details_type> create_picture(const gui::type_list::dimension_type& dimension)
        {
            const auto& width = dimension.width();
            const auto& height = dimension.height();
            return std::make_unique<picture_details_type>(width.to_pixels(), height.to_pixels());
        }

        /*!
            \brief Reads a picture.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        inline static std::unique_ptr<picture_details_type>
        read_picture(TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::stdalt::filesystem::path& path)
        {
            return std::make_unique<picture_details_type>(123, 456);
        }

        /*!
            \brief Returns the dimension of a picture.


            \param picture A picture.

            \return The dimension of the picture.
        */
        static gui::type_list::dimension_type picture_dimension(const picture_details_type& picture)
        {
            return { gui::type_list::dimension_unit_type::from_pixels(picture.dimension().first),
                     gui::type_list::dimension_unit_type::from_pixels(picture.dimension().second) };
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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& from,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& to,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED const int                                  style,
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::gui::drawing::color& color)
        {}

        /*!
            \brief Draws a focus indication.


            \param canvas    A canvas.
            \param position  A position of a region.
            \param dimension A dimension of a region.

            \throw std::system_error When the focus indication cannot be drawn.
        */
        static void draw_focus_indication(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension)
        {}

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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED const int                                  style,
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::gui::drawing::color& color)
        {}

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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension,
            TETENGO2_STDALT_MAYBE_UNUSED const Background& background)
        {}

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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const std::vector<gui::type_list::position_type>& positions,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& width,
            TETENGO2_STDALT_MAYBE_UNUSED const int                                  style,
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::gui::drawing::color& color)
        {}

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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const std::vector<gui::type_list::position_type>& positions,
            TETENGO2_STDALT_MAYBE_UNUSED const Background& background)
        {}

        /*!
            \brief Makes a dialog font.

            \tparam Font A font type.

            \return A dialog font.
        */
        template <typename Font>
        static Font make_dialog_font()
        {
            return { typename Font::string_type{ TETENGO2_TEXT("TetengoFont") }, 12, false, false, false, false };
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
            TETENGO2_STDALT_MAYBE_UNUSED const canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const Font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& max_width)
        {
            using dimension_unit_type = gui::type_list::dimension_unit_type;
            return max_width == dimension_unit_type{} || max_width >= dimension_unit_type{ 123 } ?
                       gui::type_list::dimension_type{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } } :
                       gui::type_list::dimension_type{ dimension_unit_type{ 46 }, dimension_unit_type{ 890 } };
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
            TETENGO2_STDALT_MAYBE_UNUSED const canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const Font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text)
        {
            using dimension_unit_type = gui::type_list::dimension_unit_type;
            return gui::type_list::dimension_type{ dimension_unit_type{ 456 }, dimension_unit_type{ 123 } };
        }

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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const Font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_unit_type& max_width,
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::gui::drawing::color& color,
            TETENGO2_STDALT_MAYBE_UNUSED const double                         angle)
        {}

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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const Font& font,
            TETENGO2_STDALT_MAYBE_UNUSED const type_list::string_type& text,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::gui::drawing::color& color)
        {}

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
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const Picture& picture,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension)
        {}

        /*!
            \brief Paints an icon.

            \param canvas   A canvas.
            \param icon     An icon to paint.
            \param position A position where the picture is painted.

            \throw std::system_error When the icon cannot be painted.
        */
        static void paint_icon(
            TETENGO2_STDALT_MAYBE_UNUSED canvas_details_type& canvas,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::icon& icon,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position)
        {}


    private:
        // forbidden operations

        drawing() = delete;
    };
}


#endif
