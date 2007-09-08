/*! \file
    \brief The definition of tetengo2::gui::win32::window.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WINDOW_H)
#define TETENGO2_GUI_WIN32_WINDOW_H

#include <memory>
#include <stdexcept>

#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a window for Win32 platforms.
 
        \param Handle                A handle type to the native interface. It
                                     must conform to
                                     tetengo2::gui::concept::HandleConcept.
        \param MessageReceiver       A message receiver type template. The
                                     type
                                     MessageReceiver<Widget, StaticWindowProcedure, Alerter>
                                     must conform to
                                     tetengo2::gui::MessageReceiverConcept.
        \param StaticWindowProcedure A static window procedure type. It must
                                     conform to
                                     tetengo2::gui::concept::StaticWindowProcedureConcept.
        \param Alerter               An alert type. It must conform to
                                     tetengo2::gui::concept::AlerterConcept.
        \param Canvas                A canvas type. It must conform to
                                     tetengo2::gui::concept::CanvasConcept.
        \param String                A string type. It must conform to
                                     tetengo2::concept::StringConcept.
   */
    template <
        typename Handle,
        template <
            typename Window, typename StaticWindowProcedure, typename Alerter
        >
        class    MessageReceiver,
        typename StaticWindowProcedure,
        typename Alerter,
        typename Canvas,
        typename String
    >
    class window :
        public widget<
            Handle,
            MessageReceiver,
            StaticWindowProcedure,
            Alerter,
            Canvas,
            String
        >
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a window object.
        */
        window()
        :
        m_handle(create_window())
        {
            set_message_receiver(
                std::auto_ptr<message_receiver_type>(
                    new message_receiver_type(this)
                )
            );
        }

        /*!
            \brief Destroys the window object.
        */
        virtual ~window()
        throw ()
        {}


        // functions

        // The document will be derived from tetengo2::gui::win32::widget.
        virtual handle_type handle()
        const
        {
            return m_handle;
        }


    private:
        // static functions

        static handle_type create_window()
        {
            const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
            if (instance_handle == NULL)
                throw std::runtime_error("Can't get the instance handle!");

            const ::ATOM atom = register_window_class(instance_handle);

            const handle_type handle = ::CreateWindowExW(
                0,
                reinterpret_cast<::LPCWSTR>(atom),
                L"tetengo2 main widget",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                HWND_DESKTOP,
                NULL,
                instance_handle,
                NULL
            );
            if (handle == NULL)
                throw std::runtime_error("Can't create widget!");

            return handle;
        }

        static ::ATOM register_window_class(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc =
                message_receiver_type::p_static_window_procedure();
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = sizeof(widget*);
            window_class.hInstance = instance_handle;
            window_class.hIcon = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OIC_WINLOGO),
                    IMAGE_ICON,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hIconSm = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OIC_WINLOGO),
                    IMAGE_ICON,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hCursor = reinterpret_cast< ::HICON>(
                ::LoadImageW(
                    0,
                    MAKEINTRESOURCEW(OCR_NORMAL),
                    IMAGE_CURSOR,
                    0,
                    0,
                    LR_DEFAULTSIZE | LR_SHARED | LR_VGACOLOR
                )
            );
            window_class.hbrBackground = reinterpret_cast< ::HBRUSH>(
                ::GetSysColorBrush(COLOR_3DFACE)
            );
            window_class.lpszMenuName = NULL;
            window_class.lpszClassName = L"tetengo2::gui::win32::widget";

            const ::ATOM atom = ::RegisterClassExW(&window_class);
            if (atom == NULL)
                throw std::runtime_error("Can't register widget class!");

            return atom;
        }


        // variables

        const handle_type m_handle;


    };
}}}

#endif
