/*! \file
    \brief The definition of tetengo2::gui::widget::progress dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H)
#define TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H

#include <algorithm>
#include <chrono>
#include <functional>
#include <future>
#include <memory>
#include <ratio>
#include <string>
#include <thread>

#include <boost/lexical_cast.hpp>
#include <boost/rational.hpp>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/concurrent/progressive_promise.h>
#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/stub/timer.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/widget/button.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/progress_bar.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/message/message_catalog.h>
#include <tetengo2/text.h>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
}}}


namespace tetengo2::gui::widget {
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
        virtual ~task_result_base() = default;
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
        static T get(const task_result_base& task_result_)
        {
            return static_cast<const task_result<T>&>(task_result_).get_value();
        }

        /*!
            \brief Returns the value.

            \param task_result_ A task result.

            \return The value.
        */
        static T get(task_result_base& task_result_)
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
            const message_catalog_type& message_catalog)
        : dialog{ parent, false }, m_canceling_message{ std::move(canceling_message) }, m_p_message_label{},
          m_p_progress_label{}, m_p_progress_bar{},
          m_p_cancel_button{}, m_promise{ 0 }, m_future{ m_promise.get_future() }, m_task{ std::move(task) },
          m_p_thread{}, m_p_timer{}, m_previous_progress{}, m_message_catalog{ message_catalog }
        {
            initialize_dialog(std::move(title), std::move(waiting_message));
        }

        /*!
            \brief Destroys the progress dialog.
        */
        virtual ~progress_dialog() noexcept
        {
            try
            {
                if (m_p_thread && m_p_thread->joinable())
                    m_p_thread->join();
            }
            catch (...)
            {
            }
        }


        // functions

        /*!
            \brief Returns the task future.

            \return The task future.
        */
        future_type& task_future()
        {
            return m_future;
        }


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using solid_background_type = gui::drawing::solid_background;

        using timer_details_type = detail::stub::timer;

        using timer_type = gui::timer<widget, timer_details_type>;

        using system_color_set_type = gui::drawing::system_color_set;

        using progress_type = typename future_type::progress_type;


        // variables

        const string_type m_canceling_message;

        std::unique_ptr<label> m_p_message_label;

        std::unique_ptr<label> m_p_progress_label;

        std::unique_ptr<progress_bar> m_p_progress_bar;

        std::unique_ptr<button> m_p_cancel_button;

        promise_type m_promise;

        future_type m_future;

        const task_type m_task;

        std::unique_ptr<std::thread> m_p_thread;

        std::unique_ptr<timer_type> m_p_timer;

        progress_type m_previous_progress;

        const message_catalog_type& m_message_catalog;


        // virtual functions

        virtual void do_modal_impl() override
        {
            m_p_thread = std::make_unique<std::thread>(m_task, std::ref(m_promise));

            m_p_timer = std::make_unique<timer_type>(
                *this, [this](bool& stop) { this->timer_procedure(stop); }, std::chrono::milliseconds{ 100 }, false);
        }

        virtual void on_close_impl(bool& cancel) override
        {
            if (m_future.wait_for(std::chrono::seconds{ 0 }) != std::future_status::ready)
            {
                m_future.request_abort();

                m_p_message_label->set_text(m_canceling_message);
                m_p_progress_label->set_text(string_type{});
                m_p_progress_bar->set_state(progress_bar::state_type::pausing);
                m_p_cancel_button->set_enabled(false);

                cancel = true;
                return;
            }

            if (m_p_thread && m_p_thread->joinable())
                m_p_thread->join();
        }


        // functions

        void initialize_dialog(string_type title, string_type waiting_message)
        {
            this->set_text(std::move(title));

            m_p_message_label = create_message_label(std::move(waiting_message));
            m_p_progress_label = create_progress_label();
            m_p_progress_bar = create_progress_bar();
            m_p_cancel_button = create_cancel_button();

            locate_controls();
        }

        std::unique_ptr<label> create_message_label(string_type waiting_message)
        {
            auto p_label = std::make_unique<label>(*this);

            p_label->set_text(std::move(waiting_message));
            auto p_background = std::make_unique<solid_background_type>(
                tetengo2::detail::gui_detail_impl_set().drawing_(),
                system_color_set_type::instance().dialog_background());
            p_label->set_background(std::move(p_background));

            return p_label;
        }

        std::unique_ptr<label> create_progress_label()
        {
            auto p_label = std::make_unique<label>(*this);

            p_label->set_text(string_type{ TETENGO2_TEXT("0%") });
            auto p_background = std::make_unique<solid_background_type>(
                tetengo2::detail::gui_detail_impl_set().drawing_(),
                system_color_set_type::instance().dialog_background());
            p_label->set_background(std::move(p_background));

            return p_label;
        }

        std::unique_ptr<progress_bar> create_progress_bar()
        {
            auto p_progress_bar = std::make_unique<progress_bar>(*this);

            p_progress_bar->set_goal(100);

            return p_progress_bar;
        }

        std::unique_ptr<button> create_cancel_button()
        {
            auto p_button = std::make_unique<button>(*this, button::style_type::cancel);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
            p_button->mouse_observer_set().clicked().connect([this]() { this->close(); });

            return p_button;
        }

        void locate_controls()
        {
            this->set_client_dimension(dimension_type{ dimension_unit_type{ 30 }, dimension_unit_type{ 8 } });

            m_p_message_label->set_dimension(dimension_type{ dimension_unit_type{ 26 }, dimension_unit_type{ 2 } });
            m_p_message_label->set_position(position_type{ position_unit_type{ 2 }, position_unit_type{ 1 } });

            m_p_progress_label->set_dimension(dimension_type{ dimension_unit_type{ 3 }, dimension_unit_type{ 2 } });
            m_p_progress_label->set_position(position_type{ position_unit_type{ 2 }, position_unit_type{ 3 } });

            m_p_progress_bar->set_dimension(dimension_type{ dimension_unit_type{ 23 }, dimension_unit_type{ 1 } });
            m_p_progress_bar->set_position(position_type{ position_unit_type{ 5 }, position_unit_type{ 3 } });

            m_p_cancel_button->set_dimension(dimension_type{ dimension_unit_type{ 8 }, dimension_unit_type{ 2 } });
            m_p_cancel_button->set_position(position_type{ position_unit_type{ 20 }, position_unit_type{ 5 } });
        }

        void timer_procedure(bool&)
        {
            if (this->visible() && m_future.wait_for(std::chrono::seconds{ 0 }) == std::future_status::ready)
            {
                this->close();
                return;
            }

            update_progress();
        }

        void update_progress()
        {
            if (m_p_progress_label->text().empty())
                return;

            const auto& progress = m_future.progress();
            if (progress == m_previous_progress)
                return;
            const auto percentage = boost::rational_cast<typename progress_type::int_type>(m_future.progress() * 100U);

            auto text = boost::lexical_cast<string_type>(percentage) + string_type{ TETENGO2_TEXT("%") };
            m_p_progress_label->set_text(std::move(text));

            m_p_progress_bar->set_progress(percentage);

            m_previous_progress = progress;
        }
    };
}


#endif
