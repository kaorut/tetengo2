/*! \file
    \brief The definition of tetengo2::detail::stub::common_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_COMMONDIALOG_H)
#define TETENGO2_DETAIL_STUB_COMMONDIALOG_H

//#include <memory>
//#include <utility>
#include <system_error>

#include <boost/filesystem.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include "tetengo2.unique.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog : private boost::noncopyable
    {
    public:
        // types

        //! The message box button style type.
        struct message_box_button_style_type { enum enum_t //!< Scoped enum.
        {
            ok,     //!< With OK button.
            yes_no, //!< With Yes and No buttons.
        };};

        //! The message box icon style type.
        struct message_box_icon_style_type { enum enum_t //!< Scoped enum.
        {
            error,       //!< Error.
            warning,     //!< Warning.
            information, //!< Information.
        };};

        //! The message box button ID type.
        struct message_box_button_id_type { enum enum_t //!< Scoped enum.
        {
            ok,     //!< OK button.
            yes,    //!< Yes button.
            no,     //!< No button.
            cancel, //!< Cancel button.
        };};

        //! The message box details type.
        struct message_box_details_type {};

        //! The message box details pointer type.
        typedef
            std::unique_ptr<message_box_details_type>
            message_box_details_ptr_type;

        //! The file open dialog details type.
        struct file_open_dialog_details_type {};

        //! The file open dialog details pointer type.
        typedef std::unique_ptr<file_open_dialog_details_type> file_open_dialog_details_ptr_type;

        //! The file save dialog details type.
        struct file_save_dialog_details_type {};

        //! The file save dialog details pointer type.
        typedef std::unique_ptr<file_save_dialog_details_type> file_save_dialog_details_ptr_type;

        //! The font dialog details type.
        struct font_dialog_details_type {};

        //! The font dialog details pointer type.
        typedef std::unique_ptr<font_dialog_details_type> font_dialog_details_ptr_type;

        //! The color dialog details type.
        struct color_dialog_details_type {};

        //! The color dialog details pointer type.
        typedef std::unique_ptr<color_dialog_details_type> color_dialog_details_ptr_type;

        
        // static functions

        /*!
            \brief Creates a message box.

            \tparam AbstractWindow An abstract window type.
            \tparam String1        A string type #1.
            \tparam String2        A string type #2.
            \tparam String3        A string type #3.
            \tparam String4        A string type #4.
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
        template <
            typename AbstractWindow,
            typename String1,
            typename String2,
            typename String3,
            typename String4,
            typename Encoder
        >
        static message_box_details_ptr_type create_message_box(
            AbstractWindow&                                      parent,
            String1&&                                            title,
            String2&&                                            main_content,
            String3&&                                            sub_content,
            const bool                                           cancellable,
            const typename message_box_button_style_type::enum_t button_style,
            const typename message_box_icon_style_type::enum_t   icon_style,
            const boost::optional<String4>&                      custom_ok_button_label,
            const boost::optional<std::pair<String4, String4>>&  custom_yes_no_button_labels,
            const Encoder&                                       encoder
        )
        {
            return make_unique<message_box_details_type>();
        }

        /*!
            \brief Shows a message box and return a button id.

            \param message_box A message box.

            \return The path.

            \throw std::system_error When the message box cannot be shown.
        */
        static message_box_button_id_type::enum_t show_message_box(message_box_details_type& message_box)
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
            AbstractWindow& parent,
            String&&        title,
            Filters&&       filters,
            const Encoder&  encoder
        )
        {
            return make_unique<file_open_dialog_details_type>();
        }

        /*!
            \brief Shows a file open dialog and return a path.

            \tparam Path    A path type.
            \tparam Encoder An encoder type.

            \param dialog  A file open dialog.
            \param encoder An encoder.

            \return The path.

            \throw std::system_error When the file open dialog cannot be shown.
        */
        template <typename Path, typename Encoder>
        static boost::optional<Path> show_file_open_dialog(
            file_open_dialog_details_type& dialog,
            const Encoder&                 encoder
        )
        {
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
            AbstractWindow& parent,
            String&&        title,
            OptionalPath&&  path,
            Filters&&       filters,
            const Encoder&  encoder
        )
        {
            return make_unique<file_save_dialog_details_type>();
        }

        /*!
            \brief Shows a file save dialog and return a path.

            \tparam Path    A path type.
            \tparam Encoder An encoder type.

            \param dialog  A file save dialog.
            \param encoder An encoder.

            \return The path.

            \throw std::system_error When the file save dialog cannot be shown.
        */
        template <typename Path, typename Encoder>
        static boost::optional<Path> show_file_save_dialog(
            file_save_dialog_details_type& dialog,
            const Encoder&                 encoder
        )
        {
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
        static font_dialog_details_ptr_type create_font_dialog(
            AbstractWindow& parent,
            OptionalFont&&  font,
            const Encoder&  encoder
        )
        {
            return make_unique<font_dialog_details_type>();
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
            return
                boost::make_optional(
                    Font(typename Font::string_type(TETENGO2_TEXT("font_dialog_font")), 42, false, true, false, true)
                );
        }

        /*!
            \brief Creates a color dialog.

            \tparam AbstractWindow An abstract window type.
            \tparam OptionalColor  An optional color type.
            \tparam Encoder        An encoder type.

            \param parent  A parent window.
            \param color   A color.
            \param encoder An encoder.

            \return A unique pointer to a color dialog.

            \throw std::system_error When the color dialog cannot be created.
        */
        template <typename AbstractWindow, typename OptionalColor, typename Encoder>
        static color_dialog_details_ptr_type create_color_dialog(
            AbstractWindow& parent,
            OptionalColor&& color,
            const Encoder&  encoder
        )
        {
            return make_unique<color_dialog_details_type>();
        }

        /*!
            \brief Shows a color dialog and return a font.

            \tparam Color   A color type.
            \tparam Encoder An encoder type.

            \param dialog  A color dialog.
            \param encoder An encoder.

            \return The color.

            \throw std::system_error When the color dialog cannot be shown.
        */
        template <typename Color, typename Encoder>
        static boost::optional<Color> show_color_dialog(color_dialog_details_type& dialog, const Encoder& encoder)
        {
            return boost::make_optional(Color(0xAB, 0xCD, 0xEF));
        }


    };


}}}


#endif
