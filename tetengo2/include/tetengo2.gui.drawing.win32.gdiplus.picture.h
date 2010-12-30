/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::picture.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTURE_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTURE_H

#include <utility>

#include <boost/noncopyable.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <gdiplus.h>
#undef min
#undef max

#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a picture for Win32 platforms.

        \tparam Size A size type.
    */
    template <typename Size>
    class picture : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The dimension type.
        typedef std::pair<size_type, size_type> dimension_type;


        // constructors and destructor

        /*!
            \brief Creates a picture based on a canvas.
            
            \tparam Dimension A dimension type.
            \tparam Canvas A canvas type.

            \param device_handle A device handle.
        */
        template <typename Dimension, typename Canvas>
        picture(const Dimension& dimension, Canvas& canvas)
        :
        m_bitmap(
            to_pixels< ::INT>(gui::dimension<Dimension>::width(dimension)),
            to_pixels< ::INT>(gui::dimension<Dimension>::height(dimension)),
            &canvas.gdiplus_graphics()
        )
        {
            for (std::size_t i = 0; i < 128; ++i)
                for (std::size_t j = 0; j < 96; ++j)
                    m_bitmap.SetPixel(i, j, Gdiplus::Color(128, 0, 0, 255));
        }

        /*!
            \brief Returns the GDI+ bitmap.

            \return The GDI+ bitmap.
        */
        Gdiplus::Bitmap& gdiplus_bitmap()
        {
            return m_bitmap;
        }

        /*!
            \brief Returns the GDI+ bitmap.

            \return The GDI+ bitmap.
        */
        const Gdiplus::Bitmap& gdiplus_bitmap()
        const
        {
            return m_bitmap;
        }


    private:
        // variables

        Gdiplus::Bitmap m_bitmap;


    };


}}}}}


#endif
