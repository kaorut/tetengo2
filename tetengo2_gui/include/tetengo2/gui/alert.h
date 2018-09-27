/*! \file
    \brief The definition of tetengo2::gui::alert.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_ALERT_H)
#define TETENGO2_GUI_ALERT_H

#include <exception>
#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/alert.h>

namespace boost {
    class exception;
}


namespace tetengo2::gui {
    /*!
        \brief The class for an alert.
    */
    class alert : private boost::noncopyable
    {
    public:
        // types

        //! The widget handle type.
        using widget_handle_type = detail::base::alert::widget_handle_type;


        // constructors and destructor

        /*!
            \brief Creates an alert.

            \param widget_handle A widget handle.
        */
        explicit alert(widget_handle_type widget_handle);

        /*!
            \brief Creates an alert.
        */
        alert();

        /*!
            \brief Destroys the alert.
        */
        ~alert();


        // functions

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(const boost::exception& exception) const;

        /*!
            \brief Alerts a fatal error.

            \param exception An exception.
        */
        void operator()(const std::exception& exception = std::runtime_error("Unknown Error!")) const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
