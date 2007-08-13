/*! \file
	\brief The definition of bobura::message::main_window_paint_observer.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOWPAINTOBSERVER_H)
#define BOBURA_MESSAGE_MAINWINDOWPAINTOBSERVER_H

#include <utility>


namespace bobura { namespace message
{
	/*!
		\brief The class template for a paint observer of the main window.

		$Id$
	*/
	template <typename PaintObserver>
	class main_window_paint_observer :	public PaintObserver
	{
	public:
		// types

		typedef PaintObserver parent_type;

		typedef typename parent_type::canvas_type canvas_type;


		// constructors and destructor

		main_window_paint_observer()
		{}

		virtual ~main_window_paint_observer()
		{}


		// functions

		virtual void paint(const canvas_type* p_canvas)
		{
			p_canvas->draw_text(L"‚Ä‚·‚Æ", std::make_pair(64, 32));
		}


	};
}}

#endif
