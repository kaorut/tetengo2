/*! \file
    \brief The definition of bobura::command::file_property.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_FILEPROPERTY_H)
#define BOBURA_COMMAND_FILEPROPERTY_H


namespace bobura { namespace command
{
    /*!
        \brief The class template for a file property command.

        \tparam FilePropertyDialog A file property dialog type.
        \tparam Model              A model type.
    */
    template <typename FilePropertyDialog, typename Model>
    class file_property
    {
    public:
        // types

        //! The file property dialog type.
        typedef FilePropertyDialog file_property_dialog_type;

        //! The base type.
        typedef typename file_property_dialog_type::base_type base_type;

        //! The abstract window type.
        typedef
            typename file_property_dialog_type::abstract_window_type
            abstract_window_type;

        //! The string type.
        typedef typename file_property_dialog_type::string_type string_type;

        //! The message catalog type.
        typedef
            typename file_property_dialog_type::message_catalog_type
            message_catalog_type;

        //! The model type.
        typedef Model model_type;
        
        //! The timetable type.
        typedef typename model_type::timetable_type timetable_type;


        // constructors and destructor

        /*!
            \brief Creates a file property command.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        file_property(
            abstract_window_type&       parent,
            model_type&                 model,
            const message_catalog_type& message_catalog
        )
        :
        m_parent(parent),
        m_model(model),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            file_property_dialog_type dialog(
                m_parent, m_message_catalog
            );

            dialog.set_line_name(m_model.timetable().title());
            dialog.set_file_name(
                m_model.path().template string<string_type>()
            );

            dialog.do_modal();
            if (dialog.result() != base_type::result_accepted)
                return;

            m_model.timetable().set_title(dialog.line_name());
        }


    private:
        // variables

        abstract_window_type& m_parent;

        model_type& m_model;

        const message_catalog_type& m_message_catalog;


    };


}}


#endif
