/*! \file
    \brief The definition of tetengo2::detail::base::alert.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_ALERT_H)
#define TETENGO2_DETAIL_BASE_ALERT_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2 { namespace detail { namespace base {
    /*!
        \brief The class for a detail implementation of an alert.
    */
    class alert : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The integer type.
        using integer_type = type_list::integer_type;

        //! The widget details type.
        struct widget_details_type
        {
        };

        //! The widget handle type.
        using widget_handle_type = widget_details_type*;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        ~alert();


        // functions

        /*!
            \brief Returns the root ancestor widget handle.

            \param widget_handle A widget handle.

            \return The root ancestor widget handle.
        */
        widget_handle_type root_ancestor_widget_handle(widget_handle_type widget_handle) const;

        /*!
            \brief Shows a task dialog.

            \param widget_handle    A widget handle.
            \param caption          A caption.
            \param text1            A text #1.
            \param text2            A text #2.
            \param source_file_name A source file name.
            \param source_file_line A source file line number.
        */
        void show_task_dialog(
            widget_handle_type widget_handle,
            const string_type& caption,
            const string_type& text1,
            const string_type& text2,
            const string_type& source_file_name,
            integer_type       source_file_line) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        alert();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual widget_handle_type root_ancestor_widget_handle_impl(widget_handle_type widget_handle) const = 0;

        virtual void show_task_dialog_impl(
            widget_handle_type widget_handle,
            const string_type& caption,
            const string_type& text1,
            const string_type& text2,
            const string_type& source_file_name,
            integer_type       source_file_line) const = 0;
    };


}}}


#endif
