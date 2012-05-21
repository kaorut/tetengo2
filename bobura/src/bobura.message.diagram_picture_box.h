/*! \file
    \brief The definition of bobura::message::diagram_picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H)
#define BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H

#include <tetengo2.gui.measure.h>


namespace bobura { namespace message { namespace diagram_picture_box
{
    /*!
        \brief The class template for a paint observer of the picture box.

        \tparam Canvas     A canvas type.
        \tparam PictureBox A picture box type.
        \tparam View       A view type.
    */
    template <typename Canvas, typename PictureBox, typename View>
    class paint_paint
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The view type.
        typedef View view_type;


        // constructors and destructor

        /*!
            \brief Creates a paint observer of the picture box.

            \param picture_box A picture box.
            \param view        A view.
        */
        explicit paint_paint(const picture_box_type& picture_box, const view_type& view)
        :
        m_picture_box(picture_box),
        m_view(view)
        {}


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas)
        const
        {
            m_view.draw_to(canvas, m_picture_box.client_dimension());
        }


    private:
        // variables

        const picture_box_type& m_picture_box;

        const view_type& m_view;


    };


}}}


#endif
