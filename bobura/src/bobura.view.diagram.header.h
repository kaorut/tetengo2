/*! \file
    \brief The definition of bobura::view::diagram::header.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_HEADER_H)
#define BOBURA_VIEW_DIAGRAM_HEADER_H

#include <boost/noncopyable.hpp>

#include <tetengo2.gui.measure.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a header in the diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class header : boost::noncopyable
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;


        // constructors and destructor

        /*!
            \brief Creates a header.

            \param model  A model.
            \param canvas A canvas.
        */
        header(const model_type& model, const canvas_type& canvas)
        :
        m_model(model),
        m_position(left_type(0), top_type(0)),
        m_dimension(width_type(0), height_type(0))
        {}


        // functions

        /*!
            \brief Draws to the canvas.

            \param canvas A canvas.
        */
        void draw_to(canvas_type& canvas)
        const
        {

        }


    private:
        // types

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;


        // variables

        const model_type& m_model;

        const position_type m_position;

        const dimension_type m_dimension;


    };


}}}


#endif
