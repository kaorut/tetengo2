/*! \file
    \brief The definition of concept_tetengo2::gui::Dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_DIALOG_H)
#define CONCEPTTETENGO2_GUI_DIALOG_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Window.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a dialog.

        \tparam Type A type.
    */
    template <typename Type>
    class Dialog : private Window<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(Dialog)
        {
            m_object.do_modal();
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
