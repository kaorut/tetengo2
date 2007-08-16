/*! \file
	\brief The definition of tetengo2::gui::win32::widget.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WIDGET_H)
#define TETENGO2_GUI_WIN32_WIDGET_H

#include <exception>
#include <memory>
#include <string>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>

#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32
{
	/*!
		\brief The base class template for a GUI widget for Win32 platforms.

		$Id$
	*/
	template <
		typename Handle,
		typename GuiFactory,
		template <typename Widget>
		class    MessageReceiver,
		typename Canvas
	>
	class widget : private boost::noncopyable
	{
	public:
		// types

		typedef Handle handle_type;

		typedef GuiFactory gui_factory_type;

		typedef MessageReceiver<widget> message_receiver_type;

		typedef Canvas canvas_type;


		// constructors and destructor

		widget()
		:
		m_p_message_receiver()
		{}

		virtual ~widget()
		throw ()
		{}


		// functions

		virtual handle_type handle()
		const = 0;

		message_receiver_type* message_receiver()
		const
		{
			if (m_p_message_receiver.get() == NULL)
				throw std::logic_error("Message receiver not set!");

			return m_p_message_receiver.get();
		}

		virtual void set_visible(const bool visible)
		{
			::ShowWindow(this->handle(), visible ? SW_SHOW : SW_HIDE);
		}

		virtual bool is_visible()
		const
		{
			return ::IsWindowVisible(this->handle()) == TRUE;
		}

		virtual void set_text(const std::wstring& text)
		{
			if (::SetWindowText(this->handle(), text.c_str()) == 0)
				throw std::runtime_error("Can't set text!");
		}

		virtual const std::wstring text()
		const
		{
			const int length = ::GetWindowTextLengthW(this->handle());
			if (length == 0) return std::wstring();

			const boost::scoped_array<wchar_t> p_text(
				new wchar_t[length + 1]
			);
			::GetWindowTextW(this->handle(), p_text.get(), length + 1);

			return std::wstring(p_text.get());
		}


	protected:
		// functions

		void set_message_receiver(
			std::auto_ptr<message_receiver_type> p_message_receiver
		)
		{
			m_p_message_receiver.reset(p_message_receiver.release());
		}


	private:
		// variables

		boost::scoped_ptr<message_receiver_type> m_p_message_receiver;

	};
}}}

#endif
