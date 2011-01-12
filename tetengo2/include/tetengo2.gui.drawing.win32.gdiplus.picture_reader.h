/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::picture_reader.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTUREREADER_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTUREREADER_H

#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a picture reader for Win32 platforms.

        \tparam Picture A picture type.
        \tparam Path    A path type.
    */
    template <typename Picture, typename Path>
    class picture_reader : private boost::noncopyable
    {
    public:
        // types

        //! The picture type.
        typedef Picture picture_type;

        //! The path type.
        typedef Path path_type;


        // constructors and destructor

        /*!
            \brief Creates a picture reader.

            \tparam P A path type.

            \param path A path.
        */
        template <typename P>
        picture_reader(P&& path)
        :
        m_path(std::forward<P>(path))
        {}


        // functions

        /*!
            \brief Reads a picture.

            \return A std::auto_ptr to a picture.

            \throw std::runtime_error When a picture cannot be read.
        */
        std::auto_ptr<picture_type> read()
        {
            std::auto_ptr<Gdiplus::Bitmap> p_bitmap(
                new Gdiplus::Bitmap(m_path.c_str())
            );
            if (p_bitmap->GetLastStatus() != S_OK)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't read a picture.")
                );
            }

            return std::auto_ptr<picture_type>(new picture_type(p_bitmap));
        }


    private:
        // variables

        const path_type m_path;


    };


}}}}}


#endif
