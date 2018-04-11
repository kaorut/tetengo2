/*! \file
    \brief The definition of tetengo2::detail::stub::common_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_COMMONDIALOG_H)
#define TETENGO2_DETAIL_STUB_COMMONDIALOG_H

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace tetengo2::detail::stub {
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
        };

        //! The message box details pointer type.
        using message_box_details_ptr_type = std::unique_ptr<message_box_details_type>;

        //! The file open dialog details type.
        struct file_open_dialog_details_type
        {
        };

        //! The file open dialog details pointer type.
        using file_open_dialog_details_ptr_type = std::unique_ptr<file_open_dialog_details_type>;

        //! The file save dialog details type.
        struct file_save_dialog_details_type
        {
        };

        //! The file save dialog details pointer type.
        using file_save_dialog_details_ptr_type = std::unique_ptr<file_save_dialog_details_type>;

        //! The font dialog details type.
        struct font_dialog_details_type
        {
        };

        //! The font dialog details pointer type.
        using font_dialog_details_ptr_type = std::unique_ptr<font_dialog_details_type>;

        //! The color dialog details type.
        struct color_dialog_details_type
        {
        };

        //! The color dialog details pointer type.
        using color_dialog_details_ptr_type = std::unique_ptr<color_dialog_details_type>;


        // static functions

        /*!
            \brief Creates a message box.

            \tparam AbstractWindow An abstract window type.
            \tparam String         A string type.
            \tparam Encoder        An encoder type.

            \param parent                      A parent window.
            \param title                       A title.
            \param main_content                A main content.
            \param sub_content                 A sub content.
            \param cancellable                 Whether the message box is cancellable.
            \param button_style                A button style.
            \param icon_style                  An icon style.
            \param custom_ok_button_label      A custom OK button label.
            \param custom_yes_no_button_labels A custom Yes and No button labels.
            \param encoder                     An encoder.

            \return A unique pointer to a message box.
        */
        template <typename AbstractWindow, typename String, typename Encoder>
        static message_box_details_ptr_type create_message_box(
            TETENGO2_STDALT_MAYBE_UNUSED AbstractWindow& parent,
            TETENGO2_STDALT_MAYBE_UNUSED String title,
            TETENGO2_STDALT_MAYBE_UNUSED String main_content,
            TETENGO2_STDALT_MAYBE_UNUSED String     sub_content,
            TETENGO2_STDALT_MAYBE_UNUSED const bool cancellable,
            TETENGO2_STDALT_MAYBE_UNUSED const message_box_button_style_type button_style,
            TETENGO2_STDALT_MAYBE_UNUSED const message_box_icon_style_type icon_style,
            TETENGO2_STDALT_MAYBE_UNUSED tetengo2::stdalt::optional<String> custom_ok_button_label,
            TETENGO2_STDALT_MAYBE_UNUSED       tetengo2::stdalt::optional<std::pair<String, String>>
                                               custom_yes_no_button_labels,
            TETENGO2_STDALT_MAYBE_UNUSED const Encoder& encoder)
        {
            return std::make_unique<message_box_details_type>();
        }

        /*!
            \brief Shows a message box and return a button id.

            \param message_box A message box.

            \return The path.

            \throw std::system_error When the message box cannot be shown.
        */
        static message_box_button_id_type
        show_message_box(TETENGO2_STDALT_MAYBE_UNUSED message_box_details_type& message_box)
        {
            return message_box_button_id_type::cancel;
        }

        /*!
            \brief Creates a file open dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam String         A string type.
            \tparam Filters        A filters type.
            \tparam Encoder        An encoder type.

            \param parent  A parent window.
            \param title   A title.
            \param filters A file filters. Each element is a pair of a label and a file pattern.
            \param encoder An encoder.

            \return A unique pointer to a file open dialog.

            \throw std::system_error When the file open dialog cannot be created.
        */
        template <typename AbstractWindow, typename String, typename Filters, typename Encoder>
        static file_open_dialog_details_ptr_type create_file_open_dialog(
            TETENGO2_STDALT_MAYBE_UNUSED AbstractWindow& parent,
            TETENGO2_STDALT_MAYBE_UNUSED String title,
            TETENGO2_STDALT_MAYBE_UNUSED const Filters& filters,
            TETENGO2_STDALT_MAYBE_UNUSED const Encoder& encoder)
        {
            return std::make_unique<file_open_dialog_details_type>();
        }

        /*!
            \brief Shows a file open dialog and return a path.

            \tparam Encoder An encoder type.

            \param dialog  A file open dialog.
            \param encoder An encoder.

            \return The path.

            \throw std::system_error When the file open dialog cannot be shown.
        */
        template <typename Encoder>
        static tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path> show_file_open_dialog(
            TETENGO2_STDALT_MAYBE_UNUSED file_open_dialog_details_type& dialog,
            TETENGO2_STDALT_MAYBE_UNUSED const Encoder& encoder)
        {
            tetengo2::stdalt::filesystem::path file_name{ tetengo2::stdalt::filesystem::path::string_type{
                TETENGO2_TEXT("file_open_dialog") } };
            return tetengo2::stdalt::make_optional(
                tetengo2::stdalt::filesystem::temp_directory_path() / std::move(file_name));
        }

        /*!
            \brief Creates a file save dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam String         A string type.
            \tparam OptionalPath   An optional path type.
            \tparam Filters        A filters type.
            \tparam Encoder        An encoder type.

            \param parent  A parent window.
            \param title   A title.
            \param path    A path.
            \param filters A file filters. Each element is a pair of a label and a file pattern.
            \param encoder An encoder.

            \return A unique pointer to a file save dialog.

            \throw std::system_error When the file save dialog cannot be created.
        */
        template <typename AbstractWindow, typename String, typename OptionalPath, typename Filters, typename Encoder>
        static file_save_dialog_details_ptr_type create_file_save_dialog(
            TETENGO2_STDALT_MAYBE_UNUSED AbstractWindow& parent,
            TETENGO2_STDALT_MAYBE_UNUSED String title,
            TETENGO2_STDALT_MAYBE_UNUSED const OptionalPath& path,
            TETENGO2_STDALT_MAYBE_UNUSED const Filters& filters,
            TETENGO2_STDALT_MAYBE_UNUSED const Encoder& encoder)
        {
            return std::make_unique<file_save_dialog_details_type>();
        }

        /*!
            \brief Shows a file save dialog and return a path.

            \tparam Encoder An encoder type.

            \param dialog  A file save dialog.
            \param encoder An encoder.

            \return The path.

            \throw std::system_error When the file save dialog cannot be shown.
        */
        template <typename Encoder>
        static tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path> show_file_save_dialog(
            TETENGO2_STDALT_MAYBE_UNUSED file_save_dialog_details_type& dialog,
            TETENGO2_STDALT_MAYBE_UNUSED const Encoder& encoder)
        {
            tetengo2::stdalt::filesystem::path file_name{ tetengo2::stdalt::filesystem::path::string_type{
                TETENGO2_TEXT("file_save_dialog") } };
            return tetengo2::stdalt::make_optional(tetengo2::stdalt::filesystem::temp_directory_path() / file_name);
        }

        /*!
            \brief Creates a font dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam OptionalFont   An optional font type.
            \tparam Encoder        An encoder type.

            \param parent  A parent window.
            \param font    A font.
            \param encoder An encoder.

            \return A unique pointer to a font dialog.

            \throw std::system_error When the font dialog cannot be created.
        */
        template <typename AbstractWindow, typename OptionalFont, typename Encoder>
        static font_dialog_details_ptr_type create_font_dialog(
            TETENGO2_STDALT_MAYBE_UNUSED AbstractWindow& parent,
            TETENGO2_STDALT_MAYBE_UNUSED const OptionalFont& font,
            TETENGO2_STDALT_MAYBE_UNUSED const Encoder& encoder)
        {
            return std::make_unique<font_dialog_details_type>();
        }

        /*!
            \brief Shows a font dialog and return a font.

            \tparam Font    A font type.
            \tparam Encoder An encoder type.

            \param dialog  A font dialog.
            \param encoder An encoder.

            \return The font.

            \throw std::system_error When the font dialog cannot be shown.
        */
        template <typename Font, typename Encoder>
        static tetengo2::stdalt::optional<Font> show_font_dialog(
            TETENGO2_STDALT_MAYBE_UNUSED font_dialog_details_type& dialog,
            TETENGO2_STDALT_MAYBE_UNUSED const Encoder& encoder)
        {
            return tetengo2::stdalt::make_optional(
                Font{ typename Font::string_type{ TETENGO2_TEXT("font_dialog_font") }, 42, false, true, false, true });
        }

        /*!
            \brief Creates a color dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam OptionalColor  An optional color type.

            \param parent A parent window.
            \param color  A color.

            \return A unique pointer to a color dialog.

            \throw std::system_error When the color dialog cannot be created.
        */
        template <typename AbstractWindow, typename OptionalColor>
        static color_dialog_details_ptr_type create_color_dialog(
            TETENGO2_STDALT_MAYBE_UNUSED AbstractWindow& parent,
            TETENGO2_STDALT_MAYBE_UNUSED const OptionalColor& color)
        {
            return std::make_unique<color_dialog_details_type>();
        }

        /*!
            \brief Shows a color dialog and return a font.

            \tparam Color A color type.

            \param dialog A color dialog.

            \return The color.

            \throw std::system_error When the color dialog cannot be shown.
        */
        template <typename Color>
        static tetengo2::stdalt::optional<Color>
        show_color_dialog(TETENGO2_STDALT_MAYBE_UNUSED color_dialog_details_type& dialog)
        {
            return tetengo2::stdalt::make_optional(Color{ 0xAB, 0xCD, 0xEF });
        }
    };
}


#endif
