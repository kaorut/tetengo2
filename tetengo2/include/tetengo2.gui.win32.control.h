/*! \file
    \brief The definition of tetengo2::gui::win32::control.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_CONTROL_H)
#define TETENGO2_GUI_WIN32_CONTROL_H

//#include <stdexcept>
//#include <utility>

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
 
        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a
                                      widget.
        \tparam MessageHandlerDetails A detail implementation type of a
                                      message handler.
   */
    template <
        typename Traits,
        typename WidgetDetails,
        typename MessageHandlerDetails
    >
    class control : public widget<typename Traits::base_type, WidgetDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef
            widget<typename traits_type::base_type, widget_details_type>
            base_type;

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
            \param p_details           A unique pointer to a detail
                                       implementation.
        */
        control(
            message_handler_map_type&& message_handler_map,
            details_ptr_type           p_details
        )
        :
        base_type(
            message_handler_details_type::make_control_message_handler_map(
                *this,
                std::forward<message_handler_map_type>(message_handler_map)
            )
        ),
        m_p_details(std::move(p_details)),
        m_p_original_window_procedure(
            replace_window_procedure(m_p_details.get())
        ),
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

        const details_ptr_type m_p_details;

        const ::WNDPROC m_p_original_window_procedure;

        boost::optional<color_type> m_text_color;


        // virtual functions

        virtual boost::optional<details_type&> details_impl()
        {
            return boost::optional<details_type&>(*m_p_details);
        }

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return boost::optional<const details_type&>(*m_p_details);
        }

        virtual ::WNDPROC p_default_window_procedure()
        const
        {
            return m_p_original_window_procedure;
        }


    };


}}}

#endif
