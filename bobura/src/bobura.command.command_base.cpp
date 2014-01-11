/*! \file
    \brief The definition of bobura::command::command_base.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <tetengo2.stdalt.h>
#include <tetengo2.utility.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    parameter_base::~parameter_base()
    TETENGO2_STDALT_NOEXCEPT
    {}

    parameter_base::parameter_base()
    {}

    command_base::~command_base()
    TETENGO2_STDALT_NOEXCEPT
    {}

    bool command_base::enabled(const model_type& model)
    const
    {
        return enabled_impl(model);
    }

    command_base::state_type command_base::state()
    const
    {
        return state_impl();
    }

    void command_base::execute(model_type& model, abstract_window_type& parent)
    const
    {
        execute_impl(model, parent);
    }

    void command_base::execute(model_type& model, abstract_window_type& parent, const parameter_base& parameter)
    const
    {
        execute_impl(model, parent, parameter);
    }

    bool command_base::enabled_impl(const model_type& model)
    const
    {
        tetengo2::suppress_unused_variable_warning(model);

        return true;
    }

    command_base::state_type command_base::state_impl()
    const
    {
        return state_type::default_;
    }

    void command_base::execute_impl(model_type& model, abstract_window_type& parent, const parameter_base& parameter)
    const
    {
        tetengo2::suppress_unused_variable_warning(parameter);

        execute_impl(model, parent);
    }


}}
