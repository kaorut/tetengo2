/*! \file
    \brief The definition of tetengo2::gui::widget::link_label.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/shell.h>
#include <tetengo2/gui/virtual_key.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/link_label.h>


namespace tetengo2::gui::widget {
    class link_label::impl : private boost::noncopyable
    {
    public:
        // static functions

        static void initialize_link_label(link_label* const p_link_label)
        {
            assert(p_link_label);

            p_link_label->set_background(std::make_unique<solid_background_type>(

                system_color_set_type::instance().dialog_background()));

            const auto original_font = p_link_label->font();
            p_link_label->set_font(font_type{ original_font.family(),
                                              original_font.size(),
                                              original_font.bold(),
                                              original_font.italic(),
                                              true,
                                              original_font.strikeout() });

            p_link_label->set_text_color(system_color_set_type::instance().hyperlink_text());

            auto p_cursor = std::make_unique<system_cursor_type>(system_cursor_type::style_type::hand);
            p_link_label->set_cursor(std::move(p_cursor));

            p_link_label->set_focusable(true);

            const auto focus_changed = [p_link_label]() { p_link_label->repaint(); };
            p_link_label->focus_observer_set().got_focus().connect(focus_changed);
            p_link_label->focus_observer_set().lost_focus().connect(focus_changed);
            p_link_label->paint_observer_set().paint_background().disconnect_all_slots();
            p_link_label->paint_observer_set().paint_background().connect(paint_background(*p_link_label));
            using virtual_key_type = typename keyboard_observer_set_type::virtual_key_type;
            p_link_label->keyboard_observer_set().key_up().connect(
                [p_link_label](const virtual_key_type& virtual_key, const bool, const bool, const bool) {
                    if (virtual_key == virtual_key_type::space())
                        p_link_label->m_p_impl->open_target();
                });
            p_link_label->mouse_observer_set().pressed().connect(
                [p_link_label](
                    const typename mouse_observer_set_type::mouse_button_type button,
                    const position_type&,
                    const bool,
                    const bool,
                    const bool) {
                    if (button != mouse_observer_set_type::mouse_button_type::left)
                        return;

                    p_link_label->m_p_impl->m_mouse_button_pressing = true;
                });
            p_link_label->mouse_observer_set().released().connect(
                [p_link_label](
                    const typename mouse_observer_set_type::mouse_button_type button,
                    const position_type&,
                    const bool,
                    const bool,
                    const bool) {
                    if (button != mouse_observer_set_type::mouse_button_type::left)
                        return;

                    if (p_link_label->m_p_impl->m_mouse_button_pressing)
                        p_link_label->m_p_impl->open_target();
                    p_link_label->m_p_impl->m_mouse_button_pressing = false;
                });
        }


        // constructors and destructor

        impl() : m_target{}, m_mouse_button_pressing{ false } {}


        // functions

        const string_type& target() const
        {
            return m_target;
        }

        void set_target(string_type target)
        {
            m_target = std::move(target);
        }


    private:
        // types

        using solid_background_type = gui::drawing::solid_background;

        using system_color_set_type = gui::drawing::system_color_set;

        using shell_type = gui::shell;

        using system_cursor_type = cursor::system;

        class paint_background
        {
        public:
            paint_background(link_label& self) : m_self{ self } {}

            bool operator()(canvas_type& canvas) const
            {
                if (!m_self.p_background())
                    return false;

                canvas.set_background(m_self.p_background()->clone());
                canvas.fill_rectangle(position_type{}, m_self.client_dimension());
                if (m_self.focused())
                    canvas.draw_focus_indication(position_type{}, m_self.client_dimension());

                return true;
            }

        private:
            link_label& m_self;
        };


        // variables

        string_type m_target;

        bool m_mouse_button_pressing;


        // functions

        void open_target() const
        {
            shell_type{}.execute(m_target);
        }
    };


    link_label::link_label(widget& parent) : label{ parent }, m_p_impl{ std::make_unique<impl>() }
    {
        impl::initialize_link_label(this);
    }

    link_label::~link_label() = default;

    const link_label::string_type& link_label::target() const
    {
        return m_p_impl->target();
    }

    void link_label::set_target(string_type target)
    {
        m_p_impl->set_target(std::move(target));
    }
}
