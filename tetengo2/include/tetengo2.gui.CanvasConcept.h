/*! \file
    \brief The definition of tetengo2::gui::CanvasConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_CANVASCONCEPT_H)
#define TETENGO2_GUI_CANVASCONCEPT_H

#include <memory>

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
    public:
        // functions

        /*!
            \brief Checks the constraints on a canvas.
        */
        void constraints()
        {
            typedef typename Canvas::handle_type handle_type;
            typedef typename Canvas::size_type size_type;
            typedef typename Canvas::point_type point_type;
            typedef typename Canvas::rectangle_type rectangle_type;
            typedef typename Canvas::string_type string_type;

            m_p_canvas->draw_text(string_type(), point_type());

            const_constraints(*m_p_canvas);
        }

        /*!
            \brief Checks the const constraints on a canvas.

            \param canvas A constant object.
        */
        void const_constraints(const Canvas& canvas)
        {
            const typename Canvas::handle_type handle = canvas.handle();
            boost::ignore_unused_variable_warning(handle);
        }


    private:
        // variables

        Canvas* m_p_canvas;


    };


}}

#endif
