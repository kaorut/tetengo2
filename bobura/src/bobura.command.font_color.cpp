/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "bobura.command.font_color.h"


namespace bobura { namespace command
{
    class font_color::impl
    {
    public:
        // types

        typedef font_color::model_type model_type;

        typedef font_color::abstract_window_type abstract_window_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {}


    };


    font_color::font_color()
    :
    m_p_impl(tetengo2::make_unique<impl>())
    {}

    font_color::~font_color()
    {}
    
    void font_color::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
