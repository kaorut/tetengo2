/*! \file
	\brief The definition of bobura::message::main_window_window_observer.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOWWINDOWOBSERVER_H)
#define BOBURA_MESSAGE_MAINWINDOWWINDOWOBSERVER_H

#include <tetengo2.gui.window_observer.h>


namespace bobura { namespace message
{
	/*!
		\brief The class templatefor a window observer of the main window.
	*/
	template <typename MessageLoop>
	class main_window_window_observer :	public tetengo2::gui::window_observer
	{
	public:
		// types

		typedef MessageLoop message_loop_type;


		// constructors and destructor

		main_window_window_observer(
			const message_loop_type* const p_message_loop
		)
		:
		m_p_message_loop(p_message_loop)
		{}

		virtual ~main_window_window_observer()
		throw ()
		{}


		// functions

		virtual void destroyed()
		{
			m_p_message_loop->exit(0);
		}


	private:
		// variables

		const message_loop_type* const m_p_message_loop;


	};
}}

#endif
