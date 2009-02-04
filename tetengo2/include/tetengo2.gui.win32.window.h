/*! \file
    \brief The definition of tetengo2::gui::win32::window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WINDOW_H)
#define TETENGO2_GUI_WIN32_WINDOW_H

#include <cassert>
//#include <cstddef>
//#include <exception>
//#include <memory>
//#include <stdexcept>
//#include <string>

//#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
//#include <boost/signal.hpp>
//#include <boost/ptr_container/ptr_vector.hpp>

#include "concept_tetengo2.gui.MainMenu.h"
#include "concept_tetengo2.gui.WindowObserver.h"
#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a window for Win32 platforms.
 
        \tparam Handle                A handle type to the native interface.
                                      It must conform to
                                      concept_tetengo2::gui::Handle<Handle>.
        \tparam Canvas                A canvas type. It must conform to
                                      concept_tetengo2::gui::Canvas<Canvas>.
        \tparam Alert                 An alerting unary functor type. It must
                                      conform to
                                      boost::UnaryFunction<Alert, void, Handle, std::exception>.
        \tparam Difference            A difference type. It must conform to
                                      boost::SignedInteger<Difference>.
        \tparam Size                  A size type. It must conform to
                                      boost::UnsignedInteger<Size>.
        \tparam String                A string type. It must conform to
                                      concept_tetengo2::String<String>.
        \tparam Encode                An encoding unary functor type. The
                                      types Encode<String, std::wstring> and
                                      Encode<std::wstring, String> must
                                      conform to
                                      boost::UnaryFunction<Encode, String, std::wstring>
                                      and
                                      boost::UnaryFunction<Encode, std::wstring, String>.
        \tparam MainMenu              A main menu type. It must conform to
                                      concept_tetengo2::gui::MainMenu<MainMenu>.
        \tparam PaintObserver         A paint observer type. It must conform
                                      to
                                      concept_tetengo2::gui::PaintObserver<PaintObserver>.
        \tparam WindowObserver        A window observer type. It must conform
                                      to
                                      concept_tetengo2::gui::WindowObserver<WindowObserver>.
   */
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename Difference,
        typename Size,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename MainMenu,
        typename PaintObserver,
        typename WindowObserver
    >
    class window :
        public widget<
            Handle,
            Canvas,
            Alert,
            Difference,
            Size,
            String,
            Encode,
            PaintObserver
        >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MainMenu<MainMenu>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::WindowObserver<WindowObserver>
        ));


    public:
        // types

        //! The main menu type.
        typedef MainMenu main_menu_type;

        //! The window observer type.
        typedef WindowObserver window_observer_type;

        //! The style type;
        enum style_type
        {
            style_flat,     //!< A flat window_style.
            style_frame,    //!< A frame window style.
            style_dialog,   //!< A dialog box style.
        };


        // constructors and destructor

        /*!
            \brief Creates a window.

            \param style    A window style.
            \param p_parent A pointer to a parent window. Specify NULL when
                            this window is on the top level.

            \throw std::runtime_error When a window cannot be created.
        */
        window(const style_type style, const window* const p_parent)
        :
        m_handle(create_window(style, p_parent)),
        m_p_main_menu(),
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
            \brief Activates the window.
        */
        void activate()
        {
            if (::SetForegroundWindow(this->handle()) == 0)
                throw std::runtime_error("Can't be active.");

        }

        /*!
            \brief Returns true when the window has a main menu.

            \retval true  When the window has a main menu.
            \retval false Otherwise.
        */
        bool has_main_menu()
        const
        {
            return m_p_main_menu.get() != NULL;
        }

        /*!
            \brief Returns the main menu.

            When the window does not have a main menu, the result is
            undefined.

            \return The main menu.
        */
        main_menu_type& main_menu()
        {
            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Sets a main menu.

            When p_main_menu is NULL, the currently associated main menu is
            destroyed.

            \param p_main_menu An auto pointer to a main menu.
        */
        void set_main_menu(std::auto_ptr<main_menu_type> p_main_menu)
        {
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

        /*!
            \brief Closes the window.
        */
        void close()
        {
            const ::BOOL result = ::PostMessageW(m_handle, WM_CLOSE, 0, 0);
            if (result == 0)
                throw std::runtime_error("Can't close the window.");
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
                    m_window_destroyed_handler();
                    return 0;
                }
            }
            return this->widget::window_procedure(uMsg, wParam, lParam);
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
