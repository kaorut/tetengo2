/*! \file
    \brief The definition of tetengo2::gui::widget::side_bar.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_SIDEBAR_H)
#define TETENGO2_GUI_WIDGET_SIDEBAR_H

#include <memory>

#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a side bar.
    */
    class side_bar : public custom_control
    {
    public:
        // types

        //! The dimension unit type.
        using dimension_unit_type = typename dimension_type::unit_type;


        // constructors and destructor

        /*!
            \brief Creates a side bar.

            \param parent A parent widget.
        */
        explicit side_bar(widget& parent);

        /*!
            \brief Destroys the side bar.
        */
        virtual ~side_bar();


        // functions

        /*!
            \brief Returns the preferred width.

            \return The preferred width.
        */
        const dimension_unit_type& preferred_width();

        /*!
            \brief Returns the normal preferred width.

            The normal preferred width is the width when the side bar is not minimized.

            \return The normal preferred width.
        */
        const dimension_unit_type& normal_preferred_width();

        /*!
            \brief Sets a width.

            \param width A width.
        */
        void set_width(dimension_unit_type width);

        /*!
            \brief Returns the minimized status.

            \return The minimized status.
        */
        bool minimized() const;

        /*!
            \brief Sets a minimized status.

            \param minimized A minimized status.
        */
        void set_minimized(bool minimized);

        /*!
            \brief Returns the child control area position.

            \return The child control area position.
        */
        position_type child_control_area_position() const;

        /*!
            \brief Returns the child control area dimension.

            \return The child control area dimension.
        */
        dimension_type child_control_area_dimension() const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
