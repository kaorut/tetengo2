/*! \file
    \brief The definition of tetengo2::detail::base::common_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_COMMONDIALOG_H)
#define TETENGO2_DETAIL_BASE_COMMONDIALOG_H

#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h> // IWYU pragma: keep
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
}}}


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog : private boost::noncopyable
    {
    public:
        // types

        //! The message box button style type.
        enum class message_box_button_style_type
        {
            ok, //!< With OK button.
            yes_no, //!< With Yes and No buttons.
        };

        //! The message box icon style type.
        enum class message_box_icon_style_type
        {
            error, //!< Error.
            warning, //!< Warning.
            information, //!< Information.
        };

        //! The message box button ID type.
        enum class message_box_button_id_type
        {
            ok, //!< OK button.
            yes, //!< Yes button.
            no, //!< No button.
            cancel, //!< Cancel button.
        };

        //! The message box details type.
        struct message_box_details_type
        {
            /*!
                \brief Destroys the message box details.
            */
            virtual ~message_box_details_type();
        };

        //! The message box details pointer type.
        using message_box_details_ptr_type = std::unique_ptr<message_box_details_type>;

        //! The filters type.
        using filters_type = std::vector<std::pair<type_list::string_type, type_list::string_type>>;

        //! The file open dialog details type.
        struct file_open_dialog_details_type
        {
            /*!
                \brief Destroys the file open dialog details.
            */
            virtual ~file_open_dialog_details_type();
        };

        //! The file open dialog details pointer type.
        using file_open_dialog_details_ptr_type = std::unique_ptr<file_open_dialog_details_type>;

        //! The file save dialog details type.
        struct file_save_dialog_details_type
        {
            /*!
                \brief Destroys the file save dialog details.
            */
            virtual ~file_save_dialog_details_type();
        };

        //! The file save dialog details pointer type.
        using file_save_dialog_details_ptr_type = std::unique_ptr<file_save_dialog_details_type>;

        //! The font dialog details type.
        struct font_dialog_details_type
        {
            /*!
                \brief Destroys the font dialog details.
            */
            virtual ~font_dialog_details_type();
        };

        //! The font dialog details pointer type.
        using font_dialog_details_ptr_type = std::unique_ptr<font_dialog_details_type>;

        //! The color dialog details type.
        struct color_dialog_details_type
        {
            /*!
                \brief Destroys the color dialog details.
            */
            virtual ~color_dialog_details_type();
        };

        //! The color dialog details pointer type.
        using color_dialog_details_ptr_type = std::unique_ptr<color_dialog_details_type>;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~common_dialog();


        // functions

        /*!
            \brief Creates a message box.

            \param parent                      A parent window.
            \param title                       A title.
            \param main_content                A main content.
            \param sub_content                 A sub content.
            \param cancellable                 Whether the message box is cancellable.
            \param button_style                A button style.
            \param icon_style                  An icon style.
            \param custom_ok_button_label      A custom OK button label.
            \param custom_yes_no_button_labels A custom Yes and No button labels.

            \return A unique pointer to a message box.
        */
        message_box_details_ptr_type create_message_box(
            gui::widget::abstract_window&                      parent,
            type_list::string_type                             title,
            type_list::string_type                             main_content,
            type_list::string_type                             sub_content,
            bool                                               cancellable,
            message_box_button_style_type                      button_style,
            message_box_icon_style_type                        icon_style,
            tetengo2::stdalt::optional<type_list::string_type> custom_ok_button_label,
            tetengo2::stdalt::optional<std::pair<type_list::string_type, type_list::string_type>>
                custom_yes_no_button_labels) const;

        /*!
            \brief Shows a message box and returns a button id.

            \param message_box A message box.

            \return The path.

            \throw std::system_error When the message box cannot be shown.
        */
        message_box_button_id_type show_message_box(message_box_details_type& message_box) const;

        /*!
            \brief Creates a file open dialog.

            \param parent  A parent window.
            \param title   A title.
            \param filters A file filters. Each element is a pair of a label and a file pattern.

            \return A unique pointer to a file open dialog.

            \throw std::system_error When the file open dialog cannot be created.
        */
        file_open_dialog_details_ptr_type create_file_open_dialog(
            gui::widget::abstract_window& parent,
            type_list::string_type        title,
            const filters_type&           filters) const;

        /*!
            \brief Shows a file open dialog and return a path.

            \param dialog  A file open dialog.

            \return The path.

            \throw std::system_error When the file open dialog cannot be shown.
        */
        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_open_dialog(file_open_dialog_details_type& dialog) const;

        /*!
            \brief Creates a file save dialog.

            \param parent  A parent window.
            \param title   A title.
            \param path    A path.
            \param filters A file filters. Each element is a pair of a label and a file pattern.

            \return A unique pointer to a file save dialog.

            \throw std::system_error When the file save dialog cannot be created.
        */
        file_save_dialog_details_ptr_type create_file_save_dialog(
            gui::widget::abstract_window&                                         parent,
            type_list::string_type                                                title,
            const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
            const filters_type&                                                   filters) const;

        /*!
            \brief Shows a file save dialog and return a path.

            \param dialog  A file save dialog.

            \return The path.

            \throw std::system_error When the file save dialog cannot be shown.
        */
        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_save_dialog(file_save_dialog_details_type& dialog) const;

        /*!
            \brief Creates a font dialog.

            \param parent  A parent window.
            \param font    A font.

            \return A unique pointer to a font dialog.

            \throw std::system_error When the font dialog cannot be created.
        */
        font_dialog_details_ptr_type create_font_dialog(
            gui::widget::abstract_window&                         parent,
            const tetengo2::stdalt::optional<gui::drawing::font>& font) const;

        /*!
            \brief Shows a font dialog and return a font.

            \param dialog  A font dialog.

            \return The font.

            \throw std::system_error When the font dialog cannot be shown.
        */
        tetengo2::stdalt::optional<gui::drawing::font> show_font_dialog(font_dialog_details_type& dialog) const;

        /*!
            \brief Creates a color dialog.

            \param parent A parent window.
            \param color  A color.

            \return A unique pointer to a color dialog.

            \throw std::system_error When the color dialog cannot be created.
        */
        color_dialog_details_ptr_type create_color_dialog(
            gui::widget::abstract_window&                          parent,
            const tetengo2::stdalt::optional<gui::drawing::color>& color) const;

        /*!
            \brief Shows a color dialog and return a font.

            \param dialog A color dialog.

            \return The color.

            \throw std::system_error When the color dialog cannot be shown.
        */
        tetengo2::stdalt::optional<gui::drawing::color> show_color_dialog(color_dialog_details_type& dialog) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        common_dialog();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual message_box_details_ptr_type create_message_box_impl(
            gui::widget::abstract_window&                      parent,
            type_list::string_type                             title,
            type_list::string_type                             main_content,
            type_list::string_type                             sub_content,
            bool                                               cancellable,
            const message_box_button_style_type                button_style,
            const message_box_icon_style_type                  icon_style,
            tetengo2::stdalt::optional<type_list::string_type> custom_ok_button_label,
            tetengo2::stdalt::optional<std::pair<type_list::string_type, type_list::string_type>>
                custom_yes_no_button_labels) const = 0;

        virtual message_box_button_id_type show_message_box_impl(message_box_details_type& message_box) const = 0;

        virtual file_open_dialog_details_ptr_type create_file_open_dialog_impl(
            gui::widget::abstract_window& parent,
            type_list::string_type        title,
            const filters_type&           filters) const = 0;

        virtual tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_open_dialog_impl(file_open_dialog_details_type& dialog) const = 0;

        virtual file_save_dialog_details_ptr_type create_file_save_dialog_impl(
            gui::widget::abstract_window&                                         parent,
            type_list::string_type                                                title,
            const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
            const filters_type&                                                   filters) const = 0;

        virtual tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_save_dialog_impl(file_save_dialog_details_type& dialog) const = 0;

        virtual font_dialog_details_ptr_type create_font_dialog_impl(
            gui::widget::abstract_window&                         parent,
            const tetengo2::stdalt::optional<gui::drawing::font>& font) const = 0;

        virtual tetengo2::stdalt::optional<gui::drawing::font>
        show_font_dialog_impl(font_dialog_details_type& dialog) const = 0;

        virtual color_dialog_details_ptr_type create_color_dialog_impl(
            gui::widget::abstract_window&                          parent,
            const tetengo2::stdalt::optional<gui::drawing::color>& color) const = 0;

        virtual tetengo2::stdalt::optional<gui::drawing::color>
        show_color_dialog_impl(color_dialog_details_type& dialog) const = 0;
    };
}


#endif
