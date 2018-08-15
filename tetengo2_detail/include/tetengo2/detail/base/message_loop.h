/*! \file
    \brief The definition of tetengo2::detail::base::message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_MESSAGELOOP_H)
#define TETENGO2_DETAIL_BASE_MESSAGELOOP_H

#include <memory>

#include <boost/core/noncopyable.hpp>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
}}}


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a message loop.
    */
    class message_loop : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation.
        */
        message_loop();

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~message_loop();


        // functions

        /*!
            \brief Run the message loop.

            \param window A window.

            \return The exit code.

            \throw std::system_error When a message loop error has happened.
        */
        int loop(gui::widget::abstract_window& window) const;

        /*!
            \brief Run the message loop for a dialog.

            \param dialog A dialog.

            \return The exit status code.

            \throw std::system_error When a message loop error has happened.
        */
        int dialog_loop(gui::widget::abstract_window& dialog) const;

        /*!
            \brief Breaks the message loop.

            \param exit_code An exit code.
        */
        void break_loop(int exit_code) const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual int loop_impl(gui::widget::abstract_window& window) const = 0;

        virtual int dialog_loop_impl(gui::widget::abstract_window& dialog) const = 0;

        virtual void break_loop_impl(int exit_code) const = 0;
    };
}


#endif
