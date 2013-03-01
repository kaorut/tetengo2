/*! \file
    \brief The definition of bobura::message::diagram_picture_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H)
#define BOBURA_MESSAGE_DIAGRAMPICTUREBOX_H

#include <cassert>
#include <functional>

//#include <boost/rational.hpp>

#include <tetengo2.gui.measure.h>


namespace bobura { namespace message { namespace diagram_picture_box
{
    /*!
        \brief The class template for a mouse pressed observer of the picture box.

        \tparam PictureBox A picture box type.
    */
    template <typename PictureBox>
    class mouse_pressed
    {
    public:
        // types

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The position type.
        typedef typename picture_box_type::position_type position_type;

        //! The button kind type.
        typedef typename picture_box_type::mouse_observer_set_type::mouse_button_type mouse_button_type;

        //! The set-mouse-capture function type.
        typedef std::function<void ()> set_mouse_capture_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse pressed observer of the picture box.

            \param set_mouse_capture A set-mouse-capture function.
        */
        explicit mouse_pressed(const set_mouse_capture_type& set_mouse_capture)
        :
        m_set_mouse_capture(set_mouse_capture)
        {}


        // functions

        /*!
            \brief Called when the mouse button is pressed.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void operator()(
            const typename mouse_button_type::enum_t button,
            const position_type&                     position,
            const bool                               shift,
            const bool                               control,
            const bool                               meta
        )
        const
        {
            m_set_mouse_capture();
        }


    private:
        // variables

        set_mouse_capture_type m_set_mouse_capture;


    };


    /*!
        \brief The class template for a mouse released observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam View       A view type.
    */
    template <typename PictureBox, typename View>
    class mouse_released
    {
    public:
        // types

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The position type.
        typedef typename picture_box_type::position_type position_type;

        //! The button kind type.
        typedef typename picture_box_type::mouse_observer_set_type::mouse_button_type mouse_button_type;

        //! The view type.
        typedef View view_type;

        //! The release-mouse-capture function type.
        typedef std::function<bool ()> release_mouse_capture_type;


        // constructors and destructor

        /*!
            \brief Creates a mouse released observer of the picture box.

            \param release_mouse_capture A set-mouse-capture function.
            \param view                  A view.
        */
        mouse_released(const release_mouse_capture_type& release_mouse_capture, view_type& view)
        :
        m_release_mouse_capture(release_mouse_capture),
        m_view(view)
        {}


        // functions

        /*!
            \brief Called when the mouse button is released.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        void operator()(
            const typename mouse_button_type::enum_t button,
            const position_type&                     position,
            const bool                               shift,
            const bool                               control,
            const bool                               meta
        )
        const
        {
            if (m_release_mouse_capture())
            {

            }
        }


    private:
        // variables

        release_mouse_capture_type m_release_mouse_capture;

        view_type& m_view;


    };


    /*!
        \brief The class template for a mouse wheel observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam View       A view type.
        \tparam ViewZoom   A view zoom type.
    */
    template <typename PictureBox, typename View, typename ViewZoom>
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

        //! The view zoom type.
        typedef ViewZoom view_zoom_type;


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
            const delta_type&                     delta,
            const typename direction_type::enum_t direction,
            const bool                            shift,
            const bool                            control,
            const bool                            meta
        )
        const
        {
            const delta_type adjusted_delta =
                direction == picture_box_type::mouse_observer_set_type::direction_type::horizontal ? delta : -delta;

            if (!control && !meta)
                scroll(adjusted_delta, is_vertical(direction, shift));
            else if (control && !meta)
                zoom(adjusted_delta, is_vertical(direction, shift));
        }


    private:
        // types

        typedef typename picture_box_type::scroll_bar_type::size_type scroll_bar_size_type;


        // variables

        picture_box_type& m_picture_box;

        view_type& m_view;


        // functions

        bool is_vertical(const typename direction_type::enum_t direction, const bool shift)
        const
        {
            return
                (!shift && direction == picture_box_type::mouse_observer_set_type::direction_type::vertical) ||
                (shift && direction == picture_box_type::mouse_observer_set_type::direction_type::horizontal);
        }

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

        void zoom(const delta_type delta, const bool vertical)
        const
        {
            view_zoom_type zoom(m_picture_box, m_view);

            if (vertical)
            {
                if (delta > 0)
                    zoom.vertically_zoom_in(false);
                else
                    zoom.vertically_zoom_out(false);
            }
            else
            {
                if (delta > 0)
                    zoom.horizontally_zoom_in(false);
                else
                    zoom.horizontally_zoom_out(false);
            }
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
        paint_paint(const picture_box_type& picture_box, view_type& view)
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
            m_view.draw_on(
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

        view_type& m_view;


    };


    /*!
        \brief The class template for a scroll bar observer of the picture box.

        \tparam PictureBox A picture box type.
        \tparam View       A view type.
    */
    template <typename PictureBox, typename View>
    class scroll_bar_scrolled
    {
    public:
        // types

        //! The picture box type.
        typedef PictureBox picture_box_type;

        //! The size type.
        typedef typename picture_box_type::scroll_bar_type::size_type size_type;

        //! The view type.
        typedef View view_type;

        // constructors and destructor

        /*!
            \brief Creates a scroll bar observer of the picture box.

            \param picture_box A picture box.
            \param view        A view.
        */
        scroll_bar_scrolled(const picture_box_type& picture_box, view_type& view)
        :
        m_picture_box(picture_box),
        m_view(view)
        {}


        // functions

        /*!
            \brief Called when the scroll bar is scrolled.

            \param new_position A new position.
        */
        void operator()(const size_type new_position)
        const
        {
            m_view.update_dimension();
            m_picture_box.repaint();
        }


    private:
        // variables

        const picture_box_type& m_picture_box;

        view_type& m_view;


    };


}}}


#endif
