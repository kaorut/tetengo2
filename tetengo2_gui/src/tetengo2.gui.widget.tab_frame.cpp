/*! \file
    \brief The definition of tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/operators.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/message/paint_observer_set.h>
#include <tetengo2/gui/message/size_observer_set.h>
#include <tetengo2/gui/position.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/tab_frame.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class tab_frame::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = tab_frame::size_type;

        using tab_label_type = tab_frame::tab_label_type;

        using tab_body_type = tab_frame::tab_body_type;

        using tab_type = tab_frame::tab_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;


        // static functions

        static void initialize_tab_frame(tab_frame& tab_frame_)
        {
            tab_frame_.set_dimension(dimension_type{ dimension_unit_type{ 16 }, dimension_unit_type{ 16 } });
            tab_frame_.set_background(
                std::make_unique<solid_background_type>(system_color_set_type::instance().dialog_background()));
            set_observers(tab_frame_);
        }

        static void set_observers(tab_frame& tab_frame_)
        {
            tab_frame_.child_observer_set().created().connect(
                [&tab_frame_](widget& child) { tab_frame_.m_p_impl->child_created(child, tab_frame_); });
            tab_frame_.child_observer_set().destroying().connect(
                [&tab_frame_](widget& child) { tab_frame_.m_p_impl->child_destroying(child, tab_frame_); });

            tab_frame_.size_observer_set().resized().connect([&tab_frame_]() {
                for (size_type i = 0; i < tab_frame_.tab_count(); ++i)
                {
                    auto& tab = tab_frame_.tab_at(i);
                    tab.label().resized();
                    tab.body().resized();
                }
            });

            tab_frame_.paint_observer_set().paint_background().disconnect_all_slots();
            tab_frame_.paint_observer_set().paint_background().connect([](canvas_type&) { return true; });
            tab_frame_.paint_observer_set().paint().connect([&tab_frame_](canvas_type& canvas) {
                canvas.begin_transaction(tab_frame_.client_dimension());

                if (tab_frame_.p_background())
                {
                    canvas.set_background(tab_frame_.p_background()->clone());
                    const position_type  position{ position_unit_type{ -1 }, position_unit_type{ -1 } };
                    const auto           client_dimension = tab_frame_.client_dimension();
                    const dimension_type dimension{ client_dimension.width() + dimension_unit_type{ 2 },
                                                    client_dimension.height() + dimension_unit_type{ 2 } };
                    canvas.fill_rectangle(position, dimension);
                }

                for (size_type i = 0; i < tab_frame_.tab_count(); ++i)
                {
                    const auto& tab = tab_frame_.tab_at(i);
                    tab.label().paint(canvas);
                    tab.body().paint(canvas);
                }

                canvas.end_transaction();
            });

            tab_frame_.mouse_observer_set().pressed().connect(
                [&tab_frame_](const mouse_button_type button, const position_type& position, bool, bool, bool) {
                    if (button != mouse_button_type::left)
                        return;

                    for (size_type i = 0; i < tab_frame_.tab_count(); ++i)
                    {
                        auto& tab = tab_frame_.tab_at(i);
                        tab.label().mouse_pressed(button, position);
                        tab.body().mouse_pressed(button, position);
                    }
                });
            tab_frame_.mouse_observer_set().released().connect(
                [&tab_frame_](const mouse_button_type button, const position_type& position, bool, bool, bool) {
                    if (button != mouse_button_type::left)
                        return;

                    for (size_type i = 0; i < tab_frame_.tab_count(); ++i)
                    {
                        auto& tab = tab_frame_.tab_at(i);
                        tab.label().mouse_released(button, position);
                        tab.body().mouse_released(button, position);
                    }
                });
            tab_frame_.mouse_observer_set().moved().connect(
                [&tab_frame_](const position_type& position, bool, bool, bool) {
                    for (size_type i = 0; i < tab_frame_.tab_count(); ++i)
                    {
                        auto& tab = tab_frame_.tab_at(i);
                        tab.label().mouse_moved(position);
                        tab.body().mouse_moved(position);
                    }
                });
        }


        // constructors and destructor

        impl() : m_p_tabs{} {}


        // functions

        size_type tab_count() const
        {
            return m_p_tabs.size();
        }

        const tab_type& tab_at(const size_type index) const
        {
            if (index >= m_p_tabs.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            return *m_p_tabs[index];
        }

        tab_type& tab_at(const size_type index)
        {
            if (index >= m_p_tabs.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            return *m_p_tabs[index];
        }

        size_type selected_tab_index() const
        {
            if (m_p_tabs.empty())
                BOOST_THROW_EXCEPTION(std::logic_error{ "This tab frame has no tab." });

            assert(std::count_if(m_p_tabs.begin(), m_p_tabs.end(), [](const std::unique_ptr<tab_type>& p_tab) {
                       return p_tab->selected();
                   }) == 1);
            const auto tab_position =
                std::find_if(m_p_tabs.begin(), m_p_tabs.end(), [](const std::unique_ptr<tab_type>& p_tab) {
                    return p_tab->selected();
                });
            return std::distance(m_p_tabs.begin(), tab_position);
        }

        void select_tab(const size_type index, tab_frame& self)
        {
            if (index >= m_p_tabs.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            bool needs_repaint = true;
            for (size_type i = 0; i < m_p_tabs.size(); ++i)
            {
                if (i == index)
                {
                    if (m_p_tabs[i]->selected())
                        needs_repaint = false;
                    m_p_tabs[i]->select();
                }
                else
                {
                    m_p_tabs[i]->unselect();
                }
            }

            if (needs_repaint)
                self.repaint();
        }

        void move_tab(const size_type from, const size_type to)
        {
            if (from >= m_p_tabs.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index from is out of the range." });
            if (to >= m_p_tabs.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index to is out_of the range." });
            if (from == to)
                return;

            auto p_tab = std::move(m_p_tabs[from]);
            m_p_tabs.erase(std::next(m_p_tabs.begin(), from));
            m_p_tabs.insert(std::next(m_p_tabs.begin(), to), std::move(p_tab));

            for (size_type i = std::min(from, to); i <= std::max(from, to); ++i)
                m_p_tabs[i]->set_index(i);
        }

        void child_created(widget& child, tab_frame& self)
        {
            auto* const p_child = dynamic_cast<control*>(&child);
            if (!p_child)
                return;

            auto p_tab = std::make_unique<tab_type>(self, m_p_tabs.size(), *p_child);
            m_p_tabs.push_back(std::move(p_tab));

            select_tab(m_p_tabs.size() - 1, self);
        }

        void child_destroying(widget& child, tab_frame& self)
        {
            const auto* const p_child = dynamic_cast<control*>(&child);
            if (!p_child)
                return;

            const auto tab_position_to_erase = find_tab_item(*p_child);
            if (tab_position_to_erase == m_p_tabs.end())
                return;
            const auto index_to_erase = static_cast<size_type>(std::distance(m_p_tabs.cbegin(), tab_position_to_erase));

            if (m_p_tabs.size() > 1)
            {
                const auto selected_tab_index_ = selected_tab_index();
                if (index_to_erase == selected_tab_index_)
                    select_tab(std::min(selected_tab_index_, m_p_tabs.size() - 2), self);
            }

            m_p_tabs.erase(tab_position_to_erase);
        }

        position_unit_type tab_label_top(const tab_label_type& tab_label) const
        {
            position_unit_type top = position_unit_type{};
            for (const auto& p_tab : m_p_tabs)
            {
                if (&p_tab->label() == &tab_label)
                    break;

                top += position_unit_type::from(p_tab->label().dimension().height());
            }

            return top;
        }

        const dimension_unit_type& tab_label_width() const
        {
            const auto max_width_tab = std::max_element(
                m_p_tabs.begin(),
                m_p_tabs.end(),
                [](const std::unique_ptr<tab_type>& p_tab1, const std::unique_ptr<tab_type>& p_tab2) {
                    return p_tab1->label().dimension().width() < p_tab2->label().dimension().width();
                });
            if (max_width_tab == m_p_tabs.end())
            {
                static const dimension_unit_type zero_width{};
                return zero_width;
            }

            return (*max_width_tab)->label().dimension().width();
        }


    private:
        // types

        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;

        using solid_background_type = gui::drawing::solid_background;

        using system_color_set_type = gui::drawing::system_color_set;


        // static functions

        static bool has_same_control(const tab_type& tab, const control& child)
        {
            return &tab.body().template get<control>() == &child;
        }


        // variables

        std::vector<std::unique_ptr<tab_type>> m_p_tabs;


        // functions

        typename std::vector<std::unique_ptr<tab_type>>::const_iterator find_tab_item(const control& child) const
        {
            return std::find_if(m_p_tabs.begin(), m_p_tabs.end(), [&child](const std::unique_ptr<tab_type>& p_tab) {
                return has_same_control(*p_tab, child);
            });
        }
    };


    tab_frame::tab_frame(widget& parent)
    : custom_control{ parent, false, custom_control::scroll_bar_style_type::none }, m_p_impl{ std::make_unique<impl>() }
    {
        impl::initialize_tab_frame(*this);
    }

    tab_frame::~tab_frame() = default;

    tab_frame::size_type tab_frame::tab_count() const
    {
        return m_p_impl->tab_count();
    }

    const tab_frame::tab_type& tab_frame::tab_at(const size_type index) const
    {
        return m_p_impl->tab_at(index);
    }

    tab_frame::tab_type& tab_frame::tab_at(const size_type index)
    {
        return m_p_impl->tab_at(index);
    }

    tab_frame::size_type tab_frame::selected_tab_index() const
    {
        return m_p_impl->selected_tab_index();
    }

    void tab_frame::select_tab(const size_type index)
    {
        m_p_impl->select_tab(index, *this);
    }

    void tab_frame::move_tab(const size_type from, const size_type to)
    {
        m_p_impl->move_tab(from, to);
    }


    class tab_frame::tab_type::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        impl(tab_frame& parent, const size_type index, control& control_)
        : m_label{ parent, index }, m_body{ parent, control_ }, m_selected{ false }
        {}


        // functions

        const tab_label_type& label() const
        {
            return m_label;
        }

        tab_label_type& label()
        {
            return m_label;
        }

        const tab_body_type& body() const
        {
            return m_body;
        }

        tab_body_type& body()
        {
            return m_body;
        }

        size_type index() const
        {
            return m_label.index();
        }

        void set_index(const size_type index)
        {
            m_label.set_index(index);
        }

        bool selected() const
        {
            return m_selected;
        }

        void select()
        {
            m_selected = true;
            m_body.template get<control>().set_visible(true);
        }

        void unselect()
        {
            m_selected = false;
            m_body.template get<control>().set_visible(false);
        }


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using solid_background_type = gui::drawing::solid_background;

        using system_color_set_type = gui::drawing::system_color_set;


        // variables

        tab_label_type m_label;

        tab_body_type m_body;

        bool m_selected;
    };


    tab_frame::tab_type::tab_type(tab_frame& parent, const size_type index, control& control_)
    : m_p_impl{ std::make_unique<impl>(parent, index, control_) }
    {}

    const tab_frame::tab_label_type& tab_frame::tab_type::label() const
    {
        return m_p_impl->label();
    }

    tab_frame::tab_label_type& tab_frame::tab_type::label()
    {
        return m_p_impl->label();
    }

    const tab_frame::tab_body_type& tab_frame::tab_type::body() const
    {
        return m_p_impl->body();
    }

    tab_frame::tab_body_type& tab_frame::tab_type::body()
    {
        return m_p_impl->body();
    }

    tab_frame::size_type tab_frame::tab_type::index() const
    {
        return m_p_impl->index();
    }

    void tab_frame::tab_type::set_index(const size_type index)
    {
        m_p_impl->set_index(index);
    }

    bool tab_frame::tab_type::selected() const
    {
        return m_p_impl->selected();
    }

    void tab_frame::tab_type::select()
    {
        m_p_impl->select();
    }

    void tab_frame::tab_type::unselect()
    {
        m_p_impl->unselect();
    }


    class tab_frame::tab_label_type::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        explicit impl(const size_type index) : m_index{ index }, m_title{} {}


        // functions

        size_type index() const
        {
            return m_index;
        }

        void set_index(const size_type index)
        {
            m_index = index;
        }

        const string_type& title() const
        {
            return m_title;
        }

        void set_title(string_type title, tab_label_type& self, const tab_frame& parent)
        {
            m_title = std::move(title);

            calculate_dimension(self, parent);
        }

        void resized_impl(tab_label_type& self, const tab_frame& parent)
        {
            self.set_position(position_type{ position_unit_type{}, parent.m_p_impl->tab_label_top(self) });
        }

        void paint_impl(canvas_type& canvas, const tab_label_type& self, const tab_frame& parent) const
        {
            auto original_color = canvas.get_color();
            auto p_original_background = canvas.get_background().clone();
            auto original_line_width = canvas.line_width();
            canvas.set_color(system_color_set_type::instance().control_text());
            canvas.set_background(std::make_unique<solid_background_type>(
                canvas.drawing_details(), system_color_set_type::instance().control_background()));
            canvas.set_line_width(dimension_unit_type{ 1 } / 8);

            position_unit_type unselected_left{};
            if (m_index != parent.selected_tab_index())
                unselected_left = position_unit_type{ 1 } / 12;
            position_type  label_position{ self.position().left() + unselected_left, self.position().top() };
            dimension_type label_dimension{ self.dimension().width() - dimension_unit_type::from(unselected_left),
                                            self.dimension().height() };

            canvas.fill_rectangle(label_position, label_dimension);
            {
                auto original_font = canvas.get_font();
                auto font =
                    m_index == parent.selected_tab_index() ?
                        font_type{ original_font.family(), original_font.size(),      true,
                                   original_font.italic(), original_font.underline(), original_font.strikeout() } :
                        original_font;
                canvas.set_font(std::move(font));

                const auto          text_dimension = canvas.calc_text_dimension(m_title);
                const position_type text_position{
                    label_position.left() + position_unit_type::from(label_dimension.width()) -
                        (position_unit_type::from(label_dimension.width()) -
                         dimension_unit_type::from(text_dimension.height()) - unselected_left) /
                            2,
                    label_position.top() + (position_unit_type::from(label_dimension.height()) -
                                            position_unit_type::from(text_dimension.width())) /
                                               2
                };

                canvas.draw_text(m_title, text_position, boost::math::constants::pi<double>() / 2);

                canvas.set_font(std::move(original_font));
            }
            {
                const auto          left_top = label_position;
                const position_type left_bottom{
                    label_position.left(), label_position.top() + position_unit_type::from(label_dimension.height())
                };
                const position_type right_top{
                    label_position.left() + position_unit_type::from(label_dimension.width()), label_position.top()
                };
                const position_type right_bottom{
                    label_position.left() + position_unit_type::from(label_dimension.width()),
                    label_position.top() + position_unit_type::from(label_dimension.height())
                };
                canvas.draw_line(left_top, left_bottom);
                canvas.draw_line(left_top, right_top);
                canvas.draw_line(left_bottom, right_bottom);
            }

            canvas.set_line_width(std::move(original_line_width));
            canvas.set_background(std::move(p_original_background));
            canvas.set_color(std::move(original_color));
        }

        void mouse_released_impl(const position_type& /*cursor_position*/, tab_frame& parent)
        {
            parent.select_tab(m_index);
        }


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using font_type = typename canvas_type::font_type;

        using solid_background_type = gui::drawing::solid_background;

        using system_color_set_type = gui::drawing::system_color_set;


        // static functions

        static const dimension_unit_type& horizontal_padding()
        {
            static const auto singleton = dimension_unit_type{ 1 } / 4;
            return singleton;
        }

        static const dimension_unit_type& vertical_padding()
        {
            static const auto singleton = dimension_unit_type{ 1 };
            return singleton;
        }


        // variables

        size_type m_index;

        string_type m_title;


        // functions

        void calculate_dimension(tab_label_type& self, const tab_frame& parent)
        {
            const auto p_canvas = parent.create_canvas();

            auto original_font = p_canvas->get_font();
            auto font = font_type{ original_font.family(), original_font.size(),      true,
                                   original_font.italic(), original_font.underline(), original_font.strikeout() };
            p_canvas->set_font(std::move(font));

            const auto text_dimension = p_canvas->calc_text_dimension(m_title);

            p_canvas->set_font(std::move(original_font));

            self.set_dimension(dimension_type{
                horizontal_padding() * 2 + dimension_unit_type::from(text_dimension.height()),
                vertical_padding() * 2 + dimension_unit_type::from(text_dimension.width()),
            });
        }
    };


    tab_frame::tab_label_type::tab_label_type(tab_frame& parent, const size_type index)
    : inner_item{ parent, position_type{}, dimension_type{} }, m_p_impl{ std::make_unique<impl>(index) }
    {}

    tab_frame::tab_label_type::~tab_label_type() = default;

    tab_frame::size_type tab_frame::tab_label_type::index() const
    {
        return m_p_impl->index();
    }

    void tab_frame::tab_label_type::set_index(const size_type index)
    {
        m_p_impl->set_index(index);
    }

    const tab_frame::string_type& tab_frame::tab_label_type::title() const
    {
        return m_p_impl->title();
    }

    void tab_frame::tab_label_type::set_title(string_type title)
    {
        m_p_impl->set_title(std::move(title), *this, this->parent_as<tab_frame>());
    }

    void tab_frame::tab_label_type::resized_impl()
    {
        m_p_impl->resized_impl(*this, this->parent_as<tab_frame>());
    }

    void tab_frame::tab_label_type::paint_impl(canvas_type& canvas) const
    {
        m_p_impl->paint_impl(canvas, *this, this->parent_as<tab_frame>());
    }

    void tab_frame::tab_label_type::mouse_released_impl(const position_type& cursor_position)
    {
        m_p_impl->mouse_released_impl(cursor_position, this->parent_as<tab_frame>());
    }


    class tab_frame::tab_body_type::impl : private boost::noncopyable
    {
    public:
        // constructors and destructor

        explicit impl(control& control_) : m_control{ control_ } {}


        // functions

        void resized_impl(tab_body_type& self, const tab_frame& parent)
        {
            const auto& tab_label_width = parent.m_p_impl->tab_label_width();
            self.set_position(position_type{ position_unit_type::from(tab_label_width), position_unit_type{} });
            const auto client_dimension = parent.client_dimension();
            const auto width = client_dimension.width() > tab_label_width ? client_dimension.width() - tab_label_width :
                                                                            dimension_unit_type{};
            self.set_dimension(dimension_type{ width, client_dimension.height() });

            m_control.set_position_and_dimension(self.position(), self.dimension());
        }

        const control& get_impl() const
        {
            return m_control;
        }

        control& get_impl()
        {
            return m_control;
        }


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;


        // variables

        control& m_control;
    };


    tab_frame::tab_body_type::tab_body_type(tab_frame& parent, control& control_)
    : inner_item{ parent, position_type{}, dimension_type{} }, m_p_impl{ std::make_unique<impl>(control_) }
    {}

    tab_frame::tab_body_type::~tab_body_type() = default;

    void tab_frame::tab_body_type::resized_impl()
    {
        m_p_impl->resized_impl(*this, this->parent_as<tab_frame>());
    }

    const control& tab_frame::tab_body_type::get_impl() const
    {
        return m_p_impl->get_impl();
    }

    control& tab_frame::tab_body_type::get_impl()
    {
        return m_p_impl->get_impl();
    }
}
