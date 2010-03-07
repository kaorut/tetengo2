/*! \file
    \brief The definition of tetengo2::gui::win32::dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOG_H)
#define TETENGO2_GUI_WIN32_DIALOG_H

#include <cassert>
#include <cstddef>
#include <exception>
//#include <memory>
#include <stdexcept>

#include <boost/cast.hpp>
//#include <boost/concept_check.hpp>
#include <boost/exception/exception.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

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

        //! The base type.
        typedef AbstractWindow base_type;

        //! \copydoc tetengo2::gui::win32::widget::handle_type
        typedef typename base_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::widget::canvas_type
        typedef typename base_type::canvas_type canvas_type;

        //! \copydoc tetengo2::gui::win32::widget::alert_type
        typedef typename base_type::alert_type alert_type;

        //! \copydoc tetengo2::gui::win32::widget::difference_type
        typedef typename base_type::difference_type difference_type;

        //! \copydoc tetengo2::gui::win32::widget::size_type
        typedef typename base_type::size_type size_type;

        //! \copydoc tetengo2::gui::win32::widget::position_type
        typedef typename base_type::position_type position_type;

        //! \copydoc tetengo2::gui::win32::widget::dimension_type
        typedef typename base_type::dimension_type dimension_type;

        //! \copydoc tetengo2::gui::win32::widget::string_type
        typedef typename base_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::widget::encode_from_native_type
        typedef
            typename base_type::encode_from_native_type
            encode_from_native_type;

        //! \copydoc tetengo2::gui::win32::widget::encode_to_native_type
        typedef
            typename base_type::encode_to_native_type encode_to_native_type;

        //! \copydoc tetengo2::gui::win32::widget::font_type
        typedef typename base_type::font_type font_type;

        //! \copydoc tetengo2::gui::win32::widget::child_type
        typedef typename base_type::child_type child_type;

        //! \copydoc tetengo2::gui::win32::widget::paint_observer_type
        typedef typename base_type::paint_observer_type paint_observer_type;

        //! \copydoc tetengo2::gui::win32::widget::mouse_observer_type
        typedef typename base_type::mouse_observer_type mouse_observer_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::main_menu_type.
        typedef typename base_type::main_menu_type main_menu_type;

        //! \copydoc tetengo2::gui::win32::abstract_window::window_observer_type.
        typedef typename base_type::window_observer_type window_observer_type;

        //! The message loop type.
        typedef MessageLoop message_loop_type;

        //! The quit message loop type.
        typedef QuitMessageLoop quit_message_loop_type;

        //! The result type.
        enum result_type
        {
            result_undecided,   //!< The result is not decided yet.
            result_accepted,    //!< The settings are accepted.
            result_canceled,    //!< The settings are canceled.
        };


        // constructors and destructor

        /*!
            \brief Creates a dialog.

            \param parent A parent window.

            \throw std::runtime_error When a dialog cannot be created.
        */
        explicit dialog(base_type& parent)
        :
        base_type(parent),
        m_handle(create_window(&parent)),
        m_result(result_undecided)
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

        //! \copydoc tetengo2::gui::win32::widget::handle
        virtual handle_type handle()
        const
        {
            return m_handle;
        }

        //! \copydoc tetengo2::gui::win32::abstract_window::close
        virtual void close()
        {
            check_destroyed();

            const ::BOOL result = ::DestroyWindow(this->handle());
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't destroy the dialog.")
                );
            }
        }

        /*!
            \brief Sets the result.

            \param result A result.

            \throw std::runtime_error When the dialog is already destroyed.
        */
        virtual void set_result(const result_type result)
        {
            check_destroyed();

            m_result = result;
        }

        /*!
            \brief Returns the result.

            \return The result.
        */
        virtual result_type result()
        const
        {
            return m_result;
        }

        /*!
            \brief Shows the dialog as modal.

            \return The result.

            \throw std::runtime_error When the dialog is already destroyed.
        */
        virtual result_type do_modal()
        {
            check_destroyed();

            assert(this->has_parent());
            base_type& parent = dynamic_cast<base_type&>(this->parent());
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

            return this->result();
        }


    protected:
        // functions

        //! \copydoc tetengo2::gui::win32::widget::window_procedure
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
                    const ::WORD hi_wparam = HIWORD(wParam);
                    const ::WORD lo_wparam = LOWORD(wParam);
                    if (
                        hi_wparam == 0 &&
                        (lo_wparam == IDOK || lo_wparam == IDCANCEL)
                    )
                    {
                        const ::HWND handle =
                            reinterpret_cast< ::HWND>(lParam);
                        assert(
                            handle == ::GetDlgItem(this->handle(), lo_wparam)
                        );
                        if (handle != NULL)
                        {
                            p_widget_from(handle)->click();
                        }
                        else
                        {
                            this->set_result(
                                lo_wparam == IDOK ?
                                result_accepted : result_canceled
                            );
                            this->close();
                        }
                        return 0;
                    }
                    break;
                }
            }
            return this->base_type::window_procedure(
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
                L"tetengo2::gui::win32::dialog";
            return singleton;
        }

        static handle_type create_window(const base_type* const p_parent)
        {
            const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
            if (instance_handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get the instance handle!")
                );
            }

            if (
                !window_class_is_registered(
                    window_class_name(), instance_handle
                )
            )
            {
                register_window_class(instance_handle);
            }

            const handle_type handle = ::CreateWindowExW(
                WS_EX_CONTEXTHELP | WS_EX_DLGMODALFRAME,
                window_class_name().c_str(),
                window_class_name().c_str(),
                WS_POPUPWINDOW | WS_CAPTION,
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
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a dialog!")
                );
            }

            delete_system_menus(handle);

            return handle;
        }

        static void register_window_class(const ::HINSTANCE instance_handle)
        {
            ::WNDCLASSEXW window_class;
            window_class.cbSize = sizeof(::WNDCLASSEXW);
            window_class.style = 0;
            window_class.lpfnWndProc = static_window_procedure;
            window_class.cbClsExtra = 0;
            window_class.cbWndExtra = DLGWINDOWEXTRA;
            window_class.hInstance = instance_handle;
            window_class.hIcon = NULL;
            window_class.hIconSm = NULL;
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
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't register a window class!")
                );
            }
        }

        static void delete_system_menus(const ::HWND window_handle)
        {
            const ::HMENU menu_handle = ::GetSystemMenu(window_handle, FALSE);
            if (menu_handle == NULL) return;

            if (::DeleteMenu(menu_handle, SC_SIZE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
            if (::DeleteMenu(menu_handle, SC_MAXIMIZE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
            if (::DeleteMenu(menu_handle, SC_MINIMIZE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
            if (::DeleteMenu(menu_handle, SC_RESTORE, MF_BYCOMMAND) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete system menu item.")
                );
            }
        }

        static ::LRESULT CALLBACK static_window_procedure(
            const ::HWND   hWnd,
            const ::UINT   uMsg,
            const ::WPARAM wParam,
            const ::LPARAM lParam
        )
        throw ()
        {
            try
            {
                dialog* const p_dialog =
                    boost::polymorphic_downcast<dialog*>(p_widget_from(hWnd));
                if (p_dialog != NULL)
                {
                    return p_dialog->window_procedure(
                        uMsg, wParam, lParam, ::DefDlgProcW
                    );
                }
                else
                {
                    return ::CallWindowProcW(
                        ::DefDlgProcW, hWnd, uMsg, wParam, lParam
                    );
                }
            }
            catch (const boost::exception& e)
            {
                (alert_type(hWnd))(e);
                return 0;
            }
            catch (const std::exception& e)
            {
                (alert_type(hWnd))(e);
                return 0;
            }
            catch (...)
            {
                (alert_type(hWnd))();
                return 0;
            }
        }


        // variables

        const handle_type m_handle;

        result_type m_result;


    };


}}}

#endif
