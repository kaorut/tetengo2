/*! \file
    \brief The definition of tetengo2::gui::common_dialog::font.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FONT_H)
#define TETENGO2_GUI_COMMONDIALOG_FONT_H

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    /*!
        \brief The class template for a font dialog.

        \tparam Font                  A font type.
        \tparam CommonDialogDetails   A detail implementation type of common dialogs.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam DrawingDetails        A detail implementation type of drawing.
        \tparam ScrollDetails         A detail implementation type of a scroll.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
        \tparam MenuDetails           A detail implementation type of a menu.
    */
    template <
        typename Font,
        typename CommonDialogDetails,
        typename WidgetDetails,
        typename DrawingDetails,
        typename ScrollDetails,
        typename MessageHandlerDetails>
    class font : private boost::noncopyable
    {
    public:
        // types

        //! The font type.
        using font_type = Font;

        //! The common dialog details type.
        using common_dialog_details_type = CommonDialogDetails;

        //! The details type.
        using details_type = typename common_dialog_details_type::font_dialog_details_type;

        //! The detail implementaiton pointer type;
        using details_ptr_type = typename common_dialog_details_type::font_dialog_details_ptr_type;

        //! The abstract window type.
        using abstract_window_type = gui::widget::abstract_window;


        // constructors and destructor

        /*!
            \brief Creates a font dialog.

            \param font   A font.
            \param parent A parent widget.
        */
        font(const tetengo2::stdalt::optional<font_type>& font, abstract_window_type& parent)
        : m_p_details{ common_dialog_details_type::create_font_dialog(parent, font) }, m_result{
              font ? *font : font_type::dialog_font(tetengo2::detail::gui_detail_impl_set().drawing_())
          }
        {}


        // functions

        /*!
            \brief Returns the result.

            \return The result.
        */
        const font_type& result() const
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
            const auto result = common_dialog_details_type::template show_font_dialog<font_type>(*m_p_details);
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

        font_type m_result;
    };
}


#endif
