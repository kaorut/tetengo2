/*! \file
    \brief The definition of tetengo2::GuiFactoryConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_GUIFACTORYCONCEPT_H)
#define TETENGO2_GUI_GUIFACTORYCONCEPT_H

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for handles.

        \param Handle A handle type.
    */
    template <typename GuiFactory>
    class GuiFactoryConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a handle.
        */
        void constraints()
        {
            typedef typename GuiFactory::initializer_finalizer_type t1;
            typedef typename GuiFactory::window_type                t2;
            //typedef typename GuiFactory::message_loop_type          t3;
            //typedef typename GuiFactory::quit_message_loop_type     t4;
            //typedef typename GuiFactory::alert_type                 t5;


        }


    };


}}

#endif
