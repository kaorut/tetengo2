/*! \file
    \brief The definition of tetengo2::GuiInitializerFinalizerConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIINITIALIZERFINALIZERCONCEPT_H)
#define TETENGO2_GUI_GUIINITIALIZERFINALIZERCONCEPT_H

#include <memory>

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for canvases.

        \param GuiInitializerFinalizer A canvas type.
    */
    template <typename GuiInitializerFinalizer>
    class GuiInitializerFinalizerConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a GUI intialization and
                   finalization manager.
        */
        void constraints()
        {}


    };


}}

#endif
