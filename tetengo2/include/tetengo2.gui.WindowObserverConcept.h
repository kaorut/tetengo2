/*! \file
    \brief The definition of tetengo2::gui::WindowObserverConcept.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WINDOWOBSERVERCONCEPT_H)
#define TETENGO2_GUI_WINDOWOBSERVERCONCEPT_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for window observeres.

        \param WindowObserver A window observer type.
    */
    template <typename WindowObserver>
    class WindowObserverConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a window observer.
        */
        void constraints()
        {
            m_p_window_observer->destroyed();
        }


    private:
        // variables

        WindowObserver* m_p_window_observer;


    };


}}

#endif
