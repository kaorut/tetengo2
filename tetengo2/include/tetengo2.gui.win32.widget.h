/*! \file
    \brief The definition of tetengo2::gui::win32::widget.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WIDGET_H)
#define TETENGO2_GUI_WIN32_WIDGET_H

#include <exception>
#include <memory>
#include <stdexcept>
#include <string>

#include <boost/bind.hpp>
#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/signal.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>

#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.StringConcept.h"
#include "tetengo2.gui.CanvasConcept.h"
#include "tetengo2.gui.HandleConcept.h"
#include "tetengo2.gui.PaintObserverConcept.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a GUI widget for Win32 platforms.

        \param Handle                A handle type to the native interface. It
                                     must conform to
                                     tetengo2::gui::HandleConcept<Handle>.
        \param Canvas                A canvas type. It must conform to
                                     tetengo2::gui::CanvasConcept<Canvas>.
        \param Alert                 An alerting unary functor type. It must
                                     conform to
                                     boost::UnaryFunctionConcept<Alert, void, Handle, std::exception>.
        \param String                A string type. It must conform to
                                     tetengo2::StringConcept<String>.
        \param Encode                An encoding unary functor type. The types
                                     Encode<String, std::wstring> and
                                     Encode<std::wstring, String> must conform
                                     to
                                     boost::UnaryFunctionConcept<Encode, String, std::wstring>
                                     and
                                     boost::UnaryFunctionConcept<Encode, std::wstring, String>.
        \param PaintObserver         A paint observer type. It must conform to
                                     tetengo2::gui::PaintObserverConcept<PaintObserver>.
    */
    template <
        typename Handle,
        typename Canvas,
        typename Alert,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename PaintObserver
    >
    class widget : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Handle, tetengo2::gui, HandleConcept);
        BOOST_CLASS_REQUIRE(Canvas, tetengo2::gui, CanvasConcept);
        struct concept_check_Alert
        {
            typedef std::exception exception_type;
            BOOST_CLASS_REQUIRE3(
                Alert,
                void,
                exception_type,
                boost,
                UnaryFunctionConcept
            );
        };
        BOOST_CLASS_REQUIRE(String, tetengo2, StringConcept);
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<String, std::wstring> encode_from_native_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CLASS_REQUIRE3(
                encode_from_native_type,
                String,
                native_string_type,
                boost,
                UnaryFunctionConcept
            );
            BOOST_CLASS_REQUIRE3(
                encode_to_native_type,
                native_string_type,
                String,
                boost,
                UnaryFunctionConcept
            );
        };
        BOOST_CLASS_REQUIRE(
            PaintObserver, tetengo2::gui, PaintObserverConcept
        );


    public:
        // types

        //! The handle type.
        typedef Handle handle_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The alerting unary functor type.
        typedef Alert alert_type;

        //! The string type
        typedef String string_type;

        //! The unary functor type for encoding from the native.
        typedef Encode<String, std::wstring> encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef Encode<std::wstring, String> encode_to_native_type;

        //! The paint observer type.
        typedef PaintObserver paint_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a widget.
        */
        widget()
        :
        m_paint_observers(),
        m_paint_paint_handler()
        {}

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
            \brief Sets the visible status.

            \param visible A visible status.
        */
        virtual void set_visible(const bool visible)
        {
            ::ShowWindow(this->handle(), visible ? SW_SHOW : SW_HIDE);
        }

        /*!
            \brief Returns the visible status.

            \param The visible status.
        */
        virtual bool visible()
        const
        {
            return ::IsWindowVisible(this->handle()) == TRUE;
        }

        /*!
            \brief Sets the text.

            \param text A text.
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
            catch (std::exception& e)
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

        static widget* p_widget_from(
            const ::HWND window_handle
        )
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
