/*!
	\file The definition of tetengo2::gui::win32::gui_factory.

	Copyright (C) 2007 kaoru
*/

#if !defined(TETENGO2_GUI_WIN32_GUIFACTORY_H)
#define TETENGO2_GUI_WIN32_GUIFACTORY_H

#include <exception>
#include <memory>
#include <sstream>
#include <typeinfo>

#include <boost/format.hpp>
#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.gui.win32.message_loop.h"
#include "tetengo2.gui.win32.window.h"
#include "tetengo2.gui.win32.window_message_receiver.h"


namespace tetengo2 { namespace gui { namespace win32
{
	/*!
		\class The class template for the GUI object factory for Win32
		platforms.

	*/
	template <
		typename CharType,
		typename InstanceHandleType
	>
	class gui_factory : private boost::noncopyable
	{
	public:
		// types

		typedef wchar_t char_type;

		typedef InstanceHandleType instance_handle_type; 

		typedef
			window<
				char_type,
				instance_handle_type,
				gui_factory,
				window_message_receiver
			>
			window_type;

		typedef typename window_type::handle_type window_handle_type;

		typedef message_loop<char_type> message_loop_type;


		// static functions

		static void show_fatal_error(
			const window_handle_type window_handle,
			const std::exception&    exception =
				std::runtime_error("Unknown Error!")
		)
		throw ()
		{
			try
			{
				std::ostringstream message;
				message << boost::format("%1$s:\n%2$s")
					% typeid(exception).name() % exception.what();

				::MessageBoxA(
					window_handle,
					message.str().c_str(),
					"ERROR",
					MB_OK | MB_ICONSTOP | MB_APPLMODAL
				);
			}
			catch (...)
			{}

		}


		// constructors and destructor

		gui_factory(const instance_handle_type instance_handle)
		:
		m_instance_handle(instance_handle)
		{}

		~gui_factory()
		{}


		// functions

		std::auto_ptr<window_type> create_window()
		const
		{
			return std::auto_ptr<window_type>(
				new window_type(m_instance_handle)
			);
		}

		std::auto_ptr<const message_loop_type> create_message_loop()
		const
		{
			return std::auto_ptr<const message_loop_type>(
				new message_loop_type()
			);
		}


	private:
		// variables

		const instance_handle_type m_instance_handle;


	};
}}}

#endif
