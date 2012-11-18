/*! \file
    \brief The definition of bobura::view::diagram::item.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_ITEM_H)
#define BOBURA_VIEW_DIAGRAM_ITEM_H

#include <boost/noncopyable.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view item.

        \tparam Model  A model type.
        \tparam Canvas A canvas type.
    */
    template <typename Model, typename Canvas>
    class item : boost::noncopyable
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The canvas type.
        typedef Canvas canvas_type;


        // constructors and destructor

        /*!
            \brief Destroys the item.
        */
        virtual ~item()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Draws this item on the canvas.

            \param canvas A canvas.
        */
        void draw_on(canvas_type& canvas)
        const
        {
            draw_on_impl(canvas);
        }


    private:
        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const = 0;


    };


}}}


#endif
