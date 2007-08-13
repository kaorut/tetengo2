/*!
	\file The definition of tetengo2::gui::window_observer.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(TETENGO2_GUI_WINDOWOBSERVER_H)
#define TETENGO2_GUI_WINDOWOBSERVER_H

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>


namespace tetengo2 { namespace gui
{
	/*!
		\class The class for a window observer.

		$Id$
	*/
	class window_observer :
		public boost::signals::trackable, private boost::noncopyable
	{
	public:
		// constructors and destructor

		window_observer()
		{}

		virtual ~window_observer()
		{}


		// functions

		virtual void destroyed()
		{}


	};
}}

#endif
