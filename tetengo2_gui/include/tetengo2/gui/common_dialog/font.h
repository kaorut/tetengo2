/*! \file
    \brief The definition of tetengo2::gui::common_dialog::font.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_FONT_H)
#define TETENGO2_GUI_COMMONDIALOG_FONT_H

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    /*!
        \brief The class template for a font dialog.

        \tparam Font                A font type.
        \tparam WidgetTraits        A widget traits type.
        \tparam CommonDialogDetails A detail implementation type of common dialogs.
        \tparam WidgetDetailsTraits A detail implementation type traits of a widget.
        \tparam MenuDetails         A detail implementation type of a menu.
    */
    template <
        typename Font,
        typename WidgetTraits,
        typename CommonDialogDetails,
        typename WidgetDetailsTraits,
        typename MenuDetails>
    class font : private boost::noncopyable
    {
    public:
        // types

        //! The font type.
        using font_type = Font;

        //! The widget traits type.
        using widget_traits_type = WidgetTraits;

        //! The encoder type.
        using encoder_type = typename widget_traits_type::encoder_type;

        //! The common dialog details type.
        using common_dialog_details_type = CommonDialogDetails;

        //! The details type.
        using details_type = typename common_dialog_details_type::font_dialog_details_type;

        //! The detail implementaiton pointer type;
        using details_ptr_type = typename common_dialog_details_type::font_dialog_details_ptr_type;

        //! The widget details traits type.
        using widget_details_traits_type = WidgetDetailsTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The abstract window type.
        using abstract_window_type =
            gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;


        // constructors and destructor

        /*!
            \brief Creates a font dialog.

            \param font   A font.
            \param parent A parent widget.
        */
        font(const tetengo2::stdalt::optional<font_type>& font, abstract_window_type& parent)
        : m_p_details{ common_dialog_details_type::create_font_dialog(parent, font, encoder()) }, m_result{
              font ? *font : font_type::dialog_font()
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
            const auto result =
                common_dialog_details_type::template show_font_dialog<font_type>(*m_p_details, encoder());
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
        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton{};
            return singleton;
        }


        // variables

        details_ptr_type m_p_details;

        font_type m_result;
    };
}


#endif
