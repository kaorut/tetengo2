/*! \file
    \brief The definition of tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_TABFRAME_H)
#define TETENGO2_GUI_WIDGET_TABFRAME_H

#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/widget/custom_control.h>


namespace tetengo2 { namespace gui { namespace widget
{
    template <typename String, typename Control>
    class tab;


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
        m_p_tab_items()
        {
            initialize_tab_frame(*this);
        }

        /*!
            \brief Destroys the tab frame.
        */
        virtual ~tab_frame()
        = default;


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

            explicit tab_item(tab_frame& parent)
            :
            base_type(
                parent,
                position_type{ left_type{ 0 }, top_type{ 0 } },
                dimension_type{ width_type{ 0 }, height_type{ 0 } }
            )
            {}

            virtual ~tab_item()
            = default;


        };


        // static functions

        static void initialize_tab_frame(tab_frame& /*tab_frame_*/)
        {

        }


        // variables

        std::vector<std::unique_ptr<tab_item>> m_p_tab_items;


    };


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
        */
        tab(std::unique_ptr<control_type> p_control, string_type title)
        :
        m_p_control(std::move(p_control)),
        m_title(std::move(title))
        {}


        // variables

        /*!
            \brief Returns the control.

            \tparam ConcreteControl A concrete control type.

            \return The control.
        */
        template <typename ConcreteControl>
        const ConcreteControl& control()
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
        ConcreteControl& control()
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


    private:
        // variables

        const std::unique_ptr<control_type> m_p_control;

        const string_type m_title;


    };


}}}


#endif
