/*! \file
    \brief The definition of tetengo2::gui::widget::abstract_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_ABSTRACTWINDOW_H)
#define TETENGO2_GUI_WIDGET_ABSTRACTWINDOW_H

//#include <cstddef>
//#include <memory>
//#include <stdexcept>
//#include <utility>

//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.widget.widget.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for an abstract window.

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
        public widget<
            typename Traits::base_type, WidgetDetails, MessageHandlerDetails
        >
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
            widget<
                typename traits_type::base_type,
                widget_details_type,
                message_handler_details_type
            >
            base_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The menu bar type.
        typedef typename traits_type::menu_bar_type menu_bar_type;

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


        // functions

        /*!
            \brief Activates the abstract window.
        */
        void activate()
        {
            widget_details_type::activate(*this);
        }

        /*!
            \brief Returns true when the abstract window has a menu bar.

            \retval true  When the abstract window has a menu bar.
            \retval false Otherwise.
        */
        bool has_menu_bar()
        const
        {
            return static_cast<bool>(m_p_menu_bar);
        }

        /*!
            \brief Returns the menu bar.

            \return The menu bar.

            \throw std::logic_error When the abstract window does not have a
                                    main menu.
        */
        const menu_bar_type& menu_bar()
        const
        {
            if(!has_menu_bar())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error(
                        "The abstract window does not have a menu bar."
                    )
                );
            }

            return *m_p_menu_bar;
        }

        /*!
            \brief Returns the menu bar.

            \return The menu bar.

            \throw std::logic_error When the abstract window does not have a
                                    main menu.
        */
        menu_bar_type& menu_bar()
        {
            if(!has_menu_bar())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error(
                        "The abstract window does not have a menu bar."
                    )
                );
            }

            return *m_p_menu_bar;
        }

        /*!
            \brief Sets a menu bar.

            The shortcut key table of the menu bar is updated.

            When p_menu_bar is NULL, the currently associated main menu is
            destroyed.

            \param p_menu_bar A unique pointer to a menu bar.
        */
        void set_menu_bar(std::unique_ptr<menu_bar_type> p_menu_bar)
        {
            widget_details_type::set_menu_bar(
                *this, boost::optional<const menu_bar_type&>()
            );

            if (p_menu_bar)
            {
                p_menu_bar->update_shortcut_key_table();
                widget_details_type::set_menu_bar(
                    *this,
                    boost::make_optional<const menu_bar_type&>(*p_menu_bar)
                );
            }
            m_p_menu_bar = std::move(p_menu_bar);
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
        // types

        //! The message handler map type.
        typedef
            typename message_handler_details_type::message_handler_map_type
            message_handler_map_type;


        // constructors and destructor

        /*!
            \brief Creates an abstract window.

            \param message_handler_map A message handler map.
        */
        explicit abstract_window(
            message_handler_map_type&& message_handler_map
        )
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            message_handler_details_type::make_abstract_window_message_handler_map(
                *this,
                std::forward<message_handler_map_type>(message_handler_map)
            )
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_p_menu_bar(),
        m_window_observer_set()
        {}

        /*!
            \brief Destroys the abstract window.
        */
        virtual ~abstract_window()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // variables

        std::unique_ptr<menu_bar_type> m_p_menu_bar;

        window_observer_set_type m_window_observer_set;


    };


}}}


#endif
