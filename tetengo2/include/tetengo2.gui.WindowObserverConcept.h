/*! \file
    \brief The definition of tetengo2::gui::WindowObserverConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WINDOWOBSERVERCONCEPT_H)
#define TETENGO2_GUI_WINDOWOBSERVERCONCEPT_H

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for window observeres.

        \tparam WindowObserver A window observer type.
    */
    template <typename WindowObserver>
    class WindowObserverConcept
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(WindowObserverConcept)
        {
            m_window_observer.destroyed();
        }

        
    private:
        // variables

        WindowObserver m_window_observer;


#endif
    };


}}

#endif
