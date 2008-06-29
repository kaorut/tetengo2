/*! \file
    \brief The definition of tetengo2::gui::WindowConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WINDOWCONCEPT_H)
#define TETENGO2_GUI_WINDOWCONCEPT_H

//#include <memory>

//#include <boost/concept_check.hpp>

#include "tetengo2.gui.WidgetConcept.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for windows.

        \tparam Window A window type.
    */
    template <typename Window>
    class WindowConcept :
        private boost::DefaultConstructible<Window>,
        private WidgetConcept<Window>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Window::window_observer_type window_observer_type;


        // usage checks

        BOOST_CONCEPT_USAGE(WindowConcept)
        {
            std::auto_ptr<window_observer_type> p_window_observer;
            m_window.add_window_observer(p_window_observer);
        }

        
    private:
        // variables

        Window m_window;


#endif
    };


}}

#endif
