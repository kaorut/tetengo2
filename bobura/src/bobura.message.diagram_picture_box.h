/*! \file
    \brief The definition of bobura::message::diagram_picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H)
#define BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H

#include <cassert>

#include <tetengo2.gui.measure.h>


namespace bobura { namespace message { namespace diagram_picture_box
{
    /*!
        \brief The class template for a mouse wheel observer of the picture box.

        \tparam PictureBox A picture box type.
    */
    template <typename PictureBox>
    class mouse_wheeled
    {
    public:
        // types

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The delta type.
        typedef typename picture_box_type::mouse_observer_set_type::delta_type delta_type;

        //! The direction type.
        typedef typename picture_box_type::mouse_observer_set_type::direction_type direction_type;


        // constructors and destructor

        explicit mouse_wheeled(picture_box_type& picture_box)
        :
        m_picture_box(picture_box)
        {}


        // functions

        /*!
            \brief Called when the mouse wheel is wheeled.

            \param delta     A delta.
            \param direction A direction.
            \param shift     True when shift key is pressed.
            \param control   True when control key is pressed.
            \param meta      True when meta key is pressed.
        */
        void operator()(
            const delta_type&    delta,
            const direction_type direction,
            const bool           shift,
            const bool           control,
            const bool           meta
        )
        const
        {

        }


    private:
        // variables

        picture_box_type& m_picture_box;


    };

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
        paint_paint(const picture_box_type& picture_box, const view_type& view)
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
            assert(m_picture_box.vertical_scroll_bar());
            assert(m_picture_box.horizontal_scroll_bar());
            m_view.draw_to(
                canvas,
                m_picture_box.client_dimension(),
                to_position(
                    m_picture_box.horizontal_scroll_bar()->tracking_position(),
                    m_picture_box.vertical_scroll_bar()->tracking_position()
                )
            );
        }


    private:
        // types

        typedef typename picture_box_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename picture_box_type::scroll_bar_type::size_type scroll_bar_size_type;


        // static functions

        static position_type to_position(const scroll_bar_size_type left, const scroll_bar_size_type top)
        {
            return position_type(left_type(left), top_type(top));
        }


        // variables

        const picture_box_type& m_picture_box;

        const view_type& m_view;


    };


    /*!
        \brief The class template for a scroll bar observer of the picture box.

        \tparam PictureBox A picture box type.
    */
    template <typename PictureBox>
    class scroll_bar_scrolled
    {
    public:
        // types

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The size type.
        typedef typename picture_box_type::scroll_bar_type::size_type size_type;


        // constructors and destructor

        /*!
            \brief Creates a scroll bar observer of the picture box.

            \param picture_box A picture box.
        */
        explicit scroll_bar_scrolled(const picture_box_type& picture_box)
        :
        m_picture_box(picture_box)
        {}


        // functions

        /*!
            \brief Called when the scroll bar is scrolled.

            \param new_position A new position.
        */
        void operator()(const size_type new_position)
        const
        {
            m_picture_box.repaint();
        }


    private:
        // variables

        const picture_box_type& m_picture_box;


    };


}}}


#endif
