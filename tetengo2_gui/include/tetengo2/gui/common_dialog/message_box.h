/*! \file
    \brief The definition of tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H)
#define TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::common_dialog {
    namespace message_box_style {
        /*!
            \brief The class for a button style.
        */
        class button_style
        {
        public:
            // types

            //! The string type.
            using string_type = tetengo2::type_list::string_type;

            //! The style type.
            enum class style_type
            {
                ok, //!< With OK button.
                yes_no, //!< With Yes and No buttons.
            };


            // static functions

            /*!
                \brief Makes a OK button style with a standard label.

                \param cancellable Whether the message box is cancellable.

                \return A button style.
            */
            static button_style ok(bool cancellable);

            /*!
                \brief Makes an OK button style with a custom label.

                \param cancellable     Whether the message box is cancellable.
                \param ok_button_label An OK button label.

                \return A button style.
            */
            static button_style ok(bool cancellable, string_type ok_button_label);

            /*!
                \brief Makes a Yes and No button style with standard labels.

                \param cancellable Whether the message box is cancellable.

                \return A button style.
            */
            static button_style yes_no(bool cancellable);

            /*!
                \brief Makes a OK button style with a custom label.

                \param cancellable      Whether the message box is cancellable.
                \param yes_button_label A Yes button label.
                \param no_button_label  A No button label.

                \return A button style.
            */
            static button_style yes_no(bool cancellable, string_type yes_button_label, string_type no_button_label);


            // constructors and destructor

            /*!
                \brief Copies a button style.

                \param another Another button style.
            */
            button_style(const button_style& another);

            /*!
                \brief Moves a button style.

                \param another Another button style.
            */
            button_style(button_style&& another);

            /*!
                \brief Destroys the button style.
            */
            ~button_style();


            // functions

            /*!
                \brief Returns the style.

                \return The style.
            */
            style_type style() const;

            /*!
                \brief Returns whether the message box is cancellable.

                \retval true  When the message box is cancellable.
                \retval false Otherwise.
            */
            bool cancellable() const;

            /*!
                \brief Returns the OK button label.

                \return The OK button label.
            */
            const tetengo2::stdalt::optional<string_type>& ok_button_label() const;

            /*!
                \brief Returns the Yes and No button labels.

                \return The Yes button labels.
            */
            const tetengo2::stdalt::optional<std::pair<string_type, string_type>>& yes_no_button_labels() const;


        private:
            // types

            class impl;


            // variables

            std::unique_ptr<impl> m_p_impl;


            // constructors

            button_style(
                const style_type                                                       style,
                const bool                                                             cancellable,
                const tetengo2::stdalt::optional<string_type>&                         ok_button_label,
                const tetengo2::stdalt::optional<std::pair<string_type, string_type>>& yes_no_button_labels);
        };
    }


    /*!
        \brief The class for a message box.
    */
    class message_box : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The abstract window type.
        using abstract_window_type = gui::widget::abstract_window;

        //! The button style type.
        using button_style_type = message_box_style::button_style;

        //! The icon style type.
        enum class icon_style_type
        {
            error, //!< Error.
            warning, //!< Warning.
            information, //!< Information.
        };

        //! The button ID type.
        enum class button_id_type
        {
            ok, //!< OK button.
            yes, //!< Yes button.
            no, //!< No button.
            cancel, //!< Cancel button.
        };

        //! The details type.
        using details_type = detail::base::common_dialog::message_box_details_type;


        // constructors and destructor

        /*!
            \brief Creates a message box.

            \param parent       A parent window.
            \param title        A title.
            \param main_content A main content.
            \param sub_content  A sub content.
            \param button_style A button style.
            \param icon_style   An icon style.
        */
        message_box(
            abstract_window_type&    parent,
            string_type              title,
            string_type              main_content,
            string_type              sub_content,
            const button_style_type& button_style,
            const icon_style_type    icon_style);

        /*!
            \brief Destroys the message box.
        */
        ~message_box();


        // functions

        /*!
            \brief Shows the dialog as model.

            \return The selected button id.
        */
        button_id_type do_modal();

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        const details_type& details() const;

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.
        */
        details_type& details();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
