/*! \file
    \brief The definition of tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOG_H)
#define TETENGO2_GUI_WIN32_DIALOG_H

#include <cassert>
//#include <memory>
#include <stdexcept>

//#include <boost/concept_check.hpp>
#include <boost/scope_exit.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.AbstractWindow.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a modal dialog.
 
        \tparam AbstractWindow  An abstract window type. It must conform to
                                concept_tetengo2::gui::AbstractWindow<AbstractWindow>.
        \tparam MessageLoop     A generator type for a message loop. It must
                                conform to
                                boost::Generator<MessageLoop, int>.
        \tparam QuitMessageLoop A unary functor type for quitting the message
                                loop. It must conform to
                                boost::UnaryFunction<QuitMessageLoop, void, int>
   */
    template <
        typename AbstractWindow,
        typename MessageLoop,
        typename QuitMessageLoop
    >
    class dialog : public AbstractWindow
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::AbstractWindow<AbstractWindow>
        ));
        BOOST_CONCEPT_ASSERT((boost::Generator<MessageLoop, int>));
        BOOST_CONCEPT_ASSERT((
            boost::UnaryFunction<QuitMessageLoop, void, int>
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

        //! The style type.
        enum style_type
        {
            style_flat,     //!< A flat window_style.
            style_frame,    //!< A frame window style.
            style_dialog,   //!< A dialog box style.
        };

        //! The message loop type.
        typedef MessageLoop message_loop_type;

        //! The quit message loop type.
        typedef QuitMessageLoop quit_message_loop_type;


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param parent A parent window.
            \param style  A style.

            \throw std::runtime_error When a dialog cannot be created.
        */
        dialog(
            const abstract_window_type& parent,
            const style_type            style = style_dialog
        )
        :
        abstract_window_type(parent),
        m_handle(create_window(style, &parent))
        {
            initialize(this);
        }

        /*!
            \brief Destroys the dialog.
        */
        virtual ~dialog()
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
            \brief Shows the dialog as modal.

            \throw std::runtime_error When the dialog is already destroyed.
        */
        virtual void do_modal()
        {
            check_destroyed();

            assert(this->has_parent());
            abstract_window_type& parent =
                dynamic_cast<abstract_window_type&>(this->parent());
            parent.set_enabled(false);
            BOOST_SCOPE_EXIT((&parent))
            {
                parent.set_enabled(true);
                parent.activate();
            } BOOST_SCOPE_EXIT_END

            this->add_window_observer(
                std::auto_ptr<window_observer_type> (
                    new dialog_window_observer_type()
                )
            );
            this->set_visible(true);

            message_loop_type()();
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
        // types

        struct dialog_window_observer_type : public window_observer_type
        {
            virtual void destroyed()
            {
                quit_message_loop_type()(0);
            }
        };


        // static functions

        static const string_type& window_class_name()
        {
            static const string_type singleton =
                L"tetengo2::gui::win32::window";
            return singleton;
        }

        static handle_type create_window(
            const style_type                  style,
            const abstract_window_type* const p_parent
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


    };


}}}

#endif
