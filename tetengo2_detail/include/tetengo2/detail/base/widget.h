/*! \file
    \brief The definition of tetengo2::detail::base::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_WIDGET_H)
#define TETENGO2_DETAIL_BASE_WIDGET_H

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/type_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>

namespace tetengo2 { namespace gui {
    class icon;

    namespace widget {
        class dropdown_box;
        class list_box;
        class progress_bar;
        class widget;
    }
}}


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a widget.
    */
    class widget : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = type_list::size_type;

        //! The string type.
        using string_type = type_list::string_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = int;

        //! The window state type.
        using window_state_type = int;

        //! The font type.
        struct font_type
        {
            string_type family;
            size_type   size;
            bool        bold;
            bool        italic;
            bool        underline;
            bool        strikeout;

            font_type() : family{}, size{}, bold{}, italic{}, underline{}, strikeout{} {}

            font_type(
                string_type     family,
                const size_type size,
                const bool      bold,
                const bool      italic,
                const bool      underline,
                const bool      strikeout)
            : family{ std::move(family) }, size{ size }, bold{ bold }, italic{ italic }, underline{ underline },
              strikeout{ strikeout }
            {}
        };

        //! The menu base type.
        struct menu_base_type
        {
        };

        //! The progress bar state type.
        using progress_bar_state_type = int;

        //! The widget details type.
        struct widget_details_type
        {
            /*!
                \brief Destroys the widget details.
            */
            virtual ~widget_details_type() = default;
        };

        //! The widget details pointer type.
        using widget_details_ptr_type = std::unique_ptr<widget_details_type>;


        // constructors and destructor;

        /*!
            \brief Destroys the detail implementation.
        */
        ~widget();


        // functions

        /*!
            \brief Creates a button.

            \param parent     A parent widget.
            \param is_default Set true to create a default button.
            \param is_cancel  Set true to create a cancel button.

            \return A unique pointer to a button.

            \throw std::invalid_argument When a default button already exists and is_default is true.
            \throw std::invalid_argument When a cancel button already exists and is_cancel is true.
            \throw std::system_error     When a button cannot be created.
        */
        widget_details_ptr_type create_button(gui::widget::widget& parent, bool is_default, bool is_cancel) const;

        /*!
            \brief Creates a custom control.

            \param parent           A parent widget.
            \param border           Set true to add border lines.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a custom control.

            \throw std::system_error When a custom control cannot be created.
        */
        widget_details_ptr_type
        create_custom_control(gui::widget::widget& parent, bool border, scroll_bar_style_type scroll_bar_style) const;

        /*!
            \brief Creates a dialog.

            \param p_parent       A pointer to a parent widget. When nullptr, the dialog has no parent.
            \param file_droppable Set true to enable file drop.

            \return A unique pointer to a dialog.

            \throw std::system_error When a dialog cannot be created.
        */
        widget_details_ptr_type create_dialog(gui::widget::widget* p_parent, bool file_droppable) const;

        /*!
            \brief Creates a dropdown box.

            \param parent A parent widget.

            \return A unique pointer to a dropdown box.

            \throw std::system_error When a dropdown box cannot be created.
        */
        widget_details_ptr_type create_dropdown_box(gui::widget::widget& parent) const;

        /*!
            \brief Creates an image.

            \param parent A parent widget.

            \return A unique pointer to an image.

            \throw std::system_error When an image cannot be created.
        */
        widget_details_ptr_type create_image(gui::widget::widget& parent) const;

        /*!
            \brief Creates a label.

            \param parent A parent widget.

            \return A unique pointer to a label.

            \throw std::system_error When a label cannot be created.
        */
        widget_details_ptr_type create_label(gui::widget::widget& parent) const;

        /*!
            \brief Creates a list box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a list box.

            \throw std::system_error When a list box cannot be created.
        */
        widget_details_ptr_type
        create_list_box(gui::widget::widget& parent, scroll_bar_style_type scroll_bar_style) const;

        /*!
            \brief Creates a picture box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a picture box.

            \throw std::system_error When a picture box cannot be created.
        */
        widget_details_ptr_type
        create_picture_box(gui::widget::widget& parent, scroll_bar_style_type scroll_bar_style) const;

        /*!
            \brief Creates a progress bar.

            \param parent A parent widget.

            \return A unique pointer to a picture box.

            \throw std::system_error When a picture box cannot be created.
        */
        widget_details_ptr_type create_progress_bar(gui::widget::widget& parent) const;

        /*!
            \brief Creates a text box.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a text box.

            \throw std::system_error When a text box cannot be created.
        */
        widget_details_ptr_type
        create_text_box(gui::widget::widget& parent, scroll_bar_style_type scroll_bar_style) const;

        /*!
            \brief Creates a window.

            \param p_parent         A pointer to a parent widget. When nullptr, the dialog has no parent.
            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.

            \return A unique pointer to a window.

            \throw std::system_error When a window cannot be created.
        */
        widget_details_ptr_type
        create_window(gui::widget::widget* p_parent, scroll_bar_style_type scroll_bar_style, bool file_droppable) const;

        /*!
            \brief Associates a widget to the native window system.

            \param widget A widget.

            \throw std::system_error When the widget cannot be associated.
        */
        void associate_to_native_window_system(gui::widget::widget& widget) const;

        /*!
            \brief Returns whether the widget has a parent.

            \param widget A widget.

            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        bool has_parent(const gui::widget::widget& widget) const;

        /*!
            \brief Returns the parent.

            \param widget A widget.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        gui::widget::widget& parent(gui::widget::widget& widget) const;

        /*!
            \brief Returns the root ancestor.

            \param widget A widget.

            \return The root ancestor.

            \throw std::logic_error When the widget has no root ancestor.
        */
        gui::widget::widget& root_ancestor(gui::widget::widget& widget) const;

        /*!
            \brief Sets an enabled status.

            \param widget A widget.
            \param enabled An enabled status.
        */
        void set_enabled(gui::widget::widget& widget, bool enabled) const;

        /*!
            \brief Returns the enabled status.

            \param widget A widget.

            \return The enabled status.
        */
        bool enabled(const gui::widget::widget& widget) const;

        /*!
            \brief Sets a visible status.

            \param widget A widget.
            \param visible A visible status.
        */
        void set_visible(gui::widget::widget& widget, bool visible) const;

        /*!
            \brief Returns the visible status.

            \param widget A widget.

            \return The visible status.
        */
        bool visible(const gui::widget::widget& widget) const;

        /*!
            \brief Sets a window state.

            \param widget A widget.
            \param state  A window state.

            \throw std::system_error When a window state cannot be set.
        */
        void set_window_state(gui::widget::widget& widget, const window_state_type state) const;

        /*!
            \brief Returns the window state.

            \param widget A widget.

            \return The window state.
        */
        window_state_type window_state(const gui::widget::widget& widget) const;

        /*!
            \brief Moves a widget.

            \param widget    A widget.
            \param position  A position.
            \param dimension A dimension.

            \throw std::system_error When the widget cannot be moved.
        */
        void move(
            gui::widget::widget&                  widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const;

        /*!
            \brief Returns the position.

            \param widget A widget.

            \return The position.

            \throw std::system_error When the position cannot be obtained.
        */
        gui::type_list::position_type position(const gui::widget::widget& widget) const;

        /*!
            \brief Calculates a position suitable for a dialog.

            \param widget A widget.
            \param parent A parent widget.

            \return A position.

            \throw std::system_error When a position cannot be calculated.
        */
        gui::type_list::position_type
        dialog_position(const gui::widget::widget& widget, const gui::widget::widget& parent) const;

        /*!
            \brief Returns the dimension.

            \param widget A widget.

            \return The dimension.

            \throw std::system_error When the dimension cannot be obtained.
        */
        gui::type_list::dimension_type dimension(const gui::widget::widget& widget) const;

        /*!
            \brief Sets a client dimension.

            \param widget           A widget.
            \param client_dimension A client dimension.

            \throw std::system_error When a client dimension cannot be set.
        */
        void
        set_client_dimension(gui::widget::widget& widget, const gui::type_list::dimension_type& client_dimension) const;

        /*!
            \brief Returns the client dimension.

            \param widget A widget.

            \return The client dimension.

            \throw std::system_error When the client dimension cannot be obtained.
        */
        gui::type_list::dimension_type client_dimension(const gui::widget::widget& widget) const;

        /*!
            \brief Returns the normal dimension.

            \param widget A widget.

            \return The normal dimension.

            \throw std::system_error When the normal dimension cannot be obtained.
        */
        gui::type_list::dimension_type normal_dimension(const gui::widget::widget& widget) const;

        /*!
            \brief Sets a text.

            \param widget  A widget.
            \param text    A text.

            \throw std::system_error When the text cannot be set.
        */
        void set_text(gui::widget::widget& widget, string_type text) const;

        /*!
            \brief Retuns the text.

            \param widget  A widget.

            \return The text.
        */
        string_type text(const gui::widget::widget& widget) const;

        /*!
            \brief Sets a font.

            \param widget  A widget.
            \param font    A font.

            \throw std::system_error When the font cannot be set.
        */
        void set_font(gui::widget::widget& widget, const font_type& font) const;

        /*!
            \brief Retuns the font.

            \param widget A widget.

            \return The font.

            \throw std::system_error When the font cannot be obtained.
        */
        font_type font(const gui::widget::widget& widget) const;

        /*!
            \brief Returns the children.

            \param widget A widget.

            \return The children.
        */
        std::vector<std::reference_wrapper<gui::widget::widget>> children(gui::widget::widget& widget) const;

        /*!
            \brief Repaints a widget.

            \param widget      A widget.
            \param immediately Set true to request an immediate repaint.

            \throw std::system_error When the widget cannot be repainted.
        */
        void repaint(gui::widget::widget& widget, bool immediately) const;

        /*!
            \brief Repaints a widget partially.

            \param widget    A widget.
            \param position  The position of a region to repaint.
            \param dimension The dimension of a region to repaint.

            \throw std::system_error When the widget cannot be repainted.
        */
        void repaint_partially(
            gui::widget::widget&                  widget,
            const gui::type_list::position_type&  position,
            const gui::type_list::dimension_type& dimension) const;

        /*!
            \brief Activates a widget.

            \param widget A widget.
        */
        void activate(gui::widget::widget& widget) const;

        /*!
            \brief Assigns an icon on a widget.

            \param widget A widget.
            \param p_icon A pointer to an icon.

            \throw std::system_error When an icon cannot be set.
        */
        void set_icon(gui::widget::widget& widget, const gui::icon* p_icon) const;

        /*!
            \brief Assigns a menu bar on a widget.

            \param widget A widget.
            \param p_menu A pointer to a menu. It may be nullptr to remove a menu bar.

            \throw std::system_error When a menu bar cannot be set.
        */
        void set_menu_bar(gui::widget::widget& widget, const menu_base_type* p_menu = nullptr) const;

        /*!
            \brief Checks whether a widget accepts a focus.

            \param widget A widget.

            \retval true  When the widget accepts a focus.
            \retval false Otherwise.

            \throw std::system_error When the focusable status cannot be obtained.
        */
        bool focusable(const gui::widget::widget& widget) const;

        /*!
            \brief Sets whether a widget accepts a focus.

            \param widget    A widget.
            \param focusable True when the widget accepts a focus.

            \throw std::system_error When a focusable status cannot be set.
        */
        void set_focusable(gui::widget::widget& widget, bool focusable) const;

        /*!
            \brief Focuses on a widget.

            \param widget A widget.
        */
        void set_focus(gui::widget::widget& widget) const;

        /*!
            \brief Checks whether a widget is read-only.

            \param widget A widget.

            \retval true  When the widget is read-only.
            \retval false Otherwise.

            \throw std::system_error When the read-only status cannot be obtained.
        */
        bool read_only(const gui::widget::widget& widget) const;

        /*!
            \brief Sets whether a widget is read-only.

            \param widget    A widget.
            \param read_only True when the widget is read-only.

            \throw std::system_error When the read-only status cannot be set.
        */
        void set_read_only(gui::widget::widget& widget, bool read_only) const;

        /*!
            \brief Closes a widget.

            \param widget A widget.

            \throw std::system_error When the widget cannot be closed.
        */
        void close(gui::widget::widget& widget) const;

        /*!
            \brief Returns the dropdown box value count.

            \param dropdown_box A dropdown box.

            \return The dropdown box value count.

            \throw std::system_error When the value cannot be obtained.
        */
        size_type dropdown_box_value_count(const gui::widget::dropdown_box& dropdown_box) const;

        /*!
            \brief Returns the dropdown box value.

            \param dropdown_box A dropdown box.
            \param index        An index.

            \return The dropdown box value.

            \throw std::system_error When the value cannot be obtained.
        */
        string_type dropdown_box_value(const gui::widget::dropdown_box& dropdown_box, size_type index) const;

        /*!
            \brief Sets a dropdown box value.

            \param dropdown_box A dropdown box.
            \param index        An index.
            \param value        An value.

            \throw std::system_error When the value cannot be set.
        */
        void set_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, size_type index, string_type value) const;

        /*!
            \brief Inserts a dropdown box value.

            \param dropdown_box A dropdown box.
            \param index        An index.
            \param value         An value.

            \throw std::system_error When the value cannot be inserted.
        */
        void
        insert_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, size_type index, string_type value) const;

        /*!
            \brief Erases a dropdown box value.

            \param dropdown_box A dropdown box.
            \param index    An index.

            \throw std::system_error When the value cannot be erased.
        */
        void erase_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, size_type index) const;

        /*!
            \brief Clears a dropdown box.

            \param dropdown_box A dropdown box.

            \throw std::system_error When the dropdown box cannot be cleared.
        */
        void clear_dropdown_box(gui::widget::dropdown_box& dropdown_box) const;

        /*!
            \brief Returns the selected dropdown box value index.

            \param dropdown_box A dropdown box.

            \return The selected dropdown box value index.

            \throw std::system_error When the selected value index cannot be obtained.
        */
        tetengo2::stdalt::optional<size_type>
        selected_dropdown_box_value_index(const gui::widget::dropdown_box& dropdown_box) const;

        /*!
            \brief Selects a dropdown box value.

            \param dropdown_box A dropdown box.
            \param index    An index.

            \throw std::system_error When the value cannot be selected.
        */
        void select_dropdown_box_value(gui::widget::dropdown_box& dropdown_box, size_type index) const;

        /*!
            \brief Returns the list box value count.

            \param list_box A list box.

            \return The list box value count.

            \throw std::system_error When the value cannot be obtained.
        */
        size_type list_box_value_count(const gui::widget::list_box& list_box) const;

        /*!
            \brief Returns the list box value.

            \param list_box A list box.
            \param index    An index.

            \return The list box value.

            \throw std::system_error When the value cannot be obtained.
        */
        string_type list_box_value(const gui::widget::list_box& list_box, size_type index) const;

        /*!
            \brief Sets a list box value.

            \param list_box A list box.
            \param index    An index.
            \param value    An value.

            \throw std::system_error When the value cannot be set.
        */
        void set_list_box_value(gui::widget::list_box& list_box, size_type index, string_type value) const;

        /*!
            \brief Inserts a list box value.

            \param list_box A list box.
            \param index    An index.
            \param value    An value.

            \throw std::system_error When the value cannot be inserted.
        */
        void insert_list_box_value(gui::widget::list_box& list_box, size_type index, string_type value) const;

        /*!
            \brief Erases a list box value.

            \param list_box A list box.
            \param index    An index.

            \throw std::system_error When the value cannot be erased.
        */
        void erase_list_box_value(gui::widget::list_box& list_box, size_type index) const;

        /*!
            \brief Clears a list box.

            \param list_box A list box.

            \throw std::system_error When the list box cannot be cleared.
        */
        void clear_list_box(gui::widget::list_box& list_box) const;

        /*!
            \brief Returns the selected list box value index.

            \param list_box A list box.

            \return The selected list box value index.

            \throw std::system_error When the selected value index cannot be obtained.
        */
        tetengo2::stdalt::optional<size_type>
        selected_list_box_value_index(const gui::widget::list_box& list_box) const;

        /*!
            \brief Selects a list box value.

            \param list_box A list box.
            \param index    An index.

            \throw std::system_error When the value cannot be selected.
        */
        void select_list_box_value(gui::widget::list_box& list_box, size_type index) const;

        /*!
            \brief Returns the progress bar goal.

            \param progress_bar A progress bar.

            \return The goal.

            \throw std::system_error When the goal cannot be obtained.
        */
        size_type progress_bar_goal(gui::widget::progress_bar& progress_bar) const;

        /*!
            \brief Sets a progress bar goal.

            \param progress_bar A progress bar.
            \param goal         A goal.

            \throw std::system_error When the goal cannot be set.
        */
        void set_progress_bar_goal(gui::widget::progress_bar& progress_bar, size_type goal) const;

        /*!
            \brief Returns the progress bar progress.

            \param progress_bar A progress bar.

            \return The progress.

            \throw std::system_error When the progress cannot be obtained.
        */
        size_type progress_bar_progress(gui::widget::progress_bar& progress_bar) const;

        /*!
            \brief Sets a progress bar progress.

            \param progress_bar A progress bar.
            \param progress     A progress.

            \throw std::system_error When the progress cannot be set.
        */
        void set_progress_bar_progress(gui::widget::progress_bar& progress_bar, size_type progress) const;

        /*!
            \brief Returns the progress bar state.

            \param progress_bar A progress bar.

            \return The state.

            \throw std::system_error When the state cannot be obtained.
        */
        progress_bar_state_type progress_bar_state(gui::widget::progress_bar& progress_bar) const;

        /*!
            \brief Sets a progress bar state.

            \param progress_bar A progress bar.
            \param state        A state.

            \throw std::system_error When the progress cannot be set.
        */
        void set_progress_bar_state(gui::widget::progress_bar& progress_bar, const progress_bar_state_type state) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        widget();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
