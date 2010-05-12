/*! \file
    \brief The definition of concept_tetengo2::gui::Button.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_BUTTON_H)
#define CONCEPTTETENGO2_GUI_BUTTON_H

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

        typedef typename Type::base_type base_type;

        typedef typename Type::style_type style_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Button)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const style_type style = object.style();
            boost::ignore_unused_variable_warning(style);
        }


    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
