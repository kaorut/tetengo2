/*! \file
    \brief The definition of tetengo2::detail::stub::common_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_COMMONDIALOG_H)
#define TETENGO2_DETAIL_STUB_COMMONDIALOG_H

#include <memory>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace tetengo2 { namespace detail { namespace stub {
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
            AbstractWindow&                            parent,
            String                                     title,
            String                                     main_content,
            String                                     sub_content,
            const bool                                 cancellable,
            const message_box_button_style_type        button_style,
            const message_box_icon_style_type          icon_style,
            boost::optional<String>                    custom_ok_button_label,
            boost::optional<std::pair<String, String>> custom_yes_no_button_labels,
            const Encoder&                             encoder)
        {
            boost::ignore_unused(
                parent,
                title,
                main_content,
                sub_content,
                cancellable,
                button_style,
                icon_style,
                custom_ok_button_label,
                custom_yes_no_button_labels,
                encoder);

            return stdalt::make_unique<message_box_details_type>();
        }

        /*!
            \brief Shows a message box and return a button id.

            \param message_box A message box.

            \return The path.

            \throw std::system_error When the message box cannot be shown.
        */
        static message_box_button_id_type show_message_box(message_box_details_type& message_box)
        {
            boost::ignore_unused(message_box);

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
        static file_open_dialog_details_ptr_type
        create_file_open_dialog(AbstractWindow& parent, String title, const Filters& filters, const Encoder& encoder)
        {
            boost::ignore_unused(parent, title, filters, encoder);

            return stdalt::make_unique<file_open_dialog_details_type>();
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
        static boost::optional<boost::filesystem::path>
        show_file_open_dialog(file_open_dialog_details_type& dialog, const Encoder& encoder)
        {
            boost::ignore_unused(dialog, encoder);

            return boost::make_optional(boost::filesystem::temp_directory_path() / boost::filesystem::unique_path());
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
            AbstractWindow&     parent,
            String              title,
            const OptionalPath& path,
            const Filters&      filters,
            const Encoder&      encoder)
        {
            boost::ignore_unused(parent, title, path, filters, encoder);

            return stdalt::make_unique<file_save_dialog_details_type>();
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
        static boost::optional<boost::filesystem::path>
        show_file_save_dialog(file_save_dialog_details_type& dialog, const Encoder& encoder)
        {
            boost::ignore_unused(dialog, encoder);

            return boost::make_optional(boost::filesystem::temp_directory_path() / boost::filesystem::unique_path());
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
        static font_dialog_details_ptr_type
        create_font_dialog(AbstractWindow& parent, const OptionalFont& font, const Encoder& encoder)
        {
            boost::ignore_unused(parent, font, encoder);
            return stdalt::make_unique<font_dialog_details_type>();
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
        static boost::optional<Font> show_font_dialog(font_dialog_details_type& dialog, const Encoder& encoder)
        {
            boost::ignore_unused(dialog, encoder);

            return boost::make_optional(
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
        static color_dialog_details_ptr_type create_color_dialog(AbstractWindow& parent, const OptionalColor& color)
        {
            boost::ignore_unused(parent, color);

            return stdalt::make_unique<color_dialog_details_type>();
        }

        /*!
            \brief Shows a color dialog and return a font.

            \tparam Color A color type.

            \param dialog A color dialog.

            \return The color.

            \throw std::system_error When the color dialog cannot be shown.
        */
        template <typename Color>
        static boost::optional<Color> show_color_dialog(color_dialog_details_type& dialog)
        {
            boost::ignore_unused(dialog);

            return boost::make_optional(Color{ 0xAB, 0xCD, 0xEF });
        }
    };


}}}


#endif
