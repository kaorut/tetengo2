/*! \file
    \brief The definition of tetengo2::gui::widget::map_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/message/list_selection_observer_set.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/map_box.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    class map_box::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = map_box::size_type;

        using position_unit_type = map_box::position_unit_type;

        using list_selection_observer_set_type = map_box::list_selection_observer_set_type;

        using value_type = map_box::value_type;


        // static functions

        static void initialize_map_box(map_box& map_box_)
        {
            map_box_.set_background(std::make_unique<solid_background_type>(

                system_color_set_type::instance().control_background()));

            create_items(map_box_);

            set_observers(map_box_);
        }


        // constructors and destructor

        impl()
        : m_splitter_position{ position_unit_type{ 8 } }, m_p_splitter{}, m_p_value_items{}, m_selected_value_index{},
          m_list_selection_observer_call_requested{ false }, m_list_selection_observer_set{}
        {}


        // functions

        size_type value_count() const
        {
            return m_p_value_items.size();
        }

        const value_type& value(const size_type index) const
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            return m_p_value_items[index]->value();
        }

        void set_value(const size_type index, value_type value, map_box& self)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            m_p_value_items[index]->value() = std::move(value);

            if (self.visible())
                self.size_observer_set().resized()();
        }

        void insert_value(const size_type index, value_type value, map_box& self)
        {
            if (index > value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            m_p_value_items.insert(
                std::next(m_p_value_items.begin(), index), std::make_unique<value_item>(self, std::move(value)));
            if (m_selected_value_index && index <= *m_selected_value_index)
            {
                ++(*m_selected_value_index);
                request_list_selection_observer_call(self);
            }

            if (self.visible())
                self.size_observer_set().resized()();
        }

        void erase_value(const size_type index, map_box& self)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            m_p_value_items.erase(std::next(m_p_value_items.begin(), index));
            if (m_selected_value_index)
            {
                if (index == *m_selected_value_index)
                    m_selected_value_index = TETENGO2_STDALT_NULLOPT;
                else if (index < *m_selected_value_index)
                    --(*m_selected_value_index);
                request_list_selection_observer_call(self);
            }

            if (self.visible())
                self.size_observer_set().resized()();
        }

        void clear(map_box& self)
        {
            m_p_value_items.clear();
            if (m_selected_value_index)
            {
                m_selected_value_index = TETENGO2_STDALT_NULLOPT;
                request_list_selection_observer_call(self);
            }

            if (self.visible())
                self.size_observer_set().resized()();
        }

        tetengo2::stdalt::optional<size_type> selected_value_index() const
        {
            return m_selected_value_index;
        }

        void select_value(const size_type index, map_box& self)
        {
            if (index >= value_count())
                BOOST_THROW_EXCEPTION((std::out_of_range{ "index is out of range." }));

            m_selected_value_index = tetengo2::stdalt::make_optional(std::move(index));
            ensure_selected_value_shown(self);
            request_list_selection_observer_call(self);
        }

        const position_unit_type& splitter_position() const
        {
            return m_splitter_position;
        }

        void set_splitter_position(position_unit_type position)
        {
            m_p_splitter->move(std::move(position));
        }

        const list_selection_observer_set_type& list_selection_observer_set() const
        {
            return m_list_selection_observer_set;
        }

        list_selection_observer_set_type& list_selection_observer_set()
        {
            return m_list_selection_observer_set;
        }


    private:
        // types

        using solid_background_type = gui::drawing::solid_background;

        using system_color_set_type = gui::drawing::system_color_set;

        using virtual_key_type = typename keyboard_observer_set_type::virtual_key_type;

        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;

        using delta_type = typename mouse_observer_set_type::delta_type;

        using direction_type = typename mouse_observer_set_type::direction_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using scroll_bar_size_type = typename scroll_bar_type::size_type;

        class splitter : public inner_item
        {
        public:
            // constructors and destructor

            explicit splitter(map_box& map_box_) : inner_item{ map_box_, position_type{}, dimension_type{} } {}


            // functions

            void move(position_unit_type position)
            {
                auto adjusted_position = adjust_position(std::move(position));

                if (this->template parent_as<map_box>().m_p_impl->m_splitter_position == adjusted_position)
                    return;

                this->template parent_as<map_box>().m_p_impl->m_splitter_position = std::move(adjusted_position);

                this->parent().size_observer_set().resized()();
                this->parent().repaint();
            }


        private:
            // types

            using system_cursor_type = cursor::system;


            // static functions

            static const dimension_unit_type& width()
            {
                static const dimension_unit_type singleton{ dimension_unit_type{ 1 } / 2 };
                return singleton;
            }

            static const position_unit_type& min_left()
            {
                static const auto singleton = position_unit_type{ 4 };
                return singleton;
            }


            // virtual functions

            virtual void resized_impl() override
            {
                adjust_position(this->template parent_as<map_box>().m_p_impl->m_splitter_position);
                this->set_position(
                    position_type{ this->template parent_as<map_box>().m_p_impl->m_splitter_position - width() / 2,
                                   position_unit_type{} });

                const auto map_box_client_dimension = this->parent().client_dimension();
                this->set_dimension(dimension_type{ width(), map_box_client_dimension.height() });
            }

            virtual void mouse_released_impl(const position_type& cursor_position) override
            {
                move(cursor_position.left());
            }

            virtual void mouse_moved_impl(const position_type& cursor_position) override
            {
                if (!this->parent().mouse_captured(this))
                    return;

                move(cursor_position.left());
            }

            virtual void mouse_entered_impl() override
            {
                auto p_cursor = std::make_unique<system_cursor_type>(system_cursor_type::style_type::horizontal_resize);
                this->parent().set_cursor(std::move(p_cursor));
            }

            virtual void mouse_left_impl() override
            {
                this->parent().set_cursor(std::unique_ptr<cursor_type>{});
            }


            // functions

            position_unit_type adjust_position(position_unit_type position)
            {
                const auto map_box_width = position_unit_type::from(this->parent().client_dimension().width());
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

        class value_item : public inner_item
        {
        public:
            // constructors and destructor

            explicit value_item(map_box& map_box_, value_type value)
            : inner_item{ map_box_, position_type{}, dimension_type{} }, m_value{ std::move(value) }
            {}


            // functions

            const value_type& value() const
            {
                return m_value;
            }

            value_type& value()
            {
                return m_value;
            }

            position_type position_to_paint() const
            {
                const auto scroll_bar_position =
                    this->parent().has_vertical_scroll_bar() ?
                        position_unit_type::from_pixels(this->parent().vertical_scroll_bar().tracking_position()) :
                        position_unit_type{};

                auto left = this->position().left();
                auto top = this->position().top() - scroll_bar_position * scroll_bar_size_unit();

                return { std::move(left), std::move(top) };
            }


        private:
            // static functions

            static const dimension_unit_type& padding_height()
            {
                static const dimension_unit_type singleton = dimension_unit_type{ 1 } / 8;
                return singleton;
            }

            static const dimension_unit_type& padding_width()
            {
                static const dimension_unit_type singleton = dimension_unit_type{ 1 } / 2;
                return singleton;
            }


            // variables

            value_type m_value;


            // virtual functions

            virtual void resized_impl() override
            {
                dimension_unit_type key_text_height{};
                dimension_unit_type mapped_text_height{};
                {
                    const auto p_canvas = this->parent().create_canvas();
                    key_text_height = p_canvas->calc_text_dimension(m_value.first, key_text_max_width()).height();
                    mapped_text_height =
                        p_canvas->calc_text_dimension(m_value.second, mapped_text_max_width()).height();
                }

                const auto map_box_width = this->parent().client_dimension().width();
                const auto height = std::max(key_text_height, mapped_text_height) + padding_height() * 2;
                this->set_dimension(dimension_type{ map_box_width, height });
            }

            virtual void paint_impl(canvas_type& canvas) const override
            {
                const auto position_to_paint_ = position_to_paint();
                if (outside_client_area(position_to_paint_))
                    return;

                if (this->template parent_as<map_box>().selected_value_index() == index())
                {
                    canvas.set_color(system_color_set_type::instance().selected_text());
                    canvas.set_background(std::make_unique<solid_background_type>(

                        system_color_set_type::instance().selected_background()));
                    canvas.fill_rectangle(position_to_paint_, this->dimension());
                }
                else
                {
                    canvas.set_color(system_color_set_type::instance().control_text());
                }

                canvas.draw_text(m_value.first, key_text_position(position_to_paint_), key_text_max_width());
                canvas.draw_text(m_value.second, mapped_text_position(position_to_paint_), mapped_text_max_width());

                canvas.set_color(system_color_set_type::instance().dialog_background());
                canvas.set_line_width(dimension_unit_type{ 1 } / 12);
                {
                    auto positions = border_line_positions(position_to_paint_);
                    canvas.draw_line(positions.first, positions.second);
                }
                {
                    auto positions = splitter_line_positions(position_to_paint_);
                    canvas.draw_line(positions.first, positions.second);
                }
            }

            virtual void mouse_pressed_impl(const position_type& cursor_position) override
            {
                if (!this->inside(cursor_position))
                    return;

                this->template parent_as<map_box>().select_value(index());
                this->parent().repaint();
            }


            // functions

            bool outside_client_area(const position_type& position_to_paint_) const
            {
                const auto top = position_to_paint_.top();
                if (top > position_unit_type::from(this->parent().client_dimension().height()))
                {
                    return true;
                }

                const auto bottom = top + position_unit_type::from(this->dimension().height());
                if (bottom < position_unit_type{})
                    return true;

                return false;
            }

            position_type key_text_position(const position_type& position_to_paint_) const
            {
                auto left = position_to_paint_.left() + position_unit_type::from(padding_width());
                auto top = position_to_paint_.top() + position_unit_type::from(padding_height());

                return { std::move(left), std::move(top) };
            }

            position_type mapped_text_position(const position_type& position_to_paint_) const
            {
                auto left = position_to_paint_.left() +
                            this->template parent_as<map_box>().m_p_impl->m_splitter_position +
                            position_unit_type::from(padding_width());
                auto top = position_to_paint_.top() + position_unit_type::from(padding_height());

                return { std::move(left), std::move(top) };
            }

            dimension_unit_type key_text_max_width() const
            {
                if (dimension_unit_type::from(this->template parent_as<map_box>().m_p_impl->m_splitter_position) >
                    padding_width() * 2)
                {
                    return dimension_unit_type::from(
                               this->template parent_as<map_box>().m_p_impl->m_splitter_position) -
                           padding_width() * 2;
                }
                else
                {
                    return padding_width() * 2;
                }
            }

            dimension_unit_type mapped_text_max_width() const
            {
                const dimension_unit_type map_box_client_width = this->parent().client_dimension().width();
                if (map_box_client_width >
                    dimension_unit_type::from(this->template parent_as<map_box>().m_p_impl->m_splitter_position) +
                        padding_width() * 2)
                {
                    return map_box_client_width -
                           dimension_unit_type::from(
                               this->template parent_as<map_box>().m_p_impl->m_splitter_position) -
                           padding_width() * 2;
                }
                else
                {
                    return padding_width() * 2;
                }
            }

            std::pair<position_type, position_type> border_line_positions(const position_type& position_to_paint_) const
            {
                const auto& left = position_to_paint_.left();
                const auto& top = position_to_paint_.top();
                const auto& width = this->dimension().width();
                const auto& height = this->dimension().height();

                return std::make_pair(
                    position_type{ left, top + position_unit_type::from(height) },
                    position_type{ left + position_unit_type::from(width), top + position_unit_type::from(height) });
            }

            std::pair<position_type, position_type>
            splitter_line_positions(const position_type& position_to_paint_) const
            {
                const auto& left = position_to_paint_.left();
                const auto& top = position_to_paint_.top();
                const auto& height = this->dimension().height();
                const auto& splitter_position = this->template parent_as<map_box>().m_p_impl->m_splitter_position;

                return std::make_pair(
                    position_type{ left + splitter_position, top },
                    position_type{ left + splitter_position, top + position_unit_type::from(height) });
            }

            size_type index() const
            {
                const auto my_position = std::find_if(
                    this->template parent_as<map_box>().m_p_impl->m_p_value_items.begin(),
                    this->template parent_as<map_box>().m_p_impl->m_p_value_items.end(),
                    [this](const std::unique_ptr<value_item>& p_item) { return p_item.get() == this; });
                assert(my_position != this->template parent_as<map_box>().m_p_impl->m_p_value_items.end());
                return std::distance(
                    this->template parent_as<map_box>().m_p_impl->m_p_value_items.begin(), my_position);
            }
        };


        // static functions

        static void create_items(map_box& map_box_)
        {
            map_box_.m_p_impl->m_p_splitter = std::make_unique<splitter>(map_box_);
        }

        static void set_observers(map_box& map_box_)
        {
            map_box_.size_observer_set().resized().connect([&map_box_]() {
                map_box_.m_p_impl->m_p_splitter->resized();
                std::for_each(
                    map_box_.m_p_impl->m_p_value_items.begin(),
                    map_box_.m_p_impl->m_p_value_items.end(),
                    [](const std::unique_ptr<value_item>& p_item) { p_item->resized(); });
                map_box_.m_p_impl->set_value_item_positions();
                map_box_.m_p_impl->update_scroll_bar(map_box_);
                map_box_.m_p_impl->ensure_selected_value_shown(map_box_);
            });

            map_box_.paint_observer_set().paint_background().disconnect_all_slots();
            map_box_.paint_observer_set().paint_background().connect(
                [&map_box_](canvas_type& canvas) { return map_box_.m_p_impl->paint_background(canvas, map_box_); });
            map_box_.paint_observer_set().paint().connect([&map_box_](canvas_type& canvas) {
                canvas.begin_transaction(map_box_.client_dimension());

                map_box_.m_p_impl->paint_background(canvas, map_box_);
                std::for_each(
                    map_box_.m_p_impl->m_p_value_items.begin(),
                    map_box_.m_p_impl->m_p_value_items.end(),
                    [&canvas](const std::unique_ptr<value_item>& p_item) { p_item->paint(canvas); });

                canvas.end_transaction();
            });

            map_box_.keyboard_observer_set().key_down().connect(
                [&map_box_](const virtual_key_type& virtual_key, bool, bool, bool) {
                    map_box_.m_p_impl->key_down(virtual_key, map_box_);
                });

            map_box_.mouse_observer_set().pressed().connect(
                [&map_box_](const mouse_button_type button, const position_type& position, bool, bool, bool) {
                    const auto adjusted_position = map_box_.m_p_impl->adjust_position(position, map_box_);
                    map_box_.m_p_impl->m_p_splitter->mouse_pressed(button, adjusted_position);
                    std::for_each(
                        map_box_.m_p_impl->m_p_value_items.begin(),
                        map_box_.m_p_impl->m_p_value_items.end(),
                        [button, &adjusted_position](const std::unique_ptr<value_item>& p_item) {
                            p_item->mouse_pressed(button, adjusted_position);
                        });
                });
            map_box_.mouse_observer_set().released().connect(
                [&map_box_](const mouse_button_type button, const position_type& position, bool, bool, bool) {
                    const auto adjusted_position = map_box_.m_p_impl->adjust_position(position, map_box_);
                    map_box_.m_p_impl->m_p_splitter->mouse_released(button, adjusted_position);
                    std::for_each(
                        map_box_.m_p_impl->m_p_value_items.begin(),
                        map_box_.m_p_impl->m_p_value_items.end(),
                        [button, &adjusted_position](const std::unique_ptr<value_item>& p_item) {
                            p_item->mouse_released(button, adjusted_position);
                        });

                    if (map_box_.m_p_impl->m_list_selection_observer_call_requested)
                        map_box_.m_p_impl->call_list_selection_observer();
                });
            map_box_.mouse_observer_set().moved().connect([&map_box_](const position_type& position, bool, bool, bool) {
                const auto adjusted_position = map_box_.m_p_impl->adjust_position(position, map_box_);
                map_box_.m_p_impl->m_p_splitter->mouse_moved(adjusted_position);
                std::for_each(
                    map_box_.m_p_impl->m_p_value_items.begin(),
                    map_box_.m_p_impl->m_p_value_items.end(),
                    [&adjusted_position](const std::unique_ptr<value_item>& p_item) {
                        p_item->mouse_moved(adjusted_position);
                    });
            });
            map_box_.mouse_observer_set().wheeled().connect([&map_box_](
                                                                const delta_type&    delta,
                                                                const direction_type direction,
                                                                const bool           shift,
                                                                const bool           control,
                                                                const bool           meta) {
                if (direction != direction_type::vertical || shift || control || meta)
                    return;
                map_box_.m_p_impl->wheeled(delta, map_box_);
            });

            if (map_box_.has_vertical_scroll_bar())
            {
                map_box_.vertical_scroll_bar().scroll_bar_observer_set().scrolling().connect(
                    [&map_box_](const scroll_bar_size_type new_position) {
                        map_box_.m_p_impl->scrolling(new_position, map_box_);
                    });
                map_box_.vertical_scroll_bar().scroll_bar_observer_set().scrolled().connect(
                    [&map_box_](const scroll_bar_size_type new_position) {
                        map_box_.m_p_impl->scrolling(new_position, map_box_);
                    });
            }
        }

        static scroll_bar_size_type scroll_bar_size_unit()
        {
            static const auto singleton = static_cast<scroll_bar_size_type>(position_unit_type{ 1 }.to_pixels());
            return singleton;
        }


        // variables

        position_unit_type m_splitter_position;

        std::unique_ptr<splitter> m_p_splitter;

        std::vector<std::unique_ptr<value_item>> m_p_value_items;

        tetengo2::stdalt::optional<size_type> m_selected_value_index;

        bool m_list_selection_observer_call_requested;

        list_selection_observer_set_type m_list_selection_observer_set;


        // functions

        bool paint_background(canvas_type& canvas, const map_box& self) const
        {
            if (!self.p_background())
                return false;

            canvas.set_background(self.p_background()->clone());
            canvas.fill_rectangle(position_type{}, self.client_dimension());

            return true;
        }

        void key_down(const virtual_key_type& virtual_key, map_box& self)
        {
            if (value_count() == 0)
                return;

            if (virtual_key == virtual_key_type::up())
            {
                select_value(index_to_select(-1), self);
                self.repaint();
            }
            else if (virtual_key == virtual_key_type::down())
            {
                select_value(index_to_select(1), self);
                self.repaint();
            }
            else if (virtual_key == virtual_key_type::page_up())
            {
                select_value(index_to_select(value_count_per_page(-1, self)), self);
                self.repaint();
            }
            else if (virtual_key == virtual_key_type::page_down())
            {
                select_value(index_to_select(value_count_per_page(1, self)), self);
                self.repaint();
            }
            else if (virtual_key == virtual_key_type::home())
            {
                select_value(0, self);
                self.repaint();
            }
            else if (virtual_key == virtual_key_type::end())
            {
                select_value(value_count() - 1, self);
                self.repaint();
            }
        }

        size_type index_to_select(std::ptrdiff_t delta) const
        {
            assert(value_count() > 0);

            if (!m_selected_value_index)
                return 0;

            if (delta < 0)
            {
                if (*m_selected_value_index > static_cast<size_type>(-delta))
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

        std::ptrdiff_t value_count_per_page(const std::ptrdiff_t direction, const map_box& self) const
        {
            if (!m_selected_value_index)
                return 0;

            const auto          client_height = self.client_dimension().height();
            dimension_unit_type height{};
            std::ptrdiff_t      count = 0;
            for (std::ptrdiff_t i = *m_selected_value_index; 0 <= i && i < static_cast<std::ptrdiff_t>(value_count());
                 i += direction, count += direction)
            {
                const auto& value_height = m_p_value_items[i]->dimension().height();
                if (height + value_height > client_height)
                    break;

                height += value_height;
            }

            return count;
        }

        void set_value_item_positions()
        {
            position_unit_type top{};
            for (const auto& p_value_item : m_p_value_items)
            {
                p_value_item->set_position(position_type{ position_unit_type{}, top });
                top += position_unit_type::from(p_value_item->dimension().height());
            }
        }

        position_type adjust_position(const position_type& position, const map_box& self) const
        {
            const auto& left = position.left();
            auto        adjusted_top = position.top();
            if (self.has_vertical_scroll_bar() && self.vertical_scroll_bar().enabled())
            {
                adjusted_top += position_unit_type::from_pixels(self.vertical_scroll_bar().tracking_position()) *
                                scroll_bar_size_unit();
            }

            return { left, adjusted_top };
        }

        void update_scroll_bar(map_box& self)
        {
            const auto client_height = self.client_dimension().height();
            const auto value_height = m_p_value_items.empty() ?
                                          dimension_unit_type{} :
                                          dimension_unit_type::from(m_p_value_items.back()->position().top()) +
                                              m_p_value_items.back()->dimension().height();

            auto& scroll_bar = self.vertical_scroll_bar();
            if (value_height <= client_height)
            {
                scroll_bar.scroll_bar_observer_set().scrolled()(0);
                scroll_bar.set_enabled(false);
            }
            else
            {
                const auto upper_bound = value_height.to_pixels() / scroll_bar_size_unit();
                const auto page_size = client_height.to_pixels() / scroll_bar_size_unit();
                if (scroll_bar.tracking_position() + page_size > upper_bound + 1)
                {
                    scroll_bar.scroll_bar_observer_set().scrolled()(
                        upper_bound > page_size ? upper_bound - page_size + 1 : 0);
                }
                scroll_bar.set_range(std::make_pair(scroll_bar_size_type{}, upper_bound));
                scroll_bar.set_page_size(page_size);
                scroll_bar.set_enabled(true);
            }
        }

        void scrolling(const scroll_bar_size_type new_position, map_box& self)
        {
            self.vertical_scroll_bar().set_position(new_position);
            self.repaint();
        }

        void wheeled(const delta_type& delta, map_box& self)
        {
            if (!self.vertical_scroll_bar().enabled())
                return;

            self.vertical_scroll_bar().scroll_bar_observer_set().scrolled()(calculate_new_position(delta, self));
        }

        scroll_bar_size_type calculate_new_position(const delta_type& delta, const map_box& self) const
        {
            const auto& scroll_bar = self.vertical_scroll_bar();

            using delta_int_type = typename delta_type::int_type;
            auto int_delta = boost::rational_cast<delta_int_type>(
                delta * position_unit_type{ 3 }.to_pixels() / static_cast<delta_int_type>(scroll_bar_size_unit()));
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

        void ensure_selected_value_shown(const map_box& self)
        {
            if (!m_selected_value_index)
                return;
            if (!self.has_vertical_scroll_bar())
                return;

            auto& scroll_bar = self.vertical_scroll_bar();
            if (!scroll_bar.enabled())
                return;

            const auto client_height = self.dimension().height();

            const auto& p_selected = m_p_value_items[*m_selected_value_index];
            const auto& top = p_selected->position().top();
            const auto& height = p_selected->dimension().height();
            const auto  position_to_paint = p_selected->position_to_paint();
            const auto& top_to_paint = position_to_paint.top();
            const auto  bottom_to_paint = top_to_paint + position_unit_type::from(height);

            scroll_bar_size_type scroll_bar_position = scroll_bar.tracking_position();
            if (bottom_to_paint > position_unit_type::from(client_height))
            {
                const auto scroll_bar_position_in_pixels =
                    (top + position_unit_type::from(height) - position_unit_type::from(client_height)).to_pixels();
                scroll_bar_position = scroll_bar_position_in_pixels / scroll_bar_size_unit();
                if (scroll_bar_position_in_pixels % scroll_bar_size_unit() > 0 &&
                    scroll_bar_position + 1 <= scroll_bar.range().second)
                {
                    scroll_bar_position += 1;
                }
            }
            if (top_to_paint < position_unit_type{})
            {
                scroll_bar_position = top.to_pixels() / scroll_bar_size_unit();
            }

            if (scroll_bar_position != scroll_bar.tracking_position())
                scroll_bar.scroll_bar_observer_set().scrolled()(scroll_bar_position);
        }

        void request_list_selection_observer_call(const map_box& self)
        {
            if (self.mouse_captured(nullptr))
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


    map_box::map_box(widget& parent)
    : custom_control{ parent, true, scroll_bar_style_type::vertical }, m_p_impl{ std::make_unique<impl>() }
    {
        impl::initialize_map_box(*this);
    }

    map_box::~map_box() = default;

    map_box::size_type map_box::value_count() const
    {
        return m_p_impl->value_count();
    }

    const map_box::value_type& map_box::value(const size_type index) const
    {
        return m_p_impl->value(index);
    }

    void map_box::set_value(const size_type index, value_type value)
    {
        m_p_impl->set_value(index, std::move(value), *this);
    }

    void map_box::insert_value(const size_type index, value_type value)
    {
        m_p_impl->insert_value(index, std::move(value), *this);
    }

    void map_box::erase_value(const size_type index)
    {
        m_p_impl->erase_value(index, *this);
    }

    void map_box::clear()
    {
        m_p_impl->clear(*this);
    }

    tetengo2::stdalt::optional<map_box::size_type> map_box::selected_value_index() const
    {
        return m_p_impl->selected_value_index();
    }

    void map_box::select_value(const size_type index)
    {
        m_p_impl->select_value(index, *this);
    }

    const map_box::position_unit_type& map_box::splitter_position() const
    {
        return m_p_impl->splitter_position();
    }

    void map_box::set_splitter_position(position_unit_type position)
    {
        m_p_impl->set_splitter_position(std::move(position));
    }

    const map_box::list_selection_observer_set_type& map_box::list_selection_observer_set() const
    {
        return m_p_impl->list_selection_observer_set();
    }

    map_box::list_selection_observer_set_type& map_box::list_selection_observer_set()
    {
        return m_p_impl->list_selection_observer_set();
    }
}
