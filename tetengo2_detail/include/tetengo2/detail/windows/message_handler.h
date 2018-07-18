/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H

#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/base/message_handler.h>

namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a message handler.
    */
    class message_handler : public base::message_handler
    {
    public:
        // types

        //! The message handler type.
        using message_handler_type = base::message_handler::message_handler_type;

        //! The message handler map type.
        using message_handler_map_type = base::message_handler::message_handler_map_type;

        //! The Windows message handler type.
        struct windows_message_handler_type : public message_handler_type
        {
            using function_type = std::function<void(std::uintptr_t, std::intptr_t)>;

            function_type function;

            explicit windows_message_handler_type(function_type&& function) : function{ std::move(function) } {}

            virtual ~windows_message_handler_type();
        };

        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const message_handler& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~message_handler();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        message_handler();


        // virtual functions

        virtual message_handler_map_type make_abstract_window_message_handler_map_impl(
            gui::widget::abstract_window& abstract_window,
            message_handler_map_type&&    initial_map) const override;

        virtual message_handler_map_type make_button_message_handler_map_impl(
            gui::widget::button&       button,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_control_message_handler_map_impl(
            gui::widget::control&      control,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_custom_control_message_handler_map_impl(
            gui::widget::custom_control& custom_control,
            message_handler_map_type&&   initial_map) const override;

        virtual message_handler_map_type make_dialog_message_handler_map_impl(
            gui::widget::dialog&       dialog,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_dropdown_box_message_handler_map_impl(
            gui::widget::dropdown_box& dropdown_box,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_image_message_handler_map_impl(
            gui::widget::image&        image,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_label_message_handler_map_impl(
            gui::widget::label&        label,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_list_box_message_handler_map_impl(
            gui::widget::list_box&     list_box,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_picture_box_message_handler_map_impl(
            gui::widget::picture_box&  picture_box,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_progress_bar_message_handler_map_impl(
            gui::widget::progress_bar& progress_bar,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_text_box_message_handler_map_impl(
            gui::widget::text_box&     text_box,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_widget_message_handler_map_impl(
            gui::widget::widget&       widget,
            message_handler_map_type&& initial_map) const override;

        virtual message_handler_map_type make_window_message_handler_map_impl(
            gui::widget::window&       window,
            message_handler_map_type&& initial_map) const override;
    };
}


#endif
