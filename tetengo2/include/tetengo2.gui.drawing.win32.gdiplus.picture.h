/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::picture.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTURE_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTURE_H

#include <utility>

#include <boost/noncopyable.hpp>

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
        picture(const Dimension& dimension, const Canvas& canvas)
        {}


    };


}}}}}


#endif
