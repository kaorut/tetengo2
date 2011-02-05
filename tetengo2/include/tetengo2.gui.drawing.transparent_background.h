/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::transparent_background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_TRANSPARENTBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_TRANSPARENTBACKGROUND_H

//#include <boost/optional.hpp>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.drawing.background.h"


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a transparent background for Win32
               platforms.
        
        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename DrawingDetails>
    class transparent_background : public background<DrawingDetails>
    {
    public:
        // types

        //! The base type.
        typedef background<DrawingDetails> base_type;


        // constructors and destructor

        /*!
            \brief Creates a transparent background.
        */
        transparent_background()
        :
        base_type()
        {}

        /*!
            \brief Destroys the background.
        */
        virtual ~transparent_background()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    private:
        // virtual functions

        virtual boost::optional<const typename base_type::details_type&>
        details_impl()
        const
        {
            return boost::optional<const typename base_type::details_type&>();
        }


    };


}}}}}


#endif
