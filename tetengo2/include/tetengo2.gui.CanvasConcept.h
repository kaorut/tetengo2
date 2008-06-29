/*! \file
    \brief The definition of tetengo2::gui::CanvasConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CANVASCONCEPT_H)
#define TETENGO2_GUI_CANVASCONCEPT_H

#include <boost/concept_check.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for canvases.

        \tparam Canvas A canvas type.
    */
    template <typename Canvas>
    class CanvasConcept
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Canvas::handle_type handle_type;

        typedef typename Canvas::size_type size_type;

        typedef typename Canvas::point_type point_type;

        typedef typename Canvas::rectangle_type rectangle_type;

        typedef typename Canvas::string_type string_type;


        // usage checks

        BOOST_CONCEPT_USAGE(CanvasConcept)
        {
            m_canvas.draw_text(string_type(), point_type());

            const_constraints(m_canvas);
        }

        void const_constraints(const Canvas& canvas)
        {
            const handle_type handle = canvas.handle();
            boost::ignore_unused_variable_warning(handle);
        }

        
    private:
        // variables

        Canvas m_canvas;


#endif
    };


}}

#endif
