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
        create_button(gui::widget::widget& parent, const bool is_default, const bool is_cancel) const;

        widget_details_ptr_type create_custom_control(
            gui::widget::widget&  parent,
            const bool            border,
            scroll_bar_style_type scroll_bar_style) const;

        widget_details_ptr_type create_dialog(gui::widget::widget* const p_parent, const bool file_droppable) const;

        widget_details_ptr_type create_dropdown_box(gui::widget::widget& parent) const;

        widget_details_ptr_type create_image(gui::widget::widget& parent) const;

        widget_details_ptr_type create_label(gui::widget::widget& parent) const;

        widget_details_ptr_type
        create_list_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const;

        widget_details_ptr_type
        create_picture_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const;

        widget_details_ptr_type create_progress_bar(gui::widget::widget& parent) const;

        widget_details_ptr_type
        create_text_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const;

        widget_details_ptr_type create_window(
            gui::widget::widget* const p_parent,
            scroll_bar_style_type      scroll_bar_style,
            bool                       file_droppable) const;

        void associate_to_native_window_system(gui::widget::widget& widget) const;

        bool has_parent(const gui::widget::widget& widget) const;

        gui::widget::widget& parent(gui::widget::widget& widget) const;

        gui::widget::widget& root_ancestor(gui::widget::widget& widget) const;

        void set_enabled(gui::widget::widget& widget, const bool enabled) const;

        bool enabled(const gui::widget::widget& widget) const;

        void set_visible(gui::widget::widget& widget, const bool visible) const;

        bool visible(const gui::widget::widget& widget) const;

        void set_window_state(gui::widget::widget& widget, const window_state_type state) const;

        window_state_type window_state(const gui::widget::widget& widget) const;

        void move(
            gui::widget::widget&                  widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const;

        gui::type_list::position_type position(const gui::widget::widget& widget) const;

        gui::type_list::position_type
        dialog_position(const gui::widget::widget& widget, const gui::widget::widget& parent) const;

        gui::type_list::dimension_type dimension(const gui::widget::widget& widget) const;

        void
        set_client_dimension(gui::widget::widget& widget, const gui::type_list::dimension_type& client_dimension) const;

        gui::type_list::dimension_type client_dimension(const gui::widget::widget& widget) const;

        gui::type_list::dimension_type normal_dimension(const gui::widget::widget& widget) const;

        void set_text(gui::widget::widget& widget, string_type text) const;

        string_type text(const gui::widget::widget& widget) const;

        void set_font(gui::widget::widget& widget, const font_type& font) const;

        font_type font(const gui::widget::widget& widget) const;

        std::vector<std::reference_wrapper<gui::widget::widget>> children(gui::widget::widget& widget) const;

        void repaint(gui::widget::widget& widget, const bool immediately) const;

        void repaint_partially(
            gui::widget::widget&                  widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const;

        void activate(gui::widget::widget& widget) const;

        void set_icon(gui::widget::widget& widget, const gui::icon* p_icon) const;

        void set_menu_bar(gui::widget::widget& widget, const menu_base_type* p_menu = nullptr) const;

        bool focusable(const gui::widget::widget& widget) const;

        void set_focusable(gui::widget::widget& widget, const bool focusable) const;

        void set_focus(gui::widget::widget& widget) const;

        bool read_only(const gui::widget::widget& widget) const;

        void set_read_only(gui::widget::widget& widget, const bool read_only) const;

        void close(gui::widget::widget& widget) const;

        size_type dropdown_box_value_count(const gui::widget::dropdown_box& dropdown_box) const;

        string_type dropdown_box_value(const gui::widget::dropdown_box& dropdown_box, const size_type index) const;

        void
        set_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, const size_type index, string_type value) const;

        void insert_dropdown_box_value(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value) const;

        void erase_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, const size_type index) const;

        void clear_dropdown_box(gui::widget::dropdown_box& dropdown_box) const;

        tetengo2::stdalt::optional<size_type>
        selected_dropdown_box_value_index(const gui::widget::dropdown_box& dropdown_box) const;

        void select_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, const size_type index) const;

        size_type list_box_value_count(const gui::widget::list_box& list_box) const;

        string_type list_box_value(const gui::widget::list_box& list_box, const size_type index) const;

        void set_list_box_value(gui::widget::list_box& list_box, const size_type index, string_type value) const;

        void insert_list_box_value(gui::widget::list_box& list_box, const size_type index, string_type value) const;

        void erase_list_box_value(gui::widget::list_box& list_box, const size_type index) const;

        void clear_list_box(gui::widget::list_box& list_box) const;

        tetengo2::stdalt::optional<size_type>
        selected_list_box_value_index(const gui::widget::list_box& list_box) const;

        void select_list_box_value(gui::widget::list_box& list_box, const size_type index) const;

        size_type progress_bar_goal(gui::widget::progress_bar& progress_bar) const;

        void set_progress_bar_goal(gui::widget::progress_bar& progress_bar, const size_type goal) const;

        size_type progress_bar_progress(gui::widget::progress_bar& progress_bar) const;

        void set_progress_bar_progress(gui::widget::progress_bar& progress_bar, const size_type progress) const;

        progress_bar_state_type progress_bar_state(gui::widget::progress_bar& progress_bar) const;

        void set_progress_bar_state(gui::widget::progress_bar& progress_bar, const progress_bar_state_type state) const;
    };


    widget::~widget() = default;

    widget::widget_details_ptr_type
    widget::create_button(gui::widget::widget& parent, const bool is_default, const bool is_cancel) const
    {
        return m_p_impl->create_button(parent, is_default, is_cancel);
    }

    widget::widget_details_ptr_type widget::create_custom_control(
        gui::widget::widget&        parent,
        const bool                  border,
        const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_custom_control(parent, border, scroll_bar_style);
    }

    widget::widget_details_ptr_type
    widget::create_dialog(gui::widget::widget* const p_parent, const bool file_droppable) const
    {
        return m_p_impl->create_dialog(p_parent, file_droppable);
    }

    widget::widget_details_ptr_type widget::create_dropdown_box(gui::widget::widget& parent) const
    {
        return m_p_impl->create_dropdown_box(parent);
    }

    widget::widget_details_ptr_type widget::create_image(gui::widget::widget& parent) const
    {
        return m_p_impl->create_image(parent);
    }

    widget::widget_details_ptr_type widget::create_label(gui::widget::widget& parent) const
    {
        return m_p_impl->create_label(parent);
    }

    widget::widget_details_ptr_type
    widget::create_list_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_list_box(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type
    widget::create_picture_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_picture_box(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type widget::create_progress_bar(gui::widget::widget& parent) const
    {
        return m_p_impl->create_progress_bar(parent);
    }

    widget::widget_details_ptr_type
    widget::create_text_box(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_text_box(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type widget::create_window(
        gui::widget::widget* const  p_parent,
        const scroll_bar_style_type scroll_bar_style,
        const bool                  file_droppable) const
    {
        return m_p_impl->create_window(p_parent, scroll_bar_style, file_droppable);
    }

    void widget::associate_to_native_window_system(gui::widget::widget& widget) const
    {
        m_p_impl->associate_to_native_window_system(widget);
    }

    bool widget::has_parent(const gui::widget::widget& widget) const
    {
        return m_p_impl->has_parent(widget);
    }

    gui::widget::widget& widget::parent(gui::widget::widget& widget) const
    {
        return m_p_impl->parent(widget);
    }

    gui::widget::widget& widget::root_ancestor(gui::widget::widget& widget) const
    {
        return m_p_impl->root_ancestor(widget);
    }

    void widget::set_enabled(gui::widget::widget& widget, const bool enabled) const
    {
        m_p_impl->set_enabled(widget, enabled);
    }

    bool widget::enabled(const gui::widget::widget& widget) const
    {
        return m_p_impl->enabled(widget);
    }

    void widget::set_visible(gui::widget::widget& widget, const bool visible) const
    {
        m_p_impl->set_visible(widget, visible);
    }

    bool widget::visible(const gui::widget::widget& widget) const
    {
        return m_p_impl->visible(widget);
    }

    void widget::set_window_state(gui::widget::widget& widget, const window_state_type state) const
    {
        return m_p_impl->set_window_state(widget, state);
    }

    widget::window_state_type widget::window_state(const gui::widget::widget& widget) const
    {
        return m_p_impl->window_state(widget);
    }

    void widget::move(
        gui::widget::widget&                  widget,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->move(widget, position, dimension);
    }

    gui::type_list::position_type widget::position(const gui::widget::widget& widget) const
    {
        return m_p_impl->position(widget);
    }

    gui::type_list::position_type
    widget::dialog_position(const gui::widget::widget& widget, const gui::widget::widget& parent) const
    {
        return m_p_impl->dialog_position(widget, parent);
    }

    gui::type_list::dimension_type widget::dimension(const gui::widget::widget& widget) const
    {
        return m_p_impl->dimension(widget);
    }

    void widget::set_client_dimension(
        gui::widget::widget&                  widget,
        const gui::type_list::dimension_type& client_dimension) const
    {
        m_p_impl->set_client_dimension(widget, client_dimension);
    }

    gui::type_list::dimension_type widget::client_dimension(const gui::widget::widget& widget) const
    {
        return m_p_impl->client_dimension(widget);
    }

    gui::type_list::dimension_type widget::normal_dimension(const gui::widget::widget& widget) const
    {
        return m_p_impl->normal_dimension(widget);
    }

    void widget::set_text(gui::widget::widget& widget, string_type text) const
    {
        m_p_impl->set_text(widget, std::move(text));
    }

    widget::string_type widget::text(const gui::widget::widget& widget) const
    {
        return m_p_impl->text(widget);
    }

    void widget::set_font(gui::widget::widget& widget, const font_type& font) const
    {
        m_p_impl->set_font(widget, font);
    }

    widget::font_type widget::font(const gui::widget::widget& widget) const
    {
        return m_p_impl->font(widget);
    }

    std::vector<std::reference_wrapper<gui::widget::widget>> widget::children(gui::widget::widget& widget) const
    {
        return m_p_impl->children(widget);
    }

    void widget::repaint(gui::widget::widget& widget, const bool immediately) const
    {
        m_p_impl->repaint(widget, immediately);
    }

    void widget::repaint_partially(
        gui::widget::widget&                  widget,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        return m_p_impl->repaint_partially(widget, position, dimension);
    }

    void widget::activate(gui::widget::widget& widget) const
    {
        return m_p_impl->activate(widget);
    }

    void widget::set_icon(gui::widget::widget& widget, const gui::icon* p_icon) const
    {
        m_p_impl->set_icon(widget, p_icon);
    }

    void widget::set_menu_bar(gui::widget::widget& widget, const menu_base_type* p_menu /*= nullptr*/) const
    {
        m_p_impl->set_menu_bar(widget, p_menu);
    }

    bool widget::focusable(const gui::widget::widget& widget) const
    {
        return m_p_impl->focusable(widget);
    }

    void widget::set_focusable(gui::widget::widget& widget, const bool focusable) const
    {
        m_p_impl->set_focusable(widget, focusable);
    }

    void widget::set_focus(gui::widget::widget& widget) const
    {
        return m_p_impl->set_focus(widget);
    }

    bool widget::read_only(const gui::widget::widget& widget) const
    {
        return m_p_impl->read_only(widget);
    }

    void widget::set_read_only(gui::widget::widget& widget, const bool read_only) const
    {
        return m_p_impl->set_read_only(widget, read_only);
    }

    void widget::close(gui::widget::widget& widget) const;

    widget::size_type widget::dropdown_box_value_count(const gui::widget::dropdown_box& dropdown_box) const;

    widget::string_type
    widget::dropdown_box_value(const gui::widget::dropdown_box& dropdown_box, const size_type index) const;

    void widget::set_dropdown_box_value(
        gui::widget::dropdown_box& dropdown_box,
        const size_type            index,
        string_type                value) const;

    void widget::insert_dropdown_box_value(
        gui::widget::dropdown_box& dropdown_box,
        const size_type            index,
        string_type                value) const;

    void widget::erase_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, const size_type index) const;

    void widget::clear_dropdown_box(gui::widget::dropdown_box& dropdown_box) const;

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_dropdown_box_value_index(const gui::widget::dropdown_box& dropdown_box) const;

    void widget::select_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, const size_type index) const;

    widget::size_type widget::list_box_value_count(const gui::widget::list_box& list_box) const;

    widget::string_type widget::list_box_value(const gui::widget::list_box& list_box, const size_type index) const;

    void widget::set_list_box_value(gui::widget::list_box& list_box, const size_type index, string_type value) const;

    void widget::insert_list_box_value(gui::widget::list_box& list_box, const size_type index, string_type value) const;

    void widget::erase_list_box_value(gui::widget::list_box& list_box, const size_type index) const;

    void widget::clear_list_box(gui::widget::list_box& list_box) const;

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_list_box_value_index(const gui::widget::list_box& list_box) const;

    void widget::select_list_box_value(gui::widget::list_box& list_box, const size_type index) const;

    widget::size_type widget::progress_bar_goal(gui::widget::progress_bar& progress_bar) const;

    void widget::set_progress_bar_goal(gui::widget::progress_bar& progress_bar, const size_type goal) const;

    widget::size_type widget::progress_bar_progress(gui::widget::progress_bar& progress_bar) const;

    void widget::set_progress_bar_progress(gui::widget::progress_bar& progress_bar, const size_type progress) const;

    widget::progress_bar_state_type widget::progress_bar_state(gui::widget::progress_bar& progress_bar) const;

    void
    widget::set_progress_bar_state(gui::widget::progress_bar& progress_bar, const progress_bar_state_type state) const;

    widget::widget() : m_p_impl{ std::make_unique<impl>() } {}
}