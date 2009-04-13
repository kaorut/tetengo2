/*! \file
    \brief The definition of tetengo2::gui::win32::window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WINDOW_H)
#define TETENGO2_GUI_WIN32_WINDOW_H

//#include <cstddef>
//#include <stdexcept>

//#include <boost/concept_check.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.AbstractWindow.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a window for Win32 platforms.
 
        \tparam AbstractWindow An abstract window type. It must conform to
                               concept_tetengo2::gui::AbstractWindow<AbstractWindow>.
   */
    template <typename AbstractWindow>
    class window : public AbstractWindow
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::AbstractWindow<AbstractWindow>
        ));


    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The handle type.
        typedef typename abstract_window_type::handle_type handle_type;

        //! The canvas type.
        typedef typename abstract_window_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename abstract_window_type::alert_type alert_type;

        //! The difference type.
        typedef
            typename abstract_window_type::difference_type difference_type;

        //! The size type.
        typedef typename abstract_window_type::size_type size_type;

        //! The position type.
        typedef typename abstract_window_type::position_type position_type;

        //! The dimension type.
        typedef typename abstract_window_type::dimension_type dimension_type;

        //! The string type.
        typedef typename abstract_window_type::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename abstract_window_type::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename abstract_window_type::encode_to_native_type
            encode_to_native_type;

        //! The font type.
        typedef typename abstract_window_type::font_type font_type;

        //! The child type.
        typedef typename abstract_window_type::child_type child_type;

        //! The paint observer type.
        typedef
            typename abstract_window_type::paint_observer_type
            paint_observer_type;

        //! The mouse observer type.
        typedef
            typename abstract_window_type::mouse_observer_type
            mouse_observer_type;

        //! The main menu type.
        typedef typename abstract_window_type::main_menu_type main_menu_type;

        //! The window observer type.
        typedef
            typename abstract_window_type::window_observer_type
            window_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a top level window.

            \throw std::runtime_error When a window cannot be created.
        */
        window()
        :
        abstract_window_type(),
        m_handle(create_window(NULL))
        {
            initialize(this);
        }

        /*!
            \brief Creates a owned window.

            \param parent A parent window.

            \throw std::runtime_error When a window cannot be created.
        */
        window(const abstract_window_type& parent)
        :
        abstract_window_type(parent),
        m_handle(create_window(&parent))
        {
            initialize(this);
        }

        /*!
            \brief Destroys the window.
        */
        virtual ~window()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the handle.
            
            \return The handle.
        */
        virtual handle_type handle()
        const
        {
            return m_handle;
        }


    protected:
        // functions

        /*!
            \brief Dispatches the window messages.

            \param uMsg                       A message.
            \param wParam                     A word-sized parameter.
            \param lParam                     A long-sized parameter.
            \param p_default_window_procedure A pointer to a default window
                                              procedure.

            \return The result code.
        */
        virtual ::LRESULT window_procedure(
            const ::UINT    uMsg,
            const ::WPARAM  wParam,
            const ::LPARAM  lParam,
            const ::WNDPROC p_default_window_procedure
        )
        {
            return this->abstract_window_type::window_procedure(
                uMsg, wParam, lParam, p_default_window_procedure
            );
        }


    private:
        // static functions

        static const string_type& window_class_name()
        {
            static const string_type singleton =
                L"tetengo2::gui::win32::window";
            return singleton;
        }

        static handle_type create_window(
            const abstract_window_type* const p_parent
        )
        {
            const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
            if (instance_handle == NULL)
                throw std::runtime_error("Can't get the instance handle!");

            if (
                !window_class_is_registered(
                    window_class_name(), instance_handle
                )
            )
            {
                register_window_class(instance_handle);
            }

            const handle_type handle = ::CreateWindowExW(
                WS_EX_ACCEPTFILES | WS_EX_APPWINDOW,
                window_class_name().c_str(),
                window_class_name().c_str(),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                p_parent == NULL ? HWND_DESKTOP : p_parent->handle(),
                NULL,
                instance_handle,
                NULL
            );
            if (handle == NULL)
                throw std::runtime_error("Can't create a window!");

            return handle;
        }

        static void register_window_class(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = abstract_window_type::p_static_window_procedure();
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = 0;
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
            window_class.lpszClassName = window_class_name().c_str();

            const ::ATOM atom = ::RegisterClassExW(&window_class);
            if (atom == NULL)
                throw std::runtime_error("Can't register a window class!");
        }


        // variables

        const handle_type m_handle;


    };


}}}

#endif
