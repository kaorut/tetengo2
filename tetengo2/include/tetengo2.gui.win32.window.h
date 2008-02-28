/*! \file
    \brief The definition of tetengo2::gui::win32::window.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WINDOW_H)
#define TETENGO2_GUI_WIN32_WINDOW_H

//#include <cstddef>
//#include <exception>
//#include <memory>
//#include <stdexcept>
//#include <string>

//#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
//#include <boost/signal.hpp>
//#include <boost/ptr_container/ptr_vector.hpp>

#include "tetengo2.gui.WindowObserverConcept.h"
#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a window for Win32 platforms.
 
        \tparam Handle                A handle type to the native interface.
                                      It must conform to
                                      tetengo2::gui::HandleConcept<Handle>.
        \tparam Canvas                A canvas type. It must conform to
                                      tetengo2::gui::CanvasConcept<Canvas>.
        \tparam Alert                 An alerting unary functor type. It must
                                      conform to
                                      boost::UnaryFunctionConcept<Alert, void, Handle, std::exception>.
        \tparam String                A string type. It must conform to
                                      tetengo2::StringConcept<String>.
        \tparam Encode                An encoding unary functor type. The
                                      types Encode<String, std::wstring> and
                                      Encode<std::wstring, String> must
                                      conform to
                                      boost::UnaryFunctionConcept<Encode, String, std::wstring>
                                      and
                                      boost::UnaryFunctionConcept<Encode, std::wstring, String>.
        \tparam PaintObserver         A paint observer type. It must conform
                                      to
                                      tetengo2::gui::PaintObserverConcept<PaintObserver>.
        \tparam WindowObserver        A window observer type. It must conform
                                      to
                                      tetengo2::gui::WindowObserverConcept<WindowObserver>.
   */
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename PaintObserver,
        typename WindowObserver
    >
    class window :
        public widget<
            Handle,
            Canvas,
            Alert,
            String,
            Encode,
            PaintObserver
        >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(
            WindowObserver, tetengo2::gui, WindowObserverConcept
        );


    public:
        // types

        //! The window observer type.
        typedef WindowObserver window_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a window.

            \throw std::runtime_error When a window cannot be created.
        */
        window()
        :
        m_handle(create_window()),
        m_window_observers(),
        m_window_destroyed_handler()
        {
            widget::associate_to_native_window_system(this);
        }

        /*!
            \brief Destroys the window.
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

        /*!
            \brief Adds a window observer.

            \param p_window_observer An auto pointer to a window observer.
        */
        void add_window_observer(
            std::auto_ptr<window_observer_type> p_window_observer
        )
        {
            m_window_destroyed_handler.connect(
                boost::bind(
                    &typename window_observer_type::destroyed,
                    p_window_observer.get()
                )
            );

            m_window_observers.push_back(p_window_observer);
        }


    protected:
        // functions

        // The document will be derived from
        // tetengo2::gui::win32::widget::window_procedure.
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
                    m_window_destroyed_handler();
                    return 0;
                }
            case WM_LBUTTONUP:
                // if (condition)
                {
                    throw std::runtime_error("マウスがクリックされた。");
                }
            }
            return this->widget::window_procedure(uMsg, wParam, lParam);
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
                throw std::runtime_error("Can't create a window!");

            return handle;
        }

        static ::ATOM register_window_class(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = widget::p_static_window_procedure();
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
                throw std::runtime_error("Can't register a window class!");

            return atom;
        }


        // variables

        const handle_type m_handle;

        boost::ptr_vector<window_observer_type> m_window_observers;

        boost::signal<void ()> m_window_destroyed_handler;


    };


}}}

#endif
