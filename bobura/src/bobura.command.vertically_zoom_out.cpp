/*! \file
    \brief The definition of bobura::command::vertically_zoom_out.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "bobura.command.vertically_zoom_out.h"


namespace bobura { namespace command
{
    class vertically_zoom_out::impl
    {
    public:
        // types

        typedef vertically_zoom_out::model_type model_type;

        typedef vertically_zoom_out::abstract_window_type abstract_window_type;

        typedef vertically_zoom_out::diagram_view_type diagram_view_type;

        typedef vertically_zoom_out::view_scale_list_type view_scale_list_type;


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
            m_diagram_view.set_vertical_scale(scale_list.smaller(m_diagram_view.vertical_scale()));
            parent.window_observer_set().resized()();
            parent.repaint();
        }


    private:
        // variables

        diagram_view_type& m_diagram_view;


    };


    vertically_zoom_out::vertically_zoom_out(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::make_unique<impl>(diagram_view))
    {}

    vertically_zoom_out::~vertically_zoom_out()
    {}
    
    void vertically_zoom_out::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
