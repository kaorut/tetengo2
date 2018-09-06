/*! \file
    \brief The definition of tetengo2::gui::common_dialog::color.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_COLOR_H)
#define TETENGO2_GUI_COMMONDIALOG_COLOR_H

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/widget/abstract_window.h>
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

        //! The common dialog details type.
        using common_dialog_details_type = detail::base::common_dialog;

        //! The details type.
        using details_type = common_dialog_details_type::color_dialog_details_type;

        //! The details pointer type;
        using details_ptr_type = common_dialog_details_type::color_dialog_details_ptr_type;

        //! The abstract window type.
        using abstract_window_type = gui::widget::abstract_window;


        // constructors and destructor

        /*!
            \brief Creates a color dialog.

            \param color  A color.
            \param parent A parent widget.
        */
        color(const tetengo2::stdalt::optional<color_type>& color, abstract_window_type& parent)
        : m_p_details{ detail::gui_detail_impl_set().common_dialog_().create_color_dialog(parent, color) }, m_result{
              color ? *color : color_type{ 0, 0, 0 }
          }
        {}


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const color_type& result() const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog as model.

            \retval true  When the OK button is pressed.
            \retval false Otherwise.
        */
        bool do_modal()
        {
            const auto result = detail::gui_detail_impl_set().common_dialog_().show_color_dialog(*m_p_details);
            if (!result)
                return false;

            m_result = *result;
            return true;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details() const
        {
            return *m_p_details;
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details()
        {
            return *m_p_details;
        }


    private:
        // variables

        details_ptr_type m_p_details;

        color_type m_result;
    };
}


#endif
