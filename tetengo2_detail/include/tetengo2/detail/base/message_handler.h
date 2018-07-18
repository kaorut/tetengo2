/*! \file
    \brief The definition of tetengo2::detail::base::message_handler.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_BASE_MESSAGEHANDLER_H

#include <memory>
#include <unordered_map>
#include <vector>

#include <boost/core/noncopyable.hpp>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
    class button;
    class control;
    class custom_control;
    class dialog;
    class dropdown_box;
    class image;
    class label;
    class list_box;
    class picture_box;
    class text_box;
    class widget;
    class window;
}}}


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a message handler.
    */
    class message_handler : private boost::noncopyable
    {
    public:
        // types

        //! The message handler type.
        struct message_handler_type : private boost::noncopyable
        {
            virtual ~message_handler_type();
        };

        //! The message handler map type.
        using message_handler_map_type = std::unordered_map<int, std::vector<std::unique_ptr<message_handler_type>>>;


        // constructors and destructor

        virtual ~message_handler();


        // functions

        /*!
            \brief Make a message handler map for an abstract window.

            \param abstract_window An abstract window.
            \param initial_map     An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type make_abstract_window_message_handler_map(
            gui::widget::abstract_window& abstract_window,
            message_handler_map_type&&    initial_map) const;

        /*!
            \brief Make a message handler map for a button.

            \param button      A button.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type
        make_button_message_handler_map(gui::widget ::button& button, message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a control.

            \param control     A control.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type
        make_control_message_handler_map(gui::widget::control& control, message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a custom control.

            \param custom_control A custom control.
            \param initial_map    An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type make_custom_control_message_handler_map(
            gui::widget::custom_control& custom_control,
            message_handler_map_type&&   initial_map) const;

        /*!
            \brief Make a message handler map for a dialog.

            \param dialog      A dialog.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type
        make_dialog_message_handler_map(gui::widget::dialog& dialog, message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a dropdown box.

            \param dropdown_box A dropdown box.
            \param initial_map  An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type make_dropdown_box_message_handler_map(
            gui::widget::dropdown_box& dropdown_box,
            message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for an image.

            \param image       An image.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type
        make_image_message_handler_map(gui::widget::image& image, message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a label.

            \param label       A label.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type
        make_label_message_handler_map(gui::widget::label& label, message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a list box.

            \param list_box    A list box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type make_list_box_message_handler_map(
            gui::widget::list_box&     list_box,
            message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a picture box.

            \param picture_box A picture box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type make_picture_box_message_handler_map(
            gui::widget::picture_box&  picture_box,
            message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a text box.

            \param text_box    A text box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type make_text_box_message_handler_map(
            gui::widget::text_box&     text_box,
            message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a widget.

            \param widget      A widget.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type
        make_widget_message_handler_map(gui::widget::widget& widget, message_handler_map_type&& initial_map) const;

        /*!
            \brief Make a message handler map for a window.

            \param window      A window.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        message_handler_map_type
        make_window_message_handler_map(gui::widget::window& window, message_handler_map_type&& initial_map) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        message_handler();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual message_handler_map_type make_abstract_window_message_handler_map_impl(
            gui::widget::abstract_window& abstract_window,
            message_handler_map_type&&    initial_map) const = 0;

        virtual message_handler_map_type make_button_message_handler_map_impl(
            gui::widget ::button&      button,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_control_message_handler_map_impl(
            gui::widget::control&      control,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_custom_control_message_handler_map_impl(
            gui::widget::custom_control& custom_control,
            message_handler_map_type&&   initial_map) const = 0;

        virtual message_handler_map_type make_dialog_message_handler_map_impl(
            gui::widget::dialog&       dialog,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_dropdown_box_message_handler_map_impl(
            gui::widget::dropdown_box& dropdown_box,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_image_message_handler_map_impl(
            gui::widget::image&        image,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_label_message_handler_map_impl(
            gui::widget::label&        label,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_list_box_message_handler_map_impl(
            gui::widget::list_box&     list_box,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_picture_box_message_handler_map_impl(
            gui::widget::picture_box&  picture_box,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_text_box_message_handler_map_impl(
            gui::widget::text_box&     text_box,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_widget_message_handler_map_impl(
            gui::widget::widget&       widget,
            message_handler_map_type&& initial_map) const = 0;

        virtual message_handler_map_type make_window_message_handler_map_impl(
            gui::widget::window&       window,
            message_handler_map_type&& initial_map) const = 0;
    };
}


#endif
