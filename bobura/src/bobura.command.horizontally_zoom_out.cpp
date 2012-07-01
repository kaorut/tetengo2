/*! \file
    \brief The definition of bobura::command::horizontally_zoom_out.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cassert>

//#include <boost/mpl/at.hpp>

#include "bobura.type_list.h"

#include "bobura.command.horizontally_zoom_out.h"


namespace bobura { namespace command
{
    class horizontally_zoom_out::impl
    {
    public:
        // types

        typedef horizontally_zoom_out::model_type model_type;

        typedef horizontally_zoom_out::abstract_window_type abstract_window_type;

        typedef horizontally_zoom_out::diagram_view_type diagram_view_type;

        typedef horizontally_zoom_out::view_scale_list_type view_scale_list_type;


        // constructors and destructor

        explicit impl(diagram_view_type& diagram_view)
        :
        m_diagram_view(diagram_view)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            const view_scale_list_type scale_list;
            m_diagram_view.set_horizontal_scale(scale_list.smaller(m_diagram_view.horizontal_scale()));

            main_window_type* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            p_main_window->diagram_picture_box().update_scroll_bars(
                m_diagram_view.dimension(),
                m_diagram_view.page_size(p_main_window->diagram_picture_box().client_dimension()),
                true
            );
        }


    private:
        // types

        typedef boost::mpl::at<main_window_type_list, type::main_window::main_window>::type main_window_type;


        // variables

        diagram_view_type& m_diagram_view;


    };


    horizontally_zoom_out::horizontally_zoom_out(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::make_unique<impl>(diagram_view))
    {}

    horizontally_zoom_out::~horizontally_zoom_out()
    {}
    
    void horizontally_zoom_out::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
