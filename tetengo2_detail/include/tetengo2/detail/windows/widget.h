/*! \file
    \brief The definition of tetengo2::detail::windows::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_WIDGET_H)
#define TETENGO2_DETAIL_WINDOWS_WIDGET_H

#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

//#pragma warning(push)
//#pragma warning(disable : 4005)
//#include <intsafe.h>
//#include <stdint.h> // IWYU pragma: keep
//#pragma warning(pop)
//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/encoding/locale.h>

namespace tetengo2 { namespace gui { namespace drawing {
    class font;
}}}


namespace tetengo2::detail::windows {
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
        using widget_details_type = base::widget::widget_details_type;

        //! The windows widget details type.
        struct windows_widget_details_type : public widget_details_type
        {
            //! The handle.
            std::intptr_t handle;

            //! The window procedure.
            std::intptr_t window_procedure;

            //! The handle to the first child.
            std::intptr_t first_child_handle;

            //! The window state when hidden.
            int window_state_when_hidden;

            /*!
                \brief Creates a windows widget details.

                \param handle             A handle.
                \param window_procedure   A window procedure.
                \param first_child_handle A handle to the first child.
            */
            windows_widget_details_type(
                std::intptr_t handle,
                std::intptr_t window_procedure,
                std::intptr_t first_child_handle);

            /*!
                \brief Destroys the window widget details.
            */
            virtual ~windows_widget_details_type() noexcept;
        };

        //! The widget details pointer type.
        using widget_details_ptr_type = base::widget::widget_details_ptr_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const widget& instance();

        /*!
            \brief Returns the window property key.

            This function is for an internal use.

            \return The window property key.
        */
        static const std::wstring& property_key_for_cpp_instance();

        /*!
            \brief Returns a pointer to a widget by a widget handle.

            This function is for an internal use.

            \param widget_handle A widget handle.

            \return A pointer to a widget.
        */
        static gui::widget::widget* p_widget_from(std::intptr_t widget_handle);


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
