/*! \file
    \brief The definition of tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H

#include <cassert>
#include <memory>
#include <utility>

#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/color.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a solid background.
    */
    class solid_background : public background
    {
    public:
        // types

        //! The base type.
        using base_type = background;

        //! The color type.
        using color_type = color;


        // constructors and destructor

        /*!
            \brief Creates a solid background.

            \param color A color.
        */
        explicit solid_background(color_type color)
        : base_type{}, m_color{ std::move(color) }, m_p_details{
              base_type::drawing_details_type::instance().create_solid_background(m_color)
          }
        {}

        /*!
            \brief Destroys the background.
        */
        virtual ~solid_background() = default;


        // functions

        /*!
            \brief Returns the color.

            \return The color.
        */
        const color_type& get_color() const
        {
            return m_color;
        }


    private:
        // types

        using details_type = typename base_type::details_type;

        using details_ptr_type = typename base_type::details_ptr_type;


        // variables

        const color_type m_color;

        const details_ptr_type m_p_details;


        // virtual functions

        virtual std::unique_ptr<base_type> clone_impl() const override
        {
            return std::make_unique<solid_background>(m_color);
        }

        virtual const details_type& details_impl() const override
        {
            assert(m_p_details);
            return *m_p_details;
        }

        virtual details_type& details_impl() override
        {
            assert(m_p_details);
            return *m_p_details;
        }
    };
}


#endif
