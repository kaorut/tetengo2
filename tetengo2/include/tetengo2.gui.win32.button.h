/*! \file
    \brief The definition of tetengo2::gui::win32::button.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_BUTTON_H)
#define TETENGO2_GUI_WIN32_BUTTON_H

//#include <cstddef>
//#include <stdexcept>
//#include <utility>

//#include <boost/bind.hpp>
//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a button for Win32 platforms.
 
        \tparam Traits A traits type.
   */
    template <typename Traits>
    class button : public widget<typename Traits::base_type>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef widget<typename traits_type::base_type> base_type;

        //! The style type.
        enum style_type
        {
            style_normal,   //!< A normal button.
            style_default,  //!< A default button.
            style_cancel    //!< A cancel button.
        };


        // constructors and destructor

        /*!
            \brief Creates a button.

            The window cannot have plural buttons with style_default. And so
            is style_cancel. When creating a second button with style_default
            or style_cancel, std::runtime_error is thrown.

            \param parent A parent widget.
            \param style  A style.

            \throw std::runtime_error When a button cannot be created.
        */
        explicit button(
            base_type&       parent,
            const style_type style = style_normal
        )
        :
        base_type(make_message_handler_map(message_handler_map_type())),
        m_handle(create_window(parent, style)),
        m_style(style),
        m_p_original_window_procedure(replace_window_procedure(m_handle))
        {
            initialize(this);
        }

        /*!
            \brief Destroys the button.
        */
        virtual ~button()
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Returns the style.

            \return The style.
        */
        style_type style()
        const
        {
            return m_style;
        }


    private:
        // static functions

        static handle_type create_window(
            const base_type& parent,
            const style_type style
        )
        {
            const ::DWORD create_window_style =
                style == style_default ?
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON :
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON;
            ::HMENU id = NULL;
            if (style == style_default)
            {
                if (
                    ::GetDlgItem(parent.root_ancestor().handle(), IDOK) !=
                    NULL
                )
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Default button already exists.")
                    );
                }
                id = reinterpret_cast< ::HMENU>(IDOK);
            }
            else if (style == style_cancel)
            {
                if (
                    ::GetDlgItem(parent.root_ancestor().handle(), IDCANCEL) !=
                    NULL
                )
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Cancel button already exists.")
                    );
                }
                id = reinterpret_cast< ::HMENU>(IDCANCEL);
            }
            const handle_type handle = ::CreateWindowExW(
                0,
                L"Button",
                L"tetengo2::gui::win32::button",
                create_window_style,
                0,
                0,
                64,
                64,
                parent.handle(),
                id,
                ::GetModuleHandle(NULL),
                NULL
            );
            if (handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a button!")
                );
            }

            return handle;
        }

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

        const style_type m_style;

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

            map[WM_TETENGO2_COMMAND].push_back(
                boost::bind(&button::on_tetengo2_command, this, _1, _2)
            );

            return map;
        }

        boost::optional< ::LRESULT> on_tetengo2_command(
            const ::WPARAM  wParam,
            const ::LPARAM  lParam
        )
        {
            mouse_observer_set().clicked()();
            
            return boost::optional< ::LRESULT>(0);
        }


    };


}}}

#endif
