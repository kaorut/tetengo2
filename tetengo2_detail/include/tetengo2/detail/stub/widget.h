/*! \file
    \brief The definition of tetengo2::detail::stub::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_WIDGET_H)
#define TETENGO2_DETAIL_STUB_WIDGET_H

#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui {
    class icon;

    namespace widget {
        class dropdown_box;
        class list_box;
        class progress_bar;
        class widget;
    }
}}


namespace tetengo2::detail::stub {
    /*!
        \brief The class for a detail implementation of a widget.
    */
    class widget : public base::widget
    {
    public:
        // types

        //! The size type.
        using size_type = base::widget::size_type;

        //! The string type.
        using string_type = base::widget::string_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = base::widget::scroll_bar_style_type;

        //! The window state type.
        using window_state_type = base::widget::window_state_type;

        //! The menu base type.
        using menu_base_type = base::widget::menu_base_type;

        //! The progress bar state type.
        using progress_bar_state_type = base::widget::progress_bar_state_type;

        //! The widget details type.
        struct widget_details_type : public base::widget::widget_details_type
        {
#if !defined(DOCUMENTATION)
            void*                                     p_parent;
            bool                                      enabled;
            bool                                      visible;
            int                                       window_state;
            std::pair<std::ptrdiff_t, std::ptrdiff_t> position;
            std::pair<std::size_t, std::size_t>       dimension;
            string_type                               text;
            gui::drawing::font                        font;
            std::vector<void*>                        children;
            bool                                      focusable;
            bool                                      read_only;
            std::vector<string_type>                  list_box_values;
            tetengo2::stdalt::optional<std::size_t>   selected_list_box_value_index;
            std::size_t                               progress_bar_goal;
            std::size_t                               progress_bar_progress;
            int                                       progress_bar_state;

            widget_details_type()
            : p_parent{}, enabled{}, visible{}, window_state{}, position{}, dimension{}, text{},
              font{ gui::drawing::font::dialog_font(stub::drawing::instance()) }, children{}, focusable{}, read_only{},
              list_box_values{}, selected_list_box_value_index{}, progress_bar_goal{}, progress_bar_progress{},
              progress_bar_state{}
            {}

            widget_details_type(
                void* const                               p_parent,
                const bool                                enabled,
                const bool                                visible,
                const int                                 window_state,
                std::pair<std::ptrdiff_t, std::ptrdiff_t> position,
                std::pair<std::size_t, std::size_t>       dimension,
                string_type                               text,
                gui::drawing::font                        font,
                std::vector<void*>                        children,
                const bool                                focusable,
                const bool                                read_only,
                std::vector<string_type>                  list_box_values,
                tetengo2::stdalt::optional<std::size_t>   selected_list_box_value_index,
                const std::size_t                         progress_bar_goal,
                const std::size_t                         progress_bar_progress,
                const int                                 progress_bar_state)
            : p_parent{ p_parent }, enabled{ enabled }, visible{ visible }, window_state{ window_state },
              position{ std::move(position) }, dimension{ std::move(dimension) }, text{ std::move(text) },
              font{ std::move(font) }, children{ std::move(children) }, focusable{ focusable }, read_only{ read_only },
              list_box_values{ std::move(list_box_values) }, selected_list_box_value_index{ std::move(
                                                                 selected_list_box_value_index) },
              progress_bar_goal{ progress_bar_goal }, progress_bar_progress{ progress_bar_progress },
              progress_bar_state{ progress_bar_state }
            {}

            virtual ~widget_details_type() = default;
#endif
        };

        //! The widget details pointer type.
        using widget_details_ptr_type = base::widget::widget_details_ptr_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const widget& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~widget();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        widget();


        // virtual functions

        virtual widget_details_ptr_type
        create_button_impl(gui::widget::widget& parent, const bool is_default, const bool is_cancel) const override;

        virtual widget_details_ptr_type create_custom_control_impl(
            gui::widget::widget&        parent,
            const bool                  border,
            const scroll_bar_style_type scroll_bar_style) const override;

        virtual widget_details_ptr_type
        create_dialog_impl(gui::widget::widget* const p_parent, const bool file_droppable) const override;

        virtual widget_details_ptr_type create_dropdown_box_impl(gui::widget::widget& parent) const override;

        virtual widget_details_ptr_type create_image_impl(gui::widget::widget& parent) const override;

        virtual widget_details_ptr_type create_label_impl(gui::widget::widget& parent) const override;

        virtual widget_details_ptr_type
        create_list_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const override;

        virtual widget_details_ptr_type create_picture_box_impl(
            gui::widget::widget&        parent,
            const scroll_bar_style_type scroll_bar_style) const override;

        virtual widget_details_ptr_type create_progress_bar_impl(gui::widget::widget& parent) const override;

        virtual widget_details_ptr_type
        create_text_box_impl(gui::widget::widget& parent, const scroll_bar_style_type scroll_bar_style) const override;

        virtual widget_details_ptr_type create_window_impl(
            gui::widget::widget* const  p_parent,
            const scroll_bar_style_type scroll_bar_style,
            const bool                  file_droppable) const override;

        virtual void associate_to_native_window_system_impl(gui::widget::widget& widget) const override;

        virtual bool has_parent_impl(const gui::widget::widget& widget) const override;

        virtual gui::widget::widget& parent_impl(const gui::widget::widget& widget) const override;

        virtual gui::widget::widget& root_ancestor_impl(const gui::widget::widget& widget) const override;

        virtual void set_enabled_impl(gui::widget::widget& widget, const bool enabled) const override;

        virtual bool enabled_impl(const gui::widget::widget& widget) const override;

        virtual void set_visible_impl(gui::widget::widget& widget, const bool visible) const override;

        virtual bool visible_impl(const gui::widget::widget& widget) const override;

        virtual void set_window_state_impl(gui::widget::widget& widget, const window_state_type state) const override;

        virtual window_state_type window_state_impl(const gui::widget::widget& widget) const override;

        virtual void move_impl(
            gui::widget::widget&                  widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const override;

        virtual gui::type_list::position_type position_impl(const gui::widget::widget& widget) const override;

        virtual gui::type_list::position_type
        dialog_position_impl(const gui::widget::widget& widget, const gui::widget::widget& parent) const override;

        virtual gui::type_list::dimension_type dimension_impl(const gui::widget::widget& widget) const override;

        virtual void set_client_dimension_impl(
            gui::widget::widget&                  widget,
            const gui::type_list::dimension_type& client_dimension) const override;

        virtual gui::type_list::dimension_type client_dimension_impl(const gui::widget::widget& widget) const override;

        virtual gui::type_list::dimension_type normal_dimension_impl(const gui::widget::widget& widget) const override;

        virtual void set_text_impl(gui::widget::widget& widget, string_type text) const override;

        virtual string_type text_impl(const gui::widget::widget& widget) const override;

        virtual void set_font_impl(gui::widget::widget& widget, const gui::drawing::font& font) const override;

        virtual gui::drawing::font font_impl(const gui::widget::widget& widget) const override;

        virtual std::vector<std::reference_wrapper<gui::widget::widget>>
        children_impl(gui::widget::widget& widget) const override;

        virtual void repaint_impl(const gui::widget::widget& widget, const bool immediately) const override;

        virtual void repaint_partially_impl(
            const gui::widget::widget&            widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const override;

        virtual void activate_impl(gui::widget::widget& widget) const override;

        virtual void set_icon_impl(gui::widget::widget& widget, const gui::icon* const p_icon) const override;

        virtual void
        set_menu_bar_impl(gui::widget::widget& widget, const menu_base_type* const p_menu = nullptr) const override;

        virtual bool focusable_impl(const gui::widget::widget& widget) const override;

        virtual void set_focusable_impl(gui::widget::widget& widget, const bool focusable) const override;

        virtual void set_focus_impl(gui::widget::widget& widget) const override;

        virtual bool read_only_impl(const gui::widget::widget& widget) const override;

        virtual void set_read_only_impl(gui::widget::widget& widget, const bool read_only) const override;

        virtual void close_impl(gui::widget::widget& widget) const override;

        virtual size_type dropdown_box_value_count_impl(const gui::widget::dropdown_box& dropdown_box) const override;

        virtual string_type
        dropdown_box_value_impl(const gui::widget::dropdown_box& dropdown_box, const size_type index) const override;

        virtual void set_dropdown_box_value_impl(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value) const override;

        virtual void insert_dropdown_box_value_impl(
            gui::widget::dropdown_box& dropdown_box,
            const size_type            index,
            string_type                value) const override;

        virtual void
        erase_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const override;

        virtual void clear_dropdown_box_impl(gui::widget::dropdown_box& dropdown_box) const override;

        virtual tetengo2::stdalt::optional<size_type>
        selected_dropdown_box_value_index_impl(const gui::widget::dropdown_box& dropdown_box) const override;

        virtual void
        select_dropdown_box_value_impl(gui::widget::dropdown_box& dropdown_box, const size_type index) const override;

        virtual size_type list_box_value_count_impl(const gui::widget::list_box& list_box) const override;

        virtual string_type
        list_box_value_impl(const gui::widget::list_box& list_box, const size_type index) const override;

        virtual void set_list_box_value_impl(gui::widget::list_box& list_box, const size_type index, string_type value)
            const override;

        virtual void insert_list_box_value_impl(
            gui::widget::list_box& list_box,
            const size_type        index,
            string_type            value) const override;

        virtual void erase_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const override;

        virtual void clear_list_box_impl(gui::widget::list_box& list_box) const override;

        virtual tetengo2::stdalt::optional<size_type>
        selected_list_box_value_index_impl(const gui::widget::list_box& list_box) const override;

        virtual void select_list_box_value_impl(gui::widget::list_box& list_box, const size_type index) const override;

        virtual size_type progress_bar_goal_impl(const gui::widget::progress_bar& progress_bar) const override;

        virtual void
        set_progress_bar_goal_impl(gui::widget::progress_bar& progress_bar, const size_type goal) const override;

        virtual size_type progress_bar_progress_impl(const gui::widget::progress_bar& progress_bar) const override;

        virtual void set_progress_bar_progress_impl(gui::widget::progress_bar& progress_bar, const size_type progress)
            const override;

        virtual progress_bar_state_type
        progress_bar_state_impl(const gui::widget::progress_bar& progress_bar) const override;

        virtual void set_progress_bar_state_impl(
            gui::widget::progress_bar&    progress_bar,
            const progress_bar_state_type state) const override;
    };
}


#endif
