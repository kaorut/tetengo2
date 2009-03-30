/*! \file
    \brief The definition of tetengo2::gui::win32::widget.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WIDGET_H)
#define TETENGO2_GUI_WIN32_WIDGET_H

#include <algorithm>
#include <cassert>
//#include <cstddef>
#include <exception>
#include <memory>
#include <stdexcept>
//#include <string>
#include <utility>
#include <vector>

#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>
#include <boost/scoped_array.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Canvas.h"
#include "concept_tetengo2.gui.Font.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.PaintObserver.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a GUI widget for Win32 platforms.

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
        \tparam Font                  A font type. It must conform to
                                      concept_tetengo2::gui::Font<Font>.
        \tparam PaintObserver         A paint observer type. It must conform
                                      to
                                      concept_tetengo2::gui::PaintObserver<PaintObserver>.
    */
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename Difference,
        typename Size,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename Font,
        typename PaintObserver
    >
    class widget : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Canvas<Canvas>));
        struct concept_check_Alert
        {
            typedef std::exception exception_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<Alert, void, exception_type>
            ));
        };
        BOOST_CONCEPT_ASSERT((boost::SignedInteger<Difference>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<String, std::wstring> encode_from_native_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_native_type, String, native_string_type
                >
            ));
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_to_native_type, native_string_type, String
                >
            ));
        };
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Font<Font>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::PaintObserver<PaintObserver>
        ));


    public:
        // types

        //! The handle type.
        typedef Handle handle_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The alerting unary functor type.
        typedef Alert alert_type;

        //! The difference type.
        typedef Difference difference_type;

        //! The size type.
        typedef Size size_type;

        //! The position type.
        typedef std::pair<difference_type, difference_type> position_type;

        //! The dimension type.
        typedef std::pair<size_type, size_type> dimension_type;

        //! The string type.
        typedef String string_type;

        //! The unary functor type for encoding from the native.
        typedef Encode<String, std::wstring> encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef Encode<std::wstring, String> encode_to_native_type;

        //! The font type.
        typedef Font font_type;

        //! The child type.
        typedef widget child_type;

        //! The paint observer type.
        typedef PaintObserver paint_observer_type;


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
            
            \retval true  The widget has a parent.
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
                throw std::runtime_error("Has no parent.");

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
                throw std::runtime_error("Has no parent.");

            const widget* const p_parent =
                p_widget_from(::GetParent(this->handle()));
            assert(p_parent != NULL);
            return *p_parent;
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
                throw std::runtime_error("Can't move window.");
        }

        /*!
            \brief Returns the position.

            \return The position.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual const position_type position()
        const
        {
            check_destroyed();

            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetWindowRect(this->handle(), &rectangle) == 0)
                throw std::runtime_error("Can't get window rectangle.");

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
                throw std::invalid_argument("Dimension has zero value.");

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
                throw std::runtime_error("Can't move window.");
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual const dimension_type dimension()
        const
        {
            check_destroyed();

            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetWindowRect(this->handle(), &rectangle) == 0)
                throw std::runtime_error("Can't get window rectangle.");

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
                throw std::invalid_argument(
                    "Client dimension has zero value."
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
                throw std::runtime_error("Can't adjust window rectangle.");
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
                throw std::runtime_error("Can't move window.");
        }

        /*!
            \brief Returns the client dimension.

            \return The client dimension.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual const dimension_type client_dimension()
        const
        {
            check_destroyed();

            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetClientRect(this->handle(), &rectangle) == 0)
                throw std::runtime_error("Can't get client rectangle.");

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
                this->handle(), encode_to_native_type()(text).c_str()
            );
            if (result == 0)
                throw std::runtime_error("Can't set text!");
        }

        /*!
            \brief Retuns the text.

            \return The text.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual const string_type text()
        const
        {
            check_destroyed();

            const int length = ::GetWindowTextLengthW(this->handle());
            if (length == 0) return string_type();

            const boost::scoped_array<wchar_t> p_text(
                new wchar_t[length + 1]
            );
            ::GetWindowTextW(this->handle(), p_text.get(), length + 1);

            return encode_from_native_type()(p_text.get());
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
                throw std::runtime_error("Can't create font.");
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
                throw std::runtime_error("Can't delete previous font.");
            }
        }

        /*!
            \brief Retuns the font.

            \return The font.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual const font_type font()
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
                throw std::runtime_error("Can't get log font.");
            
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
        const std::vector<child_type*> children()
        {
            return children_impl<child_type>();
        }

        /*!
            \brief Returns the constant children.

            \return The children.
        */
        const std::vector<const child_type*> children()
        const
        {
            return children_impl<const child_type>();
        }

        /*!
            \brief Adds a paint observer.

            \param p_paint_observer An auto pointer to a paint observer.

            \throw std::runtime_error When the widget is already destroyed.
        */
        virtual void add_paint_observer(
            std::auto_ptr<paint_observer_type> p_paint_observer
        )
        {
            check_destroyed();

            m_paint_paint_handler.connect(
                boost::bind(
                    &typename paint_observer_type::paint,
                    p_paint_observer.get(),
                    _1
                )
            );

            m_paint_observers.push_back(p_paint_observer);
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
        // static functions

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
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(push)
#    pragma warning(disable: 4312)
#endif
            return reinterpret_cast<widget*>(
                ::GetWindowLongPtrW(window_handle, GWLP_USERDATA)
            );
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(pop)
#endif
        }


        // constructors

        /*!
            \brief Creates a widget.
        */
        widget()
        :
        m_destroyed(false),
        m_paint_observers(),
        m_paint_paint_handler()
        {}

        /*!
            \brief Creates a widget.

            \param parent A parent.
        */
        widget(const widget& parent)
        :
        m_destroyed(false),
        m_paint_observers(),
        m_paint_paint_handler()
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
                throw std::runtime_error("This window is destroyed.");
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
            case WM_USER:
                {
                    return 0;
                }
            case WM_COMMAND:
                {
                    if (lParam == 0) break;

                    ::PostMessageW(
                        reinterpret_cast< ::HWND>(lParam),
                        WM_USER,
                        wParam,
                        reinterpret_cast< ::LPARAM>(this->handle())
                    );
                    break;
                }
            case WM_PAINT:
                {
                    if (m_paint_observers.empty()) break;

                    canvas_type canvas(this->handle(), true);
                    m_paint_paint_handler(&canvas);
                    return 0;
                }
            case WM_DESTROY:
                {
                    delete_current_font();
                    m_destroyed = true;
                    return 0;
                }
            }
            return p_default_window_procedure(
                this->handle(), uMsg, wParam, lParam
            );
        }


    private:
        // static functions

        static void associate_to_native_window_system(
            const widget* const p_widget
        )
        {
            ::SetLastError(0);
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(push)
#    pragma warning(disable: 4244)
#endif
            ::SetWindowLongPtrW(
                p_widget->handle(),
                GWLP_USERDATA, 
                reinterpret_cast< ::LONG_PTR>(p_widget)
            );
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(pop)
#endif
            const BOOL set_window_pos_result = ::SetWindowPos(
                p_widget->handle(),
                NULL,
                0,
                0,
                0,
                0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED
            );

            if (::GetLastError() > 0 || set_window_pos_result == 0)
                throw std::runtime_error("Can't set the pointer to this!");
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
                    return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
                }
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

        boost::ptr_vector<paint_observer_type> m_paint_observers;

        boost::signal<void (canvas_type*)> m_paint_paint_handler;


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
                throw std::runtime_error("Can't delete previous font.");
        }

        template <typename Child>
        const std::vector<Child*> children_impl()
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
