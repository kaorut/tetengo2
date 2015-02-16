/*! \file
    \brief The definition of tetengo2::gui::widget::progress dialog.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H)
#define TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H

#include <chrono>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <utility>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/concurrent/progressive_promise.h>
#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/timer.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a progress dialog.

        \tparam Traits             A traits type.
        \tparam TaskResult         A task result type.
        \tparam DetailsTraits      A detail implementation type traits.
        \tparam MenuDetails        A detail implementation type of a menu.
        \tparam MessageLoopDetails A detail implementation type of a message loop.
        \tparam TimerDetails       A detail implementation type of a timer.
    */
    template <
        typename Traits,
        typename TaskResult,
        typename DetailsTraits,
        typename MenuDetails,
        typename MessageLoopDetails,
        typename TimerDetails
    >
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

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The message loop details type.
        using message_loop_details_type = MessageLoopDetails;

        //! The timer details type.
        using timer_details_type = TimerDetails;

        //! The base type.
        using base_type = dialog<traits_type, details_traits_type, menu_details_type, message_loop_details_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The promise type.
        using promise_type = concurrent::progressive_promise<task_result_type, std::size_t>;

        //! The future type.
        using future_type = concurrent::progressive_future<task_result_type, std::size_t>;

        //! The task type.
        using task_type = std::function<void (promise_type& promise)>;


        // constructors and destructor

        /*!
            \brief Creates a progress dialog.

            \param parent A parent window.
            \param title  A title.
            \param task   A task.
        */
        progress_dialog(abstract_window_type& parent, string_type title, task_type task)
        :
        base_type(parent, false),
        m_promise(0),
        m_future(m_promise.get_future()),
        m_task(std::move(task)),
        m_p_thread(),
        m_p_timer()
        {
            initialize_dialog(std::move(title));
        }

        /*!
            \brief Destroys the progress dialog.
        */
        virtual ~progress_dialog()
        TETENGO2_STDALT_NOEXCEPT
        {
            try
            {
                if (m_p_thread && m_p_thread->joinable())
                    m_p_thread->join();
            }
            catch (...)
            {}
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

        using dimension_type = typename traits_type::dimension_type;

        using width_type = typename gui::dimension<dimension_type>::width_type;

        using height_type = typename gui::dimension<dimension_type>::height_type;

        using widget_type = typename abstract_window_type::base_type;

        using timer_type = gui::timer<widget_type, timer_details_type>;

        using message_loop_break_type = typename base_type::message_loop_break_type;


        // variables

        promise_type m_promise;

        future_type m_future;

        const task_type m_task;

        std::unique_ptr<std::thread> m_p_thread;

        std::unique_ptr<timer_type> m_p_timer;


        // virtual functions

        virtual void do_modal_impl()
        override
        {
            m_p_thread = stdalt::make_unique<std::thread>(m_task, std::ref(m_promise));

            m_p_timer =
                stdalt::make_unique<timer_type>(
                    *this,
                    [this](bool& stop) { this->timer_procedure(stop); },
                    std::chrono::milliseconds{ 100 },
                    false
                );
        }

        virtual void on_close_impl(bool& cancel)
        override
        {
            if (m_future.wait_for(std::chrono::seconds{ 0 }) != std::future_status::ready)
            {
                m_future.request_abort();
                cancel = true;
                return;
            }

            if (m_p_thread && m_p_thread->joinable())
                m_p_thread->join();
        }


        // functions

        void initialize_dialog(string_type title)
        {
            this->set_text(std::move(title));

            locate_controls();
        }

        void locate_controls()
        {
            this->set_client_dimension(dimension_type{ width_type{ 36 }, height_type{ 10 } });
        }

        void timer_procedure(bool&)
        {
            if (this->visible() && m_future.wait_for(std::chrono::seconds{ 0 }) == std::future_status::ready)
            {
                this->close();
                return;
            }
        }


    };


}}}


#endif
