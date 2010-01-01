/*! \file
    \brief The definition of concept_tetengo2::gui::MenuObserver.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUOBSERVER_H)
#define CONCEPTTETENGO2_GUI_MENUOBSERVER_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu observer.

        \tparam Type A type.
    */
    template <typename Type>
    class MenuObserver
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(MenuObserver)
        {
            m_object.selected();
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
