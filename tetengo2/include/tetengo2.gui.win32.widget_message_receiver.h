/*! \file
	\brief The definition of tetengo2::gui::win32::widget_message_receiver.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WIDGETMESSAGERECEIVER_H)
#define TETENGO2_GUI_WIN32_WIDGETMESSAGERECEIVER_H

#include <exception>

#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.gui.paint_observer.h"


namespace tetengo2 { namespace gui { namespace win32
{
	/*!
		\brief The base class template for a widget message management for
		Win32 platforms.

		$Id$
	*/
	template <typename Widget>
	class widget_message_receiver : private boost::noncopyable
	{
	public:
		// types

		typedef Widget widget_type;

		typedef typename widget_type::canvas_type canvas_type;

		typedef paint_observer<canvas_type> paint_observer_type;


		// static functions

		static ::WNDPROC pointer_to_static_window_procedure()
		{
			return static_window_procedure;
		}


		// constructors and destructor

		widget_message_receiver(widget_type* const p_widget)
		:
		m_p_widget(p_widget)
		{
			set_message_receiver(p_widget);
		}

		virtual ~widget_message_receiver()
		{}


		// functions

		void add_paint_observer(
			std::auto_ptr<paint_observer_type> p_paint_observer
		)
		{
			paint_paint_handler.connect(
				boost::bind(
					&typename paint_observer_type::paint,
					p_paint_observer.get(),
					_1
				)
			);

			paint_observers.push_back(p_paint_observer);
		}


	protected:
		// functions

		virtual ::LRESULT window_procedure(
			const ::UINT   uMsg,
			const ::WPARAM wParam,
			const ::LPARAM lParam
		)
		{
			switch (uMsg)
			{
			case WM_PAINT:
				if (!paint_observers.empty())
				{
					const canvas_type canvas(m_p_widget->handle());
					paint_paint_handler(&canvas);
					return 0;
				}
			}
			return ::DefWindowProcW(
				m_p_widget->handle(), uMsg, wParam, lParam
			);
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
				widget_message_receiver* const p_message_receiver =
					get_message_receiver(hWnd);
				if (p_message_receiver != NULL) {
					return p_message_receiver->window_procedure(
						uMsg, wParam, lParam
					);
				} else {
					return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
				}
			}
			catch (std::exception& e)
			{
				typename widget_type::gui_factory_type::show_fatal_error(
					hWnd, e
				);
				return 0;
			}
			catch (...)
			{
				typename widget_type::gui_factory_type::show_fatal_error(
					hWnd
				);
				return 0;
			}
		}

		static widget_message_receiver* get_message_receiver(
			const ::HWND window_handle
		)
		{
#if defined(_WIN32) && !defined(_WIN64)
#	pragma warning(push)
#	pragma warning(disable: 4312)
#endif
			return reinterpret_cast<widget_message_receiver*>(
				::GetWindowLongPtrW(window_handle, GWLP_USERDATA)
			);
#if defined(_WIN32) && !defined(_WIN64)
#	pragma warning(pop)
#endif
		}


		// variables

		widget_type* const m_p_widget;

		boost::ptr_vector<paint_observer_type> paint_observers;

		boost::signal<void (const canvas_type*)> paint_paint_handler;


		// functions

		void set_message_receiver(widget_type* const p_widget)
		{
			::SetLastError(0);
#if defined(_WIN32) && !defined(_WIN64)
#	pragma warning(push)
#	pragma warning(disable: 4244)
#endif
			::SetWindowLongPtrW(
				p_widget->handle(),
				GWLP_USERDATA, 
				reinterpret_cast< ::LONG_PTR>(this)
			);
#if defined(_WIN32) && !defined(_WIN64)
#	pragma warning(pop)
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

	};
}}}

#endif
