/*! \file
    \brief The definition of tetengo2::gui::win32::button.

    Copyright (C) 2007-2009 kaoru

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

        //! The handle type.
        typedef typename widget_type::handle_type handle_type;

        //! The canvas type.
        typedef typename widget_type::canvas_type canvas_type;

        //! The alerting unary functor type.
        typedef typename widget_type::alert_type alert_type;

        //! The difference type.
        typedef typename widget_type::difference_type difference_type;

        //! The size type.
        typedef typename widget_type::size_type size_type;

        //! The position type.
        typedef typename widget_type::position_type position_type;

        //! The dimension type.
        typedef typename widget_type::dimension_type dimension_type;

        //! The string type.
        typedef typename widget_type::string_type string_type;

        //! The unary functor type for encoding from the native.
        typedef
            typename widget_type::encode_from_native_type
            encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef
            typename widget_type::encode_to_native_type
            encode_to_native_type;

        //! The child type.
        typedef typename widget_type::child_type child_type;

        //! The paint observer type.
        typedef
            typename widget_type::paint_observer_type paint_observer_type;


        // constructors and destructor

        /*!
            \brief Creates a button.

            \param parent A parent widget.

            \throw std::runtime_error When a button cannot be created.
        */
        button(const widget_type& parent)
        :
        widget_type(parent),
        m_handle(create_window(parent))
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

        /*!
            \brief Returns the handle.
            
            \return The handle.
        */
        virtual handle_type handle()
        const
        {
            return m_handle;
        }


    protected:
        // functions

        /*!
            \brief Dispatches the button messages.

            \param uMsg   A message.
            \param wParam A word-sized parameter.
            \param lParam A long-sized parameter.

            \return The result code.
        */
        virtual ::LRESULT window_procedure(
            const ::UINT   uMsg,
            const ::WPARAM wParam,
            const ::LPARAM lParam
        )
        {
            return this->widget_type::window_procedure(uMsg, wParam, lParam);
        }


    private:
        // static functions

        static handle_type create_window(const widget_type& parent)
        {
            const handle_type handle = ::CreateWindowExW(
                0,
                L"Button",
                L"tetengo2::gui::win32::button",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON,
                0,
                0,
                64,
                64,
                parent.handle(),
                NULL,
                ::GetModuleHandle(NULL),
                NULL
            );
            if (handle == NULL)
                throw std::runtime_error("Can't create a button!");

            return handle;
        }


        // variables

        const handle_type m_handle;


    };


}}}

#endif
