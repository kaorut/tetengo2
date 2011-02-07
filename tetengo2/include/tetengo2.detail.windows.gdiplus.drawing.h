/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::drawing.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H

#include <cassert>
//#include <utility>
//#include <stdexcept>

//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.detail.windows.font.h"
#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace detail { namespace windows { namespace gdiplus
{
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing
    {
    public:
        // types

        //! The background details type.
        typedef Gdiplus::Brush background_details_type;

        //! The picture details type.
        typedef Gdiplus::Bitmap picture_details_type;


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
                new Gdiplus::SolidBrush(
                    Gdiplus::Color(
                        color.alpha(),
                        color.red(),
                        color.green(),
                        color.blue()
                    )
                )
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
            const ::LOGFONTW log_font =
                tetengo2::detail::windows::get_message_font();

            assert(log_font.lfHeight < 0);
            return Font(
                log_font.lfFaceName,
                -log_font.lfHeight,
                log_font.lfWeight >= FW_BOLD,
                log_font.lfItalic != 0,
                log_font.lfUnderline != 0,
                log_font.lfStrikeOut != 0
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
            tetengo2::cpp0x::unique_ptr<picture_details_type>::type p_picture(
                new Gdiplus::Bitmap(
                    to_pixels< ::INT>(
                        gui::dimension<Dimension>::width(dimension)
                    ),
                    to_pixels< ::INT>(
                        gui::dimension<Dimension>::height(dimension)
                    ),
                    &const_cast<Canvas&>(canvas).gdiplus_graphics()
                )
            );

            return std::move(p_picture);
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
            tetengo2::cpp0x::unique_ptr<picture_details_type>::type p_picture(
                new Gdiplus::Bitmap(path.c_str())
            );
            if (p_picture->GetLastStatus() != S_OK)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't read a picture.")
                );
            }

            return std::move(p_picture);
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
            return Dimension(
                gui::to_unit<typename gui::dimension<Dimension>::width_type>(
                    const_cast<picture_details_type&>(picture).GetWidth()
                ),
                gui::to_unit<typename gui::dimension<Dimension>::height_type>(
                    const_cast<picture_details_type&>(picture).GetHeight()
                )
            );
        }


    private:
        // forbidden operations

        drawing();


   };


}}}}


#endif
