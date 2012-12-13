/*! \file
    \brief The definition of bobura::view::diagram::zoom.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cassert>
#include <memory>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>

#include "bobura.type_list.h"

#include <tetengo2.unique.h>
#include <tetengo2.gui.measure.h>

#include "bobura.view.diagram.zoom.h"


namespace bobura { namespace view { namespace diagram
{
    class zoom::impl : private boost::noncopyable
    {
    public:
        // types

        typedef zoom::picture_box_type picture_box_type;

        typedef zoom::diagram_view_type diagram_view_type;

        typedef zoom::scale_list_type scale_list_type;

        typedef zoom::scale_type scale_type;

        typedef
            boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box>::type
            diagram_picture_box_type;


        // constructors and destructor

        impl(picture_box_type& picture_box, diagram_view_type& diagram_view)
        :
        m_p_diagram_picture_box(dynamic_cast<diagram_picture_box_type*>(&picture_box)),
        m_diagram_view(diagram_view)
        {
            assert(m_p_diagram_picture_box);
        }


        // functions

        void set_horizontal_scale(const scale_type& scale)
        {
            m_diagram_view.set_horizontal_scale(scale);
            m_p_diagram_picture_box->update_scroll_bars(
                m_diagram_view.dimension(), m_diagram_view.page_size(m_p_diagram_picture_box->client_dimension())
            );
        }

        void horizontally_zoom_in(const bool snap_to_scale_list)
        {
            const scale_list_type scale_list;
            set_horizontal_scale(larger(m_diagram_view.horizontal_scale(), scale_list, snap_to_scale_list));
        }

        void horizontally_zoom_out(const bool snap_to_scale_list)
        {
            const scale_list_type scale_list;
            set_horizontal_scale(smaller(m_diagram_view.horizontal_scale(), scale_list, snap_to_scale_list));
        }

        void set_vertical_scale(const scale_type& scale)
        {
            m_diagram_view.set_vertical_scale(scale);
            m_p_diagram_picture_box->update_scroll_bars(
                m_diagram_view.dimension(), m_diagram_view.page_size(m_p_diagram_picture_box->client_dimension())
            );
        }

        void vertically_zoom_in(const bool snap_to_scale_list)
        {
            const scale_list_type scale_list;
            set_vertical_scale(larger(m_diagram_view.vertical_scale(), scale_list, snap_to_scale_list));
        }

        void vertically_zoom_out(const bool snap_to_scale_list)
        {
            const scale_list_type scale_list;
            set_vertical_scale(smaller(m_diagram_view.vertical_scale(), scale_list, snap_to_scale_list));
        }


    private:
        // types

        typedef picture_box_type::fast_canvas_type canvas_type;

        typedef picture_box_type::position_type position_type;

        typedef tetengo2::gui::position<position_type>::left_type left_type;

        typedef tetengo2::gui::position<position_type>::top_type top_type;

        typedef picture_box_type::scroll_bar_type::size_type scroll_bar_size_type;


        // static functions

        static scale_type larger(
            const scale_type&      scale,
            const scale_list_type& scale_list,
            const bool             snap_to_scale_list
        )
        {
            if (snap_to_scale_list)
                return scale_list.larger(scale);

            const scale_type larger_scale = scale + scale_type(1, 10);
            if (larger_scale > scale_list.at(scale_list.size() - 1))
                return scale;

            return larger_scale;
        }

        static scale_type smaller(
            const scale_type&      scale,
            const scale_list_type& scale_list,
            const bool             snap_to_scale_list
        )
        {
            if (snap_to_scale_list)
                return scale_list.smaller(scale);

            const scale_type smaller_scale = scale - scale_type(1, 10);
            if (smaller_scale < scale_list.at(0))
                return scale;

            return smaller_scale;
        }

        static position_type to_position(const scroll_bar_size_type left, const scroll_bar_size_type top)
        {
            return position_type(left_type(left), top_type(top));
        }



        // variables

        diagram_picture_box_type* const m_p_diagram_picture_box;

        diagram_view_type& m_diagram_view;


    };


    zoom::zoom(picture_box_type& picture_box, diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::make_unique<impl>(picture_box, diagram_view))
    {}

    zoom::~zoom()
    {}

    void zoom::set_horizontal_scale(const scale_type& scale)
    {
        m_p_impl->set_horizontal_scale(scale);
    }

    void zoom::horizontally_zoom_in(const bool snap_to_scale_list)
    {
        m_p_impl->horizontally_zoom_in(snap_to_scale_list);
    }

    void zoom::horizontally_zoom_out(const bool snap_to_scale_list)
    {
        m_p_impl->horizontally_zoom_out(snap_to_scale_list);
    }

    void zoom::set_vertical_scale(const scale_type& scale)
    {
        m_p_impl->set_vertical_scale(scale);
    }

    void zoom::vertically_zoom_in(const bool snap_to_scale_list)
    {
        m_p_impl->vertically_zoom_in(snap_to_scale_list);
    }

    void zoom::vertically_zoom_out(const bool snap_to_scale_list)
    {
        m_p_impl->vertically_zoom_out(snap_to_scale_list);
    }


}}}
