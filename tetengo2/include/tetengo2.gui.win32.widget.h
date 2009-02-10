/*! \file
    \brief The definition of tetengo2::gui::win32::widget.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WIDGET_H)
#define TETENGO2_GUI_WIN32_WIDGET_H

#include <cassert>
//#include <cstddef>
#include <exception>
#include <memory>
#include <stdexcept>
//#include <string>
#include <utility>

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
        */
        virtual bool has_parent()
        const
        {
            return ::GetParent(this->handle()) != NULL;
        }

        /*!
            \brief Returns the parent.

            \return The parent.

            \throw std::runtime_error When the widget has no parent.
        */
        virtual const widget& parent()
        const
        {
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
        */
        virtual void set_enabled(const bool enabled)
        {
            ::EnableWindow(this->handle(), enabled ? TRUE : FALSE);
        }

        /*!
            \brief Returns the enabled status.

            \return The enabled status.
        */
        virtual bool enabled()
        const
        {
            return ::IsWindowEnabled(this->handle()) == TRUE;
        }

        /*!
            \brief Sets the visible status.

            \param visible A visible status.
        */
        virtual void set_visible(const bool visible)
        {
            ::ShowWindow(this->handle(), visible ? SW_SHOW : SW_HIDE);
        }

        /*!
            \brief Returns the visible status.

            \return The visible status.
        */
        virtual bool visible()
        const
        {
            return ::IsWindowVisible(this->handle()) == TRUE;
        }

        /*!
            \brief Sets the position.

            \param position A position.
        */
        virtual void set_position(const position_type& position)
        {
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
        */
        virtual const position_type position()
        const
        {
            ::RECT rectangle = {0, 0, 0, 0};
            if (::GetWindowRect(this->handle(), &rectangle) == 0)
                throw std::runtime_error("Can't get window rectangle.");

            return std::make_pair(rectangle.left, rectangle.top);
        }

        /*!
            \brief Sets the dimension.

            \param dimension A dimension.

            \throw std::invalid_argument When either dimension.first or
                                         dimension.second is equal to 0.
        */
        virtual void set_dimension(const dimension_type& dimension)
        {
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
        */
        virtual const dimension_type dimension()
        const
        {
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
            \brief Sets the text.

            \param text A text.

            \throw std::runtime_error When the text cannot be set.
        */
        virtual void set_text(const string_type& text)
        {
            const ::BOOL result = ::SetWindowTextW(
                this->handle(), encode_to_native_type()(text).c_str()
            );
            if (result == 0)
                throw std::runtime_error("Can't set text!");
        }

        /*!
            \brief Retuns the text.

            \return The text.
        */
        virtual const string_type text()
        const
        {
            const int length = ::GetWindowTextLengthW(this->handle());
            if (length == 0) return string_type();

            const boost::scoped_array<wchar_t> p_text(
                new wchar_t[length + 1]
            );
            ::GetWindowTextW(this->handle(), p_text.get(), length + 1);

            return encode_from_native_type()(p_text.get());
        }

        /*!
            \brief Adds a paint observer.

            \param p_paint_observer An auto pointer to a paint observer.
        */
        void add_paint_observer(
            std::auto_ptr<paint_observer_type> p_paint_observer
        )
        {
            m_paint_paint_handler.connect(
                boost::bind(
                    &typename paint_observer_type::paint,
                    p_paint_observer.get(),
                    _1
                )
            );

            m_paint_observers.push_back(p_paint_observer);
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
            \brief Associates the widget instance pointer with the native
                   window system.
            
            \param p_widget A pointer to a widget.

            \throw std::runtime_error When the widget instance pointer cannot
                                      be associated with the native window
                                      system.
        */
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


        // constructors

        /*!
            \brief Creates a widget.
        */
        widget()
        :
        m_paint_observers(),
        m_paint_paint_handler()
        {}

        /*!
            \brief Creates a widget.

            \param parent A parent.
        */
        widget(const widget& parent)
        :
        m_paint_observers(),
        m_paint_paint_handler()
        {}


        // functions

        /*!
            \brief Dispatches the window messages.

            \param uMsg   A message.
            \param wParam A word-sized parameter.
            \param lParam A long-sized parameter.

            \return The result code.
        */
        virtual ::LRESULT window_procedure(
            const ::UINT   uMsg,
            const ::WPARAM wParam,
            const ::LPARAM lParam
        )
        {
            switch (uMsg)
            {
            case WM_PAINT:
                if (!m_paint_observers.empty())
                {
                    canvas_type canvas(this->handle());
                    m_paint_paint_handler(&canvas);
                    return 0;
                }
            }
            return ::DefWindowProcW(this->handle(), uMsg, wParam, lParam);
        }


    private:
        // static functions

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
                    return p_widget->window_procedure(uMsg, wParam, lParam);
                else
                    return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
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


        // variables

        boost::ptr_vector<paint_observer_type> m_paint_observers;

        boost::signal<void (canvas_type*)> m_paint_paint_handler;


    };


}}}

#endif
