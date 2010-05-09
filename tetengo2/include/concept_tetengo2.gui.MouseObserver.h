/*! \file
    \brief The definition of concept_tetengo2::gui::MouseObserver.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MOUSEOBSERVER_H)
#define CONCEPTTETENGO2_GUI_MOUSEOBSERVER_H //!< !! Include Guard !!

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a mouse observer.

        \tparam Type A type.
    */
    template <typename Type>
    class MouseObserver
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(MouseObserver)
        {
            m_object.clicked();
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
