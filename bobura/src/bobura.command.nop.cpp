/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <tetengo2.stdalt.h>
#include <tetengo2.utility.h>

#include "bobura.command.nop.h"


namespace bobura { namespace command
{
    class nop::impl
    {
    public:
        // types

        typedef nop::model_type model_type;

        typedef nop::abstract_window_type abstract_window_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            tetengo2::suppress_unused_variable_warning(model, parent);
        }


    };


    nop::nop()
    :
    m_p_impl(tetengo2::make_unique<impl>())
    {}

    nop::~nop()
    TETENGO2_CPP11_NOEXCEPT
    {}
    
    void nop::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
