/*! \file
    \brief The definition of concept_tetengo2::gui::Window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_WINDOW_H)
#define CONCEPTTETENGO2_GUI_WINDOW_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.AbstractWindow.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a window.

        \tparam Type A type.
    */
    template <typename Type>
    class Window : private AbstractWindow<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::abstract_window_type abstract_window_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Window)
        {}


#endif
    };


}}

#endif
