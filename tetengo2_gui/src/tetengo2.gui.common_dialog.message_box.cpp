/*! \file
    \brief The definition of tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/common_dialog.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/common_dialog/message_box.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


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

    class message_box::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = message_box::string_type;

        using abstract_window_type = message_box::abstract_window_type;

        using button_style_type = message_box::button_style_type;

        using icon_style_type = message_box::icon_style_type;

        using button_id_type = message_box::button_id_type;

        using details_type = message_box::details_type;


        // constructors and destructor

        impl(
            abstract_window_type&    parent,
            string_type              title,
            string_type              main_content,
            string_type              sub_content,
            const button_style_type& button_style,
            const icon_style_type    icon_style)
        : m_p_details{ detail::gui_detail_impl_set().common_dialog_().create_message_box(
              parent,
              std::move(title),
              std::move(main_content),
              std::move(sub_content),
              button_style.cancellable(),
              to_details_button_style(button_style.style()),
              to_details_icon_style(icon_style),
              button_style.ok_button_label(),
              button_style.yes_no_button_labels()) }
        {}


        // functions

        button_id_type do_modal()
        {
            return to_button_id(detail::gui_detail_impl_set().common_dialog_().show_message_box(*m_p_details));
        }

        const details_type& details() const
        {
            return *m_p_details;
        }

        details_type& details()
        {
            return *m_p_details;
        }


    private:
        // types

        using details_ptr_type = detail::base::common_dialog::message_box_details_ptr_type;


        // static functions

        static detail::base::common_dialog::message_box_button_style_type
        to_details_button_style(const typename button_style_type::style_type style)
        {
            switch (style)
            {
            case button_style_type::style_type::ok:
                return detail::base::common_dialog::message_box_button_style_type::ok;
            case button_style_type::style_type::yes_no:
                return detail::base::common_dialog::message_box_button_style_type::yes_no;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid button style." }));
            }
        }

        static detail::base::common_dialog::message_box_icon_style_type
        to_details_icon_style(const icon_style_type style)
        {
            switch (style)
            {
            case icon_style_type::error:
                return detail::base::common_dialog::message_box_icon_style_type::error;
            case icon_style_type::warning:
                return detail::base::common_dialog::message_box_icon_style_type::warning;
            case icon_style_type::information:
                return detail::base::common_dialog::message_box_icon_style_type::information;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid icon style." }));
            }
        }

        static button_id_type
        to_button_id(const detail::base::common_dialog::message_box_button_id_type details_button_id)
        {
            switch (details_button_id)
            {
            case detail::base::common_dialog::message_box_button_id_type::ok:
                return button_id_type::ok;
            case detail::base::common_dialog::message_box_button_id_type::yes:
                return button_id_type::yes;
            case detail::base::common_dialog::message_box_button_id_type::no:
                return button_id_type::no;
            case detail::base::common_dialog::message_box_button_id_type::cancel:
                return button_id_type::cancel;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid button ID."));
            }
        }


        // variables

        details_ptr_type m_p_details;
    };


    message_box::message_box(
        abstract_window_type&    parent,
        string_type              title,
        string_type              main_content,
        string_type              sub_content,
        const button_style_type& button_style,
        const icon_style_type    icon_style)
    : m_p_impl{ std::make_unique<
          impl>(parent, std::move(title), std::move(main_content), std::move(sub_content), button_style, icon_style) }
    {}

    message_box::~message_box() = default;

    message_box::button_id_type message_box::do_modal()
    {
        return m_p_impl->do_modal();
    }

    const message_box::details_type& message_box::details() const
    {
        return m_p_impl->details();
    }

    message_box::details_type& message_box::details()
    {
        return m_p_impl->details();
    }
}