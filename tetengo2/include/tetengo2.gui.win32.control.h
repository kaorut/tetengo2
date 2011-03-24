/*! \file
    \brief The definition of tetengo2::gui::win32::control.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CONTROL_H)
#define TETENGO2_GUI_WIN32_CONTROL_H

//#include <cstddef>
//#include <stdexcept>
//#include <utility>

//#include <boost/bind.hpp>
//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a control for Win32 platforms.
 
        \tparam Traits        A traits type.
        \tparam WidgetDetails A detail implementation type of a widget.
   */
    template <typename Traits, typename WidgetDetails>
    class control : public widget<typename Traits::base_type>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The base type.
        typedef widget<typename traits_type::base_type> base_type;

        //! The color type.
        typedef typename traits_type::color_type color_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the control.
        */
        virtual ~control()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the text color.

            \return The text color.
        */
        const boost::optional<color_type>& text_color()
        const
        {
            return m_text_color;
        }

        /*!
            \brief Sets a text color.

            \tparam C A color type.

            \param text_color A text color.
        */
        template <typename C /* = boost::optional<color_type>() */>
        void set_text_color(
            C&& text_color /* = boost::optional<color_type>() */
        )
        {
            m_text_color = text_color;
        }

#if !defined(DOCUMENTATION)
        void set_text_color()
        {
            m_text_color = boost::optional<color_type>();
        }
#endif


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
        m_p_original_window_procedure(replace_window_procedure(m_handle)),
        m_text_color()
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

        boost::optional<color_type> m_text_color;


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

            if (m_text_color)
            {
                const ::COLORREF previous_color =
                    ::SetTextColor(
                        device_context,
                        RGB(
                            m_text_color->red(),
                            m_text_color->green(),
                            m_text_color->blue()
                        )
                    );
                if (previous_color == CLR_INVALID)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't set text color.")
                    );
                }
            }
            const int previous_background_mode =
                ::SetBkMode(device_context, TRANSPARENT);
            if (previous_background_mode == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't set background mode.")
                );
            }

            return boost::optional< ::LRESULT>(
                reinterpret_cast< ::LRESULT>(::GetStockObject(NULL_BRUSH))    
            );
        }


    };


}}}

#endif
