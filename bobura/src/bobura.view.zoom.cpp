/*! \file
    \brief The definition of bobura::view::zoom.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "bobura.view.zoom.h"

#include <tetengo2.unique.h>


namespace bobura { namespace view
{
    class zoom::impl
    {
    public:
        // types

        typedef zoom::picture_box_type picture_box_type;

        typedef zoom::diagram_view_type diagram_view_type;


        // constructors and destructor

        impl(picture_box_type& picture_box, diagram_view_type& diagram_view)
        {}


        // functions

        void horizontally_zoom_in()
        {

        }

        void horizontally_zoom_out()
        {

        }

        void vertically_zoom_in()
        {

        }

        void vertically_zoom_out()
        {

        }


    private:
        // variables


    };


    zoom::zoom(picture_box_type& picture_box, diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::make_unique<impl>(picture_box, diagram_view))
    {}

    zoom::~zoom()
    {}

    void zoom::horizontally_zoom_in()
    {
        m_p_impl->horizontally_zoom_in();
    }

    void zoom::horizontally_zoom_out()
    {
        m_p_impl->horizontally_zoom_out();
    }

    void zoom::vertically_zoom_in()
    {
        m_p_impl->vertically_zoom_in();
    }

    void zoom::vertically_zoom_out()
    {
        m_p_impl->vertically_zoom_out();
    }


}}
