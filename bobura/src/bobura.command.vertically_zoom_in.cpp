/*! \file
    \brief The definition of bobura::command::vertically_zoom_in.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <cassert>

//#include <boost/mpl/at.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.utility.h>

#include "bobura.type_list.h"
#include "bobura.view.diagram.zoom.h"

#include "bobura.command.vertically_zoom_in.h"


namespace bobura { namespace command
{
    class vertically_zoom_in::impl
    {
    public:
        // types

        typedef vertically_zoom_in::model_type model_type;

        typedef vertically_zoom_in::abstract_window_type abstract_window_type;

        typedef vertically_zoom_in::diagram_view_type diagram_view_type;


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

            main_window_type* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom(p_main_window->diagram_picture_box(), m_diagram_view);

            zoom.vertically_zoom_in(true);
        }


    private:
        // types

        typedef boost::mpl::at<main_window_type_list, type::main_window::main_window>::type main_window_type;

        typedef view::diagram::zoom zoom_type;


        // variables

        diagram_view_type& m_diagram_view;


    };


    vertically_zoom_in::vertically_zoom_in(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::make_unique<impl>(diagram_view))
    {}

    vertically_zoom_in::~vertically_zoom_in()
    TETENGO2_CPP11_NOEXCEPT
    {}
    
    void vertically_zoom_in::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
