/*! \file
    \brief The definition of bobura::main_window_menu_builder.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <tetengo2.unique.h>

#include "bobura.main_window_menu_builder.h"


namespace bobura
{
    class main_window_menu_builder::impl
    {
    public:
        // types

        typedef main_window_menu_builder::menu_bar_type menu_bar_type;

        typedef main_window_menu_builder::command_set_type command_set_type;

        typedef main_window_menu_builder::model_type model_type;

        typedef main_window_menu_builder::main_window_type main_window_type;

        typedef main_window_menu_builder::message_catalog_type message_catalog_type;


        // constructors and destructor

        impl(
            const command_set_type&     command_set,
            model_type&                 model,
            main_window_type&           main_window,
            const message_catalog_type& message_catalog
        )
        {}


        // functions

        std::unique_ptr<menu_bar_type> build()
        const
        {
            return std::unique_ptr<menu_bar_type>();
        }


    };


    main_window_menu_builder::main_window_menu_builder(
        const command_set_type&     command_set,
        model_type&                 model,
        main_window_type&           main_window,
        const message_catalog_type& message_catalog
    )
    :
    m_p_impl(tetengo2::make_unique<impl>(command_set, model, main_window, message_catalog))
    {}


    std::unique_ptr<main_window_menu_builder::menu_bar_type> main_window_menu_builder::build()
    const
    {
        return m_p_impl->build();
    }


}
