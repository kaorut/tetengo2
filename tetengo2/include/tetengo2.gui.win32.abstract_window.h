/*! \file
    \brief The definition of tetengo2::gui::win32::abstract_window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H)
#define TETENGO2_GUI_WIN32_ABSTRACTWINDOW_H

//#include <cassert>
//#include <cstddef>
//#include <utility>

//#include <boost/optional.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for an abstract window for Win32 platforms.
 
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
    class abstract_window :
        public widget<typename Traits::base_type, WidgetDetails>
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

        //! The main menu type.
        typedef typename traits_type::main_menu_type main_menu_type;

        //! The window observer set type.
        typedef
            typename traits_type::window_observer_set_type
            window_observer_set_type;

        //! The detail implementation type.
        typedef
            typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef
            typename widget_details_type::widget_details_ptr_type
            details_ptr_type;


        // constructors and destructor

        /*!
            \brief Destroys the abstract window.
        */
        virtual ~abstract_window()
        TETENGO2_CPP0X_NOEXCEPT
        {}


        // functions

        /*!
            \brief Activates the abstract window.
        */
        void activate()
        {
            widget_details_type::activate(*this);
        }

        /*!
            \brief Returns true when the abstract window has a main menu.

            \retval true  When the abstract window has a main menu.
            \retval false Otherwise.
        */
        bool has_main_menu()
        const
        {
            return m_p_main_menu.get() != NULL;
        }

        /*!
            \brief Returns the main menu.

            When the abstract window does not have a main menu, the result is
            undefined.

            \return The main menu.
        */
        main_menu_type& main_menu()
        {
            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Returns the main menu.

            When the abstract window does not have a main menu, the result is
            undefined.

            \return The main menu.
        */
        const main_menu_type& main_menu()
        const
        {
            assert(has_main_menu());

            return *m_p_main_menu;
        }

        /*!
            \brief Sets a main menu.

            When p_main_menu is NULL, the currently associated main menu is
            destroyed.

            \param p_main_menu A unique pointer to a main menu.
        */
        void set_main_menu(
            typename cpp0x::unique_ptr<main_menu_type>::type p_main_menu
        )
        {
            widget_details_type::set_main_menu(
                *this, boost::optional<const main_menu_type&>()
            );
            
            if (p_main_menu.get() != NULL)
            {
                widget_details_type::set_main_menu(
                    *this,
                    boost::optional<const main_menu_type&>(*p_main_menu)
                );
            }
            m_p_main_menu = std::move(p_main_menu);
        }

        /*!
            \brief Returns the window observer set.

            \return The window observer set.
        */
        const window_observer_set_type& window_observer_set()
        const
        {
            return m_window_observer_set;
        }

        /*!
            \brief Returns the window observer set.

            \return The window observer set.
        */
        window_observer_set_type& window_observer_set()
        {
            return m_window_observer_set;
        }

        /*!
            \brief Closes the abstract window.
        */
        void close()
        {
            widget_details_type::close(*this);
        }


    protected:
        // constructors

        /*!
            \brief Creates an abstract window.

            \param message_handler_map A message handler map.
        */
        explicit abstract_window(
            message_handler_map_type&& message_handler_map
        )
        :
        base_type(
            message_handler_details_type::make_abstract_window_message_handler_map(
                *this,
                std::forward<message_handler_map_type>(message_handler_map)
            )
        ),
        m_p_main_menu(),
        m_window_observer_set()
        {}


    private:
        // variables

        typename cpp0x::unique_ptr<main_menu_type>::type m_p_main_menu;

        window_observer_set_type m_window_observer_set;


    };


}}}

#endif
