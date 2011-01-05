/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::picture_reader.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTUREREADER_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTUREREADER_H

#include <utility>

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a picture reader for Win32 platforms.

        \tparam Picture     A picture type.
        \tparam InputStream An input stream type.
    */
    template <typename Picture, typename InputStream>
    class picture_reader : private boost::noncopyable
    {
    public:
        // types

        //! The picture type.
        typedef Picture picture_type;

        //! The input stream type.
        typedef InputStream input_stream_type;


        // constructors and destructor

        /*!
            \brief Creates a picture reader.
        */
        picture_reader()
        {}


        // functions

        /*!
            \brief Reads a picture.

            \param input_stream An input stream.

            \return A std::auto_ptr to a picture.
        */
        std::auto_ptr<picture_type> read(input_stream_type& input_stream)
        {
            return std::auto_ptr<picture_type>();
        }


    };


}}}}}


#endif
