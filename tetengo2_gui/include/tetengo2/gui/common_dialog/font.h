/*! \file
    \brief The definition of tetengo2::gui::common_dialog::font.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FONT_H)
#define TETENGO2_GUI_COMMONDIALOG_FONT_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    /*!
        \brief The class for a font dialog.
    */
    class font : private boost::noncopyable
    {
    public:
        // types

        //! The font type.
        using font_type = gui::drawing::font;

        //! The abstract window type.
        using abstract_window_type = gui::widget::abstract_window;

        //! The details type.
        using details_type = detail::base::common_dialog::font_dialog_details_type;


        // constructors and destructor

        /*!
            \brief Creates a font dialog.

            \param font   A font.
            \param parent A parent widget.
        */
        font(const tetengo2::stdalt::optional<font_type>& font, abstract_window_type& parent);

        /*!
            \brief Destroys the font dialog.
        */
        ~font();


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const font_type& result() const;

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

        std::unique_ptr<impl> m_p_impl;
    };
}


#endif
