/*! \file
    \brief The definition of tetengo2::gui::GuiInitializerFinalizerConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIINITIALIZERFINALIZERCONCEPT_H)
#define TETENGO2_GUI_GUIINITIALIZERFINALIZERCONCEPT_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for GUI initialization and
               finalization managers.

        \param GuiInitializerFinalizer A GUI initialization and finalization
                                       manager type.
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
