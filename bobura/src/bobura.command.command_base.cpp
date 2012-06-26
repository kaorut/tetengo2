/*! \file
    \brief The definition of bobura::command::command_base.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    bool command_base::enabled(const model_type& model)
    const
    {
        return enabled_impl(model);
    }

    void command_base::execute(model_type& model, abstract_window_type& parent)
    const
    {
        execute_impl(model, parent);
    }

    bool command_base::enabled_impl(const model_type& model)
    const
    {
        return true;
    }


}}
