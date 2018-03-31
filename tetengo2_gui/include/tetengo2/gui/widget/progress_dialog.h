/*! \file
    \brief The definition of tetengo2::gui::widget::progress dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H)
#define TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H

#include <chrono>
#include <functional>
#include <future>
#include <memory>
#include <thread>

#include <boost/lexical_cast.hpp>
#include <boost/rational.hpp>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/concurrent/progressive_promise.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/system_color_set.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/widget/button.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/progress_bar.h>
#include <tetengo2/text.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class template for a progress dialog.

        \tparam Traits             A traits type.
        \tparam TaskResult         A task result type.
        \tparam MessageCatalog     A message catalog type.
        \tparam DetailsTraits      A detail implementation type traits.
        \tparam MenuDetails        A detail implementation type of a menu.
        \tparam MessageLoopDetails A detail implementation type of a message loop.
        \tparam TimerDetails       A detail implementation type of a timer.
        \tparam SystemColorDetails A detail implementation type of a system color.
    */
    template <
        typename Traits,
        typename TaskResult,
        typename MessageCatalog,
        typename DetailsTraits,
        typename MenuDetails,
        typename MessageLoopDetails,
        typename TimerDetails,
        typename SystemColorDetails>
    class progress_dialog : public dialog<Traits, DetailsTraits, MenuDetails, MessageLoopDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The string type.
        using string_type = typename traits_type::string_type;

        //! The task result type.
        using task_result_type = TaskResult;

        //! The message catalog type.
        using message_catalog_type = MessageCatalog;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The message loop details type.
        using message_loop_details_type = MessageLoopDetails;

        //! The timer details type.
        using timer_details_type = TimerDetails;

        //! The system color details type.
        using system_color_details_type = SystemColorDetails;

        //! The base type.
        using base_type = dialog<traits_type, details_traits_type, menu_details_type, message_loop_details_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The promise type.
        using promise_type = concurrent::progressive_promise<task_result_type>;

        //! The future type.
        using future_type = concurrent::progressive_future<task_result_type>;

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
            abstract_window_type&       parent,
            string_type                 title,
            string_type                 waiting_message,
            string_type                 canceling_message,
            task_type                   task,
            const message_catalog_type& message_catalog)
        : base_type{ parent, false }, m_canceling_message{ std::move(canceling_message) }, m_p_message_label{},
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

        using position_type = typename traits_type::position_type;

        using position_unit_type = typename position_type::unit_type;

        using dimension_type = typename traits_type::dimension_type;

        using dimension_unit_type = typename dimension_type::unit_type;

        using widget_type = typename abstract_window_type::base_type;

        using label_type = label<traits_type, details_traits_type>;

        using progress_bar_type = progress_bar<traits_type, details_traits_type>;

        using button_type = button<traits_type, details_traits_type>;

        using drawing_details_type = typename details_traits_type::drawing_details_type;

        using solid_background_type = gui::drawing::solid_background<drawing_details_type>;

        using timer_type = gui::timer<widget_type, timer_details_type>;

        using system_color_set_type = gui::drawing::system_color_set<system_color_details_type>;

        using message_loop_break_type = typename base_type::message_loop_break_type;

        using progress_type = typename future_type::progress_type;


        // variables

        const string_type m_canceling_message;

        std::unique_ptr<label_type> m_p_message_label;

        std::unique_ptr<label_type> m_p_progress_label;

        std::unique_ptr<progress_bar_type> m_p_progress_bar;

        std::unique_ptr<button_type> m_p_cancel_button;

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
                m_p_progress_bar->set_state(progress_bar_type::state_type::pausing);
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

        std::unique_ptr<label_type> create_message_label(string_type waiting_message)
        {
            auto p_label = std::make_unique<label_type>(*this);

            p_label->set_text(std::move(waiting_message));
            auto p_background = std::make_unique<solid_background_type>(system_color_set_type::dialog_background());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<label_type> create_progress_label()
        {
            auto p_label = std::make_unique<label_type>(*this);

            p_label->set_text(string_type{ TETENGO2_TEXT("0%") });
            auto p_background = std::make_unique<solid_background_type>(system_color_set_type::dialog_background());
            p_label->set_background(std::move(p_background));

            return std::move(p_label);
        }

        std::unique_ptr<progress_bar_type> create_progress_bar()
        {
            auto p_progress_bar = std::make_unique<progress_bar_type>(*this);

            p_progress_bar->set_goal(100);

            return std::move(p_progress_bar);
        }

        std::unique_ptr<button_type> create_cancel_button()
        {
            auto p_button = std::make_unique<button_type>(*this, button_type::style_type::cancel);

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("Common:Cancel")));
            p_button->mouse_observer_set().clicked().connect([this]() { this->close(); });

            return std::move(p_button);
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
