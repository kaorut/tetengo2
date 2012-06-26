/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "bobura.command.exit.h"


namespace bobura { namespace command
{
    class exit::impl
    {
    public:
        // types

        typedef exit::model_type model_type;

        typedef exit::abstract_window_type abstract_window_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            parent.close();
        }


    };


    exit::exit()
    :
    m_p_impl(tetengo2::make_unique<impl>())
    {}

    exit::~exit()
    {}
    
    void exit::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
