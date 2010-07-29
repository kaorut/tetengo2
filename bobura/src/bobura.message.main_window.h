/*! \file
    \brief The definition of bobura::message::menu_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOWOBSERVERS_H)
#define BOBURA_MESSAGE_MAINWINDOWOBSERVERS_H

#include <utility>

#include <tetengo2.text.h>
#include <tetengo2.gui.menu_observer.h>
#include <tetengo2.gui.paint_observer.h>


namespace bobura { namespace message { namespace main_window
{
    /*!
        \brief The class template for a menu observer of the main window.
        
        \tparam Command A command type.
    */
    template <typename Command>
    class menu_observer : public tetengo2::gui::menu_observer
    {
    public:
        // types

        //! \return The command type.
        typedef Command command_type;


        // constructors and destructor

        /*!
            \brief Creates a menu observer of the main window.

            \param command A command.
        */
        explicit menu_observer(const command_type& command)
        :
        m_command(command)
        {}

        /*!
            \brief Destroys the menu observer of the main window.
        */
        virtual ~menu_observer()
        throw ()
        {}


        // functions

        //! \copydoc tetengo2::gui::menu_observer::selected.
        virtual void selected()
        {
            m_command();
        }


    private:
        // variables

        const command_type m_command;


    };


    /*!
        \brief The class template for a paint observer of the main window.

        \tparam Canvas A canvas type of the main window. It must conform to
                       concept_tetengo2::gui::Canvas<Canvas>.
    */
    template <typename Canvas>
    class paint_observer : public tetengo2::gui::paint_observer<Canvas>
    {
    public:
        // types

        //! \return The base type.
        typedef tetengo2::gui::paint_observer<Canvas> base_type;

        //! \copydoc tetengo2::gui::paint_observer::canvas_type
        typedef typename base_type::canvas_type canvas_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the main window.
        */
        paint_observer()
        {}

        /*!
            \brief Destroys the paint observer of the main window.
        */
        virtual ~paint_observer()
        throw ()
        {}


        // functions

        /*!
            \brief Called when it is necessary to repaint the window.

            \param p_canvas The pointer to the canvas.
        */
        virtual void paint(canvas_type* p_canvas)
        { 
            const font_type& dialog_font = font_type::dialog_font();

            p_canvas->draw_text(dialog_font.family(), std::make_pair(32, 32));

#if defined(_MSC_VER)
            p_canvas->set_font(
                font_type(
                    string_type(TETENGO2_TEXT("‚Ý‚©‚¿‚á‚ñ")),
                    64,
                    false,
                    true,
                    true,
                    false
                )
            );

            p_canvas->draw_text(
                string_type(TETENGO2_TEXT("‚ ‚¢‚¤‚¦‚¨")), std::make_pair(32, 64)
            );
#endif
        }


    private:
        // types

        typedef typename canvas_type::string_type string_type;

        typedef typename canvas_type::font_type font_type;


    };


}}}


#endif
