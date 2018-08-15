/*! \file
    \brief The definition of tetengo2::detail::stub::message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MESSAGELOOP_H)
#define TETENGO2_DETAIL_STUB_MESSAGELOOP_H

#include <memory>

#include <tetengo2/detail/base/message_loop.h>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
}}}


namespace tetengo2::detail::stub {
    /*!
        \brief The class for a detail implementation of a message loop.
    */
    class message_loop : public base::message_loop
    {
    public:
        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const message_loop& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~message_loop();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        message_loop();


        // virtual functions

        virtual int loop_impl(gui::widget::abstract_window& window) const override;

        virtual int dialog_loop_impl(gui::widget::abstract_window& dialog) const override;

        virtual void break_loop_impl(int exit_code) const override;
    };


#if 0
    /*!
        \brief The class for a detail implementation of a message loop.
    */
    class message_loop : private boost::noncopyable
    {
    public:
        // static functions

        /*!
            \brief Run the message loop.

            \tparam AbstractWindow An abstract window type.

            \param window A window.

            \return The exit code.

            \throw std::system_error When a message loop error has happened.
        */
        template <typename AbstractWindow>
        static int loop(TETENGO2_STDALT_MAYBE_UNUSED AbstractWindow& window)
        {
            return 0;
        }

        /*!
            \brief Run the message loop for a dialog.

            \tparam AbstractWindow An abstract window type.

            \param dialog A dialog.

            \return The exit status code.

            \throw std::system_error When a message loop error has happened.
        */
        template <typename AbstractWindow>
        static int dialog_loop(TETENGO2_STDALT_MAYBE_UNUSED AbstractWindow& dialog)
        {
            return 0;
        }

        /*!
            \brief Breaks the message loop.

            \param exit_code An exit code.
        */
        static void break_loop(TETENGO2_STDALT_MAYBE_UNUSED const int exit_code) {}


    private:
        // forbidden operations

        message_loop() = delete;
    };
#endif
}


#endif
