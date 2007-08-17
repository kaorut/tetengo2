/*! \file
	\brief The definition of tetengo2::gui::win32::window.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WINDOW_H)
#define TETENGO2_GUI_WIN32_WINDOW_H

#include <exception>
#include <memory>

#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
	/*!
		\brief The class template for a window for Win32 platforms.

		$Id$
	*/
	template <
		typename Handle,
		typename GuiFactory,
		template <typename Window>
		class    MessageReceiver,
		typename Canvas
	>
	class window :
		public widget<
			Handle,
			GuiFactory,
			MessageReceiver,
			Canvas
		>
	{
	public:
		// constructors and destructor

		window()
		:
		m_handle(create_window())
		{
			set_message_receiver(
				std::auto_ptr<message_receiver_type>(
					new message_receiver_type(this)
				)
			);
		}

		virtual ~window()
		throw ()
		{}


		// functions

		virtual handle_type handle()
		const
		{
			return m_handle;
		}


	private:
		// static functions

		static handle_type create_window()
		{
			const ::HINSTANCE instance_handle = ::GetModuleHandle(NULL);
			if (instance_handle == NULL)
				throw std::runtime_error("Can't get the instance handle!");

			const ::ATOM atom = register_window_class(instance_handle);

			const handle_type handle = ::CreateWindowExW(
				0,
				reinterpret_cast<::LPCWSTR>(atom),
				L"tetengo2 main widget",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				HWND_DESKTOP,
				NULL,
				instance_handle,
				NULL
			);
			if (handle == NULL)
				throw std::runtime_error("Can't create widget!");

			return handle;
		}

		static ::ATOM register_window_class(const ::HINSTANCE instance_handle)
		{
			::WNDCLASSEXW window_class;
			window_class.cbSize = sizeof(::WNDCLASSEXW);
			window_class.style = 0;
			window_class.lpfnWndProc =
				message_receiver_type::pointer_to_static_window_procedure();
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
			window_class.lpszClassName = L"tetengo2::gui::win32::widget";

			const ::ATOM atom = ::RegisterClassExW(&window_class);
			if (atom == NULL)
				throw std::runtime_error("Can't register widget class!");

			return atom;
		}


		// variables

		const handle_type m_handle;


	};
}}}

#endif
