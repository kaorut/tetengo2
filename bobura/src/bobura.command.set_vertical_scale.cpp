/*! \file
    \brief The definition of bobura::command::set_vertical_scale.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <cassert>

//#include <boost/mpl/at.hpp>

#include <tetengo2.stdalt.h>
#include <tetengo2.utility.h>

#include "bobura.type_list.h"
#include "bobura.view.diagram.zoom.h"

#include "bobura.command.set_vertical_scale.h"


namespace bobura { namespace command
{
    class set_vertical_scale::impl
    {
    public:
        // types

        typedef set_vertical_scale::model_type model_type;

        typedef set_vertical_scale::abstract_window_type abstract_window_type;

        typedef set_vertical_scale::diagram_view_type diagram_view_type;

        typedef set_vertical_scale::scale_list_type scale_list_type;

        typedef set_vertical_scale::scale_type scale_type;


        // constructors and destructor

        impl(diagram_view_type& diagram_view, const scale_type& scale)
        :
        m_diagram_view(diagram_view),
        m_scale(scale)
        {}


        // functions

        state_type state()
        const
        {
            return m_scale == m_diagram_view.vertical_scale() ? state_type::selected : state_type::default_;
        }

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            tetengo2::suppress_unused_variable_warning(model);

            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom(p_main_window->diagram_picture_box(), m_diagram_view);

            zoom.set_vertical_scale(m_scale);
        }


    private:
        // types

        typedef boost::mpl::at<main_window_type_list, type::main_window::main_window>::type main_window_type;

        typedef view::diagram::zoom zoom_type;


        // variables

        diagram_view_type& m_diagram_view;

        scale_type m_scale;


    };


    set_vertical_scale::set_vertical_scale(diagram_view_type& diagram_view, const scale_type& scale)
    :
    m_p_impl(tetengo2::make_unique<impl>(diagram_view, scale))
    {}

    set_vertical_scale::~set_vertical_scale()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    set_vertical_scale::state_type set_vertical_scale::state_impl()
    const
    {
        return m_p_impl->state();
    }

    void set_vertical_scale::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
