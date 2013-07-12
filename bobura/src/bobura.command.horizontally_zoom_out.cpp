/*! \file
    \brief The definition of bobura::command::horizontally_zoom_out.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <cassert>

//#include <boost/mpl/at.hpp>

#include <tetengo2.stdalt.h>
#include <tetengo2.utility.h>

#include "bobura.type_list.h"
#include "bobura.view.diagram.zoom.h"

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


        // constructors and destructor

        explicit impl(diagram_view_type& diagram_view)
        :
        m_diagram_view(diagram_view)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            tetengo2::suppress_unused_variable_warning(model);

            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom(p_main_window->diagram_picture_box(), m_diagram_view);

            zoom.horizontally_zoom_out(true);
        }


    private:
        // types

        typedef boost::mpl::at<main_window_type_list, type::main_window::main_window>::type main_window_type;

        typedef view::diagram::zoom zoom_type;


        // variables

        diagram_view_type& m_diagram_view;


    };


    horizontally_zoom_out::horizontally_zoom_out(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(diagram_view))
    {}

    horizontally_zoom_out::~horizontally_zoom_out()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void horizontally_zoom_out::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
