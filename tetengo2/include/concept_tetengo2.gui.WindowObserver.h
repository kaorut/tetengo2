/*! \file
    \brief The definition of concept_tetengo2::gui::WindowObserver.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_WINDOWOBSERVER_H)
#define CONCEPTTETENGO2_GUI_WINDOWOBSERVER_H

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a window observer.

        \tparam Type A type.
    */
    template <typename Type>
    class WindowObserver
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(WindowObserver)
        {
            m_object.destroyed();
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
