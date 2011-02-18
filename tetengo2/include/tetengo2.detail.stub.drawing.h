/*! \file
    \brief The definition of tetengo2::detail::stub::drawing.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_DRAWING_H)
#define TETENGO2_DETAIL_STUB_DRAWING_H

//#include <cstddef>
#include <stdexcept>
//#include <utility>
#include <vector>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing
    {
    public:
        // types

        //! The background details type.
        struct background_details_type {};

        //! The picture details type.
        struct picture_details_type
        {
            // constructors and destructor

            /*!
                \brief Creates a picture details type.

                \param width A width.
                \param height A height.
            */
            picture_details_type(
                const std::size_t width,
                const std::size_t height
            )
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

        //! The canvas details type.
        struct canvas_details_type {};


        // static functions

        /*!
            \brief Creates a solid background.

            \tparam Color A color type.

            \param color A color.

            \return A unique pointer to a solid background.
        */
        template <typename Color>
        static cpp0x::unique_ptr<background_details_type>::type
        create_solid_background(const Color& color)
        {
            return cpp0x::unique_ptr<background_details_type>::type(
                new background_details_type()
            );
        }

        /*!
            \brief Creates a transparent background.

            \return A unique pointer to a transparent background.
        */
        static cpp0x::unique_ptr<background_details_type>::type
        create_transparent_background()
        {
            return cpp0x::unique_ptr<background_details_type>::type();
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
        static cpp0x::unique_ptr<picture_details_type>::type
        create_picture(const Dimension& dimension, const Canvas& canvas)
        {
            const std::size_t width =
                gui::dimension<Dimension>::width(dimension);
            const std::size_t height =
                gui::dimension<Dimension>::height(dimension);
            return cpp0x::unique_ptr<picture_details_type>::type(
                new picture_details_type(width, height)
            );
        }

        /*!
            \brief Reads a picture.

            \tparam Path    A path type.

            \param path A path.

            \return A unique pointer to a picture.
        */
        template <typename Path>
        static cpp0x::unique_ptr<picture_details_type>::type
        read_picture(const Path& path)
        {
            return cpp0x::unique_ptr<picture_details_type>::type(
                new picture_details_type(0, 0)
            );
        }

        /*!
            \brief Returns the dimension of a picture.

            \tparam Dimension A dimension type.

            \param picture A picture.

            \return The dimension of the picture.
        */
        template <typename Dimension>
        static Dimension picture_dimension(
            const picture_details_type& picture
        )
        {
            return Dimension(
                picture.dimension().first, picture.dimension().second
            );
        }

        /*!
            \brief Creates a canvas.

            \tparam DeviceContext A device context handle type.

            \param device_context A device context handle.

            \return A unique pointer to a canvas.
        */
        template <typename DeviceContext>
        static cpp0x::unique_ptr<canvas_details_type>::type
        create_canvas(const DeviceContext device_context)
        {
            return cpp0x::unique_ptr<canvas_details_type>::type(
                new canvas_details_type()
            );
        }

        /*!
            \brief Initializes a canvas.

            \param canvas A canvas.
        */
        static void initialize_canvas(canvas_details_type& canvas)
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
            return Font(
                TETENGO2_TEXT("TetengoFont"), 12, false, false, false, false
            );
        }

        /*!
            \brief Returns the installed font families.

            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param encoder An encoder.

            \return The installed font families.
        */
        template <typename String, typename Encoder>
        static std::vector<String> installed_font_families(
            const Encoder& encoder
        )
        {
            const String font_name(TETENGO2_TEXT("TetengoFont"));
            return std::vector<String>(1, font_name);
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
        */
        template <
            typename Dimension,
            typename Font,
            typename String,
            typename Encoder
        >
        static Dimension calc_text_dimension(
            const canvas_details_type& canvas,
            const Font&                font,
            const String&              text,
            const Encoder&             encoder
        )
        {
            return Dimension(123, 456);
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

            \throw std::runtime_error When the text cannot be drawn.
        */
        template <
            typename Font,
            typename String,
            typename Encoder,
            typename Position
        >
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

            \throw std::runtime_error When the picture cannot be painted.
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
