/*! \file
    \brief The definition of tetengo2::detail::stub::widget.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_WIDGET_H)
#define TETENGO2_DETAIL_STUB_WIDGET_H

#include <algorithm>
//#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <string>
#include <tuple>
//#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a widget.
    */
    class widget
    {
    public:
        // types

        //! The widget details type.
        typedef
            std::tuple<
                // details_p_parent: pointer to parent
                void*,

                // details_enabled: enabled status
                bool,

                // details_visible: visible status
                bool,

                // details_position: position
                std::pair<std::ptrdiff_t, std::ptrdiff_t>,

                // details_dimension: dimension and client dimension
                std::pair<std::size_t, std::size_t>,

                // details_text: text
                std::wstring,

                // details_font: font
                std::tuple<std::wstring, std::size_t, bool, bool, bool, bool>,

                // details_children: children
                std::vector<void*>
            >
            widget_details_type;

        //! The widget details pointer type.
        typedef
            cpp0x::unique_ptr<widget_details_type>::type
            widget_details_ptr_type;


        // static functions

        /*!
            \brief Creates a window.

            \tparam Widget A widget type.

            \param parent A parent widget.
                          When uninitialized, the window has no parent.

            \return A unique pointer to a window.
        */
        template <typename Widget>
        static widget_details_ptr_type create_window(
            const boost::optional<Widget&>& parent =
                boost::optional<Widget&>()
        )
        {
            return create_details<Widget>(parent ? &*parent : NULL);
        }

        /*!
            \brief Creates a dialog.

            \tparam Widget A widget type.

            \param parent A parent widget.
                          When uninitialized, the dialog has no parent.

            \return A unique pointer to a dialog.
        */
        template <typename Widget>
        static widget_details_ptr_type create_dialog(
            const boost::optional<Widget&>& parent
        )
        {
            return create_details<Widget>(parent ? &*parent : NULL);
        }

        /*!
            \brief Creates a button.

            \tparam Widget A widget type.

            \param parent     A parent widget.
            \param is_default Set true to create a default button.
            \param is_cancel  Set true to create a cancel button.

            \return A unique pointer to a button.
        */
        template <typename Widget>
        static widget_details_ptr_type create_button(
            Widget&    parent,
            const bool is_default,
            const bool is_cancel
        )
        {
            return create_details<Widget>(&parent);
        }

        /*!
            \brief Creates an image.

            \tparam Widget A widget type.

            \param parent A parent widget.

            \return A unique pointer to an image.
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
        */
        template <typename Widget>
        static widget_details_ptr_type create_label(Widget& parent)
        {
            return create_details<Widget>(&parent);
        }

        /*!
            \brief Associates a widget to the native window system.

            \tparam Widget A widget type.

            \param widget A widget.

            \throw std::runtime_error When the widget cannot be associated.
        */
        template <typename Widget>
        static void associate_to_native_window_system(Widget& widget)
        {
            if (widget.has_parent())
            {
                std::get<details_children>(
                    *widget.parent().details()
                ).push_back(reinterpret_cast<void*>(&widget));
            }

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
            return std::get<details_p_parent>(*widget.details());
        }

        /*!
            \brief Returns the parent.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The parent.

            \throw std::logic_error When the widget has no parent.
        */
        template <typename Widget>
        static Widget& parent(const Widget& widget)
        {
            if (!has_parent(widget))
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The widget has no parent.")
                );
            }

            return *reinterpret_cast<Widget*>(
                std::get<details_p_parent>(*widget.details())
            );
        }

        /*!
            \brief Returns the root ancestor.

            \tparam Widget A widget type.

            \param widget A widget.

            \return The root ancestor.

            \throw std::logic_error When the widget has no root ancestor.
        */
        template <typename Widget>
        static Widget& root_ancestor(const Widget& widget)
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
            std::get<details_enabled>(*widget.details()) = enabled;
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
            return std::get<details_enabled>(*widget.details());
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
            std::get<details_visible>(*widget.details()) = visible;
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
            return std::get<details_visible>(*widget.details());
        }

        /*!
            \brief Sets a position.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.
            \tparam Position  A position type.

            \param widget   A widget.
            \param position A position.
        */
        template <typename Dimension, typename Widget, typename Position>
        static void set_position(Widget& widget, const Position& position)
        {
            typedef gui::position<Position> position_traits_type;
            std::get<details_position>(*widget.details()) =
                std::make_pair(
                    gui::to_pixels<std::size_t>(
                        position_traits_type::left(position)
                    ),
                    gui::to_pixels<std::size_t>(
                        position_traits_type::top(position)
                    )
                );
        }

        /*!
            \brief Returns the position.

            \tparam Position  A position type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The position.
        */
        template <typename Position, typename Widget>
        static Position position(const Widget& widget)
        {
            typedef gui::position<Position> position_traits_type;
            return position_traits_type::make(
                gui::to_unit<typename position_traits_type::left_type>(
                    std::get<details_position>(*widget.details()).first
                ),
                gui::to_unit<typename position_traits_type::top_type>(
                    std::get<details_position>(*widget.details()).second
                )
            );
        }

        /*!
            \brief Sets a dimension.

            \tparam Position  A position type.
            \tparam Widget    A widget type.
            \tparam Dimension A dimension type.

            \param widget   A widget.
            \param dimension A dimension.
        */
        template <typename Position, typename Widget, typename Dimension>
        static void set_dimension(Widget& widget, const Dimension& dimension)
        {
            typedef gui::dimension<Dimension> dimension_traits_type;
            std::get<details_dimension>(*widget.details()) =
                std::make_pair(
                    gui::to_pixels<std::size_t>(
                        dimension_traits_type::width(dimension)
                    ),
                    gui::to_pixels<std::size_t>(
                        dimension_traits_type::height(dimension)
                    )
                );
        }

        /*!
            \brief Returns the dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The dimension.
        */
        template <typename Dimension, typename Widget>
        static Dimension dimension(const Widget& widget)
        {
            typedef gui::dimension<Dimension> dimension_traits_type;
            return dimension_traits_type::make(
                gui::to_unit<typename dimension_traits_type::width_type>(
                    std::get<details_dimension>(*widget.details()).first
                ),
                gui::to_unit<typename dimension_traits_type::height_type>(
                    std::get<details_dimension>(*widget.details()).second
                )
            );
        }

        /*!
            \brief Sets a client dimension.

            \tparam Position  A position type.
            \tparam Widget    A widget type.
            \tparam Dimension A dimension type.

            \param widget           A widget.
            \param client_dimension A client dimension.
        */
        template <typename Position, typename Widget, typename Dimension>
        static void set_client_dimension(
            Widget&          widget,
            const Dimension& client_dimension
        )
        {
            typedef gui::dimension<Dimension> dimension_traits_type;
            std::get<details_dimension>(*widget.details()) =
                std::make_pair(
                    gui::to_pixels<std::size_t>(
                        dimension_traits_type::width(client_dimension)
                    ),
                    gui::to_pixels<std::size_t>(
                        dimension_traits_type::height(client_dimension)
                    )
                );
        }

        /*!
            \brief Returns the client dimension.

            \tparam Dimension A dimension type.
            \tparam Widget    A widget type.

            \param widget A widget.

            \return The client dimension.
        */
        template <typename Dimension, typename Widget>
        static Dimension client_dimension(const Widget& widget)
        {
            typedef gui::dimension<Dimension> dimension_traits_type;
            return dimension_traits_type::make(
                gui::to_unit<typename dimension_traits_type::width_type>(
                    std::get<details_dimension>(*widget.details()).first
                ),
                gui::to_unit<typename dimension_traits_type::height_type>(
                    std::get<details_dimension>(*widget.details()).second
                )
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

            \throw std::runtime_error When the text cannot be set.
        */
        template <typename Widget, typename String, typename Encoder>
        static void set_text(
            Widget&        widget,
            String&&       text,
            const Encoder& encoder
        )
        {
            std::get<details_text>(*widget.details()) = encoder.encode(text);
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
            return encoder.decode(std::get<details_text>(*widget.details()));
        }

        /*!
            \brief Sets a font.

            \tparam Widget A widget type.
            \tparam Font   A font type.

            \param widget A widget.
            \param font   A font.

            \throw std::runtime_error When the font cannot be set.
        */
        template <typename Widget, typename Font>
        static void set_font(Widget& widget, const Font& font)
        {
            std::get<details_font>(*widget.details()) =
                details_font_type(
                    font.family(),
                    font.size(),
                    font.bold(),
                    font.italic(),
                    font.underline(),
                    font.strikeout()
                );
        }

        /*!
            \brief Retuns the font.

            \tparam Font   A font type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The font.
        */
        template <typename Font, typename Widget>
        static Font font(const Widget& widget)
        {
            const details_font_type& font =
                std::get<details_font>(*widget.details());
            return Font(
                std::get<0>(font),
                std::get<1>(font),
                std::get<2>(font),
                std::get<3>(font),
                std::get<4>(font),
                std::get<5>(font)
            );
        }

        /*!
            \brief Returns the children.

            \tparam Child A child type.
            \tparam Widget A widget type.

            \param widget A widget.

            \return The children.
        */
        template <typename Child, typename Widget>
        static std::vector<
            typename tetengo2::cpp0x::reference_wrapper<Child>::type
        > children(
            Widget& widget
        )
        {
            const std::vector<void*>& children_as_void =
                std::get<details_children>(*widget.details());
            std::vector<
                typename tetengo2::cpp0x::reference_wrapper<Child>::type
            > children;
            children.reserve(children_as_void.size());

            std::transform(
                children_as_void.begin(),
                children_as_void.end(),
                std::back_inserter(children),
                as_child<Child>
            );

            return children;
        }

        /*!
            \brief Uses a widget canvas.

            \tparam Widget   A widget type.
            \tparam Canvas   A canvas type.
            \tparam Result   A result type.
            \tparam Function A function type.

            \param widget   A widget.
            \param function A function.

            \return A result.
        */
        template <
            typename Canvas,
            typename Result,
            typename Widget,
            typename Function
        >
        static Result use_canvas(
            const Widget&  widget,
            const Function function
        )
        {
            const typename cpp0x::unique_ptr<Canvas>::type p_canvas(
                widget.create_canvas()
            );
            return function(*p_canvas);
        }

        /*!
            \brief Activates a widget.

            \tparam Widget A widget type.

            \param widget A widget.
        */
        template <typename Widget>
        static void activate(Widget& widget)
        {}

        /*!
            \brief Assigns a main menu on a widget.

            \tparam Widget A widget type.
            \tparam Menu   A menu type.

            \param widget A widget.
            \param menu   A menu.
                          It may be uninitialized to remove a main menu.
        */
        template <typename Widget, typename Menu>
        static void set_main_menu(
            Widget&                             widget,
            const boost::optional<const Menu&>& menu =
                boost::optional<const Menu&>()
        )
        {}

        /*!
            \brief Closes a widget.

            \tparam Widget A widget type.

            \param widget A widget.
        */
        template <typename Widget>
        static void close(Widget& widget)
        {}

        /*!
            \brief Opens a target.

            \tparam Widget A widget type.
            \tparam String A string type.

            \param widget A widget.
            \param target A target.
        */
        template <typename Widget, typename String>
        static void open_target(Widget& widget, const String& target)
        {}


    private:
        // types

        enum details
        {
            details_p_parent = 0,
            details_enabled,
            details_visible,
            details_position,
            details_dimension,
            details_text,
            details_font,
            details_children
        };

        typedef
            std::tuple<std::wstring, std::size_t, bool, bool, bool, bool>
            details_font_type;


        // static functions

        template <typename Widget>
        static widget_details_ptr_type create_details(Widget* const p_parent)
        {
            widget_details_ptr_type p_details = widget_details_ptr_type(
                new widget_details_type(
                    p_parent,
                    true,
                    true,
                    std::make_pair(0, 0),
                    std::make_pair(1, 1),
                    std::wstring(),
                    details_font_type(
                        std::wstring(), 12, false, false, false, false
                    ),
                    std::vector<void*>()
                )
            );

            return std::move(p_details);
        }

        template <typename Child>
        static typename tetengo2::cpp0x::reference_wrapper<Child>::type
        as_child(void* const pointer)
        {
            return tetengo2::cpp0x::ref(*reinterpret_cast<Child*>(pointer));
        }


        // forbidden operations

        widget();


    };


}}}


#endif
