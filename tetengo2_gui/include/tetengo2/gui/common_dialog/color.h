/*! \file
    \brief The definition of tetengo2::gui::common_dialog::color.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_COLOR_H)
#define TETENGO2_GUI_COMMONDIALOG_COLOR_H

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    /*!
        \brief The class template for a color dialog.

        \tparam Color               A color type.
        \tparam WidgetTraits        A widget traits type.
        \tparam CommonDialogDetails A detail implementation type of common dialogs.
        \tparam WidgetDetailsTraits A detail implementation type traits of a widget.
        \tparam MenuDetails         A detail implementation type of a menu.
    */
    template <
        typename Color,
        typename WidgetTraits,
        typename CommonDialogDetails,
        typename WidgetDetailsTraits,
        typename MenuDetails>
    class color : private boost::noncopyable
    {
    public:
        // types

        //! The color type.
        using color_type = Color;

        //! The widget traits type.
        using widget_traits_type = WidgetTraits;

        //! The common dialog details type.
        using common_dialog_details_type = CommonDialogDetails;

        //! The details type.
        using details_type = typename common_dialog_details_type::color_dialog_details_type;

        //! The details pointer type;
        using details_ptr_type = typename common_dialog_details_type::color_dialog_details_ptr_type;

        //! The widget details traits type.
        using widget_details_traits_type = WidgetDetailsTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The abstract window type.
        using abstract_window_type =
            gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;


        // constructors and destructor

        /*!
            \brief Creates a color dialog.

            \param color  A color.
            \param parent A parent widget.
        */
        color(const tetengo2::stdalt::optional<color_type>& color, abstract_window_type& parent)
        : m_p_details{ common_dialog_details_type::create_color_dialog(parent, color) }, m_result{
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
            const auto result = common_dialog_details_type::show_color_dialog(*m_p_details);
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
