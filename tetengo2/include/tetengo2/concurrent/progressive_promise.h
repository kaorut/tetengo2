/*! \file
    \brief The definition of tetengo2::concurrent::progressive_promise.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PROGRESSIVEPROMISE_H)
#define TETENGO2_CONCURRENT_PROGRESSIVEPROMISE_H

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
        */
        progressive_promise_base()
        :
        m_promise()
        {}

        /*!
            \brief Creates a progressive promise base.

            \tparam Allocator An allocator type.

            \param allocator_arg An allocator argument.
            \param allocator     An allocator.
        */
        template <typename Allocator>
        progressive_promise_base(std::allocator_arg_t allocator_arg, const Allocator& allocator)
        :
        m_promise(std::move(allocator_arg), allocator)
        {}

        /*!
            \brief Moves a progressive promise base.

            \param another Another progressive promise base.
        */
        progressive_promise_base(progressive_promise_base&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        m_promise(std::move(another.m_promise))
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
            m_promise = std::move(another.m_promise);

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
        }

        /*
            \brief Returns the progressive future.

            \return The progressive future.
        */
        progressive_future_type get_future()
        {
            return progressive_future_type{};
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


    private:
        // variables

        promise_type m_promise;


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
        */
        progressive_promise()
        :
        base_type()
        {}

        /*!
            \brief Creates a progressive promise.

            \tparam Allocator An allocator type.

            \param allocator_arg An allocator argument.
            \param allocator     An allocator.
        */
        template <typename Allocator>
        progressive_promise(std::allocator_arg_t allocator_arg, const Allocator& allocator)
        :
        base_type(std::move(allocator_arg), allocator)
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
            base_type::set_value(result);
        }

        /*!
            \brief Sets a result value.

            \param result A result value.
        */
        void set_value(result_type&& result)
        {
            base_type::set_value(std::move(result));
        }

        /*!
            \brief Sets a result value when the thread finishes.

            \param result A result value.
        */
        void set_value_at_thread_exit(const result_type& result)
        {
            base_type::set_value_at_thread_exit(result);
        }

        /*!
            \brief Sets a result value when the thread finishes.

            \param result A result value.
        */
        void set_value_at_thread_exit(result_type&& result)
        {
            base_type::set_value_at_thread_exit(std::move(result));
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

        progressive_promise()
        :
        base_type()
        {}

        template <typename Allocator>
        progressive_promise(std::allocator_arg_t allocator_arg, const Allocator& allocator)
        :
        base_type(std::move(allocator_arg), allocator)
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
            base_type::set_value(result);
        }

        void set_value_at_thread_exit(result_type& result)
        {
            base_type::set_value_at_thread_exit(result);
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

        progressive_promise()
        :
        base_type()
        {}

        template <typename Allocator>
        progressive_promise(std::allocator_arg_t allocator_arg, const Allocator& allocator)
        :
        base_type(std::move(allocator_arg), allocator)
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
            base_type::set_value();
        }

        void set_value_at_thread_exit()
        {
            base_type::set_value_at_thread_exit();
        }


    };
#endif


}}


#endif
