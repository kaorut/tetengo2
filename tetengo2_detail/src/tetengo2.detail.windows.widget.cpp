/*! \file
    \brief The definition of tetengo2::detail::windows::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/widget/dropdown_box.h>
#include <tetengo2/gui/widget/list_box.h>
#include <tetengo2/gui/widget/progress_bar.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::detail::windows {
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


        // static functions

        static const widget& instance()
        {
            static const widget singleton;
            return singleton;
        }


        // functions

        widget_details_ptr_type create_button_impl(
            gui::widget::widget&                    parent,
            TETENGO2_STDALT_MAYBE_UNUSED const bool is_default,
            TETENGO2_STDALT_MAYBE_UNUSED const bool is_cancel) const
        {
            return create_details(&parent);
        }

        widget_details_ptr_type create_custom_control_impl(
            gui::widget::widget&                    parent,
            TETENGO2_STDALT_MAYBE_UNUSED const bool border,
            TETENGO2_STDALT_MAYBE_UNUSED const scroll_bar_style_type scroll_bar_style) const
        {
            return create_details(&parent);
        }

        widget_details_ptr_type create_dialog_impl(
            gui::widget::widget* const              p_parent,
            TETENGO2_STDALT_MAYBE_UNUSED const bool file_droppable) const
        {
            return create_details(p_parent);
        }

        widget_details_ptr_type create_dropdown_box_impl(gui::widget::widget& parent) const
        {
            return create_details(&parent);
        }

        widget_details_ptr_type create_image_impl(gui::widget::widget& parent) const
        {
            return create_details(&parent);
        }

        widget_details_ptr_type create_label_impl(gui::widget::widget& parent) const
        {
            return create_details(&parent);
        }

        widget_details_ptr_type create_list_box_impl(
            gui::widget::widget&               parent,
            TETENGO2_STDALT_MAYBE_UNUSED const scroll_bar_style_type scroll_bar_style) const
        {
            return create_details(&parent);
        }

        widget_details_ptr_type create_picture_box_impl(
            gui::widget::widget&               parent,
            TETENGO2_STDALT_MAYBE_UNUSED const scroll_bar_style_type scroll_bar_style) const
        {
            return create_details(&parent);
        }

        widget_details_ptr_type create_progress_bar_impl(gui::widget::widget& parent) const
        {
            return create_details(&parent);
        }
        widget_details_ptr_type create_text_box_impl(
            gui::widget::widget&               parent,
            TETENGO2_STDALT_MAYBE_UNUSED const scroll_bar_style_type scroll_bar_style) const
        {
            return create_details(&parent);
        }

        widget_details_ptr_type create_window_impl(
            gui::widget::widget* const         p_parent,
            TETENGO2_STDALT_MAYBE_UNUSED const scroll_bar_style_type scroll_bar_style,
            TETENGO2_STDALT_MAYBE_UNUSED const bool                  file_droppable) const
        {
            return create_details(p_parent);
        }

        void associate_to_native_window_system_impl(gui::widget::widget& widget) const
        {
            if (widget.has_parent())
                widget.parent().details().children.push_back(reinterpret_cast<void*>(&widget));
        }

        bool has_parent_impl(const gui::widget::widget& widget) const
        {
            return widget.details().p_parent != nullptr;
        }

        gui::widget::widget& parent_impl(const gui::widget::widget& widget) const
        {
            if (!has_parent_impl(widget))
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no parent." }));

            return *reinterpret_cast<gui::widget::widget*>(widget.details().p_parent);
        }

        gui::widget::widget& root_ancestor_impl(const gui::widget::widget& widget) const
        {
            return parent_impl(widget);
        }

        void set_enabled_impl(gui::widget::widget& widget, const bool enabled) const
        {
            widget.details().enabled = enabled;
        }

        bool enabled_impl(const gui::widget::widget& widget) const
        {
            return widget.details().enabled;
        }

        void set_visible_impl(gui::widget::widget& widget, const bool visible) const
        {
            widget.details().visible = visible;
        }

        bool visible_impl(const gui::widget::widget& widget) const
        {
            return widget.details().visible;
        }

        void set_window_state_impl(gui::widget::widget& widget, const window_state_type state) const
        {
            widget.details().window_state = static_cast<int>(state);
        }

        window_state_type window_state_impl(const gui::widget::widget& widget) const
        {
            return static_cast<window_state_type>(widget.details().window_state);
        }

        void move_impl(
            gui::widget::widget&                  widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const
        {
            widget.details().position = std::make_pair(position.left().to_pixels(), position.top().to_pixels());
            widget.details().dimension = std::make_pair(dimension.width().to_pixels(), dimension.height().to_pixels());
        }

        gui::type_list::position_type position_impl(const gui::widget::widget& widget) const
        {
            return { gui::type_list::position_unit_type::from_pixels(widget.details().position.first),
                     gui::type_list::position_unit_type::from_pixels(widget.details().position.second) };
        }

        gui::type_list::position_type dialog_position_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
            const gui::widget::widget&                              parent) const
        {
            return position_impl(parent);
        }

        gui::type_list::dimension_type dimension_impl(const gui::widget::widget& widget) const
        {
            return gui::type_list::dimension_type{
                gui::type_list::dimension_unit_type::from_pixels(widget.details().dimension.first),
                gui::type_list::dimension_unit_type::from_pixels(widget.details().dimension.second)
            };
        }

        void set_client_dimension_impl(
            gui::widget::widget&                  widget,
            const gui::type_list::dimension_type& client_dimension) const
        {
            widget.details().dimension =
                std::make_pair(client_dimension.width().to_pixels(), client_dimension.height().to_pixels());
        }

        gui::type_list::dimension_type client_dimension_impl(const gui::widget::widget& widget) const
        {
            return gui::type_list::dimension_type{
                gui::type_list::dimension_unit_type::from_pixels(widget.details().dimension.first),
                gui::type_list::dimension_unit_type::from_pixels(widget.details().dimension.second)
            };
        }

        gui::type_list::dimension_type normal_dimension_impl(const gui::widget::widget& widget) const
        {
            return gui::type_list::dimension_type{
                gui::type_list::dimension_unit_type::from_pixels(widget.details().dimension.first),
                gui::type_list::dimension_unit_type::from_pixels(widget.details().dimension.second)
            };
        }

        void set_text_impl(gui::widget::widget& widget, string_type text) const
        {
            widget.details().text = std::move(text);
        }

        string_type text_impl(const gui::widget::widget& widget) const
        {
            return widget.details().text;
        }

        void set_font_impl(gui::widget::widget& widget, const font_type& font) const
        {
            widget.details().font = font;
        }

        font_type font_impl(const gui::widget::widget& widget) const
        {
            return widget.details().font;
        }

        std::vector<std::reference_wrapper<gui::widget::widget>> children_impl(gui::widget::widget& widget) const
        {
            const auto&                                              children_as_void = widget.details().children;
            std::vector<std::reference_wrapper<gui::widget::widget>> children{};
            children.reserve(children_as_void.size());

            std::transform(children_as_void.begin(), children_as_void.end(), std::back_inserter(children), as_child);

            return children;
        }

        void repaint_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const bool                 immediately) const
        {}

        void repaint_partially_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::position_type& position,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::type_list::dimension_type& dimension) const
        {}

        void activate_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const {}

        void set_icon_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const gui::icon* const p_icon) const
        {}

        void set_menu_bar_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const menu_base_type* const p_menu = nullptr) const
        {}

        bool focusable_impl(const gui::widget::widget& widget) const
        {
            return widget.details().focusable;
        }

        void set_focusable_impl(gui::widget::widget& widget, const bool focusable) const
        {
            widget.details().focusable = focusable;
        }

        void set_focus_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const {}

        bool read_only_impl(const gui::widget::widget& widget) const
        {
            return widget.details().read_only;
        }

        void set_read_only_impl(gui::widget::widget& widget, const bool read_only) const
        {
            widget.details().read_only = read_only;
        }

        void close_impl(TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget) const {}

        size_type dropdown_box_value_count_impl(const gui::widget::dropdown_box& dropdown_box) const
        {
            return dropdown_box.details().list_box_values.size();
        }

        string_type dropdown_box_value_impl(const gui::widget::dropdown_box& dropdown_box, const size_type index) const
        {
            return dropdown_box.details().list_box_values[index];
        }

        void set_dropdown_box_value_impl(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value) const
        {
            dropdown_box.details().list_box_values[index] = std::move(value);
        }

        void insert_dropdown_box_value_impl(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value) const
        {
            dropdown_box.details().list_box_values.insert(
                std::next(dropdown_box.details().list_box_values.begin(), index), std::move(value));
        }

        void erase_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const
        {
            dropdown_box.details().list_box_values.erase(
                std::next(dropdown_box.details().list_box_values.begin(), index));
            if (dropdown_box.details().selected_list_box_value_index &&
                *dropdown_box.details().selected_list_box_value_index >= dropdown_box.details().list_box_values.size())
            {
                dropdown_box.details().selected_list_box_value_index = TETENGO2_STDALT_NULLOPT;
            }
        }

        void clear_dropdown_box_impl(gui::widget::dropdown_box& dropdown_box) const
        {
            dropdown_box.details().list_box_values.clear();
            dropdown_box.details().selected_list_box_value_index = TETENGO2_STDALT_NULLOPT;
        }

        tetengo2::stdalt::optional<size_type>
        selected_dropdown_box_value_index_impl(const gui::widget::dropdown_box& dropdown_box) const
        {
            return dropdown_box.details().selected_list_box_value_index;
        }

        void select_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const
        {
            dropdown_box.details().selected_list_box_value_index =
                tetengo2::stdalt::make_optional(static_cast<std::size_t>(index));
        }

        size_type list_box_value_count_impl(const gui::widget::list_box& list_box) const
        {
            return list_box.details().list_box_values.size();
        }

        string_type list_box_value_impl(const gui::widget::list_box& list_box, const size_type index) const
        {
            return list_box.details().list_box_values[index];
        }

        void set_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value) const
        {
            list_box.details().list_box_values[index] = std::move(value);
        }

        void insert_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value) const
        {
            list_box.details().list_box_values.insert(
                std::next(list_box.details().list_box_values.begin(), index), std::move(value));
        }

        void erase_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const
        {
            list_box.details().list_box_values.erase(std::next(list_box.details().list_box_values.begin(), index));
            if (list_box.details().selected_list_box_value_index &&
                *list_box.details().selected_list_box_value_index >= list_box.details().list_box_values.size())
            {
                list_box.details().selected_list_box_value_index = TETENGO2_STDALT_NULLOPT;
            }
        }

        void clear_list_box_impl(gui::widget::list_box& list_box) const
        {
            list_box.details().list_box_values.clear();
            list_box.details().selected_list_box_value_index = TETENGO2_STDALT_NULLOPT;
        }

        tetengo2::stdalt::optional<size_type>
        selected_list_box_value_index_impl(const gui::widget::list_box& list_box) const
        {
            return list_box.details().selected_list_box_value_index;
        }

        void select_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const
        {
            list_box.details().selected_list_box_value_index =
                tetengo2::stdalt::make_optional(static_cast<std::size_t>(index));
        }

        size_type progress_bar_goal_impl(const gui::widget::progress_bar& progress_bar) const
        {
            return progress_bar.details().progress_bar_goal;
        }

        void set_progress_bar_goal_impl(gui::widget::progress_bar& progress_bar, const size_type goal) const
        {
            progress_bar.details().progress_bar_goal = goal;
        }

        size_type progress_bar_progress_impl(const gui::widget::progress_bar& progress_bar) const
        {
            return progress_bar.details().progress_bar_progress;
        }

        void set_progress_bar_progress_impl(gui::widget::progress_bar& progress_bar, const size_type progress) const
        {
            progress_bar.details().progress_bar_progress = progress;
        }

        progress_bar_state_type progress_bar_state_impl(const gui::widget::progress_bar& progress_bar) const
        {
            switch (progress_bar.details().progress_bar_state)
            {
            case 0:
                return static_cast<progress_bar_state_type>(gui::widget::progress_bar::state_type::running);
            case 1:
                return static_cast<progress_bar_state_type>(gui::widget::progress_bar::state_type::pausing);
            default:
                return static_cast<progress_bar_state_type>(gui::widget::progress_bar::state_type::error);
            }
        }

        void
        set_progress_bar_state_impl(gui::widget::progress_bar& progress_bar, const progress_bar_state_type state) const
        {
            switch (static_cast<gui::widget::progress_bar::state_type>(state))
            {
            case gui::widget::progress_bar::state_type::running:
                progress_bar.details().progress_bar_state = 0;
                break;
            case gui::widget::progress_bar::state_type::pausing:
                progress_bar.details().progress_bar_state = 1;
                break;
            default:
                assert(
                    static_cast<gui::widget::progress_bar::state_type>(state) ==
                    gui::widget::progress_bar::state_type::error);
                progress_bar.details().progress_bar_state = 2;
                break;
            }
        }


    private:
        // static functions

        static widget_details_ptr_type create_details(gui::widget::widget* const p_parent)
        {
            widget_details_ptr_type p_details{ std::make_unique<widget_details_type>(
                p_parent,
                true,
                true,
                0,
                std::make_pair(0, 0),
                std::make_pair(1, 1),
                string_type{},
                font_type{ string_type{}, 12, false, false, false, false },
                std::vector<void*>{},
                false,
                false,
                std::vector<string_type>{},
                TETENGO2_STDALT_NULLOPT,
                100,
                0,
                0) };

            return p_details;
        }

        static std::reference_wrapper<gui::widget::widget> as_child(void* const pointer)
        {
            return std::ref(*reinterpret_cast<gui::widget::widget*>(pointer));
        }
    };


    const widget& widget::instance()
    {
        return impl::instance();
    }

    widget::~widget() = default;

    widget::widget() : m_p_impl{ std::make_unique<impl>() } {}

    widget::widget_details_ptr_type
    widget::create_button_impl(gui::widget::widget& parent, const bool is_default, const bool is_cancel) const
    {
        return m_p_impl->create_button_impl(parent, is_default, is_cancel);
    }

    widget::widget_details_ptr_type widget::create_custom_control_impl(
        gui::widget::widget&        parent,
        const bool                  border,
        const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_custom_control_impl(parent, border, scroll_bar_style);
    }

    widget::widget_details_ptr_type
    widget::create_dialog_impl(gui::widget::widget* const p_parent, const bool file_droppable) const
    {
        return m_p_impl->create_dialog_impl(p_parent, file_droppable);
    }

    widget::widget_details_ptr_type widget::create_dropdown_box_impl(gui::widget::widget& parent) const
    {
        return m_p_impl->create_dropdown_box_impl(parent);
    }

    widget::widget_details_ptr_type widget::create_image_impl(gui::widget::widget& parent) const
    {
        return m_p_impl->create_image_impl(parent);
    }

    widget::widget_details_ptr_type widget::create_label_impl(gui::widget::widget& parent) const
    {
        return m_p_impl->create_label_impl(parent);
    }

    widget::widget_details_ptr_type
    widget::create_list_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_list_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type
    widget::create_picture_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_picture_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type widget::create_progress_bar_impl(gui::widget::widget& parent) const
    {
        return m_p_impl->create_progress_bar_impl(parent);
    }

    widget::widget_details_ptr_type
    widget::create_text_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const
    {
        return m_p_impl->create_text_box_impl(parent, scroll_bar_style);
    }

    widget::widget_details_ptr_type widget::create_window_impl(
        gui::widget::widget* const  p_parent,
        const scroll_bar_style_type scroll_bar_style,
        const bool                  file_droppable) const
    {
        return m_p_impl->create_window_impl(p_parent, scroll_bar_style, file_droppable);
    }

    void widget::associate_to_native_window_system_impl(gui::widget::widget& widget) const
    {
        m_p_impl->associate_to_native_window_system_impl(widget);
    }

    bool widget::has_parent_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->has_parent_impl(widget);
    }

    gui::widget::widget& widget::parent_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->parent_impl(widget);
    }

    gui::widget::widget& widget::root_ancestor_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->root_ancestor_impl(widget);
    }

    void widget::set_enabled_impl(gui::widget::widget& widget, const bool enabled) const
    {
        m_p_impl->set_enabled_impl(widget, enabled);
    }

    bool widget::enabled_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->enabled_impl(widget);
    }

    void widget::set_visible_impl(gui::widget::widget& widget, const bool visible) const
    {
        m_p_impl->set_visible_impl(widget, visible);
    }

    bool widget::visible_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->visible_impl(widget);
    }

    void widget::set_window_state_impl(gui::widget::widget& widget, const window_state_type state) const
    {
        m_p_impl->set_window_state_impl(widget, state);
    }

    widget::window_state_type widget::window_state_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->window_state_impl(widget);
    }

    void widget::move_impl(
        gui::widget::widget&                  widget,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->move_impl(widget, position, dimension);
    }

    gui::type_list::position_type widget::position_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->position_impl(widget);
    }

    gui::type_list::position_type
    widget::dialog_position_impl(const gui::widget::widget& widget, const gui::widget::widget& parent) const
    {
        return m_p_impl->dialog_position_impl(widget, parent);
    }

    gui::type_list::dimension_type widget::dimension_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->dimension_impl(widget);
    }

    void widget::set_client_dimension_impl(
        gui::widget::widget&                  widget,
        const gui::type_list::dimension_type& client_dimension) const
    {
        m_p_impl->set_client_dimension_impl(widget, client_dimension);
    }

    gui::type_list::dimension_type widget::client_dimension_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->client_dimension_impl(widget);
    }

    gui::type_list::dimension_type widget::normal_dimension_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->normal_dimension_impl(widget);
    }

    void widget::set_text_impl(gui::widget::widget& widget, string_type text) const
    {
        m_p_impl->set_text_impl(widget, std::move(text));
    }

    widget::string_type widget::text_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->text_impl(widget);
    }

    void widget::set_font_impl(gui::widget::widget& widget, const font_type& font) const
    {
        m_p_impl->set_font_impl(widget, font);
    }

    widget::font_type widget::font_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->font_impl(widget);
    }

    std::vector<std::reference_wrapper<gui::widget::widget>> widget::children_impl(gui::widget::widget& widget) const
    {
        return m_p_impl->children_impl(widget);
    }

    void widget::repaint_impl(const gui::widget::widget& widget, const bool immediately) const
    {
        m_p_impl->repaint_impl(widget, immediately);
    }

    void widget::repaint_partially_impl(
        const gui::widget::widget&            widget,
        const gui::type_list::position_type&  position,
        const gui::type_list::dimension_type& dimension) const
    {
        m_p_impl->repaint_partially_impl(widget, position, dimension);
    }

    void widget::activate_impl(gui::widget::widget& widget) const
    {
        m_p_impl->activate_impl(widget);
    }

    void widget::set_icon_impl(gui::widget::widget& widget, const gui::icon* const p_icon) const
    {
        m_p_impl->set_icon_impl(widget, p_icon);
    }

    void widget::set_menu_bar_impl(gui::widget::widget& widget, const menu_base_type* const p_menu /*= nullptr*/) const
    {
        m_p_impl->set_menu_bar_impl(widget, p_menu);
    }

    bool widget::focusable_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->focusable_impl(widget);
    }

    void widget::set_focusable_impl(gui::widget::widget& widget, const bool focusable) const
    {
        m_p_impl->set_focusable_impl(widget, focusable);
    }

    void widget::set_focus_impl(gui::widget::widget& widget) const
    {
        m_p_impl->set_focus_impl(widget);
    }

    bool widget::read_only_impl(const gui::widget::widget& widget) const
    {
        return m_p_impl->read_only_impl(widget);
    }

    void widget::set_read_only_impl(gui::widget::widget& widget, const bool read_only) const
    {
        m_p_impl->set_read_only_impl(widget, read_only);
    }

    void widget::close_impl(gui::widget::widget& widget) const
    {
        m_p_impl->close_impl(widget);
    }

    widget::size_type widget::dropdown_box_value_count_impl(const gui::widget::dropdown_box& dropdown_box) const
    {
        return m_p_impl->dropdown_box_value_count_impl(dropdown_box);
    }

    widget::string_type
    widget::dropdown_box_value_impl(const gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        return m_p_impl->dropdown_box_value_impl(dropdown_box, index);
    }

    void widget::set_dropdown_box_value_impl(
        gui::widget::dropdown_box& dropdown_box,
        const size_type            index,
        string_type                value) const
    {
        m_p_impl->set_dropdown_box_value_impl(dropdown_box, index, std::move(value));
    }

    void widget::insert_dropdown_box_value_impl(
        gui::widget::dropdown_box& dropdown_box,
        const size_type            index,
        string_type                value) const
    {
        return m_p_impl->insert_dropdown_box_value_impl(dropdown_box, index, std::move(value));
    }

    void widget::erase_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        m_p_impl->erase_dropdown_box_value_impl(dropdown_box, index);
    }

    void widget::clear_dropdown_box_impl(gui::widget::dropdown_box& dropdown_box) const
    {
        m_p_impl->clear_dropdown_box_impl(dropdown_box);
    }

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_dropdown_box_value_index_impl(const gui::widget::dropdown_box& dropdown_box) const
    {
        return m_p_impl->selected_dropdown_box_value_index_impl(dropdown_box);
    }

    void widget::select_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const
    {
        m_p_impl->select_dropdown_box_value_impl(dropdown_box, index);
    }

    widget::size_type widget::list_box_value_count_impl(const gui::widget::list_box& list_box) const
    {
        return m_p_impl->list_box_value_count_impl(list_box);
    }

    widget::string_type widget::list_box_value_impl(const gui::widget::list_box& list_box, const size_type index) const
    {
        return m_p_impl->list_box_value_impl(list_box, index);
    }

    void
    widget::set_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value) const
    {
        m_p_impl->set_list_box_value_impl(list_box, index, std::move(value));
    }

    void
    widget::insert_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value) const
    {
        m_p_impl->insert_list_box_value_impl(list_box, index, std::move(value));
    }

    void widget::erase_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const
    {
        m_p_impl->erase_list_box_value_impl(list_box, index);
    }

    void widget::clear_list_box_impl(gui::widget::list_box& list_box) const
    {
        m_p_impl->clear_list_box_impl(list_box);
    }

    tetengo2::stdalt::optional<widget::size_type>
    widget::selected_list_box_value_index_impl(const gui::widget::list_box& list_box) const
    {
        return m_p_impl->selected_list_box_value_index_impl(list_box);
    }

    void widget::select_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const
    {
        m_p_impl->select_list_box_value_impl(list_box, index);
    }

    widget::size_type widget::progress_bar_goal_impl(const gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_goal_impl(progress_bar);
    }

    void widget::set_progress_bar_goal_impl(gui::widget::progress_bar& progress_bar, const size_type goal) const
    {
        m_p_impl->set_progress_bar_goal_impl(progress_bar, goal);
    }

    widget::size_type widget::progress_bar_progress_impl(const gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_progress_impl(progress_bar);
    }

    void widget::set_progress_bar_progress_impl(gui::widget::progress_bar& progress_bar, const size_type progress) const
    {
        m_p_impl->set_progress_bar_progress_impl(progress_bar, progress);
    }

    widget::progress_bar_state_type widget::progress_bar_state_impl(const gui::widget::progress_bar& progress_bar) const
    {
        return m_p_impl->progress_bar_state_impl(progress_bar);
    }

    void widget::set_progress_bar_state_impl(
        gui::widget::progress_bar&    progress_bar,
        const progress_bar_state_type state) const
    {
        return m_p_impl->set_progress_bar_state_impl(progress_bar, state);
    }
}
