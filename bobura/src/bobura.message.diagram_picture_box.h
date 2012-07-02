/*! \file
    \brief The definition of bobura::message::diagram_picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H)
#define BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H

#include <cassert>

#include <boost/rational.hpp>

#include <tetengo2.gui.measure.h>


namespace bobura { namespace message { namespace diagram_picture_box
{
    /*!
        \brief The class template for a mouse wheel observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam View       A view type.
    */
    template <typename PictureBox, typename View>
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

        //! The view type.
        typedef View view_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse wheel observer of the picture box.

            \param picture_box A picture box.
            \param view        A view.
        */
        mouse_wheeled(picture_box_type& picture_box, view_type& view)
        :
        m_picture_box(picture_box),
        m_view(view)
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
            if (!control && !meta)
            {
                scroll(
                    direction == picture_box_type::mouse_observer_set_type::direction_horizontal ? delta : -delta,
                    is_vertical(direction, shift)
                );
            }
        }


    private:
        // types

        typedef typename picture_box_type::scroll_bar_type::size_type scroll_bar_size_type;


        // variables

        picture_box_type& m_picture_box;

        view_type& m_view;


        // functions

        void scroll(const delta_type& delta, const bool vertical)
        const
        {
            if (vertical)
            {
                assert(m_picture_box.vertical_scroll_bar());
                if (!m_picture_box.vertical_scroll_bar()->enabled())
                    return;

                const scroll_bar_size_type new_position =
                    calculate_new_position(*m_picture_box.vertical_scroll_bar(), delta);
                m_picture_box.vertical_scroll_bar()->set_position(new_position);
                m_picture_box.vertical_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
            }
            else
            {
                assert(m_picture_box.horizontal_scroll_bar());
                if (!m_picture_box.horizontal_scroll_bar()->enabled())
                    return;

                const scroll_bar_size_type new_position =
                    calculate_new_position(*m_picture_box.horizontal_scroll_bar(), delta);
                m_picture_box.horizontal_scroll_bar()->set_position(new_position);
                m_picture_box.horizontal_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
            }
        }

        bool is_vertical(const direction_type direction, const bool shift)
        const
        {
            return
                (!shift && direction == picture_box_type::mouse_observer_set_type::direction_vertical) ||
                (shift && direction == picture_box_type::mouse_observer_set_type::direction_horizontal);
        }

        scroll_bar_size_type calculate_new_position(
            const typename picture_box_type::scroll_bar_type& scroll_bar,
            const delta_type&                                 delta
        )
        const
        {
            typedef typename delta_type::int_type delta_int_type;
            delta_int_type int_delta = boost::rational_cast<delta_int_type>(delta * 3);
            if (int_delta == 0)
            {
                if (delta > 0)
                    ++int_delta;
                else
                    --int_delta;
            }
            const delta_int_type new_position = scroll_bar.position() + int_delta;

            if (new_position < static_cast<delta_int_type>(scroll_bar.range().first))
                return scroll_bar.range().first;
            if (new_position > static_cast<delta_int_type>(scroll_bar.range().second - scroll_bar.page_size() + 1))
                return scroll_bar.range().second - scroll_bar.page_size() + 1;

            return new_position;
        }


    };

    /*!
        \brief The class template for a key down observer of the picture box.

        \tparam PictureBox A picture box type.
    */
    template <typename PictureBox>
    class keyboard_key_down
    {
    public:
        // types

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The virtual key type.
        typedef typename picture_box_type::keyboard_observer_set_type::virtual_key_type virtual_key_type;


        // constructors and destructor

        /*!
            \brief Creates a key down observer of the picture box.

            \param picture_box A picture box.
        */
        explicit keyboard_key_down(picture_box_type& picture_box)
        :
        m_picture_box(picture_box)
        {}


        // functions

        /*!
            \brief Called when a key is pressed down.

            \param virtual_key A virtual key.
            \param shift       True when shift key is pressed.
            \param control     True when control key is pressed.
            \param meta        True when meta key is pressed.
        */
        void operator()(const virtual_key_type& virtual_key, const bool shift, const bool control, const bool meta)
        const
        {
            if (
                virtual_key == virtual_key_type::left() ||
                virtual_key == virtual_key_type::right() ||
                virtual_key == virtual_key_type::up() ||
                virtual_key == virtual_key_type::down() ||
                virtual_key == virtual_key_type::page_up() ||
                virtual_key == virtual_key_type::page_down() ||
                virtual_key == virtual_key_type::home() ||
                virtual_key == virtual_key_type::end()
            )
            {
                if (!control && !meta)
                    scroll(virtual_key, shift);
            }
        }


    private:
        // types

        typedef typename picture_box_type::scroll_bar_type::size_type scroll_bar_size_type;


        // variables

        picture_box_type& m_picture_box;


        // functions

        void scroll(const virtual_key_type& virtual_key, const bool shift)
        const
        {
            const bool vertical = is_vertical(virtual_key, shift);
            if (vertical)
            {
                assert(m_picture_box.vertical_scroll_bar());
                if (!m_picture_box.vertical_scroll_bar()->enabled())
                    return;

                const scroll_bar_size_type new_position =
                    calculate_new_position(*m_picture_box.vertical_scroll_bar(), virtual_key);
                m_picture_box.vertical_scroll_bar()->set_position(new_position);
                m_picture_box.vertical_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
            }
            else
            {
                assert(m_picture_box.horizontal_scroll_bar());
                if (!m_picture_box.horizontal_scroll_bar()->enabled())
                    return;

                const scroll_bar_size_type new_position =
                    calculate_new_position(*m_picture_box.horizontal_scroll_bar(), virtual_key);
                m_picture_box.horizontal_scroll_bar()->set_position(new_position);
                m_picture_box.horizontal_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
            }
        }

        bool is_vertical(const virtual_key_type& virtual_key, const bool shift)
        const
        {
            if (virtual_key == virtual_key_type::up() || virtual_key == virtual_key_type::down())
            {
                return true;
            }
            else if (
                !shift &&
                (virtual_key == virtual_key_type::page_up() || virtual_key == virtual_key_type::page_down())
            )
            {
                return true;
            }
            else if (!shift && (virtual_key == virtual_key_type::home() || virtual_key == virtual_key_type::end()))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        scroll_bar_size_type calculate_new_position(
            const typename picture_box_type::scroll_bar_type& scroll_bar,
            const virtual_key_type&                           virtual_key
        )
        const
        {
            const scroll_bar_size_type min_position = scroll_bar.range().first;
            const scroll_bar_size_type max_position = scroll_bar.range().second - scroll_bar.page_size() + 1;

            if      (virtual_key == virtual_key_type::home())
            {
                return min_position;
            }
            else if (virtual_key == virtual_key_type::end())
            {
                return max_position;
            }
            else if (virtual_key == virtual_key_type::page_up())
            {
                return
                    scroll_bar.position() > min_position + scroll_bar.page_size() ?
                    scroll_bar.position() - scroll_bar.page_size() : min_position;
            }
            else if (virtual_key == virtual_key_type::page_down())
            {
                return
                    scroll_bar.position() + scroll_bar.page_size() < max_position ?
                    scroll_bar.position() + scroll_bar.page_size() : max_position;
            }
            else if (virtual_key == virtual_key_type::up() || virtual_key == virtual_key_type::left())
            {
                return scroll_bar.position() > min_position + 1 ? scroll_bar.position() - 1 : min_position;
            }
            else
            {
                assert(virtual_key == virtual_key_type::down() || virtual_key == virtual_key_type::right());

                return scroll_bar.position() + 1 < max_position ? scroll_bar.position() + 1 : max_position;
            }
        }


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
