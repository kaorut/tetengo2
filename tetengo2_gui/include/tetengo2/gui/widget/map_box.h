/*! \file
    \brief The definition of tetengo2::gui::widget::map_box.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_MAPBOX_H)
#define TETENGO2_GUI_WIDGET_MAPBOX_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/rational.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a map box.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class map_box : public custom_control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The integer size type.
        using int_size_type = typename traits_type::int_size_type;

        //! The solid background type.
        using solid_background_type = typename traits_type::solid_background_type;

        //! The system color set type.
        using system_color_set_type = typename traits_type::system_color_set_type;

        //! The system cursor type.
        using system_cursor_type = typename traits_type::system_cursor_type;

        //! The cursor type.
        using cursor_type = typename system_cursor_type::base_type;

        //! The list selection observer set type.
        using list_selection_observer_set_type = typename traits_type::list_selection_observer_set_type;

        //! The detail implementation type of a widget.
        using widget_details_type = WidgetDetails;

        //! The detail implementation type of a message handler.
        using message_handler_details_type = MessageHandlerDetails;

        //! The base type.
        using base_type =
            custom_control<typename traits_type::base_type, widget_details_type, message_handler_details_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type::base_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The left type.
        using left_type = typename gui::position<position_type>::left_type;

        //! The mouse observer set type.
        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        //! The value type.
        using value_type = std::pair<string_type, string_type>;

        //! The detail implementation type.
        using details_type = typename widget_details_type::widget_details_type;


        // constructors and destructor

        /*!
            \brief Creates a map box.

            \param parent A parent widget.
        */
        explicit map_box(widget_type& parent)
        :
        base_type(parent, true, scroll_bar_style_type::vertical),
        m_splitter_position(left_type(8)),
        m_p_splitter(),
        m_p_value_items(),
        m_selected_value_index(),
        m_list_selection_observer_call_requested(false),
        m_list_selection_observer_set()
        {
            initialize_map_box(*this);
        }

        /*!
            \brief Destroys the map box.
        */
        virtual ~map_box()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


        // functions

        /*!
            \brief Returns the value count.

            \return The value count.
        */
        int_size_type value_count()
        const
        {
            return m_p_value_items.size();
        }

        /*!
            \brief Returns the value.

            \param index An index.

            \return The value.

            \throw std::out_of_range When index is out of the range.
        */
        const value_type& value(const int_size_type index)
        const
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return m_p_value_items[index]->value();
        }

        /*!
            \brief Sets an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void set_value(const int_size_type index, value_type value)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            m_p_value_items[index]->value() = std::move(value);

            if (this->visible())
                this->size_observer_set().resized()();
        }

        /*!
            \brief Inserts an value.

            \param index An index.
            \param value An value.

            \throw std::out_of_range When index is out of the range.
        */
        void insert_value(const int_size_type index, value_type value)
        {
            if (index > value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            m_p_value_items.insert(
                boost::next(m_p_value_items.begin(), index), stdalt::make_unique<value_item>(*this, std::move(value))
            );
            if (m_selected_value_index && index <= *m_selected_value_index)
            {
                ++(*m_selected_value_index);
                request_list_selection_observer_call();
            }

            if (this->visible())
                this->size_observer_set().resized()();
        }

        /*!
            \brief Erases an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void erase_value(const int_size_type index)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            m_p_value_items.erase(boost::next(m_p_value_items.begin(), index));
            if (m_selected_value_index)
            {
                if      (index == *m_selected_value_index)
                    m_selected_value_index = boost::none;
                else if (index < *m_selected_value_index)
                    --(*m_selected_value_index);
                request_list_selection_observer_call();
            }

            if (this->visible())
                this->size_observer_set().resized()();
        }

        /*!
            \brief Clears the list box.
        */
        void clear()
        {
            m_p_value_items.clear();
            if (m_selected_value_index)
            {
                m_selected_value_index = boost::none;
                request_list_selection_observer_call();
            }

            if (this->visible())
                this->size_observer_set().resized()();
        }

        /*!
            \brief Returns the selected value index.

            \return The selected value index. Or boost::none when no value is selected.
        */
        boost::optional<int_size_type> selected_value_index()
        const
        {
            return m_selected_value_index;
        }

        /*!
            \brief Selects an value.

            \param index An index.

            \throw std::out_of_range When index is out of the range.
        */
        void select_value(const int_size_type index)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            m_selected_value_index = boost::make_optional(index);
            ensure_selected_value_shown();
            request_list_selection_observer_call();
        }

        /*!
            \brief Returns the splitter position.

            \return The splitter position.
        */
        const left_type& splitter_position()
        const
        {
            return m_splitter_position;
        }

        /*!
            \brief Sets a splitter position.

            \param position A position.
        */
        void set_splitter_position(left_type position)
        {
            m_p_splitter->move(std::move(position));
        }

        /*!
            \brief Returns the list selection observer set.

            \return The list selection observer set.
        */
        const list_selection_observer_set_type& list_selection_observer_set()
        const
        {
            return m_list_selection_observer_set;
        }

        /*!
            \brief Returns the list selection observer set.

            \return The list selection observer set.
        */
        list_selection_observer_set_type& list_selection_observer_set()
        {
            return m_list_selection_observer_set;
        }


    private:
        // types

        using keyboard_observer_set_type = typename base_type::keyboard_observer_set_type;

        using virtual_key_type = typename keyboard_observer_set_type::virtual_key_type;

        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;

        using delta_type = typename mouse_observer_set_type::delta_type;

        using direction_type = typename mouse_observer_set_type::direction_type;

        using canvas_type = typename base_type::canvas_type;

        using top_type = typename gui::position<position_type>::top_type;

        using dimension_type = typename base_type::dimension_type;

        using width_type = typename gui::dimension<dimension_type>::width_type;

        using height_type = typename gui::dimension<dimension_type>::height_type;

        using scroll_bar_type = typename base_type::scroll_bar_type;

        using scroll_bar_size_type = typename scroll_bar_type::size_type;

        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        using inner_item_type = typename base_type::inner_item_type;

        class splitter : public inner_item_type
        {
        public:
            // constructors and destructor

            explicit splitter(map_box& map_box_)
            :
            inner_item_type(
                map_box_, position_type(left_type(0), top_type(0)), dimension_type(width_type(0), height_type(0))
            )
            {}


            // functions

            void move(left_type position)
            {
                auto adjusted_position = adjust_position(std::move(position));

                if (this->template parent_to<map_box>().m_splitter_position == adjusted_position)
                    return;

                this->template parent_to<map_box>().m_splitter_position = std::move(adjusted_position);

                this->parent().size_observer_set().resized()();
                this->parent().repaint();
            }


        private:
            // static functions

            static const width_type& width()
            {
                static const width_type singleton{ width_type{ 1 } / 2 };
                return singleton;
            }

            static const left_type& min_left()
            {
                static const left_type singleton{ 4 };
                return singleton;
            }


            // virtual functions

            virtual void resized_impl()
            override
            {
                static const width_type splitter_width{ width_type{ 1 } / 2 };

                adjust_position(this->template parent_to<map_box>().m_splitter_position);
                this->set_position(
                    position_type(this->template parent_to<map_box>().m_splitter_position - width() / 2, top_type(0))
                );

                const auto map_box_client_dimension = this->parent().client_dimension();
                this->set_dimension(
                    dimension_type(width(), gui::dimension<dimension_type>::height(map_box_client_dimension))
                );
            }

            virtual void mouse_released_impl(const position_type& cursor_position)
            override
            {
                move(gui::position<position_type>::left(cursor_position));
            }

            virtual void mouse_moved_impl(const position_type& cursor_position)
            override
            {
                if (!this->parent().mouse_captured(this))
                    return;

                move(gui::position<position_type>::left(cursor_position));
            }

            virtual void mouse_entered_impl()
            override
            {
                auto p_cursor =
                    stdalt::make_unique<system_cursor_type>(system_cursor_type::style_type::horizontal_resize);
                this->parent().set_cursor(std::move(p_cursor));
            }

            virtual void mouse_left_impl()
            override
            {
               this->parent().set_cursor(std::unique_ptr<cursor_type>());
            }


            // functions

            left_type adjust_position(left_type position)
            {
                const auto map_box_width =
                    left_type::from(gui::dimension<dimension_type>::width(this->parent().client_dimension()));
                if (map_box_width > min_left() * 2)
                {
                    position = std::max(min_left(), position);
                    position = std::min(position, map_box_width - min_left());
                }
                else
                {
                    position = map_box_width / 2;
                }

                return position;
            }


        };

        class value_item : public inner_item_type
        {
        public:
            // constructors and destructor

            explicit value_item(map_box& map_box_, value_type value)
            :
            inner_item_type(
                map_box_, position_type(left_type(0), top_type(0)), dimension_type(width_type(0), height_type(0))
            ),
            m_value(std::move(value))
            {}


            // functions

            const value_type& value()
            const
            {
                return m_value;
            }

            value_type& value()
            {
                return m_value;
            }

            position_type position_to_paint()
            const
            {
                const auto scroll_bar_position =
                    this->parent().has_vertical_scroll_bar() ?
                    top_type::from_pixels(this->parent().vertical_scroll_bar().tracking_position()) :
                    top_type(0);

                auto left = gui::position<position_type>::left(this->position());
                auto top =
                    gui::position<position_type>::top(this->position()) - scroll_bar_position * scroll_bar_size_unit();

                return { std::move(left), std::move(top) };
            }


        private:
            // static functions

            static const height_type& padding_height()
            {
                static const height_type singleton = height_type(1) / 8;
                return singleton;
            }

            static const height_type& padding_width()
            {
                static const height_type singleton = height_type(1) / 2;
                return singleton;
            }


            // variables

            value_type m_value;


            // virtual functions

            virtual void resized_impl()
            override
            {
                height_type key_text_height{ 0 };
                height_type mapped_text_height{ 0 };
                {
                    const auto p_canvas = this->parent().create_canvas();
                    key_text_height =
                        gui::dimension<dimension_type>::height(
                            p_canvas->calc_text_dimension(m_value.first, key_text_max_width())
                        );
                    mapped_text_height =
                        gui::dimension<dimension_type>::height(
                            p_canvas->calc_text_dimension(m_value.second, mapped_text_max_width())
                        );
                }

                const auto map_box_width = gui::dimension<dimension_type>::width(this->parent().client_dimension());
                const auto height = std::max(key_text_height, mapped_text_height) + padding_height() * 2;
                this->set_dimension(dimension_type(map_box_width, height));
            }

            virtual void paint_impl(canvas_type& canvas)
            const override
            {
                const auto position_to_paint_ = position_to_paint();
                if (outside_client_area(position_to_paint_))
                    return;

                if (this->template parent_to<map_box>().selected_value_index() == index())
                {
                    canvas.set_color(system_color_set_type::selected_text());
                    canvas.set_background(
                        stdalt::make_unique<solid_background_type>(system_color_set_type::selected_background())
                    );
                    canvas.fill_rectangle(position_to_paint_, this->dimension());
                }
                else
                {
                    canvas.set_color(system_color_set_type::control_text());
                }

                canvas.draw_text(m_value.first, key_text_position(position_to_paint_), key_text_max_width());
                canvas.draw_text(
                    m_value.second, mapped_text_position(position_to_paint_), mapped_text_max_width()
                );

                canvas.set_color(system_color_set_type::dialog_background());
                canvas.set_line_width(typename canvas_type::size_type(1) / 12);
                {
                    auto positions = border_line_positions(position_to_paint_);
                    canvas.draw_line(positions.first, positions.second);
                }
                {
                    auto positions = splitter_line_positions(position_to_paint_);
                    canvas.draw_line(positions.first, positions.second);
                }
            }

            virtual void mouse_pressed_impl(const position_type& cursor_position)
            override
            {
                if (!this->inside(cursor_position))
                    return;

                this->template parent_to<map_box>().select_value(index());
                this->parent().repaint();
            }


            // functions

            bool outside_client_area(const position_type& position_to_paint_)
            const
            {
                const auto top = gui::position<position_type>::top(position_to_paint_);
                if (top > top_type::from(gui::dimension<dimension_type>::height(this->parent().client_dimension())))
                    return true;

                const auto bottom = top + top_type::from(gui::dimension<dimension_type>::height(this->dimension()));
                if (bottom < top_type(0))
                    return true;

                return false;
            }

            position_type key_text_position(const position_type& position_to_paint_)
            const
            {
                auto left = gui::position<position_type>::left(position_to_paint_) + left_type::from(padding_width());
                auto top = gui::position<position_type>::top(position_to_paint_) + top_type::from(padding_height());

                return { std::move(left), std::move(top) };
            }

            position_type mapped_text_position(const position_type& position_to_paint_)
            const
            {
                auto left =
                    gui::position<position_type>::left(position_to_paint_) +
                    this->template parent_to<map_box>().m_splitter_position +
                    left_type::from(padding_width());
                auto top = gui::position<position_type>::top(position_to_paint_) + top_type::from(padding_height());

                return { std::move(left), std::move(top) };
            }

            width_type key_text_max_width()
            const
            {
                if (width_type::from(this->template parent_to<map_box>().m_splitter_position) > padding_width() * 2)
                {
                    return
                        width_type::from(this->template parent_to<map_box>().m_splitter_position) -
                        padding_width() * 2;
                }
                else
                {
                    return padding_width() * 2;
                }
            }

            width_type mapped_text_max_width()
            const
            {
                const width_type map_box_client_width =
                    gui::dimension<dimension_type>::width(this->parent().client_dimension());
                if (
                    map_box_client_width >
                    width_type::from(this->template parent_to<map_box>().m_splitter_position) + padding_width() * 2
                )
                {
                    return
                        map_box_client_width -
                        width_type::from(this->template parent_to<map_box>().m_splitter_position) -
                        padding_width() * 2;
                }
                else
                {
                    return padding_width() * 2;
                }
            }

            std::pair<position_type, position_type> border_line_positions(const position_type& position_to_paint_)
            const
            {
                const auto& left = gui::position<position_type>::left(position_to_paint_);
                const auto& top = gui::position<position_type>::top(position_to_paint_);
                const auto& width = gui::dimension<dimension_type>::width(this->dimension());
                const auto& height = gui::dimension<dimension_type>::height(this->dimension());

                return
                    std::make_pair(
                        position_type(left, top + top_type::from(height)),
                        position_type(left + left_type::from(width), top + top_type::from(height))
                    );
            }

            std::pair<position_type, position_type> splitter_line_positions(const position_type& position_to_paint_)
            const
            {
                const auto& left = gui::position<position_type>::left(position_to_paint_);
                const auto& top = gui::position<position_type>::top(position_to_paint_);
                const auto& height = gui::dimension<dimension_type>::height(this->dimension());
                const auto& splitter_position = this->template parent_to<map_box>().m_splitter_position;

                return
                    std::make_pair(
                        position_type(left + splitter_position, top),
                        position_type(left + splitter_position, top + top_type::from(height))
                    );
            }

            int_size_type index()
            const
            {
                const auto my_position =
                    std::find_if(
                        this->template parent_to<map_box>().m_p_value_items.begin(),
                        this->template parent_to<map_box>().m_p_value_items.end(),
                        [this](const std::unique_ptr<value_item>& p_item) { return p_item.get() == this; }
                    );
                assert(my_position != this->template parent_to<map_box>().m_p_value_items.end());
                return std::distance(this->template parent_to<map_box>().m_p_value_items.begin(), my_position);
            }


        };


        // static functions

        static void initialize_map_box(map_box& map_box_)
        {
            map_box_.set_background(
                stdalt::make_unique<solid_background_type>(system_color_set_type::control_background())
            );

            create_items(map_box_);

            set_observers(map_box_);
        }

        static void create_items(map_box& map_box_)
        {
            map_box_.m_p_splitter = stdalt::make_unique<splitter>(map_box_);
        }

        static void set_observers(map_box& map_box_)
        {
            map_box_.size_observer_set().resized().connect(
                [&map_box_]()
                {
                    map_box_.m_p_splitter->resized();
                    std::for_each(
                        map_box_.m_p_value_items.begin(),
                        map_box_.m_p_value_items.end(),
                        [](const std::unique_ptr<value_item>& p_item) { p_item->resized(); }
                    );
                    map_box_.set_value_item_positions();
                    map_box_.update_scroll_bar();
                    map_box_.ensure_selected_value_shown();
                }
            );

            map_box_.paint_observer_set().paint_background().disconnect_all_slots();
            map_box_.paint_observer_set().paint_background().connect(
                [&map_box_](canvas_type& canvas)
                {
                    return map_box_.paint_background(canvas);
                }
            );
            map_box_.paint_observer_set().paint().connect(
                [&map_box_](canvas_type& canvas)
                {
                    canvas.begin_transaction(map_box_.client_dimension());

                    map_box_.paint_background(canvas);
                    std::for_each(
                        map_box_.m_p_value_items.begin(),
                        map_box_.m_p_value_items.end(),
                        [&canvas](const std::unique_ptr<value_item>& p_item) { p_item->paint(canvas); }
                    );

                    canvas.end_transaction();
                }
            );

            map_box_.keyboard_observer_set().key_down().connect(
                [&map_box_](const virtual_key_type& virtual_key, bool, bool, bool)
                {
                    map_box_.key_down(virtual_key);
                }   
            );

            map_box_.mouse_observer_set().pressed().connect(
                [&map_box_](const mouse_button_type button, const position_type& position, bool, bool, bool)
                {
                    const auto adjusted_position = map_box_.adjust_position(position);
                    map_box_.m_p_splitter->mouse_pressed(button, adjusted_position);
                    std::for_each(
                        map_box_.m_p_value_items.begin(),
                        map_box_.m_p_value_items.end(),
                        [button, &adjusted_position](const std::unique_ptr<value_item>& p_item)
                        {
                            p_item->mouse_pressed(button, adjusted_position);
                        }
                    );
                }
            );
            map_box_.mouse_observer_set().released().connect(
                [&map_box_](const mouse_button_type button, const position_type& position, bool, bool, bool)
                {
                    const auto adjusted_position = map_box_.adjust_position(position);
                    map_box_.m_p_splitter->mouse_released(button, adjusted_position);
                    std::for_each(
                        map_box_.m_p_value_items.begin(),
                        map_box_.m_p_value_items.end(),
                        [button, &adjusted_position](const std::unique_ptr<value_item>& p_item)
                        {
                            p_item->mouse_released(button, adjusted_position);
                        }
                    );

                    if (map_box_.m_list_selection_observer_call_requested)
                        map_box_.call_list_selection_observer();
                }
            );
            map_box_.mouse_observer_set().moved().connect(
                [&map_box_](const position_type& position, bool, bool, bool)
                {
                    const auto adjusted_position = map_box_.adjust_position(position);
                    map_box_.m_p_splitter->mouse_moved(adjusted_position);
                    std::for_each(
                        map_box_.m_p_value_items.begin(),
                        map_box_.m_p_value_items.end(),
                        [&adjusted_position](const std::unique_ptr<value_item>& p_item)
                        {
                            p_item->mouse_moved(adjusted_position);
                        }
                    );
                }
            );
            map_box_.mouse_observer_set().wheeled().connect(
                [&map_box_](
                    const delta_type&    delta,
                    const direction_type direction,
                    const bool           shift,
                    const bool           control,
                    const bool           meta
                )
                {
                    if (direction != direction_type::vertical || shift || control || meta)
                        return;
                    map_box_.wheeled(delta);
                }
            );

            if (map_box_.has_vertical_scroll_bar())
            {
                map_box_.vertical_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                    [&map_box_](const scroll_bar_size_type new_position) { map_box_.scrolling(new_position); }
                );
                map_box_.vertical_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                    [&map_box_](const scroll_bar_size_type new_position) { map_box_.scrolling(new_position); }
                );
            }
        }

        static scroll_bar_size_type scroll_bar_size_unit()
        {
            static const scroll_bar_size_type singleton = gui::to_pixels<scroll_bar_size_type>(top_type(1));
            return singleton;
        }


        // variables

        left_type m_splitter_position;

        std::unique_ptr<splitter> m_p_splitter;

        std::vector<std::unique_ptr<value_item>> m_p_value_items;

        boost::optional<int_size_type> m_selected_value_index;

        bool m_list_selection_observer_call_requested;

        list_selection_observer_set_type m_list_selection_observer_set;


        // functions

        bool paint_background(canvas_type& canvas)
        const
        {
            if (!this->background())
                return false;

            canvas.set_background(this->background()->clone());
            canvas.fill_rectangle(position_type(left_type(0), top_type(0)), this->client_dimension());

            return true;
        }

        void key_down(const virtual_key_type& virtual_key)
        {
            if (value_count() == 0)
                return;

            if (virtual_key == virtual_key_type::up())
            {
                select_value(index_to_select(-1));
                this->repaint();
            }
            else if (virtual_key == virtual_key_type::down())
            {
                select_value(index_to_select(1));
                this->repaint();
            }
            else if (virtual_key == virtual_key_type::page_up())
            {
                select_value(index_to_select(value_count_per_page(-1)));
                this->repaint();
            }
            else if (virtual_key == virtual_key_type::page_down())
            {
                select_value(index_to_select(value_count_per_page(1)));
                this->repaint();
            }
            else if (virtual_key == virtual_key_type::home())
            {
                select_value(0);
                this->repaint();
            }
            else if (virtual_key == virtual_key_type::end())
            {
                select_value(value_count() - 1);
                this->repaint();
            }
        }

        int_size_type index_to_select(std::ptrdiff_t delta)
        const
        {
            assert(value_count() > 0);

            if (!m_selected_value_index)
                return 0;

            if (delta < 0)
            {
                if (*m_selected_value_index > static_cast<int_size_type>(-delta))
                    return *m_selected_value_index + delta;
                else
                    return 0;
            }
            else
            {
                if (*m_selected_value_index + delta < value_count())
                    return *m_selected_value_index + delta;
                else
                    return value_count() - 1;
            }
        }

        std::ptrdiff_t value_count_per_page(const std::ptrdiff_t direction)
        const
        {
            if (!m_selected_value_index)
                return 0;

            const auto client_height = gui::dimension<dimension_type>::height(this->client_dimension());
            height_type height{ 0 };
            std::ptrdiff_t count = 0;
            for (
                std::ptrdiff_t i = *m_selected_value_index;
                0 <= i && i < static_cast<std::ptrdiff_t>(value_count());
                i += direction, count += direction
            )
            {
                const auto& value_height = gui::dimension<dimension_type>::height(m_p_value_items[i]->dimension());
                if (height + value_height > client_height)
                    break;

                height += value_height;
            }

            return count;
        }

        void set_value_item_positions()
        {
            top_type top{ 0 };
            for (const auto& p_value_item: m_p_value_items)
            {
                p_value_item->set_position(position_type(left_type(0), top));
                top += top_type::from(gui::dimension<dimension_type>::height(p_value_item->dimension()));
            }
        }

        position_type adjust_position(const position_type& position)
        const
        {
            const auto& left = gui::position<position_type>::left(position);
            auto adjusted_top = gui::position<position_type>::top(position);
            if (this->has_vertical_scroll_bar() && this->vertical_scroll_bar().enabled())
            {
                adjusted_top +=
                    top_type::from_pixels(this->vertical_scroll_bar().tracking_position()) * scroll_bar_size_unit();
            }

            return { left, adjusted_top };
        }

        void update_scroll_bar()
        {
            const auto client_height = gui::dimension<dimension_type>::height(this->client_dimension());
            const auto value_height =
                m_p_value_items.empty() ?
                height_type(0) :
                height_type::from(gui::position<position_type>::top(m_p_value_items.back()->position())) +
                    gui::dimension<dimension_type>::height(m_p_value_items.back()->dimension());

            auto& scroll_bar = this->vertical_scroll_bar();
            if (value_height <= client_height)
            {
                scroll_bar.scroll_bar_observer_set().scrolled()(0);
                scroll_bar.set_enabled(false);
            }
            else
            {
                const auto upper_bound = gui::to_pixels<scroll_bar_size_type>(value_height) / scroll_bar_size_unit();
                const auto page_size = gui::to_pixels<scroll_bar_size_type>(client_height) / scroll_bar_size_unit();
                if (scroll_bar.tracking_position() + page_size > upper_bound + 1)
                {
                    scroll_bar.scroll_bar_observer_set().scrolled()(
                        upper_bound > page_size ? upper_bound - page_size + 1 : 0
                    );
                }
                scroll_bar.set_range(std::make_pair(scroll_bar_size_type(0), upper_bound));
                scroll_bar.set_page_size(page_size);
                scroll_bar.set_enabled(true);
            }
        }

        void scrolling(const scroll_bar_size_type new_position)
        {
            this->vertical_scroll_bar().set_position(new_position);
            this->repaint();
        }

        void wheeled(const delta_type& delta)
        {
            if (!this->vertical_scroll_bar().enabled())
                return;

            this->vertical_scroll_bar().scroll_bar_observer_set().scrolled()(calculate_new_position(delta));
        }

        scroll_bar_size_type calculate_new_position(const delta_type& delta)
        const
        {
            const auto& scroll_bar = this->vertical_scroll_bar();

            using delta_int_type = typename delta_type::int_type;
            auto int_delta =
                boost::rational_cast<delta_int_type>(
                    delta * gui::to_pixels<delta_int_type>(top_type(3)) / scroll_bar_size_unit()
                );
            if (int_delta == 0)
            {
                if (delta > 0)
                    ++int_delta;
                else
                    --int_delta;
            }
            const delta_int_type new_position = scroll_bar.position() - int_delta;

            if (new_position < static_cast<delta_int_type>(scroll_bar.range().first))
                return scroll_bar.range().first;
            if (new_position > static_cast<delta_int_type>(scroll_bar.range().second - scroll_bar.page_size() + 1))
                return scroll_bar.range().second - scroll_bar.page_size() + 1;

            return new_position;
        }

        void ensure_selected_value_shown()
        {
            if (!m_selected_value_index)
                return;
            if (!this->has_vertical_scroll_bar())
                return;
            
            auto& scroll_bar = this->vertical_scroll_bar();
            if (!scroll_bar.enabled())
                return;

            const auto client_height = gui::dimension<dimension_type>::height(this->dimension());

            const auto& p_selected = m_p_value_items[*m_selected_value_index];
            const auto& top = gui::position<position_type>::top(p_selected->position());
            const auto& height = gui::dimension<dimension_type>::height(p_selected->dimension());
            const auto position_to_paint = p_selected->position_to_paint();
            const auto& top_to_paint = gui::position<position_type>::top(position_to_paint);
            const auto bottom_to_paint = top_to_paint + top_type::from(height);
            
            scroll_bar_size_type scroll_bar_position = scroll_bar.tracking_position();
            if (bottom_to_paint > top_type::from(client_height))
            {
                const scroll_bar_size_type scroll_bar_position_in_pixels =
                    gui::to_pixels<scroll_bar_size_type>(top + top_type::from(height) - top_type::from(client_height));
                scroll_bar_position = scroll_bar_position_in_pixels / scroll_bar_size_unit();
                if (scroll_bar_position_in_pixels % scroll_bar_size_unit() > 0)
                    scroll_bar_position += 1;
            }
            if (top_to_paint < top_type(0))
            {
                scroll_bar_position = gui::to_pixels<scroll_bar_size_type>(top) / scroll_bar_size_unit();
            }

            if (scroll_bar_position != scroll_bar.tracking_position())
                scroll_bar.scroll_bar_observer_set().scrolled()(scroll_bar_position);
        }

        void request_list_selection_observer_call()
        {
            if (this->mouse_captured(nullptr))
                m_list_selection_observer_call_requested = true;
            else
                call_list_selection_observer();
        }

        void call_list_selection_observer()
        {
            m_list_selection_observer_set.selection_changed()();
            m_list_selection_observer_call_requested = false;
        }


    };


}}}


#endif
