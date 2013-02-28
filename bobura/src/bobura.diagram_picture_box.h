/*! \file
    \brief The definition of bobura::diagram_picture_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMPICTUREBOX_H)
#define BOBURA_DIAGRAMPICTUREBOX_H

#include <cassert>
#include <memory>
//#include <utility>

#include <boost/mpl/at.hpp>
//#include <boost/rational.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.unique.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the diagram picture box.

        \tparam PictureBox      A picture box type.
        \tparam AbstractWindow  An abstract window type.
        \tparam MouseCapture    A mouse capture type.
        \tparam MessageTypeList A message type list.
    */
    template <typename PictureBox, typename AbstractWindow, typename MouseCapture, typename MessageTypeList>
    class diagram_picture_box : public PictureBox
    {
    public:
        // types

        //! The base type.
        typedef PictureBox base_type;

        //! The control type.
        typedef typename base_type::base_type control_type;

        //! The position type.
        typedef typename base_type::position_type position_type;

        //! The dimension type.
        typedef typename base_type::dimension_type dimension_type;

        //! The mouse observer set type.
        typedef typename base_type::mouse_observer_set_type mouse_observer_set_type;

        //! The scroll bar type.
        typedef typename base_type::scroll_bar_type scroll_bar_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The mouse capture type.
        typedef MouseCapture mouse_capture_type;

        //! The message type list type.
        typedef MessageTypeList message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram picture box.

            \param parent A parent.
        */
        explicit diagram_picture_box(abstract_window_type& parent)
        :
        base_type(parent, base_type::scroll_bar_style_type::both),
        m_p_mouse_capture()
        {
            set_observers();
        }

        /*!
            \brief Destroys the diagram picture box.
        */
        virtual ~diagram_picture_box()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Sets a mouse capture.
        */
        void set_mouse_capture()
        {
            assert(!m_p_mouse_capture);
            m_p_mouse_capture = tetengo2::make_unique<mouse_capture_type>(*this);
        }

        /*!
            \brief Releases a mouse capture.
        */
        void release_mouse_capture()
        {
            assert(m_p_mouse_capture);
            m_p_mouse_capture.reset();
        }

        /*!
            \brief Updates the scroll bars.

            \param view_dimension A view dimension.
            \param page_dimension A page dimension.
        */
        void update_scroll_bars(const dimension_type& view_dimension, const dimension_type& page_dimension)
        {
            assert(this->vertical_scroll_bar());
            assert(this->horizontal_scroll_bar());
            
            update_scroll_bar(
                *this->vertical_scroll_bar(),
                tetengo2::gui::dimension<dimension_type>::height(view_dimension),
                boost::rational_cast<scroll_bar_size_type>(
                    tetengo2::gui::dimension<dimension_type>::height(page_dimension).value()
                )
            );
            update_scroll_bar(
                *this->horizontal_scroll_bar(),
                tetengo2::gui::dimension<dimension_type>::width(view_dimension),
                boost::rational_cast<scroll_bar_size_type>(
                    tetengo2::gui::dimension<dimension_type>::width(page_dimension).value()
                )
            );
        }


    private:
        // types

        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename scroll_bar_type::size_type scroll_bar_size_type;


        // variables

        std::unique_ptr<mouse_capture_type> m_p_mouse_capture;


        // functions

        void set_observers()
        {
            this->keyboard_observer_set().key_down().connect(
                typename boost::mpl::at<
                    message_type_list_type, message::diagram_picture_box::type::keyboard_key_down
                >::type(*this)
            );
        }

        template <typename Size>
        void update_scroll_bar(
            scroll_bar_type&           scroll_bar,
            const Size&                view_size,
            const scroll_bar_size_type page_size

        )
        {
            const scroll_bar_size_type size =
                view_size.value() > 0 ? boost::rational_cast<scroll_bar_size_type>(view_size.value()) - 1 : 0;
            const scroll_bar_size_type previous_size = scroll_bar.range().second;

            if (view_size > 0 && 0 < page_size && page_size <= size)
            {
                scroll_bar.set_enabled(true);
                scroll_bar.set_range(std::make_pair(0U, size));
                scroll_bar.set_page_size(page_size);

                if (scroll_bar.position() + page_size > size)
                {
                    const scroll_bar_size_type new_position = size - page_size + 1;
                    scroll_bar.set_position(new_position);
                    scroll_bar.scroll_bar_observer_set().scrolled()(new_position);
                }
                else if (previous_size > 0 && previous_size != view_size.value())
                {
                    const scroll_bar_size_type new_position =
                        calculate_scroll_bar_position(
                            scroll_bar, view_size, previous_size, page_size, size - page_size + 1
                        );
                    if (new_position != scroll_bar.position())
                    {
                        scroll_bar.set_position(new_position);
                        scroll_bar.scroll_bar_observer_set().scrolled()(new_position);
                    }
                }
            }
            else
            {
                if (view_size <= page_size)
                {
                    const scroll_bar_size_type new_position = 0;
                    if (new_position != scroll_bar.position())
                    {
                        scroll_bar.set_position(new_position);
                        scroll_bar.scroll_bar_observer_set().scrolled()(new_position);
                    }
                }

                scroll_bar.set_enabled(false);
            }
        }

        template <typename ViewSize>
        scroll_bar_size_type calculate_scroll_bar_position(
            const scroll_bar_type&     scroll_bar,
            const ViewSize&            view_size,
            const scroll_bar_size_type previous_size,
            const scroll_bar_size_type page_size,
            const scroll_bar_size_type max
        )
        const
        {
            const boost::rational<scroll_bar_size_type> change_rate = view_size.value() / previous_size;
            const boost::rational<scroll_bar_size_type> half_page_size(page_size, 2);
            if ((scroll_bar.position() + half_page_size) * change_rate < half_page_size)
                return 0;
            const boost::rational<scroll_bar_size_type> new_position =
                (scroll_bar.position() + half_page_size) * change_rate - half_page_size;
            if (new_position > boost::rational<scroll_bar_size_type>(max))
                return max;
            return boost::rational_cast<scroll_bar_size_type>(new_position);
        }


    };


}

#endif
