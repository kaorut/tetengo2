/*! \file
    \brief The definition of tetengo2::detail::windows::alert.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ALERT_H)
#define TETENGO2_DETAIL_WINDOWS_ALERT_H

#include <memory>

#include <tetengo2/detail/base/alert.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of an alert.
    */
    class alert : public base::alert
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;

        //! The integer type.
        using integer_type = type_list::integer_type;

        //! The widget handle type.
        using widget_handle_type = base::alert::widget_handle_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const alert& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        ~alert();


    private:
        // types

        class impl;


        // variables

        std::unique_ptr<impl> m_p_impl;


        // constructors

        alert();


        // virtual functions

        virtual widget_handle_type root_ancestor_widget_handle_impl(widget_handle_type widget_handle)
        const override;

        virtual void show_task_dialog_impl(
            widget_handle_type widget_handle,
            const string_type& caption,
            const string_type& text1,
            const string_type& text2,
            const string_type& source_file_name,
            integer_type       source_file_line
        )
        const override;


    };


}}}


#endif
