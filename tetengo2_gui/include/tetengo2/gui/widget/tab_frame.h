/*! \file
    \brief The definition of tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TABFRAME_H)
#define TETENGO2_GUI_WIDGET_TABFRAME_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a tab frame.

        \tparam Traits              A traits type.
        \tparam DetailsTraits       A detail implementation type traits.
        \tparam MouseCaptureDetails A detail implementation type of a mouse capture.
    */
    template <
        typename Traits,
        typename DetailsTraits,
        typename MouseCaptureDetails
    >
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
            */
            explicit tab_label_type(tab_frame& parent)
            :
            base_type(
                parent,
                position_type{ left_type{ 0 }, top_type{ 0 } },
                dimension_type{ width_type{ 0 }, height_type{ 0 } }
            ),
            m_title()
            {}

            /*!
                \brief Destroys the tab body.
            */
            virtual ~tab_label_type()
            = default;


            // functions

            /*!
                \brief Returns the title.

                \return The title.
            */
            const string_type& title()
            const
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
            }


        private:
            // variables

            string_type m_title;


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
            :
            base_type(
                parent,
                position_type{ left_type{ 0 }, top_type{ 0 } },
                dimension_type{ width_type{ 0 }, height_type{ 0 } }
            ),
            m_control(control)
            {}

            /*!
                \brief Destroys the tab body.
            */
            virtual ~tab_body_type()
            = default;


            // functions

            /*!
                \brief Returns the control.

                \tparam Control A concrete control type.

                \return The control.
            */
            template <typename Control>
            const Control& get()
            const
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
            // variables

            control_type& m_control;

        };

        //! The tab type.
        class tab_type : private boost::noncopyable
        {
        public:
            // constructors and destructor

            /*!
                \brief Creates a tab.

                \param parent  A parent.
                \param control A control.
            */
            tab_type(tab_frame& parent, control_type& control)
            :
            m_label(parent),
            m_body(parent, control)
            {}


            // functions

            /*!
                \brief Returns the title.

                \return The title.
            */
            const string_type& title()
            const
            {
                return m_label.title();
            }

            /*!
                \brief Sets a title.

                \param title A title.
            */
            void set_title(string_type title)
            {
                m_label.set_title(std::move(title));
            }

            /*!
                \brief Returns the control.

                \tparam Control A concrete control type.

                \return The control.
            */
            template <typename Control>
            const Control& body()
            const
            {
                return m_body.template get<Control>();
            }

            /*!
                \brief Returns the control.

                \tparam Control A concrete control type.

                \return The control.
            */
            template <typename Control>
            Control& body()
            {
                return m_body.template get<Control>();
            }

            /*!
                \brief Returns the selected status.

                \return The selected status.
            */
            bool selected()
            const
            {
                return m_body.template get<control_type>().visible();
            }

            /*!
                \brief Selects this tab.
            */
            void select()
            {
                m_body.template get<control_type>().set_visible(true);
            }

            /*!
                \brief Unselects this tab.
            */
            void unselect()
            {
                m_body.template get<control_type>().set_visible(false);
            }


        private:
            // variables

            tab_label_type m_label;

            tab_body_type m_body;


        };


        // constructors and destructor

        /*!
            \brief Creates a tab frame.

            \param parent A parent widget.
        */
        explicit tab_frame(widget_type& parent)
        :
        base_type(parent, false, base_type::scroll_bar_style_type::none),
        m_p_tabs()
        {
            initialize_tab_frame(*this);
        }

        /*!
            \brief Destroys the tab frame.
        */
        virtual ~tab_frame()
        = default;


        // functions

        /*!
            \brief Returns the tab count.

            \return The tab count.
        */
        size_type tab_count()
        const
        {
            return m_p_tabs.size();
        }

        /*!
            \brief Returns the tab at the specified index.

            \param index An index.

            \return The tab at the speficied position.

            \throw std::out_of_range When the index is out of the range.
        */
        const tab_type& tab_at(const size_type index)
        const
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
        size_type selected_tab_index()
        const
        {
            if (m_p_tabs.empty())
                BOOST_THROW_EXCEPTION(std::logic_error{ "This tab frame has no tab." });

            assert(
                std::count_if(
                    m_p_tabs.begin(),
                    m_p_tabs.end(),
                    [this](const std::unique_ptr<tab_type>& p_tab) { return p_tab->selected(); }
                ) == 1
            );
            const auto tab_position =
                std::find_if(
                    m_p_tabs.begin(),
                    m_p_tabs.end(),
                    [this](const std::unique_ptr<tab_type>& p_tab) { return p_tab->selected(); }
                );
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

            for (size_type i = 0; i < m_p_tabs.size(); ++i)
            {
                if (i == index)
                    m_p_tabs[i]->select();
                else
                    m_p_tabs[i]->unselect();
            }
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
            m_p_tabs.erase(boost::next(m_p_tabs.begin(), from));
            m_p_tabs.insert(boost::next(m_p_tabs.begin(), to), std::move(p_tab));
        }


    private:
        // types

        using position_type = typename base_type::position_type;

        using left_type = typename gui::position<position_type>::left_type;

        using top_type = typename gui::position<position_type>::top_type;

        using dimension_type = typename base_type::dimension_type;

        using width_type = typename gui::dimension<dimension_type>::width_type;

        using height_type = typename gui::dimension<dimension_type>::height_type;


        // static functions

        static void initialize_tab_frame(tab_frame& self)
        {
            self.child_observer_set().created().connect([&self](widget_type& child) { self.child_created(child); });
            self.child_observer_set().destroying().connect(
                [&self](widget_type& child) { self.child_destroying(child); }
            );
        }


        // variables

        std::vector<std::unique_ptr<tab_type>> m_p_tabs;


        // functions

        void child_created(widget_type& child)
        {
            control_type* const p_child = dynamic_cast<control_type*>(&child);
            if (!p_child)
                return;

            auto p_tab = stdalt::make_unique<tab_type>(*this, *p_child);
            m_p_tabs.push_back(std::move(p_tab));

            select_tab(m_p_tabs.size() - 1);
        }

        void child_destroying(widget_type& child)
        {
            const control_type* const p_child = dynamic_cast<control_type*>(&child);
            if (!p_child)
                return;

            const auto tab_position_to_erase = find_tab_item(*p_child);
            if (tab_position_to_erase == m_p_tabs.end())
                return;
            const auto index_to_erase =
                static_cast<size_type>(std::distance(m_p_tabs.cbegin(), tab_position_to_erase));

            if (m_p_tabs.size() > 1)
            {
                const auto selected_tab_index_ = selected_tab_index();
                if (index_to_erase == selected_tab_index_)
                    select_tab(std::min(selected_tab_index_, m_p_tabs.size() - 2));
            }

            m_p_tabs.erase(tab_position_to_erase);
        }

        typename std::vector<std::unique_ptr<tab_type>>::const_iterator find_tab_item(const control_type& child)
        const
        {
            return
                std::find_if(
                    m_p_tabs.begin(),
                    m_p_tabs.end(),
                    [&child](const std::unique_ptr<tab_type>& p_tab)
                    {
                        return &p_tab->template body<control_type>() == &child;
                    }
                );
        }


    };


}}}


#endif
