/*! \file
    \brief The definition of concept_tetengo2::gui::Container.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_CONTAINER_H)
#define CONCEPTTETENGO2_GUI_CONTAINER_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Widget.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a container.

        \tparam Type A type.
    */
    template <typename Type>
    class Container : public Widget<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::widgets_type widgets_type;

        typedef typename Type::const_widgets_type const_widgets_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Container)
        {
            const widgets_type widgets = m_object.children();
            boost::ignore_unused_variable_warning(widgets);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const const_widgets_type widgets = object.children();
            boost::ignore_unused_variable_warning(widgets);


        }

        
    private:
        // variables

        Type& m_object;


#endif
    };


}}

#endif
