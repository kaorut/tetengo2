/*! \file
    \brief The definition of tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H)
#define TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H

#include <cassert>
#include <stdexcept>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.text.h"


namespace tetengo2 { namespace gui { namespace common_dialog
{
    namespace message_box_style
    {
        /*!
            \brief The class template for a button style.

            \tparam String A string type.
        */
        template <typename String>
        class button_style
        {
        public:
            // types

            //! The string type.
            typedef String string_type;

            //! The style type.
            enum style_type
            {
                style_ok,     //!< With OK button.
                style_yes_no, //!< With Yes and No buttons.
            };


            // static functions

            /*!
                \brief Makes a OK button style with a standard label.

                \param cancellable Whether the message box is cancellable.

                \return A button style.
            */
            static button_style ok(const bool cancellable)
            {
                return button_style(
                    style_ok, cancellable, boost::none, boost::none
                );
            }

            /*!
                \brief Makes an OK button style with a custom label.

                \tparam S A string type.

                \param cancellable     Whether the message box is cancellable.
                \param ok_button_label An OK button label.

                \return A button style.
            */
            template <typename S>
            static button_style ok(
                const bool cancellable,
                S&&        ok_button_label
            )
            {
                return button_style(
                    style_ok,
                    cancellable,
                    boost::make_optional<string_type>(
                        std::forward<S>(ok_button_label)
                    ),
                    boost::none
                );
            }

            /*!
                \brief Makes a Yes and No button style with standard labels.

                \param cancellable Whether the message box is cancellable.

                \return A button style.
            */
            static button_style yes_no(const bool cancellable)
            {
                return button_style(
                    style_yes_no, cancellable, boost::none, boost::none
                );
            }

            /*!
                \brief Makes a OK button style with a custom label.

                \tparam S1 A string type #1.
                \tparam S2 A string type #2.

                \param cancellable      Whether the message box is
                                        cancellable.
                \param yes_button_label A Yes button label.
                \param no_button_label  A No button label.

                \return A button style.
            */
            template <typename S1, typename S2>
            static button_style yes_no(
                const bool cancellable,
                S1&&       yes_button_label,
                S2&&       no_button_label
            )
            {
                return button_style(
                    style_yes_no,
                    cancellable,
                    boost::none,
                    boost::make_optional<std::pair<string_type, string_type>>(
                        std::pair<string_type, string_type>(
                            std::forward<S1>(yes_button_label),
                            std::forward<S2>(no_button_label)
                        )
                    )
                );
            }


            // functions

            /*!
                \brief Returns the style.

                \return The style.
            */
            style_type style()
            const
            {
                return m_style;
            }

            /*!
                \brief Returns whether the message box is cancellable.

                \retval true  When the message box is cancellable.
                \retval false Otherwise.
            */
            bool cancellable()
            const
            {
                return m_cancellable;
            }

            /*!
                \brief Returns the OK button label.

                \return The OK button label.
            */
            const boost::optional<string_type>& ok_button_label()
            const
            {
                return m_ok_button_label;
            }

            /*!
                \brief Returns the Yes and No button labels.

                \return The Yes button labels.
            */
            const boost::optional<std::pair<string_type, string_type>>&
            yes_no_button_labels()
            const
            {
                return m_yes_no_button_labels;
            }


        private:
            // constructors

            button_style(
                const style_type&                   style,
                const bool                          cancellable,
                const boost::optional<string_type>& ok_button_label,
                const boost::optional<std::pair<string_type, string_type>>&
                                                    yes_no_button_labels
            )
            :
            m_style(style),
            m_cancellable(cancellable),
            m_ok_button_label(ok_button_label),
            m_yes_no_button_labels(yes_no_button_labels)
            {}


            // variables

            style_type m_style;

            bool m_cancellable;

            boost::optional<string_type> m_ok_button_label;

            boost::optional<std::pair<string_type, string_type>>
            m_yes_no_button_labels;


        };



    }


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
        typedef
            message_box_style::button_style<string_type> button_style_type;

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

            \tparam S1 A string type #1.
            \tparam S2 A string type #2.
            \tparam S3 A string type #3.

            \param parent       A parent widget.
            \param title        A title.
            \param main_content A main content.
            \param sub_content  A sub content.
            \param button_style A button style.
            \param icon_style   An icon style.
        */
        template <typename S1, typename S2, typename S3>
        message_box(
            widget_type&             parent,
            S1&&                     title,
            S2&&                     main_content,
            S3&&                     sub_content,
            const button_style_type& button_style,
            const icon_style_type    icon_style
        )
        :
        m_p_details(
            common_dialog_details_type::create_message_box(
                parent,
                std::forward<S1>(title),
                std::forward<S2>(main_content),
                std::forward<S3>(sub_content),
                button_style.cancellable(),
                to_details_button_style(button_style.style()),
                to_details_icon_style(icon_style),
                button_style.ok_button_label(),
                button_style.yes_no_button_labels(),
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
        to_details_button_style(
            const typename button_style_type::style_type style
        )
        {
            switch (style)
            {
            case button_style_type::style_ok:
                return
                    common_dialog_details_type::message_box_button_style_ok;
            case button_style_type::style_yes_no:
                return
                    common_dialog_details_type::message_box_button_style_yes_no;
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
