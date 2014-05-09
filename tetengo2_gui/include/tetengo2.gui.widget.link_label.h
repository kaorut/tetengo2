/*! \file
    \brief The definition of tetengo2::gui::widget::link_label.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LINKLABEL_H)
#define TETENGO2_GUI_WIDGET_LINKLABEL_H

#include <cassert>
#include <utility>

#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.widget.label.h"
#include "tetengo2.stdalt.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a link label.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class link_label : public label<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
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
        typedef label<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The canvas type.
        typedef typename base_type::canvas_type canvas_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

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

        //! The mouse observer set type.
        typedef typename base_type::mouse_observer_set_type mouse_observer_set_type;

        //! The keyboard observer set type.
        typedef typename base_type::keyboard_observer_set_type keyboard_observer_set_type;

        //! The solid background type.
        typedef typename traits_type::solid_background_type solid_background_type;

        //! The system color set type.
        typedef typename traits_type::system_color_set_type system_color_set_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The shell type.
        typedef typename traits_type::shell_type shell_type;


        // constructors and destructor

        /*!
            \brief Creates a link label.

            \param parent A parent widget.
        */
        explicit link_label(widget_type& parent)
        :
        base_type(parent),
        m_target(),
        m_mouse_button_pressing(false)
        {
            initialize_link_label(this);
        }

        /*!
            \brief Destroys the link label.
        */
        virtual ~link_label()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION


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

            \param target a target.
        */
        void set_target(string_type target)
        {
            m_target = std::move(target);
        }


    private:
        // types

        typedef typename gui::position<position_type>::left_type left_type;

        typedef typename gui::position<position_type>::top_type top_type;

        class paint_background
        {
        public:
            paint_background(link_label& self)
            :
            m_self(self)
            {}

            bool operator()(canvas_type& canvas)
            const
            {
                if (!m_self.background())
                    return false;

                canvas.set_background(m_self.background()->clone());
                canvas.fill_rectangle(position_type(left_type(0), top_type(0)), m_self.client_dimension());
                if (m_self.focused())
                    canvas.draw_focus_indication(position_type(left_type(0), top_type(0)), m_self.client_dimension());

                return true;
            }

        private:
            link_label& m_self;

        };


        // static functions

        static void initialize_link_label(link_label* const p_link_label)
        {
            assert(p_link_label);

            p_link_label->set_background(
                stdalt::make_unique<solid_background_type>(system_color_set_type::dialog_background())
            );

            const auto original_font = p_link_label->font();
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

            p_link_label->set_text_color(system_color_set_type::hyperlink_text());

            auto p_cursor = stdalt::make_unique<system_cursor_type>(system_cursor_type::style_type::hand);
            p_link_label->set_cursor(std::move(p_cursor));

            p_link_label->set_focusable(true);

            const auto focus_changed = [p_link_label]() { p_link_label->repaint(); };
            p_link_label->focus_observer_set().got_focus().connect(focus_changed);
            p_link_label->focus_observer_set().lost_focus().connect(focus_changed);
            p_link_label->paint_observer_set().paint_background().disconnect_all_slots();
            p_link_label->paint_observer_set().paint_background().connect(paint_background(*p_link_label));
            typedef typename keyboard_observer_set_type::virtual_key_type virtual_key_type;
            p_link_label->keyboard_observer_set().key_up().connect(
                [p_link_label](const virtual_key_type& virtual_key, const bool, const bool, const bool)
                {
                    if (virtual_key == virtual_key_type::space())
                        p_link_label->open_target();
                }
            );
            p_link_label->mouse_observer_set().pressed().connect(
                [p_link_label](
                    const typename mouse_observer_set_type::mouse_button_type button,
                    const position_type&,
                    const bool,
                    const bool,
                    const bool
                )
                {
                    if (button != mouse_observer_set_type::mouse_button_type::left)
                        return;

                    p_link_label->m_mouse_button_pressing = true;
                }
            );
            p_link_label->mouse_observer_set().released().connect(
                [p_link_label](
                    const typename mouse_observer_set_type::mouse_button_type button,
                    const position_type&,
                    const bool,
                    const bool,
                    const bool
                )
                {
                    if (button != mouse_observer_set_type::mouse_button_type::left)
                        return;

                    if (p_link_label->m_mouse_button_pressing)
                        p_link_label->open_target();
                    p_link_label->m_mouse_button_pressing = false;
                }
            );
        }


        // variables

        string_type m_target;

        bool m_mouse_button_pressing;


        // functions

        void open_target()
        const
        {
            shell_type::instance().execute(m_target);
        }


    };


}}}


#endif
