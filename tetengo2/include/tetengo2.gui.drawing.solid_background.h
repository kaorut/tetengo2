/*! \file
    \brief The definition of tetengo2::gui::drawing::win32::gdiplus::solid_background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_SOLIDBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_WIN32_GDIPLUS_SOLIDBACKGROUND_H

#include <utility>

//#include <boost/optional.hpp>

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

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.drawing.background.h"


namespace tetengo2 { namespace gui { namespace drawing { namespace win32 {
namespace gdiplus
{
    /*!
        \brief The class template for a solid background for Win32 platforms.
        
        \tparam Color          A color type.
        \tparam DrawingDetails A detail implementation type of a drawing.
    */
    template <typename Color, typename DrawingDetails>
    class solid_background : public background<DrawingDetails>
    {
    public:
        // types

        //! The base type.
        typedef background<DrawingDetails> base_type;

        //! The color type.
        typedef Color color_type;


        // constructors and destructor

        /*!
            \brief Creates a solid background.

            \tparam C A color type.

            \param color A color.
        */
        template <typename C>
        solid_background(C&& color)
        :
        base_type(),
        m_color(std::forward<C>(color)),
        m_brush(
            Gdiplus::Color(
                m_color.alpha(),
                m_color.red(),
                m_color.green(),
                m_color.blue()
            )
        )
        {}

        /*!
            \brief Destroys the background.
        */
        virtual ~solid_background()
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the color.

            \return The color.
        */
        const color_type& color()
        const
        {
            return m_color;
        }


    private:
        // variables

        const color_type m_color;

        Gdiplus::SolidBrush m_brush;


        // virtual functions

        virtual boost::optional<const typename base_type::details_type&>
        details_impl()
        const
        {
            return boost::optional<const typename base_type::details_type&>(
                &m_brush
            );
        }


    };


}}}}}


#endif
