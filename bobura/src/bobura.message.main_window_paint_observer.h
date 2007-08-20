/*! \file
	\brief The definition of bobura::message::main_window_paint_observer.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOWPAINTOBSERVER_H)
#define BOBURA_MESSAGE_MAINWINDOWPAINTOBSERVER_H

#include <utility>

#include <tetengo2.gui.paint_observer.h>


namespace bobura { namespace message
{
	/*!
		\brief The class template for a paint observer of the main window.
	*/
	template <typename Canvas>
	class main_window_paint_observer :
		public tetengo2::gui::paint_observer<Canvas>
	{
	public:
		// constructors and destructor

		main_window_paint_observer()
		{}

		virtual ~main_window_paint_observer()
		throw ()
		{}


		// functions

		virtual void paint(const canvas_type* p_canvas)
		{
			p_canvas->draw_text(L"‚Ä‚·‚Æ", std::make_pair(64, 32));
		}


	};
}}

#endif
