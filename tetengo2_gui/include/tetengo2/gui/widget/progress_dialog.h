/*! \file
    \brief The definition of tetengo2::gui::widget::progress dialog.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H)
#define TETENGO2_GUI_WIDGET_PROGRESSDIALOG_H

#include <cstddef>
#include <functional>
#include <memory>
#include <thread>
#include <utility>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/concurrent/progressive_promise.h>
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
    */
    template <
        typename Traits,
        typename TaskResult,
        typename DetailsTraits,
        typename MenuDetails,
        typename MessageLoopDetails
    >
    class progress_dialog : public dialog<Traits, DetailsTraits, MenuDetails, MessageLoopDetails>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The task result type.
        using task_result_type = TaskResult;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The message loop details type.
        using message_loop_details_type = MessageLoopDetails;

        //! The base type.
        using base_type = dialog<traits_type, details_traits_type, menu_details_type, message_loop_details_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::base_type;

        //! The promise type.
        using promise_type = tetengo2::concurrent::progressive_promise<task_result_type, std::size_t>;

        //! The future type.
        using future_type = tetengo2::concurrent::progressive_future<task_result_type, std::size_t>;

        //! The task type.
        using task_type = std::function<void (promise_type& promise)>;


        // constructors and destructor

        /*!
            \brief Creates a progress dialog.

            \param parent A parent window.
        */
        progress_dialog(abstract_window_type& parent, task_type task)
        :
        base_type(parent, false),
        m_promise(0),
        m_future(m_promise.get_future()),
        m_task(std::move(task)),
        m_p_thread()
        {
            initialize_progress_dialog();
        }

        /*!
            \brief Destroys the progress dialog.
        */
        virtual ~progress_dialog()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


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
        // variables

        promise_type m_promise;

        future_type m_future;

        const task_type m_task;

        std::unique_ptr<std::thread> m_p_thread;


        // virtual functions

        virtual void do_modal_impl()
        override
        {
            m_p_thread = tetengo2::stdalt::make_unique<std::thread>(m_task, std::ref(m_promise));
            if (m_p_thread)
                m_p_thread->join();
        }


        // functions

        void initialize_progress_dialog()
        {
            base_type::initialize_dialog();
        }


    };


}}}


#endif
