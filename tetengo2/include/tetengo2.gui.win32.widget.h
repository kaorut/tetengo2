/*! \file
    \brief The definition of tetengo2::gui::win32::widget.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WIDGET_H)
#define TETENGO2_GUI_WIN32_WIDGET_H

#include <algorithm>
#include <cassert>
//#include <cstddef>
#include <exception>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
//#include <utility>
#include <vector>

#include <boost/bind.hpp>
#include <boost/exception/all.hpp>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
#include <boost/scoped_array.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a GUI widget for Win32 platforms.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class widget : private boost::noncopyable
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The handle type.
        typedef typename traits_type::handle_type handle_type;

        //! The canvas type.
        typedef typename traits_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename traits_type::alert_type alert_type;

        //! The position type.
        typedef typename traits_type::position_type position_type;

        //! The dimension type.
        typedef typename traits_type::dimension_type dimension_type;

        //! The difference type.
        typedef typename traits_type::difference_type difference_type;

        //! The size type.
        typedef typename traits_type::size_type size_type;

        //! The string type.
        typedef typename traits_type::string_type string_type;

        //! The encoder type.
        typedef typename traits_type::encoder_type encoder_type;

        //! The background type.
        typedef typename traits_type::background_type background_type;

        //! The font type.
        typedef typename traits_type::font_type font_type;

        //! The paint observer set type.
        typedef
            typename traits_type::paint_observer_set_type
            paint_observer_set_type;

        //! The mouse observer set type.
        typedef
            typename traits_type::mouse_observer_set_type
            mouse_observer_set_type;

        //! The child type.
        typedef widget child_type;


        // constructors and destructor

        /*!
            \brief Destroys the widget.
        */
        virtual ~widget()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the handle.
            
            \return The handle.

            \throw std::runtime_error When the widget is already destroyed.
        */
        handle_type handle()
        const
        {
            if (m_destroyed)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("This window is destroyed.")
                );
            }

            return handle_impl();
        }

        /*!
            \brief Returns whether the widget has a parent.
            
            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        bool has_parent()
        const
        {
            return ::GetParent(handle()) != NULL;
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::runtime_error When the widget has no parent.
        */
        widget& parent()
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            widget* const p_parent = p_widget_from(::GetParent(handle()));
            assert(p_parent != NULL);
            return *p_parent;
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::runtime_error When the widget has no parent.
        */
        const widget& parent()
        const
        {
            if (!has_parent())
                BOOST_THROW_EXCEPTION(std::runtime_error("Has no parent."));

            const widget* const p_parent =
                p_widget_from(::GetParent(handle()));
            assert(p_parent != NULL);
            return *p_parent;
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        widget& root_ancestor()
        {
            const ::HWND root_ancestor_handle =
                ::GetAncestor(handle(), GA_ROOT);
            assert(root_ancestor_handle != NULL);
            widget* const p_root_ancestor =
                p_widget_from(root_ancestor_handle);
            assert(p_root_ancestor != NULL);
            return *p_root_ancestor;
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        const widget& root_ancestor()
        const
        {
            const ::HWND root_ancestor_handle =
                ::GetAncestor(handle(), GA_ROOT);
            assert(root_ancestor_handle != NULL);
            const widget* const p_root_ancestor =
                p_widget_from(root_ancestor_handle);
            assert(p_root_ancestor != NULL);
            return *p_root_ancestor;
        }

        /*!
            \brief Sets an enabled status.

            \param enabled An enabled status.
        */
        void set_enabled(const bool enabled)
        {
            ::EnableWindow(handle(), enabled ? TRUE : FALSE);
        }

        /*!
            \brief Returns the enabled status.

            \return The enabled status.
        */
        bool enabled()
        const
        {
            return ::IsWindowEnabled(handle()) == TRUE;
        }

        /*!
            \brief Sets a visible status.

            \param visible A visible status.
        */
        void set_visible(const bool visible)
        {
            ::ShowWindow(handle(), visible ? SW_SHOW : SW_HIDE);
            if (visible)
                ::UpdateWindow(handle());
        }

        /*!
            \brief Returns the visible status.

            \return The visible status.
        */
        bool visible()
        const
        {
            return ::IsWindowVisible(handle()) == TRUE;
        }

        /*!
            \brief Creates a canvas.

            \return The unique pointer to a canvas.
        */
        typename cpp0x::unique_ptr<canvas_type>::type create_canvas()
        {
            return typename cpp0x::unique_ptr<canvas_type>::type(
                new canvas_type(handle(), false)
            );
        }

        /*!
            \brief Creates a canvas.

            \return The auto pointer to a canvas.
        */
        typename cpp0x::unique_ptr<const canvas_type>::type create_canvas()
        const
        {
            return typename cpp0x::unique_ptr<const canvas_type>::type(
                new canvas_type(handle(), false)
            );
        }

        /*!
            \brief Sets a position.

            \tparam P A position type.

            \param position A position.
        */
        template <typename P>
        void set_position(const P& position)
        {
            const dimension_type dim = dimension();
            const ::BOOL result = ::MoveWindow(
                handle(),
                to_pixels<int>(gui::position<P>::left(position)),
                to_pixels<int>(gui::position<P>::top(position)),
                to_pixels<int>(gui::dimension<dimension_type>::width(dim)),
                to_pixels<int>(gui::dimension<dimension_type>::height(dim)),
                visible() ? TRUE : FALSE
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
        */
        position_type position()
        const
        {
            ::RECT rectangle = {};
            if (::GetWindowRect(handle(), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get window rectangle.")
                );
            }

            typedef gui::position<position_type> position_traits_type;
            return position_traits_type::make(
                to_unit<typename position_traits_type::left_type>(
                    rectangle.left
                ),
                to_unit<typename position_traits_type::top_type>(
                    rectangle.top
                )
            );
        }

        /*!
            \brief Sets a dimension.

            \tparam D A dimension type.

            \param dimension A dimension.

            \throw std::invalid_argument When either dimension.first or
                                         dimension.second is equal to 0.
        */
        template <typename D>
        void set_dimension(const D& dimension)
        {
            if (
                gui::dimension<D>::width(dimension) == 0 ||
                gui::dimension<D>::height(dimension) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Dimension has zero value.")
                );
            }

            const position_type pos = position();
            const ::BOOL result = ::MoveWindow(
                handle(),
                to_pixels<int>(gui::position<position_type>::left(pos)),
                to_pixels<int>(gui::position<position_type>::top(pos)),
                to_pixels<int>(gui::dimension<D>::width(dimension)),
                to_pixels<int>(gui::dimension<D>::height(dimension)),
                visible() ? TRUE : FALSE
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
        */
        dimension_type dimension()
        const
        {
            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetWindowRect(handle(), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get window rectangle.")
                );
            }

            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            typedef gui::dimension<dimension_type> dimension_traits_type;
            return dimension_traits_type::make(
                to_unit<typename dimension_traits_type::width_type>(
                    rectangle.right - rectangle.left
                ),
                to_unit<typename dimension_traits_type::height_type>(
                    rectangle.bottom - rectangle.top
                )
            );
        }

        /*!
            \brief Sets a client dimension.

            \tparam D A dimension type.

            \param client_dimension A client dimension.

            \throw std::invalid_argument When either client_dimension.first or
                                         client_dimension.second is equal to
                                         0.
        */
        template <typename D>
        void set_client_dimension(const D& client_dimension)
        {
            if (
                gui::dimension<D>::width(client_dimension) == 0 ||
                gui::dimension<D>::height(client_dimension) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("Client dimension has zero value.")
                );
            }

            const position_type pos = position();
            const ::LONG_PTR window_style =
                ::GetWindowLongPtrW(handle(), GWL_STYLE);
            const ::LONG_PTR extended_window_style =
                ::GetWindowLongPtrW(handle(), GWL_EXSTYLE);
            const ::LONG left =
                to_pixels< ::LONG>(gui::position<position_type>::left(pos));
            const ::LONG top =
                to_pixels< ::LONG>(gui::position<position_type>::top(pos));
            const ::LONG width =
                to_pixels< ::LONG>(
                    gui::dimension<D>::width(client_dimension)
                );
            const ::LONG height =
                to_pixels< ::LONG>(
                    gui::dimension<D>::height(client_dimension)
                );
            ::RECT rectangle = { left, top, left + width, top + height };
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

            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            const ::BOOL result = ::MoveWindow(
                handle(),
                rectangle.left,
                rectangle.top,
                rectangle.right - rectangle.left,
                rectangle.bottom - rectangle.top,
                visible() ? TRUE : FALSE
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
        */
        dimension_type client_dimension()
        const
        {
            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetClientRect(handle(), &rectangle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get client rectangle.")
                );
            }

            assert(rectangle.right - rectangle.left >= 0);
            assert(rectangle.bottom - rectangle.top >= 0);
            typedef gui::dimension<dimension_type> dimension_traits_type;
            return dimension_traits_type::make(
                to_unit<typename dimension_traits_type::width_type>(
                    rectangle.right - rectangle.left
                ),
                to_unit<typename dimension_traits_type::height_type>(
                    rectangle.bottom - rectangle.top
                )
            );
        }

        /*!
            \brief Sets a text.

            \tparam S A string type.

            \param text A text.

            \throw std::runtime_error When the text cannot be set.
        */
        template <typename S>
        void set_text(S&& text)
        {
            const ::BOOL result = ::SetWindowTextW(
                handle(), encoder().encode(std::forward<S>(text)).c_str()
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
        */
        string_type text()
        const
        {
            const int length = ::GetWindowTextLengthW(handle());
            if (length == 0) return string_type();

            const boost::scoped_array<wchar_t> p_text(
                new wchar_t[length + 1]
            );
            ::GetWindowTextW(handle(), p_text.get(), length + 1);

            return encoder().decode(p_text.get());
        }

        /*!
            \brief Sets a background.

            When p_background points to NULL, the system default background is
            used.

            \param p_background A unique pointer to a background.
        */
        void set_background(
            typename cpp0x::unique_ptr<background_type>::type p_background
        )
        {
            m_p_background = std::move(p_background);
        }

        /*!
            \brief Returns the background.

            When the system default background is used, this function returns
            an uninitialized value.

            \return The background or an uninitialized value.
        */
        boost::optional<const background_type&> background()
        const
        {
            return
                m_p_background.get() != NULL ?
                boost::optional<const background_type&>(*m_p_background) :
                boost::optional<const background_type&>();
        }

        /*!
            \brief Sets a font.

            \param font a font.

            \throw std::runtime_error When the font cannot be set.
        */
        void set_font(const font_type& font)
        {
            const ::HFONT previous_font_handle =
                reinterpret_cast< ::HFONT>(
                    ::SendMessageW(handle(), WM_GETFONT, 0, 0)
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
                handle(),
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
        */
        font_type font()
        const
        {
            ::HFONT font_handle =
                reinterpret_cast< ::HFONT>(
                    ::SendMessageW(handle(), WM_GETFONT, 0, 0)
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
            \brief Clicks this widget.
        */
        void click()
        {
            m_mouse_observer_set.clicked()();
        }

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.
        */
        const paint_observer_set_type& paint_observer_set()
        const
        {
            return m_paint_observer_set;
        }

        /*!
            \brief Returns the paint observer set.

            \return The paint observer set.
        */
        paint_observer_set_type& paint_observer_set()
        {
            return m_paint_observer_set;
        }

        /*!
            \brief Returns the mouse observer set.

            \return The mouse observer set.
        */
        const mouse_observer_set_type& mouse_observer_set()
        const
        {
            return m_mouse_observer_set;
        }

        /*!
            \brief Returns the mouse observer set.

            \return The mouse observer set.
        */
        mouse_observer_set_type& mouse_observer_set()
        {
            return m_mouse_observer_set;
        }

        /*!
            \brief Returns wether the widget is destroyed.

            \retval true  When the widget is destroyed.
            \retval false Otherwise.
        */
        bool destroyed()
        const
        {
            return m_destroyed;
        }


    protected:
        // types

        //! The custom message type.
        enum message_type
        {
            WM_TETENGO2_COMMAND = WM_APP + 1,   //!< A command message.
            WM_TETENGO2_CONTROL_COLOR,          //!< A control color message.
        };

        //! The message handler type.
        typedef
            std::function<boost::optional< ::LRESULT> (::WPARAM, ::LPARAM)>
            message_handler_type;

        //! The message handler map type.
        typedef
            std::unordered_map< ::UINT, std::vector<message_handler_type>>
            message_handler_map_type;


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

            \param widget_handle A widget handle.

            \return The pointer to the widget.
        */
        static widget* p_widget_from(const ::HWND widget_handle)
        {
            return reinterpret_cast<widget*>(
                ::GetPropW(widget_handle, property_key_for_cpp_instance())
            );
        }


        // constructors

        /*!
            \brief Creates a widget.

            \param message_handler_map A message handler map.
        */
        explicit widget(message_handler_map_type&& message_handler_map)
        :
        m_message_handler_map(
            make_message_handler_map(
                std::forward<message_handler_map_type>(message_handler_map)
            )
        ),
        m_destroyed(false),
        m_p_background(),
        m_paint_observer_set(),
        m_mouse_observer_set()
        {}


        // functions

        /*!
            \brief Dispatches window messages.

            \param uMsg   A message.
            \param wParam A parameter #1.
            \param lParam A parameter #2.

            \return The result.
        */
        ::LRESULT window_procedure(
            const ::UINT    uMsg,
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            typedef
                typename message_handler_map_type::const_iterator
                map_iterator;
            const map_iterator found = m_message_handler_map.find(uMsg);
            if (found != m_message_handler_map.end())
            {
                BOOST_FOREACH (
                    const message_handler_type& handler, found->second
                )
                {
                    const boost::optional< ::LRESULT> o_result =
                        handler(wParam, lParam);
                    if (o_result) return *o_result;
                }
            }

            return ::CallWindowProcW(
                p_default_window_procedure(), handle(), uMsg, wParam, lParam
            );
        }

        /*!
            \brief Erases the background.

            \param canvas A canvas.
        */
        void erase_background(canvas_type& canvas)
        {
            if (!background()) return;

            canvas.fill_rectangle(
                position_type(0, 0), client_dimension(), *background()
            );
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
        TETENGO2_CPP0X_NOEXCEPT
        {
            try
            {
                widget* const p_widget = p_widget_from(hWnd);
                if (p_widget != NULL)
                {
                    return p_widget->window_procedure(uMsg, wParam, lParam);
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

        const message_handler_map_type m_message_handler_map;

        bool m_destroyed;

        typename cpp0x::unique_ptr<background_type>::type m_p_background;

        paint_observer_set_type m_paint_observer_set;

        mouse_observer_set_type m_mouse_observer_set;


        // virtual functions

        virtual handle_type handle_impl()
        const = 0;

        virtual ::WNDPROC p_default_window_procedure()
        const
        {
            return ::DefWindowProcW;
        }


        // functions

        message_handler_map_type make_message_handler_map(
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[WM_COMMAND].push_back(
                boost::bind(&widget::on_command, this, _1, _2)
            );
            map[WM_ERASEBKGND].push_back(
                boost::bind(&widget::on_erase_background, this, _1, _2)
            );
            map[WM_CTLCOLORBTN].push_back(
                boost::bind(&widget::on_control_color, this, _1, _2)
            );
            map[WM_CTLCOLOREDIT].push_back(
                boost::bind(&widget::on_control_color, this, _1, _2)
            );
            map[WM_CTLCOLORLISTBOX].push_back(
                boost::bind(&widget::on_control_color, this, _1, _2)
            );
            map[WM_CTLCOLORSCROLLBAR].push_back(
                boost::bind(&widget::on_control_color, this, _1, _2)
            );
            map[WM_CTLCOLORSTATIC].push_back(
                boost::bind(&widget::on_control_color, this, _1, _2)
            );
            map[WM_PAINT].push_back(
                boost::bind(&widget::on_paint, this, _1, _2)
            );
            map[WM_DESTROY].push_back(
                boost::bind(&widget::on_destroy, this, _1, _2)
            );
            map[WM_NCDESTROY].push_back(
                boost::bind(&widget::on_ncdestroy, this, _1, _2)
            );

            return map;
        }

        boost::optional< ::LRESULT> on_command(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            if (lParam == 0) return boost::optional< ::LRESULT>();

            ::PostMessageW(
                reinterpret_cast< ::HWND>(lParam),
                WM_TETENGO2_COMMAND,
                wParam,
                reinterpret_cast< ::LPARAM>(handle())
            );
            return boost::optional< ::LRESULT>();
        }

        boost::optional< ::LRESULT> on_erase_background(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            if (!background()) return boost::optional< ::LRESULT>();

            canvas_type canvas(reinterpret_cast< ::HDC>(wParam));
            erase_background(canvas);

            return boost::optional< ::LRESULT>(TRUE);
        }

        boost::optional< ::LRESULT> on_control_color(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            if (lParam == 0) return boost::optional< ::LRESULT>();

            const ::LRESULT result =
                ::SendMessageW(
                    reinterpret_cast< ::HWND>(lParam),
                    WM_TETENGO2_CONTROL_COLOR,
                    wParam,
                    0
                );

            return
                result == NULL ?
                boost::optional< ::LRESULT>() :
                boost::optional< ::LRESULT>(result);
        }

        boost::optional< ::LRESULT> on_paint(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            if (m_paint_observer_set.paint().empty())
                return boost::optional< ::LRESULT>();

            ::PAINTSTRUCT paint_struct = {};
            if (::BeginPaint(handle(), &paint_struct) == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't begin paint.")
                );
            }
            const widget& self = *this;
            BOOST_SCOPE_EXIT((&self)(&paint_struct))
            {
                ::EndPaint(self.handle(), &paint_struct);
            } BOOST_SCOPE_EXIT_END;
            canvas_type canvas(paint_struct.hdc);

            m_paint_observer_set.paint()(canvas);

            return boost::optional< ::LRESULT>(0);
        }

        boost::optional< ::LRESULT> on_destroy(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            delete_current_font();
            m_destroyed = true;
            return boost::optional< ::LRESULT>(0);
        }

        boost::optional< ::LRESULT> on_ncdestroy(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            const widget* const p_widget =
                reinterpret_cast<const widget*>(
                    ::RemovePropW(
                        handle_impl(),
                        property_key_for_cpp_instance()
                    )
                );
            assert(p_widget == this);
            return boost::optional< ::LRESULT>(0);
        }

        template <typename Child>
        std::vector<Child*> children_impl()
        const
        {
            std::vector<Child*> children;

            ::EnumChildWindows(
                handle(),
                enum_child_proc<Child>,
                reinterpret_cast< ::LPARAM>(&children)
            );

            return children;
        }

        void delete_current_font()
        {
            const ::HFONT font_handle =
                reinterpret_cast< ::HFONT>(
                ::SendMessageW(handle(), WM_GETFONT, 0, 0)
                );

            ::SendMessageW(handle(), WM_SETFONT, NULL, MAKELPARAM(0, 0));

            if (font_handle != NULL && ::DeleteObject(font_handle) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't delete previous font.")
                );
            }
        }


    };


}}}

#endif
