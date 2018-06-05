/*! \file
    \brief The definition of tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TABFRAME_H)
#define TETENGO2_GUI_WIDGET_TABFRAME_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/widget/custom_control.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class template for a tab frame.

        \tparam Traits              A traits type.
        \tparam DetailsTraits       A detail implementation type traits.
        \tparam MouseCaptureDetails A detail implementation type of a mouse capture.
    */
    template <typename Traits, typename DetailsTraits, typename MouseCaptureDetails>
    class tab_frame : public custom_control<Traits, DetailsTraits, MouseCaptureDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The mouse capture details type.
        using mouse_capture_details_type = MouseCaptureDetails;

        //! The base type.
        using base_type = custom_control<traits_type, details_traits_type, mouse_capture_details_type>;

        //! The widget type.
        using widget_type = typename base_type::base_type::base_type;

        //! The canvas type.
        using canvas_type = typename base_type::canvas_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The control type.
        using control_type = typename base_type::base_type;

        //! The size type.
        using size_type = typename control_type::size_type;

        //! The tab label type.
        class tab_label_type : public inner_item<typename tab_frame::base_type>
        {
        public:
            // types

            //! The base type.
            using base_type = inner_item<typename tab_frame::base_type>;


            // constructors and destructor

            /*!
                \brief Creates a tab label.

                \param parent A parent.
                \param index  A tab index.
                */
            tab_label_type(tab_frame& parent, const size_type index)
            : base_type{ parent, position_type{}, dimension_type{} }, m_index{ index }, m_title{}
            {}

            /*!
                \brief Destroys the tab body.
            */
            virtual ~tab_label_type() = default;


            // functions

            /*!
                \brief Returns the index.

                \return The index.
            */
            size_type index() const
            {
                return m_index;
            }

            /*!
                \brief Sets a tab index.

                \param index A tab index.
            */
            void set_index(const size_type index)
            {
                m_index = index;
            }

            /*!
                \brief Returns the title.

                \return The title.
            */
            const string_type& title() const
            {
                return m_title;
            }

            /*!
                \brief Sets a title.

                \param title A title.
            */
            void set_title(string_type title)
            {
                m_title = std::move(title);

                calculate_dimension();
            }


        private:
            // types

            using position_unit_type = typename tab_frame::position_unit_type;

            using dimension_unit_type = typename tab_frame::dimension_unit_type;

            using font_type = typename canvas_type::font_type;


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


            // virtual functions

            virtual void resized_impl() override
            {
                this->set_position(position_type{ position_unit_type{},
                                                  static_cast<const tab_frame&>(this->parent()).tab_label_top(*this) });
            }

            virtual void paint_impl(canvas_type& canvas) const override
            {
                auto original_color = canvas.get_color();
                auto p_original_background = canvas.get_background().clone();
                auto original_line_width = canvas.line_width();
                canvas.set_color(system_color_set_type::instance().control_text());
                canvas.set_background(
                    std::make_unique<solid_background_type>(system_color_set_type::instance().control_background()));
                canvas.set_line_width(dimension_unit_type{ 1 } / 8);

                position_unit_type unselected_left{};
                if (m_index != static_cast<const tab_frame&>(this->parent()).selected_tab_index())
                    unselected_left = position_unit_type{ 1 } / 12;
                position_type  label_position{ this->position().left() + unselected_left, this->position().top() };
                dimension_type label_dimension{ this->dimension().width() - dimension_unit_type::from(unselected_left),
                                                this->dimension().height() };

                canvas.fill_rectangle(label_position, label_dimension);
                {
                    auto original_font = canvas.get_font();
                    auto font =
                        m_index == static_cast<const tab_frame&>(this->parent()).selected_tab_index() ?
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

            virtual void mouse_released_impl(const position_type& /*cursor_position*/) override
            {
                static_cast<tab_frame&>(this->parent()).select_tab(m_index);
            }


            // functions

            void calculate_dimension()
            {
                const auto p_canvas = this->parent().create_canvas();

                auto original_font = p_canvas->get_font();
                auto font = font_type{ original_font.family(), original_font.size(),      true,
                                       original_font.italic(), original_font.underline(), original_font.strikeout() };
                p_canvas->set_font(std::move(font));

                const auto text_dimension = p_canvas->calc_text_dimension(m_title);

                p_canvas->set_font(std::move(original_font));

                this->set_dimension(dimension_type{
                    horizontal_padding() * 2 + dimension_unit_type::from(text_dimension.height()),
                    vertical_padding() * 2 + dimension_unit_type::from(text_dimension.width()),
                });
            }
        };

        //! The tab body type.
        class tab_body_type : public inner_item<typename tab_frame::base_type>
        {
        public:
            // types

            //! The base type.
            using base_type = inner_item<typename tab_frame::base_type>;


            // constructors and destructor

            /*!
                \brief Creates a tab body.

                \param parent A parent.
                \param control A control.
            */
            tab_body_type(tab_frame& parent, control_type& control)
            : base_type{ parent, position_type{}, dimension_type{} }, m_control{ control }
            {}

            /*!
                \brief Destroys the tab body.
            */
            virtual ~tab_body_type() = default;


            // functions

            /*!
                \brief Returns the control.

                \tparam Control A concrete control type.

                \return The control.
            */
            template <typename Control>
            const Control& get() const
            {
                assert(dynamic_cast<const Control*>(&m_control));
                return dynamic_cast<const Control&>(m_control);
            }

            /*!
                \brief Returns the control.

                \tparam Control A concrete control type.

                \return The control.
            */
            template <typename Control>
            Control& get()
            {
                assert(dynamic_cast<Control*>(&m_control));
                return dynamic_cast<Control&>(m_control);
            }


        private:
            // types

            using position_unit_type = typename tab_frame::position_unit_type;

            using dimension_unit_type = typename tab_frame::dimension_unit_type;


            // variables

            control_type& m_control;


            // virtual functions

            virtual void resized_impl() override
            {
                const auto& tab_label_width = static_cast<const tab_frame&>(this->parent()).tab_label_width();
                this->set_position(position_type{ position_unit_type::from(tab_label_width), position_unit_type{} });
                const auto client_dimension = this->parent().client_dimension();
                const auto width = client_dimension.width() > tab_label_width ?
                                       client_dimension.width() - tab_label_width :
                                       dimension_unit_type{};
                this->set_dimension(dimension_type{ width, client_dimension.height() });

                m_control.set_position_and_dimension(this->position(), this->dimension());
            }
        };

        //! The tab type.
        class tab_type : private boost::noncopyable
        {
        public:
            // constructors and destructor

            /*!
                \brief Creates a tab.

                \param parent  A parent.
                \param index   A tab index.
                \param control A control.
            */
            tab_type(tab_frame& parent, const size_type index, control_type& control)
            : m_label{ parent, index }, m_body{ parent, control }, m_selected{ false }
            {}


            // functions

            /*!
                \brief Returns the label.

                \return The label.
            */
            const tab_label_type& label() const
            {
                return m_label;
            }

            /*!
                \brief Returns the label.

                \return The label.
            */
            tab_label_type& label()
            {
                return m_label;
            }

            /*!
                \brief Returns the body.

                \return The body.
            */
            const tab_body_type& body() const
            {
                return m_body;
            }

            /*!
                \brief Returns the body.

                \return The body.
            */
            tab_body_type& body()
            {
                return m_body;
            }

            /*!
                \brief Returns the index.

                \return The index.
            */
            size_type index() const
            {
                return m_label.index();
            }

            /*!
                \brief Sets a tab index.

                \param index A tab index.
            */
            void set_index(const size_type index)
            {
                m_label.set_index(index);
            }

            /*!
                \brief Returns the selected status.

                \return The selected status.
            */
            bool selected() const
            {
                return m_selected;
            }

            /*!
                \brief Selects this tab.
            */
            void select()
            {
                m_selected = true;
                m_body.template get<control_type>().set_visible(true);
            }

            /*!
                \brief Unselects this tab.
            */
            void unselect()
            {
                m_selected = false;
                m_body.template get<control_type>().set_visible(false);
            }


        private:
            // variables

            tab_label_type m_label;

            tab_body_type m_body;

            bool m_selected;
        };


        // constructors and destructor

        /*!
            \brief Creates a tab frame.

            \param parent A parent widget.
        */
        explicit tab_frame(widget_type& parent)
        : base_type{ parent, false, base_type::scroll_bar_style_type::none }, m_p_tabs{}
        {
            initialize_tab_frame(*this);
        }

        /*!
            \brief Destroys the tab frame.
        */
        virtual ~tab_frame() = default;


        // functions

        /*!
            \brief Returns the tab count.

            \return The tab count.
        */
        size_type tab_count() const
        {
            return m_p_tabs.size();
        }

        /*!
            \brief Returns the tab at the specified index.

            \param index An index.

            \return The tab at the speficied position.

            \throw std::out_of_range When the index is out of the range.
        */
        const tab_type& tab_at(const size_type index) const
        {
            if (index >= m_p_tabs.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            return *m_p_tabs[index];
        }

        /*!
            \brief Returns the tab at the specified index.

            \param index An index.

            \return The tab at the speficied position.

            \throw std::out_of_range When the index is out of the range.
        */
        tab_type& tab_at(const size_type index)
        {
            if (index >= m_p_tabs.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            return *m_p_tabs[index];
        }

        /*!
            \brief Returns the selected tab index.

            \return The selected tab index.

            \throw std::logic_error When no tab is selected.
        */
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

        /*!
            \brief Selects a tab.

            \param index A tab index.

            \throw std::out_of_range When the index is out of the range.
        */
        void select_tab(const size_type index)
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
                this->repaint();
        }

        /*!
            \brief Moves a tab.

            \param from An origin index.
            \param to   A destination index.

            \throw std::out_of_range When from and/or to are out of the range.
        */
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


    private:
        // types

        using drawing_details_type = typename details_traits_type::drawing_details_type;

        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        using mouse_button_type = typename mouse_observer_set_type::mouse_button_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using solid_background_type = gui::drawing::solid_background<drawing_details_type>;

        using system_color_set_type = gui::drawing::system_color_set;


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
                [&tab_frame_](widget_type& child) { tab_frame_.child_created(child); });
            tab_frame_.child_observer_set().destroying().connect(
                [&tab_frame_](widget_type& child) { tab_frame_.child_destroying(child); });

            tab_frame_.size_observer_set().resized().connect([&tab_frame_]() {
                for (const std::unique_ptr<tab_type>& p_tab : tab_frame_.m_p_tabs)
                {
                    p_tab->label().resized();
                    p_tab->body().resized();
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

                for (const std::unique_ptr<tab_type>& p_tab : tab_frame_.m_p_tabs)
                {
                    p_tab->label().paint(canvas);
                    p_tab->body().paint(canvas);
                }

                canvas.end_transaction();
            });

            tab_frame_.mouse_observer_set().pressed().connect(
                [&tab_frame_](const mouse_button_type button, const position_type& position, bool, bool, bool) {
                    if (button != mouse_button_type::left)
                        return;

                    for (const std::unique_ptr<tab_type>& p_tab : tab_frame_.m_p_tabs)
                    {
                        p_tab->label().mouse_pressed(button, position);
                        p_tab->body().mouse_pressed(button, position);
                    }
                });
            tab_frame_.mouse_observer_set().released().connect(
                [&tab_frame_](const mouse_button_type button, const position_type& position, bool, bool, bool) {
                    if (button != mouse_button_type::left)
                        return;

                    for (const std::unique_ptr<tab_type>& p_tab : tab_frame_.m_p_tabs)
                    {
                        p_tab->label().mouse_released(button, position);
                        p_tab->body().mouse_released(button, position);
                    }
                });
            tab_frame_.mouse_observer_set().moved().connect(
                [&tab_frame_](const position_type& position, bool, bool, bool) {
                    for (const std::unique_ptr<tab_type>& p_tab : tab_frame_.m_p_tabs)
                    {
                        p_tab->label().mouse_moved(position);
                        p_tab->body().mouse_moved(position);
                    }
                });
        }

        static bool has_same_control(const tab_type& tab, const control_type& child)
        {
            return &tab.body().template get<control_type>() == &child;
        }


        // variables

        std::vector<std::unique_ptr<tab_type>> m_p_tabs;


        // functions

        void child_created(widget_type& child)
        {
            auto* const p_child = dynamic_cast<control_type*>(&child);
            if (!p_child)
                return;

            auto p_tab = std::make_unique<tab_type>(*this, m_p_tabs.size(), *p_child);
            m_p_tabs.push_back(std::move(p_tab));

            select_tab(m_p_tabs.size() - 1);
        }

        void child_destroying(widget_type& child)
        {
            const auto* const p_child = dynamic_cast<control_type*>(&child);
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
                    select_tab(std::min(selected_tab_index_, m_p_tabs.size() - 2));
            }

            m_p_tabs.erase(tab_position_to_erase);
        }

        typename std::vector<std::unique_ptr<tab_type>>::const_iterator find_tab_item(const control_type& child) const
        {
            return std::find_if(m_p_tabs.begin(), m_p_tabs.end(), [&child](const std::unique_ptr<tab_type>& p_tab) {
                return has_same_control(*p_tab, child);
            });
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
    };
}


#endif
