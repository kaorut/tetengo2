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

        typedef font_color::font_color_dialog_type font_color_dialog_type;

        typedef font_color::dialog_base_type dialog_base_type;

        typedef font_color::string_type string_type;

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

            dialog.do_modal();
            if (dialog.result() != dialog_base_type::result_type::accepted)
                return;
        
        }


    private:
        // variables

        const message_catalog_type& m_message_catalog;


    };


    font_color::font_color(const message_catalog_type& message_catalog)
    :
    m_p_impl(tetengo2::make_unique<impl>(message_catalog))
    {}

    font_color::~font_color()
    {}
    
    void font_color::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
