/*! \file
    \brief The definition of tetengo2::detail::stub::widget.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_WIDGET_H)
#define TETENGO2_DETAIL_STUB_WIDGET_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2/gui/measure.h>
#include <tetengo2/utility.h>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a widget.
    */
    class widget : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = std::string;

#if !defined(DOCUMENTATION)
        struct details_font_type
        {
            string_type family;
            std::size_t size;
            bool bold;
            bool italic;
            bool underline;
            bool strikeout;

            details_font_type()
            :
            family(),
            size(),
            bold(),
            italic(),
            underline(),
            strikeout()
            {}

            details_font_type(
                string_type       family,
                const std::size_t size,
                const bool        bold,
                const bool        italic,
                const bool        underline,
                const bool        strikeout
            )
            :
            family(std::move(family)),
            size(size),
            bold(bold),
            italic(italic),
            underline(underline),
            strikeout(strikeout)
            {}

        };
#endif

        //! The widget details type.
        struct widget_details_type
        {
#if !defined(DOCUMENTATION)
            void* p_parent;
            bool enabled;
            bool visible;
            int window_state;
            std::pair<std::ptrdiff_t, std::ptrdiff_t> position;
            std::pair<std::size_t, std::size_t> dimension;
            string_type text;
            details_font_type font;
            std::vector<void*> children;
            bool focusable;
            bool read_only;
            std::vector<string_type> list_box_values;
            boost::optional<std::size_t> selected_list_box_value_index;

            widget_details_type()
            :
            p_parent(),
            enabled(),
            visible(),
            window_state(),
            position(),
            dimension(),
            text(),
            font(),
            children(),
            focusable(),
            read_only(),
            list_box_values(),
            selected_list_box_value_index()
            {}

            widget_details_type(
                void* const                                 p_parent,
                const bool                                  enabled,
                const bool                                  visible,
                const int                                   window_state,
                std::pair<std::ptrdiff_t, std::ptrdiff_t>   position,
                std::pair<std::size_t, std::size_t>         dimension,
                string_type                                 text,
                details_font_type                           font,
                std::vector<void*>                          children,
                const bool                                  focusable,
                const bool                                  read_only,
                std::vector<string_type>                    list_box_values,
                boost::optional<std::size_t>                selected_list_box_value_index
            )
            :
            p_parent(p_parent),
            enabled(enabled),
            visible(visible),
            window_state(window_state),
            position(std::move(position)),
            dimension(std::move(dimension)),
            text(std::move(text)),
            font(std::move(font)),
            children(std::move(children)),
            focusable(focusable),
            read_only(read_only),
            list_box_values(std::move(list_box_values)),
            selected_list_box_value_index(std::move(selected_list_box_value_index))
            {}
#endif

        };

        //! The widget details pointer type.
        using widget_details_ptr_type = std::unique_ptr<widget_details_type>;


        // static functions

        /*!
            \brief Creates a button.

            \tparam Widget A widget type.

            \param parent     A parent widget.
            \param is_default Set true to create a default button.
            \param is_cancel  Set true to create a cancel button.

            \return A unique pointer to a button.

            \throw std::invalid_argument When a default button already exists and is_default is true.
            \throw std::invalid_argument When a cancel button already exists and is_cancel is true.
            \throw std::system_error     When a button cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_button(Widget& parent, const bool is_default, const bool is_cancel)
        {
            suppress_unused_variable_warning(is_default, is_cancel);

            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates a custom control.

            \tparam Widget A widget type.

            \param parent           A parent widget.
            \param border           Set true to add border lines.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a custom control.

            \throw std::system_error When a custom control cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_custom_control(
            Widget&                                      parent,
            const bool                                   border,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            suppress_unused_variable_warning(border, scroll_bar_style);

            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates a dialog.

            \tparam Widget A widget type.

            \param p_parent       A pointer to a parent widget. When nullptr, the dialog has no parent.
            \param file_droppable Set true to enable file drop.

            \return A unique pointer to a dialog.

            \throw std::system_error When a dialog cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_dialog(Widget* const p_parent, const bool file_droppable)
        {
            suppress_unused_variable_warning(file_droppable);

            return create_details<Widget>(p_parent);
        }

        /*!
            \brief Creates a dropdown box.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to a dropdown box.

            \throw std::system_error When a dropdown box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_dropdown_box(Widget& parent)
        {
            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates an image.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to an image.

            \throw std::system_error When an image cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_image(Widget& parent)
        {
            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates a label.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to a label.

            \throw std::system_error When a label cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_label(Widget& parent)
        {
            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates a list box.

            \tparam Widget A widget type.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a list box.

            \throw std::system_error When a list box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_list_box(
            Widget&                                      parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            suppress_unused_variable_warning(scroll_bar_style);

            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates a picture box.

            \tparam Widget A widget type.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a picture box.

            \throw std::system_error When a picture box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_picture_box(
            Widget&                                      parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            suppress_unused_variable_warning(scroll_bar_style);

            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates a text box.

            \tparam Widget A widget type.

            \param parent           A parent widget.
            \param scroll_bar_style A scroll bar style.

            \return A unique pointer to a text box.

            \throw std::system_error When a text box cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_text_box(
            Widget&                                      parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style
        )
        {
            suppress_unused_variable_warning(scroll_bar_style);

            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates a window.

            \tparam Widget A widget type.

            \param p_parent         A pointer to a parent widget. When nullptr, the dialog has no parent.
            \param scroll_bar_style A scroll bar style.
            \param file_droppable   Set true to enable file drop.

            \return A unique pointer to a window.

            \throw std::system_error When a window cannot be created.
        */
        template <typename Widget>
        static widget_details_ptr_type create_window(
            Widget* const                                p_parent,
            const typename Widget::scroll_bar_style_type scroll_bar_style,
            const bool                                   file_droppable
        )
        {
            suppress_unused_variable_warning(scroll_bar_style, file_droppable);

            return create_details<Widget>(p_parent);
        }

        /*!
            \brief Associates a widget to the native window system.

            \tparam Widget A widget type.

            \param widget A widget.

            \throw std::system_error When the widget cannot be associated.
        */
        template <typename Widget>
        static void associate_to_native_window_system(Widget& widget)
        {
            if (widget.has_parent())
                widget.parent().details().children.push_back(reinterpret_cast<void*>(&widget));
        }

        /*!
            \brief Returns whether the widget has a parent.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        template <typename Widget>
        static bool has_parent(const Widget& widget)
        {
            return widget.details().p_parent != nullptr;
        }

        /*!
            \brief Returns the parent.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        template <typename Widget>
        static Widget& parent(Widget& widget)
        {
            if (!has_parent(widget))
                BOOST_THROW_EXCEPTION((std::logic_error{ "The widget has no parent." }));

            return *reinterpret_cast<Widget*>(widget.details().p_parent);
        }

        /*!
            \brief Returns the root ancestor.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The root ancestor.

            \throw std::logic_error When the widget has no root ancestor.
        */
        template <typename Widget>
        static Widget& root_ancestor(Widget& widget)
        {
            return parent(widget);
        }

        /*!
            \brief Sets an enabled status.

            \tparam Widget A widget type.

            \param widget A widget.
            \param enabled An enabled status.
        */
        template <typename Widget>
        static void set_enabled(Widget& widget, const bool enabled)
        {
            widget.details().enabled = enabled;
        }

        /*!
            \brief Returns the enabled status.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The enabled status.
        */
        template <typename Widget>
        static bool enabled(const Widget& widget)
        {
            return widget.details().enabled;
        }

        /*!
            \brief Sets a visible status.

            \tparam Widget A widget type.

            \param widget A widget.
            \param visible A visible status.
        */
        template <typename Widget>
        static void set_visible(Widget& widget, const bool visible)
        {
            widget.details().visible = visible;
        }

        /*!
            \brief Returns the visible status.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The visible status.
        */
        template <typename Widget>
        static bool visible(const Widget& widget)
        {
            return widget.details().visible;
        }

        /*!
            \brief Sets a window state.

            \tparam WindowState A window state type.
            \tparam Widget      A widget type.

            \param widget A widget.
            \param state  A window state.

            \throw std::system_error When a window state cannot be set.
        */
        template <typename WindowState, typename Widget>
        static void set_window_state(Widget& widget, const WindowState state)
        {
            widget.details().window_state = static_cast<int>(state);
        }

        /*!
            \brief Returns the window state.

            \tparam WindowState A window state type.
            \tparam Widget      A widget type.

            \param widget A widget.

            \return The window state.
        */
        template <typename WindowState, typename Widget>
        static WindowState window_state(const Widget& widget)
        {
            return static_cast<WindowState>(widget.details().window_state);
        }

        /*!
            \brief Moves a widget.

            \tparam Widget    A widget type.
            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param widget    A widget.
            \param position  A position.
            \param dimension A dimension.

            \throw std::system_error When the widget cannot be moved.
        */
        template <typename Widget, typename Position, typename Dimension>
        static void move(Widget& widget, const Position& position, const Dimension& dimension)
        {
// This using somehow won't compile with gcc 4.7 on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
            using position_traits_type = gui::position<Position>;
            using dimension_traits_type = gui::dimension<Dimension>;
#else
            typedef gui::position<Position> position_traits_type;
            typedef gui::dimension<Dimension> dimension_traits_type;
#endif
            widget.details().position =
                std::make_pair(
                    gui::to_pixels<std::size_t>(position_traits_type::left(position)),
                    gui::to_pixels<std::size_t>(position_traits_type::top(position))
                );
            widget.details().dimension =
                std::make_pair(
                    gui::to_pixels<std::size_t>(dimension_traits_type::width(dimension)),
                    gui::to_pixels<std::size_t>(dimension_traits_type::height(dimension))
                );
        }

        /*!
            \brief Returns the position.

            \tparam Position  A position type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The position.

            \throw std::system_error When the position cannot be obtained.
        */
        template <typename Position, typename Widget>
        static Position position(const Widget& widget)
        {
// This using somehow won't compile with gcc 4.7 on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
            using position_traits_type = gui::position<Position>;
#else
            typedef gui::position<Position> position_traits_type;
#endif
            return
                position_traits_type::make(
                    gui::to_unit<typename position_traits_type::left_type>(widget.details().position.first),
                    gui::to_unit<typename position_traits_type::top_type>(widget.details().position.second)
                );
        }

        /*!
            \brief Calculates a position suitable for a dialog.

            \tparam Position     A position type.
            \tparam Widget       A widget type.
            \tparam ParentWidget A parent widget type.

            \param widget A widget.
            \param parent A parent widget.

            \return A position.

            \throw std::system_error When a position cannot be calculated.
        */
        template <typename Position, typename Widget, typename ParentWidget>
        static Position dialog_position(const Widget& widget, const ParentWidget& parent)
        {
            suppress_unused_variable_warning(widget);

            return position<Position>(parent);
        }

        /*!
            \brief Returns the dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The dimension.

            \throw std::system_error When the dimension cannot be obtained.
        */
        template <typename Dimension, typename Widget>
        static Dimension dimension(const Widget& widget)
        {
// This using somehow won't compile with gcc 4.7 on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
            using dimension_traits_type = gui::dimension<Dimension>;
#else
            typedef gui::dimension<Dimension> dimension_traits_type;
#endif
            return
                dimension_traits_type::make(
                    gui::to_unit<typename dimension_traits_type::width_type>(widget.details().dimension.first),
                    gui::to_unit<typename dimension_traits_type::height_type>(widget.details().dimension.second)
                );
        }

        /*!
            \brief Sets a client dimension.

            \tparam Position  A position type.
            \tparam Widget    A widget type.
            \tparam Dimension A dimension type.

            \param widget           A widget.
            \param client_dimension A client dimension.

            \throw std::system_error When a client dimension cannot be set.
        */
        template <typename Position, typename Widget, typename Dimension>
        static void set_client_dimension(Widget& widget, const Dimension& client_dimension)
        {
// This using somehow won't compile with gcc 4.7 on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
            using dimension_traits_type = gui::dimension<Dimension>;
#else
            typedef gui::dimension<Dimension> dimension_traits_type;
#endif
            widget.details().dimension =
                std::make_pair(
                    gui::to_pixels<std::size_t>(dimension_traits_type::width(client_dimension)),
                    gui::to_pixels<std::size_t>(dimension_traits_type::height(client_dimension))
                );
        }

        /*!
            \brief Returns the client dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The client dimension.

            \throw std::system_error When the client dimension cannot be obtained.
        */
        template <typename Dimension, typename Widget>
        static Dimension client_dimension(const Widget& widget)
        {
// This using somehow won't compile with gcc 4.7 on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
            using dimension_traits_type = gui::dimension<Dimension>;
#else
            typedef gui::dimension<Dimension> dimension_traits_type;
#endif
            return
                dimension_traits_type::make(
                    gui::to_unit<typename dimension_traits_type::width_type>(widget.details().dimension.first),
                    gui::to_unit<typename dimension_traits_type::height_type>(widget.details().dimension.second)
                );
        }

        /*!
            \brief Returns the normal dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The normal dimension.

            \throw std::system_error When the normal dimension cannot be obtained.
        */
        template <typename Dimension, typename Widget>
        static Dimension normal_dimension(const Widget& widget)
        {
// This using somehow won't compile with gcc 4.7 on Linux.
#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
            using dimension_traits_type = gui::dimension<Dimension>;
#else
            typedef gui::dimension<Dimension> dimension_traits_type;
#endif
            return
                dimension_traits_type::make(
                    gui::to_unit<typename dimension_traits_type::width_type>(widget.details().dimension.first),
                    gui::to_unit<typename dimension_traits_type::height_type>(widget.details().dimension.second)
                );
        }

        /*!
            \brief Sets a text.

            \tparam Widget  A widget type.
            \tparam String  A string type.
            \tparam Encoder An eocder type.

            \param widget  A widget.
            \param text    A text.
            \param encoder An encoder.

            \throw std::system_error When the text cannot be set.
        */
        template <typename Widget, typename String, typename Encoder>
        static void set_text(Widget& widget, String text, const Encoder& encoder)
        {
            widget.details().text = encoder.encode(std::move(text));
        }

        /*!
            \brief Retuns the text.

            \tparam String  A string type.
            \tparam Widget  A widget type.
            \tparam Encoder An eocder type.

            \param widget  A widget.
            \param encoder An encoder.

            \return The text.
        */
        template <typename String, typename Widget, typename Encoder>
        static String text(const Widget& widget, const Encoder& encoder)
        {
            return encoder.decode(widget.details().text);
        }

        /*!
            \brief Sets a font.

            \tparam Widget  A widget type.
            \tparam Font    A font type.
            \tparam Encoder An encoder type.

            \param widget  A widget.
            \param font    A font.
            \param encoder An encoder.

            \throw std::system_error When the font cannot be set.
        */
        template <typename Widget, typename Font, typename Encoder>
        static void set_font(Widget& widget, const Font& font, const Encoder& encoder)
        {
            widget.details().font =
                details_font_type{
                    encoder.encode(font.family()),
                    font.size(),
                    font.bold(),
                    font.italic(),
                    font.underline(),
                    font.strikeout()
                };
        }

        /*!
            \brief Retuns the font.

            \tparam Font   A font type.
            \tparam Widget A widget type.
            \tparam Encoder An encoder type.

            \param widget  A widget.
            \param encoder An encoder.

            \return The font.

            \throw std::system_error When the font cannot be obtained.
        */
        template <typename Font, typename Widget, typename Encoder>
        static Font font(const Widget& widget, const Encoder& encoder)
        {
            const auto& font = widget.details().font;
            return
                Font{ encoder.decode(font.family), font.size, font.bold, font.italic, font.underline, font.strikeout };
        }

        /*!
            \brief Returns the children.

            \tparam Child A child type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The children.
        */
        template <typename Child, typename Widget>
        static std::vector<std::reference_wrapper<Child>> children(Widget& widget)
        {
            const auto& children_as_void = widget.details().children;
            std::vector<std::reference_wrapper<Child>> children{};
            children.reserve(children_as_void.size());

            std::transform(
                children_as_void.begin(), children_as_void.end(), std::back_inserter(children), as_child<Child>
            );

            return children;
        }

        /*!
            \brief Repaints a widget.

            \tparam Widget A widget type.

            \param widget      A widget.
            \param immediately Set true to request an immediate repaint.

            \throw std::system_error When the widget cannot be repainted.
        */
        template <typename Widget>
        static void repaint(Widget& widget, const bool immediately)
        {
            suppress_unused_variable_warning(widget, immediately);
        }

        /*!
            \brief Repaints a widget partially.

            \tparam Widget    A widget type.
            \tparam Position  A position type.
            \tparam Dimension A dimension type.

            \param widget    A widget.
            \param position  The position of a region to repaint.
            \param dimension The dimension of a region to repaint.

            \throw std::system_error When the widget cannot be repainted.
        */
        template <typename Widget, typename Position, typename Dimension>
        static void repaint_partially(Widget& widget, const Position& position, const Dimension& dimension)
        {
            suppress_unused_variable_warning(widget, position, dimension);
        }

        /*!
            \brief Uses a widget canvas.

            \tparam Result   A result type.
            \tparam Widget   A widget type.
            \tparam Function A function type.

            \param widget   A widget.
            \param function A function.

            \return A result.
        */
        template <typename Result, typename Widget, typename Function>
        static Result use_canvas(const Widget& widget, const Function function)
        {
            const std::unique_ptr<typename Widget::canvas_type> p_canvas(widget.create_canvas());
            return function(*p_canvas);
        }

        /*!
            \brief Activates a widget.

            \tparam Widget A widget type.

            \param widget A widget.
        */
        template <typename Widget>
        static void activate(Widget& widget)
        {
            suppress_unused_variable_warning(widget);
        }

        /*!
            \brief Assigns an icon on a widget.

            \tparam Widget A widget type.
            \tparam Icon   An icon type.

            \param widget A widget.
            \param p_icon A pointer to an icon.

            \throw std::system_error When an icon cannot be set.
        */
        template <typename Widget, typename Icon>
        static void set_icon(Widget& widget, const Icon* const p_icon)
        {
            suppress_unused_variable_warning(widget, p_icon);
        }

        /*!
            \brief Assigns a menu bar on a widget.

            \tparam Widget   A widget type.
            \tparam MenuBase A menu base type.

            \param widget A widget.
            \param menu   A menu. It may be uninitialized to remove a menu bar.

            \throw std::system_error When a menu bar cannot be set.
        */
        template <typename Widget, typename MenuBase>
        static void set_menu_bar(Widget& widget, const boost::optional<const MenuBase&>& menu = boost::none)
        {
            suppress_unused_variable_warning(widget, menu);
        }

        /*!
            \brief Checks whether a widget accepts a focus.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget accepts a focus.
            \retval false Otherwise.

            \throw std::system_error When the focusable status cannot be obtained.
        */
        template <typename Widget>
        static bool focusable(const Widget& widget)
        {
            return widget.details().focusable;
        }

        /*!
            \brief Sets whether a widget accepts a focus.

            \tparam Widget A widget type.

            \param widget    A widget.
            \param focusable True when the widget accepts a focus.

            \throw std::system_error When a focusable status cannot be set.
        */
        template <typename Widget>
        static void set_focusable(Widget& widget, const bool focusable)
        {
            widget.details().focusable = focusable;
        }

        /*!
            \brief Focuses on a widget.

            \param widget A widget.
        */
        template <typename Widget>
        static void set_focus(Widget& widget)
        {
            suppress_unused_variable_warning(widget);
        }

        /*!
            \brief Checks whether a widget is read-only.

            \tparam Widget A widget type.

            \param widget A widget.

            \retval true  When the widget is read-only.
            \retval false Otherwise.

            \throw std::system_error When the read-only status cannot be obtained.
        */
        template <typename Widget>
        static bool read_only(const Widget& widget)
        {
            return widget.details().read_only;
        }

        /*!
            \brief Sets whether a widget is read-only.

            \tparam Widget A widget type.

            \param widget    A widget.
            \param read_only True when the widget is read-only.

            \throw std::system_error When the read-only status cannot be set.
        */
        template <typename Widget>
        static void set_read_only(Widget& widget, const bool read_only)
        {
            widget.details().read_only = read_only;
        }

        /*!
            \brief Closes a widget.

            \tparam Widget A widget type.

            \param widget A widget.

            \throw std::system_error When the widget cannot be closed.
        */
        template <typename Widget>
        static void close(Widget& widget)
        {
            suppress_unused_variable_warning(widget);
        }

        /*!
            \brief Returns the dropdown box value count.

            \tparam Size        A size type.
            \tparam DropdownBox A dropdown box type.

            \param dropdown_box A dropdown box.

            \return The dropdown box value count.

            \throw std::system_error When the value cannot be obtained.
        */
        template <typename Size, typename DropdownBox>
        static Size dropdown_box_value_count(const DropdownBox& dropdown_box)
        {
            return dropdown_box.details().list_box_values.size();
        }

        /*!
            \brief Returns the dropdown box value.

            \tparam String      A string type.
            \tparam DropdownBox A dropdown box type.
            \tparam Size        A size type.
            \tparam Encoder     An encoder type.

            \param dropdown_box A dropdown box.
            \param index        An index.
            \param encoder      An encoder.

            \return The dropdown box value.

            \throw std::system_error When the value cannot be obtained.
        */
        template <typename String, typename DropdownBox, typename Size, typename Encoder>
        static String dropdown_box_value(const DropdownBox& dropdown_box, const Size index, const Encoder& encoder)
        {
            return encoder.decode(dropdown_box.details().list_box_values[index]);
        }

        /*!
            \brief Sets a dropdown box value.

            \tparam DropdownBox A dropdown box type.
            \tparam Size        A size type.
            \tparam String      A string type.
            \tparam Encoder     An encoder type.

            \param dropdown_box A dropdown box.
            \param index        An index.
            \param value         An value.
            \param encoder      An encoder.

            \throw std::system_error When the value cannot be set.
        */
        template <typename DropdownBox, typename Size, typename String, typename Encoder>
        static void set_dropdown_box_value(
            DropdownBox&   dropdown_box,
            const Size     index,
            String         value,
            const Encoder& encoder
        )
        {
            dropdown_box.details().list_box_values[index] = encoder.encode(std::move(value));
        }

        /*!
            \brief Inserts a dropdown box value.

            \tparam DropdownBox A dropdown box type.
            \tparam Size        A size type.
            \tparam String      A string type.
            \tparam Encoder     An encoder type.

            \param dropdown_box A dropdown box.
            \param index        An index.
            \param value         An value.
            \param encoder      An encoder.

            \throw std::system_error When the value cannot be inserted.
        */
        template <typename DropdownBox, typename Size, typename String, typename Encoder>
        static void insert_dropdown_box_value(
            DropdownBox&   dropdown_box,
            const Size     index,
            String         value,
            const Encoder& encoder
        )
        {
            dropdown_box.details().list_box_values.insert(
                boost::next(dropdown_box.details().list_box_values.begin(), index), encoder.encode(std::move(value))
            );
        }

        /*!
            \brief Erases a dropdown box value.

            \tparam DropdownBox A dropdown box type.
            \tparam Size    A size type.

            \param dropdown_box A dropdown box.
            \param index    An index.

            \throw std::system_error When the value cannot be erased.
        */
        template <typename DropdownBox, typename Size>
        static void erase_dropdown_box_value(DropdownBox& dropdown_box, const Size index)
        {
            dropdown_box.details().list_box_values.erase(
                boost::next(dropdown_box.details().list_box_values.begin(), index)
            );
        }

        /*!
            \brief Clears a dropdown box.

            \tparam DropdownBox A dropdown box type.

            \param dropdown_box A dropdown box.

            \throw std::system_error When the dropdown box cannot be cleared.
        */
        template <typename DropdownBox>
        static void clear_dropdown_box(DropdownBox& dropdown_box)
        {
            dropdown_box.details().list_box_values.clear();
        }

        /*!
            \brief Returns the selected dropdown box value index.

            \tparam Size    A size type.
            \tparam DropdownBox A dropdown box type.

            \param dropdown_box A dropdown box.

            \return The selected dropdown box value index.

            \throw std::system_error When the selected value index cannot be obtained.
        */
        template <typename Size, typename DropdownBox>
        static boost::optional<Size> selected_dropdown_box_value_index(const DropdownBox& dropdown_box)
        {
            return dropdown_box.details().selected_list_box_value_index;
        }

        /*!
            \brief Selects a dropdown box value.

            \tparam DropdownBox A dropdown box type.
            \tparam Size    A size type.

            \param dropdown_box A dropdown box.
            \param index    An index.

            \throw std::system_error When the value cannot be selected.
        */
        template <typename DropdownBox, typename Size>
        static void select_dropdown_box_value(DropdownBox& dropdown_box, const Size index)
        {
            dropdown_box.details().selected_list_box_value_index = boost::make_optional<std::size_t>(index);
        }

        /*!
            \brief Returns the list box value count.

            \tparam Size    A size type.
            \tparam ListBox A list box type.

            \param list_box A list box.

            \return The list box value count.

            \throw std::system_error When the value cannot be obtained.
        */
        template <typename Size, typename ListBox>
        static Size list_box_value_count(const ListBox& list_box)
        {
            return list_box.details().list_box_values.size();
        }

        /*!
            \brief Returns the list box value.

            \tparam String  A string type.
            \tparam ListBox A list box type.
            \tparam Size    A size type.
            \tparam Encoder An encoder type.

            \param list_box A list box.
            \param index    An index.
            \param encoder  An encoder.

            \return The list box value.

            \throw std::system_error When the value cannot be obtained.
        */
        template <typename String, typename ListBox, typename Size, typename Encoder>
        static String list_box_value(const ListBox& list_box, const Size index, const Encoder& encoder)
        {
            return encoder.decode(list_box.details().list_box_values[index]);
        }

        /*!
            \brief Sets a list box value.

            \tparam ListBox A list box type.
            \tparam Size    A size type.
            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param list_box A list box.
            \param index    An index.
            \param value    An value.
            \param encoder  An encoder.

            \throw std::system_error When the value cannot be set.
        */
        template <typename ListBox, typename Size, typename String, typename Encoder>
        static void set_list_box_value(ListBox& list_box, const Size index, String value, const Encoder& encoder)
        {
            list_box.details().list_box_values[index] = encoder.encode(std::move(value));
        }

        /*!
            \brief Inserts a list box value.

            \tparam ListBox A list box type.
            \tparam Size    A size type.
            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param list_box A list box.
            \param index    An index.
            \param value    An value.
            \param encoder  An encoder.

            \throw std::system_error When the value cannot be inserted.
        */
        template <typename ListBox, typename Size, typename String, typename Encoder>
        static void insert_list_box_value(ListBox& list_box, const Size index, String value, const Encoder& encoder)
        {
            list_box.details().list_box_values.insert(
                boost::next(list_box.details().list_box_values.begin(), index), encoder.encode(std::move(value))
            );
        }

        /*!
            \brief Erases a list box value.

            \tparam ListBox A list box type.
            \tparam Size    A size type.

            \param list_box A list box.
            \param index    An index.

            \throw std::system_error When the value cannot be erased.
        */
        template <typename ListBox, typename Size>
        static void erase_list_box_value(ListBox& list_box, const Size index)
        {
            list_box.details().list_box_values.erase(boost::next(list_box.details().list_box_values.begin(), index));
        }

        /*!
            \brief Clears a list box.

            \tparam ListBox A list box type.

            \param list_box A list box.

            \throw std::system_error When the list box cannot be cleared.
        */
        template <typename ListBox>
        static void clear_list_box(ListBox& list_box)
        {
            list_box.details().list_box_values.clear();
        }

        /*!
            \brief Returns the selected list box value index.

            \tparam Size    A size type.
            \tparam ListBox A list box type.

            \param list_box A list box.

            \return The selected list box value index.

            \throw std::system_error When the selected value index cannot be obtained.
        */
        template <typename Size, typename ListBox>
        static boost::optional<Size> selected_list_box_value_index(const ListBox& list_box)
        {
            return list_box.details().selected_list_box_value_index;
        }

        /*!
            \brief Selects a list box value.

            \tparam ListBox A list box type.
            \tparam Size    A size type.

            \param list_box A list box.
            \param index    An index.

            \throw std::system_error When the value cannot be selected.
        */
        template <typename ListBox, typename Size>
        static void select_list_box_value(ListBox& list_box, const Size index)
        {
            list_box.details().selected_list_box_value_index = boost::make_optional<std::size_t>(index);
        }


    private:
        // static functions

        template <typename Widget>
        static widget_details_ptr_type create_details(Widget* const p_parent)
        {
            widget_details_ptr_type p_details{
                stdalt::make_unique<widget_details_type>(
                    p_parent,
                    true,
                    true,
                    0,
                    std::make_pair(0, 0),
                    std::make_pair(1, 1),
                    string_type{},
                    details_font_type{ string_type{}, 12, false, false, false, false },
                    std::vector<void*>{},
                    false,
                    false,
                    std::vector<string_type>{},
                    boost::none
                )
            };

            return std::move(p_details);
        }

        template <typename Child>
        static std::reference_wrapper<Child> as_child(void* const pointer)
        {
            return std::ref(*reinterpret_cast<Child*>(pointer));
        }


        // forbidden operations

        widget()
        = delete;


    };


}}}


#endif