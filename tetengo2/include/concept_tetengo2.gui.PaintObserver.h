/*! \file
    \brief The definition of concept_tetengo2::gui::PaintObserver.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_PAINTOBSERVER_H)
#define CONCEPTTETENGO2_GUI_PAINTOBSERVER_H //!< !! Include Guard !!

#include <cstddef>

#include <boost/concept_check.hpp>


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a paint observer.

        \tparam Type A type.
    */
    template <typename Type>
    class PaintObserver
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::canvas_type canvas_type;


        // usage checks

        BOOST_CONCEPT_USAGE(PaintObserver)
        {
            canvas_type* const p_canvas = NULL;
            m_object.paint(p_canvas);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
