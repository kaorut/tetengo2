/*! \file
    \brief The definition of tetengo2::detail::stub::drawing.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_DRAWING_H)
#define TETENGO2_DETAIL_STUB_DRAWING_H

#include "tetengo2.cpp0x_keyword.h"
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
        struct picture_details_type {};


        // static functions

        /*!
            \brief Creates a solid background.

            \tparam Color A color type.

            \param color A color.

            \return A tetengo2::cpp0x::unique_ptr::type to a solid background.
        */
        template <typename Color>
        static tetengo2::cpp0x::unique_ptr<background_details_type>::type
        create_solid_background(const Color& color)
        {
            return tetengo2::cpp0x::unique_ptr<background_details_type>::type(
                new background_details_type()
            );
        }

        /*!
            \brief Creates a transparent background.

            \return A tetengo2::cpp0x::unique_ptr::type to a transparent
                    background.
        */
        static tetengo2::cpp0x::unique_ptr<background_details_type>::type
        create_transparent_background()
        {
            return tetengo2::cpp0x::unique_ptr<
                background_details_type
            >::type();
        }

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
            \brief Creates a picture.

            \tparam Dimension A dimension type.
            \tparam Canvas    A canvas type.

            \param dimension A dimension.
            \param canvas    A canvas.

            \return A tetengo2::cpp0x::unique_ptr::type to a picture.
        */
        template <typename Dimension, typename Canvas>
        static tetengo2::cpp0x::unique_ptr<picture_details_type>::type
        create_picture(const Dimension& dimension, const Canvas& canvas)
        {
            return tetengo2::cpp0x::unique_ptr<picture_details_type>::type(
                new picture_details_type()
            );
        }

        /*!
            \brief Reads a picture.

            \tparam Path    A path type.

            \param path A path.

            \return A tetengo2::cpp0x::unique_ptr::type to a picture.
        */
        template <typename Path>
        static tetengo2::cpp0x::unique_ptr<picture_details_type>::type
        read_picture(const Path& path)
        {
            return tetengo2::cpp0x::unique_ptr<picture_details_type>::type(
                new picture_details_type()
            );
        }

        /*!
            \brief Returns the dimension of a picture.

            \tparam Dimension A dimension type.

            \param picture A picture.
        */
        template <typename Dimension>
        static Dimension picture_dimension(
            const picture_details_type& picture
        )
        {
            return Dimension();
        }


    private:
        // forbidden operations

        drawing();


    };


}}}


#endif
