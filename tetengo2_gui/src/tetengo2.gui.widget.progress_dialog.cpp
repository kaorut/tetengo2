/*! \file
    \brief The definition of tetengo2::gui::widget::progress dialog.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <algorithm>
#include <chrono>
#include <functional>
#include <future>
#include <memory>
#include <ratio>
#include <string>
#include <thread>

#include <boost/core/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/rational.hpp>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/concurrent/progressive_promise.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/widget/button.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/progress_bar.h>
#include <tetengo2/gui/widget/progress_dialog.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/text.h>


namespace tetengo2::gui::widget {
    class abstract_window;


    task_result_base::~task_result_base() = default;


    class progress_dialog::impl : private boost::noncopyable
    {
    public:
        // types

        using message_catalog_type = progress_dialog::message_catalog_type;

        using promise_type = progress_dialog::promise_type;

        using future_type = progress_dialog::future_type;

        using task_type = progress_dialog::task_type;


        // static functions

        static void initialize_dialog(progress_dialog& dialog, string_type title, string_type waiting_message)
        {
            dialog.set_text(std::move(title));

            dialog.m_p_impl->m_p_message_label = create_message_label(dialog, std::move(waiting_message));
            dialog.m_p_impl->m_p_progress_label = create_progress_label(dialog);
            dialog.m_p_impl->m_p_progress_bar = create_progress_bar(dialog);
            dialog.m_p_impl->m_p_cancel_button = create_cancel_button(dialog);

            locate_controls(dialog);
        }

        static void terminate_dialog(progress_dialog& dialog)
        {
            if (dialog.m_p_impl->m_p_thread && dialog.m_p_impl->m_p_thread->joinable())
                dialog.m_p_impl->m_p_thread->join();
        }

        // constructors and destructor

        impl(string_type canceling_message, task_type task, const message_catalog_type& message_catalog)
        : m_canceling_message{ std::move(canceling_message) }, m_p_message_label{}, m_p_progress_label{},
          m_p_progress_bar{},
          m_p_cancel_button{}, m_promise{ 0 }, m_future{ m_promise.get_future() }, m_task{ std::move(task) },
          m_p_thread{}, m_p_timer{}, m_previous_progress{}, m_message_catalog{ message_catalog }
        {}

        // virtual ~progress_dialog() noexcept
        //{
        //}


        // functions

        future_type& task_future()
        {
            return m_future;
        }

        void do_modal_impl(progress_dialog& self)
        {
            m_p_thread = std::make_unique<std::thread>(m_task, std::ref(m_promise));

            m_p_timer = std::make_unique<timer_type>(
                self,
                [this, &self](bool& stop) { this->timer_procedure(stop, self); },
                std::chrono::milliseconds{ 100 },
                false);
        }

        void on_close_impl(bool& cancel)
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


    private:
        // types

        using position_unit_type = typename position_type::unit_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using solid_background_type = gui::drawing::solid_background;

        using timer_type = gui::timer;

        using system_color_set_type = gui::drawing::system_color_set;

        using progress_type = typename future_type::progress_type;


        // static functions

        static std::unique_ptr<label> create_message_label(progress_dialog& dialog, string_type waiting_message)
        {
            auto p_label = std::make_unique<label>(dialog);

            p_label->set_text(std::move(waiting_message));
            auto p_background = std::make_unique<solid_background_type>(

                system_color_set_type::instance().dialog_background());
            p_label->set_background(std::move(p_background));

            return p_label;
        }

        static std::unique_ptr<label> create_progress_label(progress_dialog& dialog)
        {
            auto p_label = std::make_unique<label>(dialog);

            p_label->set_text(string_type{ TETENGO2_TEXT("0%") });
            auto p_background = std::make_unique<solid_background_type>(

                system_color_set_type::instance().dialog_background());
            p_label->set_background(std::move(p_background));

            return p_label;
        }

        static std::unique_ptr<progress_bar> create_progress_bar(progress_dialog& dialog)
        {
            auto p_progress_bar = std::make_unique<progress_bar>(dialog);

            p_progress_bar->set_goal(100);

            return p_progress_bar;
        }

        static std::unique_ptr<button> create_cancel_button(progress_dialog& dialog)
        {
            auto p_button = std::make_unique<button>(dialog, button::style_type::cancel);

            p_button->set_text(dialog.m_p_impl->m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
            p_button->mouse_observer_set().clicked().connect([&dialog]() { dialog.close(); });

            return p_button;
        }

        static void locate_controls(progress_dialog& dialog)
        {
            dialog.set_client_dimension(dimension_type{ dimension_unit_type{ 30 }, dimension_unit_type{ 8 } });

            dialog.m_p_impl->m_p_message_label->set_dimension(
                dimension_type{ dimension_unit_type{ 26 }, dimension_unit_type{ 2 } });
            dialog.m_p_impl->m_p_message_label->set_position(
                position_type{ position_unit_type{ 2 }, position_unit_type{ 1 } });

            dialog.m_p_impl->m_p_progress_label->set_dimension(
                dimension_type{ dimension_unit_type{ 3 }, dimension_unit_type{ 2 } });
            dialog.m_p_impl->m_p_progress_label->set_position(
                position_type{ position_unit_type{ 2 }, position_unit_type{ 3 } });

            dialog.m_p_impl->m_p_progress_bar->set_dimension(
                dimension_type{ dimension_unit_type{ 23 }, dimension_unit_type{ 1 } });
            dialog.m_p_impl->m_p_progress_bar->set_position(
                position_type{ position_unit_type{ 5 }, position_unit_type{ 3 } });

            dialog.m_p_impl->m_p_cancel_button->set_dimension(
                dimension_type{ dimension_unit_type{ 8 }, dimension_unit_type{ 2 } });
            dialog.m_p_impl->m_p_cancel_button->set_position(
                position_type{ position_unit_type{ 20 }, position_unit_type{ 5 } });
        }


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


        // functions

        void timer_procedure(bool&, progress_dialog& self)
        {
            if (self.visible() && m_future.wait_for(std::chrono::seconds{ 0 }) == std::future_status::ready)
            {
                self.close();
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


    progress_dialog::progress_dialog(
        abstract_window&            parent,
        string_type                 title,
        string_type                 waiting_message,
        string_type                 canceling_message,
        task_type                   task,
        const message_catalog_type& message_catalog)
    : dialog{ parent, false }, m_p_impl{
          std::make_unique<impl>(std::move(canceling_message), std::move(task), message_catalog)
      }
    {
        impl::initialize_dialog(*this, std::move(title), std::move(waiting_message));
    }

    progress_dialog::~progress_dialog() noexcept
    {
        try
        {
            impl::terminate_dialog(*this);
        }
        catch (...)
        {
        }
    }

    progress_dialog::future_type& progress_dialog::task_future()
    {
        return m_p_impl->task_future();
    }

    void progress_dialog::do_modal_impl()
    {
        m_p_impl->do_modal_impl(*this);
    }

    void progress_dialog::on_close_impl(bool& cancel)
    {
        m_p_impl->on_close_impl(cancel);
    }
}
