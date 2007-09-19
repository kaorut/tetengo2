/*! \file
    \brief The definition of tetengo2::CanvasConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CANVASCONCEPT_H)
#define TETENGO2_GUI_CANVASCONCEPT_H

#include <memory>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for canvases.

        \param Canvas A canvas type.
    */
    template <typename Canvas>
    class CanvasConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a GUI object factory.
        */
        void constraints()
        {

        }

        /*!
            \brief Checks the const constraints on a GUI object factory.
        */
        void const_constraints(const Canvas& canvas)
        {

        }


    private:
        // variables

        Canvas* m_p_canvas;


    };


}}

#endif
