/*! \file
    \brief The definition of tetengo2::detail::base::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/widget.h>


namespace tetengo2::detail::base {
    class widget::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = widget::size_type;

        using string_type = widget::string_type;

        using scroll_bar_style_type = widget::scroll_bar_style_type;

        using window_state_type = widget::window_state_type;

        using font_type = widget::font_type;

        using menu_base_type = widget::menu_base_type;

        using progress_bar_state_type = widget::progress_bar_state_type;

        using widget_details_type = widget::widget_details_type;

        using widget_details_ptr_type = widget::widget_details_ptr_type;


        // functions

        widget_details_ptr_type
        create_button(gui::widget::widget& parent, const bool is_default, const bool is_cancel, const widget& self)
            const
        {
            return self.create_button_impl(parent, is_default, is_cancel);
        }

        widget_details_ptr_type create_custom_control(
            gui::widget::widget&  parent,
            const bool            border,
            scroll_bar_style_type scroll_bar_style,
            const widget&         self) const
        {
            return self.create_custom_control_impl(parent, border, scroll_bar_style);
        }

        widget_details_ptr_type
        create_dialog(gui::widget::widget* const p_parent, const bool file_droppable, const widget& self) const
        {
            return self.create_dialog_impl(p_parent, file_droppable);
        }

        widget_details_ptr_type create_dropdown_box(gui::widget::widget& parent, const widget& self) const
        {
            return self.create_dropdown_box_impl(parent);
        }

        widget_details_ptr_type create_image(gui::widget::widget& parent, const widget& self) const
        {
            return self.create_image_impl(parent);
        }

        widget_details_ptr_type create_label(gui::widget::widget& parent, const widget& self) const
        {
            return self.create_label_impl(parent);
        }

        widget_details_ptr_type create_list_box(
            gui::widget::widget&        parent,
            const scroll_bar_style_type scroll_bar_style,
            const widget&               self) const
        {
            return self.create_list_box_impl(parent, scroll_bar_style);
        }

        widget_details_ptr_type create_picture_box(
            gui::widget::widget&        parent,
            const scroll_bar_style_type scroll_bar_style,
            const widget&               self) const
        {
            return self.create_picture_box_impl(parent, scroll_bar_style);
        }

        widget_details_ptr_type create_progress_bar(gui::widget::widget& parent, const widget& self) const
        {
            return self.create_progress_bar_impl(parent);
        }

        widget_details_ptr_type create_text_box(
            gui::widget::widget&        parent,
            const scroll_bar_style_type scroll_bar_style,
            const widget&               self) const
        {
            return self.create_text_box_impl(parent, scroll_bar_style);
        }

        widget_details_ptr_type create_window(
            gui::widget::widget* const  p_parent,
            const scroll_bar_style_type scroll_bar_style,
            bool                        file_droppable,
            const widget&               self) const
        {
            return self.create_window_impl(p_parent, scroll_bar_style, file_droppable);
        }

        void associate_to_native_window_system(gui::widget::widget& widget_, const widget& self) const
        {
            self.associate_to_native_window_system_impl(widget_);
        }

        bool has_parent(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.has_parent_impl(widget_);
        }

        gui::widget::widget& parent(gui::widget::widget& widget_, const widget& self) const
        {
            return self.parent_impl(widget_);
        }

        gui::widget::widget& root_ancestor(gui::widget::widget& widget_, const widget& self) const
        {
            return self.root_ancestor_impl(widget_);
        }

        void set_enabled(gui::widget::widget& widget_, const bool enabled, const widget& self) const
        {
            self.set_enabled_impl(widget_, enabled);
        }

        bool enabled(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.enabled_impl(widget_);
        }

        void set_visible(gui::widget::widget& widget_, const bool visible, const widget& self) const
        {
            self.set_visible_impl(widget_, visible);
        }

        bool visible(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.visible_impl(widget_);
        }

        void set_window_state(gui::widget::widget& widget_, const window_state_type state, const widget& self) const
        {
            self.set_window_state_impl(widget_, state);
        }

        window_state_type window_state(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.window_state_impl(widget_);
        }

        void move(
            gui::widget::widget&                  widget_,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const widget&                         self) const
        {
            self.move_impl(widget_, position, dimension);
        }

        gui::type_list::position_type position(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.position_impl(widget_);
        }

        gui::type_list::position_type
        dialog_position(const gui::widget::widget& widget_, const gui::widget::widget& parent, const widget& self) const
        {
            return self.dialog_position_impl(widget_, parent);
        }

        gui::type_list::dimension_type dimension(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.dimension_impl(widget_);
        }

        void set_client_dimension(
            gui::widget::widget&                  widget_,
            const gui::type_list::dimension_type& client_dimension,
            const widget&                         self) const
        {
            self.set_client_dimension_impl(widget_, client_dimension);
        }

        gui::type_list::dimension_type client_dimension(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.client_dimension_impl(widget_);
        }

        gui::type_list::dimension_type normal_dimension(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.normal_dimension_impl(widget_);
        }

        void set_text(gui::widget::widget& widget_, string_type text, const widget& self) const
        {
            self.set_text_impl(widget_, std::move(text));
        }

        string_type text(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.text_impl(widget_);
        }

        void set_font(gui::widget::widget& widget_, const font_type& font, const widget& self) const
        {
            self.set_font_impl(widget_, font);
        }

        font_type font(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.font_impl(widget_);
        }

        std::vector<std::reference_wrapper<gui::widget::widget>>
        children(gui::widget::widget& widget_, const widget& self) const
        {
            return self.children_impl(widget_);
        }

        void repaint(gui::widget::widget& widget_, const bool immediately, const widget& self) const
        {
            self.repaint_impl(widget_, immediately);
        }

        void repaint_partially(
            gui::widget::widget&                  widget_,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension,
            const widget&                         self) const
        {
            self.repaint_partially_impl(widget_, position, dimension);
        }

        void activate(gui::widget::widget& widget_, const widget& self) const
        {
            self.activate_impl(widget_);
        }

        void set_icon(gui::widget::widget& widget_, const gui::icon* p_icon, const widget& self) const
        {
            self.set_icon_impl(widget_, p_icon);
        }

        void set_menu_bar(gui::widget::widget& widget_, const menu_base_type* p_menu, const widget& self) const
        {
            self.set_menu_bar_impl(widget_, p_menu);
        }

        bool focusable(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.focusable_impl(widget_);
        }

        void set_focusable(gui::widget::widget& widget_, const bool focusable, const widget& self) const
        {
            self.set_focusable_impl(widget_, focusable);
        }

        void set_focus(gui::widget::widget& widget_, const widget& self) const
        {
            self.set_focus_impl(widget_);
        }

        bool read_only(const gui::widget::widget& widget_, const widget& self) const
        {
            return self.read_only_impl(widget_);
        }

        void set_read_only(gui::widget::widget& widget_, const bool read_only, const widget& self) const
        {
            self.set_read_only_impl(widget_, read_only);
        }

        void close(gui::widget::widget& widget_, const widget& self) const
        {
            self.close_impl(widget_);
        }

        size_type dropdown_box_value_count(const gui::widget::dropdown_box& dropdown_box, const widget& self) const
        {
            return self.dropdown_box_value_count_impl(dropdown_box);
        }

        string_type dropdown_box_value(
            const gui::widget::dropdown_box& dropdown_box,
            const size_type                  index,
            const widget&                    self) const
        {
            return self.dropdown_box_value_impl(dropdown_box, index);
        }

        void set_dropdown_box_value(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value,
            const widget&              self) const
        {
            self.set_dropdown_box_value_impl(dropdown_box, index, std::move(value));
        }

        void insert_dropdown_box_value(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value,
            const widget&              self) const
        {
            self.insert_dropdown_box_value_impl(dropdown_box, index, std::move(value));
        }

        void erase_dropdown_box_value(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            const widget&              self) const
        {
            self.erase_dropdown_box_value_impl(dropdown_box, index);
        }

        void clear_dropdown_box(gui::widget::dropdown_box& dropdown_box, const widget& self) const
        {
            self.clear_dropdown_box_impl(dropdown_box);
        }

        tetengo2::stdalt::optional<size_type>
        selected_dropdown_box_value_index(const gui::widget::dropdown_box& dropdown_box, const widget& self) const
        {
            return self.selected_dropdown_box_value_index_impl(dropdown_box);
        }

        void select_dropdown_box_value(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            const widget&              self) const
        {
            self.select_dropdown_box_value_impl(dropdown_box, index);
        }

        size_type list_box_value_count(const gui::widget::list_box& list_box, const widget& self) const
        {
            return self.list_box_value_count_impl(list_box);
        }

        string_type
        list_box_value(const gui::widget::list_box& list_box, const size_type index, const widget& self) const
        {
            return self.list_box_value_impl(list_box, index);
        }

        void set_list_box_value(
            gui::widget::list_box& list_box,
            const size_type        index,
            string_type            value,
            const widget&          self) const
        {
            self.set_list_box_value_impl(list_box, index, std::move(value));
        }

        void insert_list_box_value(
            gui::widget::list_box& list_box,
            const size_type        index,
            string_type            value,
            const widget&          self) const
        {
            return self.insert_list_box_value_impl(list_box, index, std::move(value));
        }

        void erase_list_box_value(gui::widget::list_box& list_box, const size_type index, const widget& self) const
        {
            self.erase_list_box_value_impl(list_box, index);
        }

        void clear_list_box(gui::widget::list_box& list_box, const widget& self) const
        {
            self.clear_list_box_impl(list_box);
        }

        tetengo2::stdalt::optional<size_type>
        selected_list_box_value_index(const gui::widget::list_box& list_box, const widget& self) const
        {
            return self.selected_list_box_value_index_impl(list_box);
        }

        void select_list_box_value(gui::widget::list_box& list_box, const size_type index, const widget& self) const
        {
            self.select_list_box_value_impl(list_box, index);
        }

        size_type progress_bar_goal(gui::widget::progress_bar& progress_bar, const widget& self) const
        {
            return self.progress_bar_goal_impl(progress_bar);
        }

        void
        set_progress_bar_goal(gui::widget::progress_bar& progress_bar, const size_type goal, const widget& self) const
        {
            self.set_progress_bar_goal_impl(progress_bar, goal);
        }

        size_type progress_bar_progress(gui::widget::progress_bar& progress_bar, const widget& self) const
        {
            return self.progress_bar_progress_impl(progress_bar);
        }

        void set_progress_bar_progress(
            gui::widget::progress_bar& progress_bar,
            const size_type            progress,
            const widget&              self) const
        {
            self.set_progress_bar_progress_impl(progress_bar, progress);
        }

        progress_bar_state_type progress_bar_state(gui::widget::progress_bar& progress_bar, const widget& self) const
        {
            return self.progress_bar_state_impl(progress_bar);
        }

        void set_progress_bar_state(
            gui::widget::progress_bar&    progress_bar,
            const progress_bar_state_type state,
            const widget&                 self) const
        {
            self.set_progress_bar_state_impl(progress_bar, state);
        }
    };


    widget::~widget() = default;

    widget::widget_details_ptr_type
    widget::create_button(gui::widget::widget& parent, const bool is_default, const bool is_cancel) const
    {
        return m_p_impl->create_button(parent, is_default, is_cancel, *this);
    }

    widget::widget_details_ptr_type widget::create_custom_control(
        gui::widget::widget&        parent,
        const bool                  border,
        const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_custom_control(parent, border, scroll_bar_style, *this);
    }

    widget::widget_details_ptr_type
    widget::create_dialog(gui::widget::widget* const p_parent, const bool file_droppable) const
    {
        return m_p_impl->create_dialog(p_parent, file_droppable, *this);
    }

    widget::widget_details_ptr_type widget::create_dropdown_box(gui::widget::widget& parent) const
    {
        return m_p_impl->create_dropdown_box(parent, *this);
    }

    widget::widget_details_ptr_type widget::create_image(gui::widget::widget& parent) const
    {
        return m_p_impl->create_image(parent, *this);
    }

    widget::widget_details_ptr_type widget::create_label(gui::widget::widget& parent) const
    {
        return m_p_impl->create_label(parent, *this);
    }

    widget::widget_details_ptr_type
    widget::create_list_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_list_box(parent, scroll_bar_style, *this);
    }

    widget::widget_details_ptr_type
    widget::create_picture_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_picture_box(parent, scroll_bar_style, *this);
    }

    widget::widget_details_ptr_type widget::create_progress_bar(gui::widget::widget& parent) const
    {
        return m_p_impl->create_progress_bar(parent, *this);
    }

    widget::widget_details_ptr_type
    widget::create_text_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_text_box(parent, scroll_bar_style, *this);
    }

    widget::widget_details_ptr_type widget::create_window(
        gui::widget::widget* const  p_parent,
        const scroll_bar_style_type scroll_bar_style,
        const bool                  file_droppable) const
    {
        return m_p_impl->create_window(p_parent, scroll_bar_style, file_droppable, *this);
    }

    void widget::associate_to_native_window_system(gui::widget::widget& widget) const
    {
        m_p_impl->associate_to_native_window_system(widget, *this);
    }

    bool widget::has_parent(const gui::widget::widget& widget) const
    {
        return m_p_impl->has_parent(widget, *this);
    }

    gui::widget::widget& widget::parent(gui::widget::widget& widget) const
    {
        return m_p_impl->parent(widget, *this);
    }

    gui::widget::widget& widget::root_ancestor(gui::widget::widget& widget) const
    {
        return m_p_impl->root_ancestor(widget, *this);
    }

    void widget::set_enabled(gui::widget::widget& widget, const bool enabled) const
    {
        m_p_impl->set_enabled(widget, enabled, *this);
    }

    bool widget::enabled(const gui::widget::widget& widget) const
    {
        return m_p_impl->enabled(widget, *this);
    }

    void widget::set_visible(gui::widget::widget& widget, const bool visible) const
    {
        m_p_impl->set_visible(widget, visible, *this);
    }

    bool widget::visible(const gui::widget::widget& widget) const
    {
        return m_p_impl->visible(widget, *this);
    }

    void widget::set_window_state(gui::widget::widget& widget, const window_state_type state) const
    {
        return m_p_impl->set_window_state(widget, state, *this);
    }

    widget::window_state_type widget::window_state(const gui::widget::widget& widget) const
    {
        return m_p_impl->window_state(widget, *this);
    }

    void widget::move(
        gui::widget::widget&                  widget,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->move(widget, position, dimension, *this);
    }

    gui::type_list::position_type widget::position(const gui::widget::widget& widget) const
    {
        return m_p_impl->position(widget, *this);
    }

    gui::type_list::position_type
    widget::dialog_position(const gui::widget::widget& widget, const gui::widget::widget& parent) const
    {
        return m_p_impl->dialog_position(widget, parent, *this);
    }

    gui::type_list::dimension_type widget::dimension(const gui::widget::widget& widget) const
    {
        return m_p_impl->dimension(widget, *this);
    }

    void widget::set_client_dimension(
        gui::widget::widget&                  widget,
        const gui::type_list::dimension_type& client_dimension) const
    {
        m_p_impl->set_client_dimension(widget, client_dimension, *this);
    }

    gui::type_list::dimension_type widget::client_dimension(const gui::widget::widget& widget) const
    {
        return m_p_impl->client_dimension(widget, *this);
    }

    gui::type_list::dimension_type widget::normal_dimension(const gui::widget::widget& widget) const
    {
        return m_p_impl->normal_dimension(widget, *this);
    }

    void widget::set_text(gui::widget::widget& widget, string_type text) const
    {
        m_p_impl->set_text(widget, std::move(text), *this);
    }

    widget::string_type widget::text(const gui::widget::widget& widget) const
    {
        return m_p_impl->text(widget, *this);
    }

    void widget::set_font(gui::widget::widget& widget, const font_type& font) const
    {
        m_p_impl->set_font(widget, font, *this);
    }

    widget::font_type widget::font(const gui::widget::widget& widget) const
    {
        return m_p_impl->font(widget, *this);
    }

    std::vector<std::reference_wrapper<gui::widget::widget>> widget::children(gui::widget::widget& widget) const
    {
        return m_p_impl->children(widget, *this);
    }

    void widget::repaint(gui::widget::widget& widget, const bool immediately) const
    {
        m_p_impl->repaint(widget, immediately, *this);
    }

    void widget::repaint_partially(
        gui::widget::widget&                  widget,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        return m_p_impl->repaint_partially(widget, position, dimension, *this);
    }

    void widget::activate(gui::widget::widget& widget) const
    {
        return m_p_impl->activate(widget, *this);
    }

    void widget::set_icon(gui::widget::widget& widget, const gui::icon* p_icon) const
    {
        m_p_impl->set_icon(widget, p_icon, *this);
    }

    void widget::set_menu_bar(gui::widget::widget& widget, const menu_base_type* p_menu /*= nullptr*/) const
    {
        m_p_impl->set_menu_bar(widget, p_menu, *this);
    }

    bool widget::focusable(const gui::widget::widget& widget) const
    {
        return m_p_impl->focusable(widget, *this);
    }

    void widget::set_focusable(gui::widget::widget& widget, const bool focusable) const
    {
        m_p_impl->set_focusable(widget, focusable, *this);
    }

    void widget::set_focus(gui::widget::widget& widget) const
    {
        return m_p_impl->set_focus(widget, *this);
    }

    bool widget::read_only(const gui::widget::widget& widget) const
    {
        return m_p_impl->read_only(widget, *this);
    }

    void widget::set_read_only(gui::widget::widget& widget, const bool read_only) const
    {
        m_p_impl->set_read_only(widget, read_only, *this);
    }

    void widget::close(gui::widget::widget& widget) const
    {
        m_p_impl->close(widget, *this);
    }

    widget::size_type widget::dropdown_box_value_count(const gui::widget::dropdown_box& dropdown_box) const
    {
        return m_p_impl->dropdown_box_value_count(dropdown_box, *this);
    }

    widget::string_type
    widget::dropdown_box_value(const gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        return m_p_impl->dropdown_box_value(dropdown_box, index, *this);
    }

    void widget::set_dropdown_box_value(
        gui::widget::dropdown_box& dropdown_box,
        const size_type            index,
        string_type                value) const
    {
        m_p_impl->set_dropdown_box_value(dropdown_box, index, std::move(value), *this);
    }

    void widget::insert_dropdown_box_value(
        gui::widget::dropdown_box& dropdown_box,
        const size_type            index,
        string_type                value) const
    {
        m_p_impl->insert_dropdown_box_value(dropdown_box, index, std::move(value), *this);
    }

    void widget::erase_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        m_p_impl->erase_dropdown_box_value(dropdown_box, index, *this);
    }

    void widget::clear_dropdown_box(gui::widget::dropdown_box& dropdown_box) const
    {
        m_p_impl->clear_dropdown_box(dropdown_box, *this);
    }

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_dropdown_box_value_index(const gui::widget::dropdown_box& dropdown_box) const
    {
        return m_p_impl->selected_dropdown_box_value_index(dropdown_box, *this);
    }

    void widget::select_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        m_p_impl->select_dropdown_box_value(dropdown_box, index, *this);
    }

    widget::size_type widget::list_box_value_count(const gui::widget::list_box& list_box) const
    {
        return m_p_impl->list_box_value_count(list_box, *this);
    }

    widget::string_type widget::list_box_value(const gui::widget::list_box& list_box, const size_type index) const
    {
        return m_p_impl->list_box_value(list_box, index, *this);
    }

    void widget::set_list_box_value(gui::widget::list_box& list_box, const size_type index, string_type value) const
    {
        m_p_impl->set_list_box_value(list_box, index, std::move(value), *this);
    }

    void widget::insert_list_box_value(gui::widget::list_box& list_box, const size_type index, string_type value) const
    {
        m_p_impl->insert_list_box_value(list_box, index, std::move(value), *this);
    }

    void widget::erase_list_box_value(gui::widget::list_box& list_box, const size_type index) const
    {
        m_p_impl->erase_list_box_value(list_box, index, *this);
    }

    void widget::clear_list_box(gui::widget::list_box& list_box) const
    {
        m_p_impl->clear_list_box(list_box, *this);
    }

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_list_box_value_index(const gui::widget::list_box& list_box) const
    {
        return m_p_impl->selected_list_box_value_index(list_box, *this);
    }

    void widget::select_list_box_value(gui::widget::list_box& list_box, const size_type index) const
    {
        m_p_impl->select_list_box_value(list_box, index, *this);
    }

    widget::size_type widget::progress_bar_goal(gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_goal(progress_bar, *this);
    }

    void widget::set_progress_bar_goal(gui::widget::progress_bar& progress_bar, const size_type goal) const
    {
        m_p_impl->set_progress_bar_goal(progress_bar, goal, *this);
    }

    widget::size_type widget::progress_bar_progress(gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_progress(progress_bar, *this);
    }

    void widget::set_progress_bar_progress(gui::widget::progress_bar& progress_bar, const size_type progress) const
    {
        m_p_impl->set_progress_bar_progress(progress_bar, progress, *this);
    }

    widget::progress_bar_state_type widget::progress_bar_state(gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_state(progress_bar, *this);
    }

    void
    widget::set_progress_bar_state(gui::widget::progress_bar& progress_bar, const progress_bar_state_type state) const
    {
        return m_p_impl->set_progress_bar_state(progress_bar, state, *this);
    }

    widget::widget() : m_p_impl{ std::make_unique<impl>() } {}
}