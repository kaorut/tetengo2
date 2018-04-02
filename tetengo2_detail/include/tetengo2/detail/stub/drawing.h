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

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>

#include <tetengo2/gui/measure.h>
#include <tetengo2/text.h>


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
            create_canvas([[maybe_unused]] const HandleOrWidgetDetails& handle_or_widget_details)
        {
            return std::make_unique<canvas_details_type>();
        }

        /*!
            \brief Begins a transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \tparam Dimension A dimension type.

            \param canvas    A canvas.
            \param dimension A dimension.

            \throw std::logic_error When another transaction has not ended yet.
        */
        template <typename Dimension>
        static void
            begin_transaction([[maybe_unused]] canvas_details_type& canvas, [[maybe_unused]] const Dimension& dimension)
        {}

        /*!
            \brief Ends the transaction.

            Some platform may not support a transuction. On such platforms, this function do nothing.

            \param canvas A canvas.

            \throw std::logic_error When no transaction has begun.
        */
        static void end_transaction([[maybe_unused]] canvas_details_type& canvas) {}

        /*!
            \brief Creates a solid background.

            \tparam Color A color type.

            \param color A color.

            \return A unique pointer to a solid background.
        */
        template <typename Color>
        static std::unique_ptr<background_details_type> create_solid_background([[maybe_unused]] const Color& color)
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

            \tparam Dimension A dimension type.

            \param dimension A dimension.

            \return A unique pointer to a picture.
        */
        template <typename Dimension>
        static std::unique_ptr<picture_details_type> create_picture(const Dimension& dimension)
        {
            const auto& width = dimension.width();
            const auto& height = dimension.height();
            return std::make_unique<picture_details_type>(
                gui::to_pixels<std::size_t>(width), gui::to_pixels<std::size_t>(height));
        }

        /*!
            \brief Reads a picture.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        inline static std::unique_ptr<picture_details_type> read_picture([
            [maybe_unused]] const boost::filesystem::path& path)
        {
            return std::make_unique<picture_details_type>(123, 456);
        }

        /*!
            \brief Returns the dimension of a picture.

            \tparam Dimension A dimension type.

            \param picture A picture.

            \return The dimension of the picture.
        */
        template <typename Dimension>
        static Dimension picture_dimension(const picture_details_type& picture)
        {
            return { gui::to_unit<typename Dimension::unit_type>(picture.dimension().first),
                     gui::to_unit<typename Dimension::unit_type>(picture.dimension().second) };
        }

        /*!
            \brief Draws a line.

            \tparam Position A position type.
            \tparam Size     A size type.
            \tparam Color    A color type.

            \param canvas A canvas.
            \param from   A beginning position.
            \param to     An ending position.
            \param width  A width.
            \param style  A style.
            \param color  A color.
        */
        template <typename Position, typename Size, typename Color>
        static void draw_line(
            [[maybe_unused]] canvas_details_type& canvas,
            [[maybe_unused]] const Position&      from,
            [[maybe_unused]] const Position&      to,
            [[maybe_unused]] const Size           width,
            [[maybe_unused]] const int            style,
            [[maybe_unused]] const Color&         color)
        {}

        /*!
            \brief Draws a focus indication.

            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param canvas    A canvas.
            \param position  A position of a region.
            \param dimension A dimension of a region.

            \throw std::system_error When the focus indication cannot be drawn.
        */
        template <typename Position, typename Dimension>
        static void draw_focus_indication(
            [[maybe_unused]] canvas_details_type& canvas,
            [[maybe_unused]] const Position&      position,
            [[maybe_unused]] const Dimension&     dimension)
        {}

        /*!
            \brief Draws a rectangle.

            \tparam Position   A position type.
            \tparam Dimension  A dimension type.
            \tparam Size       A size type.
            \tparam Color      A color type.

            \param canvas     A canvas.
            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param width      A width.
            \param style      A style.
            \param color      A color.

            \throw std::system_error When the rectangle cannot be filled.
        */
        template <typename Position, typename Dimension, typename Size, typename Color>
        static void draw_rectangle(
            [[maybe_unused]] canvas_details_type& canvas,
            [[maybe_unused]] const Position&      position,
            [[maybe_unused]] const Dimension&     dimension,
            [[maybe_unused]] const Size           width,
            [[maybe_unused]] const int            style,
            [[maybe_unused]] const Color&         color)
        {}

        /*!
            \brief Fills a rectangle region.

            \tparam Position   A position type.
            \tparam Dimension  A dimension type.
            \tparam Background A background type.

            \param canvas     A canvas.
            \param position   A position of a region.
            \param dimension  A dimension of a region.
            \param background A background.

            \throw std::system_error When the rectangle cannot be filled.
        */
        template <typename Position, typename Dimension, typename Background>
        static void fill_rectangle(
            [[maybe_unused]] canvas_details_type& canvas,
            [[maybe_unused]] const Position&      position,
            [[maybe_unused]] const Dimension&     dimension,
            [[maybe_unused]] const Background&    background)
        {}

        /*!
            \brief Draws a polygon.

            \tparam PositionIterator A position iterator type.
            \tparam Size             A size type.
            \tparam Color            A color type.

            \param canvas         A canvas.
            \param position_first A first position of a region.
            \param position_last  A last position of a region.
            \param width          A width.
            \param style          A style.
            \param color          A color.

            \throw std::system_error When the polygon cannot be filled.
        */
        template <typename PositionIterator, typename Size, typename Color>
        static void draw_polygon(
            [[maybe_unused]] canvas_details_type&   canvas,
            [[maybe_unused]] const PositionIterator position_first,
            [[maybe_unused]] const PositionIterator position_last,
            [[maybe_unused]] const Size             width,
            [[maybe_unused]] const int              style,
            [[maybe_unused]] const Color&           color)
        {}

        /*!
            \brief Fills a polygon region.

            \tparam PositionIterator A position iterator type.
            \tparam Background       A background type.

            \param canvas         A canvas.
            \param position_first A first position of a region.
            \param position_last  A last position of a region.
            \param background     A background.

            \throw std::system_error When the polygon cannot be filled.
        */
        template <typename PositionIterator, typename Background>
        static void fill_polygon(
            [[maybe_unused]] canvas_details_type&   canvas,
            [[maybe_unused]] const PositionIterator position_first,
            [[maybe_unused]] const PositionIterator position_last,
            [[maybe_unused]] const Background&      background)
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

            \tparam Dimension A dimension type.
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
        template <typename Dimension, typename Font, typename String, typename Encoder>
        static Dimension calc_text_dimension(
            [[maybe_unused]] const canvas_details_type&           canvas,
            [[maybe_unused]] const Font&                          font,
            [[maybe_unused]] const String&                        text,
            [[maybe_unused]] const Encoder&                       encoder,
            [[maybe_unused]] const typename Dimension::unit_type& max_width)
        {
            using dimension_unit_type = typename Dimension::unit_type;
            return max_width == dimension_unit_type{} || max_width >= dimension_unit_type{ 123 } ?
                       Dimension{ dimension_unit_type{ 123 }, dimension_unit_type{ 456 } } :
                       Dimension{ dimension_unit_type{ 46 }, dimension_unit_type{ 890 } };
        }

        /*!
            \brief Calculates the dimension of a vertical text.

            \tparam Dimension A dimension type.
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
        template <typename Dimension, typename Font, typename String, typename Encoder>
        static Dimension calc_vertical_text_dimension(
            [[maybe_unused]] const canvas_details_type& canvas,
            [[maybe_unused]] const Font&                font,
            [[maybe_unused]] const String&              text,
            [[maybe_unused]] const Encoder&             encoder)
        {
            using dimension_unit_type = typename Dimension::unit_type;
            return Dimension{ dimension_unit_type{ 456 }, dimension_unit_type{ 123 } };
        }

        /*!
            \brief Draws a text.

            \tparam Font          A font type.
            \tparam String        A string type.
            \tparam Encoder       An encoder type.
            \tparam Position      A position type.
            \tparam DimensionUnit A dimension unit type.
            \tparam Color         A color type.

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
        template <
            typename Font,
            typename String,
            typename Encoder,
            typename Position,
            typename DimensionUnit,
            typename Color>
        static void draw_text(
            [[maybe_unused]] canvas_details_type& canvas,
            [[maybe_unused]] const Font&          font,
            [[maybe_unused]] const String&        text,
            [[maybe_unused]] const Encoder&       encoder,
            [[maybe_unused]] const Position&      position,
            [[maybe_unused]] const DimensionUnit& max_width,
            [[maybe_unused]] const Color&         color,
            [[maybe_unused]] const double         angle)
        {}

        /*!
            \brief Draws a vertical text.

            \tparam Font      A font type.
            \tparam String    A string type.
            \tparam Encoder   An encoder type.
            \tparam Position  A position type.
            \tparam Dimension A dimension type.
            \tparam Color     A color type.

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
            typename Position,
            typename Dimension,
            typename Color>
        static void draw_vertical_text(
            [[maybe_unused]] canvas_details_type& canvas,
            [[maybe_unused]] const Font&          font,
            [[maybe_unused]] const String&        text,
            [[maybe_unused]] const Encoder&       encoder,
            [[maybe_unused]] const Position&      position,
            [[maybe_unused]] const Color&         color)
        {}

        /*!
            \brief Paints a picture.

            \tparam Picture   A picture type.
            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param canvas    A canvas.
            \param picture   A picture to paint.
            \param position  A position where the picture is painted.
            \param dimension A dimension in which the picture is painted.

            \throw std::system_error When the picture cannot be painted.
        */
        template <typename Picture, typename Position, typename Dimension>
        static void paint_picture(
            [[maybe_unused]] canvas_details_type& canvas,
            [[maybe_unused]] const Picture&       picture,
            [[maybe_unused]] const Position&      position,
            [[maybe_unused]] const Dimension&     dimension)
        {}

        /*!
            \brief Paints an icon.

            \tparam Icon     A icon type.
            \tparam Position A position type.

            \param canvas   A canvas.
            \param icon     An icon to paint.
            \param position A position where the picture is painted.

            \throw std::system_error When the icon cannot be painted.
        */
        template <typename Icon, typename Position>
        static void paint_icon(
            [[maybe_unused]] canvas_details_type& canvas,
            [[maybe_unused]] const Icon&          icon,
            [[maybe_unused]] const Position&      position)
        {}


    private:
        // forbidden operations

        drawing() = delete;
    };
}


#endif
