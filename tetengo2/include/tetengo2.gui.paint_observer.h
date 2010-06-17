/*! \file
    \brief The definition of tetengo2::gui::paint_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_PAINTOBSERVER_H)
#define TETENGO2_GUI_PAINTOBSERVER_H

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>

#include "concept_tetengo2.gui.Canvas.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The base class template for a paint observer.

        \tparam Canvas A canvas type. It must conform to
                       concept_tetengo2::gui::Canvas<Canvas>.
    */
    template <typename Canvas>
    class paint_observer :
        public boost::signals::trackable, private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Canvas<Canvas>));


    public:
        // types

        //! \return The canvas type.
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
            \brief Called when it is necessary to repaint the window.

            \param p_canvas The pointer to the canvas.
        */
        virtual void paint(canvas_type* p_canvas)
        {}


    };


}}

#endif
