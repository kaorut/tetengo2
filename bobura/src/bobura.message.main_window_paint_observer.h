/*!
	\file The definition of bobura::message::main_window_paint_observer.

	Copyright (C) 2007 kaoru
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOWPAINTOBSERVER_H)
#define BOBURA_MESSAGE_MAINWINDOWPAINTOBSERVER_H

namespace bobura { namespace message
{
	/*!
		\class The template class for a paint observer of the main window.

	*/
	template <typename PaintObserver>
	class main_window_paint_observer :	public PaintObserver
	{
	public:
		// constructors and destructor

		main_window_paint_observer()
		{}

		virtual ~main_window_paint_observer()
		{}


		// functions

		virtual void paint()
		{
		
		}


	};
}}

#endif
