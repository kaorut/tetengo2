/*! \file
    \brief The definition of tetengo2::gui::win32::widget.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WIDGET_H)
#define TETENGO2_GUI_WIN32_WIDGET_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <boost/scoped_array.hpp>
#include <boost/throw_exception.hpp>
#include <boost/exception/all.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a GUI widget for Win32 platforms.

        \tparam Handle           A handle type to the native interface.
        \tparam Canvas           A canvas type.
        \tparam Alert            An alerting unary functor type.
        \tparam Difference       A difference type.
        \tparam Size             A size type.
        \tparam String           A string type.
        \tparam Encoder          An encoder type.
        \tparam Font             A font type.
        \tparam PaintObserverSet A paint observer set type.
        \tparam MouseObserver    A mouse observer type.
    */
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename Difference,
        typename Size,
        typename String,
        typename Encoder,
        typename Font,
        typename PaintObserverSet,
        typename MouseObserver
    >
    class widget : private boost::noncopyable
    {
    public:
        // types

        //! \return The handle type.
        typedef Handle handle_type;

        //! \return The canvas type.
        typedef Canvas canvas_type;

        //! \return The alerting unary functor type.
        typedef Alert alert_type;

        //! \return The difference type.
        typedef Difference difference_type;

        //! \return The size type.
        typedef Size size_type;

        //! \return The position type.
        typedef std::pair<difference_type, difference_type> position_type;

        //! \return The dimension type.
        typedef std::pair<size_type, size_type> dimension_type;

        //! \return The string type.
        typedef String string_type;

        //! \return The encoder type.
        typedef Encoder encoder_type;

        //! \return The font type.
        typedef Font font_type;

        //! \return The child type.
        typedef widget child_type;

        //! \return The paint observer set type.
        typedef PaintObserverSet paint_observer_set_type;

        //! \return The mouse observer type.
        typedef MouseObserver mouse_observer_type;


        // constructors and destructor

        /*!
            \brief Destroys the widget.
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
            \brief Returns whether the widget has a parent.
            
            \retval true  When the widget has a parent.
            \retval false Otherwise.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual bool has_parent()
        const
        {
            check_destroyed();

            return ::GetParent(this->handle()) != NULL;
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::runtime_error When the widget is already destroyed.
            \throw std::runtime_error When the widget has no parent.
        */
        virtual widget& parent()
        {
            check_destroyed();

            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            widget* const p_parent =
                p_widget_from(::GetParent(this->handle()));
            assert(p_parent != NULL);
            return *p_parent;
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::runtime_error When the widget is already destroyed.
            \throw std::runtime_error When the widget has no parent.
        */
        virtual const widget& parent()
        const
        {
            check_destroyed();

            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            const widget* const p_parent =
                p_widget_from(::GetParent(this->handle()));
            assert(p_parent != NULL);
            return *p_parent;
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual widget& root_ancestor()
        {
            check_destroyed();

            const ::HWND root_ancestor_handle =
                ::GetAncestor(this->handle(), GA_ROOT);
            assert(root_ancestor_handle != NULL);
            widget* const p_root_ancestor =
                p_widget_from(root_ancestor_handle);
            assert(p_root_ancestor != NULL);
            return *p_root_ancestor;
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual const widget& root_ancestor()
        const
        {
            check_destroyed();

            const ::HWND root_ancestor_handle =
                ::GetAncestor(this->handle(), GA_ROOT);
            assert(root_ancestor_handle != NULL);
            const widget* const p_root_ancestor =
                p_widget_from(root_ancestor_handle);
            assert(p_root_ancestor != NULL);
            return *p_root_ancestor;
        }

        /*!
            \brief Sets the enabled status.

            \param enabled A enabled status.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual void set_enabled(const bool enabled)
        {
            check_destroyed();

            ::EnableWindow(this->handle(), enabled ? TRUE : FALSE);
        }

        /*!
            \brief Returns the enabled status.

            \return The enabled status.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual bool enabled()
        const
        {
            check_destroyed();

            return ::IsWindowEnabled(this->handle()) == TRUE;
        }

        /*!
            \brief Sets the visible status.

            \param visible A visible status.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual void set_visible(const bool visible)
        {
            check_destroyed();

            ::ShowWindow(this->handle(), visible ? SW_SHOW : SW_HIDE);
            if (visible)
                ::UpdateWindow(this->handle());
        }

        /*!
            \brief Returns the visible status.

            \return The visible status.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual bool visible()
        const
        {
            check_destroyed();

            return ::IsWindowVisible(this->handle()) == TRUE;
        }

        /*!
            \brief Creates a canvas.

            \return The auto pointer to a canvas.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual std::auto_ptr<canvas_type> create_canvas()
        {
            check_destroyed();

            return std::auto_ptr<canvas_type>(
                new canvas_type(this->handle(), false)
            );
        }

        /*!
            \brief Creates a canvas.

            \return The auto pointer to a canvas.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual std::auto_ptr<const canvas_type> create_canvas()
        const
        {
            check_destroyed();

            return std::auto_ptr<const canvas_type>(
                new canvas_type(this->handle(), false)
            );
        }

        /*!
            \brief Sets the position.

            \param position A position.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual void set_position(const position_type& position)
        {
            check_destroyed();

            const dimension_type dimension = this->dimension();

            const ::BOOL result = ::MoveWindow(
                this->handle(),
                static_cast<int>(position.first),
                static_cast<int>(position.second),
                static_cast<int>(dimension.first),
                static_cast<int>(dimension.second),
                this->visible() ? TRUE : FALSE
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't move window.")
                );
            }
        }

        /*!
            \brief Returns the position.

            \return The position.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual position_type position()
        const
        {
            check_destroyed();

            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetWindowRect(this->handle(), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get window rectangle.")
                );
            }

            return std::make_pair(rectangle.left, rectangle.top);
        }

        /*!
            \brief Sets the dimension.

            \param dimension A dimension.

            \throw std::runtime_error When the widget is already destroyed.
            \throw std::invalid_argument When either dimension.first or
                                         dimension.second is equal to 0.
        */
        virtual void set_dimension(const dimension_type& dimension)
        {
            check_destroyed();

            if (dimension.first == 0 || dimension.second == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Dimension has zero value.")
                );
            }

            const position_type position = this->position();

            const ::BOOL result = ::MoveWindow(
                this->handle(),
                static_cast<int>(position.first),
                static_cast<int>(position.second),
                static_cast<int>(dimension.first),
                static_cast<int>(dimension.second),
                this->visible() ? TRUE : FALSE
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't move window.")
                );
            }
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual dimension_type dimension()
        const
        {
            check_destroyed();

            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetWindowRect(this->handle(), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get window rectangle.")
                );
            }

            assert(rectangle.right - rectangle.left > 0);
            assert(rectangle.bottom - rectangle.top > 0);
            return std::make_pair(
                rectangle.right - rectangle.left,
                rectangle.bottom - rectangle.top
            );
        }

        /*!
            \brief Sets the client dimension.

            \param client_dimension A client dimension.

            \throw std::runtime_error When the widget is already destroyed.
            \throw std::invalid_argument When either client_dimension.first or
                                         client_dimension.second is equal to
                                         0.
        */
        virtual void set_client_dimension(
            const dimension_type& client_dimension
        )
        {
            check_destroyed();

            if (client_dimension.first == 0 || client_dimension.second == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Client dimension has zero value.")
                );
            }

            const position_type position = this->position();
            const ::LONG_PTR window_style =
                ::GetWindowLongPtrW(this->handle(), GWL_STYLE);
            const ::LONG_PTR extended_window_style =
                ::GetWindowLongPtrW(this->handle(), GWL_EXSTYLE);
            ::RECT rectangle = {
                static_cast< ::LONG>(position.first),
                static_cast< ::LONG>(position.second),
                static_cast< ::LONG>(position.first + client_dimension.first),
                static_cast< ::LONG>(
                    position.second + client_dimension.second
                )
            };
            if (
                ::AdjustWindowRectEx(
                    &rectangle,
                    static_cast< ::DWORD>(window_style),
                    FALSE,
                    static_cast< ::DWORD>(extended_window_style)
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't adjust window rectangle.")
                );
            }

            assert(rectangle.right - rectangle.left > 0);
            assert(rectangle.bottom - rectangle.top > 0);
            const ::BOOL result = ::MoveWindow(
                this->handle(),
                rectangle.left,
                rectangle.top,
                rectangle.right - rectangle.left,
                rectangle.bottom - rectangle.top,
                this->visible() ? TRUE : FALSE
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't move window.")
                );
            }
        }

        /*!
            \brief Returns the client dimension.

            \return The client dimension.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual dimension_type client_dimension()
        const
        {
            check_destroyed();

            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetClientRect(this->handle(), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get client rectangle.")
                );
            }

            assert(rectangle.right - rectangle.left > 0);
            assert(rectangle.bottom - rectangle.top > 0);
            return std::make_pair(
                rectangle.right - rectangle.left,
                rectangle.bottom - rectangle.top
            );
        }

        /*!
            \brief Sets the text.

            \param text A text.

            \throw std::runtime_error When the widget is already destroyed.
            \throw std::runtime_error When the text cannot be set.
        */
        virtual void set_text(const string_type& text)
        {
            check_destroyed();

            const ::BOOL result = ::SetWindowTextW(
                this->handle(), encoder().encode(text).c_str()
            );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't set text!")
                );
            }
        }

        /*!
            \brief Retuns the text.

            \return The text.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual string_type text()
        const
        {
            check_destroyed();

            const int length = ::GetWindowTextLengthW(this->handle());
            if (length == 0) return string_type();

            const boost::scoped_array<wchar_t> p_text(
                new wchar_t[length + 1]
            );
            ::GetWindowTextW(this->handle(), p_text.get(), length + 1);

            return encoder().decode(p_text.get());
        }

        /*!
            \brief Sets the font.

            \param font a font.

            \throw std::runtime_error When the widget is already destroyed.
            \throw std::runtime_error When the font cannot be set.
        */
        virtual void set_font(const font_type& font)
        {
            check_destroyed();

            const ::HFONT previous_font_handle =
                reinterpret_cast< ::HFONT>(
                    ::SendMessageW(this->handle(), WM_GETFONT, 0, 0)
                );

            ::LOGFONTW log_font = {
                -static_cast< ::LONG>(font.size()),
                0,
                0,
                0,
                font.bold() ? FW_BOLD : FW_NORMAL,
                font.italic() ? TRUE : FALSE,
                font.underline() ? TRUE : FALSE,
                font.strikeout() ? TRUE : FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L""
            };
            assert(font.family().size() < LF_FACESIZE);
            std::copy(
                font.family().begin(),
                font.family().end(),
                log_font.lfFaceName
            );
            log_font.lfFaceName[font.family().size()] = L'\0';
            const ::HFONT font_handle = ::CreateFontIndirectW(&log_font);
            if (font_handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create font.")
                );
            }
            ::SendMessageW(
                this->handle(),
                WM_SETFONT,
                reinterpret_cast< ::WPARAM>(font_handle),
                MAKELPARAM(TRUE, 0)
            );

            if (
                previous_font_handle != NULL &&
                ::DeleteObject(previous_font_handle) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete previous font.")
                );
            }
        }

        /*!
            \brief Retuns the font.

            \return The font.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual font_type font()
        const
        {
            check_destroyed();

            ::HFONT font_handle =
                reinterpret_cast< ::HFONT>(
                    ::SendMessageW(this->handle(), WM_GETFONT, 0, 0)
                );
            if (font_handle == NULL)
            {
                font_handle =
                    reinterpret_cast< ::HFONT>(::GetStockObject(SYSTEM_FONT));
            }

            ::LOGFONTW log_font;
            const int byte_count =
                ::GetObjectW(font_handle, sizeof(::LOGFONTW), &log_font);
            if (byte_count == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get log font.")
                );
            }
            
            return font_type(
                log_font.lfFaceName,
                log_font.lfHeight < 0 ?
                    -log_font.lfHeight : log_font.lfHeight,
                log_font.lfWeight >= FW_BOLD,
                log_font.lfItalic != FALSE,
                log_font.lfUnderline != FALSE,
                log_font.lfStrikeOut != FALSE
            );
        }

        /*!
            \brief Returns the children.

            \return The children.
        */
        std::vector<child_type*> children()
        {
            return children_impl<child_type>();
        }

        /*!
            \brief Returns the constant children.

            \return The children.
        */
        std::vector<const child_type*> children()
        const
        {
            return children_impl<const child_type>();
        }

        /*!
            \brief Clicks the widget.
        */
        void click()
        {
            m_mouse_clicked_handler();
        }

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual const paint_observer_set_type& paint_observer_set()
        const
        {
            check_destroyed();

            return m_paint_observer_set;
        }

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual paint_observer_set_type& paint_observer_set()
        {
            check_destroyed();

            return m_paint_observer_set;
        }

        /*!
            \brief Adds a mouse observer.

            \param p_mouse_observer An auto pointer to a mouse observer.

            \throw std::runtime_error When the button is already destroyed.
        */
        virtual void add_mouse_observer(
            std::auto_ptr<mouse_observer_type> p_mouse_observer
        )
        {
            check_destroyed();

            m_mouse_clicked_handler.connect(
                boost::bind(
                    &typename mouse_observer_type::clicked,
                    p_mouse_observer.get()
                )
            );

            m_mouse_observers.push_back(p_mouse_observer);
        }

        /*!
            \brief Returns wether the widget is destroyed.

            \retval true  When the widget is destroyed.
            \retval false Otherwise.
        */
        virtual bool destroyed()
        const
        {
            return m_destroyed;
        }


    protected:
        // types

        //! \return The custom message type.
        enum message_type
        {
            message_command = WM_APP,   //!< A command message.
        };


        // static functions

        /*!
            \brief Returns the encoder.

            \return The encoder.
        */
        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        /*!
            \brief Returns the static window precedure.
            
            \return The pointer to the static window precedure.
        */
        static ::WNDPROC p_static_window_procedure()
        {
            return static_window_procedure;
        }

        /*!
            \brief Initializes the widget.
            
            \param p_widget A pointer to a widget.

            \throw std::runtime_error When the widget cannot be initalized.
        */
        static void initialize(widget* const p_widget)
        {
            associate_to_native_window_system(p_widget);
            p_widget->set_font(font_type::dialog_font());
        }

        /*!
            \brief Returns the pointer to the widget.

            \param window_handle A window handle.

            \return The pointer to the widget.
        */
        static widget* p_widget_from(const ::HWND window_handle)
        {
            return reinterpret_cast<widget*>(
                ::GetPropW(window_handle, property_key_for_cpp_instance())
            );
        }


        // constructors

        /*!
            \brief Creates a widget.
        */
        widget()
        :
        m_destroyed(false),
        m_paint_observer_set(),
        m_mouse_observers(),
        m_mouse_clicked_handler()
        {}

        /*!
            \brief Creates a widget.

            \param parent  A parent.
        */
        explicit widget(widget& parent)
        :
        m_destroyed(false),
        m_paint_observer_set(),
        m_mouse_observers(),
        m_mouse_clicked_handler()
        {}


        // functions

        /*!
            \brief Checks wether the window is destroyed.

            \throw std::runtime_error When the window is already destroyed.
        */
        void check_destroyed()
        const
        {
            if (m_destroyed)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("This window is destroyed.")
                );
            }
        }

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
                    if (lParam == 0) break;

                    ::PostMessageW(
                        reinterpret_cast< ::HWND>(lParam),
                        message_command,
                        wParam,
                        reinterpret_cast< ::LPARAM>(this->handle())
                    );
                    break;
                }
            case WM_PAINT:
                {
                    if (m_paint_observer_set.paint().empty()) break;

                    canvas_type canvas(this->handle(), true);
                    m_paint_observer_set.paint()(canvas);
                    return 0;
                }
            case WM_DESTROY:
                {
                    delete_current_font();
                    m_destroyed = true;
                    break;
                }
            case WM_NCDESTROY:
                {
                    const widget* const p_widget =
                        reinterpret_cast<const widget*>(
                            ::RemovePropW(
                                this->handle(),
                                property_key_for_cpp_instance()
                            )
                        );
                    assert(p_widget == this);
                }
            }
            return ::CallWindowProcW(
                p_default_window_procedure,
                this->handle(),
                uMsg,
                wParam,
                lParam
            );
        }

        /*!
            \brief Returns the event handler for a mouse click.

            \return The event handler for a mouse click.
        */
        boost::signals2::signal<void ()>& mouse_clicked_handler()
        {
            return m_mouse_clicked_handler;
        }


    private:
        // static functions

        static ::LPCWSTR property_key_for_cpp_instance()
        {
            static const std::wstring singleton(L"C++ Instance");
            return singleton.c_str();
        }

        static void associate_to_native_window_system(widget* const p_widget)
        {
            assert(
                ::GetPropW(
                    p_widget->handle(), property_key_for_cpp_instance()
                ) == NULL
            );
            const ::BOOL result =
                ::SetPropW(
                    p_widget->handle(),
                    property_key_for_cpp_instance(),
                    reinterpret_cast< ::HANDLE>(p_widget)
                );
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't set C++ instance.")
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
                widget* const p_widget = p_widget_from(hWnd);
                if (p_widget != NULL)
                {
                    return p_widget->window_procedure(
                        uMsg, wParam, lParam, ::DefWindowProcW
                    );
                }
                else
                {
                    return ::CallWindowProcW(
                        ::DefWindowProcW, hWnd, uMsg, wParam, lParam
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

        template <typename Child>
        static ::BOOL CALLBACK enum_child_proc(
            const ::HWND   hWnd,
            const ::LPARAM lParam
        )
        {
            std::vector<Child*>* const p_children =
                reinterpret_cast<std::vector<Child*>*>(lParam);

            p_children->push_back(p_widget_from(hWnd));

            return TRUE;
        }


        // variables

        bool m_destroyed;

        paint_observer_set_type m_paint_observer_set;

        boost::ptr_vector<mouse_observer_type> m_mouse_observers;

        boost::signals2::signal<void ()> m_mouse_clicked_handler;


        // functions

        void delete_current_font()
        {
            const ::HFONT font_handle =
                reinterpret_cast< ::HFONT>(
                    ::SendMessageW(this->handle(), WM_GETFONT, 0, 0)
                );

            ::SendMessageW(
                this->handle(), WM_SETFONT, NULL, MAKELPARAM(0, 0)
            );

            if (font_handle != NULL && ::DeleteObject(font_handle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete previous font.")
                );
            }
        }

        template <typename Child>
        std::vector<Child*> children_impl()
        const
        {
            std::vector<Child*> children;

            ::EnumChildWindows(
                this->handle(),
                enum_child_proc<Child>,
                reinterpret_cast< ::LPARAM>(&children)
            );

            return children;
        }


    };


}}}

#endif
