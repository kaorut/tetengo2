/*! \file
    \brief The definition of tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H

//#include <memory>
//#include <utility>

//#include <boost/optional.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.unique.h"


namespace tetengo2 { namespace gui { namespace drawing
{
    /*!
        \brief The class template for a solid background.

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

            \param color A color.
        */
        explicit solid_background(color_type color)
        :
        base_type(),
        m_color(std::move(color)),
        m_p_details(base_type::drawing_details_type::create_solid_background(m_color))
        {}

        /*!
            \brief Destroys the background.
        */
        virtual ~solid_background()
        TETENGO2_CPP11_NOEXCEPT
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
        // types

        typedef typename base_type::details_type details_type;

        typedef typename base_type::details_ptr_type details_ptr_type;


        // variables

        const color_type m_color;

        const details_ptr_type m_p_details;


        // virtual functions

        virtual std::unique_ptr<base_type> clone_impl()
        const
        {
            return tetengo2::make_unique<solid_background>(m_color);
        }

        virtual boost::optional<const details_type&>
        details_impl()
        const
        {
            return boost::make_optional<const details_type&>(static_cast<bool>(m_p_details), *m_p_details);
        }

        virtual boost::optional<details_type&>
        details_impl()
        {
            return boost::make_optional<details_type&>(static_cast<bool>(m_p_details), *m_p_details);
        }


    };


}}}


#endif
