/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::solid_background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_SOLIDBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_SOLIDBACKGROUND_H

#include <cstddef>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.drawing.background.h"


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a solid background for Win32 platforms.
        
        \tparam Handle A handle type.
    */
    template <typename Handle>
    class solid_background : public background<Handle>
    {
    public:
        // types

        //! The base type.
        typedef background<Handle> base_type;


        // constructors and destructor

        /*!
            \brief Creates a solid background.
        */
        solid_background()
        :
        base_type()
        {}

        /*!
            \brief Destroys the background.
        */
        virtual ~solid_background()
        TETENGO2_NOEXCEPT
        {}


    private:
        // virtual functions

        virtual typename base_type::handle_type handle_impl()
        const
        {
            return NULL;
        }


    };


}}}}}


#endif
