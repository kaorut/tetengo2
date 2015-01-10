/*! \file
    \brief The definition of tetengo2::concurrent::progressive_future.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PROGRESSIVEFUTURE_H)
#define TETENGO2_CONCURRENT_PROGRESSIVEFUTURE_H

#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>


namespace tetengo2 { namespace concurrent
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        template <typename Progress>
        class progress_state : private boost::noncopyable
        {
        public:
            // types

            using progress_type = Progress;


            // constructors and destructor

            explicit progress_state(progress_type initial_progress)
            :
            m_progress(std::move(initial_progress)),
            m_aborted(false),
            m_progress_mutex(),
            m_abortion_mutex()
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
                std::lock_guard<std::mutex> lock{ m_abortion_mutex };
                return m_aborted;
            }

            void request_abort()
            {
                std::lock_guard<std::mutex> lock{ m_abortion_mutex };
                m_aborted = true;
            }


        private:
            // variables

            progress_type m_progress;

            bool m_aborted;

            mutable std::mutex m_progress_mutex;

            mutable std::mutex m_abortion_mutex;


        };

        template <>
        class progress_state<void> : private boost::noncopyable
        {
        public:
            // types

            using progress_type = void;


            // constructors and destructor

            explicit progress_state()
            :
            m_aborted(false),
            m_abortion_mutex()
            {}


            // functions

            void get()
            const
            {}

            void set()
            {}

            bool abort_requested()
            const
            {
                std::lock_guard<std::mutex> lock{ m_abortion_mutex };
                return m_aborted;
            }

            void request_abort()
            {
                std::lock_guard<std::mutex> lock{ m_abortion_mutex };
                m_aborted = true;
            }


        private:
            // variables

            bool m_aborted;

            mutable std::mutex m_abortion_mutex;


        };


    }
#endif


    /*!
        \brief The class template for a progressive future base.

        \tparam T        A type.
        \tparam Progress A progress type.
    */
    template <typename T, typename Progress>
    class progressive_future_base
    {
    public:
        // types

        //! The result type.
        using result_type = T;

        //! The progress type.
        using progress_type = Progress;

        //! The future type.
        using future_type = std::future<result_type>;


        // constructors and destructor

        /*!
            \brief Creates an empty progressive future base.
        */
        progressive_future_base()
        TETENGO2_STDALT_NOEXCEPT
        :
        m_future(),
        m_p_state()
        {}

        /*!
            \brief Moves a progressive future base.

            \param another Another progressive future base.
        */
        progressive_future_base(progressive_future_base&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        m_future(std::move(another.m_future)),
        m_p_state(std::move(another.m_p_state))
        {}

#if !defined(DOCUMENTATION)
        progressive_future_base(
            future_type&&                                                 future,
            const std::shared_ptr<detail::progress_state<progress_type>>& p_state
        )
        :
        m_future(std::move(future)),
        m_p_state(p_state)
        {}
#endif


        // functions

        /*!
            \brief Assigns another progressive future base.

            \param another Another progressive future base.

            \return This object.
        */
        progressive_future_base& operator=(progressive_future_base&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            m_future = std::move(another.m_future);
            m_p_state = std::move(another.m_p_state);

            return *this;
        }

        /*!
            \brief Returns whether this future has a shared state.

            \retval true  When this future has a shared state.
            \retval false Otherwise.
        */
        bool valid()
        const TETENGO2_STDALT_NOEXCEPT
        {
            return m_future.valid() && m_p_state;
        }

        /*!
            \brief Waits for the task.
        */
        void wait()
        const
        {
            m_future.wait();
        }

        /*!
            \brief Waits for the task for the specified relative time.

            \tparam Rep    A time count type.
            \tparam Period A time period type.

            \param rel_time A relative time.

            \return A future status.
        */
        template <typename Rep, typename Period>
        std::future_status wait_for(const std::chrono::duration<Rep, Period>& rel_time)
        const
        {
            return m_future.wait_for(rel_time);
        }

        /*!
            \brief Waits for the task for the specified absolute time.

            \tparam Clock    A time clock type.
            \tparam Duration A time duration type.

            \param abs_time A absolute time.

            \return A future status.
        */
        template <typename Clock, typename Duration>
        std::future_status wait_until(const std::chrono::time_point<Clock, Duration>& abs_time)
        const
        {
            return m_future.wait_until(abs_time);
        }

        /*!
            \brief Returns the progress.

            \return The progress.

            \throw std::logic_error When this future is not valid.
        */
        const progress_type& progress()
        const
        {
            if (!valid())
                throw std::logic_error{ "This future is not valid." };

            return m_p_state->get();
        }

        /*!
            \brief Request to abort the task.
        */
        void request_abort()
        {
            if (!valid())
                throw std::logic_error{ "This future is not valid." };

            m_p_state->request_abort();
        }


    protected:
        // functions

        /*!
            \brief Returns the future.

            \return The future.
        */
        const future_type& get_future()
        const
        {
            return m_future;
        }

        /*!
            \brief Returns the future.

            \return The future.
        */
        future_type& get_future()
        {
            return m_future;
        }


    private:
        // variables

        future_type m_future;

        std::shared_ptr<detail::progress_state<progress_type>> m_p_state;

        
        // forbidden operations

        progressive_future_base(const progressive_future_base&) = delete;

        progressive_future_base& operator=(const progressive_future_base&) = delete;
        

    };


    /*!
        \brief The class template for a progressive future.

        \tparam T        A type.
        \tparam Progress A progress type.
    */
    template <typename T, typename Progress>
    class progressive_future : public progressive_future_base<T, Progress>
    {
    public:
        // types

        //! The result type.
        using result_type = T;

        //! The progress type.
        using progress_type = Progress;

        //! The base type.
        using base_type = progressive_future_base<result_type, progress_type>;

        //! The future type.
        using future_type = std::future<result_type>;


        // constructors and destructor

        /*!
            \brief Creates an empty progressive future.
        */
        progressive_future()
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type()
        {}

        /*!
            \brief Moves a progressive future.

            \param another Another progressive future.
        */
        progressive_future(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type(std::move(another))
        {}

#if !defined(DOCUMENTATION)
        progressive_future(future_type&& future, const std::shared_ptr<detail::progress_state<progress_type>>& p_state)
        :
        base_type(std::move(future), p_state)
        {}
#endif


        // functions

        /*!
            \brief Assigns another progressive future.

            \param another Another progressive future.

            \return This object.
        */
        progressive_future& operator=(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        /*!
            \brief Returns the result.

            \return The result.
        */
        result_type get()
        {
            return this->get_future().get();
        }


    };


#if !defined(DOCUMENTATION)
    template <typename R, typename Progress>
    class progressive_future<R&, Progress> : public progressive_future_base<R&, Progress>
    {
    public:
        // types

        using result_type = R&;

        using progress_type = Progress;

        using base_type = progressive_future_base<result_type, progress_type>;

        using future_type = std::future<result_type>;


        // constructors and destructor

        progressive_future()
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type()
        {}

        progressive_future(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type(std::move(another))
        {}

        progressive_future(future_type&& future, const std::shared_ptr<detail::progress_state<progress_type>>& p_state)
        :
        base_type(std::move(future), p_state)
        {}


        // functions

        progressive_future& operator=(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        result_type get()
        {
            return this->get_future().get();
        }


    };


    template <typename Progress>
    class progressive_future<void, Progress> : public progressive_future_base<void, Progress>
    {
    public:
        // types

        using result_type = void;

        using progress_type = Progress;

        using base_type = progressive_future_base<result_type, progress_type>;

        using future_type = std::future<result_type>;


        // constructors and destructor

        progressive_future()
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type()
        {}

        progressive_future(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type(std::move(another))
        {}

        progressive_future(future_type&& future, const std::shared_ptr<detail::progress_state<progress_type>>& p_state)
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type(std::move(future), p_state)
        {}


        // functions

        progressive_future& operator=(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        result_type get()
        {
            return this->get_future().get();
        }


    };
#endif


}}


#endif
