/*! \file
    \brief The definition of bobura::message::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOW_H)
#define BOBURA_MESSAGE_MAINWINDOW_H

#include <cassert>
//#include <cstddef>
#include <iterator>
//#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/rational.hpp>

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
            BOOST_FOREACH (menu_base_type& menu_item, std::make_pair(m_popup_menu.begin(), m_popup_menu.end()))
            {
                assert(i < m_commands.size());
                const command_type* const p_command = m_commands[i];
                if (!p_command)
                    continue;

                menu_item.set_enabled(p_command->enabled(m_model));

                ++i;
            }
        }


    private:
        // types

        typedef typename popup_menu_type::base_type::base_type menu_base_type;


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
        \brief The class template for a window resized observer of the main window.

        \tparam View           A view type.
        \tparam AbstractWindow An abstract window type.
        \tparam Control        A control type.
    */
    template <typename View, typename AbstractWindow, typename Control>
    class window_resized
    {
    public:
        // types

        //! The view type.
        typedef View view_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The control type.
        typedef Control control_type;


        // constructors and destructor

        /*!
            \brief Creates a window resized observer of the main window.

            \param view                A view.
            \param window              A window.
            \param diagram_picture_box A diagram picture box.
        */
        window_resized(const view_type& view, abstract_window_type& window, control_type& diagram_picture_box)
        :
        m_view(view),
        m_window(window),
        m_diagram_picture_box(diagram_picture_box)
        {}


        // functions

        /*!
            \brief Called when the main window is resized.
        */
        void operator()()
        const
        {
            m_diagram_picture_box.set_position_and_dimension(
                position_type(left_type(0), top_type(0)), m_window.client_dimension()
            );

            update_scroll_bars();
        }


    private:
        // types

        typedef typename control_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename control_type::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename control_type::scroll_bar_type::size_type scroll_bar_size_type;


        // variables

        const view_type& m_view;

        abstract_window_type& m_window;

        control_type& m_diagram_picture_box;


        // functions

        void update_scroll_bars()
        const
        {
            assert(m_diagram_picture_box.vertical_scroll_bar());
            assert(m_diagram_picture_box.horizontal_scroll_bar());
            
            const dimension_type page_size = m_view.page_size(m_diagram_picture_box.client_dimension());
            const scroll_bar_size_type page_width =
                boost::rational_cast<scroll_bar_size_type>(
                    tetengo2::gui::dimension<dimension_type>::width(page_size).value()
                );
            const scroll_bar_size_type page_height =
                boost::rational_cast<scroll_bar_size_type>(
                    tetengo2::gui::dimension<dimension_type>::height(page_size).value()
                );

            const width_type view_width = tetengo2::gui::dimension<dimension_type>::width(m_view.dimension());
            const height_type view_height = tetengo2::gui::dimension<dimension_type>::height(m_view.dimension());
            const scroll_bar_size_type width = boost::rational_cast<scroll_bar_size_type>(view_width.value()) - 1;
            const scroll_bar_size_type height = boost::rational_cast<scroll_bar_size_type>(view_height.value()) - 1;

            const scroll_bar_size_type previous_width =
                m_diagram_picture_box.horizontal_scroll_bar()->range().second;
            const scroll_bar_size_type previous_height = m_diagram_picture_box.vertical_scroll_bar()->range().second;

            if (view_height > 0 && 0 < page_height && page_height <= height)
            {
                m_diagram_picture_box.vertical_scroll_bar()->set_enabled(true);
                m_diagram_picture_box.vertical_scroll_bar()->set_range(std::make_pair(0U, height));
                m_diagram_picture_box.vertical_scroll_bar()->set_page_size(page_height);
                if (m_diagram_picture_box.vertical_scroll_bar()->position() + page_height > height)
                {
                    const scroll_bar_size_type new_position = height - page_height + 1;
                    m_diagram_picture_box.vertical_scroll_bar()->set_position(new_position);
                    m_diagram_picture_box.vertical_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
                }
                else if (previous_height > 0 && previous_height != height)
                {
                    const scroll_bar_size_type new_position =
                        m_diagram_picture_box.vertical_scroll_bar()->position() * height / previous_height;
                    m_diagram_picture_box.vertical_scroll_bar()->set_position(new_position);
                    m_diagram_picture_box.vertical_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
                }
            }
            else
            {
                if (view_height <= page_height)
                {
                    const scroll_bar_size_type new_position = 0;
                    m_diagram_picture_box.vertical_scroll_bar()->set_position(new_position);
                    m_diagram_picture_box.vertical_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
                }
                m_diagram_picture_box.vertical_scroll_bar()->set_enabled(false);
            }

            if (view_width > 0 && 0 < page_width && page_width <= width)
            {
                m_diagram_picture_box.horizontal_scroll_bar()->set_enabled(true);
                m_diagram_picture_box.horizontal_scroll_bar()->set_range(std::make_pair(0U, width));
                m_diagram_picture_box.horizontal_scroll_bar()->set_page_size(page_width);
                const scroll_bar_size_type pos = m_diagram_picture_box.horizontal_scroll_bar()->position(); pos;
                if (m_diagram_picture_box.horizontal_scroll_bar()->position() + page_width > width)
                {
                    const scroll_bar_size_type new_position = width - page_width + 1;
                    m_diagram_picture_box.horizontal_scroll_bar()->set_position(new_position);
                    m_diagram_picture_box.horizontal_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
                }
                else if (previous_width > 0 && previous_width != width)
                {
                    const scroll_bar_size_type new_position =
                        m_diagram_picture_box.horizontal_scroll_bar()->position() * width / previous_width;
                    m_diagram_picture_box.horizontal_scroll_bar()->set_position(new_position);
                    m_diagram_picture_box.horizontal_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
                }
            }
            else
            {
                if (view_width <= page_width)
                {
                    const scroll_bar_size_type new_position = 0;
                    m_diagram_picture_box.horizontal_scroll_bar()->set_position(new_position);
                    m_diagram_picture_box.horizontal_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
                }
                m_diagram_picture_box.horizontal_scroll_bar()->set_enabled(false);
            }
        }


    };


    /*!
        \brief The class template for a window closing observer of the main window.

        \tparam AbstractWindow  An abstract window type.
        \tparam ConfirmFileSave A file save confirmation type.
    */
    template <typename AbstractWindow, typename ConfirmFileSave>
    class window_closing
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The file save confirmation type.
        typedef ConfirmFileSave confirm_file_save_type;


        // constructors and destructor

        /*!
            \brief Creates a window closing observer of the main window.

            \param window            A window.
            \param confirm_file_save A file save confirmation.
        */
        window_closing(abstract_window_type& window, const confirm_file_save_type& confirm_file_save)
        :
        m_window(window),
        m_confirm_file_save(confirm_file_save)
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
        }


    private:
        // variables

        abstract_window_type& m_window;

        const confirm_file_save_type& m_confirm_file_save;


    };


}}}


#endif
