/*! \file
    \brief The definition of tetengo2::gui::widget::abstract_window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_ABSTRACTWINDOW_H)
#define TETENGO2_GUI_WIDGET_ABSTRACTWINDOW_H

#include <memory>
#include <stdexcept>

#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/menu/shortcut_key_table.h>
#include <tetengo2/gui/message/window_observer_set.h>
#include <tetengo2/gui/message/file_drop_observer_set.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for an abstract window.

        \tparam Traits        A traits type.
        \tparam DetailsTraits A detail implementation type traits.
        \tparam MenuDetails   A detail implementation type of a menu.
    */
    template <typename Traits, typename DetailsTraits, typename MenuDetails>
    class abstract_window : public widget<Traits, DetailsTraits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The details traits type.
        using details_traits_type = DetailsTraits;

        //! The widget details type.
        using widget_details_type = typename details_traits_type::widget_details_type;

        //! The icon details type.
        using icon_details_type = typename details_traits_type::icon_details_type;

        //! The message handler details type.
        using message_handler_details_type = typename details_traits_type::message_handler_details_type;

        //! The virtual key details type.
        using virtual_key_details_type = typename details_traits_type::virtual_key_details_type;

        //! The menu details type.
        using menu_details_type = MenuDetails;

        //! The base type.
        using base_type = widget<traits_type, details_traits_type>;

        //! The dimension type.
        using dimension_type = typename base_type::dimension_type;

        //! The string type.
        using string_type = typename base_type::string_type;

        //! The encoder type.
        using encoder_type = typename base_type::encoder_type;

        //! The scroll bar style type.
        using scroll_bar_style_type = typename base_type::scroll_bar_style_type;

        //! The icon type.
        using icon_type = gui::icon<dimension_type, icon_details_type>;

        //! The shortcut key table type.
        using shortcut_key_table_type =
            gui::menu::shortcut_key_table<string_type, encoder_type, menu_details_type, virtual_key_details_type>;

        //! The menu bar type.
        using menu_bar_type =
            gui::menu::menu_bar<
                string_type, shortcut_key_table_type, encoder_type, menu_details_type, virtual_key_details_type
            >;

        //! The window observer set type.
        using window_observer_set_type = gui::message::window_observer_set;

        //! The file drop observer set type.
        using file_drop_observer_set_type = gui::message::file_drop_observer_set;

        //! The window state type.
        enum class window_state_type
        {
            normal,    //!< Normal state.
            maximized, //!< Maximized state.
            minimized, //!< Minimized state.
        };


        // functions

        /*!
            \brief Activates the abstract window.
        */
        void activate()
        {
            widget_details_type::activate(*this);
        }

        /*!
            \brief Returns the window state.

            \return The window state.
        */
        window_state_type window_state()
        const
        {
            return widget_details_type::template window_state<window_state_type>(*this);
        }

        /*!
            \brief Sets a window state.

            \param state A window state.
        */
        void set_window_state(const window_state_type state)
        {
            return widget_details_type::template set_window_state<window_state_type>(*this, state);
        }

        /*!
            \brief Returns the normal dimension.

            \return The normal dimension.
        */
        dimension_type normal_dimension()
        const
        {
            return widget_details_type::template normal_dimension<dimension_type>(*this);
        }

        /*!
            \brief Checks whether the abstract window has an icon.

            \retval true  When the abstract window has an icon.
            \retval false Otherwise.
        */
        bool has_icon()
        const
        {
            return static_cast<bool>(m_p_icon);
        }

        /*!
            \brief Returns the icon.

            \return The icon.
        */
        const icon_type& icon()
        const
        {
            if (!has_icon())
                BOOST_THROW_EXCEPTION((std::logic_error{ "This abstract window has no icon." }));

            return *m_p_icon;
        }

        /*!
            \brief Returns the icon.

            \return The icon.
        */
        icon_type& icon()
        {
            if (!has_icon())
                BOOST_THROW_EXCEPTION((std::logic_error{ "This abstract window has no icon." }));

            return *m_p_icon;
        }

        /*!
            \brief Sets an icon.

            \param p_icon A unique pointer to an icon.
        */
        void set_icon(std::unique_ptr<icon_type> p_icon)
        {
            widget_details_type::set_icon(*this, p_icon.get());
            m_p_icon = std::move(p_icon);
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

            \throw std::logic_error When the abstract window does not have a main menu.
        */
        const menu_bar_type& menu_bar()
        const
        {
            if(!has_menu_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The abstract window does not have a menu bar." }));

            return *m_p_menu_bar;
        }

        /*!
            \brief Returns the menu bar.

            \return The menu bar.

            \throw std::logic_error When the abstract window does not have a main menu.
        */
        menu_bar_type& menu_bar()
        {
            if(!has_menu_bar())
                BOOST_THROW_EXCEPTION((std::logic_error{ "The abstract window does not have a menu bar." }));

            return *m_p_menu_bar;
        }

        /*!
            \brief Sets a menu bar.

            The shortcut key table of the menu bar is updated.

            When p_menu_bar is nullptr, the currently associated main menu is destroyed.

            \param p_menu_bar A unique pointer to a menu bar.
        */
        void set_menu_bar(std::unique_ptr<menu_bar_type> p_menu_bar)
        {
            widget_details_type::set_menu_bar(*this, static_cast<const menu_bar_type*>(nullptr));

            if (p_menu_bar)
            {
                p_menu_bar->update_shortcut_key_table();
                widget_details_type::set_menu_bar(*this, p_menu_bar.get());
            }
            m_p_menu_bar = std::move(p_menu_bar);
        }

        /*!
            \brief Returns the file droppable status.

            \retval true  When a file drop is enabled.
            \retval false Otherwise.
        */
        bool file_droppable()
        const
        {
            return m_file_droppable;
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
            \brief Returns the file drop observer set.

            \return The file drop observer set.
        */
        const file_drop_observer_set_type& file_drop_observer_set()
        const
        {
            return m_file_drop_observer_set;
        }

        /*!
            \brief Returns the file drop observer set.

            \return The file drop observer set.
        */
        file_drop_observer_set_type& file_drop_observer_set()
        {
            return m_file_drop_observer_set;
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
            message_handler_map_type&&  message_handler_map
        )
        :
#if BOOST_COMP_MSVC
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            scroll_bar_style,
            message_handler_details_type::make_abstract_window_message_handler_map(
                *this, std::move(message_handler_map)
            )
        ),
#if BOOST_COMP_MSVC
#   pragma warning(pop)
#endif
        m_file_droppable(file_droppable),
        m_p_icon(),
        m_p_menu_bar(),
        m_window_observer_set(),
        m_file_drop_observer_set()
        {}

        /*!
            \brief Destroys the abstract window.
        */
        virtual ~abstract_window()
        noexcept
        {
            if (!this->destroyed())
                set_icon(std::unique_ptr<icon_type>{});
        }


    private:
        // variables

        const bool m_file_droppable;

        std::unique_ptr<icon_type> m_p_icon;

        std::unique_ptr<menu_bar_type> m_p_menu_bar;

        window_observer_set_type m_window_observer_set;

        file_drop_observer_set_type m_file_drop_observer_set;


    };


}}}


#endif
