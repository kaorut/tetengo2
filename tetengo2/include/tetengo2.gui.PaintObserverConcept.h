/*! \file
    \brief The definition of tetengo2::gui::PaintObserverConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_PAINTOBSERVERCONCEPT_H)
#define TETENGO2_GUI_PAINTOBSERVERCONCEPT_H

#include <cstddef>

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for paint observeres.

        \tparam PaintObserver A paint observer type.
    */
    template <typename PaintObserver>
    class PaintObserverConcept
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename PaintObserver::canvas_type canvas_type;


        // usage checks

        BOOST_CONCEPT_USAGE(PaintObserverConcept)
        {
            canvas_type* const p_canvas = NULL;
            m_paint_observer.paint(p_canvas);
        }

        
    private:
        // variables

        PaintObserver m_paint_observer;


#endif
    };


}}

#endif
