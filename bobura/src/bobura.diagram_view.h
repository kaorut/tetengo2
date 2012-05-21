/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <boost/noncopyable.hpp>

#include <tetengo2.gui.measure.h>


namespace bobura
{
   /*!
        \brief The class template for a diagram view.

        \tparam Model           A model type.
        \tparam Canvas          A canvas type.
        \tparam SolidBackground A solid background type.
    */
    template <typename Model, typename Canvas, typename SolidBackground>
    class diagram_view : private boost::noncopyable
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The solid background type.
        typedef SolidBackground solid_background_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram view.

            \param model A model.
        */
        explicit diagram_view(const model_type& model)
        :
        m_model(model)
        {}


        // functions

        /*!
            \brief Draws the view.

            \param canvas A canvas.
        */
        void draw_to(canvas_type& canvas)
        const
        {
            const solid_background_type white_background(color_type(255, 255, 255));
            canvas.fill_rectangle(
                position_type(left_type(2), top_type(3)),
                dimension_type(width_type(5), height_type(3)),
                white_background
            );
        }


    private:
        // types

        typedef typename canvas_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename canvas_type::dimension_type dimension_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename solid_background_type::color_type color_type;


        // variables

        const model_type& m_model;


    };


}

#endif
