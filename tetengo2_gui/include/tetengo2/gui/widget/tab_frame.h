/*! \file
    \brief The definition of tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TABFRAME_H)
#define TETENGO2_GUI_WIDGET_TABFRAME_H

#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a tab.

        \tparam String  A string type.
        \tparam Control A control type.
    */
    template <typename String, typename Control>
    class tab : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The control type.
        using control_type = Control;


        // constructors and destructors

        /*!
            \brief Creates a tab.

            \param p_control A unique pointer to a control.
            \param title     A title.

            \throw std::invalid_argument When p_control is nullptr.
        */
        tab(std::unique_ptr<control_type> p_control, string_type title)
        :
        m_p_control(std::move(p_control)),
        m_title(std::move(title))
        {
            if (!m_p_control)
                BOOST_THROW_EXCEPTION(std::invalid_argument{ "p_control is nullptr." });
        }


        // functions

        /*!
            \brief Returns the control.

            \tparam ConcreteControl A concrete control type.

            \return The control.
        */
        template <typename ConcreteControl>
        const ConcreteControl& get_control()
        const
        {
            assert(dynamic_cast<const ConcreteControl*>(m_p_control.get()));
            return dynamic_cast<const ConcreteControl&>(*m_p_control);
        }

        /*!
            \brief Returns the control.

            \tparam ConcreteControl A concrete control type.

            \return The control.
        */
        template <typename ConcreteControl>
        ConcreteControl& get_control()
        {
            assert(dynamic_cast<ConcreteControl*>(m_p_control.get()));
            return dynamic_cast<ConcreteControl&>(*m_p_control);
        }

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
            \brief Returns the visible status.

            \return The visible status.
        */
        bool visible()
        const
        {
            return m_p_control->visible();
        }

        /*!
            \brief Sets a visible status.

            \param visible A visible status.
        */
        void set_visible(const bool visible)
        {
            m_p_control->set_visible(visible);
        }


    private:
        // variables

        const std::unique_ptr<control_type> m_p_control;

        const string_type m_title;


    };


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

        //! The tab type.
        using tab_type = tab<string_type, control_type>;


        // constructors and destructor

        /*!
            \brief Creates a tab frame.

            \param parent A parent widget.
        */
        explicit tab_frame(widget_type& parent)
        :
        base_type(parent, false, base_type::scroll_bar_style_type::none),
        m_p_tab_items(),
        m_selected_tab_index()
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
            return m_p_tab_items.size();
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
            if (index >= m_p_tab_items.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            return m_p_tab_items[index]->tab();
        }

        /*!
            \brief Returns the tab at the specified index.

            \param index An index.

            \return The tab at the speficied position.

            \throw std::out_of_range When the index is out of the range.
        */
        tab_type& tab_at(const size_type index)
        {
            if (index >= m_p_tab_items.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            return m_p_tab_items[index]->tab();
        }

#if 0
        /*!
            \brief Inserts a tab.

            The inserted tab is automatically selected.

            \param index An index where the tab is inserted. It must be 0 <= index <= tab_count().
            \param p_tab A unique pointer to a tab.

            \throw std::out_of_range     When the index is out of the range.
            \throw std::invalid_argument When p_tab is nullptr.
        */
        void insert_tab(const size_type index, std::unique_ptr<tab_type> p_tab)
        {
            if (index > m_p_tab_items.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });
            if (!p_tab)
                BOOST_THROW_EXCEPTION(std::invalid_argument{ "p_tab is nullptr." });

            auto p_tab_item = stdalt::make_unique<tab_item>(*this, std::move(p_tab));
            m_p_tab_items.insert(boost::next(m_p_tab_items.begin(), index), std::move(p_tab_item));

            select_tab(index);
        }

        /*!
            \brief Erases a tab.

            \param index An tab index to erase.

            \throw std::out_of_range When the index is out of the range.
        */
        void erase_tab(const size_type index)
        {
            if (index >= m_p_tab_items.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            if (m_selected_tab_index)
            {
                if (index < *m_selected_tab_index)
                    --*m_selected_tab_index;
                else if (index == *m_selected_tab_index)
                    m_selected_tab_index = boost::none;
            }

            m_p_tab_items.erase(boost::next(m_p_tab_items.begin(), index));
        }
#endif

        /*!
            \brief Returns the selected tab index.

            \return The selected tab index.

            \throw std::logic_error When no tab is selected.
        */
        size_type selected_tab_index()
        const
        {
            if (!m_selected_tab_index || m_p_tab_items.empty())
                BOOST_THROW_EXCEPTION(std::logic_error{ "This tab frame has no tab." });

            return *m_selected_tab_index;
        }

        /*!
            \brief Selects a tab.

            \param index A tab index.

            \throw std::out_of_range When the index is out of the range.
        */
        void select_tab(const size_type index)
        {
            if (index >= m_p_tab_items.size())
                BOOST_THROW_EXCEPTION(std::out_of_range{ "index is out of the range." });

            for (size_type i = 0; i < m_p_tab_items.size(); ++i)
            {
                if (i == index)
                    m_p_tab_items[i]->select();
                else
                    m_p_tab_items[i]->unselect();
            }
            m_selected_tab_index = boost::make_optional(index);
        }


    private:
        // types

        using position_type = typename base_type::position_type;

        using left_type = typename gui::position<position_type>::left_type;

        using top_type = typename gui::position<position_type>::top_type;

        using dimension_type = typename base_type::dimension_type;

        using width_type = typename gui::dimension<dimension_type>::width_type;

        using height_type = typename gui::dimension<dimension_type>::height_type;

        class tab_item : public inner_item<typename tab_frame::base_type>
        {
        public:
            // types

            using base_type = inner_item<typename tab_frame::base_type>;


            // constructors and destructors

            explicit tab_item(tab_frame& parent, std::unique_ptr<tab_type> p_tab)
            :
            base_type(
                parent,
                position_type{ left_type{ 0 }, top_type{ 0 } },
                dimension_type{ width_type{ 0 }, height_type{ 0 } }
            ),
            m_p_tab(std::move(p_tab))
            {
                assert(m_p_tab);
            }

            virtual ~tab_item()
            = default;


            // functions

            const tab_type& tab()
            const
            {
                return *m_p_tab;
            }

            tab_type& tab()
            {
                return *m_p_tab;
            }

            void select()
            {
                m_p_tab->set_visible(true);
            }

            void unselect()
            {
                m_p_tab->set_visible(false);
            }


        private:
            // variables

            const std::unique_ptr<tab_type> m_p_tab;


        };


        // static functions

        static void initialize_tab_frame(tab_frame& self)
        {
            self.child_observer_set().created().connect([&self](widget_type& child) { self.child_created(child); });
            self.child_observer_set().destroying().connect(
                [&self](widget_type& child) { self.child_destroying(child); }
            );
        }


        // variables

        std::vector<std::unique_ptr<tab_item>> m_p_tab_items;

        boost::optional<size_type> m_selected_tab_index;


        // functions

        void child_created(widget_type& child)
        {
            control_type* const p_child = dynamic_cast<control_type*>(&child);
            if (!p_child)
                return;

        }

        void child_destroying(widget_type& child)
        {
            const control_type* const p_child = dynamic_cast<control_type*>(&child);
            if (!p_child)
                return;

            const auto tab_item_position = find_tab_item(*p_child);
            if (tab_item_position == m_p_tab_items.end())
                return;

        }

        typename std::vector<std::unique_ptr<tab_item>>::const_iterator find_tab_item(const control_type& child)
        const
        {
            return
                std::find_if(
                    m_p_tab_items.begin(),
                    m_p_tab_items.end(),
                    [&child](const std::unique_ptr<tab_item>& p_item)
                    {
                        return &p_item->tab().template get_control<control_type>() == &child;
                    }
                );
        }


    };


}}}


#endif
