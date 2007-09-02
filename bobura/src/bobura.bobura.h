/*! \file
	\brief The definition of bobura::bobura.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "bobura.message.main_window_paint_observer.h"
#include "bobura.message.main_window_window_observer.h"


namespace bobura
{
	/*!
		\brief The class template for the bobura application.

		\param GuiFactory An abstract factory type to create platform specific
		                  GUI components. It must conform to
						  tetengo2::gui::gui_factory_concept.
	*/
	template <typename GuiFactory>
	class bobura : private boost::noncopyable
	{
	public:
		// types

		//! The abstract factory type to create platform specific GUI
		//! components.
		typedef GuiFactory gui_factory_type;


		// constructors and destructor

		/*!
			\brief Creates a bobura application.

			\param p_gui_factory An auto pointer to a GUI factory.
		*/
		bobura(std::auto_ptr<const gui_factory_type> p_gui_factory)
		:
		m_p_gui_factory(p_gui_factory)
		{}

		/*!
			\brief Destroys the bobura application.
		*/
		~bobura()
		throw ()
		{}


		// functions

		/*!
			\brief Runs the main process of the application.

			\return The exit status code.
		*/
		int run()
		const
		{
			const boost::scoped_ptr<window_type> p_main_window(
				m_p_gui_factory->create_window()
			);

			const boost::scoped_ptr<const message_loop_type> p_message_loop(
				m_p_gui_factory->create_message_loop()
			);

			set_message_observers(
				p_main_window.get(), p_message_loop.get()
			);
			p_main_window->set_text(L"ぼうぶら テストプログラム");
			p_main_window->set_visible(true);

			return p_message_loop->run();
		}


	private:
		//types

		typedef typename gui_factory_type::canvas_type canvas_type;

		typedef typename gui_factory_type::window_type window_type;

		typedef
			typename gui_factory_type::message_loop_type message_loop_type;

		typedef
			typename window_type::message_receiver_type message_receiver_type;

		typedef
			typename message_receiver_type::window_observer_type
			window_observer_type;

		typedef
			typename message_receiver_type::paint_observer_type
			paint_observer_type;


		// variables

		const boost::scoped_ptr<const gui_factory_type> m_p_gui_factory;


		// functions

		void set_message_observers(
			window_type* const             p_window,
			const message_loop_type* const p_message_loop
		)
		const
		{
			p_window->message_receiver()->add_window_observer(
				std::auto_ptr<window_observer_type> (
					new message::main_window_window_observer<
						message_loop_type
					>(p_message_loop)
				)
			);

			p_window->message_receiver()->add_paint_observer(
				std::auto_ptr<paint_observer_type> (
					new message::main_window_paint_observer<canvas_type>()
				)
			);
		}

	};
}

#endif
