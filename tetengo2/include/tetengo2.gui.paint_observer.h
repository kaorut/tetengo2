/*! \file
    \brief The definition of tetengo2::gui::paint_observer.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_PAINTOBSERVER_H)
#define TETENGO2_GUI_PAINTOBSERVER_H

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class template for a paint observer.

        \param Canvas A canvas type. It must conform to
                      tetengo2::gui::concepts::CanvasConcept.
    */
    template <typename Canvas>
    class paint_observer :
        public boost::signals::trackable, private boost::noncopyable
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer.
        */
        paint_observer()
        {}

        /*!
            \brief Destroys the paint observer.
        */
        virtual ~paint_observer()
        throw ()
        {}


        // functions

        /*!
            \brief Called when it is necessary to repaint the main window.

            \param p_canvas The pointer to the canvas.
        */
        virtual void paint(const canvas_type* p_canvas)
        {}


    };
}}

#endif
