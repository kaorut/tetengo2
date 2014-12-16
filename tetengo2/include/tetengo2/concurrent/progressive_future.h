/*! \file
    \brief The definition of tetengo2::concurrent::progressive_future.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_CONCURRENT_PROGRESSIVEFUTURE_H)
#define TETENGO2_CONCURRENT_PROGRESSIVEFUTURE_H

#include <chrono>
#include <future>
#include <utility>

#include <tetengo2.h>


namespace tetengo2 { namespace concurrent
{
#if !defined(DOCUMENTATION)
    namespace detail
    {


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
        m_future()
        {}

        /*!
            \brief Moves a progressive future base.

            \param another Another progressive future base.
        */
        progressive_future_base(progressive_future_base&& another)
        TETENGO2_STDALT_NOEXCEPT
        :
        m_future(std::move(another.m_future))
        {}


        // functions

        /*!
            \brief Assigns another progressive future base.

            \param another Another progressive future base.

            \return This object.
        */
        progressive_future_base& operator=(progressive_future_base&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
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
            return m_future.valid();
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
            m_future.wait_for(rel_time);
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
            m_future.wait_until(abs_time);
        }



    protected:
        /*!
            \brief Returns the result.

            This function is for the derived classes of this class.

            \return The result.
        */
        result_type get_impl()
        {
            return m_future.get();
        }


    private:
        // variables

        future_type m_future;

        
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


        // functions

        /*!
            \brief Assigns another progressive future.

            \param another Another progressive future.

            \return This object.
        */
        progressive_future& operator=(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            return base_type::operator=(another);
        }

        /*!
            \brief Returns the result.

            \return The result.
        */
        result_type get()
        {
            return get_impl();
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


        // functions

        progressive_future& operator=(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            return base_type::operator=(another);
        }

        result_type get()
        {
            return get_impl();
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


        // functions

        progressive_future& operator=(progressive_future&& another)
        TETENGO2_STDALT_NOEXCEPT
        {
            return base_type::operator=(another);
        }

        result_type get()
        {
            get_impl();
        }


    };
#endif


}}


#endif
