/*! \file
    \brief The definition of tetengo2::detail::windows::message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGELOOP_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGELOOP_H

#include <memory>

#include <tetengo2/detail/base/message_loop.h>

namespace tetengo2 { namespace gui { namespace widget {
    class abstract_window;
}}}


namespace tetengo2::detail::windows {
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
}


#endif
