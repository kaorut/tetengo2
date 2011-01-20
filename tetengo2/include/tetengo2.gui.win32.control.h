/*! \file
    \brief The definition of tetengo2::gui::win32::control.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CONTROL_H)
#define TETENGO2_GUI_WIN32_CONTROL_H

//#include <stdexcept>
//#include <utility>

//#include <boost/bind.hpp>
//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a control for Win32 platforms.
 
        \tparam Traits A traits type.
   */
    template <typename Traits>
    class control : public widget<typename Traits::base_type>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef widget<typename traits_type::base_type> base_type;


        // constructors and destructor

        /*!
            \brief Destroys the control.
        */
        virtual ~control()
        TETENGO2_NOEXCEPT
        {}


    protected:
        // constructors

        /*!
            \brief Creates a control.

            \param message_handler_map A message handler map.
            \param handle              A handle.
        */
        control(
            message_handler_map_type&& message_handler_map,
            const handle_type          handle
        )
        :
        base_type(
            make_message_handler_map(
                std::forward<message_handler_map_type>(message_handler_map)
            )
        ),
        m_handle(handle),
        m_p_original_window_procedure(replace_window_procedure(m_handle))
        {}


    private:
        // static functions

        static ::WNDPROC replace_window_procedure(const ::HWND handle)
        {
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(push)
#    pragma warning(disable: 4244)
#endif
            const ::LONG_PTR result = 
                ::SetWindowLongPtrW(
                    handle,
                    GWLP_WNDPROC,
                    reinterpret_cast< ::LONG_PTR>(
                        base_type::p_static_window_procedure()
                    )
                );
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(pop)
#endif
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't replace window procedure.")
                );
            }

            return reinterpret_cast< ::WNDPROC>(result);
        }


        // variables

        const handle_type m_handle;

        const ::WNDPROC m_p_original_window_procedure;


        // virtual functions

        virtual handle_type handle_impl()
        const
        {
            return m_handle;
        }

        virtual ::WNDPROC p_default_window_procedure()
        const
        {
            return m_p_original_window_procedure;
        }


        // functions

        message_handler_map_type make_message_handler_map(
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[WM_TETENGO2_CONTROL_COLOR].push_back(
                boost::bind(&control::on_control_color, this, _1, _2)
            );

            return map;
        }

        boost::optional< ::LRESULT> on_control_color(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            if (!background()) return boost::optional< ::LRESULT>();

            const ::HDC device_context = reinterpret_cast< ::HDC>(wParam);
            canvas_type canvas(device_context);
            erase_background(canvas);

            ::SetBkMode(device_context, TRANSPARENT);

            return boost::optional< ::LRESULT>(
                reinterpret_cast< ::LRESULT>(::GetStockObject(NULL_BRUSH))    
            );
        }


    };


}}}

#endif
