/*! \file
    \brief The definition of tetengo2::detail::stub::drawing.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_DRAWING_H)
#define TETENGO2_DETAIL_STUB_DRAWING_H

#include <cassert>
//#include <cstddef>
//#include <memory>
#include <stdexcept>
#include <system_error>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.text.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing : private boost::noncopyable
    {
    public:
        // types

        //! The system color index type.
        enum system_color_index_type
        {
            system_color_index_dialog_background, //!< Dialog background.
        };

        //! The background details type.
        struct background_details_type {};

        //! The background details pointer type.
        typedef std::unique_ptr<background_details_type> background_details_ptr_type;

        //! The picture details type.
        struct picture_details_type
        {
            // constructors and destructor

            /*!
                \brief Creates a picture details type.

                \param width A width.
                \param height A height.
            */
            picture_details_type(const std::size_t width, const std::size_t height)
            :
            m_dimension(width, height)
            {}

            /*!
                \brief Returns the dimension.

                \return The dimension.
            */
            const std::pair<std::size_t, std::size_t>& dimension()
            const
            {
                return m_dimension;
            }


        private:
            // variables

            std::pair<std::size_t, std::size_t> m_dimension;


        };

        //! The picture details pointer type.
        typedef std::unique_ptr<picture_details_type> picture_details_ptr_type;

        //! The canvas details type.
        struct canvas_details_type {};

        //! The canvas details pointer type.
        typedef std::unique_ptr<canvas_details_type> canvas_details_ptr_type;


        // static functions

        /*!
            \brief Returns the system color.

            \tparam Color A color type.

            \param index An index;

            \return The system color.
        */
        template <typename Color>
        static Color system_color(const system_color_index_type index)
        {
            switch (index)
            {
            case system_color_index_dialog_background:
                return Color(192, 192, 192);
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid system color index."));
            }
        }

        /*!
            \brief Creates a canvas.

            \tparam HandleOrWidgetDetails A handle type or a widget details type.

            \param handle_or_widget_details A handle or a widget details.

            \return A unique pointer to a canvas.
        */
        template <typename HandleOrWidgetDetails>
        static std::unique_ptr<canvas_details_type> create_canvas(
            const HandleOrWidgetDetails& handle_or_widget_details
        )
        {
            return make_unique<canvas_details_type>();
        }

        /*!
            \brief Creates a solid background.

            \tparam Color A color type.

            \param color A color.

            \return A unique pointer to a solid background.
        */
        template <typename Color>
        static std::unique_ptr<background_details_type> create_solid_background(const Color& color)
        {
            return make_unique<background_details_type>();
        }

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        static std::unique_ptr<background_details_type> create_transparent_background()
        {
            return std::unique_ptr<background_details_type>();
        }

        /*!
            \brief Creates a picture.

            \tparam Dimension A dimension type.
            \tparam Canvas    A canvas type.

            \param dimension A dimension.
            \param canvas    A canvas.

            \return A unique pointer to a picture.
        */
        template <typename Dimension, typename Canvas>
        static std::unique_ptr<picture_details_type> create_picture(const Dimension& dimension, const Canvas& canvas)
        {
            const std::size_t width = gui::dimension<Dimension>::width(dimension);
            const std::size_t height = gui::dimension<Dimension>::height(dimension);
            return make_unique<picture_details_type>(width, height);
        }

        /*!
            \brief Reads a picture.

            \tparam Path A path type.

            \param path A path.

            \return A unique pointer to a picture.

            \throw std::system_error When the picture cannot be read.
        */
        template <typename Path>
        static std::unique_ptr<picture_details_type> read_picture(const Path& path)
        {
            return make_unique<picture_details_type>(123, 456);
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
            return
                Dimension(
                    typename Dimension::first_type(picture.dimension().first),
                    typename Dimension::second_type(picture.dimension().second)
                );
        }

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
            canvas_details_type& canvas,
            const Position&      position,
            const Dimension&     dimension
        )
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
            canvas_details_type& canvas,
            const Position&      position,
            const Dimension&     dimension,
            const Background&    background
        )
        {}

        /*!
            \brief Makes a dialog font.

            \tparam Font A font type.

            \return A dialog font.
        */
        template <typename Font>
        static Font make_dialog_font()
        {
            return Font(TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false);
        }

        /*!
            \brief Calculates the dimension of a text.

            \tparam Dimension A dimension type.
            \tparam Font      A font type.
            \tparam String    A string type.
            \tparam Encoder   An encoder type.

            \param canvas  A canvas.
            \param font    A font.
            \param text    A text.
            \param encoder An encoder.

            \return The dimension of the text.

            \throw std::system_error When the dimention of a text cannot be calculated.
        */
        template <typename Dimension, typename Font, typename String, typename Encoder>
        static Dimension calc_text_dimension(
            const canvas_details_type& canvas,
            const Font&                font,
            const String&              text,
            const Encoder&             encoder
        )
        {
            typedef typename gui::dimension<Dimension>::width_type width_type;
            typedef typename gui::dimension<Dimension>::height_type height_type;
            return Dimension(width_type(123), height_type(456));
        }

        /*!
            \brief Draws a text.

            \tparam Font     A font type.
            \tparam String   A string type.
            \tparam Encoder  An encoder type.
            \tparam Position A position type.

            \param canvas   A canvas.
            \param font     A font.
            \param text     A text to draw.
            \param encoder  An encoder.
            \param position A position where the text is drawn.

            \throw std::system_error When the text cannot be drawn.
        */
        template <typename Font, typename String, typename Encoder, typename Position>
        static void draw_text(
            canvas_details_type& canvas,
            const Font&          font,
            const String&        text,
            const Encoder&       encoder,
            const Position&      position
        )
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
            canvas_details_type& canvas,
            const Picture&       picture,
            const Position&      position,
            const Dimension&     dimension
        )
        {}


    private:
        // forbidden operations

        drawing();


    };


}}}


#endif
