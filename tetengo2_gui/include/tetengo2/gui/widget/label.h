/*! \file
    \brief The definition of tetengo2::gui::widget::label.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LABEL_H)
#define TETENGO2_GUI_WIDGET_LABEL_H

#include <memory>

#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for a label.
    */
    class label : public control
    {
    public:
        // types

        //! The dimension unit type.
        using dimension_unit_type = typename dimension_type::unit_type;


        // constructors and destructor

        /*!
            \brief Creates a label.

            \param parent A parent widget.
        */
        explicit label(widget& parent);

        /*!
            \brief Destroys the label.
        */
        virtual ~label() noexcept;


        // functions

        /*!
            \brief Fit the dimension to the dimension of the text.
        */
        void fit_to_content();

        /*!
            \brief Fit the dimension to the dimension of the text.

            \param max_width A maximum width.
        */
        void fit_to_content(dimension_unit_type max_width);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
