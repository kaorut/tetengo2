/*! \file
    \brief The definition of bobura::message::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOW_H)
#define BOBURA_MESSAGE_MAINWINDOW_H

#include <boost/rational.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>


namespace bobura { namespace message { namespace main_window
{
    /*!
        \brief The class template for a menu selection observer of the main
               window.

        \tparam Command        A command type.
        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
    */
    template <typename Command, typename Model, typename AbstractWindow>
    class menu_selected
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
            \brief Creates a menu selection observer of the main window.

            \param command A command.
            \param model   A model.
            \param parent  A parent window.
        */
        menu_selected(const command_type& command, model_type& model, abstract_window_type& parent)
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
            m_command(m_model, m_parent);
        }


    private:
        // variables

        command_type m_command;

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

            assert(m_diagram_picture_box.vertical_scroll_bar());
            assert(m_diagram_picture_box.horizontal_scroll_bar());
            const dimension_type view_dimension = m_view.dimension();
            const dimension_type picture_box_client_dimension = m_diagram_picture_box.client_dimension();
            m_diagram_picture_box.vertical_scroll_bar()->set_range(
                std::make_pair(
                    0U,
                    boost::rational_cast<scroll_bar_size_type>(
                        tetengo2::gui::dimension<dimension_type>::height(view_dimension).value()
                    )
                )
            );
            m_diagram_picture_box.vertical_scroll_bar()->set_page_size(
                boost::rational_cast<scroll_bar_size_type>(
                    tetengo2::gui::dimension<dimension_type>::height(picture_box_client_dimension).value()
                )
            );
            m_diagram_picture_box.horizontal_scroll_bar()->set_range(
                std::make_pair(
                    0U,
                    boost::rational_cast<scroll_bar_size_type>(
                        tetengo2::gui::dimension<dimension_type>::width(view_dimension).value()
                    )
                )
            );
            m_diagram_picture_box.horizontal_scroll_bar()->set_page_size(
                boost::rational_cast<scroll_bar_size_type>(
                    tetengo2::gui::dimension<dimension_type>::width(picture_box_client_dimension).value()
                )
            );
        }


    private:
        // types

        typedef typename control_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename control_type::dimension_type dimension_type;

        typedef typename control_type::scroll_bar_type::size_type scroll_bar_size_type;


        // variables

        const view_type& m_view;

        abstract_window_type& m_window;

        control_type& m_diagram_picture_box;


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
            cancel = m_confirm_file_save(m_window);
        }


    private:
        // variables

        abstract_window_type& m_window;

        const confirm_file_save_type& m_confirm_file_save;


    };


}}}


#endif
