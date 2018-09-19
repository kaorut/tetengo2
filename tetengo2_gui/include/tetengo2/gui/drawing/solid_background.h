/*! \file
    \brief The definition of tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_SOLIDBACKGROUND_H

#include <memory>

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

        //! The drawing details type.
        using drawing_details_type = base_type::drawing_details_type;


        // constructors and destructor

        /*!
            \brief Creates a solid background.

            \param drawing_details A detailm implementation of a drawing.
            \param color           A color.
        */
        solid_background(const drawing_details_type& drawing_details, color_type color);

        /*!
            \brief Creates a solid background.

            Creates a background for widgets.

            \param color           A color.
        */
        explicit solid_background(color_type color);

        /*!
            \brief Destroys the solid background.
        */
        virtual ~solid_background();


        // functions

        /*!
            \brief Returns the color.

            \return The color.
        */
        const color_type& get_color() const;


    private:
        // types

        using details_type = base_type::details_type;

        using details_ptr_type = drawing_details_type::background_details_ptr_type;

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual std::unique_ptr<base_type> clone_impl() const override;

        virtual const drawing_details_type& drawing_details_impl() const override;

        virtual const details_type& details_impl() const override;

        virtual details_type& details_impl() override;
    };
}


#endif
