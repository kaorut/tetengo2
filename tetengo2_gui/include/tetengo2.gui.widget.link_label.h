/*! \file
    \brief The definition of tetengo2::gui::widget::link_label.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LINKLABEL_H)
#define TETENGO2_GUI_WIDGET_LINKLABEL_H

//#include <cassert>
//#include <memory>
//#include <stdexcept>
//#include <utility>

#include "tetengo2.cpp11.h"
#include "tetengo2.unique.h"
#include "tetengo2.gui.widget.label.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a link label.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a
                                      widget.
        \tparam MessageHandlerDetails A detail implementation type of a
                                      message handler.
   */
    template <
        typename Traits,
        typename WidgetDetails,
        typename MessageHandlerDetails
    >
    class link_label :
        public label<
            typename Traits::base_type, WidgetDetails, MessageHandlerDetails
        >
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef
            label<
                typename traits_type::base_type,
                widget_details_type,
                message_handler_details_type
            >
            base_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The widget type.
        typedef typename base_type::base_type::base_type widget_type;

        //! The string type.
        typedef typename base_type::string_type string_type;

        //! The font type.
        typedef typename base_type::font_type font_type;

        //! The system cursor type.
        typedef typename base_type::system_cursor_type system_cursor_type;

        //! The cursor type.
        typedef typename base_type::cursor_type cursor_type;

        //! The color type.
        typedef typename base_type::color_type color_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a link label.

            \param parent A parent widget.

            \throw std::runtime_error When a link label cannot be created.
        */
        explicit link_label(widget_type& parent)
        :
        base_type(parent),
        m_target()
        {
            initialize(this);
        }

        /*!
            \brief Destroys the link label.
        */
        virtual ~link_label()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the target.

            \return The target.
        */
        const string_type& target()
        const
        {
            return m_target;
        }

        /*!
            \brief Sets a target.

            \tparam S A string type.

            \param target a target.
        */
        template <typename S>
        void set_target(S&& target)
        {
            m_target = std::forward<S>(target);
        }


    private:
        // types

        class focus_changed
        {
        public:
            focus_changed(link_label& self)
            :
            m_self(self)
            {}

            void operator()()
            const
            {
                m_self.repaint();
            }


        private:
            link_label& m_self;


        };

        class clicked
        {
        public:
            clicked(link_label& self)
            :
            m_self(self)
            {}

            void operator()()
            const
            {
                widget_details_type::open_target(m_self, m_self.target());
            }


        private:
            const link_label& m_self;


        };


        // static functions

        static void initialize(link_label* const p_link_label)
        {
            assert(p_link_label);

            const font_type original_font = p_link_label->font();
            p_link_label->set_font(
                font_type(
                    original_font.family(),
                    original_font.size(),
                    original_font.bold(),
                    original_font.italic(),
                    true,
                    original_font.strikeout()
                )
            );

            p_link_label->set_text_color(color_type(0, 0, 255));

            std::unique_ptr<cursor_type> p_cursor(
                make_unique<system_cursor_type>(
                    system_cursor_type::style_hand
                )
            );
            p_link_label->set_cursor(std::move(p_cursor));

            p_link_label->set_focusable(true);

            p_link_label->focus_observer_set().got_focus().connect(
                focus_changed(*p_link_label)
            );
            p_link_label->focus_observer_set().lost_focus().connect(
                focus_changed(*p_link_label)
            );
            p_link_label->mouse_observer_set().clicked().connect(
                clicked(*p_link_label)
            );
        }


        // variables

        string_type m_target;


    };


}}}


#endif
