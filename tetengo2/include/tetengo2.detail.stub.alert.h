/*! \file
    \brief The definition of tetengo2::detail::stub::alert.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_ALERT_H)
#define TETENGO2_DETAIL_STUB_ALERT_H

#include <cstddef>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class template for a detail implementation of an alert.

        \tparam String A string type.
        \tparam Encoder An encoder type.
    */
    template <typename String, typename Encoder>
    class alert
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The widget handle type.
        typedef const void* widget_handle_type;


        // static functions

        /*!
            \brief Returns the root ancestor widget handle.

            \param widget_handle A widget handle.

            \return The root ancestor widget handle.
        */
        static widget_handle_type root_ancestor_widget_handle(
            const widget_handle_type widget_handle
        )
        {
            return NULL;
        }

        /*!
            \brief Shows a task dialog.

            \param widget_handle    A widget handle.
            \param caption          A caption.
            \param text1            A text #1.
            \param text2            A text #2.
            \param source_file_name A source file name.
            \param source_file_line A source file line number.
            \param source_function  A source function.
            \param encoder          An encoder.
        */
        static void show_task_dialog(
            const widget_handle_type widget_handle,
            const string_type&       caption,
            const string_type&       text1,
            const string_type&       text2,
            const string_type&       source_file_name,
            const int                source_file_line,
            const string_type&       source_function,
            const encoder_type&      encoder
        )
        {}


    private:
        // forbidden operations

        alert();


    };


}}}


#endif
