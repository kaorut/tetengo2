/*! \file
	\brief The definition of tetengo2::gui::paint_observer.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(TETENGO2_GUI_PAINTOBSERVER_H)
#define TETENGO2_GUI_PAINTOBSERVER_H

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>


namespace tetengo2 { namespace gui
{
	/*!
		\brief The base class template for a paint observer.
	*/
	template <typename Canvas>
	class paint_observer :
		public boost::signals::trackable, private boost::noncopyable
	{
	public:
		// types

		typedef Canvas canvas_type;


		// constructors and destructor

		paint_observer()
		{}

		virtual ~paint_observer()
		throw ()
		{}


		// functions

		virtual void paint(const canvas_type* /* p_canvas */)
		{}


	};
}}

#endif
