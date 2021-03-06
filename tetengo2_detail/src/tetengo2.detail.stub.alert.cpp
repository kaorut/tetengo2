/*! \file
    \brief The definition of tetengo2::detail::stub::alert.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/alert.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::stub {
    class alert::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = alert::string_type;

        using integer_type = alert::integer_type;

        using widget_handle_type = alert::widget_handle_type;


        // static functions

        static const alert& instance()
        {
            static const alert singleton{};
            return singleton;
        }


        // functions

        widget_handle_type
        root_ancestor_widget_handle_impl(TETENGO2_STDALT_MAYBE_UNUSED const widget_handle_type widget_handle) const
        {
            return nullptr;
        }

        virtual void show_task_dialog_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const widget_handle_type widget_handle,
            TETENGO2_STDALT_MAYBE_UNUSED const string_type& caption,
            TETENGO2_STDALT_MAYBE_UNUSED const string_type& text1,
            TETENGO2_STDALT_MAYBE_UNUSED const string_type& text2,
            TETENGO2_STDALT_MAYBE_UNUSED const string_type& source_file_name,
            TETENGO2_STDALT_MAYBE_UNUSED const integer_type source_file_line) const
        {}
    };


    const alert& alert::instance()
    {
        return impl::instance();
    }

    alert::~alert() = default;

    alert::alert() : m_p_impl{ std::make_unique<impl>() } {}

    alert::widget_handle_type alert::root_ancestor_widget_handle_impl(const widget_handle_type widget_handle) const
    {
        return m_p_impl->root_ancestor_widget_handle_impl(widget_handle);
    }

    void alert::show_task_dialog_impl(
        const widget_handle_type widget_handle,
        const string_type&       caption,
        const string_type&       text1,
        const string_type&       text2,
        const string_type&       source_file_name,
        const integer_type       source_file_line) const
    {
        m_p_impl->show_task_dialog_impl(widget_handle, caption, text1, text2, source_file_name, source_file_line);
    }
}
