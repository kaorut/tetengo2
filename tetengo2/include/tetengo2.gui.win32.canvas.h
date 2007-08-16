/*! \file
	\brief The definition of tetengo2::gui::win32::canvas.

	Copyright (C) 2007 kaoru

	$Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CANVAS_H)
#define TETENGO2_GUI_WIN32_CANVAS_H

#include <string>
#include <utility>

#include <boost/noncopyable.hpp>

#define OEMRESOURCE
#include <windows.h>


namespace tetengo2 { namespace gui { namespace win32
{
	/*!
		\brief The class template for a canvas for Win32 platforms.

		$Id$
	*/
	template <typename Handle, typename WindowHandle>
	class canvas : private boost::noncopyable
	{
	public:
		// types

		typedef Handle handle_type;

		typedef WindowHandle window_handle_type;

		typedef std::pair<std::size_t, std::size_t> point_type;

		typedef std::pair<point_type, point_type> rectangle_type;


		// constructors and destructor

		canvas(const window_handle_type window_handle)
		:
		m_window_handle(window_handle),
		m_paint_info()
		{
			if (::BeginPaint(m_window_handle, &m_paint_info) == NULL)
				throw std::runtime_error("Can't begin paint!");
		}

		~canvas()
		{
			::EndPaint(m_window_handle, &m_paint_info);
		}


		// functions

		handle_type handle()
		const
		{
			return m_paint_info.hdc;
		}

		void draw_text(const std::wstring& text, const point_type& point)
		const
		{
			::BOOL successful = ::TextOut(
				this->handle(),
				static_cast<int>(point.first),
				static_cast<int>(point.second),
				text.c_str(),
				static_cast<int>(text.length())
			);
			if (successful == 0)
				throw std::runtime_error("Can't draw text!");
		}


	private:
		// variables

		const window_handle_type m_window_handle;

		::PAINTSTRUCT m_paint_info;


	};
}}}

#endif
