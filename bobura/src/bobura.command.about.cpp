/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include "bobura.command.about.h"


namespace bobura { namespace command
{
    class about::impl
    {
    public:
        // types

        typedef about::model_type model_type;

        typedef about::abstract_window_type abstract_window_type;

        typedef about::about_dialog_type about_dialog_type;

        typedef about::message_catalog_type message_catalog_type;

        typedef about::settings_type settings_type;


        // constructors and destructor

        impl(const message_catalog_type& message_catalog, const settings_type& settings)
        :
        m_message_catalog(message_catalog),
        m_settings(settings)
        {}


        // functions

        bool enabled(const model_type& model)
        const
        {
            return true;
        }

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            about_dialog_type(parent, m_message_catalog, m_settings).do_modal();
        }


    private:
        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


    };


    about::about(const message_catalog_type& message_catalog, const settings_type& settings)
    :
    m_p_impl(tetengo2::make_unique<impl>(message_catalog, settings))
    {}

    about::~about()
    {}
    
    bool about::enabled_impl(const model_type& model)
    const
    {
        return m_p_impl->enabled(model);
    }

    void about::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
