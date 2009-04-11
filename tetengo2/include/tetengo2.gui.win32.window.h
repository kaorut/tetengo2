/*! \file
    \brief The definition of tetengo2::gui::win32::window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WINDOW_H)
#define TETENGO2_GUI_WIN32_WINDOW_H

#include <cassert>
//#include <cstddef>
//#include <memory>
//#include <stdexcept>

//#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
#include <boost/signal.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.MainMenu.h"
#include "concept_tetengo2.gui.WindowObserver.h"
#include "concept_tetengo2.gui.Widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a window for Win32 platforms.
 
        \tparam Widget         A widget type. It must conform to
                               concept_tetengo2::gui::Widget<Widget>.
        \tparam MainMenu       A main menu type. It must conform to
                               concept_tetengo2::gui::MainMenu<MainMenu>.
        \tparam WindowObserver A window observer type. It must conform to
                               concept_tetengo2::gui::WindowObserver<WindowObserver>.
   */
    template <typename Widget, typename MainMenu, typename WindowObserver>
    class window : public Widget
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Widget<Widget>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MainMenu<MainMenu>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::WindowObserver<WindowObserver>
        ));


    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! The handle type.
        typedef typename widget_type::handle_type handle_type;

        //! The canvas type.
        typedef typename widget_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename widget_type::alert_type alert_type;

        //! The difference type.
        typedef typename widget_type::difference_type difference_type;

        //! The size type.
        typedef typename widget_type::size_type size_type;

        //! The position type.
        typedef typename widget_type::position_type position_type;

        //! The dimension type.
        typedef typename widget_type::dimension_type dimension_type;

        //! The string type.
        typedef typename widget_type::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        //! The font type.
        typedef typename widget_type::font_type font_type;

        //! The child type.
        typedef typename widget_type::child_type child_type;

        //! The paint observer type.
        typedef
            typename widget_type::paint_observer_type paint_observer_type;

        //! The main menu type.
        typedef MainMenu main_menu_type;

        //! The window observer type.
        typedef WindowObserver window_observer_type;

        //! The style type.
        enum style_type
        {
            style_flat,     //!< A flat window_style.
            style_frame,    //!< A frame window style.
            style_dialog,   //!< A dialog box style.
        };


        // constructors and destructor

        /*!
            \brief Creates a top level window.

            \param style    A style.

            \throw std::runtime_error When a window cannot be created.
        */
        window(const style_type style = style_frame)
        :
        widget_type(),
        m_handle(create_window(style, NULL)),
        m_p_main_menu(),
        m_window_observers(),
        m_window_destroyed_handler()
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

        /*!
            \brief Activates the window.

            \throw std::runtime_error When the window is already destroyed.
        */
        virtual void activate()
        {
            check_destroyed();

            ::BringWindowToTop(this->handle());
        }

        /*!
            \brief Returns true when the window has a main menu.

            \retval true  When the window has a main menu.
            \retval false Otherwise.

            \throw std::runtime_error When the window is already destroyed.
        */
        virtual bool has_main_menu()
        const
        {
            check_destroyed();

            return m_p_main_menu.get() != NULL;
        }

        /*!
            \brief Returns the main menu.

            When the window does not have a main menu, the result is
            undefined.

            \return The main menu.

            \throw std::runtime_error When the window is already destroyed.
        */
        virtual main_menu_type& main_menu()
        {
            check_destroyed();

            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Returns the main menu.

            When the window does not have a main menu, the result is
            undefined.

            \return The main menu.

            \throw std::runtime_error When the window is already destroyed.
        */
        virtual const main_menu_type& main_menu()
        const
        {
            check_destroyed();

            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Sets a main menu.

            When p_main_menu is NULL, the currently associated main menu is
            destroyed.

            \param p_main_menu An auto pointer to a main menu.

            \throw std::runtime_error When the window is already destroyed.
        */
        virtual void set_main_menu(std::auto_ptr<main_menu_type> p_main_menu)
        {
            check_destroyed();

            if (::SetMenu(m_handle, NULL) == 0)
                throw std::runtime_error("Can't unset the main menu.");
            
            m_p_main_menu = p_main_menu;
            
            if (m_p_main_menu.get() != NULL)
            {
                if (::SetMenu(m_handle, m_p_main_menu->handle()) == 0)
                    throw std::runtime_error("Can't set a main menu.");
                if (::DrawMenuBar(m_handle) == 0)
                    throw std::runtime_error("Can't draw the main menu.");
            }
        }

        /*!
            \brief Adds a window observer.

            \param p_window_observer An auto pointer to a window observer.

            \throw std::runtime_error When the window is already destroyed.
        */
        virtual void add_window_observer(
            std::auto_ptr<window_observer_type> p_window_observer
        )
        {
            check_destroyed();

            m_window_destroyed_handler.connect(
                boost::bind(
                    &typename window_observer_type::destroyed,
                    p_window_observer.get()
                )
            );

            m_window_observers.push_back(p_window_observer);
        }

        /*!
            \brief Closes the window.

            \throw std::runtime_error When the window is already destroyed.
        */
        virtual void close()
        {
            check_destroyed();

            const ::BOOL result = ::PostMessageW(m_handle, WM_CLOSE, 0, 0);
            if (result == 0)
                throw std::runtime_error("Can't close the window.");
        }


    protected:
        // constructors

        /*!
            \brief Creates a owned window.

            \param parent A parent window.
            \param style  A style.

            \throw std::runtime_error When a window cannot be created.
        */
        window(const window& parent, const style_type style = style_frame)
        :
        widget_type(parent),
        m_handle(create_window(style, &parent)),
        m_p_main_menu(),
        m_window_observers(),
        m_window_destroyed_handler()
        {
            initialize(this);
        }


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
            switch (uMsg)
            {
            case WM_COMMAND:
                {
                    const ::WORD source = HIWORD(wParam);
                    const ::WORD id = LOWORD(wParam);
                    if (source == 0)
                    {
                        if (!has_main_menu()) break;

                        typename main_menu_type::menu_item_type* const
                        p_found = main_menu().find_by_id(id);
                        if (p_found == NULL) break;
                        p_found->select();
                        return 0;
                    }

                    break;
                }
            case WM_INITMENUPOPUP:
                {
                    if (!has_main_menu()) break;

                    const ::HMENU handle = reinterpret_cast< ::HMENU>(wParam);
                    typename main_menu_type::menu_item_type* const
                    p_found = main_menu().find_by_handle(handle);
                    if (p_found == NULL) break;
                    p_found->select();
                    return 0;
                }
            case WM_DESTROY:
                {
                    if (m_window_observers.empty()) break;

                    m_window_destroyed_handler();
                    break;
                }
            }
            return this->widget_type::window_procedure(
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
            const style_type    style,
            const window* const p_parent
        )
        {
            const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
            if (instance_handle == NULL)
                throw std::runtime_error("Can't get the instance handle!");

            if (!window_class_is_registered(instance_handle))
                register_window_class(instance_handle);

            const handle_type handle = ::CreateWindowExW(
                create_window_exstyle(style),
                window_class_name().c_str(),
                window_class_name().c_str(),
                create_window_style(style),
                style == style_frame ? CW_USEDEFAULT : 0,
                style == style_frame ? CW_USEDEFAULT : 0,
                style == style_frame ? CW_USEDEFAULT : 128,
                style == style_frame ? CW_USEDEFAULT : 128,
                p_parent == NULL ? HWND_DESKTOP : p_parent->handle(),
                NULL,
                instance_handle,
                NULL
            );
            if (handle == NULL)
                throw std::runtime_error("Can't create a window!");

            if (style == style_dialog)
                delete_system_menu_items(handle);

            return handle;
        }

        static bool window_class_is_registered(
            const ::HINSTANCE instance_handle
        )
        {
            ::WNDCLASSEXW window_class;
            const ::BOOL result = ::GetClassInfoExW(
                instance_handle, window_class_name().c_str(), &window_class
            );

            return result != 0;
        }

        static void register_window_class(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = widget_type::p_static_window_procedure();
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

        static ::DWORD create_window_exstyle(const style_type style)
        {
            switch (style)
            {
            case style_frame:
                return WS_EX_ACCEPTFILES | WS_EX_APPWINDOW;
            case style_dialog:
                return WS_EX_CONTEXTHELP | WS_EX_DLGMODALFRAME;
            default:
                throw std::invalid_argument("Invalid style.");
            }
        }

        static ::DWORD create_window_style(const style_type style)
        {
            switch (style)
            {
            case style_frame:
                return WS_OVERLAPPEDWINDOW;
            case style_dialog:
                return WS_POPUPWINDOW | WS_CAPTION;
            default:
                throw std::invalid_argument("Invalid style.");
            }
        }

        static void delete_system_menu_items(const ::HWND window_handle)
        {
            const ::HMENU menu_handle = ::GetSystemMenu(window_handle, FALSE);
            if (menu_handle == NULL) return;

            if (::DeleteMenu(menu_handle, SC_SIZE, MF_BYCOMMAND) == 0)
                throw std::runtime_error("Can't delete system menu item.");
            if (::DeleteMenu(menu_handle, SC_MAXIMIZE, MF_BYCOMMAND) == 0)
                throw std::runtime_error("Can't delete system menu item.");
            if (::DeleteMenu(menu_handle, SC_MINIMIZE, MF_BYCOMMAND) == 0)
                throw std::runtime_error("Can't delete system menu item.");
            if (::DeleteMenu(menu_handle, SC_RESTORE, MF_BYCOMMAND) == 0)
                throw std::runtime_error("Can't delete system menu item.");
        }


        // variables

        const handle_type m_handle;

        std::auto_ptr<main_menu_type> m_p_main_menu;

        boost::ptr_vector<window_observer_type> m_window_observers;

        boost::signal<void ()> m_window_destroyed_handler;


    };


}}}

#endif
