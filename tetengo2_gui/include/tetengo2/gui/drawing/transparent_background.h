/*! \file
    \brief The definition of tetengo2::gui::drawing::transparent_background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H)
#define TETENGO2_GUI_DRAWING_TRANSPARENTBACKGROUND_H

#include <memory>

#include <tetengo2/gui/drawing/background.h>


namespace tetengo2::gui::drawing {
    /*!
        \brief The class for a transparent background.
    */
    class transparent_background : public background
    {
    public:
        // types

        //! The base type.
        using base_type = background;

        //! The drawing details type.
        using drawing_details_type = base_type::drawing_details_type;


        // constructors and destructor

        /*!
            \brief Creates a transparent background.

            \param drawing_details A detailm implementation of a drawing.
        */
        explicit transparent_background(const drawing_details_type& drawing_details);

        /*!
            \brief Creates a transparent background.

            Creates a background for widgets.
        */
        transparent_background();

        /*!
            \brief Destroys the background.
        */
        virtual ~transparent_background();


    private:
        // types

        using details_type = base_type::details_type;

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
