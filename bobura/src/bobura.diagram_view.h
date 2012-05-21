/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <boost/noncopyable.hpp>

namespace bobura
{
   /*!
        \brief The class template for a diagram view.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class diagram_view : private boost::noncopyable
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;


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

        }


    private:
        // variables

        const model_type& m_model;


    };


}

#endif
