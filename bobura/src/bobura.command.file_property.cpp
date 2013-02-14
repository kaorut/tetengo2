/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <tetengo2.cpp11.h>

#include "bobura.command.file_property.h"


namespace bobura { namespace command
{
    class file_property::impl
    {
    public:
        // types

        typedef file_property::model_type model_type;

        typedef file_property::abstract_window_type abstract_window_type;

        typedef file_property::timetable_type timetable_type;

        typedef file_property::file_property_dialog_type file_property_dialog_type;

        typedef file_property::dialog_base_type dialog_base_type;

        typedef file_property::string_type string_type;

        typedef file_property::message_catalog_type message_catalog_type;


        // constructors and destructor

        explicit impl(const message_catalog_type& message_catalog)
        :
        m_message_catalog(message_catalog)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            file_property_dialog_type dialog(parent, m_message_catalog);

            dialog.set_company_name(model.timetable().company_name());
            dialog.set_line_name(model.timetable().line_name());
            dialog.set_note(model.timetable().note());
            if (model.has_path())
                dialog.set_file_name(model.path().template string<string_type>());

            dialog.do_modal();
            if (dialog.result() != dialog_base_type::result_type::accepted)
                return;

            model.timetable().set_company_name(dialog.company_name());
            model.timetable().set_line_name(dialog.line_name());
            model.timetable().set_note(dialog.note());
        }


    private:
        // variables

        const message_catalog_type& m_message_catalog;


    };


    file_property::file_property(const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::make_unique<impl>(message_catalog))
    {}

    file_property::~file_property()
    TETENGO2_CPP11_NOEXCEPT
    {}
    
    void file_property::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
