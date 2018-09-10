/*! \file
    \brief The definition of tetengo2::detail::base::common_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
}}}


namespace tetengo2::detail::base {
    class common_dialog::impl : private boost::noncopyable
    {
    public:
        // types

        using message_box_button_style_type = common_dialog::message_box_button_style_type;

        using message_box_icon_style_type = common_dialog::message_box_icon_style_type;

        using message_box_button_id_type = common_dialog::message_box_button_id_type;

        using message_box_details_type = common_dialog::message_box_details_type;

        using message_box_details_ptr_type = common_dialog::message_box_details_ptr_type;

        using filters_type = common_dialog::filters_type;

        using file_open_dialog_details_type = common_dialog::file_open_dialog_details_type;

        using file_open_dialog_details_ptr_type = common_dialog::file_open_dialog_details_ptr_type;

        using file_save_dialog_details_type = common_dialog::file_save_dialog_details_type;

        using file_save_dialog_details_ptr_type = common_dialog::file_save_dialog_details_ptr_type;

        using font_dialog_details_type = common_dialog::font_dialog_details_type;

        using font_dialog_details_ptr_type = common_dialog::font_dialog_details_ptr_type;

        using color_dialog_details_type = common_dialog::color_dialog_details_type;

        using color_dialog_details_ptr_type = common_dialog::color_dialog_details_ptr_type;


        // functions

        message_box_details_ptr_type create_message_box(
            gui::widget::abstract_window&                      parent,
            type_list::string_type                             title,
            type_list::string_type                             main_content,
            type_list::string_type                             sub_content,
            const bool                                         cancellable,
            const message_box_button_style_type                button_style,
            const message_box_icon_style_type                  icon_style,
            tetengo2::stdalt::optional<type_list::string_type> custom_ok_button_label,
            tetengo2::stdalt::optional<std::pair<type_list::string_type, type_list::string_type>>
                                 custom_yes_no_button_labels,
            const common_dialog& self) const
        {
            return self.create_message_box_impl(
                parent,
                std::move(title),
                std::move(main_content),
                std::move(sub_content),
                cancellable,
                button_style,
                icon_style,
                std::move(custom_ok_button_label),
                std::move(custom_yes_no_button_labels));
        }

        message_box_button_id_type
        show_message_box(message_box_details_type& message_box, const common_dialog& self) const
        {
            return self.show_message_box_impl(message_box);
        }

        file_open_dialog_details_ptr_type create_file_open_dialog(
            gui::widget::abstract_window& parent,
            type_list::string_type        title,
            const filters_type&           filters,
            const common_dialog&          self) const
        {
            return self.create_file_open_dialog_impl(parent, std::move(title), filters);
        }

        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_open_dialog(file_open_dialog_details_type& dialog, const common_dialog& self) const
        {
            return self.show_file_open_dialog_impl(dialog);
        }

        file_save_dialog_details_ptr_type create_file_save_dialog(
            gui::widget::abstract_window&                                         parent,
            type_list::string_type                                                title,
            const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
            const filters_type&                                                   filters,
            const common_dialog&                                                  self) const
        {
            return self.create_file_save_dialog_impl(parent, std::move(title), path, filters);
        }

        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_save_dialog(file_save_dialog_details_type& dialog, const common_dialog& self) const
        {
            return self.show_file_save_dialog_impl(dialog);
        }

        font_dialog_details_ptr_type create_font_dialog(
            gui::widget::abstract_window&                         parent,
            const tetengo2::stdalt::optional<gui::drawing::font>& font,
            const common_dialog&                                  self) const
        {
            return self.create_font_dialog_impl(parent, font);
        }

        tetengo2::stdalt::optional<gui::drawing::font>
        show_font_dialog(font_dialog_details_type& dialog, const common_dialog& self) const
        {
            return self.show_font_dialog_impl(dialog);
        }

        color_dialog_details_ptr_type create_color_dialog(
            gui::widget::abstract_window&                          parent,
            const tetengo2::stdalt::optional<gui::drawing::color>& color,
            const common_dialog&                                   self) const
        {
            return self.create_color_dialog_impl(parent, color);
        }

        tetengo2::stdalt::optional<gui::drawing::color>
        show_color_dialog(color_dialog_details_type& dialog, const common_dialog& self) const
        {
            return self.show_color_dialog_impl(dialog);
        }
    };


    common_dialog::message_box_details_type::~message_box_details_type() = default;

    common_dialog::file_open_dialog_details_type::~file_open_dialog_details_type() = default;

    common_dialog::file_save_dialog_details_type::~file_save_dialog_details_type() = default;

    common_dialog::font_dialog_details_type::~font_dialog_details_type() = default;

    common_dialog::color_dialog_details_type::~color_dialog_details_type() = default;

    common_dialog::~common_dialog() = default;

    common_dialog::message_box_details_ptr_type common_dialog::create_message_box(
        gui::widget::abstract_window&                      parent,
        type_list::string_type                             title,
        type_list::string_type                             main_content,
        type_list::string_type                             sub_content,
        const bool                                         cancellable,
        const message_box_button_style_type                button_style,
        const message_box_icon_style_type                  icon_style,
        tetengo2::stdalt::optional<type_list::string_type> custom_ok_button_label,
        tetengo2::stdalt::optional<std::pair<type_list::string_type, type_list::string_type>>
            custom_yes_no_button_labels) const
    {
        return m_p_impl->create_message_box(
            parent,
            std::move(title),
            std::move(main_content),
            std::move(sub_content),
            cancellable,
            button_style,
            icon_style,
            std::move(custom_ok_button_label),
            std::move(custom_yes_no_button_labels),
            *this);
    }

    common_dialog::message_box_button_id_type
    common_dialog::show_message_box(message_box_details_type& message_box) const
    {
        return m_p_impl->show_message_box(message_box, *this);
    }

    common_dialog::file_open_dialog_details_ptr_type common_dialog::create_file_open_dialog(
        gui::widget::abstract_window& parent,
        type_list::string_type        title,
        const filters_type&           filters) const
    {
        return m_p_impl->create_file_open_dialog(parent, std::move(title), filters, *this);
    }

    tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
    common_dialog::show_file_open_dialog(file_open_dialog_details_type& dialog) const
    {
        return m_p_impl->show_file_open_dialog(dialog, *this);
    }

    common_dialog::file_save_dialog_details_ptr_type common_dialog::create_file_save_dialog(
        gui::widget::abstract_window&                                         parent,
        type_list::string_type                                                title,
        const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
        const filters_type&                                                   filters) const
    {
        return m_p_impl->create_file_save_dialog(parent, std::move(title), path, filters, *this);
    }

    tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
    common_dialog::show_file_save_dialog(file_save_dialog_details_type& dialog) const
    {
        return m_p_impl->show_file_save_dialog(dialog, *this);
    }

    common_dialog::font_dialog_details_ptr_type common_dialog::create_font_dialog(
        gui::widget::abstract_window&                         parent,
        const tetengo2::stdalt::optional<gui::drawing::font>& font) const
    {
        return m_p_impl->create_font_dialog(parent, font, *this);
    }

    tetengo2::stdalt::optional<gui::drawing::font>
    common_dialog::show_font_dialog(font_dialog_details_type& dialog) const
    {
        return m_p_impl->show_font_dialog(dialog, *this);
    }

    common_dialog::color_dialog_details_ptr_type common_dialog::create_color_dialog(
        gui::widget::abstract_window&                          parent,
        const tetengo2::stdalt::optional<gui::drawing::color>& color) const
    {
        return m_p_impl->create_color_dialog(parent, color, *this);
    }

    tetengo2::stdalt::optional<gui::drawing::color>
    common_dialog::show_color_dialog(color_dialog_details_type& dialog) const
    {
        return m_p_impl->show_color_dialog(dialog, *this);
    }

    common_dialog::common_dialog() : m_p_impl{ std::make_unique<impl>() } {}
}
