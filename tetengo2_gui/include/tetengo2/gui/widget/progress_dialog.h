/*! \file
    \brief The definition of tetengo2::gui::widget::progress dialog.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H)
#define TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H

#include <functional>
#include <memory>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/concurrent/progressive_promise.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/message/message_catalog.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::widget {
    class abstract_window;

    /*!
        \brief The base class for a task result.
    */
    class task_result_base
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the task result.
        */
        virtual ~task_result_base();
    };


    /*!
        \brief The class for a task result.

        \tparam T A type.
    */
    template <typename T>
    struct task_result : public task_result_base
    {
    public:
        // static functions

        /*!
            \brief Returns the value.

            \param task_result_ A task result.

            \return The value.
        */
        static const T& get(const task_result_base& task_result_)
        {
            return static_cast<const task_result<T>&>(task_result_).get_value();
        }

        /*!
            \brief Returns the value.

            \param task_result_ A task result.

            \return The value.
        */
        static T& get(task_result_base& task_result_)
        {
            return static_cast<task_result<T>&>(task_result_).get_value();
        }


        // constructors and destructor

        /*!
            \brief Creates a task result.

            \param value A value.
        */
        explicit task_result(T value) : m_value{ std::move(value) } {}

        /*!
            \brief Destroys the task result.
        */
        virtual ~task_result() = default;


        // functions

        /*!
            \brief Returns the value.

            \return The value.
        */
        const T& get_value() const
        {
            return m_value;
        }

        /*!
            \brief Returns the value.

            \return The value.
        */
        T& get_value()
        {
            return m_value;
        }


    private:
        // variables

        T m_value;
    };


    /*!
        \brief The class for a progress dialog.
    */
    class progress_dialog : public dialog
    {
    public:
        // types

        //! The string type.
        using string_type = tetengo2::type_list::string_type;

        //! The message catalog type.
        using message_catalog_type = tetengo2::message::message_catalog;

        //! The promise type.
        using promise_type = concurrent::progressive_promise<std::unique_ptr<task_result_base>>;

        //! The future type.
        using future_type = concurrent::progressive_future<std::unique_ptr<task_result_base>>;

        //! The task type.
        using task_type = std::function<void(promise_type& promise)>;


        // constructors and destructor

        /*!
            \brief Creates a progress dialog.

            \param parent            A parent window.
            \param title             A title.
            \param waiting_message   A waiting message.
            \param canceling_message A canceling message.
            \param task              A task.
            \param message_catalog   A message catalog.
        */
        progress_dialog(
            abstract_window&            parent,
            string_type                 title,
            string_type                 waiting_message,
            string_type                 canceling_message,
            task_type                   task,
            const message_catalog_type& message_catalog);

        /*!
            \brief Destroys the progress dialog.
        */
        virtual ~progress_dialog() noexcept;


        // functions

        /*!
            \brief Returns the task future.

            \return The task future.
        */
        future_type& task_future();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void do_modal_impl() override;

        virtual void on_close_impl(bool& cancel) override;
    };
}


#endif
