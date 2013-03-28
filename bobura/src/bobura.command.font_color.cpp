/*! \file
    \brief The definition of bobura::command::font_color.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <utility>

#include <tetengo2.cpp11.h>

#include "bobura.command.font_color.h"


namespace bobura { namespace command
{
    class font_color::impl
    {
    public:
        // types

        typedef font_color::model_type model_type;

        typedef font_color::abstract_window_type abstract_window_type;

        typedef font_color::font_color_dialog_type font_color_dialog_type;

        typedef font_color::dialog_base_type dialog_base_type;

        typedef font_color::message_catalog_type message_catalog_type;


        // constructors and destructor

        explicit impl(const message_catalog_type& message_catalog)
        :
        m_message_catalog(message_catalog)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            font_color_dialog_type dialog(parent, m_message_catalog);

            const auto& font_color_set = model.timetable().font_color_set();
            dialog.set_background(font_color_set.background());
            dialog.set_company_line_name(
                font_color_set.company_line_name().font(), font_color_set.company_line_name().color()
            );
            dialog.set_note(font_color_set.note().font(), font_color_set.note().color());
            dialog.set_time_line(font_color_set.time_line().font(), font_color_set.time_line().color());
            dialog.set_local_station(font_color_set.local_station().font(), font_color_set.local_station().color());
            dialog.set_principal_station(
                font_color_set.principal_station().font(), font_color_set.principal_station().color()
            );
            dialog.set_local_terminal_station(
                font_color_set.local_terminal_station().font(), font_color_set.local_terminal_station().color()
            );
            dialog.set_principal_terminal_station(
                font_color_set.principal_terminal_station().font(),
                font_color_set.principal_terminal_station().color()
            );
            dialog.set_train_name(font_color_set.train_name());

            dialog.do_modal();
            if (dialog.result() != dialog_base_type::result_type::accepted)
                return;
        
            font_color_set_type new_font_color_set(
                dialog.background(),
                font_color_type(dialog.company_line_name().first, dialog.company_line_name().second),
                font_color_type(dialog.note().first, dialog.note().second),
                font_color_type(dialog.time_line().first, dialog.time_line().second),
                font_color_type(dialog.local_station().first, dialog.local_station().second),
                font_color_type(dialog.principal_station().first, dialog.principal_station().second),
                font_color_type(dialog.local_terminal_station().first, dialog.local_terminal_station().second),
                font_color_type(
                    dialog.principal_terminal_station().first, dialog.principal_terminal_station().second
                ),
                dialog.train_name()
            );
            model.timetable().set_font_color_set(std::move(new_font_color_set));
        }


    private:
        // types

        typedef model_type::timetable_type::font_color_set_type font_color_set_type;

        typedef font_color_set_type::font_color_type font_color_type;


        // variables

        const message_catalog_type& m_message_catalog;


    };


    font_color::font_color(const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::make_unique<impl>(message_catalog))
    {}

    font_color::~font_color()
    TETENGO2_CPP11_NOEXCEPT
    {}
    
    void font_color::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
