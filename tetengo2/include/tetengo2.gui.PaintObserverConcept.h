/*! \file
    \brief The definition of tetengo2::PaintObserverConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_PAINTOBSERVERCONCEPT_H)
#define TETENGO2_GUI_PAINTOBSERVERCONCEPT_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for paint observeres.

        \param PaintObserver A paint observer type.
    */
    template <typename PaintObserver>
    class PaintObserverConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a paint observer.
        */
        void constraints()
        {
            typedef typename PaintObserver::canvas_type canvas_type;

            canvas_type* p_canvas = NULL;
            m_p_paint_observer->paint(p_canvas);
        }


    private:
        // variables

        PaintObserver* m_p_paint_observer;


    };


}}

#endif
