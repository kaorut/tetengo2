/*! \file
    \brief The definition of tetengo2::gui::win32::button.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_BUTTON_H)
#define TETENGO2_GUI_WIN32_BUTTON_H

//#include <stdexcept>
//#include <utility>

//#include <boost/bind.hpp>
//#include <boost/optional.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.win32.control.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a button for Win32 platforms.
 
        \tparam Traits        A traits type.
        \tparam WidgetDetails A detail implementation type of a widget.
   */
    template <typename Traits, typename WidgetDetails>
    class button : public control<typename Traits::base_type, WidgetDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The base type.
        typedef
            control<typename traits_type::base_type, widget_details_type>
            base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;

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
            widget_type&     parent,
            const style_type style = style_normal
        )
        :
        base_type(
            make_message_handler_map(message_handler_map_type()),
            widget_details_type::create_button(
                parent,
                style == style_default,
                style == style_cancel
            )
        ),
        m_style(style)
        {
            initialize(this);
        }

        /*!
            \brief Destroys the button.
        */
        virtual ~button()
        TETENGO2_CPP0X_NOEXCEPT
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
        // variables

        const style_type m_style;


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
