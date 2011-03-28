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
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.measure.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a GUI widget for Win32 platforms.

        \tparam Traits        A traits type.
        \tparam WidgetDetails A detail implementation type of a widget.
    */
    template <typename Traits, typename WidgetDetails>
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

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;

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
            \brief Returns whether the widget has a parent.
            
            \retval true  When the widget has a parent.
            \retval false Otherwise.
        */
        bool has_parent()
        const
        {
            return widget_details_type::has_parent(*this);
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

            return widget_details_type::parent(*this);
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

            return widget_details_type::parent(*this);
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        widget& root_ancestor()
        {
            return widget_details_type::root_ancestor(*this);
        }

        /*!
            \brief Returns the root ancestor.

            \return The root ancestor.
        */
        const widget& root_ancestor()
        const
        {
            return widget_details_type::root_ancestor(*this);
        }

        /*!
            \brief Sets an enabled status.

            \param enabled An enabled status.
        */
        void set_enabled(const bool enabled)
        {
            widget_details_type::set_enabled(*this, enabled);
        }

        /*!
            \brief Returns the enabled status.

            \return The enabled status.
        */
        bool enabled()
        const
        {
            return widget_details_type::enabled(*this);
        }

        /*!
            \brief Sets a visible status.

            \param visible A visible status.
        */
        void set_visible(const bool visible)
        {
            widget_details_type::set_visible(*this, visible);
        }

        /*!
            \brief Returns the visible status.

            \return The visible status.
        */
        bool visible()
        const
        {
            return widget_details_type::visible(*this);
        }

        /*!
            \brief Creates a canvas.

            \return The unique pointer to a canvas.
        */
        typename cpp0x::unique_ptr<canvas_type>::type create_canvas()
        {
            return typename cpp0x::unique_ptr<canvas_type>::type(
                new canvas_type(&*details(), false)
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
                new canvas_type(&*details(), false)
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
            widget_details_type::set_position<dimension_type>(
                *this, position
            );
        }

        /*!
            \brief Returns the position.

            \return The position.
        */
        position_type position()
        const
        {
            return widget_details_type::position<position_type>(*this);
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

            widget_details_type::set_dimension<position_type>(
                *this, dimension
            );
        }

        /*!
            \brief Returns the dimension.

            \return The dimension.
        */
        dimension_type dimension()
        const
        {
            return widget_details_type::dimension<dimension_type>(*this);
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

            widget_details_type::set_client_dimension<position_type>(
                *this, client_dimension
            );
        }

        /*!
            \brief Returns the client dimension.

            \return The client dimension.
        */
        dimension_type client_dimension()
        const
        {
            return widget_details_type::client_dimension<dimension_type>(
                *this
            );
        }

        /*!
            \brief Sets a text.

            \tparam S A string type.

            \param text A text.
        */
        template <typename S>
        void set_text(S&& text)
        {
            widget_details_type::set_text(
                *this, std::forward<S>(text), encoder()
            );
        }

        /*!
            \brief Retuns the text.

            \return The text.
        */
        string_type text()
        const
        {
            return widget_details_type::text<string_type>(*this, encoder());
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

            \param font A font.

            \throw std::runtime_error When the font cannot be set.
        */
        void set_font(const font_type& font)
        {
            widget_details_type::set_font(*this, font);
        }

        /*!
            \brief Retuns the font.

            \return The font.
        */
        font_type font()
        const
        {
            return widget_details_type::font<font_type>(*this);
        }

        /*!
            \brief Returns the children.

            \return The children.
        */
        std::vector<child_type&> children()
        {
            return widget_details_type::children<child_type>(*this);
        }

        /*!
            \brief Returns the constant children.

            \return The children.
        */
        std::vector<const child_type&> children()
        const
        {
            return widget_details_type::children<const child_type>(*this);
        }

        /*!
            \brief Clicks this widget.
        */
        void click()
        {
            m_mouse_observer_set.clicked()();
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
                p_default_window_procedure(), &*details(), uMsg, wParam, lParam
            );
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.

            \throw std::runtime_error When the widget is already destroyed.
        */
        boost::optional<details_type&> details()
        {
            if (m_destroyed)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("This widget is destroyed.")
                );
            }

            return details_impl();
        }

        /*!
            \brief Returns the detail implementation.

            \return The detail implementation.

            \throw std::runtime_error When the widget is already destroyed.
        */
        boost::optional<const details_type&> details()
        const
        {
            if (m_destroyed)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("This widget is destroyed.")
                );
            }

            return details_impl();
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
            return widget_details_type::window_procedure<widget>;
        }

        /*!
            \brief Initializes the widget.
            
            \param p_widget A pointer to a widget.
        */
        static void initialize(widget* const p_widget)
        {
            assert(p_widget != NULL);

            widget_details_type::associate_to_native_window_system(*p_widget);
            p_widget->set_font(font_type::dialog_font());
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


    private:
        // static functions

        static ::LPCWSTR property_key_for_cpp_instance()
        {
            static const std::wstring singleton(L"C++ Instance");
            return singleton.c_str();
        }


        // variables

        const message_handler_map_type m_message_handler_map;

        bool m_destroyed;

        typename cpp0x::unique_ptr<background_type>::type m_p_background;

        paint_observer_set_type m_paint_observer_set;

        mouse_observer_set_type m_mouse_observer_set;


        // virtual functions

        virtual boost::optional<details_type&> details_impl()
        = 0;

        virtual boost::optional<const details_type&> details_impl()
        const
        = 0;

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
                reinterpret_cast< ::LPARAM>(&*details())
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
            if (::BeginPaint(&*details(), &paint_struct) == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't begin paint.")
                );
            }
            widget& self = *this;
            BOOST_SCOPE_EXIT((&self)(&paint_struct))
            {
                ::EndPaint(&*self.details(), &paint_struct);
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
                        &*details(), property_key_for_cpp_instance()
                    )
                );
            assert(p_widget == this);

            m_destroyed = true;

            return boost::optional< ::LRESULT>(0);
        }

        void delete_current_font()
        {
            const ::HFONT font_handle =
                reinterpret_cast< ::HFONT>(
                ::SendMessageW(&*details(), WM_GETFONT, 0, 0)
                );

            ::SendMessageW(&*details(), WM_SETFONT, NULL, MAKELPARAM(0, 0));

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
