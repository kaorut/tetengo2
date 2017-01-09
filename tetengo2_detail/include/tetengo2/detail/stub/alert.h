/*! \file
    \brief The definition of tetengo2::detail::stub::alert.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_ALERT_H)
#define TETENGO2_DETAIL_STUB_ALERT_H

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of an alert.
    */
    class alert : private boost::noncopyable
    {
    public:
        // types

        //! The widget handle type.
        using widget_handle_type = const void*;


        // static functions

        /*!
            \brief Returns the root ancestor widget handle.

            \param widget_handle A widget handle.

            \return The root ancestor widget handle.
        */
        static widget_handle_type root_ancestor_widget_handle(const widget_handle_type widget_handle)
        {
            boost::ignore_unused(widget_handle);

            return nullptr;
        }

        /*!
            \brief Shows a task dialog.

            \tparam String  A string type.
            \tparam Encoder An encoder type.

            \param widget_handle    A widget handle.
            \param caption          A caption.
            \param text1            A text #1.
            \param text2            A text #2.
            \param source_file_name A source file name.
            \param source_file_line A source file line number.
            \param encoder          An encoder.
        */
        template <typename String, typename Encoder>
        static void show_task_dialog(
            const widget_handle_type widget_handle,
            const String&            caption,
            const String&            text1,
            const String&            text2,
            const String&            source_file_name,
            const int                source_file_line,
            const Encoder&           encoder
        )
        {
            boost::ignore_unused(widget_handle, caption, text1, text2, source_file_name, source_file_line, encoder);
        }


    private:
        // forbidden operations

        alert()
        = delete;


    };


}}}


#endif
