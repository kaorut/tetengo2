/*! \file
    \brief The definition of tetengo2::gui::widget::abstract_window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_ABSTRACTWINDOW_H)
#define TETENGO2_GUI_WIDGET_ABSTRACTWINDOW_H

#include <memory>

#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/message/file_drop_observer_set.h>
#include <tetengo2/gui/message/window_observer_set.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    /*!
        \brief The class for an abstract window.
    */
    class abstract_window : public widget
    {
    public:
        // types

        //! The icon type.
        using icon_type = gui::icon;

        //! The menu bar type.
        using menu_bar_type = gui::menu::menu_bar;

        //! The window observer set type.
        using window_observer_set_type = gui::message::window_observer_set;

        //! The file drop observer set type.
        using file_drop_observer_set_type = gui::message::file_drop_observer_set;

        //! The window state type.
        enum class window_state_type
        {
            normal, //!< Normal state.
            maximized, //!< Maximized state.
            minimized, //!< Minimized state.
        };


        // constructors and destructor

        /*!
            \brief Destroys the abstract window.
        */
        virtual ~abstract_window() noexcept;


        // functions

        /*!
            \brief Activates the abstract window.
        */
        void activate();

        /*!
            \brief Returns the window state.

            \return The window state.
        */
        window_state_type window_state() const;

        /*!
            \brief Sets a window state.

            \param state A window state.
        */
        void set_window_state(const window_state_type state);

        /*!
            \brief Returns the normal dimension.

            \return The normal dimension.
        */
        dimension_type normal_dimension() const;

        /*!
            \brief Checks whether the abstract window has an icon.

            \retval true  When the abstract window has an icon.
            \retval false Otherwise.
        */
        bool has_icon() const;

        /*!
            \brief Returns the icon.

            \return The icon.
        */
        const icon_type& icon() const;

        /*!
            \brief Returns the icon.

            \return The icon.
        */
        icon_type& icon();

        /*!
            \brief Sets an icon.

            \param p_icon A unique pointer to an icon.
        */
        void set_icon(std::unique_ptr<icon_type> p_icon);

        /*!
            \brief Returns true when the abstract window has a menu bar.

            \retval true  When the abstract window has a menu bar.
            \retval false Otherwise.
        */
        bool has_menu_bar() const;

        /*!
            \brief Returns the menu bar.

            \return The menu bar.

            \throw std::logic_error When the abstract window does not have a main menu.
        */
        const menu_bar_type& menu_bar() const;

        /*!
            \brief Returns the menu bar.

            \return The menu bar.

            \throw std::logic_error When the abstract window does not have a main menu.
        */
        menu_bar_type& menu_bar();

        /*!
            \brief Sets a menu bar.

            The shortcut key table of the menu bar is updated.

            When p_menu_bar is nullptr, the currently associated main menu is destroyed.

            \param p_menu_bar A unique pointer to a menu bar.
        */
        void set_menu_bar(std::unique_ptr<menu_bar_type> p_menu_bar);

        /*!
            \brief Returns the file droppable status.

            \retval true  When a file drop is enabled.
            \retval false Otherwise.
        */
        bool file_droppable() const;

        /*!
            \brief Returns the window observer set.

            \return The window observer set.
        */
        const window_observer_set_type& window_observer_set() const;

        /*!
            \brief Returns the window observer set.

            \return The window observer set.
        */
        window_observer_set_type& window_observer_set();

        /*!
            \brief Returns the file drop observer set.

            \return The file drop observer set.
        */
        const file_drop_observer_set_type& file_drop_observer_set() const;

        /*!
            \brief Returns the file drop observer set.

            \return The file drop observer set.
        */
        file_drop_observer_set_type& file_drop_observer_set();

        /*!
            \brief Closes the abstract window.
        */
        void close();


    protected:
        // types

        //! The message handler map type.
        using message_handler_map_type = typename message_handler_details_type::message_handler_map_type;


        // constructors and destructor

        /*!
            \brief Creates an abstract window.

            \param scroll_bar_style    A scroll bar style type.
            \param file_droppable      Set true to enable file drop.
            \param message_handler_map A message handler map.
        */
        abstract_window(
            const scroll_bar_style_type scroll_bar_style,
            const bool                  file_droppable,
            message_handler_map_type&&  message_handler_map);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
