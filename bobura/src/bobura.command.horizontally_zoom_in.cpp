/*! \file
    \brief The definition of bobura::command::horizontally_zoom_in.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "bobura.command.horizontally_zoom_in.h"


namespace bobura { namespace command
{
    class horizontally_zoom_in::impl
    {
    public:
        // types

        typedef horizontally_zoom_in::model_type model_type;

        typedef horizontally_zoom_in::abstract_window_type abstract_window_type;

        typedef horizontally_zoom_in::diagram_view_type diagram_view_type;

        typedef horizontally_zoom_in::view_scale_list_type view_scale_list_type;


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
            m_diagram_view.set_horizontal_scale(scale_list.larger(m_diagram_view.horizontal_scale()));
            parent.window_observer_set().resized()();
            parent.repaint();
        }


    private:
        // variables

        diagram_view_type& m_diagram_view;


    };


    horizontally_zoom_in::horizontally_zoom_in(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::make_unique<impl>(diagram_view))
    {}

    horizontally_zoom_in::~horizontally_zoom_in()
    {}
    
    void horizontally_zoom_in::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
