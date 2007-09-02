/*! \file
    \brief The definition of tetengo2::gui::win32::window_message_receiver.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WINDOWMESSAGERECEIVER_H)
#define TETENGO2_GUI_WIN32_WINDOWMESSAGERECEIVER_H

#include <memory>

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.gui.window_observer.h"
#include "tetengo2.gui.win32.widget_message_receiver.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a window message receiver for
        Win32 platforms.

        \param Widget                A widget type. It must confirm to
                                     tetengo2::gui::concepts::WidgetConcept.
        \param StaticWindowProcedure A static window procedure type. It must
                                     conform to
                                     tetengo2::gui::concepts::StaticWindowProcedureConcept.
        \param Alerter               An alerter type. It must conform to
                                     tetengo2::gui::concepts::AlerterConcept.
    */
    template <
        typename Widget,
        typename StaticWindowProcedure,
        typename Alerter
    >
    class window_message_receiver :
        public widget_message_receiver<Widget, StaticWindowProcedure, Alerter>
    {
    public:
        // types

        //! The window observer type.
        typedef window_observer window_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a window message receiver object.

            \param p_widget A pointer to a widget.
        */
        window_message_receiver(widget_type* const p_widget)
        :
        widget_message_receiver(p_widget)
        {}

        /*!
            \brief Destroys the window message receiver object.
        */
        virtual ~window_message_receiver()
        throw ()
        {}


        // functions

        /*!
            \brief Adds a window observer.

            \param p_window_observer An auto pointer to a window observer.
        */
        void add_window_observer(
            std::auto_ptr<window_observer_type> p_window_observer
        )
        {
            window_destroyed_handler.connect(
                boost::bind(
                    &typename window_observer_type::destroyed,
                    p_window_observer.get()
                )
            );

            window_observers.push_back(p_window_observer);
        }


    protected:
        // functions

        virtual ::LRESULT window_procedure(
            const ::UINT   uMsg,
            const ::WPARAM wParam,
            const ::LPARAM lParam
        )
        {
            switch (uMsg)
            {
            case WM_DESTROY:
                {
                    window_destroyed_handler();
                    return 0;
                }
            case WM_LBUTTONUP:
                // if (condition)
                {
                    throw std::runtime_error("Mouse Clicked");
                }
            }
            return this->widget_message_receiver::window_procedure(
                uMsg, wParam, lParam
            );
        }


    private:
        // variables

        boost::ptr_vector<window_observer_type> window_observers;

        boost::signal<void ()> window_destroyed_handler;


    };
}}}

#endif
