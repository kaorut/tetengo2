/*! \file
    \brief The definition of tetengo2::concurrent::progressive_promise.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PROGRESSIVEPROMISE_H)
#define TETENGO2_CONCURRENT_PROGRESSIVEPROMISE_H

#include <cassert>
#include <exception>
#include <future>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>
#include <boost/rational.hpp>

#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace concurrent
{
    /*!
        \brief The class template for a progressive promise base.

        \tparam T  A type.
    */
    template <typename T>
    class progressive_promise_base : private boost::noncopyable
    {
    public:
        // types

        //! The result type.
        using result_type = T;

        //! The progress type.
        using progress_type = boost::rational<type_list::size_type>;

        //! The promise type.
        using promise_type = std::promise<result_type>;

        //! The progressive future type.
        using progressive_future_type = progressive_future<result_type>;


        // constructors and destructor

        /*!
            \brief Creates a progressive promise base.

            \param initial_progress An initial progress.
        */
        explicit progressive_promise_base(progress_type initial_progress)
        :
        m_promise(),
        m_p_state(std::make_shared<detail::progress_state>(std::move(initial_progress)))
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
        m_p_state(std::make_shared<detail::progress_state>(std::move(initial_progress)))
        {}

        /*!
            \brief Moves a progressive promise base.

            \param another Another progressive promise base.
        */
        progressive_promise_base(progressive_promise_base&& another)
        noexcept
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
        noexcept
        {
            progressive_promise_base{ std::move(another) }.swap(*this);
            return *this;
        }

        /*!
            \brief Swaps this and another promises.

            \param another Another promise.
        */
        void swap(progressive_promise_base& another)
        noexcept
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

        /*!
            \brief Checks whether a task abort is requested.

            \retval true  When a task abort is requested.
            \retval false Otherwise.
        */
        bool abort_requested()
        const
        {
            assert(m_p_state);
            return m_p_state->abort_requested();
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

        std::shared_ptr<detail::progress_state> m_p_state;


    };


    /*!
        \brief The class template for a progressive promise.

        \tparam T A type.
    */
    template <typename T>
    class progressive_promise : public progressive_promise_base<T>
    {
    public:
        // types

        //! The result type.
        using result_type = T;

        //! The progress type.
        using progress_type = boost::rational<type_list::size_type>;

        //! The base type.
        using base_type = progressive_promise_base<result_type>;

        //! The promise type.
        using promise_type = std::promise<result_type>;

        //! The progressive future type.
        using progressive_future_type = progressive_future<result_type>;


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
        noexcept
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
        noexcept
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        /*!
            \brief Swaps this and another promises.

            \param another Another promise.
        */
        void swap(progressive_promise& another)
        noexcept
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

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_CLANG >= BOOST_VERSION_NUMBER(3, 5, 0) && BOOST_COMP_CLANG < BOOST_VERSION_NUMBER(3, 6, 0)) \
)
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
#endif


    };


#if !defined(DOCUMENTATION)
    template <typename R>
    class progressive_promise<R&> : public progressive_promise_base<R&>
    {
    public:
        // types

        using result_type = R&;

        using progress_type = boost::rational<type_list::size_type>;

        using base_type = progressive_promise_base<result_type>;

        using promise_type = std::promise<result_type>;

        using progressive_future_type = progressive_future<result_type>;


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
        noexcept
        :
        base_type(std::move(another))
        {}


        // functions

        progressive_promise& operator=(progressive_promise&& another)
        noexcept
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        void swap(progressive_promise& another)
        noexcept
        {
            base_type::swap(another);
        }

        void set_value(result_type& result)
        {
            this->get_promise().set_value(result);
        }

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_CLANG >= BOOST_VERSION_NUMBER(3, 5, 0) && BOOST_COMP_CLANG < BOOST_VERSION_NUMBER(3, 6, 0)) \
)
        void set_value_at_thread_exit(result_type& result)
        {
            this->get_promise().set_value_at_thread_exit(result);
        }
#endif


    };


    template <>
    class progressive_promise<void> : public progressive_promise_base<void>
    {
    public:
        // types

        using result_type = void;

        using progress_type = boost::rational<type_list::size_type>;

        using base_type = progressive_promise_base<result_type>;

        using promise_type = std::promise<result_type>;

        using progressive_future_type = progressive_future<result_type>;


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
        noexcept
        :
        base_type(std::move(another))
        {}


        // functions

        progressive_promise& operator=(progressive_promise&& another)
        noexcept
        {
            base_type::operator=(std::move(another));
            return *this;
        }

        void swap(progressive_promise& another)
        noexcept
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

        \tparam T A type.

        \param one     One promise.
        \param another Another promise.
    */
    template <typename T>
    void swap(
        tetengo2::concurrent::progressive_promise<T>& one,
        tetengo2::concurrent::progressive_promise<T>& another
    )
    noexcept
    {
        one.swap(another);
    }


}


#endif
