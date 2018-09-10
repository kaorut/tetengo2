/*! \file
    \brief The definition of tetengo2::detail::windows::common_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H)
#define TETENGO2_DETAIL_WINDOWS_COMMONDIALOG_H

#include <memory>
#include <utility>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui {
    namespace drawing {
        class font;
    }
    namespace widget {
        class abstract_window;
    }
}}


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog : public base::common_dialog
    {
    public:
        // types

        //! The message box button style type.
        using message_box_button_style_type = base::common_dialog::message_box_button_style_type;

        //! The message box icon style type.
        using message_box_icon_style_type = base::common_dialog::message_box_icon_style_type;

        //! The message box button ID type.
        using message_box_button_id_type = base::common_dialog::message_box_button_id_type;

        //! The message box details type.
        using message_box_details_type = base::common_dialog::message_box_details_type;

        //! The message box details pointer type.
        using message_box_details_ptr_type = base::common_dialog::message_box_details_ptr_type;

        //! The filters type.
        using filters_type = base::common_dialog::filters_type;

        //! The file open dialog details type.
        using file_open_dialog_details_type = base::common_dialog::file_open_dialog_details_type;

        //! The file open dialog details pointer type.
        using file_open_dialog_details_ptr_type = base::common_dialog::file_open_dialog_details_ptr_type;

        //! The file save dialog details type.
        using file_save_dialog_details_type = base::common_dialog::file_save_dialog_details_type;

        //! The file save dialog details pointer type.
        using file_save_dialog_details_ptr_type = base::common_dialog::file_save_dialog_details_ptr_type;

        //! The font dialog details type.
        using font_dialog_details_type = base::common_dialog::font_dialog_details_type;

        //! The font dialog details pointer type.
        using font_dialog_details_ptr_type = base::common_dialog::font_dialog_details_ptr_type;

        //! The color dialog details type.
        using color_dialog_details_type = base::common_dialog::color_dialog_details_type;

        //! The color dialog details pointer type.
        using color_dialog_details_ptr_type = base::common_dialog::color_dialog_details_ptr_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const common_dialog& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~common_dialog();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        common_dialog();


        // virtual functions

        virtual message_box_details_ptr_type create_message_box_impl(
            gui::widget::abstract_window&                      parent,
            type_list::string_type                             title,
            type_list::string_type                             main_content,
            type_list::string_type                             sub_content,
            bool                                               cancellable,
            message_box_button_style_type                      button_style,
            message_box_icon_style_type                        icon_style,
            tetengo2::stdalt::optional<type_list::string_type> custom_ok_button_label,
            tetengo2::stdalt::optional<std::pair<type_list::string_type, type_list::string_type>>
                custom_yes_no_button_labels) const override;

        virtual message_box_button_id_type show_message_box_impl(message_box_details_type& message_box) const override;

        virtual file_open_dialog_details_ptr_type create_file_open_dialog_impl(
            gui::widget::abstract_window& parent,
            type_list::string_type        title,
            const filters_type&           filters) const override;

        virtual tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_open_dialog_impl(file_open_dialog_details_type& dialog) const override;

        virtual file_save_dialog_details_ptr_type create_file_save_dialog_impl(
            gui::widget::abstract_window&                                         parent,
            type_list::string_type                                                title,
            const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
            const filters_type&                                                   filters) const override;

        virtual tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_save_dialog_impl(file_save_dialog_details_type& dialog) const override;

        virtual font_dialog_details_ptr_type create_font_dialog_impl(
            gui::widget::abstract_window&                         parent,
            const tetengo2::stdalt::optional<gui::drawing::font>& font) const override;

        virtual tetengo2::stdalt::optional<gui::drawing::font>
        show_font_dialog_impl(font_dialog_details_type& dialog) const override;

        virtual color_dialog_details_ptr_type create_color_dialog_impl(
            gui::widget::abstract_window&                          parent,
            const tetengo2::stdalt::optional<gui::drawing::color>& color) const override;

        virtual tetengo2::stdalt::optional<gui::drawing::color>
        show_color_dialog_impl(color_dialog_details_type& dialog) const override;
    };
}


#endif
