/*! \file
    \brief The definition of tetengo2::detail::base::message_handler.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/message_handler.h>

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
    class progress_bar;
    class text_box;
    class widget;
    class window;
}}}


namespace tetengo2::detail::base {
    message_handler::message_handler_type::~message_handler_type() = default;


    class message_handler::impl : private boost::noncopyable
    {
    public:
        // types

        using message_handler_type = message_handler::message_handler_type;

        //! The message handler map type.
        using message_handler_map_type = message_handler::message_handler_map_type;


        // functions

        message_handler_map_type make_abstract_window_message_handler_map(
            gui::widget::abstract_window& abstract_window,
            message_handler_map_type&&    initial_map,
            const message_handler&        self) const
        {
            return self.make_abstract_window_message_handler_map_impl(abstract_window, std::move(initial_map));
        }

        message_handler_map_type make_button_message_handler_map(
            gui::widget::button&       button,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_button_message_handler_map_impl(button, std::move(initial_map));
        }

        message_handler_map_type make_control_message_handler_map(
            gui::widget::control&      control,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_control_message_handler_map_impl(control, std::move(initial_map));
        }

        message_handler_map_type make_custom_control_message_handler_map(
            gui::widget::custom_control& custom_control,
            message_handler_map_type&&   initial_map,
            const message_handler&       self) const
        {
            return self.make_custom_control_message_handler_map_impl(custom_control, std::move(initial_map));
        }

        message_handler_map_type make_dialog_message_handler_map(
            gui::widget::dialog&       dialog,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_dialog_message_handler_map_impl(dialog, std::move(initial_map));
        }

        message_handler_map_type make_dropdown_box_message_handler_map(
            gui::widget::dropdown_box& dropdown_box,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_dropdown_box_message_handler_map_impl(dropdown_box, std::move(initial_map));
        }

        message_handler_map_type make_image_message_handler_map(
            gui::widget::image&        image,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_image_message_handler_map_impl(image, std::move(initial_map));
        }

        message_handler_map_type make_label_message_handler_map(
            gui::widget::label&        label,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_label_message_handler_map_impl(label, std::move(initial_map));
        }

        message_handler_map_type make_list_box_message_handler_map(
            gui::widget::list_box&     list_box,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_list_box_message_handler_map_impl(list_box, std::move(initial_map));
        }

        message_handler_map_type make_picture_box_message_handler_map(
            gui::widget::picture_box&  picture_box,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_picture_box_message_handler_map_impl(picture_box, std::move(initial_map));
        }

        message_handler_map_type make_progress_bar_message_handler_map(
            gui::widget::progress_bar& progress_bar,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_progress_bar_message_handler_map_impl(progress_bar, std::move(initial_map));
        }

        message_handler_map_type make_text_box_message_handler_map(
            gui::widget::text_box&     text_box,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_text_box_message_handler_map_impl(text_box, std::move(initial_map));
        }

        message_handler_map_type make_widget_message_handler_map(
            gui::widget::widget&       widget,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_widget_message_handler_map_impl(widget, std::move(initial_map));
        }

        message_handler_map_type make_window_message_handler_map(
            gui::widget::window&       window,
            message_handler_map_type&& initial_map,
            const message_handler&     self) const
        {
            return self.make_window_message_handler_map_impl(window, std::move(initial_map));
        }
    };


    message_handler::~message_handler() = default;

    message_handler::message_handler_map_type message_handler::make_abstract_window_message_handler_map(
        gui::widget::abstract_window& abstract_window,
        message_handler_map_type&&    initial_map) const
    {
        return m_p_impl->make_abstract_window_message_handler_map(abstract_window, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_button_message_handler_map(
        gui::widget::button&       button,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_button_message_handler_map(button, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_control_message_handler_map(
        gui::widget::control&      control,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_control_message_handler_map(control, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_custom_control_message_handler_map(
        gui::widget::custom_control& custom_control,
        message_handler_map_type&&   initial_map) const
    {
        return m_p_impl->make_custom_control_message_handler_map(custom_control, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_dialog_message_handler_map(
        gui::widget::dialog&       dialog,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_dialog_message_handler_map(dialog, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_dropdown_box_message_handler_map(
        gui::widget::dropdown_box& dropdown_box,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_dropdown_box_message_handler_map(dropdown_box, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_image_message_handler_map(
        gui::widget::image&        image,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_image_message_handler_map(image, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_label_message_handler_map(
        gui::widget::label&        label,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_label_message_handler_map(label, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_list_box_message_handler_map(
        gui::widget::list_box&     list_box,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_list_box_message_handler_map(list_box, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_picture_box_message_handler_map(
        gui::widget::picture_box&  picture_box,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_picture_box_message_handler_map(picture_box, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_progress_bar_message_handler_map(
        gui::widget::progress_bar& progress_bar,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_progress_bar_message_handler_map(progress_bar, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_text_box_message_handler_map(
        gui::widget::text_box&     text_box,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_text_box_message_handler_map(text_box, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_widget_message_handler_map(
        gui::widget::widget&       widget,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_widget_message_handler_map(widget, std::move(initial_map), *this);
    }

    message_handler::message_handler_map_type message_handler::make_window_message_handler_map(
        gui::widget::window&       window,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_window_message_handler_map(window, std::move(initial_map), *this);
    }

    message_handler::message_handler() : m_p_impl{ std::make_unique<impl>() } {}
}