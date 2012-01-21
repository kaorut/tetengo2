/*! \file
    \brief The definition of tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H)
#define TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H

#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.text.h"


namespace tetengo2 { namespace gui { namespace common_dialog
{
    /*!
        \brief The class template for a message box.

        \tparam Widget              A widget type.
        \tparam String              A string type.
        \tparam Encoder             An encoder type.
        \tparam CommonDialogDetails A detail implementation type of common
                                    dialogs.
    */
    template <
        typename Widget,
        typename String,
        typename Encoder,
        typename CommonDialogDetails
    >
    class message_box : private boost::noncopyable
    {
    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The detail implementation type of common dialogs.
        typedef CommonDialogDetails common_dialog_details_type;

        //! The detail implementation type.
        typedef
            typename common_dialog_details_type::message_box_details_type
            details_type;

        //! The detail implementaiton pointer type;
        typedef
            typename common_dialog_details_type::message_box_details_ptr_type
            details_ptr_type;

        //! The button style type.
        enum button_style_type
        {
            button_style_ok,            //!< With OK button.
            button_style_ok_cancel,     //!< With OK and Cancel button.
            button_style_yes_no_cancel, //!< With Yes, No and Cancel button.
        };

        //! The icon style type.
        enum icon_style_type
        {
            icon_style_error,       //!< Error.
            icon_style_warning,     //!< Warning.
            icon_style_information, //!< Information.
        };

        //! The button ID type.
        enum button_id_type
        {
            button_ok,     //!< OK button.
            button_yes,    //!< Yes button.
            button_no,     //!< No button.
            button_cancel, //!< Cancel button.
        };


        // constructors and destructor

        /*!
            \brief Creates a message box.

            \tparam S A string type.

            \param parent       A parent widget.
            \param title        A title.
            \param main_content A main content.
            \param sub_content  A sub content.
            \param button_style A button style.
            \param icon_style   An icon style.
        */
        template <typename S>
        message_box(
            widget_type&            parent,
            S&&                     title,
            S&&                     main_content,
            S&&                     sub_content,
            const button_style_type button_style,
            const icon_style_type   icon_style
        )
        :
        m_p_details(
            common_dialog_details_type::create_message_box(
                parent,
                std::forward<S>(title),
                std::forward<S>(main_content),
                std::forward<S>(sub_content),
                to_details_button_style(button_style),
                to_details_icon_style(icon_style),
                encoder()
            )
        )
        {}


        // functions

        /*!
            \brief Shows the dialog as model.

            \return The selected button id.
        */
        button_id_type do_modal()
        {
            return to_button_id(
                common_dialog_details_type::show_message_box(*m_p_details)
            );
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details()
        const
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

        static typename common_dialog_details_type::message_box_button_style_type
        to_details_button_style(const button_style_type style)
        {
            switch (style)
            {
            case button_style_ok:
                return
                    common_dialog_details_type::message_box_button_style_ok;
            case button_style_ok_cancel:
                return
                    common_dialog_details_type::message_box_button_style_ok_cancel;
            case button_style_yes_no_cancel:
                return
                    common_dialog_details_type::message_box_button_style_yes_no_cancel;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Invalid button style.")
                );
            }
        }

        static typename common_dialog_details_type::message_box_icon_style_type
        to_details_icon_style(const icon_style_type style)
        {
            switch (style)
            {
            case icon_style_error:
                return
                    common_dialog_details_type::message_box_icon_style_error;
            case icon_style_warning:
                return
                    common_dialog_details_type::message_box_icon_style_warning;
            case icon_style_information:
                return
                    common_dialog_details_type::message_box_icon_style_information;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Invalid icon style.")
                );
            }
        }

        static button_id_type to_button_id(
            const typename common_dialog_details_type::message_box_button_id_type
            details_button_id
        )
        {
            switch (details_button_id)
            {
            case common_dialog_details_type::message_box_button_ok:
                return button_ok;
            case common_dialog_details_type::message_box_button_yes:
                return button_yes;
            case common_dialog_details_type::message_box_button_no:
                return button_no;
            case common_dialog_details_type::message_box_button_cancel:
                return button_cancel;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Invalid button ID.")
                );
            }
        }

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // variables

        details_ptr_type m_p_details;


    };


}}}


#endif
