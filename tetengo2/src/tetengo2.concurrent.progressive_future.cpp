/*! \file
    \brief The definition of tetengo2::concurrent::progressive_future.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <mutex>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace concurrent
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        class progress_state::impl : private boost::noncopyable
        {
        public:
            // types

            using progress_type = typename progress_state::progress_type;


            // constructors and destructor

            explicit impl(progress_type initial_progress)
            :
            m_progress(std::move(initial_progress)),
            m_abort_requested(false),
            m_progress_mutex(),
            m_abort_request_mutex()
            {}


            // functions

            const progress_type& get()
            const
            {
                std::lock_guard<std::mutex> lock{ m_progress_mutex };
                return m_progress;
            }

            void set(progress_type progress)
            {
                std::lock_guard<std::mutex> lock{ m_progress_mutex };
                m_progress = std::move(progress);
            }

            bool abort_requested()
            const
            {
                std::lock_guard<std::mutex> lock{ m_abort_request_mutex };
                return m_abort_requested;
            }

            void request_abort()
            {
                std::lock_guard<std::mutex> lock{ m_abort_request_mutex };
                m_abort_requested = true;
            }


        private:
            // variables

            progress_type m_progress;

            bool m_abort_requested;

            mutable std::mutex m_progress_mutex;

            mutable std::mutex m_abort_request_mutex;


        };


        progress_state::progress_state(progress_type initial_progress)
        :
        m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(initial_progress)))
        {}

        progress_state::~progress_state()
        = default;

        const progress_state::progress_type& progress_state::get()
        const
        {
            return m_p_impl->get();
        }

        void progress_state::set(progress_type progress)
        {
            m_p_impl->set(std::move(progress));
        }

        bool progress_state::abort_requested()
        const
        {
            return m_p_impl->abort_requested();
        }

        void progress_state::request_abort()
        {
            m_p_impl->request_abort();
        }


    }
#endif


}}
