/*! \file
    \brief The definition of tetengo2::detail::base::timer.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_TIMER_H)
#define TETENGO2_DETAIL_BASE_TIMER_H

#include <memory>

#include <boost/core/noncopyable.hpp>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a timer.
    */
    class timer : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Destroys the detail implementation of a timer.
        */
        virtual ~timer();


        // functions

        /*!
            \brief Returns the stopped status.

            \return The stopped status.
        */
        bool stopped() const;

        /*!
            \brief Stops the timer.
        */
        void stop();


    protected:
        /*!
            \brief Creates a detail implementation of a timer.
        */
        timer();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool stopped_impl() const = 0;

        virtual void stop_impl() = 0;
    };
}


#endif
