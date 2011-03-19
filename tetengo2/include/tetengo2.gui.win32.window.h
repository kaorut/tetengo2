/*! \file
    \brief The definition of tetengo2::gui::win32::window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_WINDOW_H)
#define TETENGO2_GUI_WIN32_WINDOW_H

//#include <stdexcept>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.win32.abstract_window.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a window for Win32 platforms.
 
        \tparam Traits        A traits type.
        \tparam WidgetDetails A detail implementation type of a widget.
   */
    template <typename Traits, typename WidgetDetails>
    class window : public abstract_window<typename Traits::base_type>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef abstract_window<typename traits_type::base_type> base_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a top level window.

            \throw std::runtime_error When a window cannot be created.
        */
        window()
        :
        base_type(message_handler_map_type()),
        m_p_details(
            widget_details_type::create_window<
                typename base_type::base_type
            >()
        )
        {
            initialize(this);
        }

        /*!
            \brief Creates a owned window.

            \param parent A parent window.

            \throw std::runtime_error When a window cannot be created.
        */
        explicit window(base_type& parent)
        :
        base_type(message_handler_map_type()),
        m_p_details(
            widget_details_type::create_window<typename base_type::base_type>(
                parent
            )
        )
        {
            initialize(this);
        }

        /*!
            \brief Destroys the window.
        */
        virtual ~window()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    private:
        // variables

        const details_ptr_type m_p_details;


        // virtual functions

        virtual handle_type handle_impl()
        const
        {
            return m_p_details.get();
        }


    };


}}}

#endif
