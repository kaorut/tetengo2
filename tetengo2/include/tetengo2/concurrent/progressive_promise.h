/*! \file
    \brief The definition of tetengo2::concurrent::progressive_promise.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PROGRESSIVEPROMISE_H)
#define TETENGO2_CONCURRENT_PROGRESSIVEPROMISE_H

#include <cassert>
#include <exception>
#include <future>
#include <memory>
#include <utility>

#include <tetengo2.h>


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a progressive promise base.

        \tparam T        A type.
        \tparam Progress A progress type.
    */
    template <typename T, typename Progress>
    class progressive_promise_base
    {
    public:
        // types

        //! The result type.
        using result_type = T;

        //! The progress type.
        using progress_type = Progress;

        //! The promise type.
        using promise_type = std::promise<result_type>;

        //! The progressive future type.
        using progressive_future_type = progressive_future<result_type, progress_type>;


        // constructors and destructor

        /*!
            \brief Creates a progressive promise base.

            \param initial_progress An initial progress.
        */
        explicit progressive_promise_base(progress_type initial_progress)
        :
        m_promise(),
        m_p_state(std::make_shared<detail::progress_state<progress_type>>(std::move(initial_progress)))
        {}

        /*!
            \brief Creates a progressive promise base.

            \tparam Allocator An allocator type.

            \param initial_progress An initial progress.
            \param allocator_arg    An allocator argument.
            \param allocator        An allocator.
        */
        template <typename Allocator>
        progressive_promise_base(
            progress_type        initial_progress,
            std::allocator_arg_t allocator_arg,
            const Allocator&     allocator
        )
        :
        m_promise(std::move(allocator_arg), allocator),
        m_p_state(std::make_shared<detail::progress_state<progress_type>>(std::move(initial_progress)))
        {}

        /*!
            \brief Moves a progressive promise base.

            \param another Another progressive promise base.
        */
        progressive_promise_base(progressive_promise_base&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        m_promise(std::move(another.m_promise)),
        m_p_state(std::move(another.m_p_state))
        {}


        // functions

        /*!
            \brief Assigns another progressive promise base.

            \param another Another progressive promise base.

            \return This object.
        */
        progressive_promise_base& operator=(progressive_promise_base&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            progressive_promise_base{ std::move(another) }.swap(*this);
            return *this;
        }

        /*!
            \brief Swaps this and another promises.

            \param another Another promise.
        */
        void swap(progressive_promise_base& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            m_promise.swap(another.m_promise);
            m_p_state.swap(another.m_p_state);
        }

        /*!
            \brief Returns the progressive future.

            \return The progressive future.
        */
        progressive_future_type get_future()
        {
            return progressive_future_type{ m_promise.get_future(), m_p_state };
        }

        /*!
            \brief Sets an exception.

            \param p_exception An exception pointer.
        */
        void set_exception(std::exception_ptr p_exception)
        {
            m_promise.set_exception(std::move(p_exception));
        }

        /*!
            \brief Sets an exception when the thread finishes.

            \param p_exception An exception pointer.
        */
        void set_exception_at_thread_exit(std::exception_ptr p_exception)
        {
            m_promise.set_exception_at_thread_exit(std::move(p_exception));
        }

        /*!
            \brief Sets a progress.

            \param progress A progress.
        */
        void set_progress(progress_type progress)
        {
            assert(m_p_state);
            m_p_state->set(std::move(progress));
        }


    protected:
        // functions

        /*!
            \brief Returns the promise.

            \return The promise.
        */
        const promise_type& get_promise()
        const
        {
            return m_promise;
        }

        /*!
            \brief Returns the promise.

            \return The promise.
        */
        promise_type& get_promise()
        {
            return m_promise;
        }


    private:
        // variables

        promise_type m_promise;

        std::shared_ptr<detail::progress_state<progress_type>> m_p_state;


        // firbidden operations

        progressive_promise_base(const progressive_promise_base&) = delete;

        progressive_promise_base& operator=(const progressive_promise_base&) = delete;


    };


    /*!
        \brief The class template for a progressive promise.

        \tparam T        A type.
        \tparam Progress A progress type.
    */
    template <typename T, typename Progress>
    class progressive_promise : public progressive_promise_base<T, Progress>
    {
    public:
        // types

        //! The result type.
        using result_type = T;

        //! The progress type.
        using progress_type = Progress;

        //! The base type.
        using base_type = progressive_promise_base<result_type, progress_type>;

        //! The promise type.
        using promise_type = std::promise<result_type>;

        //! The progressive future type.
        using progressive_future_type = progressive_future<result_type, progress_type>;


        // constructors and destructor

        /*!
            \brief Creates a progressive promise.

            \param initial_progress An initial progress.
        */
        explicit progressive_promise(progress_type initial_progress)
        :
        base_type(std::move(initial_progress))
        {}

        /*!
            \brief Creates a progressive promise.

            \tparam Allocator An allocator type.

            \param initial_progress An initial progress.
            \param allocator_arg    An allocator argument.
            \param allocator        An allocator.
        */
        template <typename Allocator>
        progressive_promise(
            progress_type        initial_progress,
            std::allocator_arg_t allocator_arg,
            const Allocator&     allocator
        )
        :
        base_type(std::move(initial_progress), std::move(allocator_arg), allocator)
        {}

        /*!
            \brief Moves a progressive promise.

            \param another Another progressive promise.
        */
        progressive_promise(progressive_promise&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type(std::move(another))
        {}


        // functions

        /*!
            \brief Assigns another progressive promise.

            \param another Another progressive promise.

            \return This object.
        */
        progressive_promise& operator=(progressive_promise&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        /*!
            \brief Swaps this and another promises.

            \param another Another promise.
        */
        void swap(progressive_promise& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::swap(another);
        }

        /*!
            \brief Sets a result value.

            \param result A result value.
        */
        void set_value(const result_type& result)
        {
            this->get_promise().set_value(result);
        }

        /*!
            \brief Sets a result value.

            \param result A result value.
        */
        void set_value(result_type&& result)
        {
            this->get_promise().set_value(std::move(result));
        }

        /*!
            \brief Sets a result value when the thread finishes.

            \param result A result value.
        */
        void set_value_at_thread_exit(const result_type& result)
        {
            this->get_promise().set_value_at_thread_exit(result);
        }

        /*!
            \brief Sets a result value when the thread finishes.

            \param result A result value.
        */
        void set_value_at_thread_exit(result_type&& result)
        {
            this->get_promise().set_value_at_thread_exit(std::move(result));
        }


    };


#if !defined(DOCUMENTATION)
    template <typename R, typename Progress>
    class progressive_promise<R&, Progress> : public progressive_promise_base<R&, Progress>
    {
    public:
        // types

        using result_type = R&;

        using progress_type = Progress;

        using base_type = progressive_promise_base<result_type, progress_type>;

        using promise_type = std::promise<result_type>;

        using progressive_future_type = progressive_future<result_type, progress_type>;


        // constructors and destructor

        explicit progressive_promise(progress_type initial_progress)
        :
        base_type(std::move(initial_progress))
        {}

        template <typename Allocator>
        progressive_promise(
            progress_type        initial_progress,
            std::allocator_arg_t allocator_arg,
            const Allocator&     allocator
        )
        :
        base_type(std::move(initial_progress), std::move(allocator_arg), allocator)
        {}

        progressive_promise(progressive_promise&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type(std::move(another))
        {}


        // functions

        progressive_promise& operator=(progressive_promise&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        void swap(progressive_promise& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::swap(another);
        }

        void set_value(result_type& result)
        {
            this->get_promise().set_value(result);
        }

        void set_value_at_thread_exit(result_type& result)
        {
            this->get_promise().set_value_at_thread_exit(result);
        }


    };


    template <typename Progress>
    class progressive_promise<void, Progress> : public progressive_promise_base<void, Progress>
    {
    public:
        // types

        using result_type = void;

        using progress_type = Progress;

        using base_type = progressive_promise_base<result_type, progress_type>;

        using promise_type = std::promise<result_type>;

        using progressive_future_type = progressive_future<result_type, progress_type>;


        // constructors and destructor

        explicit progressive_promise(progress_type initial_progress)
        :
        base_type(std::move(initial_progress))
        {}

        template <typename Allocator>
        progressive_promise(
            progress_type        initial_progress,
            std::allocator_arg_t allocator_arg,
            const Allocator&     allocator
        )
        :
        base_type(std::move(initial_progress), std::move(allocator_arg), allocator)
        {}

        progressive_promise(progressive_promise&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        base_type(std::move(another))
        {}


        // functions

        progressive_promise& operator=(progressive_promise&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        void swap(progressive_promise& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            base_type::swap(another);
        }

        void set_value()
        {
            this->get_promise().set_value();
        }

        void set_value_at_thread_exit()
        {
            this->get_promise().set_value_at_thread_exit();
        }


    };
#endif


}}


namespace std
{
    /*!
        \brief Swaps promises.

        \tparam T        A type.
        \tparam Progress A progress type.

        \param one     One promise.
        \param another Another promise.
    */
    template <typename T, typename Progress>
    void swap(
        tetengo2::concurrent::progressive_promise<T, Progress>& one,
        tetengo2::concurrent::progressive_promise<T, Progress>& another
    )
    TETENGO2_STDALT_NOEXCEPT
    {
        one.swap(another);
    }


}


#endif
