/*! \file
    \brief The definition of bobura::command::nop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#define USE_TYPES_FOR_APPLICATION
#include "bobura.type_list.h"

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

        bool enabled(const model_type& model)
        const
        {
            return true;
        }

        void execute(model_type& model, abstract_window_type& parent)
        const
        {}


    };


    nop::nop()
    :
    m_p_impl(tetengo2::make_unique<impl>())
    {}

    nop::~nop()
    {}
    
    bool nop::enabled_impl(const model_type& model)
    const
    {
        return m_p_impl->enabled(model);
    }

    void nop::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
