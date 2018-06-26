/*! \file
    \brief The definition of tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <tetengo2/gui/common_dialog/message_box.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::gui::common_dialog {
    namespace message_box_style {
        class button_style::impl
        {
        public:
            // types

            using string_type = button_style::string_type;

            using style_type = button_style::style_type;


            // static functions

            static button_style ok(const bool cancellable)
            {
                return { style_type::ok, cancellable, TETENGO2_STDALT_NULLOPT, TETENGO2_STDALT_NULLOPT };
            }

            static button_style ok(const bool cancellable, string_type ok_button_label)
            {
                return { style_type::ok,
                         cancellable,
                         tetengo2::stdalt::make_optional(std::move(ok_button_label)),
                         TETENGO2_STDALT_NULLOPT };
            }

            static button_style yes_no(const bool cancellable)
            {
                return { style_type::yes_no, cancellable, TETENGO2_STDALT_NULLOPT, TETENGO2_STDALT_NULLOPT };
            }

            static button_style
            yes_no(const bool cancellable, string_type yes_button_label, string_type no_button_label)
            {
                return button_style(
                    style_type::yes_no,
                    cancellable,
                    TETENGO2_STDALT_NULLOPT,
                    tetengo2::stdalt::make_optional(
                        std::make_pair(std::move(yes_button_label), std::move(no_button_label))));
            }


            // constructors and destructor

            impl(
                const style_type                                                       style,
                const bool                                                             cancellable,
                const tetengo2::stdalt::optional<string_type>&                         ok_button_label,
                const tetengo2::stdalt::optional<std::pair<string_type, string_type>>& yes_no_button_labels)
            : m_style{ style }, m_cancellable{ cancellable }, m_ok_button_label{ ok_button_label },
              m_yes_no_button_labels{ yes_no_button_labels }
            {}


            // functions

            style_type style() const
            {
                return m_style;
            }

            bool cancellable() const
            {
                return m_cancellable;
            }

            const tetengo2::stdalt::optional<string_type>& ok_button_label() const
            {
                return m_ok_button_label;
            }

            const tetengo2::stdalt::optional<std::pair<string_type, string_type>>& yes_no_button_labels() const
            {
                return m_yes_no_button_labels;
            }


        private:
            // variables

            style_type m_style;

            bool m_cancellable;

            tetengo2::stdalt::optional<string_type> m_ok_button_label;

            tetengo2::stdalt::optional<std::pair<string_type, string_type>> m_yes_no_button_labels;
        };


        button_style button_style::ok(const bool cancellable)
        {
            return impl::ok(cancellable);
        }

        button_style button_style::ok(const bool cancellable, string_type ok_button_label)
        {
            return impl::ok(cancellable, std::move(ok_button_label));
        }

        button_style button_style::yes_no(const bool cancellable)
        {
            return impl::yes_no(cancellable);
        }

        button_style
        button_style::yes_no(const bool cancellable, string_type yes_button_label, string_type no_button_label)
        {
            return impl::yes_no(cancellable, std::move(yes_button_label), std::move(no_button_label));
        }

        button_style::button_style(const button_style& another) : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) }
        {}

        button_style::button_style(button_style&& another) : m_p_impl{ std::move(another.m_p_impl) } {}

        button_style::~button_style() = default;

        button_style::style_type button_style::style() const
        {
            return m_p_impl->style();
        }

        bool button_style::cancellable() const
        {
            return m_p_impl->cancellable();
        }

        const tetengo2::stdalt::optional<button_style::string_type>& button_style::ok_button_label() const
        {
            return m_p_impl->ok_button_label();
        }

        const tetengo2::stdalt::optional<std::pair<button_style::string_type, button_style::string_type>>&
        button_style::yes_no_button_labels() const
        {
            return m_p_impl->yes_no_button_labels();
        }

        button_style::button_style(
            const style_type                                                       style,
            const bool                                                             cancellable,
            const tetengo2::stdalt::optional<string_type>&                         ok_button_label,
            const tetengo2::stdalt::optional<std::pair<string_type, string_type>>& yes_no_button_labels)
        : m_p_impl{ std::make_unique<impl>(style, cancellable, ok_button_label, yes_no_button_labels) }
        {}
    }

    // message_box class definition here
}