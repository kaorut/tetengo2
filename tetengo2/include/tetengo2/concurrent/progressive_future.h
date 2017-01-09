/*! \file
    \brief The definition of tetengo2::concurrent::progressive_future.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PROGRESSIVEFUTURE_H)
#define TETENGO2_CONCURRENT_PROGRESSIVEFUTURE_H

#include <chrono>
#include <future>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2 { namespace concurrent
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        class progress_state : private boost::noncopyable
        {
        public:
            // types

            using progress_type = boost::rational<type_list::size_type>;


            // constructors and destructor

            explicit progress_state(progress_type initial_progress);

            ~progress_state();


            // functions

            const progress_type& get()
            const;

            void set(progress_type progress);

            bool abort_requested()
            const;

            void request_abort();


        private:
            // types

            class impl;


            // variables

            const std::unique_ptr<impl> m_p_impl;


        };


    }
#endif


    /*!
        \brief The class template for a progressive future base.

        \tparam T A type.
    */
    template <typename T>
    class progressive_future_base : private boost::noncopyable
    {
    public:
        // types

        //! The result type.
        using result_type = T;

        //! The future type.
        using future_type = std::future<result_type>;

        //! The progress type.
        using progress_type = boost::rational<type_list::size_type>;


        // constructors and destructor

        /*!
            \brief Creates an empty progressive future base.
        */
        progressive_future_base()
        noexcept
        :
        m_future(),
        m_p_state()
        {}

        /*!
            \brief Moves a progressive future base.

            \param another Another progressive future base.
        */
        progressive_future_base(progressive_future_base&& another)
        noexcept
        :
        m_future(std::move(another.m_future)),
        m_p_state(std::move(another.m_p_state))
        {}

#if !defined(DOCUMENTATION)
        progressive_future_base(
            future_type&&                                  future,
            const std::shared_ptr<detail::progress_state>& p_state
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
        noexcept
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
        const noexcept
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

        std::shared_ptr<detail::progress_state> m_p_state;

        
    };


    /*!
        \brief The class template for a progressive future.

        \tparam T A type.
    */
    template <typename T>
    class progressive_future : public progressive_future_base<T>
    {
    public:
        // types

        //! The result type.
        using result_type = T;

        //! The base type.
        using base_type = progressive_future_base<result_type>;

        //! The future type.
        using future_type = std::future<result_type>;

        //! The progress type.
        using progress_type = boost::rational<type_list::size_type>;


        // constructors and destructor

        /*!
            \brief Creates an empty progressive future.
        */
        progressive_future()
        noexcept
        :
        base_type()
        {}

        /*!
            \brief Moves a progressive future.

            \param another Another progressive future.
        */
        progressive_future(progressive_future&& another)
        noexcept
        :
        base_type(std::move(another))
        {}

#if !defined(DOCUMENTATION)
        progressive_future(future_type&& future, const std::shared_ptr<detail::progress_state>& p_state)
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
        noexcept
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
    template <typename R>
    class progressive_future<R&> : public progressive_future_base<R&>
    {
    public:
        // types

        using result_type = R&;

        using base_type = progressive_future_base<result_type>;

        using future_type = std::future<result_type>;

        using progress_type = boost::rational<type_list::size_type>;


        // constructors and destructor

        progressive_future()
        noexcept
        :
        base_type()
        {}

        progressive_future(progressive_future&& another)
        noexcept
        :
        base_type(std::move(another))
        {}

        progressive_future(future_type&& future, const std::shared_ptr<detail::progress_state>& p_state)
        :
        base_type(std::move(future), p_state)
        {}


        // functions

        progressive_future& operator=(progressive_future&& another)
        noexcept
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        result_type get()
        {
            return this->get_future().get();
        }


    };


    template <>
    class progressive_future<void> : public progressive_future_base<void>
    {
    public:
        // types

        using result_type = void;

        using base_type = progressive_future_base<result_type>;

        using future_type = std::future<result_type>;

        using progress_type = boost::rational<type_list::size_type>;


        // constructors and destructor

        progressive_future()
        noexcept
        :
        base_type()
        {}

        progressive_future(progressive_future&& another)
        noexcept
        :
        base_type(std::move(another))
        {}

        progressive_future(future_type&& future, const std::shared_ptr<detail::progress_state>& p_state)
        noexcept
        :
        base_type(std::move(future), p_state)
        {}


        // functions

        progressive_future& operator=(progressive_future&& another)
        noexcept
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        void get()
        {
            this->get_future().get();
        }


    };
#endif


}}


#endif
