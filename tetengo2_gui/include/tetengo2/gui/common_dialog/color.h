/*! \file
    \brief The definition of tetengo2::gui::common_dialog::color.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_COLOR_H)
#define TETENGO2_GUI_COMMONDIALOG_COLOR_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    /*!
        \brief The class for a color dialog.
    */
    class color : private boost::noncopyable
    {
    public:
        // types

        //! The color type.
        using color_type = gui::drawing::color;

        //! The abstract window type.
        using abstract_window_type = gui::widget::abstract_window;

        //! The details type.
        using details_type = detail::base::common_dialog::color_dialog_details_type;


        // constructors and destructor

        /*!
            \brief Creates a color dialog.

            \param color  A color.
            \param parent A parent widget.
        */
        color(const tetengo2::stdalt::optional<color_type>& color, abstract_window_type& parent);

        /*!
            \brief Destroys the color dialog.
        */
        ~color();


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const color_type& result() const;

        /*!
            \brief Shows the dialog as model.

            \retval true  When the OK button is pressed.
            \retval false Otherwise.
        */
        bool do_modal();

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
