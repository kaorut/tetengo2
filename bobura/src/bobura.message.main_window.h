/*! \file
    \brief The definition of bobura::message::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOW_H)
#define BOBURA_MESSAGE_MAINWINDOW_H

//#include <cstddef>
#include <memory>
//#include <type_traits>
//#include <utility>

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
        explicit menu_selected(const command_type& command, model_type& model, abstract_window_type& parent)
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
        \brief The class template for a paint observer of the main window.

        \tparam Canvas        A canvas type.
        \tparam Position      A position type.
        \tparam PictureReader A picture reader type.
    */
    template <typename Canvas, typename Position, typename PictureReader>
    class paint_paint
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef Position position_type;

        //! The picture reader type.
        typedef PictureReader picture_reader_type;

        //! The path type.
        typedef typename picture_reader_type::path_type path_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the main window.

            \tparam P A path type.

            \param image_directory_path An image directory path.
        */
        template <typename P>
        explicit paint_paint(
            P&& image_directory_path,
            typename std::enable_if<std::is_convertible<P, path_type>::value>::type* = NULL
        )
        :
        m_image_directory_path(std::forward<P>(image_directory_path))
        {}


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas)
        const
        {
            //picture_reader_type reader(
            //    m_image_directory_path / typename path_type::string_type(TETENGO2_TEXT("kumakuma.jpg"))
            //);
            //const std::unique_ptr<typename canvas_type::picture_type> p_pic2(reader.read());
            //canvas.paint_picture(*p_pic2, position_type(left_type(0), top_type(0)));

            const font_type& dialog_font = font_type::dialog_font();
            canvas.draw_text(dialog_font.family(), position_type(left_type(2), top_type(2)));

            canvas.set_font(font_type(string_type(TETENGO2_TEXT("Times New Roman")), 64, false, true, true, false));
            canvas.draw_text(string_type(TETENGO2_TEXT("Hello, world")), position_type(left_type(4), top_type(4)));
        }


    private:
        // types

        typedef typename canvas_type::string_type string_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename canvas_type::font_type font_type;


        // variables

        path_type m_image_directory_path;


    };


    /*!
        \brief The class template for a window resized observer of the main window.

        \tparam AbstractWindow An abstract window type.
        \tparam Control        A control type.
    */
    template <typename AbstractWindow, typename Control>
    class window_resized
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The control type.
        typedef Control control_type;


        // constructors and destructor

        /*!
            \brief Creates a window resized observer of the main window.

            \param window              A window.
            \param diagram_picture_box A diagram picture box.
        */
        window_resized(abstract_window_type& window, control_type& diagram_picture_box)
        :
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
            m_diagram_picture_box.set_position(position_type(left_type(0), top_type(0)));
            m_diagram_picture_box.set_dimension(m_window.client_dimension());
        }


    private:
        // types

        typedef typename control_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;


        // variables

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
