/*! \file
    \brief The definition of tetengo2::gui::widget::link_label.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_LINKLABEL_H)
#define TETENGO2_GUI_WIDGET_LINKLABEL_H

#include <cassert>
#include <utility>

#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/shell.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a link label.

        \tparam Traits             A traits type.
        \tparam DetailsTraits      A detail implementation type traits.
        \tparam SystemColorDetails A detail implementation type of system colors.
        \tparam ShellDetails       A detail implementation type of a shell.
    */
    template <typename Traits, typename DetailsTraits, typename SystemColorDetails, typename ShellDetails>
    class link_label : public label<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The drawing details type.
        using drawing_details_type = typename details_traits_type::drawing_details_type;

        //! The system color details type.
        using system_color_details_type = SystemColorDetails;

        //! The shell details type.
        using shell_details_type = ShellDetails;

        //! The base type.
        using base_type = label<traits_type, details_traits_type>;

        //! The canvas type.
        using canvas_type = typename base_type::canvas_type;

        //! The position type.
        using position_type = typename base_type::position_type;

        //! The widget type.
        using widget_type = typename base_type::base_type::base_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The font type.
        using font_type = typename base_type::font_type;

        //! The encoder type.
        using encoder_type = typename base_type::encoder_type;

        //! The system cursor type.
        using system_cursor_type = typename base_type::system_cursor_type;

        //! The mouse observer set type.
        using mouse_observer_set_type = typename base_type::mouse_observer_set_type;

        //! The keyboard observer set type.
        using keyboard_observer_set_type = typename base_type::keyboard_observer_set_type;

        //! The solid background type.
        using solid_background_type = gui::drawing::solid_background<drawing_details_type>;

        //! The system color set type.
        using system_color_set_type = gui::drawing::system_color_set<system_color_details_type>;

        //! The shell type.
        using shell_type = gui::shell<string_type, encoder_type, shell_details_type>;


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
        = default;


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

        using left_type = typename gui::position<position_type>::left_type;

        using top_type = typename gui::position<position_type>::top_type;

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
                canvas.fill_rectangle(position_type{ left_type{ 0 }, top_type{ 0 } }, m_self.client_dimension());
                if (m_self.focused())
                {
                    canvas.draw_focus_indication(
                        position_type{ left_type{ 0 }, top_type{ 0 } }, m_self.client_dimension()
                    );
                }

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
                font_type{
                    original_font.family(),
                    original_font.size(),
                    original_font.bold(),
                    original_font.italic(),
                    true,
                    original_font.strikeout()
                }
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
            using virtual_key_type = typename keyboard_observer_set_type::virtual_key_type;
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
