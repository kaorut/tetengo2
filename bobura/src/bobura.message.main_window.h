/*! \file
    \brief The definition of bobura::message::menu_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOWOBSERVERS_H)
#define BOBURA_MESSAGE_MAINWINDOWOBSERVERS_H

#include <functional>
#include <utility>

#include <tetengo2.text.h>
#include <tetengo2.gui.menu_observer.h>


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

        //! \copydoc tetengo2::gui::menu_observer::selected
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
        
        \tparam Canvas A canvas type.
    */
    template <typename Canvas>
    class paint : public std::unary_function<Canvas, void>
    {
    public:
        // types

        //! \return The canvas type.
        typedef Canvas canvas_type;


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas)
        const
        {
            const font_type& dialog_font = font_type::dialog_font();

            canvas.draw_text(dialog_font.family(), std::make_pair(32, 32));

#if defined(_MSC_VER)
            canvas.set_font(
                font_type(
                    string_type(TETENGO2_TEXT("‚Ý‚©‚¿‚á‚ñ")),
                    64,
                    false,
                    true,
                    true,
                    false
                )
            );

            canvas.draw_text(
                string_type(TETENGO2_TEXT("‚ ‚¢‚¤‚¦‚¨")),
                std::make_pair(32, 64)
            );
#endif
        }


    private:
        typedef typename canvas_type::string_type string_type;

        typedef typename canvas_type::font_type font_type;


    };


}}}


#endif
