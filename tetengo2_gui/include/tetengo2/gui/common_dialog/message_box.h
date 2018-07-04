/*! \file
    \brief The definition of tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H)
#define TETENGO2_GUI_COMMONDIALOG_MESSAGEBOX_H

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/widget/abstract_window.h>
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
            static button_style ok(const bool cancellable);

            /*!
                \brief Makes an OK button style with a custom label.

                \param cancellable     Whether the message box is cancellable.
                \param ok_button_label An OK button label.

                \return A button style.
            */
            static button_style ok(const bool cancellable, string_type ok_button_label);

            /*!
                \brief Makes a Yes and No button style with standard labels.

                \param cancellable Whether the message box is cancellable.

                \return A button style.
            */
            static button_style yes_no(const bool cancellable);

            /*!
                \brief Makes a OK button style with a custom label.

                \param cancellable      Whether the message box is cancellable.
                \param yes_button_label A Yes button label.
                \param no_button_label  A No button label.

                \return A button style.
            */
            static button_style
            yes_no(const bool cancellable, string_type yes_button_label, string_type no_button_label);


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
        \brief The class template for a message box.

        \tparam CommonDialogDetails A detail implementation type of common dialogs.
        \tparam WidgetDetailsTraits A detail implementation type traits of a widget.
        \tparam MenuDetails         A detail implementation type of a menu.
    */
    template <typename CommonDialogDetails, typename WidgetDetailsTraits, typename MenuDetails>
    class message_box : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The common dialog details type.
        using common_dialog_details_type = CommonDialogDetails;

        //! The details type.
        using details_type = typename common_dialog_details_type::message_box_details_type;

        //! The detail implementaiton pointer type;
        using details_ptr_type = typename common_dialog_details_type::message_box_details_ptr_type;

        //! The widget details traits type.
        using widget_details_traits_type = WidgetDetailsTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The abstract window type.
        using abstract_window_type = gui::widget::abstract_window<
            typename widget_details_traits_type::widget_details_type,
            typename widget_details_traits_type::drawing_details_type,
            typename widget_details_traits_type::scroll_details_type,
            typename widget_details_traits_type::message_handler_details_type,
            menu_details_type>;

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
            const icon_style_type    icon_style)
        : m_p_details{ common_dialog_details_type::create_message_box(
              parent,
              std::move(title),
              std::move(main_content),
              std::move(sub_content),
              button_style.cancellable(),
              to_details_button_style(button_style.style()),
              to_details_icon_style(icon_style),
              button_style.ok_button_label(),
              button_style.yes_no_button_labels()) }
        {}


        // functions

        /*!
            \brief Shows the dialog as model.

            \return The selected button id.
        */
        button_id_type do_modal()
        {
            return to_button_id(common_dialog_details_type::show_message_box(*m_p_details));
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

        static typename common_dialog_details_type::message_box_button_style_type
        to_details_button_style(const typename button_style_type::style_type style)
        {
            switch (style)
            {
            case button_style_type::style_type::ok:
                return common_dialog_details_type::message_box_button_style_type::ok;
            case button_style_type::style_type::yes_no:
                return common_dialog_details_type::message_box_button_style_type::yes_no;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid button style." }));
            }
        }

        static typename common_dialog_details_type::message_box_icon_style_type
        to_details_icon_style(const icon_style_type style)
        {
            switch (style)
            {
            case icon_style_type::error:
                return common_dialog_details_type::message_box_icon_style_type::error;
            case icon_style_type::warning:
                return common_dialog_details_type::message_box_icon_style_type::warning;
            case icon_style_type::information:
                return common_dialog_details_type::message_box_icon_style_type::information;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid icon style." }));
            }
        }

        static button_id_type
        to_button_id(const typename common_dialog_details_type::message_box_button_id_type details_button_id)
        {
            switch (details_button_id)
            {
            case common_dialog_details_type::message_box_button_id_type::ok:
                return button_id_type::ok;
            case common_dialog_details_type::message_box_button_id_type::yes:
                return button_id_type::yes;
            case common_dialog_details_type::message_box_button_id_type::no:
                return button_id_type::no;
            case common_dialog_details_type::message_box_button_id_type::cancel:
                return button_id_type::cancel;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid button ID."));
            }
        }


        // variables

        details_ptr_type m_p_details;
    };
}


#endif
