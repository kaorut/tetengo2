/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FILEPROPERTY_H)
#define BOBURA_COMMAND_FILEPROPERTY_H

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a file property command.

        \tparam Model              A model type.
        \tparam AbstractWindow     An abstract window type.
        \tparam FilePropertyDialog A file property dialog type.
    */
    template <typename Model, typename AbstractWindow, typename FilePropertyDialog>
    class file_property : public command_base<Model, AbstractWindow>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The timetable type.
        typedef typename model_type::timetable_type timetable_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The base type.
        typedef command_base<model_type, abstract_window_type> base_type;

        //! The file property dialog type.
        typedef FilePropertyDialog file_property_dialog_type;

        //! The base type.
        typedef typename file_property_dialog_type::base_type dialog_base_type;

        //! The string type.
        typedef typename file_property_dialog_type::string_type string_type;

        //! The message catalog type.
        typedef typename file_property_dialog_type::message_catalog_type message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file property command.

            \param message_catalog A message catalog.
        */
        explicit file_property(const message_catalog_type& message_catalog)
        :
        m_message_catalog(message_catalog)
        {}


    private:
        // variables

        const message_catalog_type& m_message_catalog;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const
        {
            return true;
        }

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const
        {
            file_property_dialog_type dialog(parent, m_message_catalog);

            dialog.set_line_name(model.timetable().title());
            if (model.has_path())
                dialog.set_file_name(model.path().template string<string_type>());

            dialog.do_modal();
            if (dialog.result() != dialog_base_type::result_accepted)
                return;

            model.timetable().set_title(dialog.line_name());
        }


    };


}}


#endif
