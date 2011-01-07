/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::picture.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTURE_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTURE_H

#include <memory>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

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
            \tparam Canvas    A canvas type.

            \param dimension A dimension.
            \param canvas    A canvas.
        */
        template <typename Dimension, typename Canvas>
        picture(const Dimension& dimension, const Canvas& canvas)
        :
        m_p_bitmap(
            new Gdiplus::Bitmap(
                to_pixels< ::INT>(
                    gui::dimension<Dimension>::width(dimension)
                ),
                to_pixels< ::INT>(
                    gui::dimension<Dimension>::height(dimension)
                ),
                &const_cast<Canvas&>(canvas).gdiplus_graphics()
            )
        )
        {}

        /*!
            \brief Creates a picture with a GDI+ bitmap.

            \param p_bitmap A std::auto_ptr to a GDI+ bitmap.
        */
        picture(std::auto_ptr<Gdiplus::Bitmap> p_bitmap)
        :
        m_p_bitmap(p_bitmap)
        {}


        // functions

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension()
        const
        {
            Gdiplus::Bitmap* const p_bitmap =
                const_cast<Gdiplus::Bitmap*>(m_p_bitmap.get());
            return dimension_type(
                to_unit<size_type>(p_bitmap->GetWidth()),
                to_unit<size_type>(p_bitmap->GetHeight())
            );
        }

        /*!
            \brief Returns the GDI+ bitmap.

            \return The GDI+ bitmap.
        */
        Gdiplus::Bitmap& gdiplus_bitmap()
        {
            return *m_p_bitmap;
        }

        /*!
            \brief Returns the GDI+ bitmap.

            \return The GDI+ bitmap.
        */
        const Gdiplus::Bitmap& gdiplus_bitmap()
        const
        {
            return *m_p_bitmap;
        }


    private:
        // variables

        const boost::scoped_ptr<Gdiplus::Bitmap> m_p_bitmap;


    };


}}}}}


#endif
