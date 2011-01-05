/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::picture_reader.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTUREREADER_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTUREREADER_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a picture reader for Win32 platforms.

        \tparam Picture A picture type.
    */
    template <typename Picture>
    class picture_reader : private boost::noncopyable
    {
    public:
        // types

        //! The picture type.
        typedef Picture picture_type;


        // constructors and destructor

        /*!
            \brief Creates a picture reader.
        */
        picture_reader()
        {}


    };


}}}}}


#endif
