/*! \file
    \brief The definition of tetengo2::gui::win32::widget.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WIDGET_H)
#define TETENGO2_GUI_WIN32_WIDGET_H

#include <exception>
#include <memory>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>

#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a GUI widget for Win32 platforms.

        \param Handle          A handle type to the native interface. It must
                               conform to
                               tetengo2::gui::concepts::HandleConcept.
        \param MessageReceiver A message receiver type template. The type
                               MessageReceiver<widget> must conform to
                               tetengo2::gui::MessageReceiverConcept.
        \param Alerter         An alerter type. It must conform to
                               tetengo2::gui::concepts::AlerterConcept.
        \param Canvas          A canvas type. It must conform to
                               tetengo2::gui::concepts::CanvasConcept.
    */
    template <
        typename Handle,
        template <typename Widget, typename Alerter>
        class    MessageReceiver,
        typename Alerter,
        typename Canvas
    >
    class widget : private boost::noncopyable
    {
    public:
        // types

        //! The handle type.
        typedef Handle handle_type;

        //! The alerter type.
        typedef Alerter alerter_type;

        //! The message receiver type.
        typedef MessageReceiver<widget, alerter_type> message_receiver_type;

        //! The canvas type.
        typedef Canvas canvas_type;


        // constructors and destructor

        /*!
            \brief Creates a widget object.
        */
        widget()
        :
        m_p_message_receiver()
        {}

        /*!
            \brief Destroys the widget object.
        */
        virtual ~widget()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the handle.
            
            \return The handle.
        */
        virtual handle_type handle()
        const = 0;

        /*!
            \brief Returns the message receiver.

            \return The pointer to the message receiver.
        */
        message_receiver_type* message_receiver()
        const
        {
            if (m_p_message_receiver.get() == NULL)
                throw std::logic_error("Message receiver not set!");

            return m_p_message_receiver.get();
        }

        /*!
            \brief Sets the visible status.

            \param visible A visible status.
        */
        virtual void set_visible(const bool visible)
        {
            ::ShowWindow(this->handle(), visible ? SW_SHOW : SW_HIDE);
        }

        /*!
            \brief Returns the visible status.

            \param The visible status.
        */
        virtual bool is_visible()
        const
        {
            return ::IsWindowVisible(this->handle()) == TRUE;
        }

        /*!
            \brief Sets the text.

            \param text A text.
        */
        virtual void set_text(const std::wstring& text)
        {
            if (::SetWindowText(this->handle(), text.c_str()) == 0)
                throw std::runtime_error("Can't set text!");
        }

        /*!
            \brief Retuns the text.

            \return The text.
        */
        virtual const std::wstring text()
        const
        {
            const int length = ::GetWindowTextLengthW(this->handle());
            if (length == 0) return std::wstring();

            const boost::scoped_array<wchar_t> p_text(
                new wchar_t[length + 1]
            );
            ::GetWindowTextW(this->handle(), p_text.get(), length + 1);

            return std::wstring(p_text.get());
        }


    protected:
        // functions

        /*!
            \brief Sets the message receiver.

            \param p_message_receiver An auto pointer to a message receiver.
        */
        void set_message_receiver(
            std::auto_ptr<message_receiver_type> p_message_receiver
        )
        {
            m_p_message_receiver.reset(p_message_receiver.release());
        }


    private:
        // variables

        boost::scoped_ptr<message_receiver_type> m_p_message_receiver;

    };
}}}

#endif
