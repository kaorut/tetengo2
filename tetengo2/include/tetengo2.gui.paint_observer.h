/*!
	\file The definition of tetengo2::gui::paint_observer.

	Copyright (C) 2007 kaoru
*/

#if !defined(TETENGO2_GUI_PAINTOBSERVER_H)
#define TETENGO2_GUI_PAINTOBSERVER_H

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>


namespace tetengo2 { namespace gui
{
	/*!
		\class The class for a window observer.

	*/
	class paint_observer :
		public boost::signals::trackable, private boost::noncopyable
	{
	public:
		// constructors and destructor

		paint_observer()
		{}

		virtual ~paint_observer()
		{}


		// functions

		virtual void paint()
		{}


	};
}}

#endif
