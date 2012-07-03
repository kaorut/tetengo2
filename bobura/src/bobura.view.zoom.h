/*! \file
    \brief The definition of bobura::view::zoom.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_ZOOM_H)
#define BOBURA_VIEW_ZOOM_H

//#include <memory>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>

#include "bobura.basic_type_list.h"


namespace bobura { namespace view
{
    /*!
        \brief The class for a zoom of a view.
    */
    class zoom : boost::noncopyable
    {
    public:
        // types

        //! The picture box type.
        typedef boost::mpl::at<ui_type_list, type::ui::picture_box>::type picture_box_type;

        //! The diagram view type.
        typedef boost::mpl::at<view_type_list, type::view::view>::type diagram_view_type;


        // constructors and destructor

        /*!
            \brief Creates a zoom of a view.
        */
        zoom(picture_box_type& picture_box, diagram_view_type& diagram_view);

        /*!
            \brief Destroys a zoom of a view.
        */
        ~zoom();


        // functions

        /*!
            \brief Hozirontally zoom in.

            \param snap_to_scale_list True to snaps the dimension to the scale list.
        */
        void horizontally_zoom_in(bool snap_to_scale_list);

        /*!
            \brief Hozirontally zoom out.

            \param snap_to_scale_list True to snaps the dimension to the scale list.
        */
        void horizontally_zoom_out(bool snap_to_scale_list);

        /*!
            \brief Vertically zoom in.

            \param snap_to_scale_list True to snaps the dimension to the scale list.
        */
        void vertically_zoom_in(bool snap_to_scale_list);

        /*!
            \brief Vertically zoom out.

            \param snap_to_scale_list True to snaps the dimension to the scale list.
        */
        void vertically_zoom_out(bool snap_to_scale_list);


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}


#endif
