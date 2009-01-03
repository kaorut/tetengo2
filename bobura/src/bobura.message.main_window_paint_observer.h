/*! \file
    \brief The definition of bobura::message::main_window_paint_observer.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAININDOWPAINTOBSERVER_H)
#define BOBURA_MESSAGE_MAINWINDOWPAINTOBSERVER_H

#include <utility>

#include <tetengo2.gui.paint_observer.h>


namespace bobura { namespace message
{
    /*!
        \brief The class template for a paint observer of the main window.

        \tparam Canvas A canvas type of the main window. It must conform to
                       concept_tetengo2::gui::Canvas<Canvas>.
    */
    template <typename Canvas>
    class main_window_paint_observer :
        public tetengo2::gui::paint_observer<Canvas>
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a paint observer of the main window.
        */
        main_window_paint_observer()
        {}

        /*!
            \brief Destroys the paint observer of the main window.
        */
        virtual ~main_window_paint_observer()
        throw ()
        {}


        // functions

        /*!
            \brief Called when it is necessary to repaint the window.

            \param p_canvas The pointer to the canvas.
        */
        virtual void paint(canvas_type* p_canvas)
        {
            p_canvas->draw_text(L"‚±‚ñ‚É‚¿‚ÍA¢ŠEI", std::make_pair(64, 32));
            p_canvas->draw_text(L"Hello, world!", std::make_pair(96, 64));
        }


    };


}}

#endif
