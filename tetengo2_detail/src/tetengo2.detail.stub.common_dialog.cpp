/*! \file
    \brief The definition of tetengo2::detail::stub::common_dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/common_dialog.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/type_list.h>


namespace tetengo2::detail::stub {
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


        // static functions

        static const common_dialog& instance()
        {
            static const common_dialog singleton;
            return singleton;
        }


        // functions

        message_box_details_ptr_type create_message_box_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::abstract_window& parent,
            TETENGO2_STDALT_MAYBE_UNUSED type_list::string_type title,
            TETENGO2_STDALT_MAYBE_UNUSED type_list::string_type main_content,
            TETENGO2_STDALT_MAYBE_UNUSED type_list::string_type sub_content,
            TETENGO2_STDALT_MAYBE_UNUSED const bool             cancellable,
            TETENGO2_STDALT_MAYBE_UNUSED const message_box_button_style_type button_style,
            TETENGO2_STDALT_MAYBE_UNUSED const message_box_icon_style_type icon_style,
            TETENGO2_STDALT_MAYBE_UNUSED tetengo2::stdalt::optional<type_list::string_type> custom_ok_button_label,
            TETENGO2_STDALT_MAYBE_UNUSED                                                    tetengo2::stdalt::optional<
                std::pair<type_list::string_type, type_list::string_type>> custom_yes_no_button_labels) const
        {
            return std::make_unique<message_box_details_type>();
        }

        message_box_button_id_type
        show_message_box_impl(TETENGO2_STDALT_MAYBE_UNUSED message_box_details_type& message_box) const
        {
            return message_box_button_id_type::cancel;
        }

        file_open_dialog_details_ptr_type create_file_open_dialog_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::abstract_window& parent,
            TETENGO2_STDALT_MAYBE_UNUSED type_list::string_type title,
            TETENGO2_STDALT_MAYBE_UNUSED const filters_type& filters) const
        {
            return std::make_unique<file_open_dialog_details_type>();
        }

        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_open_dialog_impl(TETENGO2_STDALT_MAYBE_UNUSED file_open_dialog_details_type& dialog) const
        {
            tetengo2::stdalt::filesystem::path file_name{ tetengo2::stdalt::filesystem::path::string_type{
                TETENGO2_TEXT("file_open_dialog") } };
            return tetengo2::stdalt::make_optional(
                tetengo2::stdalt::filesystem::temp_directory_path() / std::move(file_name));
        }

        file_save_dialog_details_ptr_type create_file_save_dialog_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::abstract_window& parent,
            TETENGO2_STDALT_MAYBE_UNUSED type_list::string_type title,
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
            TETENGO2_STDALT_MAYBE_UNUSED const filters_type& filters) const
        {
            return std::make_unique<file_save_dialog_details_type>();
        }

        tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
        show_file_save_dialog_impl(TETENGO2_STDALT_MAYBE_UNUSED file_save_dialog_details_type& dialog) const
        {
            tetengo2::stdalt::filesystem::path file_name{ tetengo2::stdalt::filesystem::path::string_type{
                TETENGO2_TEXT("file_save_dialog") } };
            return tetengo2::stdalt::make_optional(tetengo2::stdalt::filesystem::temp_directory_path() / file_name);
        }

        font_dialog_details_ptr_type create_font_dialog_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::abstract_window& parent,
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::stdalt::optional<gui::drawing::font>& font) const
        {
            return std::make_unique<font_dialog_details_type>();
        }

        tetengo2::stdalt::optional<gui::drawing::font>
        show_font_dialog_impl(TETENGO2_STDALT_MAYBE_UNUSED font_dialog_details_type& dialog) const
        {
            return tetengo2::stdalt::make_optional(gui::drawing::font{
                type_list::string_type{ TETENGO2_TEXT("font_dialog_font") }, 42, false, true, false, true });
        }

        color_dialog_details_ptr_type create_color_dialog_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::abstract_window& parent,
            TETENGO2_STDALT_MAYBE_UNUSED const tetengo2::stdalt::optional<gui::drawing::color>& color) const
        {
            return std::make_unique<color_dialog_details_type>();
        }

        tetengo2::stdalt::optional<gui::drawing::color>
        show_color_dialog_impl(TETENGO2_STDALT_MAYBE_UNUSED color_dialog_details_type& dialog) const
        {
            return tetengo2::stdalt::make_optional(gui::drawing::color{ 0xAB, 0xCD, 0xEF });
        }
    };


    const common_dialog& common_dialog::instance()
    {
        return impl::instance();
    }

    common_dialog::~common_dialog() = default;

    common_dialog::common_dialog() : m_p_impl{ std::make_unique<impl>() } {}

    common_dialog::message_box_details_ptr_type common_dialog::create_message_box_impl(
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
        return m_p_impl->create_message_box_impl(
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

    common_dialog::message_box_button_id_type
    common_dialog::show_message_box_impl(message_box_details_type& message_box) const
    {
        return m_p_impl->show_message_box_impl(message_box);
    }

    common_dialog::file_open_dialog_details_ptr_type common_dialog::create_file_open_dialog_impl(
        gui::widget::abstract_window& parent,
        type_list::string_type        title,
        const filters_type&           filters) const
    {
        return m_p_impl->create_file_open_dialog_impl(parent, std::move(title), filters);
    }

    tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
    common_dialog::show_file_open_dialog_impl(file_open_dialog_details_type& dialog) const
    {
        return m_p_impl->show_file_open_dialog_impl(dialog);
    }

    common_dialog::file_save_dialog_details_ptr_type common_dialog::create_file_save_dialog_impl(
        gui::widget::abstract_window&                                         parent,
        type_list::string_type                                                title,
        const tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>& path,
        const filters_type&                                                   filters) const
    {
        return m_p_impl->create_file_save_dialog_impl(parent, std::move(title), path, filters);
    }

    tetengo2::stdalt::optional<tetengo2::stdalt::filesystem::path>
    common_dialog::show_file_save_dialog_impl(file_save_dialog_details_type& dialog) const
    {
        return m_p_impl->show_file_save_dialog_impl(dialog);
    }

    common_dialog::font_dialog_details_ptr_type common_dialog::create_font_dialog_impl(
        gui::widget::abstract_window&                         parent,
        const tetengo2::stdalt::optional<gui::drawing::font>& font) const
    {
        return m_p_impl->create_font_dialog_impl(parent, font);
    }

    tetengo2::stdalt::optional<gui::drawing::font>
    common_dialog::show_font_dialog_impl(font_dialog_details_type& dialog) const
    {
        return m_p_impl->show_font_dialog_impl(dialog);
    }

    common_dialog::color_dialog_details_ptr_type common_dialog::create_color_dialog_impl(
        gui::widget::abstract_window&                          parent,
        const tetengo2::stdalt::optional<gui::drawing::color>& color) const
    {
        return m_p_impl->create_color_dialog_impl(parent, color);
    }

    tetengo2::stdalt::optional<gui::drawing::color>
    common_dialog::show_color_dialog_impl(color_dialog_details_type& dialog) const
    {
        return m_p_impl->show_color_dialog_impl(dialog);
    }
}
