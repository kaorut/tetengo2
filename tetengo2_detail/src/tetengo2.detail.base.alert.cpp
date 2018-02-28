/*! \file
    \brief The definition of tetengo2::detail::base::alert.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace base {
    class alert::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = alert::string_type;

        using integer_type = alert::integer_type;

        using widget_handle_type = alert::widget_handle_type;


        // functions

        widget_handle_type root_ancestor_widget_handle(const widget_handle_type widget_handle, const alert& base) const
        {
            return base.root_ancestor_widget_handle_impl(widget_handle);
        }

        void show_task_dialog(
            const widget_handle_type widget_handle,
            const string_type&       caption,
            const string_type&       text1,
            const string_type&       text2,
            const string_type&       source_file_name,
            const integer_type       source_file_line,
            const alert&             base) const
        {
            base.show_task_dialog_impl(widget_handle, caption, text1, text2, source_file_name, source_file_line);
        }
    };


    alert::~alert() = default;

    alert::widget_handle_type alert::root_ancestor_widget_handle(const widget_handle_type widget_handle) const
    {
        return m_p_impl->root_ancestor_widget_handle(widget_handle, *this);
    }

    void alert::show_task_dialog(
        const widget_handle_type widget_handle,
        const string_type&       caption,
        const string_type&       text1,
        const string_type&       text2,
        const string_type&       source_file_name,
        const integer_type       source_file_line) const
    {
        m_p_impl->show_task_dialog(widget_handle, caption, text1, text2, source_file_name, source_file_line, *this);
    }

    alert::alert() : m_p_impl(stdalt::make_unique<impl>()) {}


}}}
