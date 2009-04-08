/*! \file
    \brief The definition of concept_tetengo2::gui::Button.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_BUTTON_H)
#define CONCEPTTETENGO2_GUI_BUTTON_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Widget.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a button.

        \tparam Type A type.
    */
    template <typename Type>
    class Button : private Widget<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::widget_type widget_type;

        typedef typename Type::mouse_observer_type mouse_observer_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Button)
        {
            std::auto_ptr<mouse_observer_type> p_mouse_observer;
            m_object.add_mouse_observer(p_mouse_observer);
        }


    private:
        // variables

        Type m_object;

        
#endif
    };


}}

#endif
