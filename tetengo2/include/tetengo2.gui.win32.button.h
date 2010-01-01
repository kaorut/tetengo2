/*! \file
    \brief The definition of tetengo2::gui::win32::button.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_BUTTON_H)
#define TETENGO2_GUI_WIN32_BUTTON_H

//#include <cstddef>
//#include <stdexcept>

//#include <boost/concept_check.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.gui.Widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a button for Win32 platforms.
 
        \tparam Widget A widget type. It must conform to
                       concept_tetengo2::gui::Widget<Widget>.
   */
    template <typename Widget>
    class button : public Widget
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Widget<Widget>));


    public:
        // types

        //! The widget type.
        typedef Widget widget_type;

        //! \copydoc tetengo2::gui::win32::widget::handle_type
        typedef typename widget_type::handle_type handle_type;

        //! \copydoc tetengo2::gui::win32::widget::canvas_type
        typedef typename widget_type::canvas_type canvas_type;

        //! \copydoc tetengo2::gui::win32::widget::alert_type
        typedef typename widget_type::alert_type alert_type;

        //! \copydoc tetengo2::gui::win32::widget::difference_type
        typedef typename widget_type::difference_type difference_type;

        //! \copydoc tetengo2::gui::win32::widget::size_type
        typedef typename widget_type::size_type size_type;

        //! \copydoc tetengo2::gui::win32::widget::position_type
        typedef typename widget_type::position_type position_type;

        //! \copydoc tetengo2::gui::win32::widget::dimension_type
        typedef typename widget_type::dimension_type dimension_type;

        //! \copydoc tetengo2::gui::win32::widget::string_type
        typedef typename widget_type::string_type string_type;

        //! \copydoc tetengo2::gui::win32::widget::encode_from_native_type
        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        //! \copydoc tetengo2::gui::win32::widget::encode_to_native_type
        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        //! \copydoc tetengo2::gui::win32::widget::font_type
        typedef typename widget_type::font_type font_type;

        //! \copydoc tetengo2::gui::win32::widget::child_type
        typedef typename widget_type::child_type child_type;

        //! \copydoc tetengo2::gui::win32::widget::paint_observer_type
        typedef typename widget_type::paint_observer_type paint_observer_type;

        //! \copydoc tetengo2::gui::win32::widget::mouse_observer_type
        typedef typename widget_type::mouse_observer_type mouse_observer_type;

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
        button(widget_type& parent, const style_type style = style_normal)
        :
        widget_type(parent),
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
        throw ()
        {}


        // functions

        //! \copydoc tetengo2::gui::win32::widget::handle
        virtual handle_type handle()
        const
        {
            return m_handle;
        }

        /*!
            \brief Returns the style.

            \return The style.
        */
        virtual style_type style()
        const
        {
            return m_style;
        }


    protected:
        // functions

        //! \copydoc tetengo2::gui::win32::widget::window_procedure
        virtual ::LRESULT window_procedure(
            const ::UINT    uMsg,
            const ::WPARAM  wParam,
            const ::LPARAM  lParam,
            const ::WNDPROC p_default_window_procedure
        )
        {
            switch (uMsg)
            {
            case message_command:
                {
                    mouse_clicked_handler()();
                    break;
                }
            }
            return this->widget_type::window_procedure(
                uMsg, wParam, lParam, m_p_original_window_procedure
            );
        }


    private:
        // static functions

        static handle_type create_window(
            const widget_type& parent,
            const style_type   style
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
                    throw std::runtime_error(
                        "Default button already exists."
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
                    throw std::runtime_error(
                        "Cancel button already exists."
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
                throw std::runtime_error("Can't create a button!");

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
                        widget_type::p_static_window_procedure()
                    )
                );
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(pop)
#endif
            if (result == 0)
                throw std::runtime_error("Can't replace window procedure.");

            return reinterpret_cast< ::WNDPROC>(result);
        }


        // variables

        const handle_type m_handle;

        const style_type m_style;

        const ::WNDPROC m_p_original_window_procedure;


    };


}}}

#endif
