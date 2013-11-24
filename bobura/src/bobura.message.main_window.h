/*! \file
    \brief The definition of bobura::message::main_window.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOW_H)
#define BOBURA_MESSAGE_MAINWINDOW_H

#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <vector>

#include <boost/throw_exception.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>


namespace bobura { namespace message { namespace main_window
{
    /*!
        \brief The class template for a popup menu selection observer of the main window.

        \tparam PopupMenu A popup menu type.
        \tparam Command   A command type.
        \tparam Model     A model type.
    */
    template <typename PopupMenu, typename Command, typename Model>
    class popup_menu_selected
    {
    public:
        // types

        //! The popup menu type.
        typedef PopupMenu popup_menu_type;

        //! The command type.
        typedef Command command_type;

        //! The model type.
        typedef Model model_type;


        // constructors and destructor

        /*!
            \brief Creates a popup menu selection observer of the main window.

            \param popup_menu A popup menu type.
            \param commands   Commands.
            \param model      A model.
        */
        popup_menu_selected(
            popup_menu_type&                   popup_menu,
            std::vector<const command_type*>&& commands,
            const model_type&                  model
        )
        :
        m_popup_menu(popup_menu),
        m_commands(commands),
        m_model(model)
        {
            assert(
                static_cast<std::size_t>(std::distance(m_popup_menu.begin(), m_popup_menu.end())) == m_commands.size()
            );
        }


        // functions

        /*!
            \brief Called when the menu is selected.
        */
        void operator()()
        const
        {
            std::size_t i = 0;
            for (auto& menu_item: m_popup_menu)
            {
                assert(i < m_commands.size());
                const auto* const p_command = m_commands[i];
                if (!p_command)
                {
                    ++i;
                    continue;
                }

                menu_item.set_enabled(p_command->enabled(m_model));
                menu_item.set_state(translate_state(p_command->state()));

                ++i;
            }
        }


    private:
        // types

        typedef typename popup_menu_type::base_type::base_type menu_base_type;


        // static functions

        static typename menu_base_type::state_type translate_state(const typename command_type::state_type state)
        {
            switch (state)
            {
            case command_type::state_type::default_:
                return menu_base_type::state_type::default_;
            case command_type::state_type::checked:
                return menu_base_type::state_type::checked;
            case command_type::state_type::selected:
                return menu_base_type::state_type::selected;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid command state."));
            }
        }


        // variables

        popup_menu_type& m_popup_menu;

        std::vector<const command_type*> m_commands;

        const model_type& m_model;


    };


    /*!
        \brief The class template for a menu command selection observer of the main window.

        \tparam Command        A command type.
        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename Command, typename Model, typename AbstractWindow>
    class menu_command_selected
    {
    public:
        // types

        //! The command type.
        typedef Command command_type;

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command selection observer of the main window.

            \param command A command.
            \param model   A model.
            \param parent  A parent window.
        */
        menu_command_selected(const command_type& command, model_type& model, abstract_window_type& parent)
        :
        m_command(command),
        m_model(model),
        m_parent(parent)
        {}


        // functions

        /*!
            \brief Called when the menu is selected.
        */
        void operator()()
        const
        {
            m_command.execute(m_model, m_parent);
        }


    private:
        // variables

        const command_type& m_command;

        model_type& m_model;

        abstract_window_type& m_parent;


    };


    /*!
        \brief The class template for a file drop observer of the main window.

        \tparam CommandSet     A command set type.
        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename CommandSet, typename Model, typename AbstractWindow>
    class file_dropped
    {
    public:
        // types

        //! The command set type.
        typedef CommandSet command_set_type;

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The path type.
        typedef typename abstract_window_type::file_drop_observer_set_type::path_type path_type;


        // constructors and destructor

        /*!
            \brief Creates a file drop observer of the main window.

            \param command_set A command set.
            \param model       A model.
            \param parent      A parent window.
        */
        file_dropped(const command_set_type& command_set, model_type& model, abstract_window_type& parent)
        :
        m_command_set(command_set),
        m_model(model),
        m_parent(parent)
        {}


        // functions

        /*!
            \brief Called when the menu is selected.

            \param paths Paths.
        */
        void operator()(const std::vector<path_type>& paths)
        const
        {
            if (paths.empty())
                return;

            const auto p_paramter = m_command_set.create_load_from_file_parameter(paths[0]);
            m_command_set.load_from_file().execute(m_model, m_parent, *p_paramter);
        }


    private:
        // variables

        const command_set_type& m_command_set;

        model_type& m_model;

        abstract_window_type& m_parent;


    };


    /*!
        \brief The class template for a window resized observer of the main window.

        \tparam View              A view type.
        \tparam AbstractWindow    An abstract window type.
        \tparam DiagramPictureBox A diagram picture box type.
        \tparam PropertyBar       A property bar type.
    */
    template <typename View, typename AbstractWindow, typename DiagramPictureBox, typename PropertyBar>
    class window_resized
    {
    public:
        // types

        //! The view type.
        typedef View view_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The diagram picture box type.
        typedef DiagramPictureBox diagram_picture_box_type;

        //! The property bar type.
        typedef PropertyBar property_bar_type;


        // constructors and destructor

        /*!
            \brief Creates a window resized observer of the main window.

            \param view                A view.
            \param window              A window.
            \param diagram_picture_box A diagram picture box.
            \param property_bar        A property bar.
        */
        window_resized(
            view_type&                view,
            abstract_window_type&     window,
            diagram_picture_box_type& diagram_picture_box,
            property_bar_type&        property_bar
        )
        :
        m_view(view),
        m_window(window),
        m_diagram_picture_box(diagram_picture_box),
        m_property_bar(property_bar)
        {}


        // functions

        /*!
            \brief Called when the main window is resized.
        */
        void operator()()
        const
        {
            if (m_window.window_state() == window_state_type::minimized)
                return;

            const auto window_dimension = m_window.client_dimension();
            const auto& window_width = tetengo2::gui::dimension<dimension_type>::width(window_dimension);
            const auto& window_height = tetengo2::gui::dimension<dimension_type>::height(window_dimension);
            const auto& property_bar_width = m_property_bar.preferred_width();
            {
                const position_type position(
                    left_type::from(window_width) - left_type::from(property_bar_width), top_type(0)
                );
                const dimension_type dimension(property_bar_width, window_height);
                m_property_bar.set_position_and_dimension(position, dimension);
                m_property_bar.repaint();
                m_property_bar.size_observer_set().resized()();
            }
            {
                const position_type position(left_type(0), top_type(0));
                const dimension_type dimension(
                    window_width > property_bar_width ? window_width - property_bar_width : width_type(0),
                    window_height
                );
                m_diagram_picture_box.set_position_and_dimension(position, dimension);
                m_view.update_dimension();
                m_diagram_picture_box.update_scroll_bars(
                    m_view.dimension(), m_view.page_size(m_diagram_picture_box.client_dimension())
                );
                m_diagram_picture_box.repaint();
            }
        }


    private:
        // types

        typedef typename abstract_window_type::window_state_type window_state_type;

        typedef typename diagram_picture_box_type::base_type::base_type control_type;

        typedef typename control_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename control_type::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;


        // variables

        view_type& m_view;

        abstract_window_type& m_window;

        diagram_picture_box_type& m_diagram_picture_box;

        property_bar_type& m_property_bar;


    };


    /*!
        \brief The class template for a window closing observer of the main window.

        \tparam AbstractWindow  An abstract window type.
        \tparam ConfirmFileSave A file save confirmation type.
        \tparam Settings        A settings type.
    */
    template <typename AbstractWindow, typename ConfirmFileSave, typename Settings>
    class window_closing
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;

        //! The settings type.
        typedef Settings settings_type;


        // constructors and destructor

        /*!
            \brief Creates a window closing observer of the main window.

            \param window            A window.
            \param confirm_file_save A file save confirmation.
            \param settings          Settings.
        */
        window_closing(
            abstract_window_type&         window,
            const confirm_file_save_type& confirm_file_save,
            settings_type&                settings
        )
        :
        m_window(window),
        m_confirm_file_save(confirm_file_save),
        m_settings(settings)
        {}


        // functions

        /*!
            \brief Called when the main window is closing.

            \param cancel Set true to cancel the window closing.
        */
        void operator()(bool& cancel)
        const
        {
            cancel = !m_confirm_file_save(m_window);

            if (!cancel)
            {
                m_settings.set_main_window_dimension(m_window.normal_dimension());
                m_settings.set_main_window_maximized(m_window.window_state() == window_state_type::maximized);
            }
        }


    private:
        // types

        typedef typename abstract_window_type::window_state_type window_state_type;


        // variables

        abstract_window_type& m_window;

        const confirm_file_save_type& m_confirm_file_save;

        settings_type& m_settings;


    };


}}}


#endif
