/*! \file
    \brief The definition of tetengo2::detail::stub::common_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_COMMONDIALOG_H)
#define TETENGO2_DETAIL_STUB_COMMONDIALOG_H

//#include <memory>

#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of dialogs.
    */
    class common_dialog
    {
    public:
        // types

        //! The message box button style type.
        enum message_box_button_style_type
        {
            message_box_button_style_ok,     //!< With OK button.
            message_box_button_style_yes_no, //!< With Yes and No button.
        };

        //! The message box icon style type.
        enum message_box_icon_style_type
        {
            message_box_icon_style_error,       //!< Error.
            message_box_icon_style_warning,     //!< Warning.
            message_box_icon_style_information, //!< Information.
        };

        //! The message box button ID type.
        enum message_box_button_id_type
        {
            message_box_button_ok,     //!< OK button.
            message_box_button_yes,    //!< Yes button.
            message_box_button_no,     //!< No button.
            message_box_button_cancel, //!< Cancel button.
        };

        //! The message box details type.
        struct message_box_details_type {};

        //! The message box details pointer type.
        typedef
            std::unique_ptr<message_box_details_type>
            message_box_details_ptr_type;

        //! The file open dialog details type.
        struct file_open_dialog_details_type {};

        //! The file open dialog details pointer type.
        typedef
            std::unique_ptr<file_open_dialog_details_type>
            file_open_dialog_details_ptr_type;

        
        // static functions

        /*!
            \brief Creates a message box.

            \tparam Widget  A widget type.
            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param parent       A parent widget.
            \param title        A title.
            \param main_content A main content.
            \param sub_content  A sub content.
            \param cancellable  Whether the message box is cancellable.
            \param button_style A button style.
            \param icon_style   An icon style.
            \param encoder      An encoder.

            \return A unique pointer to a message box.
        */
        template <typename Widget, typename String, typename Encoder>
        static message_box_details_ptr_type create_message_box(
            Widget&                             parent,
            String&&                            title,
            String&&                            instruction,
            String&&                            details,
            const bool                          cancellable,
            const message_box_button_style_type button_style,
            const message_box_icon_style_type   icon_style,
            const Encoder&                      encoder
        )
        {
            return make_unique<message_box_details_type>();
        }

        /*!
            \brief Shows a message box and return a button id.

            \param message_box A message box.

            \return The path.
        */
        static message_box_button_id_type show_message_box(
            message_box_details_type& message_box
        )
        {
            return message_box_button_cancel;
        }

        /*!
            \brief Creates a file open dialog.

            \tparam Widget  A widget type.
            \tparam String  A string type.
            \tparam Filters A filters type.
            \tparam Encoder An encoder type.

            \param parent  A parent widget.
            \param title   A title.
            \param filters A file filters.
                           Each element is a pair of a label and a file
                           pattern.
            \param encoder An encoder.

            \return A unique pointer to a file open dialog.
        */
        template <
            typename Widget,
            typename String,
            typename Filters,
            typename Encoder
        >
        static file_open_dialog_details_ptr_type create_file_open_dialog(
            Widget&        parent,
            String&&       title,
            Filters&&      filters,
            const Encoder& encoder
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
        */
        template <typename Path, typename Encoder>
        static Path show_file_open_dialog(
            file_open_dialog_details_type& dialog,
            const Encoder&                 encoder
        )
        {
            return Path(L"hoge.txt");
        }


    };


}}}


#endif
