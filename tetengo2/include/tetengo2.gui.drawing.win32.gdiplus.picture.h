/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::picture.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTURE_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_PICTURE_H

#include <memory>
#include <utility>

#include <boost/noncopyable.hpp>

#include "tetengo2.cpp0x_keyword.h"


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a picture for Win32 platforms.

        \tparam Size           A size type.
        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename Size, typename DrawingDetails>
    class picture : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The dimension type.
        typedef std::pair<size_type, size_type> dimension_type;

        //! The detail implementation type of a drawing.
        typedef DrawingDetails drawing_details_type;

        //! The detail implementation type of a picture.
        typedef
            typename drawing_details_type::picture_details_type details_type;


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
        m_p_details(drawing_details_type::create_picture(dimension, canvas))
        {}

        /*!
            \brief Creates a picture with a detail implementation.

            \param p_bitmap A std::auto_ptr to a detail implementation.
        */
        picture(std::auto_ptr<details_type> p_details)
        :
        m_p_details(p_details.release())
        {}


        // functions

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension()
        const
        {
            return drawing_details_type::picture_dimension<dimension_type>(
                *m_p_details
            );
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
        {
            return *m_p_details;
        }


    private:
        // variables

        const typename tetengo2::cpp0x::unique_ptr<details_type>::type
        m_p_details;


    };


}}}}}


#endif
